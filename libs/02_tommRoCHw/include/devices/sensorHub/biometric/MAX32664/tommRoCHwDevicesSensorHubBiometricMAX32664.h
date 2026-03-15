
#ifndef TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_H_
#define TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_H_

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
#define TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_I2C_7_BIT_ADDRESS  (0b1010101)


// Device data.
#define TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_SAMPLES_MAX_AMOUNT                 (25)
#define TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_DEVICE_DATA_BPM_BUFFER_SIZE_BYTE   (76)
#define TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_DEVICE_DATA_SIZE                   (   TOMMROC_UTIL_FUNCT_PTR_SIZE                 +   \
                                                                                                TOMMROC_UTIL_FUNCT_PTR_SIZE                 +   \
                                                                                                TOMMROC_UTIL_FUNCT_PTR_SIZE                 +   \
                                                                                                TOMMROC_UTIL_FUNCT_PTR_SIZE                 +   \
                                                                                                TOMMROC_UTIL_FUNCT_PTR_SIZE                 +   \
                                                                                                TOMMROC_UTIL_FUNCT_PTR_SIZE                 +   \
                                                                                                TOMMROC_UTIL_FUNCT_PTR_SIZE                 +   \
                                                                                                TOMMROC_UTIL_FUNCT_PTR_SIZE                 +   \
                                                                                                TOMMROC_UTIL_U8_SIZE                        +   \
                                                                                                TOMMROC_UTIL_U8_SIZE                        +   \
                                                                                                TOMMROC_UNIT_MEASURE_KBYTE_TO_BYTE(8) + 16  +   \
                                                                                                (TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_SAMPLES_MAX_AMOUNT * TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_DEVICE_DATA_BPM_BUFFER_SIZE_BYTE))

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_MODE_SIMPLE_HR_SPo2 = 0,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_MODE_WHRM,

} tommRoC_hw_devices_sensor_hub_biometric_max32664_mode_enum_t;

typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_OP_MODE_CONTINUOUS_HRM_CONTINUOUS_SPo2 = 0,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_OP_MODE_CONTINUOUS_HRM_ONE_SHOT_SPo2,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_OP_MODE_CONTINUOUS_HRM,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_OP_MODE_SAMPLED_HRM,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_OP_MODE_SAMPLED_HRM_ONE_SHOT_SPo2,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_OP_MODE_ACTIVITY_TRACKING_ONLY,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_OP_MODE_SPo2_CALIBRATION,

} tommRoC_hw_devices_sensor_hub_biometric_max32664_op_mode_enum_t;

typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_OUTPUT_MODE_OUTPUT_FORMAT_PAUSE = 0,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_OUTPUT_MODE_OUTPUT_FORMAT_SENSOR_DATA,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_OUTPUT_MODE_OUTPUT_FORMAT_ALGORITHM_DATA,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_OUTPUT_MODE_OUTPUT_FORMAT_SENSOR_AND_ALGORITHM_DATA,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_OUTPUT_MODE_OUTPUT_FORMAT_SAMPLE_COUNTER_BYTE_SENSOR_DATA,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_OUTPUT_MODE_OUTPUT_FORMAT_SAMPLE_COUNTER_BYTE_ALGORITHM_DATA,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_OUTPUT_MODE_OUTPUT_FORMAT_SAMPLE_COUNTER_BYTE_SENSOR_AND_ALGORITHM_DATA,

} tommRoC_hw_devices_sensor_hub_biometric_max32664_output_mode_enum_t;

typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_ACTIVITY_CLASS_REST = 0,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_ACTIVITY_CLASS_OTHER,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_ACTIVITY_CLASS_WALK,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_ACTIVITY_CLASS_RUN,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_ACTIVITY_CLASS_BIKE,

} tommRoC_hw_devices_sensor_hub_biometric_max32664_activity_class_enum_t;

typedef enum {

    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_SCD_STATE_UNDETECTED = 0,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_SCD_STATE_OFF_SKIN,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_SCD_STATE_ON_SOME_SUBJECT,
    TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_SCD_STATE_ON_SKIN,

} tommRoC_hw_devices_sensor_hub_biometric_max32664_SCD_state_enum_t;


typedef struct {

    tommRoC_hw_devices_sensor_hub_biometric_max32664_mode_enum_t        mode;
    tommRoC_hw_devices_sensor_hub_biometric_max32664_op_mode_enum_t     opMode;
    tommRoC_hw_devices_sensor_hub_biometric_max32664_output_mode_enum_t outputMode;
    tommRoC_util_enabled_status_enum_t                                  accControl;
    uint8_t                                                             sampleReportPeriod; // 0x01 to 0xFF: LSB is 40msec.

} tommRoC_hw_devices_sensor_hub_biometric_max32664_config_t;

#define __EMPTY_tommRoC_hw_devices_sensor_hub_biometric_max32664_config_t__                                                 \
{                                                                                                                           \
    /* .mode */                 TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_MODE_SIMPLE_HR_SPo2,                       \
    /* .opMode */               TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_OP_MODE_CONTINUOUS_HRM_CONTINUOUS_SPo2,    \
    /* .outputMode */           TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_OUTPUT_MODE_OUTPUT_FORMAT_SENSOR_DATA,     \
    /* .accControl */           TOMMRO_C_UTIL_DISABLED,                                                                     \
    /* .sampleReportPeriod */   1,                                                                                          \
}


typedef union {

    struct {

        uint16_t    heartRate;  // Heart rate
        uint8_t     confidence; // 0-100%
        uint16_t    SpO2;       // SpO2 value 0-100%
        uint8_t     status;     // 0: Success, 1: Not Ready, 2: Object Detected, 3: Finger Detected

    } simple_hr_spo2;

    struct {

        uint32_t                                                                PPG1;                   // Green counter
        uint32_t                                                                PPG2;                   // N/A
        uint32_t                                                                PPG3;                   // N/A
        uint32_t                                                                PPG4;                   // Green2 counter
        uint32_t                                                                PPG5;                   // IR LED counter
        uint32_t                                                                PPG6;                   // Red LED counter
        int16_t                                                                 accelX;                 // Two's complement. LSB = 0.001g
        int16_t                                                                 accelY;                 // Two's complement. LSB = 0.001g
        int16_t                                                                 accelZ;                 // Two's complement. LSB = 0.001g
        tommRoC_hw_devices_sensor_hub_biometric_max32664_op_mode_enum_t         current_operating_mode; // Current operation mode:
        uint16_t                                                                HR;                     // Heart rate
        uint8_t                                                                 HRConfidence;           // 0-100%
        uint16_t                                                                RR;                     // Inter-beat interval in ms
        uint8_t                                                                 RRConfidence;           // 0-100%
        tommRoC_hw_devices_sensor_hub_biometric_max32664_activity_class_enum_t  activityClass;          // Activity class (Rest/Other/Walk/Run/Bike)
        uint32_t                                                                totalWalkSteps;         // Total number of walking steps since the last reset
        uint32_t                                                                totalRunSteps;          // Total number of running steps since the last reset
        uint32_t                                                                totalEnergyExpKcal;     // Total energy expenditure since the last reset [kcal]
        uint32_t                                                                totalAMRKcal;           // Total active energy expenditure since the last reset [kcal]
        uint8_t                                                                 is_led_cur1_adj;
        uint16_t                                                                adj_led_cur1;
        uint8_t                                                                 is_led_cur2_adj;
        uint16_t                                                                adj_led_cur2;
        uint8_t                                                                 is_led_cur3_adj;
        uint16_t                                                                adj_led_cur3;
        uint8_t                                                                 is_int_time_adj;
        uint8_t                                                                 t_int_code;
        uint8_t                                                                 is_f_smp_adj;
        uint8_t                                                                 adj_f_smp;
        uint8_t                                                                 smp_ave;
        uint8_t                                                                 hrm_afe_state;
        uint8_t                                                                 is_high_motion;
        tommRoC_hw_devices_sensor_hub_biometric_max32664_SCD_state_enum_t       SCDState;           // Skin contact state (Undetected/Off skin/On some subject/On skin)
        uint16_t                                                                R;                  // SpO2 R value
        uint16_t                                                                SpO2;               // SpO2 value 0-100%
        uint8_t                                                                 SpO2Confidence;     // 0-100%
        uint8_t                                                                 percentComplete;
        uint8_t                                                                 lowSignalQualityFlag;
        uint8_t                                                                 motionFlag;
        uint8_t                                                                 lowPiFlag;
        uint8_t                                                                 unreliableRFlag;
        uint8_t                                                                 spo2State;

    } whrm;

} tommRoC_hw_devices_sensor_hub_biometric_max32664_bio_data_t;


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_SENSOR_HUB_BIOMETRIC_MAX32664_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_sensor_hub_biometric_max32664_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHubBiometricMAX32664InitI2C(
        const   uint8_t                                                                 i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                                               const   busHandlerPtr,
        const   tommRoC_guard_t*                                                const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t*                     const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHubBiometricMAX32664AttachDeviceData(
        const   tommRoC_hw_devices_sensor_hub_biometric_max32664_device_data_t* const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        RSTNPinLow              chip RESET pin low function pointer.
 * param[in]        RSTNPinHigh             chip RESET pin high function pointer.
 * param[in]        MFIOPinSetAsInput       chip MFIO pin set as input function pointer.
 * param[in]        MFIOPinSetAsOutputLow   chip MFIO pin set as output low function pointer.
 * param[in]        MFIOPinSetAsOutputHigh  chip MFIO pin set as output high function pointer.
 * param[in]        MFIOPinInputStatus      get chip MFIO pin status function pointer.
 * param[in]        MFIOPinOutputLow        chip MFIO pin low function pointer.
 * param[in]        MFIOPinOutputHigh       chip MFIO pin high function pointer.
 * param[in]        configPtr               chip configuration pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHubBiometricMAX32664Start(
        const   tommRoC_hw_gpio_set_cb_t                                                RSTNPinLow,
        const   tommRoC_hw_gpio_set_cb_t                                                RSTNPinHigh,
        const   tommRoC_hw_gpio_set_dir_cb_t                                            MFIOPinSetAsInput,
        const   tommRoC_hw_gpio_set_dir_cb_t                                            MFIOPinSetAsOutputLow,
        const   tommRoC_hw_gpio_set_dir_cb_t                                            MFIOPinSetAsOutputHigh,
        const   tommRoC_hw_gpio_get_cb_t                                                MFIOPinInputStatus,
        const   tommRoC_hw_gpio_set_cb_t                                                MFIOPinOutputLow,
        const   tommRoC_hw_gpio_set_cb_t                                                MFIOPinOutputHigh,
        const   tommRoC_hw_devices_sensor_hub_biometric_max32664_config_t*      const   configPtr,
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Read wrist heart rate algorithm data [heart rate, confidence, SpO2 and finger detected status].
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       bioDataPtr              biometric wrist heart rate algorithm data pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_ERR_SUCCESS         -> new valid algorithm result available.
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHubBiometricMAX32664ReadBioData(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
                tommRoC_hw_devices_sensor_hub_biometric_max32664_bio_data_t*    const   bioDataPtr);

/**
 * Read current firmware version.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       majorVersionPtr         firmware version major pointer.
 * param[out]       minorVersionPtr         firmware version minor pointer.
 * param[out]       revisionPtr             firmware version revision pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHubBiometricMAX32664FwVersionRead(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
                uint8_t*                                                        const   majorVersionPtr,
                uint8_t*                                                        const   minorVersionPtr,
                uint8_t*                                                        const   revisionPtr);

/**
 * Stop the algorithm.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHubBiometricMAX32664StopAlgorithm(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Chip shutdown.
 * NOTE: restart is only possible by power cycle or toggling RSTN (re-call start function)
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHubBiometricMAX32664Shutdown(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr);

/**
 * Firmware update.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        fwBufferPtr             firmware image data buffer pointer.
 * param[in]        fwBufferSize            firmware image data buffer size [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesSensorHubBiometricMAX32664FwUpdate(
        const   tommRoC_hw_bus_device_t*                                        const   busDevicePtr,
        const   uint8_t*                                                        const   fwBufferPtr,
        const   uint32_t                                                                fwBufferSize);

#endif
