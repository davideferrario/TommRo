
#ifndef TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_H_
#define TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_H_

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
#define TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_I2C_7_BIT_ADDRESS (0b1010111)


#define TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_FIFO_SIZE_SAMPLES (32)

// Device data.
#define TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_DEVICE_DATA_SIZE  (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                        TOMMROC_UTIL_U8_SIZE        +   \
                                                                        TOMMROC_UTIL_U8_SIZE            )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_OPERATING_MODE_DISABLED = 0,
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_OPERATING_MODE_LED1,              // LED1 Enabled. Only one ADC conversion for LED1 (IR led).
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_OPERATING_MODE_LED1_LED2,         // LED1/LED2 Enabled. Two ADC conversions for LED1 (IR led) and LED2 (RED led).
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_OPERATING_MODE_FLEX_LED,          // Flex-LED mode. LED types are programmed with led Sequence config.

} tommRoC_hw_devices_sensor_hrspo2_max86916_operating_mode_enum_t;

typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_SEQUENCE_OFF = 0,             // Led OFF
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_SEQUENCE_LED1,                // LED1 - IR led
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_SEQUENCE_LED2,                // LED2 - RED led
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_SEQUENCE_LED3,                // LED3 - GREEN led
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_SEQUENCE_LED4,                // LED4 - BLUE led

} tommRoC_hw_devices_sensor_hrspo2_max86916_led_sequence_enum_t;

/**
 * From datasheet:
 *
 * This set the ADC range of the sensor.
 */
typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_ADC_FULL_SCALE_4096nA = 0,        // ADC’s full-scale = 4096nA    - LSB (PA) = 7.81
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_ADC_FULL_SCALE_8192nA,            // ADC’s full-scale = 8192nA    - LSB (PA) = 15.63
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_ADC_FULL_SCALE_16384nA,           // ADC’s full-scale = 16384nA   - LSB (PA) = 31.25
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_ADC_FULL_SCALE_32768nA,           // ADC’s full-scale = 32768nA   - LSB (PA) = 62.50

} tommRoC_hw_devices_sensor_hrspo2_max86916_adc_full_scale_enum_t;

/**
 * From datasheet:
 *
 * This set the sampling rate of the optical sensor.
 */
typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_SAMPLE_RATE_50SPS = 0,            // Sample per second = 50
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_SAMPLE_RATE_100SPS,               // Sample per second = 100
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_SAMPLE_RATE_200SPS,               // Sample per second = 200
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_SAMPLE_RATE_400SPS,               // Sample per second = 400
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_SAMPLE_RATE_800SPS,               // Sample per second = 800
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_SAMPLE_RATE_1000SPS,              // Sample per second = 1000
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_SAMPLE_RATE_1600SPS,              // Sample per second = 1600
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_SAMPLE_RATE_3200SPS,              // Sample per second = 3200

} tommRoC_hw_devices_sensor_hrspo2_max86916_sample_rate_enum_t;

/**
 * From datasheet:
 *
 * This set the pulse width of the LED drivers and the integration time of ADC.
 */
typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_PULSE_WIDTH_70uS = 0,         // Integration time: 50us   - ADC resolution: 19 bits
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_PULSE_WIDTH_120uS,            // Integration time: 100us  - ADC resolution: 19 bits
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_PULSE_WIDTH_220uS,            // Integration time: 200us  - ADC resolution: 19 bits
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_PULSE_WIDTH_420uS,            // Integration time: 400us  - ADC resolution: 19 bits

} tommRoC_hw_devices_sensor_hrspo2_max86916_led_pulse_width_enum_t;

/**
 * From datasheet:
 *
 * Adjacent samples (of each individual LED) can be internally averaged to reduce the amount of data throughput.
 * Each LED channel will be averaged individually and output sequentially as programmed in the LED Sequence Registers.
 *
 * This set the number of samples that are averaged on chip before being written to the FIFO.
 * The effective output sample rate is the sample rate programmed in SR divided by the Sample Average value.
 */
typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_FIFO_SAMPLE_AVERAGING_1 = 0,      // N. of samples averaged per FIFO sample = 1 (no averaging)
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_FIFO_SAMPLE_AVERAGING_2,          // N. of samples averaged per FIFO sample = 2
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_FIFO_SAMPLE_AVERAGING_4,          // N. of samples averaged per FIFO sample = 4
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_FIFO_SAMPLE_AVERAGING_8,          // N. of samples averaged per FIFO sample = 8
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_FIFO_SAMPLE_AVERAGING_16,         // N. of samples averaged per FIFO sample = 16
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_FIFO_SAMPLE_AVERAGING_32,         // N. of samples averaged per FIFO sample = 32

} tommRoC_hw_devices_sensor_hrspo2_max86916_fifo_sample_averaging_enum_t;

/**
 * From datasheet:
 *
 * Range selection of the LED current.
 */
typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_CURRENT_RANGE_50mA = 0,       // Led current range = 50mA
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_CURRENT_RANGE_100mA,          // Led current range = 100mA
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_CURRENT_RANGE_150mA,          // Led current range = 150mA
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_CURRENT_RANGE_200mA,          // Led current range = 200mA

} tommRoC_hw_devices_sensor_hrspo2_max86916_led_current_range_enum_t;


// Configuration structure.
typedef struct {

    tommRoC_hw_devices_sensor_hrspo2_max86916_operating_mode_enum_t         operatingMode;
    tommRoC_hw_devices_sensor_hrspo2_max86916_led_sequence_enum_t           ledSequencePos1;    // NOTE: used only if TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_OPERATING_MODE_FLEX_LED
    tommRoC_hw_devices_sensor_hrspo2_max86916_led_sequence_enum_t           ledSequencePos2;    // NOTE: used only if TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_OPERATING_MODE_FLEX_LED
    tommRoC_hw_devices_sensor_hrspo2_max86916_led_sequence_enum_t           ledSequencePos3;    // NOTE: used only if TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_OPERATING_MODE_FLEX_LED
    tommRoC_hw_devices_sensor_hrspo2_max86916_led_sequence_enum_t           ledSequencePos4;    // NOTE: used only if TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_OPERATING_MODE_FLEX_LED
    tommRoC_hw_devices_sensor_hrspo2_max86916_adc_full_scale_enum_t         ADCFullScale;
    tommRoC_hw_devices_sensor_hrspo2_max86916_sample_rate_enum_t            sampleRate;
    tommRoC_hw_devices_sensor_hrspo2_max86916_led_pulse_width_enum_t        ledPulseWidth;
    tommRoC_hw_devices_sensor_hrspo2_max86916_fifo_sample_averaging_enum_t  fifoSampleAveraging;

    tommRoC_util_enabled_status_enum_t alcEnabledStatus;        // Ambient Light Cancellation enabled status.
    tommRoC_util_enabled_status_enum_t proxEnabledStatus;       // Proximity function enabled status.

    /**
     * Interrupt enabled.
     */
    tommRoC_util_enabled_status_enum_t alcOvfIntEnabledStatus;  // INT triggers when ambient light cancellation has reached maximum limit.
    tommRoC_util_enabled_status_enum_t smpRdyIntEnabledStatus;  // INT triggers when there is a new sample in data FIFO.
    tommRoC_util_enabled_status_enum_t aFullIntEnabledStatus;   // INT triggers when FIFO buffer will overflow the threshold set by FIFO_A_FULL[3:0]

    /**
     * From datasheet:
     *
     * This set the nominal current pulse amplitude of LEDx (x = 1 to 4) as shown in the table below.
     *
     * LEDX_RGE     | 50.0mA    | 100.0mA   | 150.0mA   | 200.0mA
     * 0x00 ->      |  0.0mA    |   0.0mA   |   0.0mA   |   0.0mA
     * 0x01 ->      |  0.2mA    |   0.4mA   |   0.6mA   |   0.8mA
     * 0x02 ->      |  0.4mA    |   0.8mA   |   1.2mA   |   1.6mA
     * ...
     * 0xFF ->      | 50.4mA    | 100.8mA   | 151.2mA   | 201.6mA
     *
     * LSB          |  0.2mA    |   0.4mA   |   0.6mA   | 0.8mA
     */
    tommRoC_hw_devices_sensor_hrspo2_max86916_led_current_range_enum_t led1CurrentRange;
    tommRoC_hw_devices_sensor_hrspo2_max86916_led_current_range_enum_t led2CurrentRange;
    tommRoC_hw_devices_sensor_hrspo2_max86916_led_current_range_enum_t led3CurrentRange;
    tommRoC_hw_devices_sensor_hrspo2_max86916_led_current_range_enum_t led4CurrentRange;
    uint8_t led1PulseAmplitude;
    uint8_t led2PulseAmplitude;
    uint8_t led3PulseAmplitude;
    uint8_t led4PulseAmplitude;

} tommRoC_hw_devices_sensor_hrspo2_max86916_config_t;

#define __EMPTY_tommRoC_hw_devices_sensor_hrspo2_max86916_config_t__                                    \
{                                                                                                       \
    /* .operatingMode */            TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_OPERATING_MODE_DISABLED,  \
    /* .ledSequencePos1 */          TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_SEQUENCE_OFF,         \
    /* .ledSequencePos2 */          TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_SEQUENCE_OFF,         \
    /* .ledSequencePos3 */          TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_SEQUENCE_OFF,         \
    /* .ledSequencePos4 */          TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_SEQUENCE_OFF,         \
    /* .ADCFullScale */             TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_ADC_FULL_SCALE_4096nA,    \
    /* .sampleRate */               TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_SAMPLE_RATE_50SPS,        \
    /* .ledPulseWidth */            TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_PULSE_WIDTH_70uS,     \
    /* .fifoSampleAveraging */      TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_FIFO_SAMPLE_AVERAGING_1,  \
                                                                                                        \
    /* .alcEnabledStatus */         TOMMRO_C_UTIL_ENABLED,                                              \
    /* .proxEnabledStatus */        TOMMRO_C_UTIL_DISABLED,                                             \
                                                                                                        \
    /* .alcOvfIntEnabledStatus */   TOMMRO_C_UTIL_DISABLED,                                             \
    /* .smpRdyIntEnabledStatus */   TOMMRO_C_UTIL_DISABLED,                                             \
    /* .aFullIntEnabledStatus */    TOMMRO_C_UTIL_DISABLED,                                             \
                                                                                                        \
    /* .led1CurrentRange */         TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_CURRENT_RANGE_50mA,   \
    /* .led2CurrentRange */         TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_CURRENT_RANGE_50mA,   \
    /* .led3CurrentRange */         TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_CURRENT_RANGE_50mA,   \
    /* .led4CurrentRange */         TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_LED_CURRENT_RANGE_50mA,   \
                                                                                                        \
    /* .led1PulseAmplitude */       (0x00),                                                             \
    /* .led2PulseAmplitude */       (0x00),                                                             \
    /* .led3PulseAmplitude */       (0x00),                                                             \
    /* .led4PulseAmplitude */       (0x00),                                                             \
}


// Error flag structure.
typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_FLAG_ALC_OVF_NOT_DETECTED = 0,    // Ambient Light Cancellation Overflow not detected
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_FLAG_ALC_OVF_DETECTED,            // Ambient Light Cancellation Overflow detected

} tommRoC_hw_devices_sensor_hrspo2_max86916_error_flag_alc_ovf_enum_t;

typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_FLAG_FIFO_OVF_NOT_DETECTED = 0,   // FIFO Overflow Counter not detected
    TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_FLAG_FIFO_OVF_DETECTED,           // FIFO Overflow Counter detected

} tommRoC_hw_devices_sensor_hrspo2_max86916_error_flag_fifo_ovf_enum_t;

typedef struct {

    tommRoC_hw_devices_sensor_hrspo2_max86916_error_flag_alc_ovf_enum_t     alcOvf;
    tommRoC_hw_devices_sensor_hrspo2_max86916_error_flag_fifo_ovf_enum_t    fifoOvf;

} tommRoC_hw_devices_sensor_hrspo2_max86916_error_flag_t;

#define __EMPTY_tommRoC_hw_devices_sensor_hrspo2_max86916_error_flag_t__                    \
{                                                                                           \
    /* .alcOvf */   TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_FLAG_ALC_OVF_NOT_DETECTED,    \
    /* .fifoOvf */  TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_FLAG_FIFO_OVF_NOT_DETECTED,   \
}


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_SENSOR_HRSPO2_MAX86916_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_sensor_hrspo2_max86916_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX86916InitI2C(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX86916AttachDeviceData(
        const   tommRoC_hw_devices_sensor_hrspo2_max86916_device_data_t*    const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        INTBStatus              get INTB pin status function pointer (NULL if not used/not available).
 * param[in]        configPtr               chip configuration pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX86916Start(
        const   tommRoC_hw_gpio_get_cb_t                                            INTBStatus,
        const   tommRoC_hw_devices_sensor_hrspo2_max86916_config_t*         const   configPtr,
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Configure chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        configPtr               chip configuration pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX86916Configure(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
        const   tommRoC_hw_devices_sensor_hrspo2_max86916_config_t*         const   configPtr);

/**
 * Get samples.
 * NOTE: led1/led2/led3/led4 mapping is determined by operating_mode/led sequence configuration.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       led1ADCPtr              output led 1 ADC values pointer.
 * param[out]       led2ADCPtr              output led 2 ADC values pointer.
 * param[out]       led3ADCPtr              output led 3 ADC values pointer.
 * param[out]       led4ADCPtr              output led 4 ADC values pointer.
 * param[in]        toReadSampleAmount      to read samples amount.
 * param[out]       readedSampleAmountPtr   readed samples count pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX86916Get(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                uint32_t*                                                   const   led1ADCPtr,
                uint32_t*                                                   const   led2ADCPtr,
                uint32_t*                                                   const   led3ADCPtr,
                uint32_t*                                                   const   led4ADCPtr,
        const   uint8_t                                                             toReadSampleAmount,
                uint8_t*                                                    const   readedSampleAmountPtr);

/**
 * Get chip error flag.
 * NOTE: internal error flag are not cleared. For that, a clear function call is needed.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       errorFlagPtr            output error flag struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX86916GetErrorFlag(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                tommRoC_hw_devices_sensor_hrspo2_max86916_error_flag_t*     const   errorFlagPtr);

/**
 * Clear chip error flag.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX86916ClearErrorFlag(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

/**
 * Sleep (shutdown)/wake (wakeup) chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX86916Sleep(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHRSpO2MAX86916Wake(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr);

#endif
