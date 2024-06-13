#include "i2c.h"

static int ssd1306_i2c_write(struct ssd1306_i2c_module *module, unsigned char *buf, unsigned int len)
{
    return i2c_master_send(module->client, buf, len);
}
static int ssd1306_i2c_read(struct ssd1306_i2c_module *module, unsigned char *out_buf, unsigned int len)
{
    return i2c_master_recv(module->client, out_buf, len);
}
static void ssd1306_write(struct ssd1306_i2c_module *module, bool is_cmd, unsigned char data)
{
    unsigned char buf[2];
    if (is_cmd == WRITE_DATA)
    {
        buf[0] = 0x40;
    }
    else
    {
        buf[0] = 0x00;
    }
    buf[1] = data;
    ssd1306_i2c_write(module, buf, 2); // write address and data
}
static void ssd1306_set_cursor(struct ssd1306_i2c_module *module, uint8_t line, uint8_t cursor_position)
{
    /*
        Set cursor must has the start and end line,
        Also have start and end of cursor position    */
    if (line <= SSD1306_MAX_LINE && cursor_position < SSD1306_MAX_SEG)
    {
        module->line_num = line;
        module->cursor_position = cursor_position;
        ssd1306_write(module, WRITE_COMMAND, 0x21);
        ssd1306_write(module, WRITE_COMMAND, cursor_position);
        ssd1306_write(module, WRITE_COMMAND, SSD1306_MAX_SEG - 1);
        ssd1306_write(module, WRITE_COMMAND, 0x22);
        ssd1306_write(module, WRITE_COMMAND, line);
        ssd1306_write(module, WRITE_COMMAND, SSD1306_MAX_LINE);
    }
}
static void ssd1306_goto_next_line(struct ssd1306_i2c_module *module)
{
    module->line_num++;
    module->line_num = (module->line_num & SSD1306_MAX_LINE);
    ssd1306_set_cursor(module, module->line_num, 0); // reset at new line
}
static void ssd1306_print_char(struct ssd1306_i2c_module *module, unsigned char data)
{
    uint8_t temp =0 ;
    uint8_t data_byte=0;
    if ((SSD1306_MAX_SEG < module->cursor_position + module->font_size) || (data == '\n'))
    {
        ssd1306_goto_next_line(module);
    }
    if (data != '\n')
    {
        data -= 0x20; // tru thi moi ra duoc gia tri cua OLED
        do
        {
            data_byte = ssd1306_font[data][temp++];
            ssd1306_write(module, WRITE_DATA, data_byte);
            module->cursor_position++;
        } while (temp < SSD1306_DEF_FONT_SIZE);
    }

    ssd1306_write(module, WRITE_DATA, 0);
    module->cursor_position++;
}
static void ssd1306_print_string(struct ssd1306_i2c_module *module, unsigned char *data)
{
    while (*data)
    {
        ssd1306_print_char(module, (*data)++);
    }
}
static void ssd1306_set_brightness(struct ssd1306_i2c_module *module, int brightness)
{
    if (brightness < MIN_BRIGHTNESS)
    {
        brightness = MIN_BRIGHTNESS;
    }
    else if (brightness > MAX_BRIGHTNESS)
    {
        brightness = MAX_BRIGHTNESS;
    }
    ssd1306_write(module, WRITE_COMMAND, 0x81);
    ssd1306_write(module, WRITE_COMMAND, brightness);
}
static void ssd1306_clear_screen(struct ssd1306_i2c_module *module)
{
    int i;
    int total_size = SSD1306_MAX_SEG * (SSD1306_MAX_LINE + 1);
    for (i = 0; i < total_size; i++)
    {
        ssd1306_write(module, WRITE_DATA, 0);
    }
}
static void ssd1306_turn_off(struct ssd1306_i2c_module *module)
{
    ssd1306_clear_screen(module);
    ssd1306_write(module, WRITE_COMMAND, 0xAE);
}
static int ssd1306_display_init(struct ssd1306_i2c_module *module)
{
    msleep(100);
    ssd1306_write(module, WRITE_COMMAND, 0xAE); // Entire Display OFF
    ssd1306_write(module, WRITE_COMMAND, 0xD5); // Set Display Clock Divide Ratio and Oscillator Frequency
    ssd1306_write(module, WRITE_COMMAND, 0x80); // Default Setting for Display Clock Divide Ratio and Oscillator Frequency that is recommended
    ssd1306_write(module, WRITE_COMMAND, 0xA8); // Set Multiplex Ratio
    ssd1306_write(module, WRITE_COMMAND, 0x3F); // 64 COM lines
    ssd1306_write(module, WRITE_COMMAND, 0xD3); // Set display offset
    ssd1306_write(module, WRITE_COMMAND, 0x00); // 0 offset
    ssd1306_write(module, WRITE_COMMAND, 0x40); // Set first line as the start line of the display
    ssd1306_write(module, WRITE_COMMAND, 0x8D); // Charge pump
    ssd1306_write(module, WRITE_COMMAND, 0x14); // Enable charge dump during display on
    ssd1306_write(module, WRITE_COMMAND, 0x20); // Set memory addressing mode
    ssd1306_write(module, WRITE_COMMAND, 0x00); // Horizontal addressing mode
    ssd1306_write(module, WRITE_COMMAND, 0xA1); // Set segment remap with column address 127 mapped to segment 0
    ssd1306_write(module, WRITE_COMMAND, 0xC8); // Set com output scan direction, scan from com63 to com 0
    ssd1306_write(module, WRITE_COMMAND, 0xDA); // Set com pins hardware configuration
    ssd1306_write(module, WRITE_COMMAND, 0x12); // Alternative com pin configuration, disable com left/right remap
    ssd1306_write(module, WRITE_COMMAND, 0x81); // Set contrast control
    ssd1306_write(module, WRITE_COMMAND, 0x80); // Set Contrast to 128
    ssd1306_write(module, WRITE_COMMAND, 0xD9); // Set pre-charge period
    ssd1306_write(module, WRITE_COMMAND, 0xF1); // Phase 1 period of 15 DCLK, Phase 2 period of 1 DCLK
    ssd1306_write(module, WRITE_COMMAND, 0xDB); // Set Vcomh deselect level
    ssd1306_write(module, WRITE_COMMAND, 0x20); // Vcomh deselect level ~ 0.77 Vcc
    ssd1306_write(module, WRITE_COMMAND, 0xA4); // Entire display ON, resume to RAM content display
    ssd1306_write(module, WRITE_COMMAND, 0xA6); // Set Display in Normal Mode, 1 = ON, 0 = OFF
    ssd1306_write(module, WRITE_COMMAND, 0x2E); // Deactivate scroll
    ssd1306_write(module, WRITE_COMMAND, 0xAF); // Display ON in normal mode
    ssd1306_clear_screen(module);

    return 0;
}
static const struct of_device_id i2c_of_id[] =
    {
        {.compatible = "i2c_driver_oled"},
        {}};
static int i2c_probe_new(struct i2c_client *client)
{
    pr_info("Hello, this is driver of OLED SSD1306 \n");
    pr_info("Address is %X\n", client->addr);

    module = kmalloc(sizeof(module), GFP_KERNEL);
    if (!module)
    {
        pr_info("Can't allocate memory \n");
        return -ENOMEM;
    }
    module->client = client;
    module->cursor_position = 0;
    module->font_size = SSD1306_DEF_FONT_SIZE;
    module->line_num = 0;

    i2c_set_clientdata(client, module);
    ssd1306_display_init(module);
    ssd1306_set_cursor(module, 0, 0);
    ssd1306_print_string(module, "Hello\n world\n");
    return 0;
}
static int i2c_remove(struct i2c_client *client)
{
    module = i2c_get_clientdata(client);
    ssd1306_print_string(module, "End!!!");
    msleep(1000);

    module->line_num = 0;
    module->cursor_position = 0;
    ssd1306_turn_off(module);

    kfree(module);
    pr_info("goodbye i2c \n");
    return 0;
}
MODULE_DEVICE_TABLE(of, i2c_of_id);
static struct i2c_driver my_i2c_driver =
    {
        .probe_new = i2c_probe_new,
        .remove = i2c_remove,
        .driver = {
            .name = "my_i2c",
            .of_match_table = i2c_of_id,
            .owner = THIS_MODULE},
};

module_i2c_driver(my_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERS);