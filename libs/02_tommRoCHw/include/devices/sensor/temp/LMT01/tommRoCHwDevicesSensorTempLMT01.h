
#ifndef TOMMROC_HW_DEVICES_SENSOR_TEMP_LMT01_H_
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_LMT01_H_

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

// Device data.
#define TOMMROC_HW_DEVICES_SENSOR_TEMP_LMT01_DEVICE_DATA_SIZE   (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE     )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// LMT01 temperature sensor base functionality callback functions type definition.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_sensor_temp_lmt01_power_ON_funct_t)(void);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_sensor_temp_lmt01_power_OFF_funct_t)(void);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_sensor_temp_lmt01_counter_enable_funct_t)(void);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_sensor_temp_lmt01_counter_disable_funct_t)(void);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_sensor_temp_lmt01_counter_get_funct_t)(uint32_t* const countPtr);


// LMT01 temperature sensor config callback functions.
typedef struct {

    tommRoC_hw_devices_sensor_temp_lmt01_power_ON_funct_t           powerON;
    tommRoC_hw_devices_sensor_temp_lmt01_power_OFF_funct_t          powerOFF;
    tommRoC_hw_devices_sensor_temp_lmt01_counter_enable_funct_t     counterEnable;
    tommRoC_hw_devices_sensor_temp_lmt01_counter_disable_funct_t    counterDisable;
    tommRoC_hw_devices_sensor_temp_lmt01_counter_get_funct_t        counterGet;

} tommRoC_hw_devices_sensor_temp_lmt01_config_t;

#define __EMPTY_tommRoC_hw_devices_sensor_temp_lmt01_config_t__ \
{                                                               \
    /* .powerON */          NULL,                               \
    /* .powerOFF */         NULL,                               \
    /* .counterEnable */    NULL,                               \
    /* .counterDisable */   NULL,                               \
    /* .counterGet */       NULL,                               \
}


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_SENSOR_TEMP_LMT01_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_sensor_temp_lmt01_device_data_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init bus device as for no bus.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       busDevicePtr            output bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempLMT01Init(
        const   tommRoC_guard_t*                                    const   guardPtr,
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
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempLMT01AttachDeviceData(
        const   tommRoC_hw_devices_sensor_temp_lmt01_device_data_t* const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        configPtr               device configuration pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempLMT01Start(
        const   tommRoC_hw_devices_sensor_temp_lmt01_config_t*      const   configPtr,
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Get temperature.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       valuePtr                output temperature pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorTempLMT01GetT(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                tommRoC_unit_measure_temperature_celsius_t*         const   valuePtr);

#endif
