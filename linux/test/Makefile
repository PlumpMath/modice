include ../Makefile.vars

ARM := ARCH=arm CROSS_COMPILE=$(CMPL)
TARGET := ../trg

LIBNAME := ../gpio
SNDLIBNAME := sound

define copy
scp $(TARGET)/$1 root@$(CLIENT):~/
ssh root@$(CLIENT)
endef

define test
$(CMPL)gcc -o $(TARGET)/$1 $1.c $(LIBNAME).c -lasound -I $(KDIR)/include -I ..
$(call copy,$1)
endef

default: gpio

gpio:
	$(call test,gpio_test)

i2s:
	$(call test,i2s_test)

clean: clean_gpio clean_i2s

clean_gpio:
	rm $(TARGET)/gpio_test
clean_i2s:
	rm $(TARGET)/i2s_test