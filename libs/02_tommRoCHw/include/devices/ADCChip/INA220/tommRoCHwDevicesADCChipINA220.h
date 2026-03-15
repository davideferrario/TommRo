
#ifndef TOMMROC_HW_DEVICES_ADC_CHIP_INA220_H_
#define TOMMROC_HW_DEVICES_ADC_CHIP_INA220_H_

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
#define TOMMROC_HW_DEVICES_ADC_CHIP_INA220_I2C_7_BIT_ADDRESS_A1A0_PIN_GNDGND    (0b1000000)
#define TOMMROC_HW_DEVICES_ADC_CHIP_INA220_I2C_7_BIT_ADDRESS_A1A0_PIN_GNDVDD    (0b1000001)
#define TOMMROC_HW_DEVICES_ADC_CHIP_INA220_I2C_7_BIT_ADDRESS_A1A0_PIN_VDDGND    (0b1000100)
#define TOMMROC_HW_DEVICES_ADC_CHIP_INA220_I2C_7_BIT_ADDRESS_A1A0_PIN_VDDVDD    (0b1000101)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of bus voltage range.
typedef enum {

    /**
     * 16V FSR.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_16V_FSR = 0,

    /**
     * 32V FSR (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_32V_FSR,

} tommRoC_hw_devices_adc_chip_ina220_bus_voltage_range_enum_t;


// Enumeration of PGA gain and range.
typedef enum {

    /**
     * Range = +/-40mV
     * Gain = 1
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_PGA_RANGE_40_mV = 0,

    /**
     * Range = +/-80mV
     * Gain = 1/2
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_PGA_RANGE_80_mV,

    /**
     * Range = +/-160mV
     * Gain = 1/4
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_PGA_RANGE_160_mV,

    /**
     * Range = +/-320mV (default)
     * Gain = 1/8
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_PGA_RANGE_320_mV,

} tommRoC_hw_devices_adc_chip_ina220_pga_range_enum_t;


// Enumeration of operating mode.
typedef enum {

    /**
     * Power down.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_MODE_POWER_DOWN = 0,

    /**
     * Shunt voltage, triggered.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_MODE_SHUNT_TRIGGERED,

    /**
     * Bus voltage, triggered.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_MODE_BUS_TRIGGERED,

    /**
     * Shunt and bus voltage, triggered.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_MODE_SHUNT_AND_BUS_TRIGGERED,

    /**
     * ADC off (disabled).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_MODE_ADC_OFF,

    /**
     * Shunt voltage, continuous.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_MODE_SHUNT_CONTINUOUS,

    /**
     * Bus voltage, continuous.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_MODE_BUS_CONTINUOUS,

    /**
     * Shunt and bus voltage, continuous (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_MODE_SHUNT_AND_BUS_CONTINUOUS,

} tommRoC_hw_devices_adc_chip_ina220_mode_enum_t;


// Enumeration of INA220 properties.
typedef enum {

    /**
     * Chip reset.
     *
     * Available:   set
     * Notes:       propValuePtr has to be bool*.
     *              Set *propValuePtr to TRUE, will reset chip; set to FALSE no operation is done.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_RESET_PROP = 0,

    /**
     * Bus voltage range.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ina220_bus_voltage_range_enum_t*.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_BUS_VOLTAGE_RANGE_PROP,

    /**
     * PGA gain and range.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ina220_pga_range_enum_t*.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_BUS_PGA_RANGE_PROP,

    /**
     * PGA gain and range.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ina220_mode_enum_t*.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_MODE_PROP,

} tommRoC_hw_devices_adc_chip_ina220_prop_enum_t;


// Enumeration of INA220 value types.
typedef enum {

    /**
     * Shunt voltage [mV].
     * Notes:       valuePtr has to be float*.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_SHUNT_VOLTAGE = 0,

    /**
     * Bus voltage [V].
     * Notes:       valuePtr has to be float*.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_BUS_VOLTAGE,

    /**
     * Power register.
     * Notes:       valuePtr has to be uint16_t*.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_POWER_REGISTER,

    /**
     * Current register.
     * Notes:       valuePtr has to be uint16_t*.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_INA220_CURRENT_REGISTER,

} tommRoC_hw_devices_adc_chip_ina220_value_type_enum_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipINA220InitI2C(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipINA220Start(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr);

/**
 * Read value.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        valueType               value types.
 * param[out]       valuePtr                output value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipINA220Read(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_devices_adc_chip_ina220_value_type_enum_t            valueType,
                void*                                                   const   valuePtr);

/**
 * Get property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipINA220GetProp(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr,
        const   tommRoC_hw_devices_adc_chip_ina220_prop_enum_t          property,
                void*                                           const   propValuePtr);

/**
 * Set property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[in]        propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipINA220SetProp(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr,
        const   tommRoC_hw_devices_adc_chip_ina220_prop_enum_t          property,
        const   void*                                           const   propValuePtr);

#endif
