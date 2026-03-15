
#ifndef TOMMROC_HW_DEVICES_SENSOR_SHT3xDIS_H_
#define TOMMROC_HW_DEVICES_SENSOR_SHT3xDIS_H_

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
#define TOMMROC_HW_DEVICES_SENSOR_SHT3xDIS_I2C_7_BIT_ADDRESS_ADDR_PIN_GND   (0b1000100)
#define TOMMROC_HW_DEVICES_SENSOR_SHT3xDIS_I2C_7_BIT_ADDRESS_ADDR_PIN_VDD   (0b1000101)


// Device data.
#define TOMMROC_HW_DEVICES_SENSOR_SHT3xDIS_DEVICE_DATA_SIZE (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                TOMMROC_UTIL_FUNCT_PTR_SIZE     )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_SENSOR_SHT3xDIS_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_sensor_sht3xdis_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorSHT3xDISInitI2C(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorSHT3xDISAttachDeviceData(
        const   tommRoC_hw_devices_sensor_sht3xdis_device_data_t*   const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        nRESETLow               set nRESET pin low function pointer (NULL if none).
 * param[in]        nRESETHigh              set nRESET pin high function pointer (NULL if none).
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorSHT3xDISStart(
        const   tommRoC_hw_gpio_set_cb_t                                    nRESETLow,
        const   tommRoC_hw_gpio_set_cb_t                                    nRESETHigh,
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Get temperature/humidity.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       temperaturePtr          output temperature pointer.
 * param[out]       humidityPtr             output humidity pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorSHT3xDISGet(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                tommRoC_unit_measure_temperature_celsius_t*         const   temperaturePtr,
                tommRoC_unit_measure_humidity_relative_x_100_t*     const   humidityPtr);

#endif
