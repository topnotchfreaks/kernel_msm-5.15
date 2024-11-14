// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2024, Qualcomm Innovation Center, Inc. All rights reserved.
 *
 */

#define pr_fmt(fmt) "%s: " fmt, __func__

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/extcon.h>

#define HDMI_INPUT_HDMI_IN 1
#define HDMI_INPUT_TYPEC 0

enum hdmi_input_t {
	NONE,
	TYPEC,
	HDMI_IN,
};

struct hdmi_input_mux {
	struct device *dev;
	struct platform_device *pdev;
	int irq;
	u32 hdmi_detect_gpio;
	u32 hdmi_select_gpio;
	enum hdmi_input_t hdmi_src;
	bool hdmi_detect;
	bool hdmi_auto_switch;
	struct extcon_dev *edev;
	struct notifier_block hdmi_sw_nb;
};

static int hdmi_input_mux_parse_dt(struct device *dev,
		struct hdmi_input_mux *pdata)
{
	struct device_node *np = dev->of_node;
	u32 auto_switch_en = 0;
	int ret = 0;
	struct extcon_dev *edev = NULL;

	pdata->hdmi_detect_gpio = of_get_named_gpio(np, "hdmi-detect-gpio", 0);
	if (!gpio_is_valid(pdata->hdmi_detect_gpio)) {
		dev_err(dev, "hdmi detect gpio not specified\n");
		ret = -EINVAL;
	}
	pr_debug("hdmi-detect-gpio=%d\n", pdata->hdmi_detect_gpio);

	pdata->hdmi_select_gpio = of_get_named_gpio(np, "hdmi-select-gpio", 0);
	if (!gpio_is_valid(pdata->hdmi_select_gpio)) {
		dev_err(dev, "hdmi select gpio not specified\n");
		ret = -EINVAL;
	}
	pr_debug("hdmi-select-gpio=%d\n", pdata->hdmi_select_gpio);

	if (!of_property_read_u32(np, "hdmi-auto-switch", &auto_switch_en)) {
		pr_info("Auto detect HDMI input = %s\n",
				(auto_switch_en ? "True" : "False"));
		pdata->hdmi_auto_switch = auto_switch_en;
	} else {
		pr_info("hdmi-auto-switch default sets to true.\n");
		pdata->hdmi_auto_switch = true;
	}

	if (of_property_read_bool(dev->of_node, "extcon")) {
		edev = extcon_get_edev_by_phandle(pdata->dev, 0);
		if (IS_ERR(edev) && PTR_ERR(edev) != -ENODEV) {
			pr_warn("extcon not exist!");
			edev = NULL;
		}
	}

	pdata->edev = edev;
	return ret;
}

static int hdmi_input_mux_gpio_configure(struct hdmi_input_mux *pdata, bool on)
{
	int ret = 0;

	if (on) {
		ret = gpio_request(pdata->hdmi_detect_gpio, "hdmi-detect-gpio");
		if (ret) {
			pr_err("hdmi detect gpio request failed\n");
			goto error;
		}
		ret = gpio_direction_input(pdata->hdmi_detect_gpio);
		if (ret) {
			pr_err("hdmi detect gpio direction failed\n");
			goto hdmi_detect_error;
		}
		ret = gpio_request(pdata->hdmi_select_gpio, "hdmi-select-gpio");
		if (ret) {
			pr_err("hdmi select gpio request failed\n");
			goto hdmi_detect_error;
		}
		/* Default select HDMI_IN port as input. */
		ret = gpio_direction_output(pdata->hdmi_select_gpio, HDMI_INPUT_HDMI_IN);
		if (ret) {
			pr_err("hdmi select gpio direction failed\n");
			goto hdmi_select_error;
		}
		pdata->hdmi_src = HDMI_IN;
	} else {
		gpio_free(pdata->hdmi_select_gpio);
		gpio_free(pdata->hdmi_detect_gpio);
	}
	return ret;
hdmi_select_error:
	gpio_free(pdata->hdmi_select_gpio);
hdmi_detect_error:
	gpio_free(pdata->hdmi_detect_gpio);
error:
	return ret;
}

static void hdmi_input_mux_send_uevent(struct hdmi_input_mux *pdata)
{
	char name[32], status[32];
	char *envp[5];
	char *event_string = "HOTPLUG=1";

	scnprintf(name, 32, "name = %s", "HDMI_IN");
	scnprintf(status, 32, "status = %s", pdata->hdmi_detect ? "connect" : "disconnect");
	pr_debug("[%s]:[%s]\n", name, status);
	envp[0] = name;
	envp[1] = status;
	envp[2] = event_string;
	envp[3] = NULL;
	envp[4] = NULL;
	kobject_uevent_env(&pdata->dev->kobj, KOBJ_CHANGE, envp);
}

static void hdmi_input_mux_auto_switch(struct hdmi_input_mux *pdata)
{
	if (!pdata)
		return;
	pr_debug("HDMI-in %s, auto switch to %s\n",
		(pdata->hdmi_detect ? "connected" : "disconnected"),
		(pdata->hdmi_detect ? "hdmi" : "type-c"));
	if (pdata->hdmi_detect) {
		gpio_set_value(pdata->hdmi_select_gpio, HDMI_INPUT_HDMI_IN);
		pdata->hdmi_src = HDMI_IN;
	} else {
		gpio_set_value(pdata->hdmi_select_gpio, HDMI_INPUT_TYPEC);
		pdata->hdmi_src = TYPEC;
	}
}

static int hdmi_sw_notifier(struct notifier_block *nb,
	unsigned long event, void *ptr)
{
	struct extcon_dev *edev = ptr;
	struct hdmi_input_mux *pdata =
		container_of(nb, struct hdmi_input_mux, hdmi_sw_nb);

	if (!edev || !pdata)
		return NOTIFY_DONE;

	pr_debug("Type-C input %s\n", (event ? "connected" : "disconnected"));
	pdata->hdmi_detect = !event;

	if (pdata->hdmi_auto_switch)
		hdmi_input_mux_auto_switch(pdata);

	return NOTIFY_DONE;
}

static irqreturn_t hdmi_input_mux_irq_thread_handler(int irq, void *dev_id)
{
	struct hdmi_input_mux *pdata = (struct hdmi_input_mux *)dev_id;
	bool old_status;

	old_status = pdata->hdmi_detect;
	if (gpio_get_value(pdata->hdmi_detect_gpio) == 1)
		pdata->hdmi_detect = true;
	else
		pdata->hdmi_detect = false;
	if (old_status != pdata->hdmi_detect)
		hdmi_input_mux_send_uevent(pdata);
	pr_debug("irq hdmi in detect:%s!\n", pdata->hdmi_detect ? "connect" : "disconnect");
	if (pdata->hdmi_auto_switch)
		hdmi_input_mux_auto_switch(pdata);

	return IRQ_HANDLED;
}

static ssize_t hdmi_det_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct hdmi_input_mux *pdata = dev_get_drvdata(dev);

	return scnprintf(buf, 3, "%d\n", pdata->hdmi_detect ? 1 : 0);
}

static ssize_t select_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct hdmi_input_mux *pdata = dev_get_drvdata(dev);

	return scnprintf(buf, 7, "%s",
			(pdata->hdmi_src == HDMI_IN) ? "hdmi\n" : "typec\n");
}

static ssize_t select_store(struct device *dev,
		struct device_attribute *attr, const char *buf,
		size_t count)
{
	struct hdmi_input_mux *pdata = dev_get_drvdata(dev);

	if (!pdata)
		return -EINVAL;

	gpio_direction_output(pdata->hdmi_select_gpio, 1);

	if (strncmp(buf, "typec", 5) == 0) {
		pdata->hdmi_src = TYPEC;
		gpio_set_value(pdata->hdmi_select_gpio, HDMI_INPUT_TYPEC);
		pr_debug("typec!\n");
	} else if (strncmp(buf, "hdmi", 4) == 0) {
		pdata->hdmi_src = HDMI_IN;
		gpio_set_value(pdata->hdmi_select_gpio, HDMI_INPUT_HDMI_IN);
		pr_debug("hdmi!\n");
	} else
		pr_debug("%s", buf);
	return count;
}

static ssize_t auto_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct hdmi_input_mux *pdata = dev_get_drvdata(dev);

	return scnprintf(buf, 6, "%d\n", pdata->hdmi_auto_switch);
}

static ssize_t auto_store(struct device *dev,
		struct device_attribute *attr, const char *buf,
		size_t count)
{
	int auto_switch_en = 0;
	struct hdmi_input_mux *pdata = dev_get_drvdata(dev);

	if (!pdata)
		return -EINVAL;
	if (kstrtoint(buf, 0, &auto_switch_en) != 0)
		return -EINVAL;
	pdata->hdmi_auto_switch = !!auto_switch_en;
	/* IRQ handler wilil store HDMI-in connect status
	 * even if auto switch was disabled.
	 * Check connect status when auto switch enabled,
	 * or end user need re-plug again.
	 */
	if (pdata->hdmi_auto_switch)
		hdmi_input_mux_auto_switch(pdata);

	return count;
}

static DEVICE_ATTR_RO(hdmi_det);
static DEVICE_ATTR_RW(select);
static DEVICE_ATTR_RW(auto);

static struct attribute *hdmi_input_mux_sysfs_attrs[] = {
	&dev_attr_hdmi_det.attr,
	&dev_attr_select.attr,
	&dev_attr_auto.attr,
	NULL,
};

static struct attribute_group hdmi_input_mux_sysfs_attrs_grp = {
	.attrs = hdmi_input_mux_sysfs_attrs,
};

static int hdmi_input_mux_sysfs_init(struct device *dev)
{
	int rc = 0;

	if (!dev) {
		pr_err("%s: Invalid params\n", __func__);
		return -EINVAL;
	}
	rc = sysfs_create_group(&dev->kobj, &hdmi_input_mux_sysfs_attrs_grp);
	if (rc)
		pr_err("%s: sysfs group creation failed %d\n", __func__, rc);
	return rc;
}

static void hdmi_input_mux_sysfs_remove(struct device *dev)
{
	if (!dev)
		return;
	sysfs_remove_group(&dev->kobj, &hdmi_input_mux_sysfs_attrs_grp);
}

static const struct of_device_id hdmi_input_mux_id[] = {
	{ .compatible = "hdmi_input_mux" },
	{},
};

MODULE_DEVICE_TABLE(of, hdmi_input_mux_id);  // of = Open Firmware

static int hdmi_input_mux_probe(struct platform_device *pdev)
{
	struct hdmi_input_mux *pdata;
	struct device *dev = &pdev->dev;
	int ret;

	pdata = devm_kzalloc(dev, sizeof(struct hdmi_input_mux), GFP_KERNEL);
	pdata->dev = dev;
	ret = hdmi_input_mux_parse_dt(&pdev->dev, pdata);

	if (ret) {
		pr_err("failed to parse device tree\n");
		goto error;
	}
	ret = hdmi_input_mux_gpio_configure(pdata, true);
	if (ret) {
		pr_err("failed to configure GPIOs\n");
		goto error;
	}

	dev_set_drvdata(dev, pdata);
	ret = hdmi_input_mux_sysfs_init(dev);
	if (ret) {
		pr_err("sysfs init failed\n");
		goto error_sysfs;
	}

	if (pdata->edev) {
		pdata->hdmi_sw_nb.notifier_call = hdmi_sw_notifier;
		ret = extcon_register_notifier(pdata->edev, EXTCON_MECHANICAL,
				&pdata->hdmi_sw_nb);
		if (ret < 0) {
			pr_err("extcon init failed: %d\n", ret);
			pdata->edev = NULL;
		}
	}

	if (pdata->edev) {
		pdata->hdmi_detect =
			!(extcon_get_state(pdata->edev, EXTCON_MECHANICAL));
	} else {
		/* Extcon not exist, detect hdmi hpd pin to do auto switch. */
		pdata->hdmi_detect =
			!!(gpio_get_value(pdata->hdmi_detect_gpio));
		pdata->irq = gpio_to_irq(pdata->hdmi_detect_gpio);
		ret = request_threaded_irq(pdata->irq, NULL,
				hdmi_input_mux_irq_thread_handler,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				"hdmi_detect_irq", pdata);
		if (ret) {
			pr_err("hdmi_detect_irq failed\n");
			goto error_irq;
		}
	}
	if (pdata->hdmi_auto_switch)
		hdmi_input_mux_auto_switch(pdata);

	dev_info(dev, "%s done\n", __func__);
	return 0;
error_irq:
	disable_irq(pdata->irq);
	free_irq(pdata->irq, pdata);
error_sysfs:
	hdmi_input_mux_gpio_configure(pdata, false);
error:
	devm_kfree(dev, pdata);
	pr_err("hdmi_input_mux init fail!\n");
	return -1;
}

static int hdmi_input_mux_remove(struct platform_device *pdev)
{
	struct hdmi_input_mux *pdata = dev_get_drvdata(&pdev->dev);
	int ret = 0;

	if (!pdata)
		goto end;
	hdmi_input_mux_sysfs_remove(&pdev->dev);
	disable_irq(pdata->irq);
	free_irq(pdata->irq, pdata);
	ret = hdmi_input_mux_gpio_configure(pdata, false);
	devm_kfree(&pdev->dev, pdata);
	pr_info("hdmi_input_mux remove!\n");
end:
	return ret;
}

static struct platform_driver hdmi_input_mux_driver = {
	.probe = hdmi_input_mux_probe,
	.remove = hdmi_input_mux_remove,
	.driver = {
		.name = "hdmi_input_mux",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hdmi_input_mux_id),
	},
};

static int __init hdmi_input_mux_init(void)
{
	pr_info("hdmi_input_mux init!\n");
	return platform_driver_register(&hdmi_input_mux_driver);
}

static void __exit hdmi_input_mux_exit(void)
{
	pr_info("hdmi_input_mux exit!\n");
	platform_driver_unregister(&hdmi_input_mux_driver);
}

MODULE_LICENSE("GPL");
module_init(hdmi_input_mux_init);
module_exit(hdmi_input_mux_exit);
