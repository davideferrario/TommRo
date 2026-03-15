
#ifndef TOMMROC_HW_COMM_NFC_NDEF_TYPE_TNF1_H_
#define TOMMROC_HW_COMM_NFC_NDEF_TYPE_TNF1_H_

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

// NFC NDEF TNF1 message record size.
#define TOMMROC_HW_COMM_NFC_NDEF_TYPE_TNF1_TEXT_RECORD_SIZE_BYTE(langCodeStrLen, textStrLen)    \
        (TOMMROC_HW_COMM_NFC_NDEF_RECORD_SHORT_PAYLOAD_NO_ID_SIZE_BYTE(                         \
                TOMMROC_UTIL_U8_SIZE,                                                           \
                TOMMROC_UTIL_U8_SIZE + langCodeStrLen + textStrLen))

#define TOMMROC_HW_COMM_NFC_NDEF_TYPE_TNF1_URI_RECORD_SIZE_BYTE(URIStrLen)                      \
        (TOMMROC_HW_COMM_NFC_NDEF_RECORD_SHORT_PAYLOAD_NO_ID_SIZE_BYTE(                         \
                TOMMROC_UTIL_U8_SIZE,                                                           \
                TOMMROC_UTIL_U8_SIZE + URIStrLen))

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * TNF1 record type.
 */
typedef enum {

    // TNF1 text record type.
    TOMMROC_HW_COMM_NFC_NDEF_TYPE_TNF1_TEXT_RECORD_TYPE = 0,

    // TNF1 URI record type.
    TOMMROC_HW_COMM_NFC_NDEF_TYPE_TNF1_URI_RECORD_TYPE,

} tommRoC_hw_comm_nfc_ndef_type_tnf1_type_enum_t;


/**
 * Encoding type (UTF8 or UTF16).
 */
typedef enum {

    // Encoding type is UTF8.
    TOMMROC_HW_COMM_NFC_NDEF_TYPE_TNF1_ENCODING_TYPE_UTF8 = 0,

    // Encoding type is UTF16.
    TOMMROC_HW_COMM_NFC_NDEF_TYPE_TNF1_ENCODING_TYPE_UTF16,

} tommRoC_hw_comm_nfc_ndef_type_tnf1_enc_type_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* Encode functions */

/**
 * Encode a TNF1 (Well Known) Text record.
 *
 * param[in]        CF                      chunk flag.
 * param[in]        ME                      message end.
 * param[in]        MB                      message begin.
 * param[in]        encType                 text encoding type.
 * param[in]        langCodeStrPtr          language code string pointer.
 * param[in]        textStrPtr              text string pointer.
 * param[out]       recordBufferPtr         output data buffer pointer.
 * param[in]        recordBufferMaxSize     output data buffer max size
 * param[out]       recordBufferLenPtr      output data length pointer
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNFCNDEFTypeTNF1WellKnownTextRecordEncode(
        const   tommRoC_hw_comm_nfc_ndef_record_header_CF_enum_t            CF,
        const   tommRoC_hw_comm_nfc_ndef_record_header_ME_enum_t            ME,
        const   tommRoC_hw_comm_nfc_ndef_record_header_MB_enum_t            MB,
        const   tommRoC_hw_comm_nfc_ndef_type_tnf1_enc_type_enum_t          encType,
        const   char*                                               const   langCodeStrPtr,
        const   char*                                               const   textStrPtr,
                uint8_t*                                            const   recordBufferPtr,
        const   uint16_t                                                    recordBufferMaxSize,
                uint16_t*                                           const   recordBufferLenPtr);

/**
 * Encode a TNF1 (Well Known) URI record.
 *
 * param[in]        CF                      chunk flag.
 * param[in]        ME                      message end.
 * param[in]        MB                      message begin.
 * param[in]        IDCode                  ID code.
 * param[in]        URIStrPtr               URI string pointer.
 * param[out]       recordBufferPtr         output data buffer pointer.
 * param[in]        recordBufferMaxSize     output data buffer max size
 * param[out]       recordBufferLenPtr      output data length pointer
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNFCNDEFTypeTNF1WellKnownURIRecordEncode(
        const   tommRoC_hw_comm_nfc_ndef_record_header_CF_enum_t            CF,
        const   tommRoC_hw_comm_nfc_ndef_record_header_ME_enum_t            ME,
        const   tommRoC_hw_comm_nfc_ndef_record_header_MB_enum_t            MB,
        const   uint8_t                                                     IDCode,
        const   char*                                               const   URIStrPtr,
                uint8_t*                                            const   recordBufferPtr,
        const   uint16_t                                                    recordBufferMaxSize,
                uint16_t*                                           const   recordBufferLenPtr);


/******************* Decode functions */

/**
 * Decode a TNF1 (Well Known) record to get type (Text or URI).
 *
 * param[in]        recordBufferPtr         data buffer pointer.
 * param[in]        recordBufferLen         data buffer length.
 * param[out]       CFPtr                   chunk flag pointer.
 * param[out]       MEPtr                   message end pointer.
 * param[out]       MBPtr                   message begin pointer.
 * param[out]       typePtr                 TNF1 type pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNFCNDEFTypeTNF1WellKnownRecordDecodeType(
        const   uint8_t*                                            const   recordBufferPtr,
        const   uint16_t                                                    recordBufferLen,
                tommRoC_hw_comm_nfc_ndef_record_header_CF_enum_t*   const   CFPtr,
                tommRoC_hw_comm_nfc_ndef_record_header_ME_enum_t*   const   MEPtr,
                tommRoC_hw_comm_nfc_ndef_record_header_MB_enum_t*   const   MBPtr,
                tommRoC_hw_comm_nfc_ndef_type_tnf1_type_enum_t*     const   typePtr);

/**
 * Decode a TNF1 (Well Known) Text record.
 *
 * param[in]        recordBufferPtr         data buffer pointer.
 * param[in]        recordBufferLen         data buffer length.
 * param[out]       CFPtr                   chunk flag pointer.
 * param[out]       MEPtr                   message end pointer.
 * param[out]       MBPtr                   message begin pointer.
 * param[out]       encTypePtr              text encoding type pointer.
 * param[out]       langCodeStrPtr          language code string buffer pointer.
 * param[in]        langCodeStrMaxSize      language code string buffer max size.
 * param[out]       textStrPtr              text string buffer pointer.
 * param[in]        textStrMaxSize          text string buffer max size.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNFCNDEFTypeTNF1WellKnownTextRecordDecode(
        const   uint8_t*                                            const   recordBufferPtr,
        const   uint16_t                                                    recordBufferLen,
                tommRoC_hw_comm_nfc_ndef_record_header_CF_enum_t*   const   CFPtr,
                tommRoC_hw_comm_nfc_ndef_record_header_ME_enum_t*   const   MEPtr,
                tommRoC_hw_comm_nfc_ndef_record_header_MB_enum_t*   const   MBPtr,
                tommRoC_hw_comm_nfc_ndef_type_tnf1_enc_type_enum_t* const   encTypePtr,
                char*                                               const   langCodeStrPtr,
        const   uint16_t                                                    langCodeStrMaxSize,
                char*                                               const   textStrPtr,
        const   uint16_t                                                    textStrMaxSize);

/**
 * Decode a TNF1 (Well Known) URI record.
 *
 * param[in]        recordBufferPtr         data buffer pointer.
 * param[in]        recordBufferLen         data buffer length.
 * param[out]       CFPtr                   chunk flag pointer.
 * param[out]       MEPtr                   message end pointer.
 * param[out]       MBPtr                   message begin pointer.
 * param[out]       IDCodePtr               ID code pointer.
 * param[out]       URIStrPtr               URI string buffer pointer.
 * param[in]        URIStrMaxSize           URI string buffer max size.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNFCNDEFTypeTNF1WellKnownURIRecordDecode(
        const   uint8_t*                                            const   recordBufferPtr,
        const   uint16_t                                                    recordBufferLen,
                tommRoC_hw_comm_nfc_ndef_record_header_CF_enum_t*   const   CFPtr,
                tommRoC_hw_comm_nfc_ndef_record_header_ME_enum_t*   const   MEPtr,
                tommRoC_hw_comm_nfc_ndef_record_header_MB_enum_t*   const   MBPtr,
                uint8_t*                                            const   IDCodePtr,
                char*                                               const   URIStrPtr,
        const   uint16_t                                                    URIStrMaxSize);

#endif
