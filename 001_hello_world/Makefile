obj-m +=helloworld.o

KDIR:=/home/book/work/qemu/linux/build

PWD?=$(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
