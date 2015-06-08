KDIR := ~/sl2c100_kernel_2.6.29_20100622
CMPL := arm-s5pc1xx-linux-gnueabi-
ARM := ARCH=arm CROSS_COMPILE=$(CMPL)
PWD := $(shell pwd)

TESTNAME := test
NAME := modice
DEVNAME := $(NAME)_dev
LIBNAME := gpio
APPNAME := $(NAME)
obj-m := $(NAME).o
ccflags-y := -D NAME=$(NAME) -O

default:app copy_app

driver:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) modules
	mv $(NAME).ko trg/

app:
	$(CMPL)gcc -o trg/$(APPNAME) $(APPNAME).c $(LIBNAME).c -lasound

test:
	$(CMPL)gcc -o trg/$(TESTNAME) $(TESTNAME).c -I $(KDIR)/include
	scp trg/$(TESTNAME) root@192.168.25.18:~/
	ssh root@192.168.25.18
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) clean
	rm trg/$(NAME).ko

copy_driver:
	scp trg/$(NAME).ko root@192.168.25.18:~/
	ssh root@192.168.25.18
copy_app:
	scp trg/$(APPNAME) root@192.168.25.18:~/
	ssh root@192.168.25.18
connect:
	ssh root@192.168.25.18
