
#ifndef TOMMROC_CODER_H_
#define TOMMROC_CODER_H_

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
 * @defgroup tommRoCCoder tommRoCCoder
 *
 * @brief  TommRoC library coder module
 * @author TommRo Software Department
 *
 * This module is providing encode/decode functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"

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

/**
 * BCD Encode.
 * NOTE: every input uint8_t data is encoded into a uint16_t value.
 *
 * param[in]        inputBufferPtr          input buffer data pointer [binary encoded].
 * param[in]        inputBufferLen          input buffer data len.
 * param[out]       outputBufferPtr         output buffer data pointer [BCD encoded].
 * param[in]        outputBufferMaxSize     output buffer data max size [byte].
 *
 * return tommRoC_err_enum_t
*/
tommRoC_err_enum_t tommRoCCoderBCDEncoderEncode(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint16_t*   const   outputBufferPtr,
        const   uint16_t            outputBufferMaxSize);

/**
 * BCD Decode.
 * NOTE: every input uint16_t data is decoded into a uint8_t value.
 *
 * param[in]        inputBufferPtr          input buffer data pointer [BCD encoded].
 * param[in]        inputBufferLen          input buffer data amount.
 * param[out]       outputBufferPtr         output buffer data pointer [binary encoded].
 * param[in]        outputBufferMaxSize     output buffer data max size [byte].
 *
 * return tommRoC_err_enum_t
*/
tommRoC_err_enum_t tommRoCCoderBCDEncoderDecode(
        const   uint16_t*   const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr,
        const   uint16_t            outputBufferMaxSize);

/**
 * BCD Encode (limited version).
 * NOTE: it is supposed that every input uint8_t data is between [0; 99], so that could be encoded into a uint8_t value.
 *
 * param[in]        inputBufferPtr          input buffer data pointer [binary encoded].
 * param[in]        inputBufferLen          input buffer data len.
 * param[out]       outputBufferPtr         output buffer data pointer [BCD encoded].
 * param[in]        outputBufferMaxSize     output buffer data max size [byte].
 *
 * return tommRoC_err_enum_t
*/
tommRoC_err_enum_t tommRoCCoderBCDEncoderLimitedEncode(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr,
        const   uint16_t            outputBufferMaxSize);

/**
 * BCD Decode (limited version).
 * NOTE: it is supposed that every output uint8_t data is between [0; 99], so that could be decoded into a uint8_t value.
 *
 * param[in]        inputBufferPtr          input buffer data pointer [BCD encoded].
 * param[in]        inputBufferLen          input buffer data amount.
 * param[out]       outputBufferPtr         output buffer data pointer [binary encoded].
 * param[in]        outputBufferMaxSize     output buffer data max size [byte].
 *
 * return tommRoC_err_enum_t
*/
tommRoC_err_enum_t tommRoCCoderBCDEncoderLimitedDecode(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr,
        const   uint16_t            outputBufferMaxSize);

/**
 * UU Encoder Encode.
 *
 * param[in]        inputBufferPtr          input buffer data pointer.
 * param[in]        inputBufferLen          input buffer data len.
 * param[out]       outputBufferPtr         output buffer data pointer.
 * param[in]        outputBufferMaxSize     output buffer data max size [byte].
 * param[out]       outputBufferLenPtr      output buffer data len pointer.
 *
 * return tommRoC_err_enum_t
*/
tommRoC_err_enum_t tommRoCCoderUUEncoderEncode(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr,
        const   uint16_t            outputBufferMaxSize,
                uint16_t*   const   outputBufferLenPtr);

/**
 * UU Encoder Decode.
 *
 * param[in]        inputBufferPtr          input buffer data pointer.
 * param[in]        inputBufferLen          input buffer data len.
 * param[out]       outputBufferPtr         output buffer data pointer.
 * param[in]        outputBufferMaxSize     output buffer data max size [byte].
 * param[out]       outputBufferLenPtr      output buffer data len pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCoderUUEncoderDecode(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr,
        const   uint16_t            outputBufferMaxSize,
                uint16_t*   const   outputBufferLenPtr);

/**
 * @}
 */

#endif
