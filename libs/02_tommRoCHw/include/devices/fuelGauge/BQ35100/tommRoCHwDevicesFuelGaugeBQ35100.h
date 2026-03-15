
#ifndef TOMMROC_HW_DEVICES_FUEL_GAUGE_BQ35100_H_
#define TOMMROC_HW_DEVICES_FUEL_GAUGE_BQ35100_H_

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

#include "DEF/fuelGauge/tommRoCHwDEFFuelGauge.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Compatible device I2C addresses.
#define TOMMROC_HW_DEVICES_FUEL_GAUGE_BQ35100_I2C_7_BIT_ADDRESS     (0b1010101)

// Device data.
#define TOMMROC_HW_DEVICES_FUEL_GAUGE_BQ35100_DEVICE_DATA_SIZE      (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                        TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                        TOMMROC_UTIL_U32_SIZE       +   \
                                                                        TOMMROC_UTIL_U32_SIZE           )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef enum {

    /**
     * From datasheet:
     *
     * The ACCUMULATOR mode (ACC) is chemistry-independent and accumulates the passed discharge of the battery
     * when the gauge is enabled, but also provides no gas gauging data, such as remaining state-of-health (RSOC),
     * full charge capacity (FCC), or end-of-service (EOS) indication.
     * This is the default configuration as it is also the required mode for the device when it is calibrated.
     * Once calibration is completed, the device can be set to the appropriate gauging mode or left in the default mode.
     */
    TOMMROC_HW_DEVICES_FUEL_GAUGE_BQ35100_GAUGING_MODE_ACCUMULATOR = 0,

    /**
     * From datasheet:
     *
     * STATE-OF-HEALTH mode is typically used with lithium manganese dioxide (Li-MnO2) cells as the voltage state-of-health (SOH)
     * profile has a defined slope to enable accuracy
     */
    TOMMROC_HW_DEVICES_FUEL_GAUGE_BQ35100_GAUGING_MODE_STATE_OF_HEALTH,

    /**
     * From datasheet:
     *
     * END-OF-SERVICE mode is only used with lithium thionyl chloride (Li-SOCl2) cells.
     * For more details, including information on Operation Config A [GMSEL], R Data Seconds, see the BQ35100 Technical Reference Manual.
     */
    TOMMROC_HW_DEVICES_FUEL_GAUGE_BQ35100_GAUGING_MODE_END_OF_SERVICE,

} tommRoC_hw_devices_fuel_gauge_bq35100_gauging_mode_enum_t;


// Configuration structure.
typedef struct {

    tommRoC_hw_devices_fuel_gauge_bq35100_gauging_mode_enum_t   gaugingMode;    // Operating mode.

} tommRoC_hw_devices_fuel_gauge_bq35100_config_t;

#define __EMPTY_tommRoC_hw_devices_fuel_gauge_bq35100_config_t__                        \
{                                                                                       \
    /* .gaugingMode */  TOMMROC_HW_DEVICES_FUEL_GAUGE_BQ35100_GAUGING_MODE_ACCUMULATOR, \
}


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_FUEL_GAUGE_BQ35100_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_fuel_gauge_bq35100_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeBQ35100InitI2C(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeBQ35100AttachDeviceData(
        const   tommRoC_hw_devices_fuel_gauge_bq35100_device_data_t*    const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Start chip.
 * NOTE: if available - NOT NULL - GEHigh (fuel gauge enable) function is called in the end of function. Then the chip is left enabled.
 *
 * param[in]        configPtr               chip configuration pointer.
 * param[in]        GEPinLow                gauge enable pin set low function pointer (NULL if none).
 * param[in]        GEPinHigh               gauge enable pin set high function pointer (NULL if none).
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeBQ35100Start(
        const   tommRoC_hw_devices_fuel_gauge_bq35100_config_t*         const   configPtr,
        const   tommRoC_hw_gpio_set_cb_t                                        GEPinLow,
        const   tommRoC_hw_gpio_set_cb_t                                        GEPinHigh,
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Get readable value.
 * NOTE: valid property:
 *
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_ACCUMULATED_CAPACITY
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TEMPERATURE_K
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TEMPERATURE_C
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_VOLTAGE
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_CURRENT
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_INTERNAL_TEMPERATURE_K
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_INTERNAL_TEMPERATURE_C
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_STATE_OF_CHARGE
 * - TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_DESIGN_CAPACITY
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       valuePtr                value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeBQ35100GetValue(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_fuel_gauge_def_value_enum_t                          property,
                void*                                                   const   valuePtr);

/**
 * Enable/Disable chip.
 * NOTE: To disable, internal LDO is disconnected from REGIN when driven low.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeBQ35100Enable(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesFuelGaugeBQ35100Disable(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

#endif
