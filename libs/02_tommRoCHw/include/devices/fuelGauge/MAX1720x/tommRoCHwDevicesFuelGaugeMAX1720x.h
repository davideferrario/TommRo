
#ifndef TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1720x_H_
#define TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1720x_H_

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

#include <stdbool.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// Compatible device I2C addresses.
#define TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1720x_I2C_7_BIT_ADDRESS    (0b0110110)


// Device data.
#define TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1720x_DEVICE_DATA_SIZE     (   TOMMROC_UTIL_FLOAT_SIZE +   \
                                                                        TOMMROC_UTIL_U8_SIZE        )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of chip reset at startup.
typedef enum {

    /**
     * From datasheet:
     *
     * HARDWARE RESET
     * --------------
     * Send the hardware reset command to recall all nonvolatile memory
     * into shadow RAM and reset all hardware based operations of the IC.
     * This command should always be followed by the reset fuel gauge command
     * to fully reset operation of the IC.
     *
     *
     * FUEL GAUGE RESET
     * ----------------
     * The fuel gauge reset command resets operation of theICs without
     * restoring nonvolatile memory values into shadow RAM.
     * This command allows different configurations to be tested without
     * using one of the limited number of nonvolatile memory writes
     */


    /**
     * Perform no reset at chip startup.
     */
    TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1720x_NO_RESET = 0,

    /**
     * Perform only fuel gauge reset at chip startup.
     */
    TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1720x_FUEL_GAUGE_RESET,

    /**
     * Perform hardware reset followed by fuel gauge reset at chip startup.
     */
    TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1720x_FULL_RESET,

} tommRoC_hw_devices_fuel_gauge_max1720x_reset_type_enum_t;


typedef enum {

    /**
     * Active mode.
     */
    TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1720x_MODE_ACTIVE = 0,

    /**
     * Hibernate mode.
     */
    TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1720x_MODE_HIBERNATE,

} tommRoC_hw_devices_fuel_gauge_max1720x_mode_type_enum_t;


// Register raw value structure.
typedef struct {

    // Register address.
    uint16_t    add;

    // Register value.
    uint16_t    value;

} tommRoC_hw_devices_fuel_gauge_max1720x_register_raw_t;


// Configuration structure.
typedef struct {

    /**
     * Sense resistor value.
     * NOTE: internal current/capacity registers has voltage format.
     * RSense is used to divide voltage to determine amps or amp-hours.
     * Default value is 0.010 ohm.
     */
    tommRoC_unit_measure_resistance_ohm_t RSense;

    /**
     * Chip reset type
     */
    tommRoC_hw_devices_fuel_gauge_max1720x_reset_type_enum_t    resetType;

    /**
     * Active/Hibernate mode type
     */
    tommRoC_hw_devices_fuel_gauge_max1720x_mode_type_enum_t     modeType;

    /**
     * Init register at startup struct.
     * NOTE: setup to NULL and 0 if not needed.
     */
    tommRoC_hw_devices_fuel_gauge_max1720x_register_raw_t*      initRegPtr;
    uint8_t                                                     initRegAmount;

} tommRoC_hw_devices_fuel_gauge_max1720x_config_t;

#define __EMPTY_tommRoC_hw_devices_fuel_gauge_max1720x_config_t__               \
{                                                                               \
    /* .RSense */           0.010f,                                             \
    /* .resetType */        TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1720x_FULL_RESET,  \
    /* .modeType */         TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1720x_MODE_ACTIVE, \
    /* .initRegPtr */       NULL,                                               \
    /* .initRegAmount */    0,                                                  \
}


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_FUEL_GAUGE_MAX1720x_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_fuel_gauge_max1720x_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1720xInitI2C(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1720xAttachDeviceData(
        const   tommRoC_hw_devices_fuel_gauge_max1720x_device_data_t*   const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        configPtr               device configuration pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1720xStart(
        const   tommRoC_hw_devices_fuel_gauge_max1720x_config_t*        const   configPtr,
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Get if chip is MAX17205.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        isMAX17205Ptr           is MAX17205 pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1720xIsMAX17205(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                bool*                                                   const   isMAX17205Ptr);

/**
 * Get value.
 * NOTE: valid property:
 *
 * Common MAX17201/MAX17205 values
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_VOLTAGE
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_CURRENT
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TEMPERATURE_C
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_STATE_OF_CHARGE
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_REMAINING_CAPACITY
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TTE
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TTF
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_INTERNAL_RESISTANCE
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_COULOMB_COUNTER
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_REGISTER_RAW
 *
 * Specific MAX17205 values
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_VOLTAGE_CELL1
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_VOLTAGE_CELL2
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_VOLTAGE_CELL3
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_VOLTAGE_CELL4
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TEMPERATURE_1
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TEMPERATURE_2
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       valuePtr                value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1720xGetValue(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_fuel_gauge_def_value_enum_t                          property,
                void*                                                   const   valuePtr);

/**
 * Set value.
 * NOTE: valid property:
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_REGISTER_RAW
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[in]        valuePtr                value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1720xSetValue(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_fuel_gauge_def_value_enum_t                          property,
        const   void*                                                   const   valuePtr);

/**
 * Hibernate/Active chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1720xHibernate(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeMAX1720xActive(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

#endif
