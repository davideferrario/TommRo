
#ifndef TOMMROC_HW_DEVICES_SENSOR_TEMP_TMP007_H_
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_TMP007_H_

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
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_TMP007_I2C_7_BIT_ADDRESS_ADR1ADR0_PIN_GNDGND (0b1000000)
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_TMP007_I2C_7_BIT_ADDRESS_ADR1ADR0_PIN_GNDVDD (0b1000001)
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_TMP007_I2C_7_BIT_ADDRESS_ADR1ADR0_PIN_VDDGND (0b1000100)
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_TMP007_I2C_7_BIT_ADDRESS_ADR1ADR0_PIN_VDDVDD (0b1000101)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

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
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempTMP007InitI2C(
        const   uint8_t                                             i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                           const   busHandlerPtr,
        const   tommRoC_guard_t*                            const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t* const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempTMP007Start(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Get temperature DIE.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       valuePtr                output temperature pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempTMP007GetTDie(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr,
                tommRoC_unit_measure_temperature_celsius_t* const   valuePtr);

/**
 * Get temperature OBJ.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       valuePtr                output temperature pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempTMP007GetTObj(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr,
                tommRoC_unit_measure_temperature_celsius_t* const   valuePtr);

#endif
