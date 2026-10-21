// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 MediaTek Inc.
 */

#define LOG_TAG "dump"

#include "ddp_reg.h"
#include "ddp_log.h"
#include "ddp_dump.h"
#include "ddp_ovl.h"
#include "ddp_wdma.h"
#include "ddp_wdma_ex.h"
#include "ddp_rdma.h"
#include "ddp_rdma_ex.h"
#include "ddp_dsi.h"
#include "ddp_rsz.h"
#ifdef CONFIG_MTK_SMI_EXT
#include "smi_public.h"
#endif

static char *ddp_signal_0(int bit)
{
	switch (bit) {
	case 0:
		return
			"disp_aal0__to__disp_gamma0";
	case 1:
		return
			"disp_ccorr0__to__disp_aal0";
	case 2:
		return
			"disp_color0__to__disp_color0_out_sel_in0";
	case 3:
		return
			"disp_color_out_sel__to__disp_ccorr0";
	case 4:
		return
			"disp_dither0__to__disp_dither0_mout";
	case 5:
		return
			"disp_gamma0__to__disp_dither0";
	case 6:
		return
			"disp_ovl0_2l__to__disp_ovl0_2l_mout";
	case 7:
		return
			"disp_ovl0_2l_mout_out0__to__disp_path0_sel_in1";
	case 8:
		return
			"disp_ovl0_2l_mout_out1__to__disp_wdma0_sel_in2";
	case 9:
		return
			"disp_ovl0_2l_mout_out2__to__disp_rsz0_sel_in1";
	case 10:
		return
			"disp_ovl0__to__disp_ovl0_mout";
	case 11:
		return
			"disp_ovl0_mout_out0__to__disp_path0_sel_in0";
	case 12:
		return
			"disp_ovl0_mout_out1__to__disp_ovl0_2l_in0";
	case 13:
		return
			"disp_ovl0_mout_out2__to__disp_wdma0_sel_in1";
	case 14:
		return
			"disp_ovl0_mout_out3__to__disp_rsz0_sel_in0";
	case 15:
		return
			"disp_path0_sel__to__disp_rdma0";
	case 16:
		return
			"disp_rdma0__to__disp_rdma0_rsz0_in_sout";
	case 17:
		return
			"disp_rdma_rsz_in_sout_out0__to__disp_rdma_rsz_sel_in0";
	case 18:
		return
			"disp_rdma_rsz_in_sout_out1__to__disp_rsz0_sel_in2";
	case 19:
		return
			"disp_rdma0_rsz0_sel__to__disp_rdma0_sout";
	case 20:
		return
			"disp_rdma0_sout_out0__to__dsi0_sel_in0";
	case 21:
		return
			"disp_rdma0_sout_out1__to__disp_color0";
	case 22:
		return
			"disp_rdma0_sout_out2__to__disp_color0_out_sel_in1";
	case 23:
		return
			"disp_rsz0__to__disp_rsz0_mout";
	case 24:
		return
			"disp_rsz0_mout_out0__to__disp_path0_sel_in2";
	case 25:
		return
			"disp_rsz0_mout_out1__to__disp_ovl0_in2";
	case 26:
		return
			"disp_rsz0_mout_out2__to__disp_ovl0_2l_in2";
	case 27:
		return
			"disp_rsz0_mout_out3__to__disp_rdma0_rsz0_sel_in1";
	case 28:
		return
			"disp_rsz0_mout_out4__to__disp_wdma0_sel_in3";
	case 29:
		return
			"disp_rsz0_sel__to__disp_rsz0";
	case 30:
		return
			"disp_wdma0_sel__to__disp_wdma0";
	case 31:
		return
			"dither0_mout_out0__to__dsi0_sel_in1";
	default:
		return NULL;
	}
}

static char *ddp_signal_1(int bit)
{
	switch (bit) {
	case 0:
		return "dither0_mout_out1__to__disp_wdma0_sel_in0";
	case 1:
		return "dsi0_sel__to__dsi0";
	default:
		return NULL;
	}
}

static char *ddp_greq_name(int bit)
{
	switch (bit) {
	case 0:
		return "OVL0 ";
	case 1:
		return "OVL0_2L ";
	case 2:
		return "DISP_RDMA0 ";
	case 3:
		return "DISP_WDMA0 ";
	case 4:
		return "MDP_RDMA0 ";
	case 5:
		return "MDP_WDMA0 ";
	case 6:
		return "MDP_WROT0 ";
	case 7:
		return "DISP_FAKE ";
	default:
		return NULL;
	}
}

static char *ddp_get_mutex_module0_name(unsigned int bit)
{
	switch (bit) {
	case 0:  return "mdp_rdma0";
	case 1:  return "mdp_ccorr0";
	case 2:  return "mdp_rsz0";
	case 3:  return "mdp_rsz1";
	case 4:  return "mdp_wdma0";
	case 5:  return "mdp_wrot0";
	case 6:  return "mdp_tdshp";
	case 7:  return "disp_ovl0";
	case 8:  return "disp_ovl0_2l";
	case 9:  return "disp_rdma0";
	case 10: return "disp_wdma0";
	case 11: return "disp_color0";
	case 12: return "disp_ccorr0";
	case 13: return "disp_aal0";
	case 14: return "disp_gamma0";
	case 15: return "disp_dither0";
	case 16: return "DSI0";
	case 17: return "disp_rsz0";
	case 18: return "img_dl_ready";
	case 19: return "disp_pwm0";
	default: return "mutex-unknown";
	}
}



char *ddp_get_fmt_name(enum DISP_MODULE_ENUM module, unsigned int fmt)
{
	if (module == DISP_MODULE_WDMA0) {
		switch (fmt) {
		case 0:
			return "rgb565";
		case 1:
			return "rgb888";
		case 2:
			return "rgba8888";
		case 3:
			return "argb8888";
		case 4:
			return "uyvy";
		case 5:
			return "yuy2";
		case 7:
			return "y-only";
		case 8:
			return "iyuv";
		case 12:
			return "nv12";
		default:
			DDPDUMP("ddp_get_fmt_name, unknown fmt=%d, module=%d\n",
				fmt, module);
			return "unknown";
		}
	} else if (module == DISP_MODULE_OVL0) {
		switch (fmt) {
		case 0:
			return "rgb565";
		case 1:
			return "rgb888";
		case 2:
			return "rgba8888";
		case 3:
			return "argb8888";
		case 4:
			return "uyvy";
		case 5:
			return "yuyv";
		default:
			DDPDUMP("ddp_get_fmt_name, unknown fmt=%d, module=%d\n",
				fmt, module);
			return "unknown";
		}
	} else if (module == DISP_MODULE_RDMA0 || module == DISP_MODULE_RDMA1) {
		switch (fmt) {
		case 0:
			return "rgb565";
		case 1:
			return "rgb888";
		case 2:
			return "rgba8888";
		case 3:
			return "argb8888";
		case 4:
			return "uyvy";
		case 5:
			return "yuyv";
		default:
			DDPDUMP("ddp_get_fmt_name, unknown fmt=%d, module=%d\n",
				fmt, module);
			return "unknown";
		}
	} else {
		DDPDUMP("ddp_get_fmt_name, unknown module=%d\n", module);
	}

	return "unknown";
}

static char *ddp_clock_0(int bit)
{
	switch (bit) {
	case 7:
		return "ovl0, ";
	case 8:
		return "ovl0_2L, ";
	case 9:
		return "disp_rsz0, ";
	case 10:
		return "rdma0, ";
	case 11:
		return "wdma0, ";
	case 12:
		return "color, ";
	case 13:
		return "ccorr, ";
	case 14:
		return "aal, ";
	case 15:
		return "gamma, ";
	case 16:
		return "dither, ";
	case 17:
		return "dsi0_mm(cg), ";
	case 19:
		return "smi_common(cg), ";
	case 20:
		return "smi_larb0(cg), ";
	case 21:
		return "smi_comm0(cg), ";
	case 22:
		return "smi_comm1(cg), ";
	case 28:
		return "dsi0_interface(cg), ";
	case 29:
		return "26M, ";
	default:
		return NULL;
	}
}

/* mt6765 no need ddp_clock_1 */
/*
 *
 *	static char *ddp_clock_1(int bit)
 *	{
 *		switch (bit) {
 *		case 0:
 *			return "dsi0_mm(cg), ";
 *		case 1:
 *			return "dsi0_interface(cg), ";
 *		case 7:
 *			return "26M, ";
 *		default:
 *			return NULL;
 *		}
 *	}
 */

static inline void mutex_dump_reg(void)
{
	return;
}


static void mutex_dump_analysis(void)
{
	int i = 0;
	int j = 0;
	char mutex_module[512] = { '\0' };
	char *p = NULL;
	int len = 0;
	unsigned int val;

	DDPDUMP("== DISP Mutex Analysis ==\n");
	for (i = 0; i < 5; i++) {
		p = mutex_module;
		len = 0;
		if (DISP_REG_GET(DISP_REG_CONFIG_MUTEX_MOD0(i)) == 0)
			continue;

		val = DISP_REG_GET(DISP_REG_CONFIG_MUTEX_SOF(i));
		len = sprintf(p, "MUTEX%d :SOF=%s,EOF=%s,WAIT=%d,module=(",
			i,
			ddp_get_mutex_sof_name(
				REG_FLD_VAL_GET(SOF_FLD_MUTEX0_SOF, val)),
			ddp_get_mutex_sof_name(
				REG_FLD_VAL_GET(SOF_FLD_MUTEX0_EOF, val)),
			REG_FLD_VAL_GET(SOF_FLD_MUTEX0_SOF_WAIT, val));

		p += len;
		for (j = 0; j < 32; j++) {
			unsigned int regval =
				DISP_REG_GET(DISP_REG_CONFIG_MUTEX_MOD0(i));

			if ((regval & (1 << j))) {
				len = sprintf(p, "%s,",
					ddp_get_mutex_module0_name(j));
				p += len;
			}
		}
		DDPDUMP("%s)\n", mutex_module);
	}
}

static inline void mmsys_config_dump_reg(void)
{
	return;
}

 /*  ------ clock:
  * Before power on mmsys:
  * CLK_CFG_0_CLR (address is 0x10000048) = 0x80000000 (bit 31).
  * Before using DISP_PWM0 or DISP_PWM1:
  * CLK_CFG_1_CLR(address is 0x10000058)=0x80 (bit 7).
  * Before using DPI pixel clock:
  * CLK_CFG_6_CLR(address is 0x100000A8)=0x80 (bit 7).
  *
  * Only need to enable the corresponding bits of MMSYS_CG_CON0 and
  * MMSYS_CG_CON1 for the modules: smi_common, larb0, mdp_crop, fake_eng,
  * mutex_32k, pwm0, pwm1, dsi0, dsi1, dpi.
  * Other bits could keep 1. Suggest to keep smi_common and larb0
  * always clock on.
  *
  * --------valid & ready
  * example:
  * ovl0 -> ovl0_mout_ready=1 means engines after ovl_mout are
  *         ready for receiving data
  *	ovl0_mout_ready=0 means ovl0_mout can not receive data,
  *         maybe ovl0_mout or after engines config error
  * ovl0 -> ovl0_mout_valid=1 means engines before ovl0_mout is OK,
  *	ovl0_mout_valid=0 means ovl can not transfer data to ovl0_mout,
  *         means ovl0 or before engines are not ready.
  */

static void mmsys_config_dump_analysis(void)
{
	unsigned int i = 0;
	unsigned int reg = 0;
	char clock_on[512] = { '\0' };
	char *pos = NULL;
	char *name;
	/* int len = 0; */

	unsigned int valid0 = DISP_REG_GET(DISP_REG_CONFIG_DISP_DL_VALID_0);
	unsigned int valid1 = DISP_REG_GET(DISP_REG_CONFIG_DISP_DL_VALID_1);
	unsigned int ready0 = DISP_REG_GET(DISP_REG_CONFIG_DISP_DL_READY_0);
	unsigned int ready1 = DISP_REG_GET(DISP_REG_CONFIG_DISP_DL_READY_1);
	unsigned int greq = DISP_REG_GET(DISP_REG_CONFIG_SMI_LARB0_GREQ);

	DDPDUMP("== DISP MMSYS_CONFIG ANALYSIS ==\n");
#if 0 /* TODO: mmsys clk?? */
	DDPDUMP("mmsys clock=0x%x, CG_CON0=0x%x, CG_CON1=0x%x\n",
		DISP_REG_GET(DISP_REG_CLK_CFG_0_MM_CLK),
		DISP_REG_GET(DISP_REG_CONFIG_MMSYS_CG_CON0),
		DISP_REG_GET(DISP_REG_CONFIG_MMSYS_CG_CON1));
	if ((DISP_REG_GET(DISP_REG_CLK_CFG_0_MM_CLK) >> 31) & 0x1)
		DDPERR("mmsys clock abnormal!!\n");
#endif

	reg = DISP_REG_GET(DISP_REG_CONFIG_MMSYS_CG_CON0);
	for (i = 0; i < 32; i++) {
		if ((reg & (1 << i)) == 0) {
			name = ddp_clock_0(i);
			if (name)
				strncat(clock_on, name,
					(sizeof(clock_on) -
					strlen(clock_on) - 1));
		}
	}

/* mt6765 no need ddp_clock_1 */
/*
 *	reg = DISP_REG_GET(DISP_REG_CONFIG_MMSYS_CG_CON1);
 *	for (i = 0; i < 32; i++) {
 *		if ((reg & (1 << i)) == 0) {
 *			name = ddp_clock_1(i);
 *			if (name)
 *				strncat(clock_on, name,
 *					(sizeof(clock_on) -
 *					strlen(clock_on) - 1));
 *		}
 *	}
 */
	DDPDUMP("clock on modules:%s\n", clock_on);

	DDPDUMP("valid0=0x%x,valid1=0x%x,ready0=0x%x,ready1=0x%x,greq=0%x\n",
		valid0, valid1, ready0, ready1, greq);
	for (i = 0; i < 32; i++) {
		name = ddp_signal_0(i);
		if (!name)
			continue;

		pos = clock_on;

		if ((valid0 & (1 << i)))
			pos += sprintf(pos, "%s,", "v");
		else
			pos += sprintf(pos, "%s,", "n");

		if ((ready0 & (1 << i)))
			pos += sprintf(pos, "%s", "r");
		else
			pos += sprintf(pos, "%s", "n");

		pos += sprintf(pos, ": %s", name);

		DDPDUMP("%s\n", clock_on);
	}

	for (i = 0; i < 32; i++) {
		name = ddp_signal_1(i);
		if (!name)
			continue;

		pos = clock_on;

		if ((valid1 & (1 << i)))
			pos += sprintf(pos, "%s,", "v");
		else
			pos += sprintf(pos, "%s,", "n");

		if ((ready1 & (1 << i)))
			pos += sprintf(pos, "%s", "r");
		else
			pos += sprintf(pos, "%s", "n");

		pos += sprintf(pos, ": %s", name);

		DDPDUMP("%s\n", clock_on);
	}

	/* greq: 1 means SMI dose not grant, maybe SMI hang */
	if (greq)
		DDPDUMP("greq: 1 means SMI dose not grant, maybe SMI hang");

	clock_on[0] = '\0';
	for (i = 0; i < 32; i++) {
		if (greq & (1 << i)) {
			name = ddp_greq_name(i);
			if (!name)
				continue;
			strncat(clock_on, name,
				(sizeof(clock_on) - strlen(clock_on) - 1));
		}
	}
	DDPDUMP("%s\n", clock_on);
#ifdef CONFIG_MTK_SMI_EXT
	/* dump SMI status, when maybe SMI hang */
	if (greq)
		smi_debug_bus_hang_detect(false, "DISP");
#endif
}

static inline void gamma_dump_reg(enum DISP_MODULE_ENUM module)
{
	return;
}

static inline void gamma_dump_analysis(enum DISP_MODULE_ENUM module)
{
	return;
}


static inline void color_dump_reg(enum DISP_MODULE_ENUM module)
{
	return;
}

static inline void color_dump_analysis(enum DISP_MODULE_ENUM module)
{
	return;
}

static inline void aal_dump_reg(enum DISP_MODULE_ENUM module)
{
	return;
}

static inline void aal_dump_analysis(enum DISP_MODULE_ENUM module)
{
	return;
}

static inline void pwm_dump_reg(enum DISP_MODULE_ENUM module)
{
	return;
}

static void pwm_dump_analysis(enum DISP_MODULE_ENUM module)
{
	int index = 0;
	unsigned int reg_base = 0;

	index = 0;
	reg_base = DISPSYS_PWM0_BASE;

	DDPDUMP("== DISP PWM%d ANALYSIS ==\n", index);
#if 0 /* TODO: clk reg?? */
	DDPDUMP("pwm clock=%d\n",
		(DISP_REG_GET(DISP_REG_CLK_CFG_1_CLR) >> 7) & 0x1);
#endif

}



static inline void ccorr_dump_reg(enum DISP_MODULE_ENUM module)
{
	return;
}

static void ccorr_dump_analyze(enum DISP_MODULE_ENUM module)
{
	int i;
	unsigned int offset = 0x1000;
	int ccorr_en, ccorr_cfg, ccorr_size, ccorr_in_cnt, ccorr_out_cnt;

	if (module == DISP_MODULE_CCORR0)
		i = 0;
	else
		i = 1;

	ccorr_en = DISP_REG_GET(DISP_REG_CCORR_EN + i * offset);
	ccorr_cfg = DISP_REG_GET(DISP_REG_CCORR_CFG + i * offset);
	ccorr_size = DISP_REG_GET(DISP_REG_CCORR_SIZE + i * offset);
	ccorr_in_cnt = DISP_REG_GET(DISP_REG_CCORR_IN_CNT + i * offset);
	ccorr_out_cnt = DISP_REG_GET(DISP_REG_CCORR_OUT_CNT + i * offset);

	DDPDUMP("ccorr: en=%d, config=%d, w=%d, h=%d\n",
		ccorr_en, ccorr_cfg, (ccorr_size >> 16) & 0x1fff,
		ccorr_size & 0x1fff);
	DDPDUMP("ccorr: in_p_cnt=%d, in_l_cnt=%d, out_p_cnt=%d, out_l_cnt=%d\n",
		ccorr_in_cnt & 0x1fff,
		(ccorr_in_cnt >> 16) & 0x1fff,	ccorr_out_cnt & 0x1fff,
		(ccorr_out_cnt >> 16) & 0x1fff);
}

static inline void dither_dump_reg(enum DISP_MODULE_ENUM module)
{
	return;
}


static void dither_dump_analyze(enum DISP_MODULE_ENUM module)
{
	int i;
	unsigned int offset = 0x1000;
	int dither_size, dither_in_cnt, dither_out_cnt;

	if (module == DISP_MODULE_DITHER0)
		i = 0;
	else
		i = 1;

	dither_size = DISP_REG_GET(DISP_REG_DITHER_SIZE + i * offset);
	dither_in_cnt = DISP_REG_GET(DISP_REG_DITHER_IN_CNT + i * offset);
	dither_out_cnt = DISP_REG_GET(DISP_REG_DITHER_OUT_CNT + i * offset);

	DDPDUMP(
		"dither: en=%d, config=%d, w=%d, h=%d, in_p_cnt=%d, in_l_cnt=%d, out_p_cnt=%d, out_l_cnt=%d\n",
		 DISP_REG_GET(DISPSYS_DITHER0_BASE + 0x000 + i * offset),
		 DISP_REG_GET(DISPSYS_DITHER0_BASE + 0x020 + i * offset),
		 (dither_size >> 16) & 0x1fff, dither_size & 0x1fff,
		 dither_in_cnt & 0x1fff, (dither_in_cnt >> 16) & 0x1fff,
		 dither_out_cnt & 0x1fff, (dither_out_cnt >> 16) & 0x1fff);
}

static void dsi_dump_reg(enum DISP_MODULE_ENUM module)
{
	DSI_DumpRegisters(module, 1);
}

int ddp_dump_reg(enum DISP_MODULE_ENUM module)
{
	switch (module) {
	case DISP_MODULE_WDMA0:
		wdma_dump_reg(module);
		break;
	case DISP_MODULE_RDMA0:
	case DISP_MODULE_RDMA1:
		rdma_dump_reg(module);
		break;
	case DISP_MODULE_OVL0:
	case DISP_MODULE_OVL0_2L:
	case DISP_MODULE_OVL1_2L:
		ovl_dump_reg(module);
		break;
	case DISP_MODULE_GAMMA0:
		gamma_dump_reg(module);
		break;
	case DISP_MODULE_CONFIG:
		mmsys_config_dump_reg();
		break;
	case DISP_MODULE_MUTEX:
		mutex_dump_reg();
		break;
	case DISP_MODULE_COLOR0:
		color_dump_reg(module);
		break;
	case DISP_MODULE_AAL0:
		aal_dump_reg(module);
		break;
	case DISP_MODULE_PWM0:
		pwm_dump_reg(module);
		break;
	case DISP_MODULE_DSI0:
	case DISP_MODULE_DSI1:
	case DISP_MODULE_DSIDUAL:
		dsi_dump_reg(module);
		break;
	case DISP_MODULE_CCORR0:
		ccorr_dump_reg(module);
		break;
	case DISP_MODULE_DITHER0:
		dither_dump_reg(module);
		break;
	case DISP_MODULE_RSZ0:
		rsz_dump_reg(module);
		break;
	default:
		DDPDUMP("no dump_reg for module %s(%d)\n",
			ddp_get_module_name(module), module);
	}
	return 0;
}

int ddp_dump_analysis(enum DISP_MODULE_ENUM module)
{
	switch (module) {
	case DISP_MODULE_WDMA0:
		wdma_dump_analysis(module);
		break;
	case DISP_MODULE_RDMA0:
	case DISP_MODULE_RDMA1:
		rdma_dump_analysis(module);
		break;
	case DISP_MODULE_OVL0:
	case DISP_MODULE_OVL0_2L:
	case DISP_MODULE_OVL1_2L:
		ovl_dump_analysis(module);
		break;
	case DISP_MODULE_GAMMA0:
		gamma_dump_analysis(module);
		break;
	case DISP_MODULE_CONFIG:
		mmsys_config_dump_analysis();
		break;
	case DISP_MODULE_MUTEX:
		mutex_dump_analysis();
		break;
	case DISP_MODULE_COLOR0:
		color_dump_analysis(module);
		break;
	case DISP_MODULE_AAL0:
		aal_dump_analysis(module);
		break;
	case DISP_MODULE_PWM0:
		pwm_dump_analysis(module);
		break;
	case DISP_MODULE_DSI0:
	case DISP_MODULE_DSI1:
	case DISP_MODULE_DSIDUAL:
		dsi_analysis(module);
		break;
	case DISP_MODULE_CCORR0:
		ccorr_dump_analyze(module);
		break;
	case DISP_MODULE_DITHER0:
		dither_dump_analyze(module);
		break;
	case DISP_MODULE_RSZ0:
		rsz_dump_analysis(module);
		break;
	default:
		DDPDUMP("no dump_analysis for module %s(%d)\n",
			ddp_get_module_name(module), module);
	}
	return 0;
}
