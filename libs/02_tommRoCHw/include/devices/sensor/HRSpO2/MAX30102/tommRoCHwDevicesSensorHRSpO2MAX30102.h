
#ifndef TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_H_
#define TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_H_

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
#define TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_I2C_7_BIT_ADDRESS (0b1010111)


#define TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_FIFO_SIZE_SAMPLES (32)

// Device data.
#define TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_DEVICE_DATA_SIZE  (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                        TOMMROC_UTIL_U8_SIZE        +   \
                                                                        TOMMROC_UTIL_U8_SIZE            )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_OPERATING_MODE_HEART_RATE = 0,    // Heart Rate mode - Red only.
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_OPERATING_MODE_SPO2,              // SpO2 mode - Red and IR.
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_OPERATING_MODE_MULTI_LED,         // Multi-LED mode - Red and IR.

} tommRoC_hw_devices_sensor_hrspo2_max30102_operating_mode_enum_t;

/**
 * From datasheet:
 *
 * This sets the SpO2 sensor ADC’s full-scale range.
 */
typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_SPO2_ADC_FULL_SCALE_2048nA = 0,   // SpO2 sensor ADC’s full-scale = 2048 nA
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_SPO2_ADC_FULL_SCALE_4096nA,       // SpO2 sensor ADC’s full-scale = 4096 nA
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_SPO2_ADC_FULL_SCALE_8192nA,       // SpO2 sensor ADC’s full-scale = 8192 nA
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_SPO2_ADC_FULL_SCALE_16384nA,      // SpO2 sensor ADC’s full-scale = 16384 nA

} tommRoC_hw_devices_sensor_hrspo2_max30102_spo2_adc_full_scale_enum_t;

/**
 * From datasheet:
 *
 * These define the effective sampling rate with one sample consisting of one IR pulse/conversion and one Red pulse/conversion.
 * The sample rate and pulse width are related in that the sample rate sets an upper bound on the pulse width time.
 * If the user selects a sample rate that is too high for the selected LED_PW setting,
 * the highest possible sample rate is programmed instead into the register.
 */
typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_SPO2_SAMPLE_RATE_50SPS = 0,       // Sample per second = 50
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_SPO2_SAMPLE_RATE_100SPS,          // Sample per second = 100
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_SPO2_SAMPLE_RATE_200SPS,          // Sample per second = 200
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_SPO2_SAMPLE_RATE_400SPS,          // Sample per second = 400
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_SPO2_SAMPLE_RATE_800SPS,          // Sample per second = 800
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_SPO2_SAMPLE_RATE_1000SPS,         // Sample per second = 1000
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_SPO2_SAMPLE_RATE_1600SPS,         // Sample per second = 1600
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_SPO2_SAMPLE_RATE_3200SPS,         // Sample per second = 3200

} tommRoC_hw_devices_sensor_hrspo2_max30102_spo2_sample_rate_enum_t;

/**
 * From datasheet:
 *
 * These set the LED pulse width (the IR and Red have the same pulse width), and therefore, indirectly
 * sets the integration time of the ADC in each sample.
 * The ADC resolution is directly related to the integration time.
 *
 * The longer the pulse width the longer range of detection you'll have.
 * - At 69 us and 0.4mA it's about 2 inches.
 * - At 411 us and 0.4mA it's about 6 inches.
 */
typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_LED_PULSE_WIDTH_69uS = 0,         // ADC resolution: 15 bits
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_LED_PULSE_WIDTH_118uS,            // ADC resolution: 16 bits
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_LED_PULSE_WIDTH_215uS,            // ADC resolution: 17 bits
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_LED_PULSE_WIDTH_411uS,            // ADC resolution: 18 bits

} tommRoC_hw_devices_sensor_hrspo2_max30102_led_pulse_width_enum_t;

/**
 * From datasheet:
 *
 * To reduce the amount of data throughput, adjacent samples (in each individual channel) can be
 * averaged and decimated on the chip by setting this register.
 */
typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_FIFO_SAMPLE_AVERAGING_1 = 0,      // N. of samples averaged per FIFO sample = 1 (no averaging)
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_FIFO_SAMPLE_AVERAGING_2,          // N. of samples averaged per FIFO sample = 2
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_FIFO_SAMPLE_AVERAGING_4,          // N. of samples averaged per FIFO sample = 4
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_FIFO_SAMPLE_AVERAGING_8,          // N. of samples averaged per FIFO sample = 8
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_FIFO_SAMPLE_AVERAGING_16,         // N. of samples averaged per FIFO sample = 16
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_FIFO_SAMPLE_AVERAGING_32,         // N. of samples averaged per FIFO sample = 32

} tommRoC_hw_devices_sensor_hrspo2_max30102_fifo_sample_averaging_enum_t;

// Configuration structure.
typedef struct {

    tommRoC_hw_devices_sensor_hrspo2_max30102_operating_mode_enum_t         operatingMode;
    tommRoC_hw_devices_sensor_hrspo2_max30102_spo2_adc_full_scale_enum_t    spo2ADCFullScale;
    tommRoC_hw_devices_sensor_hrspo2_max30102_spo2_sample_rate_enum_t       spo2SampleRate;
    tommRoC_hw_devices_sensor_hrspo2_max30102_led_pulse_width_enum_t        ledPulseWidth;
    tommRoC_hw_devices_sensor_hrspo2_max30102_fifo_sample_averaging_enum_t  fifoSampleAveraging;

    /**
     * From datasheet:
     *
     * These set the current level of each LED (rate = 0.2 mA).
     * 0x00 ->  0.0 mA
     * 0x01 ->  0.2 mA
     * 0x02 ->  0.4 mA  - Presence detection of about 4 inch
     * ...      ...
     * 0x1F ->  6.4 mA  - Presence detection of about 8 inch
     * ...      ...
     * 0x7F ->  25.4 mA - Presence detection of about 8 inch
     * ...      ...
     * 0xFF ->  51.0 mA - Presence detection of about 12 inch
     */
    uint8_t                                                                 ledREDPulseAmplitude;
    uint8_t                                                                 ledIRPulseAmplitude;

} tommRoC_hw_devices_sensor_hrspo2_max30102_config_t;

#define __EMPTY_tommRoC_hw_devices_sensor_hrspo2_max30102_config_t__                                    \
{                                                                                                       \
    /* .operatingMode */        TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_OPERATING_MODE_SPO2,          \
    /* .spo2ADCFullScale */     TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_SPO2_ADC_FULL_SCALE_2048nA,   \
    /* .spo2SampleRate */       TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_SPO2_SAMPLE_RATE_50SPS,       \
    /* .ledPulseWidth */        TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_LED_PULSE_WIDTH_69uS,         \
    /* .fifoSampleAveraging */  TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_FIFO_SAMPLE_AVERAGING_1,      \
    /* .ledREDPulseAmplitude */ (0x1F),                                                                 \
    /* .ledIRPulseAmplitude */  (0x1F),                                                                 \
}


// Error flag structure.
typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_FLAG_ALC_OVF_NOT_DETECTED = 0,    // Ambient Light Cancellation Overflow not detected
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_FLAG_ALC_OVF_DETECTED,            // Ambient Light Cancellation Overflow detected

} tommRoC_hw_devices_sensor_hrspo2_max30102_error_flag_alc_ovf_enum_t;

typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_FLAG_FIFO_OVF_NOT_DETECTED = 0,   // FIFO Overflow Counter not detected
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_FLAG_FIFO_OVF_DETECTED,           // FIFO Overflow Counter detected

} tommRoC_hw_devices_sensor_hrspo2_max30102_error_flag_fifo_ovf_enum_t;

typedef struct {

    tommRoC_hw_devices_sensor_hrspo2_max30102_error_flag_alc_ovf_enum_t     alcOvf;
    tommRoC_hw_devices_sensor_hrspo2_max30102_error_flag_fifo_ovf_enum_t    fifoOvf;

} tommRoC_hw_devices_sensor_hrspo2_max30102_error_flag_t;

#define __EMPTY_tommRoC_hw_devices_sensor_hrspo2_max30102_error_flag_t__                    \
{                                                                                           \
    /* .alcOvf */   TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_FLAG_ALC_OVF_NOT_DETECTED,    \
    /* .fifoOvf */  TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_FLAG_FIFO_OVF_NOT_DETECTED,   \
}


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX30102_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_sensor_hrspo2_max30102_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX30102InitI2C(
        const   uint8_t                                                             i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                                           const   busHandlerPtr,
        const   tommRoC_guard_t*                                            const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t*                 const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX30102AttachDeviceData(
        const   tommRoC_hw_devices_sensor_hrspo2_max30102_device_data_t*    const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        INTStatus               get INT pin status function pointer (NULL if not used/not available).
 * param[in]        configPtr               chip configuration pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX30102Start(
        const   tommRoC_hw_gpio_get_cb_t                                            INTStatus,
        const   tommRoC_hw_devices_sensor_hrspo2_max30102_config_t*         const   configPtr,
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Configure chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        configPtr               chip configuration pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX30102Configure(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
        const   tommRoC_hw_devices_sensor_hrspo2_max30102_config_t*         const   configPtr);

/**
 * Get samples.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       ledRedADCPtr            output led RED ADC values pointer.
 * param[out]       ledIrADCPtr             output led IR ADC values pointer.
 * param[in]        toReadSampleAmount      to read samples amount.
 * param[out]       readedSampleAmountPtr   readed samples count pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX30102Get(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                uint32_t*                                                   const   ledRedADCPtr,
                uint32_t*                                                   const   ledIrADCPtr,
        const   uint8_t                                                             toReadSampleAmount,
                uint8_t*                                                    const   readedSampleAmountPtr);

/**
 * Get temperature.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       temperaturePtr          output temperature pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX30102GetTemp(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                tommRoC_unit_measure_temperature_celsius_t*                 const   temperaturePtr);

/**
 * Get chip error flag.
 * NOTE: internal error flag are not cleared. For that, a clear function call is needed.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       errorFlagPtr            output error flag struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX30102GetErrorFlag(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                tommRoC_hw_devices_sensor_hrspo2_max30102_error_flag_t*     const   errorFlagPtr);

/**
 * Clear chip error flag.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX30102ClearErrorFlag(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Sleep (shutdown)/wake (wakeup) chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX30102Sleep(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX30102Wake(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

#endif
