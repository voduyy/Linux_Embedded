#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/sys.h>
#include <linux/of.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
#define DRIVER_AUTHOR "Vo Duy"
#define DRIVER_DESCRIPTION "sysfs group"
#define DRIVER_VERSION "1.0"
#define LED_ON 1
#define LED_OFF 0
#define LOW 0
#define HIGH 1
struct my_device_properties
{
    struct kobject *kobj_ref;
} my_dev;

static ssize_t direction_show(struct kobject *kobject, struct kobj_attribute *attr, char *buf);
static ssize_t direction_store(struct kobject *kobject, struct kobj_attribute *attr, const char *buf, size_t count);
static ssize_t value_show(struct kobject *kobject, struct kobj_attribute *attr, char *buf);
static ssize_t value_store(struct kobject *kobject, struct kobj_attribute *attr, const char *buf, size_t count);

struct kobj_attribute direction_attr = __ATTR(direction, 0660, direction_show, direction_store);
struct kobj_attribute value_attr = __ATTR(value, 0660, value_show, value_store);

struct gpio_desc *my_gpio;
struct device *mdev;
struct my_sys_data
{
    char direction[10];
    int value;
} m_sys_data;

static struct attribute *m_attr[] = {
    &direction_attr.attr,
    &value_attr.attr,
    NULL,
};

static struct attribute_group attr_group =
    {
        .attrs = m_attr,
};

static ssize_t direction_show(struct kobject *kobject, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%s", m_sys_data.direction);
}
static ssize_t direction_store(struct kobject *kobject, struct kobj_attribute *attr, const char *buf, size_t count)
{
    if (sysfs_streq(buf, "in"))
    {
        gpiod_direction_input(my_gpio);
    }
    else if (sysfs_streq(buf, "out"))
    {
        gpiod_direction_output(my_gpio, 0);
    }
    strcpy(m_sys_data.direction, buf);

    return count;
}
static ssize_t value_show(struct kobject *kobject, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d", m_sys_data.value);
}
static ssize_t value_store(struct kobject *kobject, struct kobj_attribute *attr, const char *buf, size_t count)
{
    sscanf(buf, "%d", &m_sys_data.value);
    switch (m_sys_data.value)
    {
    case LED_OFF:
        gpiod_set_value(my_gpio, LOW);
        break;
    case LED_ON:
        gpiod_set_value(my_gpio, HIGH);
        break;
    default:
        return count;
    }
    pr_info("State of LED %s\n",gpiod_get_value(my_gpio)?"HIGH": "LOW");
    return count;
}

static const struct of_device_id gpio_id[] = {
    {.compatible = "gpio_based_subsystem"},
    {},
};
MODULE_DEVICE_TABLE(of, gpio_id);

static int m_gpio_probe(struct platform_device *pdev)
{
    pr_info("Hello this is my gpio\n");
    my_dev.kobj_ref = kobject_create_and_add("my_gpio_sysfs", NULL);
    if (sysfs_create_group(my_dev.kobj_ref, &attr_group))
    {
        pr_info("Can't create\n");
        goto rm_kobject;
    }
    mdev = &pdev->dev;
    my_gpio = gpiod_get(mdev, "led44", GPIOD_OUT_LOW);
    if (IS_ERR(my_gpio))
    {
        pr_info("Cannot request GPIO\n");
        goto rm_sysfs;
    }

    pr_info("Initialize successfully\n");
    return 0;
rm_sysfs:
    sysfs_remove_group(my_dev.kobj_ref, &attr_group);
rm_kobject:
    kobject_put(my_dev.kobj_ref);
    return -1;
}
static int m_gpio_remove(struct platform_device *pdev)
{
    gpiod_put(my_gpio);
    kobject_put(my_dev.kobj_ref);
    sysfs_remove_group(my_dev.kobj_ref, &attr_group);
    pr_info("Goodbye \n");
    return 0;
}
struct platform_driver m_gpio_driver = {
    .probe = m_gpio_probe,
    .remove = m_gpio_remove,
    .driver = {
        .name = "gpio driver",
        .owner = THIS_MODULE,
        .of_match_table = gpio_id,
    },
};
module_platform_driver(m_gpio_driver);
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESCRIPTION);
MODULE_VERSION(DRIVER_VERSION);