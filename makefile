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
	# Set flag to compile submodules with mock_flag
ifeq ($(MAKECMDGOALS),mock)
	cd $(basename $@) && make MOCK_FLAG=-DMOCK_DATA && cp $@ ../$(BUILD_DIR)/
else
	cd $(basename $@) && make && cp $@ ../$(BUILD_DIR)/
endif

debug: $(MODULES)
	$(CC) -o $(BUILD) $(MAIN) $(patsubst %, $(BUILD_DIR)/%, $(MODULES)) $(OVRLIB) -I$(BUILD_DIR) $(INCDIR) $(MODULES_INC) $(CFLAGS) $(CFLAGSDEBUG)

mock: compile
	

clean:	
	rm -f $(BUILD_DIR)/*
	rm -f $(patsubst %, $(BUILD_DIR)/%, $(MODULES))
	rm -f $(patsubst %.a, %/*.a, $(MODULES))
	rm -f $(patsubst %.a, %/obj/*.o, $(MODULES))

.PHONY: doc
doc:
	doxygen Doxyfile.conf -u
