
#ifndef TOMMROC_HW_COMM_NFC_SNEP_H_
#define TOMMROC_HW_COMM_NFC_SNEP_H_

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
#include "tommRoCHwErr.h"

#include "TOMMROC.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/
#define TOMMROC_HW_COMM_NFC_SNEP_HEADER_SIZE_BYTE   (   TOMMROC_UTIL_U8_SIZE    +   \
                                                        TOMMROC_UTIL_U8_SIZE    +   \
                                                        TOMMROC_UTIL_U32_SIZE       )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// NFC SNEP request type.
typedef enum {

    // Send remaining fragments
    TOMMROC_HW_COMM_NFC_SNEP_REQUEST_CONTINUE_TYPE = 0,

    // Return an NDEF message
    TOMMROC_HW_COMM_NFC_SNEP_REQUEST_GET_TYPE,

    // Accept an NDEF message
    TOMMROC_HW_COMM_NFC_SNEP_REQUEST_PUT_TYPE,

    // Do not send remaining fragments
    TOMMROC_HW_COMM_NFC_SNEP_REQUEST_REJECT_TYPE,

} tommRoC_hw_comm_nfc_snep_request_type_enum_t;


// NFC SNEP response type.
typedef enum {

    // Continue send remaining fragments
    TOMMROC_HW_COMM_NFC_SNEP_RESPONSE_CONTINUE_TYPE = 0,

    // Operation succeeded
    TOMMROC_HW_COMM_NFC_SNEP_RESPONSE_SUCCESS_TYPE,

    // Resource not found
    TOMMROC_HW_COMM_NFC_SNEP_RESPONSE_NOT_FOUND_TYPE,

    // Resource exceeds data size limit
    TOMMROC_HW_COMM_NFC_SNEP_RESPONSE_EXCESS_DATA_TYPE,

    // Malformed request not understood
    TOMMROC_HW_COMM_NFC_SNEP_RESPONSE_BAD_REQUEST_TYPE,

    // Unsupported functionality requested
    TOMMROC_HW_COMM_NFC_SNEP_RESPONSE_NOT_IMPLEMENTED_TYPE,

    // Unsupported protocol version
    TOMMROC_HW_COMM_NFC_SNEP_RESPONSE_UNSUPPORTED_VERSION_TYPE,

    // Do not send remaining fragments
    TOMMROC_HW_COMM_NFC_SNEP_RESPONSE_REJECT_TYPE,

} tommRoC_hw_comm_nfc_snep_response_type_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* Encode functions */

/**
 * Encode a request message.
 *
 * param[in]        request                 request type.
 * param[in]        informationPtr          message information buffer pointer.
 * param[in]        informationLen          message information buffer length.
 * param[out]       resultBufferPtr         output data buffer pointer.
 * param[in]        resultBufferMaxSize     output data buffer max size
 * param[out]       resultBufferLenPtr      output data length pointer
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNFCSNEPRequestEncode(
        const   tommRoC_hw_comm_nfc_snep_request_type_enum_t            request,
        const   void*                                           const   informationPtr,
        const   uint16_t                                                informationLen,
                void*                                           const   resultBufferPtr,
        const   uint16_t                                                resultBufferMaxSize,
                uint16_t*                                       const   resultBufferLenPtr);

/**
 * Encode a response message.
 *
 * param[in]        response                response type.
 * param[in]        informationPtr          message information buffer pointer.
 * param[in]        informationLen          message information buffer length.
 * param[out]       resultBufferPtr         output data buffer pointer.
 * param[in]        resultBufferMaxSize     output data buffer max size
 * param[out]       resultBufferLenPtr      output data length pointer
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNFCSNEPResponseEncode(
        const   tommRoC_hw_comm_nfc_snep_response_type_enum_t           response,
        const   void*                                           const   informationPtr,
        const   uint16_t                                                informationLen,
                void*                                           const   resultBufferPtr,
        const   uint16_t                                                resultBufferMaxSize,
                uint16_t*                                       const   resultBufferLenPtr);


/******************* Decode functions */

/**
 * Decode a request message.
 *
 * param[in]        inputBufferPtr          data buffer pointer.
 * param[in]        inputBufferLen          data buffer length.
 * param[out]       requestPtr              request type pointer.
 * param[out]       informationPtr          output message information buffer pointer.
 * param[in]        informationMaxSize      output message information buffer max size.
 * param[out]       informationLenPtr       output message information buffer length pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNFCSNEPRequestDecode(
        const   void*                                           const   inputBufferPtr,
        const   uint16_t                                                inputBufferLen,
                tommRoC_hw_comm_nfc_snep_request_type_enum_t*   const   requestPtr,
                void*                                           const   informationPtr,
        const   uint16_t                                                informationMaxSize,
                uint16_t*                                       const   informationLenPtr);

/**
 * Decode a response message.
 *
 * param[in]        inputBufferPtr          data buffer pointer.
 * param[in]        inputBufferLen          data buffer length.
 * param[out]       responsePtr             response type pointer.
 * param[out]       informationPtr          output message information buffer pointer.
 * param[in]        informationMaxSize      output message information buffer max size.
 * param[out]       informationLenPtr       output message information buffer length pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNFCSNEPResponseDecode(
        const   void*                                           const   inputBufferPtr,
        const   uint16_t                                                inputBufferLen,
                tommRoC_hw_comm_nfc_snep_response_type_enum_t*  const   responsePtr,
                void*                                           const   informationPtr,
        const   uint16_t                                                informationMaxSize,
                uint16_t*                                       const   informationLenPtr);

#endif
