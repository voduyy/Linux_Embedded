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
	{ 0x8f281531, "module_layout" },
	{ 0xdb56c538, "platform_driver_unregister" },
	{ 0x7379b3fd, "__platform_driver_register" },
	{ 0x911fa199, "gpiod_get" },
	{ 0x8e37f02e, "gpiod_put" },
	{ 0xc5850110, "printk" },
	{ 0x4e8a994a, "gpiod_set_value" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "7956BB6895B9EECEBC0CE75");
