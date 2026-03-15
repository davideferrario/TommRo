
#ifndef TOMMROC_CRYPTO_CCTALK_H_
#define TOMMROC_CRYPTO_CCTALK_H_

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
 * @defgroup tommRoCCryptoCCTalk tommRoCCryptoCCTalk
 *
 * @brief  TommRoC library crypto ccTalk module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted crypto ccTalk functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCUnitMeasure.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// Crypto CCTalk key size [bit].
#define TOMMRO_C_CRYPTO_CCTALK_KEY_SIZE_BIT             (48)

// Crypto CCTalk key size [byte].
#define TOMMRO_C_CRYPTO_CCTALK_KEY_SIZE_BYTE            (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(TOMMRO_C_CRYPTO_CCTALK_KEY_SIZE_BIT))

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * CCTalk data encryption.
 * NOTE: CCTalk key length have to be TOMMRO_C_CRYPTO_CCTALK_KEY_SIZE_BYTE (6 bytes).
 *
 * param[in]        keyPtr                  CCTalk key. Have to be an array of size TOMMRO_C_CRYPTO_CCTALK_KEY_SIZE_BYTE (6 bytes).
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer length [byte].
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoCCTalkEncrypt(
        const   uint8_t*    const   keyPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
        const   uint16_t            outputBufferMaxSize,
                uint8_t*    const   outputBufferPtr);

/**
 * CCTalk data decryption.
 * NOTE: CCTalk key length have to be TOMMRO_C_CRYPTO_CCTALK_KEY_SIZE_BYTE (6 bytes).
 *
 * param[in]        keyPtr                  CCTalk key. Have to be an array of size TOMMRO_C_CRYPTO_CCTALK_KEY_SIZE_BYTE (6 bytes).
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer length [byte].
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoCCTalkDecrypt(
        const   uint8_t*    const   keyPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
        const   uint16_t            outputBufferMaxSize,
                uint8_t*    const   outputBufferPtr);

/**
 * @}
 */

#endif
