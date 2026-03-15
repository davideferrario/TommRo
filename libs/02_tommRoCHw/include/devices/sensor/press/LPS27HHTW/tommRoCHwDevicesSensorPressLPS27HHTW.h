
#ifndef TOMMROC_HW_DEVICES_SENSOR_PRESS_LPS27HHTW_H_
#define TOMMROC_HW_DEVICES_SENSOR_PRESS_LPS27HHTW_H_

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

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Compatible device I2C addresses.
#define TOMMROC_HW_DEVICES_SENSOR_PRESS_LPS27HHTW_I2C_7_BIT_ADDRESS_SA0_PIN_GND (0b1011100)
#define TOMMROC_HW_DEVICES_SENSOR_PRESS_LPS27HHTW_I2C_7_BIT_ADDRESS_SA0_PIN_VDD (0b1011101)


// Device data.
#define TOMMROC_HW_DEVICES_SENSOR_PRESS_LPS27HHTW_DEVICE_DATA_SIZE  (TOMMROC_UTIL_BOOL_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Output data rate selection
typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_PRESS_LPS27HHTW_ODR_NOT_USED = 0, // Power-down/One shot mode
    TOMMROC_HW_DEVICES_SENSOR_PRESS_LPS27HHTW_ODR_1_HZ,         // ODR = 1Hz
    TOMMROC_HW_DEVICES_SENSOR_PRESS_LPS27HHTW_ODR_10_HZ,        // ODR = 10Hz
    TOMMROC_HW_DEVICES_SENSOR_PRESS_LPS27HHTW_ODR_25_HZ,        // ODR = 25Hz
    TOMMROC_HW_DEVICES_SENSOR_PRESS_LPS27HHTW_ODR_50_HZ,        // ODR = 50Hz
    TOMMROC_HW_DEVICES_SENSOR_PRESS_LPS27HHTW_ODR_75_HZ,        // ODR = 75Hz
    TOMMROC_HW_DEVICES_SENSOR_PRESS_LPS27HHTW_ODR_100_HZ,       // ODR = 100Hz
    TOMMROC_HW_DEVICES_SENSOR_PRESS_LPS27HHTW_ODR_200_HZ,       // ODR = 200Hz

} tommRoC_hw_devices_sensor_press_lps27hhtw_odr_enum_t;


// Configuration structure.
typedef struct {

    tommRoC_hw_mems_def_conversion_mode_enum_t              conversionMode; // Conversion mode.
    tommRoC_hw_devices_sensor_press_lps27hhtw_odr_enum_t    ODR;            // ODR

} tommRoC_hw_devices_sensor_press_lps27hhtw_config_t;

#define __EMPTY_tommRoC_hw_devices_sensor_press_lps27hhtw_config_t__                \
{                                                                                   \
    /* .conversionMode */   TOMMRO_C_HW_DEVICES_DEF_CONVERSION_MODE_ON_DEMAND,      \
    /* .ODR */              TOMMROC_HW_DEVICES_SENSOR_PRESS_LPS27HHTW_ODR_NOT_USED, \
}


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_SENSOR_PRESS_LPS27HHTW_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_sensor_press_lps27hhtw_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorPressLPS27HHTWInitI2C(
        const   uint8_t                                                             i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                                           const   busHandlerPtr,
        const   tommRoC_guard_t*                                            const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t*                 const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

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
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorPressLPS27HHTWInitSPI(
        const   tommRoC_hw_gpio_set_cb_t                                            chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                                            chipDeSelect,
        const   tommRoC_hw_bus_t*                                           const   busHandlerPtr,
        const   tommRoC_guard_t*                                            const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t*                 const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorPressLPS27HHTWAttachDeviceData(
        const   tommRoC_hw_devices_sensor_press_lps27hhtw_device_data_t*    const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        configPtr               chip configuration pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorPressLPS27HHTWStart(
        const   tommRoC_hw_devices_sensor_press_lps27hhtw_config_t*         const   configPtr,
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Get pressure.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       pressurePtr             output pressure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorPressLPS27HHTWGetP(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                tommRoC_unit_measure_pressure_pa_t*                         const   pressurePtr);

/**
 * Get temperature.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       temperaturePtr          output temperature pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorPressLPS27HHTWGetT(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                tommRoC_unit_measure_temperature_celsius_t*                 const   temperaturePtr);

/**
 * Get pressure/temperature.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       pressurePtr             output pressure pointer.
 * param[out]       temperaturePtr          output temperature pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorPressLPS27HHTWGet(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                tommRoC_unit_measure_pressure_pa_t*                         const   pressurePtr,
                tommRoC_unit_measure_temperature_celsius_t*                 const   temperaturePtr);

#endif
