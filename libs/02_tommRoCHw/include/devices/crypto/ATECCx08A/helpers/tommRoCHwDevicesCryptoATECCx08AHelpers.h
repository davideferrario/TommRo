
#ifndef TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_HELPERS_H_
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_HELPERS_H_

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
#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"

#include "TOMMROC.h"

#include <stdbool.h>

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
 * Converts a binary buffer to a hex string suitable for easy reading.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        inputBinBufferPtr       binary data buffer pointer.
 * param[in]        inputBinBufferSize      binary data buffer size [byte].
 * param[out]       outputHexBufferStrPtr   output hex string buffer pointer.
 * param[in]        outputHexBufferSize     output hex string buffer max size [byte].
 * param[out]       outputHexBufferLenPtr   output hex string buffer len [byte] pointer.
 * param[in]        isPretty                new lines should be added for pretty printing.
 * param[in]        isSpace                 convert the output hex with space between it.
 * param[in]        isUpper                 convert the output hex to upper case.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCryptoATECCx08AHelpersBinToHex(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   uint8_t*                    const   inputBinBufferPtr,
        const   uint32_t                            inputBinBufferSize,
                char*                       const   outputHexBufferStrPtr,
        const   uint32_t                            outputHexBufferSize,
                uint32_t*                   const   outputHexBufferLenPtr,
        const   bool                                isPretty,
        const   bool                                isSpace,
        const   bool                                isUpper);

/**
 * Converts a hex string suitable for easy reading to a binary buffer.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        inputHexBufferStrPtr    hex string buffer pointer.
 * param[in]        inputHexBufferSize      hex string buffer size [byte].
 * param[out]       outputBinBufferPtr      output binary buffer pointer.
 * param[in]        outputBinBufferSize     output binary buffer max size [byte].
 * param[out]       outputBinBufferLenPtr   output binary buffer len [byte] pointer.
 * param[in]        isSpace                 convert the output hex with space between it.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCryptoATECCx08AHelpersHexToBin(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   char*                       const   inputHexBufferStrPtr,
        const   uint32_t                            inputHexBufferSize,
                uint8_t*                    const   outputBinBufferPtr,
        const   uint32_t                            outputBinBufferSize,
                uint32_t*                   const   outputBinBufferLenPtr,
        const   bool                                isSpace);

#endif
