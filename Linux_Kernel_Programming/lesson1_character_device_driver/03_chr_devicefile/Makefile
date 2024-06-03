EXTRA_CFLAGS = -Wall

obj-m += chr_devicefile.o 
KDIR = /lib/modules/`uname -r`/build
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean