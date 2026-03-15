
#ifndef TOMMROC_SW_KEY_H_
#define TOMMROC_SW_KEY_H_

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
#include "tommRoCSwErr.h"

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
 * Key format conversion from DER structure to PER string.
 *
 * param[in]        keyPtr                  key DER structure buffer pointer.
 * param[in]        keySize                 key DER structure buffer size [byte].
 * param[out]       outputBufferPtr         output key PER string buffer pointer.
 * param[in]        outputBufferMaxSize     output key PER string buffer max. size [byte].
 *
 * NOTE: output PER string is terminated with '\0'.
 *
 * return tommRoC_sw_err_enum_t
 */
tommRoC_sw_err_enum_t tommRoCSwKeyFormatDERToPEM(
        const   uint8_t*    const   keyPtr,
        const   uint16_t            keySize,
                char*       const   outputBufferPtr,
        const   uint16_t            outputBufferMaxSize);

/**
 * Key format conversion from PER string to DER structure.
 *
 * param[in]        keyStrPtr               key PER string buffer pointer ('\0' terminated).
 * param[out]       outputBufferPtr         output DER structure key buffer pointer.
 * param[in]        outputBufferMaxSize     output DER structure key buffer max. size [byte].
 * param[out]       outputBufferLenPtr      output DER structure key length pointer [byte].
 *
 * return tommRoC_sw_err_enum_t
 */
tommRoC_sw_err_enum_t tommRoCSwKeyFormatPEMToDER(
        const   char*       const   keyStrPtr,
                uint8_t*    const   outputBufferPtr,
        const   uint16_t            outputBufferMaxSize,
                uint16_t*   const   outputBufferLenPtr);

#endif
