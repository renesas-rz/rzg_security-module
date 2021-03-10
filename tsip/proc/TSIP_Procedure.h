/*
 * Copyright (c) 2020, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! *****************************************************************************
    @file    TSIP_Procedure.h
    @brief   TSIP Procedure
    
    @par    Copyright
    Copyright (C) 2011 - 2019 Renesas Electronics Corporation. All rights reserved.
    @par    History
    @subsection sub_history 
    - Initial version\n
 ********************************************************************************/

#ifndef  TSIP_PROCEDURE_H_
#define  TSIP_PROCEDURE_H_

/*------------------------------------------------------------------------------*/
/*                        Include Files                                         */
/*------------------------------------------------------------------------------*/

#include  <stdint.h>
#include  <stddef.h>

extern void TSIPPrc_p00(void);
extern uint8_t TSIPPrc_p01(void);
extern uint8_t TSIPPrc_p02(void);
extern uint8_t TSIPPrc_p03(void);
extern uint8_t TSIPPrc_p04(const uint32_t InData_SharedKeyIndex[],
                           const uint32_t InData_SessionKey[],
                           const uint32_t InData_IV[],
                           const uint32_t InData_InstData[],
                                 uint32_t OutData_InstData[]);
extern uint8_t TSIPPrc_p10(void);
extern uint8_t TSIPPrc_p11(const uint32_t InData_Operation[],
                           const uint32_t InData_IV[],
                           const uint32_t InData_KeyOperationCode[],
                                 uint32_t OutData_KeyIndex[]);
extern uint8_t TSIPPrc_p12(void);
extern uint8_t TSIPPrc_p13(void);
extern uint8_t TSIPPrc_p14(const uint32_t InData_Prog_Num[]);
extern uint8_t TSIPPrc_p15(const uint32_t InData_Prog[],
                           const uint32_t InData_ProgLength[],
                                 uint32_t OutData_Prog[],
                                 uint32_t OutData_Header[]);
extern uint8_t TSIPPrc_p16(const uint32_t InData_Header[]);
extern uint8_t TSIPPrc_p17(const uint32_t InData_Prog[],
                           const uint32_t InData_ProgLength[],
                                 uint32_t OutData_Prog[]);


extern uint8_t TSIPPrc_p40(void);
extern uint8_t TSIPPrc_p43(const uint32_t InData_IV[],
                           const uint32_t InData_InstData[],
                                 uint32_t OutData_InstData[]);
extern uint8_t TSIPPrc_p44(const uint32_t InData_Prog_Num[]);
extern uint8_t TSIPPrc_p45(const uint32_t InData_ProgNo[],
                           const uint32_t InData_Prog[],
                           const uint32_t InData_ProgLength[],
                                 uint32_t OutData_Prog[]);

extern uint8_t TSIPPrc_p30(const uint32_t InData_Text[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_Text_Last[],
                           const uint32_t InData_Text_Last_LEN[],
                                 uint32_t OutData_Text[],
                                 uint32_t OutData_Text_Last[],
                                 uint32_t OutData_Header[]);
extern uint8_t TSIPPrc_p31(const uint32_t InData_Header[],
                           const uint32_t InData_Text[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_Text_Last[],
                           const uint32_t InData_Text_Last_LEN[],
                                 uint32_t OutData_Text[],
                                 uint32_t OutData_Text_Last[]);

extern uint8_t TSIPPrc_p3c(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_IV[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_Text[],
                                 uint32_t OutData_Text[]);
extern uint8_t TSIPPrc_p3d(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_IV[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_Text[],
                                 uint32_t OutData_Text[]);
extern uint8_t TSIPPrc_p4c(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_IV[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_Text[],
                                 uint32_t OutData_Text[]);
extern uint8_t TSIPPrc_p4d(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_IV[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_Text[],
                                 uint32_t OutData_Text[]);

extern uint8_t TSIPPrc_p7a(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_Text[],
                                 uint32_t OutData_Text[]);
extern uint8_t TSIPPrc_p7b(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_Text[],
                                 uint32_t OutData_Text[]);
extern uint8_t TSIPPrc_p7c(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_Text[],
                                 uint32_t OutData_Text[]);
extern uint8_t TSIPPrc_p7d(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_Text[],
                                 uint32_t OutData_Text[]);
extern uint8_t TSIPPrc_p7e(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_Text[],
                                 uint32_t OutData_Text[]);
extern uint8_t TSIPPrc_p7f(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_Text[],
                                 uint32_t OutData_Text[]);

extern uint8_t TSIPPrc_p5f(const uint32_t InData_SHA1InitVal[],
                           const uint32_t InData_PaddedMsg[],
                           const uint32_t MAX_CNT,
                           const uint32_t Last_Data[],
                           const uint32_t Last_Data_Cnt,
                                 uint32_t OutData_MsgDigest[]);
extern uint8_t TSIPPrc_p6f(const uint32_t InData_SHA256InitVal[],
                           const uint32_t InData_PaddedMsg[],
                           const uint32_t MAX_CNT,
                           const uint32_t Last_Data[],
                           const uint32_t Last_Data_Cnt,
                                 uint32_t OutData_MsgDigest[]);

extern uint8_t TSIPPrc_p8a(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_IV[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_PaddedMsg[],
                                 uint32_t OutData_MAC[]);
extern uint8_t TSIPPrc_p8b(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_IV[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_PaddedMsg[],
                           const uint32_t Last_Data[],
                           const uint32_t InData_MsgType[],
                                 uint32_t OutData_MAC[]);
extern uint8_t TSIPPrc_p8c(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_IV[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_PaddedMsg[],
                           const uint32_t Last_Data[],
                           const uint32_t InData_MsgType[],
                           const uint32_t InData_CompareMAC[],
                           const uint32_t InData_CompareMACLen[]);
extern uint8_t TSIPPrc_p9a(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_IV[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_PaddedMsg[],
                                 uint32_t OutData_MAC[]);
extern uint8_t TSIPPrc_p9b(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_IV[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_PaddedMsg[],
                           const uint32_t Last_Data[],
                           const uint32_t InData_MsgType[],
                                 uint32_t OutData_MAC[]);
extern uint8_t TSIPPrc_p9c(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_IV[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_PaddedMsg[],
                           const uint32_t Last_Data[],
                           const uint32_t InData_MsgType[],
                           const uint32_t InData_CompareMAC[],
                           const uint32_t InData_CompareMACLen[]);

extern uint8_t TSIPPrc_p5a(const uint32_t InData_KeyIndex[],
                                 uint32_t OutData_MAC[]);
extern uint8_t TSIPPrc_p5b(const uint32_t InData_MAC[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_PaddedMsg[],
                                 uint32_t OutData_MAC[]);
extern uint8_t TSIPPrc_p5c(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_MAC[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_PaddedMsg[],
                           const uint32_t Last_Data[],
                           const uint32_t Last_Data_Cnt,
                                 uint32_t OutData_MAC[]);
extern uint8_t TSIPPrc_p5d(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_MAC[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_PaddedMsg[],
                           const uint32_t Last_Data[],
                           const uint32_t Last_Data_Cnt,
                           const uint32_t InData_CompareMAC[],
                           const uint32_t InData_CompareMACLen[]);
extern uint8_t TSIPPrc_p6a(const uint32_t InData_KeyIndex[],
                                 uint32_t OutData_MAC[]);
extern uint8_t TSIPPrc_p6b(const uint32_t InData_MAC[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_PaddedMsg[],
                                 uint32_t OutData_MAC[]);
extern uint8_t TSIPPrc_p6c(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_MAC[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_PaddedMsg[],
                           const uint32_t Last_Data[],
                           const uint32_t Last_Data_Cnt,
                                 uint32_t OutData_MAC[]);
extern uint8_t TSIPPrc_p6d(const uint32_t InData_KeyIndex[],
                           const uint32_t InData_MAC[],
                           const uint32_t MAX_CNT,
                           const uint32_t InData_PaddedMsg[],
                           const uint32_t Last_Data[],
                           const uint32_t Last_Data_Cnt,
                           const uint32_t InData_CompareMAC[],
                           const uint32_t InData_CompareMACLen[]);

extern uint8_t TSIPPrc_p3f(uint32_t OutData_Text[]);

extern uint8_t TSIPPrc_p3e(const uint32_t InData_Operation[],
                           const uint32_t InData_IV[],
                           const uint32_t InData_KeyOperationCode[],
                                 uint32_t OutData_KeyIndex[]);

extern uint8_t TSIPPrc_p50(const uint32_t InData_Certificates[],
                           const uint32_t InData_CertificatesLength[],
                           const uint32_t InData_Signature[],
                           const uint32_t InData_CertificatesInfo[],
                                 uint32_t OutData_PubKey[]);
extern uint8_t TSIPPrc_p51(const uint32_t InData_PubKey[],
                           const uint32_t InData_TBSCertificate[],
                           const uint32_t InData_TBSCertificateLength[],
                           const uint32_t InData_Signature[],
                           const uint32_t InData_TBSCertificateInfo[],
                                 uint32_t OutData_PubKey[]);
extern uint8_t TSIPPrc_p52(const uint32_t InData_PubKey[],
                           const uint32_t InData_TBSCertificate[],
                           const uint32_t InData_TBSCertificateLength[],
                           const uint32_t InData_Signature[],
                           const uint32_t InData_TBSCertificateInfo[],
                                 uint32_t OutData_PubKey[]);

extern uint8_t TSIPPrc_p61(const uint32_t InData_PubKey[],
                           const uint32_t InData_PreMasterSecret[],
                                 uint32_t OutData_PreMasterSecret[]);

extern uint8_t TSIPPrc_p70(uint32_t OutData_PreMasterSecret[]);
extern uint8_t TSIPPrc_p71(const uint32_t InData_PreMasterSecret[],
                           const uint32_t InData_ClientRandom[],
                           const uint32_t InData_ServerRandom[],
                                 uint32_t OutData_MasterSecret[]);
extern uint8_t TSIPPrc_p72(const uint32_t InData_Sel_CipherSuite[],
                           const uint32_t InData_MasterSecret[],
                           const uint32_t InData_ClientRandom[],
                           const uint32_t InData_ServerRandom[],
                                 uint32_t OutData_ClientMACKeyOperationCode[],
                                 uint32_t OutData_ServerMACKeyOperationCode[],
                                 uint32_t OutData_ClientEncKeyOperationCode[],
                                 uint32_t OutData_ServerEncKeyOperationCode[],
                                 uint32_t OutData_ClientIV[],
                                 uint32_t OutData_ServerIV[]);
extern uint8_t TSIPPrc_p73(const uint32_t InData_Sel_VerifyData[],
                           const uint32_t InData_MasterSecret[],
                           const uint32_t InData_HandShakeHash[],
                                 uint32_t OutData_VerifyData[]);
extern uint8_t TSIPPrc_p74(const uint32_t MAX_CNT,
                                 uint32_t OutData_KeyIndex[],
                                 uint32_t OutData_Modulus[],
                                 uint32_t OutData_PubExp[]);

extern uint8_t TSIPPrc_subprc01(void);
extern uint8_t TSIPPrc_subprc02(void);
extern uint8_t TSIPPrc_subprc18(void);

extern uint8_t TSIPPrc_subprc22(void);
extern uint8_t TSIPPrc_subprc70(void);
extern uint8_t TSIPPrc_subprc71(void);
extern uint8_t TSIPPrc_subprc72(void);

#endif  /* TSIP_PROCEDURE_H */

