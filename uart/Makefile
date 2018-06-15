.PHONY: all clean flash

TARGET = test

CC = sdcc
MCU = STM8S003
PART = stm8s003f3

BUILD_DIR = ./build
INC_DIR = ./include

LIBS = 

# Make sure main file is the first in list
OBJS = $(TARGET).rel $(LIBS)

CFLAGS = -DSDCC -D$(MCU) -mstm8 --out-fmt-ihx --std-c99
CFLAGS += -DDEBUG
LDFLAGS = -mstm8 -lstm8

all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET).ihx

$(BUILD_DIR):
		mkdir $(BUILD_DIR)

# Link main with libs
$(BUILD_DIR)/$(TARGET).ihx: $(BUILD_DIR)/$(OBJS)
		@echo "==========================="
		@echo ">> Linking $< << "
		$(CC) $(LDFLAGS) -I$(INC_DIR) $< -o $@

# Compile main
$(BUILD_DIR)/$(TARGET).rel: $(TARGET).c
		@echo ">> Compiling $< <<"
		$(CC) -I$(INC_DIR) -c $(CFLAGS) $< -o $@

# Compile all other libs except main
$(BUILD_DIR)/$(LIBS).rel: $(LIBS).c
		@echo ">> Compiling $< <<"
		$(CC) -I$(INC_DIR) -c $(CFLAGS) $< -o $@

clean:
		@rm -f $(BUILD_DIR)/*.asm
		@rm -f $(BUILD_DIR)/*.rst
		@rm -f $(BUILD_DIR)/*.ihx
		@rm -f $(BUILD_DIR)/*.rel
		@rm -f $(BUILD_DIR)/*.sym
		@rm -f $(BUILD_DIR)/*.lst
		@rm -f $(BUILD_DIR)/*.map
		@rm -f $(BUILD_DIR)/*.cdb
		@rm -f $(BUILD_DIR)/*.lk
		@rm -f $(BUILD_DIR)/*.mem
		@echo "Cleaning done."
	
flash:
		stm8flash -c stlinkv2 -p $(PART) -w $(BUILD_DIR)/$(NAME).ihx
