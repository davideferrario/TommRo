
#ifndef TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1704x_H_
#define TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1704x_H_

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

#include "DEF/fuelGauge/tommRoCHwDEFFuelGauge.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Compatible device I2C addresses.
#define TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1704x_I2C_7_BIT_ADDRESS    (0b0110110)


// Device data.
#define TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1704x_DEVICE_DATA_SIZE     (TOMMROC_UTIL_U8_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Detected device type.
typedef enum {

    TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1704x_TYPE_MAX17043 = 0,
    TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1704x_TYPE_MAX17044,
    TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1704x_TYPE_MAX17048,
    TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1704x_TYPE_MAX17049,

} tommRoC_hw_devices_fuel_gauge_max1704x_type_enum_t;


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1704x_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_fuel_gauge_max1704x_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1704xInitI2C(
        const   uint8_t                                                         i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                                       const   busHandlerPtr,
        const   tommRoC_guard_t*                                        const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t*             const   specificSlavePtr,
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
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1704xAttachDeviceData(
        const   tommRoC_hw_devices_fuel_gauge_max1704x_device_data_t*   const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1704xStart(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Get detected device type.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       typePtr                 device type pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1704xGetDeviceType(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                tommRoC_hw_devices_fuel_gauge_max1704x_type_enum_t*     const   typePtr);

/**
 * Get readable value.
 * NOTE: valid property:
 *
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_VOLTAGE
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_STATE_OF_CHARGE
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TTE (valid only for MAX17048 and MAX17049 device. NOTE: device does not know if it is in charge/discharge. Application have to know)
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TTF (valid only for MAX17048 and MAX17049 device. NOTE: device does not know if it is in charge/discharge. Application have to know)
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       valuePtr                value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1704xGetValue(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_fuel_gauge_def_value_enum_t                          property,
                void*                                                   const   valuePtr);

/**
 * Sleep/wake chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1704xSleep(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1704xWake(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Enter/exit hibernate mode.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1704xHibernateEnter(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1704xHibernateExit(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

#endif
