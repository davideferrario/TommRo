
#ifndef TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_JWT_H_
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_JWT_H_

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

#if defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_8_BIT_SIZE)
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_JWT_SIZE    ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_JWT_SIZE    ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE)
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_JWT_SIZE    (8)
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_JWT_SIZE    (16)
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_JWT_SIZE];
} tommRoC_hw_devices_crypto_ateccx08a_jwt_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Initialize a JWT structure.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        jwtPtr                  JWT structure pointer.
 * param[out]       bufferPtr               buffer to store the token pointer.
 * param[in]        bufferSize              buffer to store the token size [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCryptoATECCx08AJWTInit(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr,
                tommRoC_hw_devices_crypto_ateccx08a_jwt_t*  const   jwtPtr,
                void*                                       const   bufferPtr,
        const   uint16_t                                            bufferSize);

/**
 * Add a string claim to a JWT structure.
 * NOTE: function does not escape strings so the user has to ensure they are valid for use in a JSON string.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        jwtPtr                  JWT structure pointer.
 * param[out]       claimStrPtr             name of the claim string to be inserted pointer.
 * param[in]        valueStrPtr             value string to be inserted pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCryptoATECCx08AJWTAddClaimString(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr,
                tommRoC_hw_devices_crypto_ateccx08a_jwt_t*  const   jwtPtr,
        const   char*                                       const   claimStrPtr,
        const   char*                                       const   valueStrPtr);

/**
 * Add a numeric claim to a JWT structure.
 * NOTE: function does not escape strings so the user has to ensure they are valid for use in a JSON string.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        jwtPtr                  JWT structure pointer.
 * param[out]       claimStrPtr             name of the claim string to be inserted pointer.
 * param[in]        valueStrPtr             integer value to be inserted.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCryptoATECCx08AJWTAddClaimNumeric(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr,
                tommRoC_hw_devices_crypto_ateccx08a_jwt_t*  const   jwtPtr,
        const   char*                                       const   claimStrPtr,
        const   int32_t                                             value);

/**
 * Close the claims of a JWT structure, encode them and sign the result.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        jwtPtr                  JWT structure pointer.
 * param[out]       slotKeyId               slot number of the key used to sign.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCryptoATECCx08AJWTFinalize(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr,
                tommRoC_hw_devices_crypto_ateccx08a_jwt_t*  const   jwtPtr,
        const   uint16_t                                            slotKeyId);

/**
 * Check the JWT structure to see what character needs to be added in order to append a claim
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        jwtPtr                  JWT structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCryptoATECCx08AJWTCheckPayloadStart(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr,
                tommRoC_hw_devices_crypto_ateccx08a_jwt_t*  const   jwtPtr);

/**
 * Verifies the signature of a JWT structure using public key.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        bufferPtr               buffer holding encoded JWT pointer.
 * param[in]        bufferSize              buffer holding encoded JWT size [byte].
 * param[in]        publicKeyPtr            public key (raw byte format) pointer.
 * param[in]        publicKeySize           public key (raw byte format) size [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCryptoATECCx08AJWTVerify(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr,
        const   void*                                       const   bufferPtr,
        const   uint16_t                                            bufferSize,
        const   uint8_t*                                    const   publicKeyPtr,
        const   uint16_t                                            publicKeySize);

#endif
