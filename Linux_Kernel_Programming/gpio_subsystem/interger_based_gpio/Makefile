BBB_KERNEL := /home/voduy/Workspace/beagleboneblack_version2/kernelbuildscripts/KERNEL
TOOLCHAIN := /home/voduy//Workspace/beagleboneblack_version2/kernelbuildscripts/dl/gcc-8.5.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-

EXTRA_CFLAGS=-Wall
obj-m := gpio.o

all:
	make ARCH=arm CROSS_COMPILE=$(TOOLCHAIN) -C $(BBB_KERNEL) M=$(shell pwd) modules
	
clean:
	make -C $(BBB_KERNEL) M=$(shell pwd) clean