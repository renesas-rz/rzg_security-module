/*
 * Copyright (c) 2020, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SEC_MODULE_H
#define SEC_MODULE_H

/******************************************************************************
Macro definitions
******************************************************************************/
#define SEC_MODULE_BASE			(0x440E0000)
#define SEC_MODULE_LIMIT		(SEC_MODULE_BASE + 0x1E000)
#define SEC_MODULE_PAGE_SIZE	(0x1000)

/* Return Value */
#define SEC_MODULE_RET_OK                 (0)
#define SEC_MODULE_RET_ERROR_INIT         (-1)
#define SEC_MODULE_RET_ERROR_PARAMETER    (-2)
#define SEC_MODULE_RET_ERROR_FAIL         (-3)
#define SEC_MODULE_RET_ERROR_VERIFICATION (-4)

#define SEC_MODULE_SHARED_SIZE (0x200)

#define SEC_MODULE_ENTRY (SEC_MODULE_BASE + SEC_MODULE_SHARED_SIZE)

#ifndef __ASSEMBLER__

/******************************************************************************
Typedef definitions
******************************************************************************/

typedef int (* fp_sec_module_api_t) (void);

typedef enum {
	CMD_RESET_INIT = 0,
	CMD_INJECT_KEY,
	CMD_RE_ENC_DATA,
	CMD_VERIFY_KEY,
	CMD_VERIFY_DATA,
	CMD_MAX,
} e_cmd_type_t;

typedef struct {
	uint64_t inst_area;
} st_reset_init_t;

typedef struct {
	uint64_t key_ring;
	uint64_t prov_key;
} st_inject_key_t;

typedef struct {
	int num;
	struct {
		uint64_t src;
		uint64_t len;
		uint64_t dst;
	} list[16];
} st_re_enc_data_t;

typedef struct {
	uint64_t src;
	uint64_t len;
	uint64_t dst;
	uint64_t heap;
} st_verify_data_t;

typedef struct {
	uint64_t cmd;
	uint64_t len;
	union {
		st_reset_init_t reset_init;
		st_inject_key_t inject_key;
		st_re_enc_data_t re_enc_data;
		st_verify_data_t verify_data;
	} prm;
} st_sec_module_arg_t;

/******************************************************************************
Exported global functions (to be accessed by other files)
******************************************************************************/

#endif /* __ASSEMBLER__ */

#endif /* SEC_MODULE_H */
