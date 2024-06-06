#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/printk.h>
#include <linux/atomic.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#define DRIVER_AUTHOR "VoDuy"
#define DRIVER_DESC "Hello kernel file operations"
#define DRIVER_VERS "1.0"
#define NPAGES 1
static ssize_t m_read(struct file *filp, char __user *user_buf, size_t size, loff_t *offset);
static ssize_t m_write(struct file *filp, const char __user *user_buf, size_t size, loff_t *offset);
static int m_open(struct inode *inode, struct file *file);
static int m_release(struct inode *inode, struct file *file);
static int __init chrdev_init(void);
static void __exit chrdev_exit(void);
size_t to_read,to_write;
struct my_dev_properties
{
    int32_t size;
    dev_t dev_num;
    struct class *my_class;
    struct cdev my_cdev;
    char *kmalloc_ptr;
} my_dev;
struct file_operations fops =
    {
        .owner = THIS_MODULE,
        .read = m_read,
        .write = m_write,
        .open = m_open,
        .release = m_release};
enum
{
    CDEV_NO_USE = 0,
    CDEV_BEING_USED = 1
};
static atomic_t state_of_module = ATOMIC_INIT(CDEV_NO_USE);
static int count = 0;
static ssize_t m_read(struct file *filp, char __user *user_buf, size_t size, loff_t *offset)
{
    pr_info("Function read() being called\n");
    if(size ==0)
    {
        pr_info("Null size \n");
        return 0;

    }
    to_read = (size > my_dev.size - *offset) ? (my_dev.size - *offset) : size;
    if (copy_to_user(user_buf, my_dev.kmalloc_ptr + *offset, to_read) != 0)
    {
        return -EFAULT;
    }
    *offset += to_read;
    return to_read;
}
static ssize_t m_write(struct file *filp, const char __user *user_buf, size_t size, loff_t *offset)
{
    pr_info("Function write() being called\n");
    
    if(*offset > NPAGES*PAGE_SIZE)
    {
        return -EFAULT;
    }
    to_write = (size + *offset) > (NPAGES * PAGE_SIZE) ? (NPAGES * PAGE_SIZE - *offset) : size;

    memset(my_dev.kmalloc_ptr, 0, NPAGES * PAGE_SIZE);
    if (copy_from_user(my_dev.kmalloc_ptr + *offset, user_buf, to_write) != 0)
    {
        return -EFAULT;
    }
    pr_info("Data from usr: %s", my_dev.kmalloc_ptr);
    *offset += to_write;
    my_dev.size = *offset;
    return to_write;
}
static int m_open(struct inode *inode, struct file *file)
{
    pr_info("Function open() being called\n");

    if (atomic_cmpxchg(&state_of_module, CDEV_NO_USE, CDEV_BEING_USED))
    {
        pr_info("You are being locked %d times, stop using this module\n",++count);
        pr_info("Being used this module by another process\n");
        return -EBUSY; // LOG: Device or resource busy
    }
    pr_info("You are using this module\n");
    try_module_get(THIS_MODULE);
    pr_info("Quantity of user: %d\n", module_refcount(THIS_MODULE));
    return 0;
}
static int m_release(struct inode *inode, struct file *file)
{
    pr_info("Function close() being called\n");
    atomic_set(&state_of_module, CDEV_NO_USE);
    module_put(THIS_MODULE);
    return 0;
}
static int __init chrdev_init(void)
{
    if (alloc_chrdev_region(&my_dev.dev_num, 0, 1, "my_device_number") < 0)
    {
        pr_info("Can't alloc chrdev number\n");
        return -1;
    }

    pr_info("Create device_number successfully, major = %d, minor = %d\n", MAJOR(my_dev.dev_num), MINOR(my_dev.dev_num));
    if ((my_dev.my_class = class_create(THIS_MODULE, "my_new_class")) == NULL)
    {
        pr_info("Can't create class \n");
        goto rm_dev_num;
    }
    if ((device_create(my_dev.my_class, NULL, my_dev.dev_num, NULL, "my_device")) == NULL)
    {
        pr_info("Can't create device file\n");
        goto rm_class;
    }

    cdev_init(&my_dev.my_cdev, &fops);
    if (cdev_add(&my_dev.my_cdev, my_dev.dev_num, 1) < 0)
    {
        pr_info("Can't create character device file\n");
        goto rm_device;
    }
    my_dev.kmalloc_ptr = kmalloc(NPAGES * PAGE_SIZE, __GFP_FS);
    pr_info("hello\n");
    pr_info("Create successfully\n");
    return 0;
rm_device:
    device_destroy(my_dev.my_class, my_dev.dev_num);
rm_class:
    class_destroy(my_dev.my_class);
rm_dev_num:
    unregister_chrdev_region(my_dev.dev_num, 1);
    return -1;
}
static void __exit chrdev_exit(void)
{
    kfree(my_dev.kmalloc_ptr);
    cdev_del(&my_dev.my_cdev);
    device_destroy(my_dev.my_class, my_dev.dev_num);
    class_destroy(my_dev.my_class);
    unregister_chrdev_region(my_dev.dev_num, 1);
    pr_info("Goodbye, kernel\n");
}

module_init(chrdev_init);
module_exit(chrdev_exit);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERS);
