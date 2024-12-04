# SPDX-License-Identifier: MIT
# Copyright (c) 2024 Lars Görner

### Toolchain
TC_PREFIX := arm-none-eabi
CC := $(TC_PREFIX)-gcc.exe
AS := $(TC_PREFIX)-as.exe
LD := $(TC_PREFIX)-ld.exe
OBJ_DUMP := $(TC_PREFIX)-objdump.exe
OBJ_CPY := $(TC_PREFIX)-objcopy.exe

FW_FILE := build/fw.elf
FW_FILE_DUMP := $(subst .elf,.list,$(FW_FILE))

LD_SCRIPT := boot/memory.ld
LD_MAP_FILE := $(subst .elf,.map,$(FW_FILE))

CFLAGS += -mcpu=cortex-m0
CFLAGS += -O2
CFLAGS += -std=c11 -ffreestanding
CFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wl,--nostdlib,--gc-sections,-Map,$(LD_MAP_FILE),-T,$(LD_SCRIPT),--print-memory-usage

SRC += boot/boot.c
SRC += app/main.c app/hw_init.c app/display.c app/input.c
SRC += app/input.c app/edit_init_date.c
SRC += app/assets/graphics/background.c 
SRC += app/assets/fonts/font_32px.c app/assets/fonts/font_2_32px.c

.PHONY: all clean ocd

all: $(SRC)
	$(CC) $(CFLAGS) -o $(FW_FILE) $^
	$(OBJ_DUMP) --disassemble --header --full-contents $(FW_FILE) > $(FW_FILE_DUMP)

clean:
	rm build/*

ocd:
	openocd -f interface/stlink.cfg -f target/stm32f0x.cfg
