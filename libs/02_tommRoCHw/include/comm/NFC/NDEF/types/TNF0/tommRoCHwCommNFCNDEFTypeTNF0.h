
#ifndef TOMMROC_HW_COMM_NFC_NDEF_TYPE_TNF0_H_
#define TOMMROC_HW_COMM_NFC_NDEF_TYPE_TNF0_H_

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

/**
 * Empty Record.
 * No type/ID/payload is associated with this NDEF Record.
 * This record type is useful on newly formatted cards since every NDEF tag
 * must have at least one NDEF Record.
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

// NFC NDEF TNF0 message record size.
#define TOMMROC_HW_COMM_NFC_NDEF_TYPE_TNF0_SIZE_BYTE    \
        (TOMMROC_HW_COMM_NFC_NDEF_RECORD_SHORT_PAYLOAD_NO_ID_SIZE_BYTE(0, 0))

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* Encode functions */

/**
 * Encode a TNF0 (Empty) record.
 *
 * param[in]        CF                      chunk flag.
 * param[in]        ME                      message end.
 * param[in]        MB                      message begin.
 * param[out]       recordBufferPtr         output data buffer pointer.
 * param[in]        recordBufferMaxSize     output data buffer max size
 * param[out]       recordBufferLenPtr      output data length pointer
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNFCNDEFTypeTNF0EmptyRecordEncode(
        const   tommRoC_hw_comm_nfc_ndef_record_header_CF_enum_t            CF,
        const   tommRoC_hw_comm_nfc_ndef_record_header_ME_enum_t            ME,
        const   tommRoC_hw_comm_nfc_ndef_record_header_MB_enum_t            MB,
                uint8_t*                                            const   recordBufferPtr,
        const   uint16_t                                                    recordBufferMaxSize,
                uint16_t*                                           const   recordBufferLenPtr);


/******************* Decode functions */

/**
 * Decode a TNF0 (Empty) record.
 *
 * param[in]        recordBufferPtr         data buffer pointer.
 * param[in]        recordBufferLen         data buffer length.
 * param[out]       CFPtr                   chunk flag pointer.
 * param[out]       MEPtr                   message end pointer.
 * param[out]       MBPtr                   message begin pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNFCNDEFTypeTNF0EmptyRecordDecode(
        const   uint8_t*                                            const   recordBufferPtr,
        const   uint16_t                                                    recordBufferLen,
                tommRoC_hw_comm_nfc_ndef_record_header_CF_enum_t*   const   CFPtr,
                tommRoC_hw_comm_nfc_ndef_record_header_ME_enum_t*   const   MEPtr,
                tommRoC_hw_comm_nfc_ndef_record_header_MB_enum_t*   const   MBPtr);

#endif
