// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2021, The Linux Foundation. All rights reserved.
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/io.h>
#include <linux/types.h>
#include "linux/gunyah/gh_mem_notifier.h"
#include "linux/gunyah/gh_rm_drv.h"
#include <linux/pinctrl/consumer.h>
#include <linux/pinctrl/qcom-pinctrl.h>
#include <linux/slab.h>
#include <linux/notifier.h>

#define GH_TLMM_MEM_LABEL 0x8

struct gh_tlmm_mem_info {
	gh_memparcel_handle_t vm_mem_handle;
	u32 *iomem_bases;
	u32 *iomem_sizes;
	u32 iomem_list_size;
};

struct gh_tlmm_vm_info {
	struct notifier_block guest_memshare_nb;
	enum gh_vm_names vmid;
	struct gh_tlmm_mem_info mem_info;
	struct gh_tlmm_mem_info lend_mem_info;
	void *mem_cookie;
};

static struct gh_tlmm_vm_info gh_tlmm_vm_info_data;
static struct device *gh_tlmm_dev;

static struct gh_acl_desc *gh_tlmm_alloc_acl(enum gh_vm_names vm_name,
						bool lend_gpio)
{
	struct gh_acl_desc *acl_desc;
	gh_vmid_t vmid;
	gh_vmid_t primary_vmid;

	gh_rm_get_vmid(vm_name, &vmid);
	gh_rm_get_vmid(GH_PRIMARY_VM, &primary_vmid);

	if (lend_gpio) {
		acl_desc = kzalloc(struct_size(acl_desc, acl_entries, 1),
			GFP_KERNEL);
		if (!acl_desc)
			return ERR_PTR(-ENOMEM);

		acl_desc->n_acl_entries = 1;
		acl_desc->acl_entries[0].vmid = vmid;
		acl_desc->acl_entries[0].perms = GH_RM_ACL_R | GH_RM_ACL_W;
	} else {
		acl_desc = kzalloc(struct_size(acl_desc, acl_entries, 2),
			GFP_KERNEL);
		if (!acl_desc)
			return ERR_PTR(-ENOMEM);

		acl_desc->n_acl_entries = 2;
		acl_desc->acl_entries[0].vmid = vmid;
		acl_desc->acl_entries[0].perms = GH_RM_ACL_R;
		acl_desc->acl_entries[1].vmid = primary_vmid;
		acl_desc->acl_entries[1].perms = GH_RM_ACL_R | GH_RM_ACL_W;
	}

	return acl_desc;
}

static struct gh_sgl_desc *gh_tlmm_alloc_sgl(struct gh_tlmm_mem_info
						*shared_mem_info)
{
	struct gh_sgl_desc *sgl_desc;
	int i;

	sgl_desc = kzalloc(struct_size(sgl_desc, sgl_entries,
				shared_mem_info->iomem_list_size), GFP_KERNEL);
	if (!sgl_desc)
		return ERR_PTR(-ENOMEM);

	sgl_desc->n_sgl_entries = shared_mem_info->iomem_list_size;

	for (i = 0; i < shared_mem_info->iomem_list_size; i++) {
		sgl_desc->sgl_entries[i].ipa_base = shared_mem_info->iomem_bases[i];
		sgl_desc->sgl_entries[i].size = shared_mem_info->iomem_sizes[i];
	}

	return sgl_desc;
}

static int gh_tlmm_vm_mem_share(struct gh_tlmm_vm_info *gh_tlmm_vm_info_data,
			struct gh_tlmm_mem_info *mem_info)
{
	struct gh_acl_desc *acl_desc;
	struct gh_sgl_desc *sgl_desc;
	gh_memparcel_handle_t mem_handle;
	int num_regs = 0;
	int rc = 0;
	bool is_lend;

	if (mem_info == &gh_tlmm_vm_info_data->mem_info)
		is_lend = false;
	else
		is_lend = true;

	num_regs = mem_info->iomem_list_size;
	if (num_regs <= 0)
		return rc;

	acl_desc = gh_tlmm_alloc_acl(gh_tlmm_vm_info_data->vmid, is_lend);

	if (IS_ERR(acl_desc)) {
		dev_err(gh_tlmm_dev, "Failed to get acl of IO memories for TLMM\n");
		return PTR_ERR(acl_desc);
	}

	sgl_desc = gh_tlmm_alloc_sgl(mem_info);
	if (IS_ERR(sgl_desc)) {
		dev_err(gh_tlmm_dev, "Failed to get sgl of IO memories for TLMM\n");
		rc = PTR_ERR(sgl_desc);
		goto sgl_error;
	}

	if (!is_lend)
		rc = gh_rm_mem_share(GH_RM_MEM_TYPE_IO, 0, GH_TLMM_MEM_LABEL,
				acl_desc, sgl_desc, NULL, &mem_handle);
	else
		rc = gh_rm_mem_lend(GH_RM_MEM_TYPE_IO, 0, GH_TLMM_MEM_LABEL,
				acl_desc, sgl_desc, NULL, &mem_handle);
	if (rc) {
		dev_err(gh_tlmm_dev, "Failed to share IO memories for TLMM rc:%d\n", rc);
		goto error;
	}

	mem_info->vm_mem_handle = mem_handle;

error:
	kfree(sgl_desc);
sgl_error:
	kfree(acl_desc);

	return rc;
}

static int __maybe_unused gh_guest_memshare_nb_handler(struct notifier_block *this,
					unsigned long cmd, void *data)
{
	struct gh_tlmm_vm_info *vm_info;
	struct gh_rm_notif_vm_status_payload *vm_status_payload = data;
	u8 vm_status = vm_status_payload->vm_status;
	gh_vmid_t peer_vmid;

	vm_info = container_of(this, struct gh_tlmm_vm_info, guest_memshare_nb);

	if (cmd != GH_RM_NOTIF_VM_STATUS)
		return NOTIFY_DONE;

	gh_rm_get_vmid(GH_TRUSTED_VM, &peer_vmid);

	if (peer_vmid != vm_status_payload->vmid)
		return NOTIFY_DONE;

	/*
	 * Listen to STATUS_READY notification from RM.
	 * These notifications come from RM after PIL loading the VM images.
	 */
	if (vm_status == GH_RM_VM_STATUS_READY) {
		gh_tlmm_vm_mem_share(&gh_tlmm_vm_info_data, &gh_tlmm_vm_info_data.mem_info);
		gh_tlmm_vm_mem_share(&gh_tlmm_vm_info_data, &gh_tlmm_vm_info_data.lend_mem_info);
	}

	return NOTIFY_DONE;
}

static int gh_tlmm_vm_mem_release(struct gh_tlmm_vm_info *gh_tlmm_vm_info_data)
{
	int rc = 0;
	gh_memparcel_handle_t vm_mem_handle;

	vm_mem_handle = gh_tlmm_vm_info_data->mem_info.vm_mem_handle;
	if (!vm_mem_handle) {
		dev_err(gh_tlmm_dev, "Invalid memory handle\n");
		return -EINVAL;
	}

	rc = gh_rm_mem_release(vm_mem_handle, 0);
	if (rc)
		dev_err(gh_tlmm_dev, "VM mem release failed rc:%d\n", rc);

	rc = gh_rm_mem_notify(vm_mem_handle,
		GH_RM_MEM_NOTIFY_OWNER_RELEASED,
		GH_MEM_NOTIFIER_TAG_TLMM, 0);
	if (rc)
		dev_err(gh_tlmm_dev, "Failed to notify mem release to PVM rc:%d\n",
							rc);

	gh_tlmm_vm_info_data->mem_info.vm_mem_handle = 0;
	return rc;
}

static int gh_tlmm_vm_mem_reclaim(struct gh_tlmm_vm_info *gh_tlmm_vm_info_data)
{
	int rc = 0;
	gh_memparcel_handle_t vm_mem_handle;

	vm_mem_handle = gh_tlmm_vm_info_data->mem_info.vm_mem_handle;
	if (!vm_mem_handle) {
		dev_err(gh_tlmm_dev, "Invalid memory handle\n");
		return -EINVAL;
	}

	rc = gh_rm_mem_reclaim(vm_mem_handle, 0);
	if (rc)
		dev_err(gh_tlmm_dev, "VM mem reclaim failed rc:%d\n", rc);

	gh_tlmm_vm_info_data->mem_info.vm_mem_handle = 0;

	return rc;
}

static int gh_tlmm_prepare_iomem(struct platform_device *dev, struct gh_tlmm_mem_info
					*mem_info, char *list_name)
{
	int i, gpio, ret, num_regs = 0;
	struct resource res;
	struct device_node *np = dev->dev.of_node;

	mem_info->iomem_list_size = 0;

	num_regs = of_gpio_named_count(np, list_name);
	if (num_regs < 0)
		return 0;

	mem_info->iomem_list_size = num_regs;

	mem_info->iomem_bases = devm_kcalloc(&dev->dev, num_regs, sizeof(*mem_info->iomem_bases),
							GFP_KERNEL);
	if (!mem_info->iomem_bases)
		return -ENOMEM;

	mem_info->iomem_sizes = devm_kcalloc(&dev->dev, num_regs, sizeof(*mem_info->iomem_sizes),
					GFP_KERNEL);
	if (!mem_info->iomem_sizes)
		return -ENOMEM;

	for (i = 0; i < num_regs; i++)  {
		gpio = of_get_named_gpio(np, list_name, i);

		if (gpio < 0) {
			dev_err(gh_tlmm_dev, "Failed to read gpio list %d\n", gpio);
			return gpio;
		}

		ret = msm_gpio_get_pin_address(gpio, &res);
		if (!ret) {
			dev_err(gh_tlmm_dev, "Invalid gpio = %d\n", gpio);
			return -EINVAL;
		}

		mem_info->iomem_bases[i] = res.start;
		mem_info->iomem_sizes[i] = resource_size(&res);
	}

	return 0;
}

static int gh_tlmm_vm_populate_vm_info(struct platform_device *dev, struct gh_tlmm_vm_info *vm_info)
{
	int rc = 0;
	struct device_node *np = dev->dev.of_node;
	gh_memparcel_handle_t __maybe_unused vm_mem_handle;
	bool master;
	u32 peer_vmid;

	master = of_property_read_bool(np, "qcom,master");
	if (!master) {
		rc = of_property_read_u32_index(np, "qcom,rm-mem-handle",
				1, &vm_mem_handle);
		if (rc) {
			dev_err(gh_tlmm_dev, "Failed to receive mem handle rc:%d\n", rc);
			goto vm_error;
		}

		vm_info->mem_info.vm_mem_handle = vm_mem_handle;
	}

	rc = of_property_read_u32(np, "peer-name", &peer_vmid);
	if (rc) {
		dev_dbg(gh_tlmm_dev, "peer-name not found rc=%x using default\n", rc);
		peer_vmid = GH_TRUSTED_VM;
	}

	vm_info->vmid = peer_vmid;

	rc = gh_tlmm_prepare_iomem(dev, &vm_info->mem_info, "tlmm-vm-gpio-list");
	if (rc < 0) {
		dev_err(gh_tlmm_dev, "Failed to prepare iomem for gpio list %d\n", rc);
		return rc;
	}

	rc = gh_tlmm_prepare_iomem(dev, &vm_info->lend_mem_info, "tlmm-vm-gpio-lend-list");
	if (rc < 0) {
		dev_err(gh_tlmm_dev, "Failed to prepare iomem for gpio lend list%d\n", rc);
		return rc;
	}

	if (vm_info->mem_info.iomem_list_size == 0 &&
		vm_info->lend_mem_info.iomem_list_size == 0) {
		dev_err(gh_tlmm_dev, "Invalid number of gpios specified\n");
		rc = -EINVAL;
		goto vm_error;
	}

	return rc;

vm_error:
	return rc;
}

static void __maybe_unused gh_tlmm_vm_mem_on_release_handler(enum gh_mem_notifier_tag tag,
		unsigned long notif_type, void *entry_data, void *notif_msg)
{
	struct gh_rm_notif_mem_released_payload *release_payload;
	struct gh_tlmm_vm_info *vm_info;

	if (notif_type != GH_RM_NOTIF_MEM_RELEASED) {
		dev_err(gh_tlmm_dev, "Invalid notification type\n");
		return;
	}

	if (tag != GH_MEM_NOTIFIER_TAG_TLMM) {
		dev_err(gh_tlmm_dev, "Invalid tag\n");
		return;
	}

	if (!entry_data || !notif_msg) {
		dev_err(gh_tlmm_dev, "Invalid data or notification message\n");
		return;
	}

	vm_info = (struct gh_tlmm_vm_info *)entry_data;
	if (!vm_info) {
		dev_err(gh_tlmm_dev, "Invalid vm_info\n");
		return;
	}

	release_payload = (struct gh_rm_notif_mem_released_payload  *)notif_msg;
	if (release_payload->mem_handle != vm_info->mem_info.vm_mem_handle &&
	    release_payload->mem_handle != vm_info->lend_mem_info.vm_mem_handle) {
		dev_err(gh_tlmm_dev, "Invalid mem handle detected\n");
		return;
	}

	gh_tlmm_vm_mem_reclaim(vm_info);
}

static int gh_tlmm_vm_mem_access_probe(struct platform_device *pdev)
{
	void __maybe_unused *mem_cookie;
	int owner_vmid, ret;
	struct device_node *node;
	gh_vmid_t vmid;

	gh_tlmm_dev = &pdev->dev;

	if (gh_tlmm_vm_populate_vm_info(pdev, &gh_tlmm_vm_info_data)) {
		dev_err(gh_tlmm_dev, "Failed to populate TLMM VM info\n");
		return -EINVAL;
	}

	node = of_find_compatible_node(NULL, NULL, "qcom,gunyah-vm-id-1.0");
	if (IS_ERR_OR_NULL(node)) {
		node = of_find_compatible_node(NULL, NULL, "qcom,haven-vm-id-1.0");
		if (IS_ERR_OR_NULL(node)) {
			dev_err(gh_tlmm_dev, "Could not find vm-id node\n");
			return -ENODEV;
		}
	}

	ret = of_property_read_u32(node, "qcom,owner-vmid", &owner_vmid);
	if (ret) {
		/* GH_PRIMARY_VM */
		mem_cookie = gh_mem_notifier_register(GH_MEM_NOTIFIER_TAG_TLMM,
					gh_tlmm_vm_mem_on_release_handler, &gh_tlmm_vm_info_data);
		if (IS_ERR(mem_cookie)) {
			dev_err(gh_tlmm_dev, "Failed to register on release notifier%d\n",
						PTR_ERR(mem_cookie));
			return -EINVAL;
		}

		gh_tlmm_vm_info_data.mem_cookie = mem_cookie;
		gh_tlmm_vm_info_data.guest_memshare_nb.notifier_call = gh_guest_memshare_nb_handler;

		gh_tlmm_vm_info_data.guest_memshare_nb.priority = INT_MAX;
		ret = gh_rm_register_notifier(&gh_tlmm_vm_info_data.guest_memshare_nb);
		if (ret)
			return ret;
	} else {
		ret = gh_rm_get_vmid(GH_TRUSTED_VM, &vmid);
		if (ret)
			return ret;

		if (gh_tlmm_vm_info_data.mem_info.iomem_list_size > 0)
			gh_tlmm_vm_mem_release(&gh_tlmm_vm_info_data);
	}

	return 0;

}

static int gh_tlmm_vm_mem_access_remove(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	bool master;

	master = of_property_read_bool(np, "qcom,master");
	if (master)
		gh_mem_notifier_unregister(gh_tlmm_vm_info_data.mem_cookie);
	gh_rm_unregister_notifier(&gh_tlmm_vm_info_data.guest_memshare_nb);

	return 0;
}

static const struct of_device_id gh_tlmm_vm_mem_access_of_match[] = {
	{ .compatible = "qcom,tlmm-vm-mem-access"},
	{}
};
MODULE_DEVICE_TABLE(of, gh_tlmm_vm_mem_access_of_match);

static struct platform_driver gh_tlmm_vm_mem_access_driver = {
	.probe = gh_tlmm_vm_mem_access_probe,
	.remove = gh_tlmm_vm_mem_access_remove,
	.driver = {
		.name = "gh_tlmm_vm_mem_access",
		.of_match_table = gh_tlmm_vm_mem_access_of_match,
	},
};

static int __init gh_tlmm_vm_mem_access_init(void)
{
	return platform_driver_register(&gh_tlmm_vm_mem_access_driver);
}
module_init(gh_tlmm_vm_mem_access_init);

static __exit void gh_tlmm_vm_mem_access_exit(void)
{
	platform_driver_unregister(&gh_tlmm_vm_mem_access_driver);
}
module_exit(gh_tlmm_vm_mem_access_exit);

MODULE_DESCRIPTION("Qualcomm Technologies, Inc. TLMM VM Memory Access Driver");
MODULE_LICENSE("GPL v2");
