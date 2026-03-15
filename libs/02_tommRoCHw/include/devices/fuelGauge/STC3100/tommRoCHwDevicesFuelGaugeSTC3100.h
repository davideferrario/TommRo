
#ifndef TOMMROC_HW_DEVICES_FUEL_GAUGE_STC3100_H_
#define TOMMROC_HW_DEVICES_FUEL_GAUGE_STC3100_H_

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
#define TOMMROC_HW_DEVICES_FUEL_GAUGE_STC3100_I2C_7_BIT_ADDRESS (0b1110000)


// Device data.
#define TOMMROC_HW_DEVICES_FUEL_GAUGE_STC3100_DEVICE_DATA_SIZE  (sizeof(tommRoC_unit_measure_resistance_ohm_t))

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Configuration structure.
typedef struct {

    /**
     * Sense resistor value.
     *
     * NOTE:
     * The voltage drop across the external sense resistor is integrated during a conversion period and input to a 12- to 14-bit AD converter.
     * Default value is 0.010 ohm.
     */
    tommRoC_unit_measure_resistance_ohm_t   RSense;

} tommRoC_hw_devices_fuel_gauge_stc3100_config_t;

#define __EMPTY_tommRoC_hw_devices_fuel_gauge_stc3100_config_t__                \
{                                                                               \
    /* .RSense */   ((tommRoC_unit_measure_resistance_ohm_t) (10.0f / 1000.0f)) \
}


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_FUEL_GAUGE_STC3100_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_fuel_gauge_stc3100_device_data_t;


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
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeSTC3100InitI2C(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeSTC3100AttachDeviceData(
        const   tommRoC_hw_devices_fuel_gauge_stc3100_device_data_t*    const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        configPtr               device configuration pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeSTC3100Start(
        const   tommRoC_hw_devices_fuel_gauge_stc3100_config_t*         const   configPtr,
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Get value.
 * NOTE: valid property:
 *
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_VOLTAGE
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_CURRENT
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TEMPERATURE_C
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_REMAINING_CAPACITY
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       valuePtr                value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeSTC3100GetValue(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_fuel_gauge_def_value_enum_t                          property,
                void*                                                   const   valuePtr);

#endif
