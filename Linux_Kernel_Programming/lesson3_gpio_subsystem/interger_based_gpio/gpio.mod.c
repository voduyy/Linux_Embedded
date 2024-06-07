#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0x6fbd61d8, "module_layout" },
	{ 0xfe990052, "gpio_free" },
	{ 0xc5850110, "printk" },
	{ 0x3a78f97f, "gpiod_get_raw_value" },
	{ 0xe2621d8c, "gpiod_set_raw_value" },
	{ 0x919e5361, "gpiod_direction_output_raw" },
	{ 0x1c2ddadb, "gpio_to_desc" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "9885EE6C0EDC249586C2F69");
