#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/types.h>

#define DRIVER_AUTHOR "VoDuy"
#define DRIVER_DESCRIPTION "sysfs"
#define DRIVER_VERSION "1.0"
struct mdev_properties
{
    struct kobject *kobj_ref;
} mdev;
static ssize_t sysfs_show(struct kobject *kobject, struct kobj_attribute *attr, char *buf);
static ssize_t sysfs_store(struct kobject *kobject, struct kobj_attribute *attr, const char *buf, size_t count);

static int __init my_sysfs_init(void);
static void __exit my_sysfs_exit(void);

struct kobj_attribute sys_attr = __ATTR(direction, 0660, sysfs_show, sysfs_store);

static int __init my_sysfs_init(void)
{
    pr_info("Hello\n");
    mdev.kobj_ref = kobject_create_and_add("my_sysfs", NULL);
    if (sysfs_create_file(mdev.kobj_ref, &sys_attr.attr)) /* return 0 */
    {
        pr_info("Can't create file\n");
        goto rm_kobject;
    }
    pr_info("Initialize successfully\n");
    return 0;
rm_kobject:
    kobject_put(mdev.kobj_ref);
    return -1;
}
static void __exit my_sysfs_exit(void)
{
    pr_info("Goodbye\n");
    sysfs_remove_file(mdev.kobj_ref, &sys_attr.attr);
    kobject_put(mdev.kobj_ref);
}
static ssize_t sysfs_show(struct kobject *kobject, struct kobj_attribute *attr, char *buf)
{
    pr_info("Sysfs show being called .... \n");
    return 0;
}

static ssize_t sysfs_store(struct kobject *kobject, struct kobj_attribute *attr, const char *buf, size_t count)
{
    pr_info("Sysfs store being called .... \n");
    return count;
}
module_init(my_sysfs_init);
module_exit(my_sysfs_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESCRIPTION);
MODULE_VERSION(DRIVER_VERSION);