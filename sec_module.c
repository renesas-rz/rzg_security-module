/*
 * Copyright (c) 2020-2021, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/******************************************************************************
 Includes <System Includes> , "Project Includes"
******************************************************************************/
#include <stdint.h>
#include <stddef.h>

#include "sec_module.h"
#include "R_TSIP_Boot_Lib.h"

/******************************************************************************
Macro definitions
******************************************************************************/

#define WORK_ADR_SRAM_SIZE (480)

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef int (* func_cmd) (unsigned int len, void* const param);

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
volatile st_sec_module_arg_t gs_arguments __attribute__((section("SHARED_AREA"))) = {0};

/******************************************************************************
Private global variables and functions
******************************************************************************/
static int cmd_reset_init(unsigned int len, void * const param);
static int cmd_inject_key(unsigned int len, void * const param);
static int cmd_re_enc_data(unsigned int len, void * const param);
static int cmd_verify_key(unsigned int len, void * const param);
static int cmd_verify_data(unsigned int len, void * const param);

static const func_cmd gs_command_function[CMD_MAX] = {
    cmd_reset_init,
    cmd_inject_key,
    cmd_re_enc_data,
    cmd_verify_key,
    cmd_verify_data,
};

static uint32_t gs_work_addr_sram[WORK_ADR_SRAM_SIZE/4];

/******************************************************************************
 * Function Name : sec_module
 * Description   : main function of sec_module
 * Arguments     : none
 * Return Value  : SEC_MODULE_RET_OK
 *                 - Success.
 *                 SEC_MODULE_RET_ERROR_INIT
 *                 - Hardware reset required.
 *                 SEC_MODULE_RET_ERROR_PARAMETER
 *                 - Resolve the cause and call again.
 *                 SEC_MODULE_RET_ERROR_FAIL
 *                 - Resolve the cause and call again.
 *                 SEC_MODULE_RET_ERROR_VERIFICATION
 *                 - Hardware reset required.
 ******************************************************************************/
int sec_module (void)
{
    e_cmd_type_t cmd = (e_cmd_type_t)gs_arguments.cmd;
    unsigned int len = (unsigned int)gs_arguments.len;
    void * prm = (void *)&gs_arguments.prm;
    
    if ((0 > cmd) || (CMD_MAX <= cmd)) {
        return SEC_MODULE_RET_ERROR_PARAMETER;
    }
    
    return gs_command_function[cmd] (len, prm);
} /* End of function sec_module() */

/******************************************************************************
 * Function Name : cmd_reset_init
 * Description   : function of CMD_RESET_INIT command
 * Arguments     : len
 *                  - Size of command parameter
 *                 param
 *                  - Pointer where the command parameter is located
 * Return Value  : SEC_MODULE_RET_OK
 *                 SEC_MODULE_RET_ERROR_INIT
 *                 SEC_MODULE_RET_ERROR_PARAMETER
 *                 SEC_MODULE_RET_ERROR_FAIL
 ******************************************************************************/
static int cmd_reset_init(unsigned int len, void* const param)
{
    unsigned long err;
    unsigned char * S_RAMData;
    unsigned char * S_INSTData;

    st_reset_init_t* const p_reset_init = (st_reset_init_t *)param;

    if((sizeof(st_reset_init_t) != len) || (NULL == p_reset_init)) {
        return SEC_MODULE_RET_ERROR_PARAMETER;
    }

    S_RAMData = (unsigned char *)gs_work_addr_sram;
    S_INSTData = (unsigned char *)p_reset_init->inst_area;

    err = R_TSIP_Init (S_RAMData, S_INSTData);
    if (R_PASS != err) {
        if (R_INITIALIZATION_ERROR == err) {
            return SEC_MODULE_RET_ERROR_INIT;
        }
        else if (R_PARAMETER_FAIL == err) {
            return SEC_MODULE_RET_ERROR_PARAMETER;
        }
        else {
            return SEC_MODULE_RET_ERROR_FAIL;
        }
    }

    return SEC_MODULE_RET_OK;
} /* End of function cmd_reset_init() */

/******************************************************************************
 * Function Name : cmd_inject_key
 * Description   : function of CMD_INJECT_KEY command
 * Arguments     : len
 *                  - Size of command parameter
 *                 param
 *                  - Pointer where the command parameter is located
 * Return Value  : SEC_MODULE_RET_OK
 *                 SEC_MODULE_RET_ERROR_PARAMETER
 *                 SEC_MODULE_RET_ERROR_FAIL
 ******************************************************************************/
static int cmd_inject_key(unsigned int len, void* const param)
{

    unsigned long err;
    unsigned char *InData_ProvisioningKeyOperationCode;
    unsigned char *InData_KeyRingOperationCode;

    st_inject_key_t* const p_inject_key = (st_inject_key_t *)param;

    if((sizeof(st_inject_key_t) != len) || (NULL == p_inject_key)) {
        return SEC_MODULE_RET_ERROR_PARAMETER;
    }

    InData_ProvisioningKeyOperationCode = (unsigned char *)p_inject_key->prov_key;
    InData_KeyRingOperationCode = (unsigned char *)p_inject_key->key_ring;

    err = R_TSIP_Inject_Key(InData_ProvisioningKeyOperationCode, InData_KeyRingOperationCode);
    if (R_PASS != err) {
        if (R_PARAMETER_FAIL == err) {
            return SEC_MODULE_RET_ERROR_PARAMETER;
        }
        else {
            return SEC_MODULE_RET_ERROR_FAIL;
        }
    }

    return SEC_MODULE_RET_OK;
} /* End of function cmd_inject_key() */

/******************************************************************************
 * Function Name : cmd_re_enc_data
 * Description   : function of CMD_RE_ENC_DATA command
 * Arguments     : len
 *                  - Size of command parameter
 *                 param
 *                  - Pointer where the command parameter is located
 * Return Value  : SEC_MODULE_RET_OK
 *                 SEC_MODULE_RET_ERROR_PARAMETER
 *                 SEC_MODULE_RET_ERROR_FAIL
 ******************************************************************************/
static int cmd_re_enc_data(unsigned int len, void* const param)
{
    unsigned long err;
    TSIP_REENC_BOOT_DATA tsip_reenc_boot_data;
    st_re_enc_data_t* const p_re_enc_data = (st_re_enc_data_t *)param;

    if((sizeof(st_re_enc_data_t) != len) || (NULL == p_re_enc_data)) {
        return SEC_MODULE_RET_ERROR_PARAMETER;
    }

    for (int i = 0; i < 16; i++) {
        tsip_reenc_boot_data[i].InData_BootData = 0;
        tsip_reenc_boot_data[i].InData_BootData_ByteSize = 0;
        tsip_reenc_boot_data[i].OutData_BootData = 0;

        if(i < p_re_enc_data->num) {
            tsip_reenc_boot_data[i].InData_BootData = (unsigned char *)p_re_enc_data->list[i].src;
            tsip_reenc_boot_data[i].InData_BootData_ByteSize = p_re_enc_data->list[i].len;
            tsip_reenc_boot_data[i].OutData_BootData = (unsigned char *)p_re_enc_data->list[i].dst;
        }
    }

    err = R_TSIP_ReEncBootData(&tsip_reenc_boot_data);
    if (R_PASS != err) {
        if (R_PARAMETER_FAIL == err) {
            return SEC_MODULE_RET_ERROR_PARAMETER;
        }
        else {
            return SEC_MODULE_RET_ERROR_FAIL;
        }
    }

    return SEC_MODULE_RET_OK;
} /* End of function cmd_re_enc_data() */

/******************************************************************************
 * Function Name : cmd_verify_key
 * Description   : function of CMD_VERIFY_KEY command
 * Arguments     : len
 *                  - Size of command parameter
 *                 param
 *                  - Pointer where the command parameter is located
 * Return Value  : SEC_MODULE_RET_OK
 *                 SEC_MODULE_RET_ERROR_VERIFICATION
 *                 SEC_MODULE_RET_ERROR_FAIL
 ******************************************************************************/
static int cmd_verify_key(unsigned int len, void* const param)
{
    unsigned long err;
    (void)len;
    (void)param;

    err = R_TSIP_KeyRing_Verify();
    if (R_PASS != err) {
        if (R_KEYRING_FORMAT_FAIL == err) {
            return SEC_MODULE_RET_ERROR_VERIFICATION;
        }
        else if (R_VERIFICATION_FAIL == err) {
            return SEC_MODULE_RET_ERROR_VERIFICATION;
        }
        else {
            return SEC_MODULE_RET_ERROR_FAIL;
        }
    }

    return SEC_MODULE_RET_OK;
} /* End of function cmd_verify_key() */

/******************************************************************************
 * Function Name : cmd_verify_data
 * Description   : function of CMD_VERIFY_DATA command
 * Arguments     : len
 *                  - Size of command parameter
 *                 param
 *                  - Pointer where the command parameter is located
 * Return Value  : SEC_MODULE_RET_OK
 *                 SEC_MODULE_RET_ERROR_PARAMETER
 *                 SEC_MODULE_RET_ERROR_VERIFICATION
 *                 SEC_MODULE_RET_ERROR_FAIL
 ******************************************************************************/
static int cmd_verify_data(unsigned int len, void* const param)
{
    unsigned long err;
    unsigned char *InData_BootData;
    unsigned long InData_BootData_ByteSize;
    unsigned char *InData_BootData_HeapArea;
    unsigned char *OutData_BootData;

    st_verify_data_t* const p_verify_data = (st_verify_data_t *)param;

    if(sizeof(st_verify_data_t) != len) {
        return SEC_MODULE_RET_ERROR_PARAMETER;
    }

    InData_BootData = (unsigned char *)p_verify_data->src;
    InData_BootData_ByteSize = p_verify_data->len;
    InData_BootData_HeapArea = (unsigned char *)p_verify_data->heap;
    OutData_BootData = (unsigned char *)p_verify_data->dst;

    /* User Data decryption and verificaiton. In this sample, use same heap area for each user data */
    err = R_TSIP_VerifyBootData (InData_BootData,
                                 InData_BootData_ByteSize,
                                 InData_BootData_HeapArea,
                                 OutData_BootData);
    if (R_PASS != err) {
        if (R_PARAMETER_FAIL == err) {
            return SEC_MODULE_RET_ERROR_PARAMETER;
        }
        else if(R_VERIFICATION_FAIL == err) {
            return SEC_MODULE_RET_ERROR_VERIFICATION;
        }
        else {
            return SEC_MODULE_RET_ERROR_FAIL;
        }
    }

    return SEC_MODULE_RET_OK;
} /* End of function cmd_verify_data() */

