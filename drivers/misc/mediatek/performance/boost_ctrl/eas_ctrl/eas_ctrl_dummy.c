// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2026 IsHacker
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include "boost_ctrl.h"

#ifndef CONFIG_MTK_SCHED_EXTENSION
static ssize_t perfmgr_dummy_proc_write(struct file *filp, const char *ubuf, size_t cnt, loff_t *pos)
{

	return cnt;
}

static int perfmgr_dummy_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%d\n", -1);

	return 0;
}

#define PROC_FOPS_RW(name) \
static int perfmgr_ ## name ## _proc_open(\
	struct inode *inode, struct file *file) \
{ \
	return single_open(file,\
	 perfmgr_dummy_proc_show, PDE_DATA(inode));\
} \
static const struct file_operations perfmgr_ ## name ## _proc_fops = { \
	.owner	= THIS_MODULE, \
	.open	= perfmgr_ ## name ## _proc_open, \
	.read	= seq_read, \
	.llseek	= seq_lseek,\
	.release = single_release,\
	.write	= perfmgr_dummy_proc_write,\
}

#define PROC_ENTRY(name) {__stringify(name), &perfmgr_ ## name ## _proc_fops}

PROC_FOPS_RW(perf_uclamp_min);
PROC_FOPS_RW(perf_fg_uclamp_min);
PROC_FOPS_RW(perf_bg_uclamp_min);
PROC_FOPS_RW(perf_ta_uclamp_min);
#endif

int dummy_uclamp_ctrl_init(struct proc_dir_entry *parent) {
#ifndef CONFIG_MTK_SCHED_EXTENSION
	int i, ret = 0;

	struct pentry {
		const char *name;
		const struct file_operations *fops;
	};

	const struct pentry entries[] = {
		PROC_ENTRY(perf_uclamp_min),
		PROC_ENTRY(perf_fg_uclamp_min),
		PROC_ENTRY(perf_bg_uclamp_min),
		PROC_ENTRY(perf_ta_uclamp_min),
	};

	for (i = 0; i < ARRAY_SIZE(entries); i++) {
		if (!proc_create(entries[i].name, 0644,
					parent, entries[i].fops)) {
			pr_err("%s(), create dummy /eas_ctrl%s failed\n",
					__func__, entries[i].name);
			ret = -EINVAL;
			goto out;
		}
	}

out:
	return ret;
#else
	int ret = 0;
	pr_info("uclamp_ctrl_dummy: CONFIG_MTK_SCHED_EXTENSION is enabled, not creating procfs entries.\n");
	return ret;
#endif
}
