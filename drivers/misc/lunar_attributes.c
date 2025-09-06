#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/lunar_attributes.h>

struct lunar_attributes lunar_data = {
    .lunar_kgsl_skip_zeroing = 0,
};

#define LUNAR_ATTR_RW(name) \
static ssize_t name##_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) \
{ \
    return sprintf(buf, "%d\n", lunar_data.name); \
} \
static ssize_t name##_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) \
{ \
    int val; \
    if (kstrtoint(buf, 10, &val)) \
        return -EINVAL; \
    lunar_data.name = val; \
    return count; \
} \
static struct kobj_attribute name##_attr = __ATTR(name, 0644, name##_show, name##_store);

LUNAR_ATTR_RW(lunar_kgsl_skip_zeroing);

static struct attribute *lunar_attrs[] = {
    &lunar_kgsl_skip_zeroing_attr.attr,
    NULL
};

static struct attribute_group lunar_attr_group = {
    .attrs = lunar_attrs,
};

static struct kobject *lunar_kobj;

static int __init lunar_attributes_init(void) {
    int retval;

    lunar_kobj = kobject_create_and_add("lunar_attributes", kernel_kobj);
    if (!lunar_kobj)
        return -ENOMEM;

    retval = sysfs_create_group(lunar_kobj, &lunar_attr_group);
    if (retval)
        kobject_put(lunar_kobj);

    return retval;
}

static void __exit lunar_attributes_exit(void) {
    kobject_put(lunar_kobj);
}

module_init(lunar_attributes_init);
module_exit(lunar_attributes_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("kvsnr113 <kvsnrprojkt113@gmail.com>");
MODULE_DESCRIPTION("LUNAR kgsl skip zeroing attribute module");