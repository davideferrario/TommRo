
#ifndef TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_H_
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_H_

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
#include "tommRoCHwBus.h"
#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"

#include "devices/crypto/ATECCx08A/basic/tommRoCHwDevicesCryptoATECCx08ABasic.h"
#include "devices/crypto/ATECCx08A/cert/tommRoCHwDevicesCryptoATECCx08ACert.h"
#include "devices/crypto/ATECCx08A/helpers/tommRoCHwDevicesCryptoATECCx08AHelpers.h"
#include "devices/crypto/ATECCx08A/JWT/tommRoCHwDevicesCryptoATECCx08AJWT.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Compatible device I2C addresses.
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_TNGTLS_I2C_7_BIT_ADDRESS    (0b0110101) // ATECC608A-TNGTLS Trust&GO Device
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_TFLXTLS_I2C_7_BIT_ADDRESS   (0b0110110) // ATECC608A-TFLXTLS TrustFLEX Device
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_MAHDA_I2C_7_BIT_ADDRESS     (0b1100000) // ATECC608A-MAHDA TrustCUSTOM Device


// Device data.
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_DEVICE_DATA_SIZE    (48)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_DEVICE_DATA_SIZE    (52)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_DEVICE_DATA_SIZE    (88)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_DEVICE_DATA_SIZE    (88)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)
#define TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_DEVICE_DATA_SIZE    (88)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_CRYPTO_ATECCx08A_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_crypto_ateccx08a_device_data_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init bus device as for I2C master bus.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        i2c7BitSlaveAddress     I2C 7 bit slave address.
 * param[in]        busHandlerPtr           bus pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       specificSlavePtr        output specific I2C slave pointer [needed as static because linked by bus device].
 * param[out]       busDevicePtr            output bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCryptoATECCx08AInitI2C(
        const   uint8_t                                                     i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                                   const   busHandlerPtr,
        const   tommRoC_guard_t*                                    const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t*         const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCryptoATECCx08AAttachDeviceData(
        const   tommRoC_hw_devices_crypto_ateccx08a_device_data_t*  const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCryptoATECCx08AStart(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

#endif
