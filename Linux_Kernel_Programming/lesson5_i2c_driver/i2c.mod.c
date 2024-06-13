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
	{ 0xd0bf0a9a, "i2c_del_driver" },
	{ 0xe335b1c5, "i2c_register_driver" },
	{ 0xf9a482f9, "msleep" },
	{ 0x4e7af083, "kmem_cache_alloc_trace" },
	{ 0x2beac39b, "kmalloc_caches" },
	{ 0xc5850110, "printk" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0xff43d9d3, "i2c_transfer_buffer_flags" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Ci2c_driver_oled");
MODULE_ALIAS("of:N*T*Ci2c_driver_oledC*");

MODULE_INFO(srcversion, "DAE77F67CF955BB9738AB70");
