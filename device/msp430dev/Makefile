all: prog0.elf

prog0.elf: main.c launchpad.c adc.c
	msp430-gcc -Os -mmcu=msp430g2553 main.c launchpad.c adc.c -o prog0.elf
	
mrproper:
	rm -rf prog0.elf
