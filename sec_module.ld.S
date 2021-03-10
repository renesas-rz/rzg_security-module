/*
 * Copyright (c) 2019, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "sec_module.h"

OUTPUT_FORMAT(elf64-littleaarch64)
OUTPUT_ARCH(aarch64)
ENTRY(sec_module)

MEMORY {
    RAM (rwx): ORIGIN = SEC_MODULE_BASE, LENGTH = SEC_MODULE_LIMIT - SEC_MODULE_BASE
}


SECTIONS
{
    . = SEC_MODULE_BASE;
    ASSERT(. == ALIGN(SEC_MODULE_PAGE_SIZE),
           "SECMOD_BASE address is not aligned on a page boundary.")
    arg . : {
        KEEP(* (SHARED_AREA))
       . = SEC_MODULE_SHARED_SIZE;
    } >RAM
    . = SEC_MODULE_ENTRY;
    ro . : {
        *(.text.sec_module)
        *(.text*)
        *(.rodata*)
        . = ALIGN(SEC_MODULE_PAGE_SIZE);
        __RO_END__ = .;
    } >RAM
    __RW_START__ = . ;
    .data . : {
        __DATA_START__ = .;
        *(.data*)
        __DATA_END__ = .;
    } >RAM
    .bss : ALIGN(16) {
        __BSS_START__ = .;
        *(.bss*)
        *(COMMON)
        __BSS_END__ = .;
    } >RAM
    __RW_END__ = .;
    __SECMOD_END__ = .;
    __BSS_SIZE__ = SIZEOF(.bss);
    ASSERT(. <= SEC_MODULE_LIMIT, "Security Module has exceeded its limit.")
}
