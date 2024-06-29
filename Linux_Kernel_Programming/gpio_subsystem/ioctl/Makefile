# TOOLCHAIN
BBB_KERNEL := /home/voduy/Workspace/beagleboneblack_version2/kernelbuildscripts/KERNEL
TOOLCHAIN := /home/voduy/Workspace/beagleboneblack_version2/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-

# Compiler flags
EXTRA_CFLAGS = -Wall

# Kernel modules to build
obj-m += gpio.o 

# Build targets
all: build_gpio build_userspace_app
	
build_gpio:
	make ARCH=arm CROSS_COMPILE=$(TOOLCHAIN) -C $(BBB_KERNEL) M=$(shell pwd) modules
build_userspace_app:
	$(TOOLCHAIN)gcc -o app userspace_app.c -I$(TOOLCHAIN)/../../include
clean:
	make -C $(BBB_KERNEL) M=$(shell pwd) clean
