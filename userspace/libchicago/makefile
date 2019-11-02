# File author is Ítalo Lima Marconato Matias
#
# Created on October 29 of 2019, at 18:21 BRT
# Last edited on November 02 of 2019, at 13:54 BRT

ARCH ?= x86
VERBOSE ?= false
DEBUG ?= false

SYSROOT_DIR ?=
LIB_DIR ?= System/Libraries
INC_DIR ?= Development/Headers

ifeq ($(ARCH),x86)
	SUBARCH ?= 32
	
	ifeq ($(SUBARCH),32)
		FULL_ARCH := $(ARCH)
		TARGET ?= i686-chicago
		ARCH_CFLAGS += -msse2
	else ifeq ($(SUBARCH),64)
		FULL_ARCH := $(ARCH)-$(SUBARCH)
		TARGET ?= x86_64-chicago
		ARCH_CFLAGS += -DARCH_64 -mno-mmx
	else
		UNSUPPORTED_ARCH := true
	endif
	
	ARCH_OBJECTS := io/file.c.o
	ARCH_OBJECTS += mm/alloc.c.o mm/virt.c.o
	ARCH_OBJECTS += sys/process.c.o sys/version.c.o
else
	UNSUPPORTED_ARCH := true
endif

OBJECTS := sys/string.c.o

ARCH_OBJECTS := $(addprefix build/$(FULL_ARCH)/arch/$(ARCH)/,$(ARCH_OBJECTS))
OBJECTS := $(addprefix build/$(FULL_ARCH)/,$(OBJECTS))
OUTPUT := build/libchicago-$(FULL_ARCH).so

ifneq ($(VERBOSE),true)
NOECHO := @
endif

PATH := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/../../toolchain/$(ARCH)-$(SUBARCH)/bin:$(PATH)
SHELL := env PATH=$(PATH) /bin/bash

all: $(OUTPUT)

clean:
ifeq ($(UNSUPPORTED_ARCH),true)
	$(error Unsupported architecture $(ARCH), subarch $(SUBARCH))
endif
	$(NOECHO)rm -f $(ARCH_OBJECTS) $(OBJECTS) $(OUTPUT)

clean-all:
ifeq ($(UNSUPPORTED_ARCH),true)
	$(error Unsupported architecture $(ARCH), subarch $(SUBARCH))
endif
	$(NOECHO)rm -rf build

remake: clean all
ifeq ($(UNSUPPORTED_ARCH),true)
	$(error Unsupported architecture $(ARCH), subarch $(SUBARCH))
endif

install: all
ifeq ($(UNSUPPORTED_ARCH),true)
	$(error Unsupported architecture $(ARCH), subarch $(SUBARCH))
endif
	$(NOECHO)echo Installing headers
	$(NOECHO)cp -RT include $(SYSROOT_DIR)/$(INC_DIR)
	$(NOECHO)echo Installing libchicago.so
	$(NOECHO)cp $(OUTPUT) $(SYSROOT_DIR)/$(LIB_DIR)/libchicago.so

$(OUTPUT): $(ARCH_OBJECTS) $(OBJECTS)
ifeq ($(UNSUPPORTED_ARCH),true)
	$(error Unsupported architecture $(ARCH), subarch $(SUBARCH))
endif
	$(NOECHO)echo Linking $@
	$(NOECHO)if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(NOECHO)
	$(NOECHO)$(TARGET)-gcc -shared -nostdlib -fno-plt -o $@ $(ARCH_OBJECTS) $(OBJECTS) $(ARCH_LDFLAGS)

build/$(FULL_ARCH)/%.s.o: %.s
ifeq ($(UNSUPPORTED_ARCH),true)
	$(error Unsupported architecture $(ARCH), subarch $(SUBARCH))
endif
	$(NOECHO)echo Compiling $<
	$(NOECHO)if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(NOECHO)$(TARGET)-gcc $(ARCH_AFLAGS) $< -o $@

build/$(FULL_ARCH)/%.c.o: %.c
ifeq ($(UNSUPPORTED_ARCH),true)
	$(error Unsupported architecture $(ARCH), subarch $(SUBARCH))
endif
	$(NOECHO)echo Compiling $<
	$(NOECHO)if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
ifeq ($(DEBUG),yes)
	$(NOECHO)$(TARGET)-gcc -DARCH=L\"$(ARCH)\" -DDEBUG -g -std=c11 -Iinclude -Iarch/$(ARCH)/include -fno-plt -fno-builtin -fshort-wchar -O0 -Wall -Wextra -Wno-implicit-fallthrough -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast $(ARCH_CFLAGS) -c $< -o $@
else
	$(NOECHO)$(TARGET)-gcc -DARCH=L\"$(ARCH)\" -std=c11 -Iinclude -Iarch/$(ARCH)/include -fno-plt -fno-builtin -fshort-wchar -funroll-loops -fomit-frame-pointer -ffast-math -O3 -Wall -Wextra -Wno-implicit-fallthrough -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast $(ARCH_CFLAGS) -c $< -o $@
endif