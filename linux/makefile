include Makefile.vars

PWD := $(shell pwd)
ARM := ARCH=arm CROSS_COMPILE=$(CMPL)

NAME := modice
DEVNAME := $(NAME)_dev
LIBNAME := gpio
SNDLIBNAME := sound
APPNAME := $(NAME)
obj-m := $(NAME).o
ccflags-y := -D NAME=$(NAME) -O

TARGET := trg

default:app copy_app

driver:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) modules
	mv $(NAME).ko trg/

app:
	$(CMPL)gcc -o trg/$(APPNAME) $(APPNAME).c $(LIBNAME).c -lasound

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) clean
	rm trg/$(NAME).ko

copy_driver:
	$(call copy,$(NAME).ko)
copy_app:
	$(call copy,$(APPNAME))