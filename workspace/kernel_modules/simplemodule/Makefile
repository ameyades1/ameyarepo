obj-m := simplemodule.o

all: simplemodule.c
	@echo "\n----Compiling Module----\n"
	make -C /lib/modules/`uname -r`/build M=$(PWD) modules

clean:
	@echo "\n----Clean----\n"
	make -C /lib/modules/`uname -r`/build M=$(PWD) clean

load:
	@echo "\n----Loading Module----\n"
	insmod ./simplemodule.ko

info:
	modinfo -a ./simplemodule.ko  
	modinfo -d ./simplemodule.ko
	modinfo -p ./simplemodule.ko 

modify:
	@echo "\n----Modify the parameters----\n"
	insmod ./simplemodule.ko number=1234 word="Apple"
	dmesg | tail -3

unload:
	@echo "\n----Unloading Module----\n"
	rmmod simplemodule 
	dmesg | tail -3
