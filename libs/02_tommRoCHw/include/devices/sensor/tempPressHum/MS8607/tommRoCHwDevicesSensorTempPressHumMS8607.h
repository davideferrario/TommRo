
#ifndef TOMMROC_HW_DEVICES_SENSOR_TEMP_PRESS_HUM_MS8607_H_
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_PRESS_HUM_MS8607_H_

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

/**
 * NOTE:
 * Two distinct I2C addresses are used (one for pressure and temperature, the other for relative humidity).
 * Use pressure/temperature for init function. The correct address will be used in library.
 */

// Compatible device I2C addresses.
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_PRESS_HUM_MS8607_TP_I2C_7_BIT_ADDRESS    (0b1110110)
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_PRESS_HUM_MS8607_RH_I2C_7_BIT_ADDRESS    (0b1000000)


// Device data.
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_PRESS_HUM_MS8607_DEVICE_DATA_SIZE    (   TOMMROC_UTIL_U16_SIZE   +   \
                                                                                TOMMROC_UTIL_U16_SIZE   +   \
                                                                                TOMMROC_UTIL_U16_SIZE   +   \
                                                                                TOMMROC_UTIL_U16_SIZE   +   \
                                                                                TOMMROC_UTIL_U16_SIZE   +   \
                                                                                TOMMROC_UTIL_U16_SIZE       )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_TEMP_PRESS_HUM_MS8607_OSR_256 = 0,    // Low resolution/faster mode.
    TOMMROC_HW_DEVICES_SENSOR_TEMP_PRESS_HUM_MS8607_OSR_512,
    TOMMROC_HW_DEVICES_SENSOR_TEMP_PRESS_HUM_MS8607_OSR_1024,
    TOMMROC_HW_DEVICES_SENSOR_TEMP_PRESS_HUM_MS8607_OSR_2048,
    TOMMROC_HW_DEVICES_SENSOR_TEMP_PRESS_HUM_MS8607_OSR_4096,
    TOMMROC_HW_DEVICES_SENSOR_TEMP_PRESS_HUM_MS8607_OSR_8192,       // Top resolution/slowest mode.

} tommRoC_hw_devices_sensor_temp_press_hum_ms8607_osr_mode_enum_t;


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_SENSOR_TEMP_PRESS_HUM_MS8607_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_sensor_temp_press_hum_ms8607_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempPressHumMS8607InitI2C(
        const   uint8_t                                                                 i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                                               const   busHandlerPtr,
        const   tommRoC_guard_t*                                                const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t*                     const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempPressHumMS8607AttachDeviceData(
        const   tommRoC_hw_devices_sensor_temp_press_hum_ms8607_device_data_t*  const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempPressHumMS8607Start(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Get pressure/temperature.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        osrMode                 read OSR resolution mode.
 * param[out]       pressurePtr             output pressure pointer.
 * param[out]       temperaturePtr          output temperature pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempPressHumMS8607GetTP(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   tommRoC_hw_devices_sensor_temp_press_hum_ms8607_osr_mode_enum_t         osrMode,
                tommRoC_unit_measure_pressure_bar_t*                            const   pressurePtr,
                tommRoC_unit_measure_temperature_celsius_t*                     const   temperaturePtr);

/**
 * Get relative humidity.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       humidityRelativePtr     output relative humidity pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempPressHumMS8607GetRH(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
                tommRoC_unit_measure_humidity_relative_t*                       const   humidityRelativePtr);

#endif
