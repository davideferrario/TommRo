
#ifndef TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_BASIC_H_
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_BASIC_H_

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

// Serial number size
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_BASIC_SERIAL_NUMBER_SIZE_BYTE   (9)

// Keys size
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_BASIC_PUB_KEY_SIZE_BYTE         (64)    // Size of a p256 public key
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_BASIC_PRIV_KEY_SIZE_BYTE        (32)    // Size of a p256 private key
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_BASIC_SIG_SIZE_BYTE             (64)    // Size of a p256 signature
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_BASIC_KEY_SIZE_BYTE             (32)    // Size of a symmetric SHA key
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_BASIC_RSA2048_KEY_SIZE_BYTE     (256)   // Size of a RSA private key

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Read device serial number.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       serialNumberPtr         serial number buffer pointer (must be at least TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_BASIC_SERIAL_NUMBER_SIZE_BYTE).
 * param[in]        serialNumberMaxSize     serial number buffer max. size [byte].
 * param[out]       serialNumberLenPtr      output serial number length pointer [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCryptoATECCx08ABasicReadSerialNumber(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
                uint8_t*                    const   serialNumberPtr,
        const   uint16_t                            serialNumberMaxSize,
                uint16_t*                   const   serialNumberLenPtr);

/**
 * Calculate (generate) the public key from an existing private key in a slot.
 * NOTE: keys are exported as uint8_t data buffer (big endian). Format will be the 32 byte X and Y big-endian integers concatenated.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        slotKeyId               slot number of the private key.
 * param[out]       publicKeyPtr            public key buffer pointer (must be at least TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_BASIC_PUB_KEY_SIZE_BYTE byte size for P256 curve - NULL if public key is not required).
 * param[in]        publicKeyMaxSize        public key buffer max. size [byte].
 * param[out]       publicKeyLenPtr         output public key length pointer [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCryptoATECCx08ABasicGetPubkey(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   uint16_t                            slotKeyId,
                uint8_t*                    const   publicKeyPtr,
        const   uint16_t                            publicKeyMaxSize,
                uint16_t*                   const   publicKeyLenPtr);

/**
 * Read an ECC P256 public key from a slot configured for clear reads.
 * NOTE: keys are exported as uint8_t data buffer (big endian). Format will be the 32 byte X and Y big-endian integers concatenated.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        slotKeyId               slot number of the private key (only slots 8 to 15 are large enough for a public key).
 * param[out]       publicKeyPtr            public key buffer pointer (must be at least TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_BASIC_PUB_KEY_SIZE_BYTE byte size for P256 curve).
 * param[in]        publicKeyMaxSize        public key buffer max. size [byte].
 * param[out]       publicKeyLenPtr         output public key length pointer [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCryptoATECCx08ABasicReadPubkey(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   uint16_t                            slotKeyId,
                uint8_t*                    const   publicKeyPtr,
        const   uint16_t                            publicKeyMaxSize,
                uint16_t*                   const   publicKeyLenPtr);

#endif
