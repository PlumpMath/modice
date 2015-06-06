KDIR := ~/sl2c100_kernel_2.6.29_20100622
CMPL := arm-s5pc1xx-linux-gnueabi-
ARM := ARCH=arm CROSS_COMPILE=$(CMPL)
PWD := $(shell pwd)

TESTNAME := test
NAME := modice
DEVNAME := $(NAME)_dev
LIBNAME := $(NAME)_lib
APPNAME := $(NAME)_app
obj-m := $(NAME).o
ccflags-y := -D NAME=$(NAME) -O -D DEBUG#TODO:comment DEBUG on demand

default:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) modules
	mv $(NAME).ko trg/
	scp trg/$(NAME).ko root@192.168.25.18:~/
	ssh root@192.168.25.18

app:
	$(CMPL)gcc -o trg/$(APPNAME) $(APPNAME).c $(LIBNAME).c -D NAME=$(NAME)

test:
	$(CMPL)gcc -o trg/$(TESTNAME) $(TESTNAME).c -I $(KDIR)/include

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) clean
	rm trg/$(NAME).ko

copy:
	#sshpass -p pi scp trg/* root@203.252.182.222:~/
	#scp trg/* pi@192.168.25.40:~/ESS/assignment1/trg/
	scp trg/$(NAME).ko root@192.168.25.18:~/