
#ifndef TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_H_
#define TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_H_

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

// Unique module Serial Number size [byte]
#define TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_SERIAL_NUMBER_SIZE                (4)

// Module serial data internal buffer size [byte].
#define TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_SERIAL_DATA_INTERNAL_BUFFER_SIZE  (250)

// Device data.
#define TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_DEVICE_DATA_SIZE  (   TOMMROC_UTIL_FUNCT_PTR_SIZE                                 +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE                                 +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE                                 +   \
                                                                    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_SERIAL_NUMBER_SIZE        )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef enum {
                                                                //                  433MHz  869.75-870MHz   902-928MHz  Other frequencies   Units
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_POWER_OUTPUT_0 = 0,   // Minimum power    0       -2              -12         0                   [dBm]
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_POWER_OUTPUT_1,       //                  1       -1              -11         1                   [dBm]
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_POWER_OUTPUT_2,       //                  2       0               -10         2                   [dBm]
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_POWER_OUTPUT_3,       //                  3       1               -9          3                   [dBm]
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_POWER_OUTPUT_4,       //                  4       2               -8          4                   [dBm]
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_POWER_OUTPUT_5,       //                  5       3               -7          5                   [dBm]
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_POWER_OUTPUT_6,       //                  6       4               -6          6                   [dBm]
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_POWER_OUTPUT_7,       //                  7       5               -5          7                   [dBm]
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_POWER_OUTPUT_8,       //                  8       6               -4          8                   [dBm]
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_POWER_OUTPUT_9,       // Maximum power    9       7               -3          9                   [dBm]

    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_POWER_OUTPUT_MINIMUM = TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_POWER_OUTPUT_0,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_POWER_OUTPUT_MAXIMUM = TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_POWER_OUTPUT_9,

} tommRoC_hw_devices_comm_rf868_eric4_9_power_output_enum_t;

typedef enum {

    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_CHANNEL_0 = 0,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_CHANNEL_1,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_CHANNEL_2,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_CHANNEL_3,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_CHANNEL_4,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_CHANNEL_5,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_CHANNEL_6,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_CHANNEL_7,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_CHANNEL_8,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_CHANNEL_9,

} tommRoC_hw_devices_comm_rf868_eric4_9_channel_enum_t;

typedef enum {
                                                                    //                              ON time     Current
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_RECEIVE_POWER_SAVE_0 = 0, // No power saving (default)    100%        16mA
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_RECEIVE_POWER_SAVE_1,     //                              12.50%      2mA
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_RECEIVE_POWER_SAVE_2,     //                              6.25%       1mA
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_RECEIVE_POWER_SAVE_3,     //                              3.33%       500uA
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_RECEIVE_POWER_SAVE_4,     //                              1.56%       250uA
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_RECEIVE_POWER_SAVE_5,     //                              0.78%       125uA
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_RECEIVE_POWER_SAVE_6,     //                              0.39%       63uA
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_RECEIVE_POWER_SAVE_7,     //                              0.20%       32uA
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_RECEIVE_POWER_SAVE_8,     // Completely OFF in receive    0%          0uA
                                                                    // Only wake in transmission

} tommRoC_hw_devices_comm_rf868_eric4_9_receive_power_save_enum_t;

typedef enum {

    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_OVER_AIR_DATA_RATE_1200_BPS = 0,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_OVER_AIR_DATA_RATE_2400_BPS,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_OVER_AIR_DATA_RATE_4800_BPS,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_OVER_AIR_DATA_RATE_9600_BPS,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_OVER_AIR_DATA_RATE_19200_BPS,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_OVER_AIR_DATA_RATE_38400_BPS,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_OVER_AIR_DATA_RATE_76800_BPS,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_OVER_AIR_DATA_RATE_100000_BPS,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_OVER_AIR_DATA_RATE_250000_BPS,
    TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_OVER_AIR_DATA_RATE_500000_BPS,

} tommRoC_hw_devices_comm_rf868_eric4_9_over_air_data_rate_enum_t;

// Configuration structure.
typedef struct {

    tommRoC_hw_devices_comm_rf868_eric4_9_power_output_enum_t       powerOutput;        // RF power output
    tommRoC_hw_devices_comm_rf868_eric4_9_channel_enum_t            channel;            // Channel
    tommRoC_hw_devices_comm_rf868_eric4_9_receive_power_save_enum_t receivePowerSave;   // Receive Power save
    tommRoC_hw_devices_comm_rf868_eric4_9_over_air_data_rate_enum_t overAirDataRate;    // Over-Air data rate
    uint8_t*                                                        AESKeyPtr;          // AES KEY: must have TOMMRO_C_CRYPTO_AES_KEY_128_BIT_SIZE_BYTE size

} tommRoC_hw_devices_comm_rf868_eric4_9_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_rf868_eric4_9_config_t__                                \
{                                                                                               \
    /* .powerOutput */      TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_POWER_OUTPUT_9,               \
    /* .channel */          TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_CHANNEL_0,                    \
    /* .receivePowerSave */ TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_RECEIVE_POWER_SAVE_0,         \
    /* .overAirDataRate */  TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_OVER_AIR_DATA_RATE_38400_BPS, \
    /* .AESKeyPtr */        NULL,                                                               \
}


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_comm_rf868_eric4_9_device_data_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init bus device as for UART bus.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        busHandlerPtr           bus pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       specificPtr             output specific UART pointer [needed as static because linked by bus device].
 * param[out]       busDevicePtr            output bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRF868eRIC4_9InitUART(
        const   tommRoC_hw_bus_t*                                       const   busHandlerPtr,
        const   tommRoC_guard_t*                                        const   guardPtr,
                tommRoC_hw_bus_device_specific_uart_t*                  const   specificPtr,
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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRF868eRIC4_9AttachDeviceData(
        const   tommRoC_hw_devices_comm_rf868_eric4_9_device_data_t*    const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        resetLow                set RESET pin low function pointer (NULL if not used).
 * param[in]        resetHigh               set RESET pin high function pointer (NULL if not used).
 * param[in]        busyStatus              get BUSY pin status function pointer (NULL if not used).
 * param[in]        configPtr               chip configuration pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRF868eRIC4_9Start(
        const   tommRoC_hw_gpio_set_cb_t                                        resetLow,
        const   tommRoC_hw_gpio_set_cb_t                                        resetHigh,
        const   tommRoC_hw_gpio_get_cb_t                                        busyStatus,
        const   tommRoC_hw_devices_comm_rf868_eric4_9_config_t*         const   configPtr,
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Read module serial number.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       serialNumberPtr         serial number buffer pointer. Have to be an array of TOMMROC_HW_DEVICES_COMM_RF868_eRIC4_9_SERIAL_NUMBER_SIZE byte size.
 * param[in]        serialNumberSize        serial number buffer size [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRF868eRIC4_9SerialNumberRead(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                uint8_t*                                                const   serialNumberPtr,
        const   uint16_t                                                        serialNumberSize);

/**
 * Write buffer.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        writeBufferPtr          data buffer.
 * param[in]        writeBufferLen          data buffer length.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRF868eRIC4_9WriteBuffer(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   uint8_t*                                                const   writeBufferPtr,
        const   uint16_t                                                        writeBufferLen);

/**
 * Read buffer.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommRF868eRIC4_9ReadBuffer(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                uint8_t*                                                const   readBufferPtr,
        const   uint16_t                                                        toReadAmount,
                uint16_t*                                               const   readedAmountPtr);

#endif
