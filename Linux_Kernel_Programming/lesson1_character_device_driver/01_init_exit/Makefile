EXTRA_CFLAGS = -Wall
obj-m += init_exit.o 
KDIR = /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=${PWD} modules
#M= khong phai M =
clean:
	make -C $(KDIR) M=${PWD} clean

