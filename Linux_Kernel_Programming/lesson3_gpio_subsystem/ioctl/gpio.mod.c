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
	{ 0x8e061c72, "platform_driver_unregister" },
	{ 0x42899e9a, "__platform_driver_register" },
	{ 0x6e5731c0, "gpiod_get_value" },
	{ 0x1a83fde1, "gpiod_set_value" },
	{ 0x2dd9a1a0, "module_refcount" },
	{ 0xc9f01501, "try_module_get" },
	{ 0x489a34cb, "gpiod_get" },
	{ 0xb9c8e072, "device_create" },
	{ 0x6e281da3, "__class_create" },
	{ 0x9da20cef, "cdev_add" },
	{ 0x9c4b2604, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x7d7ba167, "module_put" },
	{ 0xc5850110, "printk" },
	{ 0x82c94c14, "gpiod_put" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x4d43d4d2, "cdev_del" },
	{ 0x71a5f1ed, "class_destroy" },
	{ 0xd26b5ad8, "device_destroy" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cgpio_based_subsystem");
MODULE_ALIAS("of:N*T*Cgpio_based_subsystemC*");

MODULE_INFO(srcversion, "6F718070B3F1A38BFFB06DD");
