EXTRA_CFLAGS = -Wall
obj-m  = timer_thread.o
K_BUILD = /lib/modules/`uname -r`/build

all:
	make -C $(K_BUILD) M=$(shell pwd) modules
clean:
	make -C $(K_BUILD) M=$(shell pwd) clean
