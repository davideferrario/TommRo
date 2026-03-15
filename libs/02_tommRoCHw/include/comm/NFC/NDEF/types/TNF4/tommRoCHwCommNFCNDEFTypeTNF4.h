
#ifndef TOMMROC_HW_COMM_NFC_NDEF_TYPE_TNF4_H_
#define TOMMROC_HW_COMM_NFC_NDEF_TYPE_TNF4_H_

/*
 *******************************************************************************
 * License
 * (C) Copyright 2017
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications according to the supply agreement.
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: this software is provided
 * "AS IS", with no express or implied warranties of any kind, including,
 * but not limited to, any implied warranties of merchantability or
 * fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Supplier will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 */

/**
 * Author
 * TommRo Software Department
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "comm/NFC/NDEF/tommRoCHwCommNFCNDEFRecord.h"

#include "tommRoCHwErr.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwCommNFCNDEFTypeTNF4ExternalRecordEncode(
        const   tommRoC_hw_comm_nfc_ndef_record_header_CF_enum_t            CF,
        const   tommRoC_hw_comm_nfc_ndef_record_header_ME_enum_t            ME,
        const   tommRoC_hw_comm_nfc_ndef_record_header_MB_enum_t            MB,
        const   void*                                               const   typePtr,
        const   uint8_t                                                     typeLen,
        const   void*                                               const   IDPtr,
        const   uint8_t                                                     IDLen,
        const   void*                                               const   payloadPtr,
        const   uint16_t                                                    payloadLen,
                uint8_t*                                            const   recordBufferPtr,
        const   uint16_t                                                    recordBufferMaxSize,
                uint16_t*                                           const   recordBufferLenPtr);

tommRoC_hw_err_enum_t tommRoCHwCommNFCNDEFTypeTNF4ExternalRecordDecode(
        const   uint8_t*                                            const   recordBufferPtr,
        const   uint16_t                                                    recordBufferLen,
                tommRoC_hw_comm_nfc_ndef_record_header_CF_enum_t*   const   CFPtr,
                tommRoC_hw_comm_nfc_ndef_record_header_ME_enum_t*   const   MEPtr,
                tommRoC_hw_comm_nfc_ndef_record_header_MB_enum_t*   const   MBPtr,
                void*                                               const   typePtr,
        const   uint16_t                                                    typeMaxSize,
                uint16_t*                                           const   typeLenPtr,
                void*                                               const   IDPtr,
        const   uint16_t                                                    IDMaxSize,
                uint16_t*                                           const   IDLenPtr,
                void*                                               const   payloadPtr,
        const   uint16_t                                                    payloadMaxSize,
                uint16_t*                                           const   payloadLenPtr);

#endif
