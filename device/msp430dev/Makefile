all: prog0.elf

prog0.elf: main.c launchpad.c
	msp430-gcc -Os -mmcu=msp430g2553 main.c launchpad.c -o prog0.elf
