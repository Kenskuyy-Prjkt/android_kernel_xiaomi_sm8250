#ifndef _LINUX_LUNAR_ATTRIBUTES_H
#define _LINUX_LUNAR_ATTRIBUTES_H

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>

struct lunar_attributes {
    int kgsl_skip_zeroing;
};

extern struct lunar_attributes lunar_data;
#endif /* _LINUX_LUNAR_ATTRIBUTES_H */