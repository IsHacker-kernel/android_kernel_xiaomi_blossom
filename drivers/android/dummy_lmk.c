// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2025 IsHacker
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#ifndef CONFIG_PSI
static const char *minfree = "0,0,0,0,0,0";
static const int adj = 1001;

module_param(minfree, charp, 0444);
module_param(adj, int, 0444);
#endif


static int __init dummy_lmk_init(void)
{
#ifdef CONFIG_PSI
	pr_err("dummy_lmk: Disabling. Please disable CONFIG_PSI first!\n");
	pr_err("dummy_lmk: Userspace lmkd is now active.\n");
#endif
	return 0;
}

static void __exit dummy_lmk_exit(void)
{
	return;
}

module_init(dummy_lmk_init);
module_exit(dummy_lmk_exit);

MODULE_AUTHOR("IsHacker");
MODULE_LICENSE("GPL");
