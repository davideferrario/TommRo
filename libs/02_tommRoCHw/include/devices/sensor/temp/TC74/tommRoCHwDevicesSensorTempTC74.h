
#ifndef TOMMROC_HW_DEVICES_SENSOR_TEMP_TC74_H_
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_TC74_H_

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
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_TC74_I2C_7_BIT_ADDRESS_A0    (0b1001000)
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_TC74_I2C_7_BIT_ADDRESS_A1    (0b1001001)
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_TC74_I2C_7_BIT_ADDRESS_A2    (0b1001010)
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_TC74_I2C_7_BIT_ADDRESS_A3    (0b1001011)
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_TC74_I2C_7_BIT_ADDRESS_A4    (0b1001100)
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_TC74_I2C_7_BIT_ADDRESS_A5    (0b1001101)
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_TC74_I2C_7_BIT_ADDRESS_A6    (0b1001110)
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_TC74_I2C_7_BIT_ADDRESS_A7    (0b1001111)

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
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempTC74InitI2C(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempTC74Start(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Get temperature.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       valuePtr                output temperature pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempTC74GetT(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr,
                tommRoC_unit_measure_temperature_celsius_t* const   valuePtr);

/**
 * Sleep (stand-by)/wake (normal) chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempTC74Sleep(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempTC74Wake(
        const   tommRoC_hw_bus_device_t*                    const   busDevicePtr);

#endif
