
#ifndef TOMMROC_HW_DEVICES_CAP_TOUCH_CY8CMBR3xxx_H_
#define TOMMROC_HW_DEVICES_CAP_TOUCH_CY8CMBR3xxx_H_

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

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Compatible device I2C addresses.
#define TOMMROC_HW_DEVICES_CAP_TOUCH_CY8CMBR3xxx_I2C_7_BIT_ADDRESS  (0b0110111)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Button status indicators
typedef struct {

    /**
     * From datasheet:
     *
     * Button status indicator (touched/not touched) for Sensor x.
     * When Sensor x is configured as a button sensor, BASE_THRESHOLD0 is used to determine status.
     * When Sensor x is configured as a proximity sensor, PROX_TOUCH_TH0 is applied to determine status.
     *
     * TOMMRO_C_UTIL_DISABLED   -> Sensor x is inactive (not touched).
     * TOMMRO_C_UTIL_ENABLED    -> Sensor x is active (touched).
     */
    tommRoC_util_enabled_status_enum_t sensorStatus[TOMMROC_UNIT_MEASURE_BYTE_TO_BIT(TOMMROC_UTIL_U16_SIZE)];

} tommRoC_hw_devices_cap_touch_cy8cmbr3xxx_button_stat_t;

#define __EMPTY_tommRoC_hw_devices_cap_touch_cy8cmbr3xxx_button_stat_t_sensorStatus_field__ {                           \
                                                                                                TOMMRO_C_UTIL_DISABLED, \
                                                                                                TOMMRO_C_UTIL_DISABLED, \
                                                                                                TOMMRO_C_UTIL_DISABLED, \
                                                                                                TOMMRO_C_UTIL_DISABLED, \
                                                                                                TOMMRO_C_UTIL_DISABLED, \
                                                                                                TOMMRO_C_UTIL_DISABLED, \
                                                                                                TOMMRO_C_UTIL_DISABLED, \
                                                                                                TOMMRO_C_UTIL_DISABLED, \
                                                                                                TOMMRO_C_UTIL_DISABLED, \
                                                                                                TOMMRO_C_UTIL_DISABLED, \
                                                                                                TOMMRO_C_UTIL_DISABLED, \
                                                                                                TOMMRO_C_UTIL_DISABLED, \
                                                                                                TOMMRO_C_UTIL_DISABLED, \
                                                                                                TOMMRO_C_UTIL_DISABLED, \
                                                                                                TOMMRO_C_UTIL_DISABLED, \
                                                                                                TOMMRO_C_UTIL_DISABLED, \
                                                                                            }
#define __EMPTY_tommRoC_hw_devices_cap_touch_cy8cmbr3xxx_button_stat_t__                                        \
{                                                                                                               \
    /* .sensorStatus */ __EMPTY_tommRoC_hw_devices_cap_touch_cy8cmbr3xxx_button_stat_t_sensorStatus_field__,    \
}

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCapTouchCY8CMBR3xxxInitI2C(
        const   uint8_t                                                         i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                                       const   busHandlerPtr,
        const   tommRoC_guard_t*                                        const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t*             const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        configDataPtr           register configuration buffer pointer (NULL if none).
 * param[in]        configDataSize          register configuration buffer size (0 if none).
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCapTouchCY8CMBR3xxxStart(
        const   uint8_t*                                                const   configDataPtr,
        const   uint8_t                                                         configDataSize,
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Get button status indicators.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        buttonStatPtr           button status indicators pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCapTouchCY8CMBR3xxxGetStat(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                tommRoC_hw_devices_cap_touch_cy8cmbr3xxx_button_stat_t* const   buttonStatPtr);

/**
 * Get latched button status indicators.
 * NOTE: after read, LATCHED_BUTTON_STAT is cleared.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        latchedButtonStatPtr    latched button status indicators pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCapTouchCY8CMBR3xxxGetLatchedStat(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                tommRoC_hw_devices_cap_touch_cy8cmbr3xxx_button_stat_t* const   latchedButtonStatPtr);

/**
 * Sleep/wake chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCapTouchCY8CMBR3xxxSleep(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCapTouchCY8CMBR3xxxWake(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

#endif
