# Program's name
PROJ=bikex

# Where's my src and build folder
# xml hash eval file_handler
MODULES				= bikex.a device.a ovr.a unity.a
BUILD_DIR			= build

# OVR library
OVRLIB=ovr/sdk/lib/linux/Release/x86_64/libovr.a

# Include module headers
MODULES_INC			= $(patsubst %.a, -I%, $(MODULES))

#Include ovr sdk
INCDIR = -Iovr/sdk/src

# Build file
BUILD = $(BUILD_DIR)/$(PROJ)

# Main file
MAIN=main.cpp

# Compiler
CC=g++
CFLAGS=-lGL -ludev -lXrandr -lX11 -lpthread  
CFLAGSDEBUG=-g

# Targets $(call FILTER_OUT,lex, $(FILES))
compile: $(MODULES)
	$(CC) -o $(BUILD) $(MAIN) $(patsubst %, $(BUILD_DIR)/%, $(MODULES)) $(OVRLIB) -I$(BUILD_DIR) $(INCDIR) $(MODULES_INC) $(CFLAGS)

$(MODULES):
	cd $(basename $@) && make && cp $@ ../$(BUILD_DIR)/

debug:$(MODULES)
	$(CC) -o $(BUILD) $(MAIN) $(patsubst %, $(BUILD_DIR)/%, $(MODULES)) $(OVRLIB) -I$(BUILD_DIR) $(INCDIR) $(MODULES_INC) $(CFLAGS) $(CFLAGSDEBUG)


clean:	
	rm -f $(BUILD_DIR)/*
	rm -f $(patsubst %, $(BUILD_DIR)/%, $(MODULES))
	rm -f $(patsubst %.a, %/*.a, $(MODULES))

doc:
	doxygen Doxyfile.conf -u
