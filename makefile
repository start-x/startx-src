# Program's name
PROJ=bikex

# Where's my src and build folder
# xml hash eval file_handler
MODULES				= bikex.a breaks.a ovr.a sensors.a unity.a
BUILD_DIR			= build

# Include module headers
MODULES_INC			= $(patsubst %.a, -I%, $(MODULES))

# Build file
BUILD = $(BUILD_DIR)/$(PROJ)

# Main file
MAIN=main.cpp

# Compiler
CC=g++
CFLAGS=

# Targets $(call FILTER_OUT,lex, $(FILES))
compile: $(MODULES)
	$(CC) -o $(BUILD) $(MAIN) $(patsubst %, $(BUILD_DIR)/%, $(MODULES)) -I$(BUILD_DIR) $(MODULES_INC) $(CFLAGS)

$(MODULES):
	cd $(basename $@) && make && cp $@ ../$(BUILD_DIR)/

clean:	
	rm -f $(BUILD_DIR)/*
	rm -f $(patsubst %, $(BUILD_DIR)/%, $(MODULES))
	rm -f $(patsubst %.a, %/*.a, $(MODULES))