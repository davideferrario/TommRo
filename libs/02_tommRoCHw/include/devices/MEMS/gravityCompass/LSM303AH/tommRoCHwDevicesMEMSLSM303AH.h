
#ifndef TOMMROC_HW_DEVICES_MEMS_LSM303AH_H_
#define TOMMROC_HW_DEVICES_MEMS_LSM303AH_H_

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
#include "tommRoCHwGPIO.h"

#include "DEF/devices/tommRoCHwDEFDevices.h"
#include "DEF/MEMS/tommRoCHwDEFMEMS.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Compatible device I2C addresses.
#define TOMMROC_HW_DEVICES_MEMS_LSM303AH_GRAVITY_I2C_7_BIT_ADDRESS  (0b0011101)
#define TOMMROC_HW_DEVICES_MEMS_LSM303AH_COMPASS_I2C_7_BIT_ADDRESS  (0b0011110)


// Device data.
#define TOMMROC_HW_DEVICES_MEMS_LSM303AH_DEVICE_DATA_SIZE   (   TOMMROC_UTIL_U8_SIZE    +   \
                                                                TOMMROC_UTIL_U16_SIZE   +   \
                                                                TOMMROC_UTIL_BOOL_SIZE  +   \
                                                                TOMMROC_UTIL_U16_SIZE       )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Configuration structure - Gravity section.
typedef struct {

    tommRoC_hw_devices_def_operating_mode_enum_t    operatingMode;          // Operating mode.
    tommRoC_hw_def_mems_gravity_full_scale_enum_t   fullScale;              // Full scale.
    tommRoC_hw_mems_def_interrupt_mode_enum_t       interruptMode;          // Interrupt.
    tommRoC_util_bit_status_enum_t                  interruptPolarity;      // Interrupt active pin polarity.
                                                                            // TOMMRO_C_UTIL_HIGH_LEVEL (default)   -> the interrupt pins are active high (low to high on interrupt condition).
                                                                            // TOMMRO_C_UTIL_LOW_LEVEL              -> the interrupt pins are active low (high to low on interrupt condition).

    tommRoC_util_enabled_status_enum_t              highPassFilterStatus;   // Status of high pass filter.

    /**
     * From datasheet:
     *
     * When the activity/inactivity recognition function is activated, the LSM303AH device is able
     * to automatically enter low-power mode and decrease the accelerometer sampling rate to 12.5 Hz,
     * increasing back the accelerometer ODR and bandwidth as soon as the wake-up interrupt event has been detected.
     */
    tommRoC_util_enabled_status_enum_t              actvtyInactvtyStatus;   // Status of activity/inactivity recognition function.

} tommRoC_hw_devices_mems_lsm303ah_gravity_config_t;

#define __EMPTY_tommRoC_hw_devices_mems_lsm303ah_gravity_config_t__                 \
{                                                                                   \
    /* .operatingMode */        TOMMRO_C_HW_DEVICES_DEF_OPERATING_MODE_LOW_POWER,   \
    /* .fullScale */            TOMMRO_C_HW_DEF_MEMS_GRAVITY_FULL_SCALE_2G,         \
    /* .interruptMode */        TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_DISABLED,       \
    /* .interruptPolarity */    TOMMRO_C_UTIL_HIGH_LEVEL,                           \
    /* .highPassFilterStatus */ TOMMRO_C_UTIL_DISABLED,                             \
    /* .actvtyInactvtyStatus */ TOMMRO_C_UTIL_DISABLED,                             \
}


// Configuration structure - Compass section.
typedef struct {

    tommRoC_hw_devices_def_operating_mode_enum_t    operatingMode;          // Operating mode.
    tommRoC_hw_mems_def_conversion_mode_enum_t      conversionMode;         // Conversion mode.
    tommRoC_util_enabled_status_enum_t              offsetCancStatus;       // Status of offset cancellation.

} tommRoC_hw_devices_mems_lsm303ah_compass_config_t;

#define __EMPTY_tommRoC_hw_devices_mems_lsm303ah_compass_config_t__                 \
{                                                                                   \
    /* .operatingMode */        TOMMRO_C_HW_DEVICES_DEF_OPERATING_MODE_LOW_POWER,   \
    /* .conversionMode */       TOMMRO_C_HW_DEVICES_DEF_CONVERSION_MODE_ON_DEMAND,  \
    /* .offsetCancStatus */     TOMMRO_C_UTIL_DISABLED,                             \
}


// Configuration structure.
typedef struct {

    tommRoC_hw_devices_mems_lsm303ah_gravity_config_t   gravityConfig;
    tommRoC_hw_devices_mems_lsm303ah_compass_config_t   compassConfig;

} tommRoC_hw_devices_mems_lsm303ah_config_t;

#define __EMPTY_tommRoC_hw_devices_mems_lsm303ah_config_t__                                 \
{                                                                                           \
    /* .gravityConfig */    __EMPTY_tommRoC_hw_devices_mems_lsm303ah_gravity_config_t__,    \
    /* .compassConfig */    __EMPTY_tommRoC_hw_devices_mems_lsm303ah_compass_config_t__,    \
}


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_MEMS_LSM303AH_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_mems_lsm303ah_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesMEMSLSM303AHInitI2C(
        const   uint8_t                                                     i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                                   const   busHandlerPtr,
        const   tommRoC_guard_t*                                    const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t*         const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Init bus device as for SPI master bus.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        chipSelect              chip select function pointer.
 * param[in]        chipDeSelect            chip de-select function pointer.
 * param[in]        busHandlerPtr           bus pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       specificSlavePtr        output specific SPI slave pointer [needed as static because linked by bus device].
 * param[out]       busDevicePtr            output bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMEMSLSM303AHInitSPI(
        const   tommRoC_hw_gpio_set_cb_t                                    chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                                    chipDeSelect,
        const   tommRoC_hw_bus_t*                                   const   busHandlerPtr,
        const   tommRoC_guard_t*                                    const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t*         const   specificSlavePtr,
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
tommRoC_hw_err_enum_t tommRoCHwDevicesMEMSLSM303AHAttachDeviceData(
        const   tommRoC_hw_devices_mems_lsm303ah_device_data_t*     const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        configPtr               chip configuration pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMEMSLSM303AHStart(
        const   tommRoC_hw_devices_mems_lsm303ah_config_t*          const   configPtr,
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Get MEMS all results (gravity/compass) result as natural [float] format.
 * NOTE: compass unit measure is Gauss.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       gravityResultPtr        gravity result structure [g] pointer.
 * param[out]       compassResultPtr        compass result structure [G] pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMEMSLSM303AHGet(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                tommRoC_hw_mems_def_result_t*                       const   gravityResultPtr,
                tommRoC_hw_mems_def_result_t*                       const   compassResultPtr);

/**
 * Get MEMS acceleration result as natural [float] format.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       resultPtr               result structure [g] pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMEMSLSM303AHGravityGet(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                tommRoC_hw_mems_def_result_t*                       const   resultPtr);

/**
 * Get MEMS acceleration result as signed 16-bit format.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       resultPtr               result structure [mg] pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMEMSLSM303AHGravityGet16Bit(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                tommRoC_hw_mems_def_result_16bit_t*                 const   resultPtr);

/**
 * Get MEMS compass result as natural [float] format.
 * NOTE: unit measure is Gauss.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       resultPtr               result structure [G] pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesMEMSLSM303AHCompassGet(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                tommRoC_hw_mems_def_result_t*                       const   resultPtr);

#endif
