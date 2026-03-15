
#ifndef TOMMROC_HW_COMM_NFC_NDEF_H_
#define TOMMROC_HW_COMM_NFC_NDEF_H_

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

#include "comm/NFC/NDEF/types/tommRoCHwCommNFCNDEFTypes.h"

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

/******************* Encode functions */

/**
 * Encode a record.
 *
 * param[in]        TNF                     type name format.
 * param[in]        CF                      chunk flag.
 * param[in]        ME                      message end.
 * param[in]        MB                      message begin.
 * param[in]        typePtr                 type buffer pointer.
 * param[in]        typeLen                 type buffer length.
 * param[in]        IDPtr                   ID buffer pointer.
 * param[in]        IDLen                   ID buffer length.
 * param[in]        payloadPtr              payload buffer pointer.
 * param[in]        payloadLen              payload buffer length.
 * param[out]       recordBufferPtr         output data buffer pointer.
 * param[in]        recordBufferMaxSize     output data buffer max size
 * param[out]       recordBufferLenPtr      output data length pointer
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNFCNDEFRecordEncode(
        const   tommRoC_hw_comm_nfc_ndef_record_header_TNF_enum_t           TNF,
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


/******************* Decode functions */

/**
 * Decode only type of a record.
 *
 * param[in]        recordBufferPtr         data buffer pointer.
 * param[in]        recordBufferLen         data buffer length.
 * param[out]       TNFPtr                  type name format pointer.
 * param[out]       CFPtr                   chunk flag pointer.
 * param[out]       MEPtr                   message end pointer.
 * param[out]       MBPtr                   message begin pointer.
 * param[out]       typePtr                 output type buffer pointer.
 * param[in]        typeMaxSize             output type buffer max size.
 * param[out]       typeLenPtr              output type length pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNFCNDEFRecordDecodeType(
        const   uint8_t*                                            const   recordBufferPtr,
        const   uint16_t                                                    recordBufferLen,
                tommRoC_hw_comm_nfc_ndef_record_header_TNF_enum_t*  const   TNFPtr,
                tommRoC_hw_comm_nfc_ndef_record_header_CF_enum_t*   const   CFPtr,
                tommRoC_hw_comm_nfc_ndef_record_header_ME_enum_t*   const   MEPtr,
                tommRoC_hw_comm_nfc_ndef_record_header_MB_enum_t*   const   MBPtr,
                void*                                               const   typePtr,
        const   uint16_t                                                    typeMaxSize,
                uint16_t*                                           const   typeLenPtr);

/**
 * Decode a record.
 *
 * param[in]        recordBufferPtr         data buffer pointer.
 * param[in]        recordBufferLen         data buffer length.
 * param[out]       TNFPtr                  type name format pointer.
 * param[out]       CFPtr                   chunk flag pointer.
 * param[out]       MEPtr                   message end pointer.
 * param[out]       MBPtr                   message begin pointer.
 * param[out]       typePtr                 output type buffer pointer.
 * param[in]        typeMaxSize             output type buffer max size.
 * param[out]       typeLenPtr              output type length pointer.
 * param[out]       IDPtr                   output ID buffer pointer.
 * param[in]        IDMaxSize               output ID buffer max size.
 * param[out]       IDLenPtr                output ID length pointer.
 * param[out]       payloadPtr              output payload buffer pointer.
 * param[in]        payloadMaxSize          output payload buffer max size.
 * param[out]       payloadLenPtr           output payload length pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNFCNDEFRecordDecode(
        const   uint8_t*                                            const   recordBufferPtr,
        const   uint16_t                                                    recordBufferLen,
                tommRoC_hw_comm_nfc_ndef_record_header_TNF_enum_t*  const   TNFPtr,
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
