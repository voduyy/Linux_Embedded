#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/device.h>

static int lcd_send_command(struct i2c_client *client, uint8_t command)
{
    uint8_t buf[2] = {0x00, command}; // Control byte + command
    int ret = i2c_master_send(client, buf, 2);
    msleep(5); // Allow command to process
    return ret;
}

static int lcd_send_data(struct i2c_client *client, uint8_t data)
{
    uint8_t buf[2] = {0x40, data}; // Control byte + data
    int ret = i2c_master_send(client, buf, 2);
    msleep(5); // Allow data to process
    return ret;
}

static int lcd_init(struct i2c_client *client)
{
    lcd_send_command(client, 0x38); // Function set
    lcd_send_command(client, 0x0C); // Display on
    lcd_send_command(client, 0x01); // Clear display
    lcd_send_command(client, 0x06);
    msleep(2);
    return 0;
}

static int lcd_display_string(struct i2c_client *client, const char *str)
{
    while (*str)
    {
        lcd_send_data(client, *str++);
    }
    return 0;
}

static int lcd16x2_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    lcd_init(client);
    lcd_display_string(client, "hello");
    struct device_node *np = client->dev.of_node;
    uint32_t reg;

    if (!np)
    {
        dev_err(&client->dev, "Device tree node not found\n");
        return -ENODEV;
    }

    if (of_property_read_u32(np, "reg", &reg))
    {
        dev_err(&client->dev, "Failed to read reg property\n");
        return -EINVAL;
    }

    dev_info(&client->dev, "reg property of lcd16x2 node: 0x%x\n", reg);

    pr_info("LCD driver probed\n");
    return 0;
}

static int lcd16x2_i2c_remove(struct i2c_client *client)
{
    lcd_send_command(client, 0x01); // Clear display
    pr_info("LCD driver removed\n");
    return 0;
}

static const struct i2c_device_id lcd16x2_i2c_match_id[] = {
    {"lcd16x2", 0},
    {}};

MODULE_DEVICE_TABLE(i2c, lcd16x2_i2c_match_id);

static struct i2c_driver lcd16x2_i2c_driver = {
    .driver = {
        .name = "lcd16x2",
        .owner = THIS_MODULE,
    },
    .probe = lcd16x2_i2c_probe,
    .remove = lcd16x2_i2c_remove,
    .id_table = lcd16x2_i2c_match_id,
};

module_i2c_driver(lcd16x2_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("voduy");
MODULE_DESCRIPTION("lcd16x2");