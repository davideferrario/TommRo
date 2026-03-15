
#ifndef TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_H_
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_H_

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
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_I2C_7_BIT_ADDRESS_A1A0_PIN_GNDGND   (0b1000000)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_I2C_7_BIT_ADDRESS_A1A0_PIN_GNDVDD   (0b1000001)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_I2C_7_BIT_ADDRESS_A1A0_PIN_GNDSDA   (0b1000010)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_I2C_7_BIT_ADDRESS_A1A0_PIN_GNDSCL   (0b1000011)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_I2C_7_BIT_ADDRESS_A1A0_PIN_VDDGND   (0b1000100)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_I2C_7_BIT_ADDRESS_A1A0_PIN_VDDVDD   (0b1000101)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_I2C_7_BIT_ADDRESS_A1A0_PIN_VDDSDA   (0b1000110)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_I2C_7_BIT_ADDRESS_A1A0_PIN_VDDSCL   (0b1000111)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_I2C_7_BIT_ADDRESS_A1A0_PIN_SDAGND   (0b1001000)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_I2C_7_BIT_ADDRESS_A1A0_PIN_SDAVDD   (0b1001001)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_I2C_7_BIT_ADDRESS_A1A0_PIN_SDASDA   (0b1001010)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_I2C_7_BIT_ADDRESS_A1A0_PIN_SDASCL   (0b1001011)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_I2C_7_BIT_ADDRESS_A1A0_PIN_SCLGND   (0b1001100)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_I2C_7_BIT_ADDRESS_A1A0_PIN_SCLVDD   (0b1001101)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_I2C_7_BIT_ADDRESS_A1A0_PIN_SCLSDA   (0b1001110)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_I2C_7_BIT_ADDRESS_A1A0_PIN_SCLSCL   (0b1001111)


// Device data.
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_DEVICE_DATA_SIZE    (   TOMMROC_UTIL_U8_SIZE    +   \
                                                                    TOMMROC_UTIL_FLOAT_SIZE     )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of supported conversion mode.
typedef enum {

    /**
     * Single shot conversion (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_CM_SINGLE_SHOT_MODE = 0,

    /**
     * Continuous conversion.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_CM_CONTINUOUS_MODE,

} tommRoC_hw_devices_adc_chip_ads1119_conversion_mode_enum_t;

// Enumeration of input multiplexer configuration.
typedef enum {

    /**
     * AINp = AIN0; AINn = AIN1 (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_MUX_AIN0_AIN1 = 0,

    /**
     * AINp = AIN2; AINn = AIN3
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_MUX_AIN2_AIN3,

    /**
     * AINp = AIN1; AINn = AIN2
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_MUX_AIN1_AIN2,

    /**
     * AINp = AIN0; AINn = AGND
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_MUX_AIN0_AGND,

    /**
     * AINp = AIN1; AINn = AGND
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_MUX_AIN1_AGND,

    /**
     * AINp = AIN2; AINn = AGND
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_MUX_AIN2_AGND,

    /**
     * AINp = AIN3; AINn = AGND
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_MUX_AIN3_AGND,

    /**
     * AINp = AVDD/2; AINn = AVDD/2
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_MUX_AVDD_2_AVDD_2,

} tommRoC_hw_devices_adc_chip_ads1119_multiplexer_enum_t;

// Enumeration of gain configuration.
typedef enum {

    /**
     * Device gain = 1 (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_GAIN_1 = 0,

    /**
     * Device gain = 4.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_GAIN_4,

} tommRoC_hw_devices_adc_chip_ads1119_gain_enum_t;

// Enumeration of data rate configuration.
typedef enum {

    /**
     * Data rate = 20 SPS (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_DR_20_SPS = 0,

    /**
     * Data rate = 90 SPS.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_DR_90_SPS,

    /**
     * Data rate = 330 SPS.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_DR_330_SPS,

    /**
     * Data rate = 1000 SPS.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_DR_1000_SPS,

} tommRoC_hw_devices_adc_chip_ads1119_data_rate_enum_t;

// Enumeration of voltage reference source that is used for the conversion configuration.
typedef enum {

    /**
     * Voltage reference = Internal 2.048V (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_VREF_TYPE_INTERNAL_2_048V = 0,

    /**
     * Voltage reference = External REFP/REFN input.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_VREF_TYPE_EXTERNAL_REFP_REFN,

} tommRoC_hw_devices_adc_chip_ads1119_vref_type_enum_t;


// Enumeration of ADS properties.
typedef enum {

    /**
     * Conversion mode.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads1119_conversion_mode_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_CONVERSION_MODE_PROP = 0,

    /**
     * Input multiplexer.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads1119_multiplexer_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_MULTIPLEXER_PROP,

    /**
     * Gain.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads1119_gain_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_GAIN_PROP,

    /**
     * Data rate.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads1119_data_rate_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_DATA_RATE_PROP,

    /**
     * VREF type.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads1119_vref_type_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_VREF_TYPE_PROP,

    /**
     * External VREF value.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_unit_measure_voltage_volt_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS1119_EXTERNAL_VREF_PROP,

} tommRoC_hw_devices_adc_chip_ads1119_prop_enum_t;


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_ADC_CHIP_ADS1119_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_adc_chip_ads1119_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS1119InitI2C(
        const   uint8_t                                                     i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                                   const   busHandlerPtr,
        const   tommRoC_guard_t*                                    const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t*         const   specificSlavePtr,
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
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS1119AttachDeviceData(
        const   tommRoC_hw_devices_adc_chip_ads1119_device_data_t*  const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS1119Start(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Read ADC raw value.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       valuePtr                output ADC raw value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS1119ReadRaw(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                int16_t*                                            const   valuePtr);

/**
 * Read ADC voltage.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       valuePtr                output ADC value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS1119Read(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                tommRoC_unit_measure_voltage_volt_t*                const   valuePtr);

/**
 * Get property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS1119GetProp(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   tommRoC_hw_devices_adc_chip_ads1119_prop_enum_t             property,
                void*                                               const   propValuePtr);

/**
 * Set property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[in]        propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS1119SetProp(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   tommRoC_hw_devices_adc_chip_ads1119_prop_enum_t             property,
        const   void*                                               const   propValuePtr);

#endif
