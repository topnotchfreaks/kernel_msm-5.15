// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2025, Qualcomm Innovation Center, Inc. All rights reserved.
 */

#include <linux/clk-provider.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/regmap.h>

#include <dt-bindings/clock/qcom,lpassaoncc-sm6115.h>

#include "clk-alpha-pll.h"
#include "clk-branch.h"
#include "clk-pll.h"
#include "clk-rcg.h"
#include "clk-regmap.h"
#include "clk-regmap-divider.h"
#include "clk-regmap-mux.h"
#include "common.h"
#include "reset.h"
#include "vdd-level-bengal.h"

static DEFINE_VDD_REGULATORS(vdd_lpi_cx, VDD_NUM + 1, 1, vdd_corner);

static struct clk_vdd_class *lpass_aon_cc_sm6115_regulators[] = {
	&vdd_lpi_cx,
};

enum {
	P_BI_TCXO,
	P_LPASS_AON_CC_PLL_OUT_AUX,
	P_LPASS_AON_CC_PLL_OUT_AUX2,
	P_LPASS_AON_CC_PLL_OUT_EARLY,
};

static const struct pll_vco aon_cc_pll_vco[] = {
	{ 1000000000, 2000000000, 0 },
	{ 750000000, 1500000000, 1 },
	{ 500000000, 1000000000, 2 },
	{ 250000000, 500000000, 3 },
};

/* 614.4 MHz Configuration */
static const struct alpha_pll_config lpass_aon_cc_pll_config = {
	.l = 0x20,
	.alpha = 0x0,
	.config_ctl_val = 0x40008529,
	.user_ctl_val = 0x200101,
	.user_ctl_hi_val = 0x00000004,
	.aux_output_mask = BIT(1),
	.aux2_output_mask = BIT(2),
	.early_output_mask = BIT(3),
	.post_div_val = 0x1 << 8,
	.post_div_mask = GENMASK(11, 8),
	.vco_val = 0x2 << 20,
	.vco_mask = GENMASK(21, 20),
};

static struct clk_alpha_pll lpass_aon_cc_pll = {
	.offset = 0x0,
	.vco_table = aon_cc_pll_vco,
	.num_vco = ARRAY_SIZE(aon_cc_pll_vco),
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.clkr = {
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_pll",
			.parent_data = &(const struct clk_parent_data) {
				.fw_name = "bi_tcxo",
			},
			.num_parents = 1,
			.ops = &clk_alpha_pll_ops,
		},
		.vdd_data = {
			.vdd_class = &vdd_lpi_cx,
			.num_rate_max = VDD_NUM,
			.rate_max = (unsigned long[VDD_NUM]) {
				[VDD_MIN] = 1000000000,
				[VDD_NOMINAL] = 2000000000},
		},
	},
};

static const struct clk_div_table post_div_table_lpass_aon_cc_pll_out_aux[] = {
	{ 0x5, 5 },
	{ }
};

static struct clk_alpha_pll_postdiv lpass_aon_cc_pll_out_aux = {
	.offset = 0x0,
	.post_div_shift = 15,
	.post_div_table = post_div_table_lpass_aon_cc_pll_out_aux,
	.num_post_div = ARRAY_SIZE(post_div_table_lpass_aon_cc_pll_out_aux),
	.width = 3,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.clkr.hw.init = &(const struct clk_init_data) {
		.name = "lpass_aon_cc_pll_out_aux",
		.parent_hws = (const struct clk_hw*[]) {
			&lpass_aon_cc_pll.clkr.hw,
		},
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_alpha_pll_postdiv_fabia_ops,
	},
};

static const struct clk_div_table post_div_table_lpass_aon_cc_pll_out_aux2[] = {
	{ 0x1, 2 },
	{ }
};

static struct clk_alpha_pll_postdiv lpass_aon_cc_pll_out_aux2 = {
	.offset = 0x0,
	.post_div_shift = 8,
	.post_div_table = post_div_table_lpass_aon_cc_pll_out_aux2,
	.num_post_div = ARRAY_SIZE(post_div_table_lpass_aon_cc_pll_out_aux2),
	.width = 4,
	.regs = clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_DEFAULT],
	.clkr.hw.init = &(const struct clk_init_data) {
		.name = "lpass_aon_cc_pll_out_aux2",
		.parent_hws = (const struct clk_hw*[]) {
			&lpass_aon_cc_pll.clkr.hw,
		},
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_alpha_pll_postdiv_fabia_ops,
	},
};

static const struct parent_map lpass_aon_cc_parent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_LPASS_AON_CC_PLL_OUT_EARLY, 2 },
};

static const struct clk_parent_data lpass_aon_cc_parent_data_0[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &lpass_aon_cc_pll.clkr.hw },
};

static const struct parent_map lpass_aon_cc_parent_map_1[] = {
	{ P_BI_TCXO, 0 },
};

static const struct clk_parent_data lpass_aon_cc_parent_data_1[] = {
	{ .fw_name = "bi_tcxo" },
};

static const struct parent_map lpass_aon_cc_parent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_LPASS_AON_CC_PLL_OUT_AUX2, 4 },
};

static const struct clk_parent_data lpass_aon_cc_parent_data_2[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &lpass_aon_cc_pll_out_aux2.clkr.hw },
};

static const struct parent_map lpass_aon_cc_parent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_LPASS_AON_CC_PLL_OUT_AUX, 1 },
};

static const struct clk_parent_data lpass_aon_cc_parent_data_4[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &lpass_aon_cc_pll_out_aux.clkr.hw },
};

static const struct freq_tbl ftbl_lpass_aon_cc_cpr_clk_src[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static struct clk_rcg2 lpass_aon_cc_cpr_clk_src = {
	.cmd_rcgr = 0x2004,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = lpass_aon_cc_parent_map_1,
	.freq_tbl = ftbl_lpass_aon_cc_cpr_clk_src,
	.enable_safe_config = true,
	.clkr.hw.init = &(const struct clk_init_data) {
		.name = "lpass_aon_cc_cpr_clk_src",
		.parent_data = lpass_aon_cc_parent_data_1,
		.num_parents = ARRAY_SIZE(lpass_aon_cc_parent_data_1),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	},
	.clkr.vdd_data = {
		.vdd_class = &vdd_lpi_cx,
		.num_rate_max = VDD_NUM,
		.rate_max = (unsigned long[VDD_NUM]) {
			[VDD_LOWER] = 19200000},
	},
};

static const struct freq_tbl ftbl_lpass_aon_cc_main_rcg_clk_src[] = {
	F(38400000, P_LPASS_AON_CC_PLL_OUT_AUX2, 8, 0, 0),
	F(76800000, P_LPASS_AON_CC_PLL_OUT_AUX2, 4, 0, 0),
	{ }
};

static struct clk_rcg2 lpass_aon_cc_main_rcg_clk_src = {
	.cmd_rcgr = 0x1000,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = lpass_aon_cc_parent_map_2,
	.freq_tbl = ftbl_lpass_aon_cc_main_rcg_clk_src,
	.enable_safe_config = true,
	.clkr.hw.init = &(const struct clk_init_data) {
		.name = "lpass_aon_cc_main_rcg_clk_src",
		.parent_data = lpass_aon_cc_parent_data_2,
		.num_parents = ARRAY_SIZE(lpass_aon_cc_parent_data_2),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	},
	.clkr.vdd_data = {
		.vdd_class = &vdd_lpi_cx,
		.num_rate_max = VDD_NUM,
		.rate_max = (unsigned long[VDD_NUM]) {
			[VDD_LOWER] = 38400000,
			[VDD_NOMINAL] = 76800000},
	},
};

static struct clk_rcg2 lpass_aon_cc_q6_xo_clk_src = {
	.cmd_rcgr = 0x8004,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = lpass_aon_cc_parent_map_1,
	.freq_tbl = ftbl_lpass_aon_cc_cpr_clk_src,
	.enable_safe_config = true,
	.clkr.hw.init = &(const struct clk_init_data) {
		.name = "lpass_aon_cc_q6_xo_clk_src",
		.parent_data = lpass_aon_cc_parent_data_1,
		.num_parents = ARRAY_SIZE(lpass_aon_cc_parent_data_1),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	},
	.clkr.vdd_data = {
		.vdd_class = &vdd_lpi_cx,
		.num_rate_max = VDD_NUM,
		.rate_max = (unsigned long[VDD_NUM]) {
			[VDD_LOWER] = 19200000},
	},
};

static const struct freq_tbl ftbl_lpass_aon_cc_tx_mclk_rcg_clk_src[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(24576000, P_LPASS_AON_CC_PLL_OUT_AUX, 5, 0, 0),
	{ }
};

static struct clk_rcg2 lpass_aon_cc_tx_mclk_rcg_clk_src = {
	.cmd_rcgr = 0x13004,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = lpass_aon_cc_parent_map_4,
	.freq_tbl = ftbl_lpass_aon_cc_tx_mclk_rcg_clk_src,
	.enable_safe_config = true,
	.clkr.hw.init = &(const struct clk_init_data) {
		.name = "lpass_aon_cc_tx_mclk_rcg_clk_src",
		.parent_data = lpass_aon_cc_parent_data_4,
		.num_parents = ARRAY_SIZE(lpass_aon_cc_parent_data_4),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	},
	.clkr.vdd_data = {
		.vdd_class = &vdd_lpi_cx,
		.num_rate_max = VDD_NUM,
		.rate_max = (unsigned long[VDD_NUM]) {
			[VDD_LOWER] = 24576000},
	},
};

static struct clk_rcg2 lpass_aon_cc_va_rcg_clk_src = {
	.cmd_rcgr = 0x12004,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = lpass_aon_cc_parent_map_1,
	.freq_tbl = ftbl_lpass_aon_cc_cpr_clk_src,
	.enable_safe_config = true,
	.clkr.hw.init = &(const struct clk_init_data) {
		.name = "lpass_aon_cc_va_rcg_clk_src",
		.parent_data = lpass_aon_cc_parent_data_1,
		.num_parents = ARRAY_SIZE(lpass_aon_cc_parent_data_1),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	},
	.clkr.vdd_data = {
		.vdd_class = &vdd_lpi_cx,
		.num_rate_max = VDD_NUM,
		.rate_max = (unsigned long[VDD_NUM]) {
			[VDD_LOWER] = 19200000},
	},
};

static const struct freq_tbl ftbl_lpass_aon_cc_vs_vddcx_clk_src[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(614400000, P_LPASS_AON_CC_PLL_OUT_EARLY, 1, 0, 0),
	{ }
};

static struct clk_rcg2 lpass_aon_cc_vs_vddcx_clk_src = {
	.cmd_rcgr = 0x15010,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = lpass_aon_cc_parent_map_0,
	.freq_tbl = ftbl_lpass_aon_cc_vs_vddcx_clk_src,
	.enable_safe_config = true,
	.clkr.hw.init = &(const struct clk_init_data) {
		.name = "lpass_aon_cc_vs_vddcx_clk_src",
		.parent_data = lpass_aon_cc_parent_data_0,
		.num_parents = ARRAY_SIZE(lpass_aon_cc_parent_data_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	},
	.clkr.vdd_data = {
		.vdd_class = &vdd_lpi_cx,
		.num_rate_max = VDD_NUM,
		.rate_max = (unsigned long[VDD_NUM]) {
			[VDD_LOWER] = 614400000},
	},
};

static struct clk_rcg2 lpass_aon_cc_vs_vddmx_clk_src = {
	.cmd_rcgr = 0x15000,
	.mnd_width = 0,
	.hid_width = 5,
	.parent_map = lpass_aon_cc_parent_map_0,
	.freq_tbl = ftbl_lpass_aon_cc_vs_vddcx_clk_src,
	.enable_safe_config = true,
	.clkr.hw.init = &(const struct clk_init_data) {
		.name = "lpass_aon_cc_vs_vddmx_clk_src",
		.parent_data = lpass_aon_cc_parent_data_0,
		.num_parents = ARRAY_SIZE(lpass_aon_cc_parent_data_0),
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_rcg2_ops,
	},
	.clkr.vdd_data = {
		.vdd_class = &vdd_lpi_cx,
		.num_rate_max = VDD_NUM,
		.rate_max = (unsigned long[VDD_NUM]) {
			[VDD_LOWER] = 614400000},
	},
};

static struct clk_regmap_div lpass_aon_cc_cdiv_tx_mclk_div_clk_src = {
	.reg = 0x13010,
	.shift = 0,
	.width = 2,
	.clkr.hw.init = &(const struct clk_init_data) {
		.name = "lpass_aon_cc_cdiv_tx_mclk_div_clk_src",
		.parent_hws = (const struct clk_hw*[]) {
			&lpass_aon_cc_tx_mclk_rcg_clk_src.clkr.hw,
		},
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_regmap_div_ro_ops,
	},
};

static struct clk_regmap_div lpass_aon_cc_cdiv_va_div_clk_src = {
	.reg = 0x12010,
	.shift = 0,
	.width = 2,
	.clkr.hw.init = &(const struct clk_init_data) {
		.name = "lpass_aon_cc_cdiv_va_div_clk_src",
		.parent_hws = (const struct clk_hw*[]) {
			&lpass_aon_cc_va_rcg_clk_src.clkr.hw,
		},
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
		.ops = &clk_regmap_div_ro_ops,
	},
};

static struct clk_branch lpass_aon_cc_ahb_timeout_clk = {
	.halt_reg = 0x9030,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = {
		.enable_reg = 0x9030,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_ahb_timeout_clk",
			.parent_hws = (const struct clk_hw*[]) {
				&lpass_aon_cc_main_rcg_clk_src.clkr.hw,
			},
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_aon_h_clk = {
	.halt_reg = 0x903c,
	.halt_check = BRANCH_HALT,
	.clkr = {
		.enable_reg = 0x903c,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_aon_h_clk",
			.parent_hws = (const struct clk_hw*[]) {
				&lpass_aon_cc_main_rcg_clk_src.clkr.hw,
			},
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_bus_alt_clk = {
	.halt_reg = 0x9048,
	.halt_check = BRANCH_HALT,
	.clkr = {
		.enable_reg = 0x9048,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_bus_alt_clk",
			.parent_hws = (const struct clk_hw*[]) {
				&lpass_aon_cc_main_rcg_clk_src.clkr.hw,
			},
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_csr_h_clk = {
	.halt_reg = 0x9010,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = {
		.enable_reg = 0x9010,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_csr_h_clk",
			.parent_hws = (const struct clk_hw*[]) {
				&lpass_aon_cc_main_rcg_clk_src.clkr.hw,
			},
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_mcc_access_clk = {
	.halt_reg = 0x904c,
	.halt_check = BRANCH_HALT,
	.clkr = {
		.enable_reg = 0x904c,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_mcc_access_clk",
			.parent_hws = (const struct clk_hw*[]) {
				&lpass_aon_cc_main_rcg_clk_src.clkr.hw,
			},
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_pdc_h_clk = {
	.halt_reg = 0x900c,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = {
		.enable_reg = 0x900c,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_pdc_h_clk",
			.parent_hws = (const struct clk_hw*[]) {
				&lpass_aon_cc_main_rcg_clk_src.clkr.hw,
			},
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_q6_atbm_clk = {
	.halt_reg = 0xa010,
	.halt_check = BRANCH_HALT,
	.clkr = {
		.enable_reg = 0xa010,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_q6_atbm_clk",
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_qsm_xo_clk = {
	.halt_reg = 0x6000,
	.halt_check = BRANCH_HALT,
	.clkr = {
		.enable_reg = 0x6000,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_qsm_xo_clk",
			.parent_hws = (const struct clk_hw*[]) {
				&lpass_aon_cc_q6_xo_clk_src.clkr.hw,
			},
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_rsc_hclk_clk = {
	.halt_reg = 0x9078,
	.halt_check = BRANCH_HALT,
	.hwcg_reg = 0x9078,
	.hwcg_bit = 1,
	.clkr = {
		.enable_reg = 0x9078,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_rsc_hclk_clk",
			.parent_hws = (const struct clk_hw*[]) {
				&lpass_aon_cc_main_rcg_clk_src.clkr.hw,
			},
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_sleep_clk = {
	.halt_reg = 0x10004,
	.halt_check = BRANCH_HALT,
	.clkr = {
		.enable_reg = 0x10004,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_sleep_clk",
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_ssc_h_clk = {
	.halt_reg = 0x9040,
	.halt_check = BRANCH_HALT,
	.clkr = {
		.enable_reg = 0x9040,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_ssc_h_clk",
			.parent_hws = (const struct clk_hw*[]) {
				&lpass_aon_cc_main_rcg_clk_src.clkr.hw,
			},
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_tx_mclk_2x_clk = {
	.halt_reg = 0x1300c,
	.halt_check = BRANCH_HALT,
	.clkr = {
		.enable_reg = 0x1300c,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_tx_mclk_2x_clk",
			.parent_hws = (const struct clk_hw*[]) {
				&lpass_aon_cc_tx_mclk_rcg_clk_src.clkr.hw,
			},
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_tx_mclk_clk = {
	.halt_reg = 0x13014,
	.halt_check = BRANCH_HALT,
	.clkr = {
		.enable_reg = 0x13014,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_tx_mclk_clk",
			.parent_hws = (const struct clk_hw*[]) {
				&lpass_aon_cc_cdiv_tx_mclk_div_clk_src.clkr.hw,
			},
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_va_2x_clk = {
	.halt_reg = 0x1200c,
	.halt_check = BRANCH_HALT,
	.clkr = {
		.enable_reg = 0x1200c,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_va_2x_clk",
			.parent_hws = (const struct clk_hw*[]) {
				&lpass_aon_cc_va_rcg_clk_src.clkr.hw,
			},
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_va_clk = {
	.halt_reg = 0x12014,
	.halt_check = BRANCH_HALT,
	.clkr = {
		.enable_reg = 0x12014,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_va_clk",
			.parent_hws = (const struct clk_hw*[]) {
				&lpass_aon_cc_cdiv_va_div_clk_src.clkr.hw,
			},
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_va_mem0_clk = {
	.halt_reg = 0x9028,
	.halt_check = BRANCH_HALT,
	.clkr = {
		.enable_reg = 0x9028,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_va_mem0_clk",
			.parent_hws = (const struct clk_hw*[]) {
				&lpass_aon_cc_main_rcg_clk_src.clkr.hw,
			},
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_vs_vddcx_clk = {
	.halt_reg = 0x15018,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = {
		.enable_reg = 0x15018,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_vs_vddcx_clk",
			.parent_hws = (const struct clk_hw*[]) {
				&lpass_aon_cc_vs_vddcx_clk_src.clkr.hw,
			},
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_branch lpass_aon_cc_vs_vddmx_clk = {
	.halt_reg = 0x15008,
	.halt_check = BRANCH_HALT_VOTED,
	.clkr = {
		.enable_reg = 0x15008,
		.enable_mask = BIT(0),
		.hw.init = &(const struct clk_init_data) {
			.name = "lpass_aon_cc_vs_vddmx_clk",
			.parent_hws = (const struct clk_hw*[]) {
				&lpass_aon_cc_vs_vddmx_clk_src.clkr.hw,
			},
			.num_parents = 1,
			.flags = CLK_SET_RATE_PARENT,
			.ops = &clk_branch2_ops,
		},
	},
};

static struct clk_regmap *lpass_aon_cc_sm6115_clocks[] = {
	[LPASS_AON_CC_AHB_TIMEOUT_CLK] = &lpass_aon_cc_ahb_timeout_clk.clkr,
	[LPASS_AON_CC_AON_H_CLK] = &lpass_aon_cc_aon_h_clk.clkr,
	[LPASS_AON_CC_BUS_ALT_CLK] = &lpass_aon_cc_bus_alt_clk.clkr,
	[LPASS_AON_CC_CDIV_TX_MCLK_DIV_CLK_SRC] = &lpass_aon_cc_cdiv_tx_mclk_div_clk_src.clkr,
	[LPASS_AON_CC_CDIV_VA_DIV_CLK_SRC] = &lpass_aon_cc_cdiv_va_div_clk_src.clkr,
	[LPASS_AON_CC_CPR_CLK_SRC] = &lpass_aon_cc_cpr_clk_src.clkr,
	[LPASS_AON_CC_CSR_H_CLK] = &lpass_aon_cc_csr_h_clk.clkr,
	[LPASS_AON_CC_MAIN_RCG_CLK_SRC] = &lpass_aon_cc_main_rcg_clk_src.clkr,
	[LPASS_AON_CC_MCC_ACCESS_CLK] = &lpass_aon_cc_mcc_access_clk.clkr,
	[LPASS_AON_CC_PDC_H_CLK] = &lpass_aon_cc_pdc_h_clk.clkr,
	[LPASS_AON_CC_PLL] = &lpass_aon_cc_pll.clkr,
	[LPASS_AON_CC_PLL_OUT_AUX] = &lpass_aon_cc_pll_out_aux.clkr,
	[LPASS_AON_CC_PLL_OUT_AUX2] = &lpass_aon_cc_pll_out_aux2.clkr,
	[LPASS_AON_CC_Q6_ATBM_CLK] = &lpass_aon_cc_q6_atbm_clk.clkr,
	[LPASS_AON_CC_Q6_XO_CLK_SRC] = &lpass_aon_cc_q6_xo_clk_src.clkr,
	[LPASS_AON_CC_QSM_XO_CLK] = &lpass_aon_cc_qsm_xo_clk.clkr,
	[LPASS_AON_CC_RSC_HCLK_CLK] = &lpass_aon_cc_rsc_hclk_clk.clkr,
	[LPASS_AON_CC_SLEEP_CLK] = &lpass_aon_cc_sleep_clk.clkr,
	[LPASS_AON_CC_SSC_H_CLK] = &lpass_aon_cc_ssc_h_clk.clkr,
	[LPASS_AON_CC_TX_MCLK_2X_CLK] = &lpass_aon_cc_tx_mclk_2x_clk.clkr,
	[LPASS_AON_CC_TX_MCLK_CLK] = &lpass_aon_cc_tx_mclk_clk.clkr,
	[LPASS_AON_CC_TX_MCLK_RCG_CLK_SRC] = &lpass_aon_cc_tx_mclk_rcg_clk_src.clkr,
	[LPASS_AON_CC_VA_2X_CLK] = &lpass_aon_cc_va_2x_clk.clkr,
	[LPASS_AON_CC_VA_CLK] = &lpass_aon_cc_va_clk.clkr,
	[LPASS_AON_CC_VA_MEM0_CLK] = &lpass_aon_cc_va_mem0_clk.clkr,
	[LPASS_AON_CC_VA_RCG_CLK_SRC] = &lpass_aon_cc_va_rcg_clk_src.clkr,
	[LPASS_AON_CC_VS_VDDCX_CLK] = &lpass_aon_cc_vs_vddcx_clk.clkr,
	[LPASS_AON_CC_VS_VDDCX_CLK_SRC] = &lpass_aon_cc_vs_vddcx_clk_src.clkr,
	[LPASS_AON_CC_VS_VDDMX_CLK] = &lpass_aon_cc_vs_vddmx_clk.clkr,
	[LPASS_AON_CC_VS_VDDMX_CLK_SRC] = &lpass_aon_cc_vs_vddmx_clk_src.clkr,
};

static const struct regmap_config lpass_aon_cc_sm6115_regmap_config = {
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_register = 0x20008,
	.fast_io = true,
};

static struct qcom_cc_desc lpass_aon_cc_sm6115_desc = {
	.config = &lpass_aon_cc_sm6115_regmap_config,
	.clks = lpass_aon_cc_sm6115_clocks,
	.num_clks = ARRAY_SIZE(lpass_aon_cc_sm6115_clocks),
	.clk_regulators = lpass_aon_cc_sm6115_regulators,
	.num_clk_regulators = ARRAY_SIZE(lpass_aon_cc_sm6115_regulators),
};

static const struct of_device_id lpass_aon_cc_sm6115_match_table[] = {
	{ .compatible = "qcom,lpassaoncc-sm6115" },
	{ }
};
MODULE_DEVICE_TABLE(of, lpass_aon_cc_sm6115_match_table);

static int lpass_aon_cc_sm6115_probe(struct platform_device *pdev)
{
	struct regmap *regmap;
	int ret;

	regmap = qcom_cc_map(pdev, &lpass_aon_cc_sm6115_desc);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	ret = qcom_cc_runtime_init(pdev, &lpass_aon_cc_sm6115_desc);
	if (ret)
		return ret;

	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret)
		return ret;

	clk_alpha_pll_configure(&lpass_aon_cc_pll, regmap, &lpass_aon_cc_pll_config);

	/*
	 * Keep clocks always enabled:
	 *	lpass_aon_cc_q6_ahbs_clk
	 *	lpass_aon_cc_q6_ahbm_clk
	 */
	regmap_update_bits(regmap, 0x9020, BIT(0), BIT(0));
	regmap_update_bits(regmap, 0x901C, BIT(0), BIT(0));


	ret = qcom_cc_really_probe(pdev, &lpass_aon_cc_sm6115_desc, regmap);
	if (ret) {
		dev_err(&pdev->dev, "Failed to register LPASS AON CC clocks ret=%d\n", ret);
		goto err_put_rpm;
	}

	dev_info(&pdev->dev, "Registered LPASS AON CC clocks\n");

err_put_rpm:
	pm_runtime_put_sync(&pdev->dev);
	return ret;
}

static void lpass_aon_cc_sm6115_sync_state(struct device *dev)
{
	qcom_cc_sync_state(dev, &lpass_aon_cc_sm6115_desc);
}

static const struct dev_pm_ops lpass_aon_cc_sm6115_pm_ops = {
	SET_RUNTIME_PM_OPS(qcom_cc_runtime_suspend, qcom_cc_runtime_resume, NULL)
};

static struct platform_driver lpass_aon_cc_sm6115_driver = {
	.probe = lpass_aon_cc_sm6115_probe,
	.driver = {
		.name = "lpassaoncc-sm6115",
		.of_match_table = lpass_aon_cc_sm6115_match_table,
		.sync_state = lpass_aon_cc_sm6115_sync_state,
		.pm = &lpass_aon_cc_sm6115_pm_ops,
	},
};

static int __init lpass_aon_cc_sm6115_init(void)
{
	return platform_driver_register(&lpass_aon_cc_sm6115_driver);
}
subsys_initcall(lpass_aon_cc_sm6115_init);

static void __exit lpass_aon_cc_sm6115_exit(void)
{
	platform_driver_unregister(&lpass_aon_cc_sm6115_driver);
}
module_exit(lpass_aon_cc_sm6115_exit);


MODULE_DESCRIPTION("QTI LPASSAONCC SM6115 Driver");
MODULE_LICENSE("GPL");
