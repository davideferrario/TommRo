
#ifndef TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_H_
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_H_

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
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_I2C_7_BIT_ADDRESS_A1A0_PIN_GNDGND   (0b1000000)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_I2C_7_BIT_ADDRESS_A1A0_PIN_GNDVDD   (0b1000001)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_I2C_7_BIT_ADDRESS_A1A0_PIN_GNDSDA   (0b1000010)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_I2C_7_BIT_ADDRESS_A1A0_PIN_GNDSCL   (0b1000011)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_I2C_7_BIT_ADDRESS_A1A0_PIN_VDDGND   (0b1000100)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_I2C_7_BIT_ADDRESS_A1A0_PIN_VDDVDD   (0b1000101)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_I2C_7_BIT_ADDRESS_A1A0_PIN_VDDSDA   (0b1000110)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_I2C_7_BIT_ADDRESS_A1A0_PIN_VDDSCL   (0b1000111)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_I2C_7_BIT_ADDRESS_A1A0_PIN_SDAGND   (0b1001000)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_I2C_7_BIT_ADDRESS_A1A0_PIN_SDAVDD   (0b1001001)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_I2C_7_BIT_ADDRESS_A1A0_PIN_SDASDA   (0b1001010)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_I2C_7_BIT_ADDRESS_A1A0_PIN_SDASCL   (0b1001011)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_I2C_7_BIT_ADDRESS_A1A0_PIN_SCLGND   (0b1001100)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_I2C_7_BIT_ADDRESS_A1A0_PIN_SCLVDD   (0b1001101)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_I2C_7_BIT_ADDRESS_A1A0_PIN_SCLSDA   (0b1001110)
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_I2C_7_BIT_ADDRESS_A1A0_PIN_SCLSCL   (0b1001111)


// Device data.
#define TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_DEVICE_DATA_SIZE  (   TOMMROC_UTIL_U8_SIZE    +   \
                                                                    TOMMROC_UTIL_FLOAT_SIZE     )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of gain configuration.
typedef enum {

    /**
     * Device gain = 1 (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_GAIN_1 = 0,

    /**
     * Device gain = 2.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_GAIN_2,

    /**
     * Device gain = 4.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_GAIN_4,

    /**
     * Device gain = 8.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_GAIN_8,

    /**
     * Device gain = 16.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_GAIN_16,

    /**
     * Device gain = 32.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_GAIN_32,

    /**
     * Device gain = 64.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_GAIN_64,

    /**
     * Device gain = 128.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_GAIN_128,

} tommRoC_hw_devices_adc_chip_ads122c04_gain_enum_t;

// Enumeration of input multiplexer configuration.
typedef enum {

    /**
     * AINp = AIN0; AINn = AIN1 (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MUX_AIN0_AIN1 = 0,

    /**
     * AINp = AIN0; AINn = AIN2
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MUX_AIN0_AIN2,

    /**
     * AINp = AIN0; AINn = AIN3
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MUX_AIN0_AIN3,

    /**
     * AINp = AIN1; AINn = AIN0
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MUX_AIN1_AIN0,

    /**
     * AINp = AIN1; AINn = AIN2
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MUX_AIN1_AIN2,

    /**
     * AINp = AIN1; AINn = AIN3
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MUX_AIN1_AIN3,

    /**
     * AINp = AIN2; AINn = AIN3
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MUX_AIN2_AIN3,

    /**
     * AINp = AIN3; AINn = AIN2
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MUX_AIN3_AIN2,

    /**
     * AINp = AIN0; AINn = AVSS
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MUX_AIN0_AVSS,

    /**
     * AINp = AIN1; AINn = AVSS
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MUX_AIN1_AVSS,

    /**
     * AINp = AIN2; AINn = AVSS
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MUX_AIN2_AVSS,

    /**
     * AINp = AIN3; AINn = AVSS
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MUX_AIN3_AVSS,

    /**
     * (Vrefp – Vrefn) / 4 monitor (PGA bypassed)
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MUX_Verfp_MINUS_Vrefn_DIV_4_MONITOR,

    /**
     * (AVDD – AVSS) / 4 monitor (PGA bypassed)
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MUX_AVDD_MINUS_AVSS_DIV_4_MONITOR,

    /**
     * AINp and AINn shorted to (AVDD + AVSS) / 2
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MUX_AINp_AINn_TO_AVDD_PLUS_AVSS_DIV_2,

} tommRoC_hw_devices_adc_chip_ads122c04_multiplexer_enum_t;

// Enumeration of voltage reference source that is used for the conversion configuration.
typedef enum {

    /**
     * Voltage reference = Internal 2.048V (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_VREF_TYPE_INTERNAL_2_048V = 0,

    /**
     * Voltage reference = External REFP/REFN input.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_VREF_TYPE_EXTERNAL_REFP_REFN,

    /**
     * Voltage reference = Analog supply (AVDD – AVSS).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_VREF_TYPE_AVDD_MINUS_AVSS,

} tommRoC_hw_devices_adc_chip_ads122c04_vref_type_enum_t;

// Enumeration of supported conversion mode.
typedef enum {

    /**
     * Single shot conversion (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_CM_SINGLE_SHOT_MODE = 0,

    /**
     * Continuous conversion.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_CM_CONTINUOUS_MODE,

} tommRoC_hw_devices_adc_chip_ads122c04_conversion_mode_enum_t;

// Enumeration of supported operating mode.
typedef enum {

    /**
     * Normal mode (256-kHz modulator clock) (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MODE_NORMAL_MODE = 0,

    /**
     * Turbo mode (512-kHz modulator clock).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MODE_TURBO_MODE,

} tommRoC_hw_devices_adc_chip_ads122c04_operating_mode_enum_t;

// Enumeration of data rate configuration.
typedef enum {

    /**
     * Data rate: Normal mode = 20 SPS/Turbo mode = 40 SPS (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_DR_NM_20_SPS_TM_40_SPS = 0,

    /**
     * Data rate: Normal mode = 45 SPS/Turbo mode = 90 SPS.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_DR_NM_45_SPS_TM_90_SPS,

    /**
     * Data rate: Normal mode = 90 SPS/Turbo mode = 180 SPS.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_DR_NM_90_SPS_TM_180_SPS,

    /**
     * Data rate: Normal mode = 175 SPS/Turbo mode = 350 SPS.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_DR_NM_175_SPS_TM_350_SPS,

    /**
     * Data rate: Normal mode = 330 SPS/Turbo mode = 660 SPS.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_DR_NM_330_SPS_TM_660_SPS,

    /**
     * Data rate: Normal mode = 600 SPS/Turbo mode = 1200 SPS.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_DR_NM_600_SPS_TM_1200_SPS,

    /**
     * Data rate: Normal mode = 1000 SPS/Turbo mode = 2000 SPS.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_DR_NM_1000_SPS_TM_2000_SPS,

} tommRoC_hw_devices_adc_chip_ads122c04_data_rate_enum_t;

// Enumeration of IDAC current setting configuration.
typedef enum {

    /**
     * IDAC1/IDAC2 excitation current sources = OFF (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC_OFF = 0,

    /**
     * IDAC1/IDAC2 excitation current sources = 10 uA.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC_10uA,

    /**
     * IDAC1/IDAC2 excitation current sources = 50 uA.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC_50uA,

    /**
     * IDAC1/IDAC2 excitation current sources = 100 uA.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC_100uA,

    /**
     * IDAC1/IDAC2 excitation current sources = 250 uA.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC_250uA,

    /**
     * IDAC1/IDAC2 excitation current sources = 500 uA.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC_500uA,

    /**
     * IDAC1/IDAC2 excitation current sources = 1000 uA.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC_1000uA,

    /**
     * IDAC1/IDAC2 excitation current sources = 1500 uA.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC_1500uA,

} tommRoC_hw_devices_adc_chip_ads122c04_idac_current_enum_t;

// Enumeration of IDAC1 routing configuration.
typedef enum {

    /**
     * IDAC1 disabled (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC1_ROUTE_DISABLED = 0,

    /**
     * IDAC1 connected to AIN0.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC1_ROUTE_TO_AIN0,

    /**
     * IDAC1 connected to AIN1.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC1_ROUTE_TO_AIN1,

    /**
     * IDAC1 connected to AIN2.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC1_ROUTE_TO_AIN2,

    /**
     * IDAC1 connected to AIN3.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC1_ROUTE_TO_AIN3,

    /**
     * IDAC1 connected to REFP.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC1_ROUTE_TO_REFP,

    /**
     * IDAC1 connected to REFN.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC1_ROUTE_TO_REFN,

} tommRoC_hw_devices_adc_chip_ads122c04_idac1_routing_enum_t;

// Enumeration of IDAC2 routing configuration.
typedef enum {

    /**
     * IDAC2 disabled (default).
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC2_ROUTE_DISABLED = 0,

    /**
     * IDAC2 connected to AIN0.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC2_ROUTE_TO_AIN0,

    /**
     * IDAC2 connected to AIN1.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC2_ROUTE_TO_AIN1,

    /**
     * IDAC2 connected to AIN2.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC2_ROUTE_TO_AIN2,

    /**
     * IDAC2 connected to AIN3.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC2_ROUTE_TO_AIN3,

    /**
     * IDAC2 connected to REFP.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC2_ROUTE_TO_REFP,

    /**
     * IDAC2 connected to REFN.
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC2_ROUTE_TO_REFN,

} tommRoC_hw_devices_adc_chip_ads122c04_idac2_routing_enum_t;


// Enumeration of ADS properties.
typedef enum {

    /**
     * Gain.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads122c04_gain_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_GAIN_PROP = 0,

    /**
     * Input multiplexer.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads122c04_multiplexer_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MULTIPLEXER_PROP,

    /**
     * VREF type.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads122c04_vref_type_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_VREF_TYPE_PROP,

    /**
     * External VREF or analog supply value.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_unit_measure_voltage_volt_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_EXTERNAL_VREF_PROP,

    /**
     * Conversion mode.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads122c04_conversion_mode_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_CONVERSION_MODE_PROP,

    /**
     * Operating mode.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads122c04_operating_mode_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_OPERATING_MODE_PROP,

    /**
     * Data rate.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads122c04_data_rate_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_DATA_RATE_PROP,

    /**
     * IDAC current.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads122c04_idac_current_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC_CURRENT_PROP,

    /**
     * IDAC1 routing.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads122c04_idac1_routing_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC1_ROUTING_PROP,

    /**
     * IDAC2 routing.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_devices_adc_chip_ads122c04_idac2_routing_enum_t*
     */
    TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC2_ROUTING_PROP,

} tommRoC_hw_devices_adc_chip_ads122c04_prop_enum_t;


// Configuration structure.
typedef struct {

    tommRoC_hw_devices_adc_chip_ads122c04_gain_enum_t               gain;           // GAIN
    tommRoC_hw_devices_adc_chip_ads122c04_multiplexer_enum_t        mux;            // Multiplexer
    tommRoC_hw_devices_adc_chip_ads122c04_vref_type_enum_t          VREFType;       // VREF type
    tommRoC_hw_devices_adc_chip_ads122c04_conversion_mode_enum_t    convMode;       // Conversion mode
    tommRoC_hw_devices_adc_chip_ads122c04_operating_mode_enum_t     opMode;         // Operating mode
    tommRoC_hw_devices_adc_chip_ads122c04_data_rate_enum_t          dataRate;       // Data rate
    tommRoC_hw_devices_adc_chip_ads122c04_idac_current_enum_t       IDACCurrent;    // IDAC current
    tommRoC_hw_devices_adc_chip_ads122c04_idac1_routing_enum_t      IDAC1Routing;   // IDAC1 routing
    tommRoC_hw_devices_adc_chip_ads122c04_idac2_routing_enum_t      IDAC2Routing;   // IDAC2 routing

} tommRoC_hw_devices_adc_chip_ads122c04_config_t;

#define __EMPTY_tommRoC_hw_devices_adc_chip_ads122c04_config_t__                            \
{                                                                                           \
    /* .gain */         TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_GAIN_1,                      \
    /* .mux */          TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MUX_AIN0_AIN1,               \
    /* .VREFType */     TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_VREF_TYPE_INTERNAL_2_048V,   \
    /* .CM */           TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_CM_SINGLE_SHOT_MODE,         \
    /* .mode */         TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_MODE_NORMAL_MODE,            \
    /* .dataRate */     TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_DR_NM_20_SPS_TM_40_SPS,      \
    /* .IDACCurrent */  TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC_OFF,                    \
    /* .IDAC1Route */   TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC1_ROUTE_DISABLED,        \
    /* .IDAC2Route */   TOMMRO_C_HW_DEVICES_ADC_CHIP_ADS122C04_IDAC2_ROUTE_DISABLED,        \
}

// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_ADC_CHIP_ADS122C04_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_adc_chip_ads122c04_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS122C04InitI2C(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS122C04AttachDeviceData(
        const   tommRoC_hw_devices_adc_chip_ads122c04_device_data_t*    const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        configPtr               chip configuration pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS122C04Start(
        const   tommRoC_hw_devices_adc_chip_ads122c04_config_t*         const   configPtr,
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Read ADC voltage.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       valuePtr                output ADC value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS122C04Read(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                tommRoC_unit_measure_voltage_volt_t*                    const   valuePtr);

/**
 * Get property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS122C04GetProp(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_devices_adc_chip_ads122c04_prop_enum_t               property,
                void*                                                   const   propValuePtr);

/**
 * Set property.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[in]        propValuePtr            value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesADCChipADS122C04SetProp(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_devices_adc_chip_ads122c04_prop_enum_t               property,
        const   void*                                                   const   propValuePtr);

#endif
