#include "spi.h"
static ssize_t m_read(struct file *filp, char __user *user_buf, size_t size, loff_t *offset)
{
    pr_info("Function read() being called\n");
    return 0;
}
static ssize_t m_write(struct file *filp, const char __user *user_buf, size_t size, loff_t *offset)
{
    return size;
}
static int m_open(struct inode *inode, struct file *file)
{
    pr_info("Function open() being called\n");

    if (atomic_cmpxchg(&state_of_module, CDEV_NO_USE, CDEV_BEING_USED))
    {
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

static const struct of_device_id my_spi_of_id[] = {
    {.compatible = "nokia,lcd-spi"},
    {},
};
MODULE_DEVICE_TABLE(of, my_spi_of_id);
void nokia5110_init()
{
    // set GPIOs
    gpiod_set_value(cs, 0);
    gpiod_set_value(reset, 0);
    udelay(2);
    gpiod_set_value(reset, 1);

    // init LCD
    nokia5110_send_byte(LCD_CMD, 0x21); // LCD Extended Commands
    nokia5110_send_byte(LCD_CMD, 0xb1); // Set LCD Cop (Contrast).	//0xb1
    nokia5110_send_byte(LCD_CMD, 0x04); // Set Temp coefficent.		//0x04
    nokia5110_send_byte(LCD_CMD, 0x14); // LCD bias mode 1:48. 		//0x13
    nokia5110_send_byte(LCD_CMD, 0x0c); // LCD in normal mode. 0x0d inverse mode
    nokia5110_send_byte(LCD_CMD, 0x20);
    nokia5110_send_byte(LCD_CMD, 0x0c);

    nokia5110_clear_screen();
}
void nokia5110_clear_screen()
{
    int i;
    for (i = 0; i < LCD_WIDTH * LCD_HEIGHT / 8; i++)
        nokia5110_send_byte(LCD_DATA, 0x00);

    nokia5110_send_byte(LCD_CMD, 0x80 | 0); // set x coordinate to 0
    nokia5110_send_byte(LCD_CMD, 0x40 | 0); // set y coordinate to 0
}
void nokia5110_send_byte(bool kind_of_data, unsigned char data)
{
    if (kind_of_data == LCD_CMD)
    {
        gpiod_set_value(dc, LOW);
    }
    else if (kind_of_data == LCD_DATA)
    {
        gpiod_set_value(dc, HIGH);
    }
    spi_xfer.tx_buf = &data;
    spi_xfer.len = sizeof(data);
    spi_xfer.bits_per_word = 8;
    spi_message_init(&spi_msg);
    spi_message_add_tail(&spi_xfer, &spi_msg);
    spi_sync(nokia5110, &spi_msg);
}
void nokia5110_write_char(unsigned char data)
{
    nokia5110_send_byte(LCD_DATA, 0x00);
    int i;
    for (i = 0; i < 5; i++)
    {
        nokia5110_send_byte(LCD_DATA, ASCII[data - 0x20][i]);
    }
    nokia5110_send_byte(LCD_DATA, 0x00);
}
void nokia5110_write_string(char *data)
{
    while (*data)
    {
        nokia5110_write_char(*data++);
    }
}
static int nokia_probe(struct spi_device *spi)
{
    if (alloc_chrdev_region(&my_dev.dev_num, 0, 1, "my_device_num") < 0)
    {
        pr_info("Can't alloc device numbers \n");
        return 1;
    }
    pr_info("Alloc successfully device numbers, Major = %d, Minor = %d \n", MAJOR(my_dev.dev_num), MINOR(my_dev.dev_num));
    cdev_init(&my_dev.my_cdevice, &fops);
    if (cdev_add(&my_dev.my_cdevice, my_dev.dev_num, 1) < 0)
    {
        pr_info("Can't generate character device \n");
        goto rm_device_num;
    }
    if (IS_ERR(my_dev.my_class = class_create(THIS_MODULE, "my_new_led_class")))
    {
        pr_info("Can't create class \n");
        goto rm_cdev;
    }
    if (IS_ERR(device_create(my_dev.my_class, NULL, my_dev.dev_num, NULL, "my_device")))
    {
        pr_info("Can't create device \n");
        goto rm_class;
    }
    spi_dev = &spi->dev;
    cs = devm_gpiod_get(spi_dev, "cs", GPIOD_OUT_LOW);
    reset = devm_gpiod_get(spi_dev, "reset", GPIOD_OUT_LOW);
    dc = devm_gpiod_get(spi_dev, "dc", GPIOD_OUT_LOW);
    nokia5110 = spi;
    nokia5110_init();
    nokia5110_write_string("HELLO WORLD");
    return 0;
rm_class:
    class_destroy(my_dev.my_class);
rm_cdev:
    cdev_del(&my_dev.my_cdevice);
rm_device_num:
    unregister_chrdev_region(my_dev.dev_num, 1);
    return 1;
}
static int nokia_remove(struct spi_device *spi)
{

    nokia5110_write_string("goodbye");
    mdelay(1000);
    nokia5110_clear_screen();
    gpiod_put(dc);
    gpiod_put(reset);
    gpiod_put(cs);
    device_destroy(my_dev.my_class, my_dev.dev_num);
    class_destroy(my_dev.my_class);
    cdev_del(&my_dev.my_cdevice);
    unregister_chrdev_region(my_dev.dev_num, 1);
    return 0;
}

static struct spi_driver my_drv_nokia = {
    .driver = {
        .name = "nokia",
        .of_match_table = my_spi_of_id,
    },
    .probe = nokia_probe,
    .remove = nokia_remove,
};

module_spi_driver(my_drv_nokia);
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERS);