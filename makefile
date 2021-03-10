#
# Copyright (c) 2021, Renesas Electronics Corporation. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

TARGET_NAME	:= sec_module

# directory definition
TOPDIR		:= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
SRCDIR		:= $(TOPDIR)
OUTDIR		:= $(SRCDIR)out/
OBJDIR		:= $(SRCDIR)obj/

#output file name
BIN_FILE	:= $(OUTDIR)$(TARGET_NAME).bin
MOT_FILE	:= $(OUTDIR)$(TARGET_NAME).srec
ELF_FILE	:= $(OUTDIR)$(TARGET_NAME).elf
MAP_FILE	:= $(OUTDIR)$(TARGET_NAME).map

#source file name
SOURCES		=	./sec_module.c \
				./tsip/wrapper/TSIP_Wrapper_Local_API.c \
				./tsip/wrapper/TSIP_Wrapper_Init_API.c \
				./tsip/wrapper/TSIP_Wrapper_Boot_API.c \
				./tsip/wrapper/TSIP_Wrapper_Prepare_API.c \
				./tsip/wrapper/TSIP_Wrapper_KeyRingVerify_API.c \
				./tsip/core/TSIP_Core_Boot_API.c \
				./tsip/core/TSIP_Core_KeyRingVerify_API.c \
				./tsip/core/TSIP_Core_Proc_API.c \
				./tsip/core/TSIP_Core_Prepare_API.c \
				./tsip/core/TSIP_Core_Local_API.c \
				./tsip/core/TSIP_Core_Init_API.c \
				./tsip/stub/TSIP_Stub_API_nonos.c \
				./tsip/stub/TSIP_Driver_nonos.c

#object file name
OBJECTS		:= $(SOURCES:%.c=${OBJDIR}%.o)

#linker file name
LINKER_FILE	:= $(SRCDIR)sec_module.ld.S
SCRIPT_FILE := $(OBJDIR)sec_module.ld
DEP_FILE	:= $(SCRIPT_FILE:.ld=.d)

# compile option
CPU			?=	-march=armv8-a
CFLAGS		+=	-mgeneral-regs-only -mstrict-align -ffunction-sections -fdata-sections \
				-ffreestanding -fno-builtin -fno-common -g -O2 -std=gnu99 -fno-stack-protector
CPPFLAGS	+=	-mgeneral-regs-only -mstrict-align
INCDIR		+=	-I$(SRCDIR) -I$(SRCDIR)tsip

# Linker option

LDFLAGS	= -nostdlib -L$(SEC_LIB_DIR)

ifeq ($(LSI),G2E)
	LDFLAGS	+= -lr_secure_ip_lib_g2e
endif
ifeq ($(LSI),G2M)
	LDFLAGS	+= -lr_secure_ip_lib_g2m
endif
ifeq ($(LSI),G2N)
	LDFLAGS	+= -lr_secure_ip_lib_g2n
endif
ifeq ($(LSI),G2H)
	LDFLAGS	+= -lr_secure_ip_lib_g2h
endif

################################################################################
# Toolchain

CROSS_COMPILE ?= aarch64-poky-linux-

CC		:= $(CROSS_COMPILE)gcc
CPP		:= $(CROSS_COMPILE)cpp
LD		:= $(CROSS_COMPILE)ld
OC		:= $(CROSS_COMPILE)objcopy

###################################################
# Definition of suffix rule applies to extension
.SUFFIXES: .c .o

###################################################
# Compile

.PHONY: all
all: $(MOT_FILE)
	$(OC) -I srec -O binary --srec-forceS3 $(MOT_FILE) $(BIN_FILE)

$(MOT_FILE):$(ELF_FILE)
	$(OC) -O srec --srec-forceS3 $(ELF_FILE) $(MOT_FILE)
	
$(ELF_FILE):$(SCRIPT_FILE) $(OBJECTS)
	if [ ! -d $(@D) ]; then mkdir -p $(@D); fi
	$(LD) -o $(ELF_FILE) $(OBJECTS) $(LDFLAGS) --script $(SCRIPT_FILE) -Map $(MAP_FILE)

$(SCRIPT_FILE):$(LINKER_FILE)
	if [ ! -d $(@D) ]; then mkdir -p $(@D); fi
	$(CPP) $(CPU) $(CPPFLAGS) $(INCDIR) -P -x assembler-with-cpp -D__LINKER__ -Wp,-MD,$(DEP_FILE) -MT $@ -MP -o $@ $<

$(OBJDIR)%.o:$(SRCDIR)%.c
	if [ ! -d $(@D) ]; then mkdir -p $(@D); fi
	$(CC) $(CPU) $(CFLAGS) $(INCDIR)  -D_TSIP_SB -D_TSIP_NONOS -c $< -o $@

###################################################
# Clean
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(OUTDIR)
