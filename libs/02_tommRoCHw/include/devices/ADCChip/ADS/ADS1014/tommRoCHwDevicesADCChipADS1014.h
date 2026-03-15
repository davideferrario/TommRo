
#ifndef TOMMROC_HW_DEVICES_ADC_CHIP_ADS1014_H_
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1014_H_

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
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1014_I2C_7_BIT_ADDRESS_ADDR_PIN_GND  (0b1001000)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1014_I2C_7_BIT_ADDRESS_ADDR_PIN_VDD  (0b1001001)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of supported conversion mode.
typedef enum {

    /**
     * Single shot conversion (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_SINGLE_SHOT_MODE = 0,

    /**
     * Continuous conversion.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_CONTINUOUS_MODE,

} tommRoC_hw_devices_adc_chip_ads1014_conversion_mode_enum_t;

// Enumeration of input multiplexer configuration.
typedef enum {

    /**
     * AINp = AIN0; AINn = AIN1 (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_AIN0_AIN1 = 0,

    /**
     * AINp = AIN0; AINn = AIN3
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_AIN0_AIN3,

    /**
     * AINp = AIN1; AINn = AIN3
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_AIN1_AIN3,

    /**
     * AINp = AIN2; AINn = AIN3
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_AIN2_AIN3,

    /**
     * AINp = AIN0; AINn = GND
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_AIN0_GND,

    /**
     * AINp = AIN1; AINn = GND
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_AIN1_GND,

    /**
     * AINp = AIN2; AINn = GND
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_AIN2_GND,

    /**
     * AINp = AIN3; AINn = GND
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_AIN3_GND,

} tommRoC_hw_devices_adc_chip_ads1014_multiplexer_enum_t;

// Enumeration of full scale range configuration.
typedef enum {

    /**
     * FSR = +/-6.144V
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_FSR_6_144 = 0,

    /**
     * FSR = +/-4.096V
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_FSR_4_096,

    /**
     * FSR = +/-2.048V (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_FSR_2_048,

    /**
     * FSR = +/-1.024V
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_FSR_1_024,

    /**
     * FSR = +/-0.512V
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_FSR_0_512,

    /**
     * FSR = +/-0.256V
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_FSR_0_256,

} tommRoC_hw_devices_adc_chip_ads1014_fsr_enum_t;

// Enumeration of conversion ready pin configuration.
typedef enum {

    /**
     * Conversion ready pin disabled (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_READY_PIN_DISABLED = 0,

    /**
     * Conversion ready pin enabled (active low).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_READY_PIN_ENABLED_ACTIVE_LOW,

    /**
     * Conversion ready pin enabled (active high).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_READY_PIN_ENABLED_ACTIVE_HIGH,

} tommRoC_hw_devices_adc_chip_ads1014_ready_pin_enum_t;


// Enumeration of ADS properties.
typedef enum {

    /**
     * Conversion mode.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads1014_conversion_mode_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_CONVERSION_MODE_PROP = 0,

    /**
     * Input multiplexer.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads1014_multiplexer_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_MULTIPLEXER_PROP,

    /**
     * Gain amplifier.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads1014_fsr_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_FSR_PROP,

    /**
     * Conversion ready pin.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads1014_ready_pin_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1014_READY_PIN_PROP,

} tommRoC_hw_devices_adc_chip_ads1014_prop_enum_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS1014InitI2C(
        const   uint8_t                                                 i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                               const   busHandlerPtr,
        const   tommRoC_guard_t*                                const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t*     const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                        const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS1014Start(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr);

/**
 * Read ADC voltage.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       valuePtr                output ADC value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS1014Read(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr,
                float*                                          const   valuePtr);

/**
 * Get property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS1014GetProp(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr,
        const   tommRoC_hw_devices_adc_chip_ads1014_prop_enum_t         property,
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
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS1014SetProp(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr,
        const   tommRoC_hw_devices_adc_chip_ads1014_prop_enum_t         property,
        const   void*                                           const   propValuePtr);

#endif
