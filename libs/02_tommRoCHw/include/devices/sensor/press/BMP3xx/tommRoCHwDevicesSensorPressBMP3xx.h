
#ifndef TOMMROC_HW_DEVICES_SENSOR_PRESS_BMP3xx_H_
#define TOMMROC_HW_DEVICES_SENSOR_PRESS_BMP3xx_H_

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

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Compatible device I2C addresses.
#define TOMMROC_HW_DEVICES_SENSOR_PRESS_BMP3xx_I2C_7_BIT_ADDRESS_SDO_GND    (0b1110110)
#define TOMMROC_HW_DEVICES_SENSOR_PRESS_BMP3xx_I2C_7_BIT_ADDRESS_SDO_VDD    (0b1110111)


// Device data.
#if defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_8_BIT_SIZE)
#define TOMMROC_HW_DEVICES_SENSOR_PRESS_BMP3xx_STRUCT_BMP3_DEV_DATA_SIZE    ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMROC_HW_DEVICES_SENSOR_PRESS_BMP3xx_STRUCT_BMP3_DEV_DATA_SIZE    ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE)
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#define TOMMROC_HW_DEVICES_SENSOR_PRESS_BMP3xx_STRUCT_BMP3_DEV_DATA_SIZE    (176)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#define TOMMROC_HW_DEVICES_SENSOR_PRESS_BMP3xx_STRUCT_BMP3_DEV_DATA_SIZE    (184)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)
#define TOMMROC_HW_DEVICES_SENSOR_PRESS_BMP3xx_STRUCT_BMP3_DEV_DATA_SIZE    ()
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)
#define TOMMROC_HW_DEVICES_SENSOR_PRESS_BMP3xx_STRUCT_BMP3_DEV_DATA_SIZE    ()
#endif
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMROC_HW_DEVICES_SENSOR_PRESS_BMP3xx_STRUCT_BMP3_DEV_DATA_SIZE    (200)
#endif

#define TOMMROC_HW_DEVICES_SENSOR_PRESS_BMP3xx_DEVICE_DATA_SIZE (TOMMROC_HW_DEVICES_SENSOR_PRESS_BMP3xx_STRUCT_BMP3_DEV_DATA_SIZE)


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_SENSOR_PRESS_BMP3xx_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_sensor_press_bmp3xx_device_data_t;

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Sensor error status
typedef struct {

    tommRoC_util_enabled_status_enum_t fatalError;
    tommRoC_util_enabled_status_enum_t commandError;
    tommRoC_util_enabled_status_enum_t configurationError;

} tommRoC_hw_devices_sensor_press_bmp3xx_error_status_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorPressBMP3xxInitI2C(
        const   uint8_t                                                         i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                                       const   busHandlerPtr,
        const   tommRoC_guard_t*                                        const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t*             const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

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
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorPressBMP3xxInitSPI(
        const   tommRoC_hw_gpio_set_cb_t                                        chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                                        chipDeSelect,
        const   tommRoC_hw_bus_t*                                       const   busHandlerPtr,
        const   tommRoC_guard_t*                                        const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t*             const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorPressBMP3xxAttachDeviceData(
        const   tommRoC_hw_devices_sensor_press_bmp3xx_device_data_t*   const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorPressBMP3xxStart(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Get pressure.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       pressurePtr             output pressure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorPressBMP3xxGetP(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                tommRoC_unit_measure_pressure_pa_t*                     const   pressurePtr);

/**
 * Get temperature.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       temperaturePtr          output temperature pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorPressBMP3xxGetT(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                tommRoC_unit_measure_temperature_celsius_t*             const   temperaturePtr);

/**
 * Get both pressure/temperature.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       pressurePtr             output pressure pointer.
 * param[out]       temperaturePtr          output temperature pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorPressBMP3xxGetPT(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                tommRoC_unit_measure_pressure_pa_t*                     const   pressurePtr,
                tommRoC_unit_measure_temperature_celsius_t*             const   temperaturePtr);

/**
 * Get error status.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       errorStatusPtr          error status pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorPressBMP3xxGetErrorStatus(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                tommRoC_hw_devices_sensor_press_bmp3xx_error_status_t*  const   errorStatusPtr);

/**
 * Enable interrupt INT.
 * NOTE: just used for DMG BBX test.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorPressBMP3xxINT(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

#endif
