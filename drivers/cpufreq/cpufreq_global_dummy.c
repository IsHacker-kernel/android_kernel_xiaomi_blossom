// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2025 IsHacker
 */

#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cpu.h>

int freq = 0;

struct kobject *cpufreq_global_dummy_kobject;
struct kobject cpufreq_p0_dummy_kobj;
struct kobject cpufreq_p4_dummy_kobj;


static struct attribute scaling_min_freq = {
 .name = "scaling_min_freq",
 .mode = 0666,
};


static struct attribute scaling_max_freq = {
 .name = "scaling_max_freq",
 .mode = 0666,
};

static struct attribute *default_cpufreq_dummy_attrs[] = {
	&scaling_min_freq,
	&scaling_max_freq,
	NULL
};

static ssize_t cpufreq_dummy_show(struct kobject *kobj, struct attribute *attr, char *buf)
{
	int ret;
	ret = sysfs_emit(buf, "%d", freq);
	return ret;
}

static ssize_t cpufreq_dummy_store(struct kobject *kobj, struct attribute *attr, char *buf, size_t count)
{
	int ret;
	ret = kstrtoint(buf, 10, &freq);

	if(ret < 0)
		return ret;

 	return count;
}

static const struct sysfs_ops cpufreq_dummy_sysfs_ops = {
	.show	= cpufreq_dummy_show,
	.store	= cpufreq_dummy_store,
};

static void cpufreq_dummy_sysfs_release(struct kobject *kobj)
{
	printk("CPUFREQ dummy object destroyed.");
}

static struct kobj_type ktype_dummy_cpufreq = {
	.sysfs_ops	= &cpufreq_dummy_sysfs_ops,
	.default_attrs	= default_cpufreq_dummy_attrs,
	.release	= cpufreq_dummy_sysfs_release,
};

static int __init cpufreq_dummy_init(void) {
	int p0;
	int p4;

	cpufreq_global_dummy_kobject = kobject_create_and_add("cpufreq", &cpu_subsys.dev_root->kobj);

	p0 = kobject_init_and_add(&cpufreq_p0_dummy_kobj, &ktype_dummy_cpufreq,
				   cpufreq_global_dummy_kobject, "policy0");
	p4 = kobject_init_and_add(&cpufreq_p4_dummy_kobj, &ktype_dummy_cpufreq,
				   cpufreq_global_dummy_kobject, "policy4");
	if (p0)
		return -ENOMEM;
	if (p4)
		return -ENOMEM;

	printk("CPUFREQ dummy object created.");

	return 0;
}

static void __exit cpufreq_dummy_exit(void) {
	kobject_put(cpufreq_global_dummy_kobject);
	kobject_put(&cpufreq_p0_dummy_kobj);
	kobject_put(&cpufreq_p4_dummy_kobj);
}

module_init(cpufreq_dummy_init);
module_exit(cpufreq_dummy_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("IsHacker");
