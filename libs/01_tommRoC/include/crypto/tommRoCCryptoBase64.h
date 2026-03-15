
#ifndef TOMMROC_CRYPTO_BASE64_H_
#define TOMMROC_CRYPTO_BASE64_H_

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
 * @defgroup tommRoCCryptoBase64 tommRoCCryptoBase64
 *
 * @brief  TommRoC library crypto Base64 module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted crypto Base64 functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCString.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// Macro to get base64 encoded size starting from plain size (NULL terminator - '\0' - character included).
#define TOMMROC_CRYPTO_BASE64_ENCODED_SIZE_BYTE(plainLen)           ((0 == (plainLen % 3UL)) ? (((plainLen / 3UL) * 4UL) + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE) : ((((plainLen + (3UL - (plainLen % 3UL))) / 3UL) * 4UL) + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE))

// Macro to get base64 encoded size starting from plain size (NULL terminator - '\0' - character NOT included).
#define TOMMROC_CRYPTO_BASE64_ENCODED_NO_TERM_SIZE_BYTE(plainLen)   (TOMMROC_CRYPTO_BASE64_ENCODED_SIZE_BYTE(plainLen) - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Base64 encode.
 *
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer length [byte].
 * param[in]        outputStrMaxSize        output string buffer max size [byte].
 * param[out]       outputStrPtr            output string buffer pointer.
 *                                          NOTE: NULL terminator ('\0') char will be added at the end of the string.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoBase64Encode(
        const   uint8_t*    const   inputBufferPtr,
        const   uint32_t            inputBufferLen,
        const   uint32_t            outputStrMaxSize,
                char*       const   outputStrPtr);

/**
 * Base64 encode.
 * NOTE: NULL terminator ('\0') char not added at the end of the string version.
 *
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer length [byte].
 * param[in]        outputStrMaxSize        output string buffer max size [byte].
 * param[out]       outputStrPtr            output string buffer pointer.
 * param[out]       outputStrLenPtr         output string length [byte] pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoBase64EncodeNoTerm(
        const   uint8_t*    const   inputBufferPtr,
        const   uint32_t            inputBufferLen,
        const   uint32_t            outputStrMaxSize,
                char*       const   outputStrPtr,
                uint32_t*   const   outputStrLenPtr);

/**
 * Base64 decode.
 *
 * param[in]        inputStrPtr             input string buffer pointer [NOTE: string have to be terminated with '\0'].
 * param[out]       outputBufferPtr         output data buffer pointer.
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferLenPtr      output data buffer result length pointer [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoBase64Decode(
        const   char*       const   inputStrPtr,
                uint8_t*    const   outputBufferPtr,
        const   uint32_t            outputBufferMaxSize,
                uint32_t*   const   outputBufferLenPtr);

/**
 * Base64 decode (with input string length as parameter version).
 *
 * param[in]        inputStrPtr             input string buffer pointer.
 * param[in]        inputStrLen             input string length [byte].
 * param[out]       outputBufferPtr         output data buffer pointer.
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferLenPtr      output data buffer result length pointer [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoBase64DecodeLen(
        const   char*       const   inputStrPtr,
        const   uint16_t            inputStrLen,
                uint8_t*    const   outputBufferPtr,
        const   uint32_t            outputBufferMaxSize,
                uint32_t*   const   outputBufferLenPtr);

/**
 * @}
 */

#endif
