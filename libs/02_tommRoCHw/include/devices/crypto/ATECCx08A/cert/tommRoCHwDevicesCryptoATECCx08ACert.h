
#ifndef TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_CERT_H_
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_CERT_H_

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

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef enum {

    TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_CERT_SIGNER_TYPE = 0,
    TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_CERT_DEVICE_TYPE,

} tommRoC_hw_devices_crypto_ateccx08a_cert_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Read signer/device certificate from the ATECCx08A device.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        certType                certificate type (signer or device).
 * param[out]       certPtr                 certificate buffer pointer (must be at least TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_PUB_KEY_SIZE_BYTE byte size for P256 curve).
 * param[in]        certMaxSize             certificate buffer max. size [byte].
 * param[out]       certLenPtr              output certificate length pointer [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCryptoATECCx08ACertRead(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   tommRoC_hw_devices_crypto_ateccx08a_cert_enum_t             certType,
                uint8_t*                                            const   certPtr,
        const   uint16_t                                                    certMaxSize,
                uint16_t*                                           const   certLenPtr);

#endif
