
TARGET = prog0
OUTPUT = $(TARGET).elf

DEVICE = msp430g2553
MCU =-lfp -mmcu=$(DEVICE)

COMPILER = msp430
CC = $(COMPILER)-gcc
AR = $(COMPILER)-ar
LD = $(COMPILER)-ld -v 
AS = $(COMPILER)-as
CP = $(COMPILER)-objcopy
OD = $(COMPILER)-objdump
STRIP = $(COMPILER)-strip


CC_FLAGS = -fno-common -Os $(MCU) $(INCDIR)
AR_FLAGS = rcs
LD_FLAGS = $(LIBDIR) -lc -lfp -lm $(MMCU) $(INCDIR) -Os
CP_FLAGS = -O ihex
OD_FLAGS = -x --syms

INCDIR=-I.
LIBDIR=-L. 
CFLAGS= -Os -mmcu=$(MCU) $(INCDIR) $(LIBDIR)
OBJDIR =.

SRC = launchpad.c main.c adc.c

OBJ = ${SRC:.c=.o}
DEP=$(wildcard *.h)
#msp430-gcc -Os -mmcu=msp430g2553 main.c launchpad.c -o prog0.elf

all: $(TARGET).hex

.c.o:
	$(CC) -c -o $@ $< $(CFLAGS) 

$(TARGET).hex: $(OUTPUT)
	@echo "Converting to hex:" $(OBJS)
	$(CP) $(CP_FLAGS) $(OUTPUT) ./$@
	$(OD) $(OD_FLAGS) $(OBJ) > _$(TARGET).dmp
	$(CC) -fno-common -Os -g $(LD_FLAGS) $(INCDIR) $(SRC) -o $(TARGET).elf -Wl,-Map=_$(TARGET).map $(MCU)
	$(OD) -S -g $(OUTPUT) > _$(TARGET).list
	@echo "Done."
	cp $(OUTPUT) $(TARGET).debug.elf
	@size $(TARGET).debug.elf -Adt
	$(STRIP) $(OUTPUT)
	@size $(OUTPUT) -Adt

$(OUTPUT): $(OBJ)
	@echo "Linking..."
#	$(LD) $(LD_FLAGS) -o $@ $(OBJ)-$(DEVICE) $(INCLUDES) -Os -O3
	$(CC) $(LD_FLAGS) -o $@ $(OBJ) $(MCU)
	@echo "Done."


clean:
	rm -f $(OBJDIR)/*.o
