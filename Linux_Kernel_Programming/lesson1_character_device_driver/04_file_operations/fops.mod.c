#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
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
__used __section("__versions") = {
	{ 0xdc658e53, "module_layout" },
	{ 0x954ad0e5, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x6f021618, "class_destroy" },
	{ 0xbfeffc40, "device_destroy" },
	{ 0xfbb5c7d2, "cdev_add" },
	{ 0xf4837e68, "cdev_init" },
	{ 0xef4c61eb, "device_create" },
	{ 0xe05148c6, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x39cc82d7, "module_refcount" },
	{ 0x6b88d85e, "try_module_get" },
	{ 0x14e27de, "module_put" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x92997ed8, "_printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "C41E2652818A69543696BDB");
