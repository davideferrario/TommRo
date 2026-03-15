
#ifndef TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_H_
#define TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_H_

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

// Device data.
#define TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_DEVICE_DATA_SIZE        (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                            TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                            TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                            TOMMROC_UTIL_FUNCT_PTR_SIZE     )

// Node Label/Node ID maximum data size [byte]
#define TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_NODE_LABEL_MAX_SIZE_BYTE    (16)
#define TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_NODE_ID_MAX_SIZE_BYTE       (8)

// Maximum user data size [byte]
#define TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_USER_DATA_MAX_SIZE_BYTE     (34)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Position measurement modes
typedef enum {

    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_MEAS_MODE_TWR = 0,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_MEAS_MODE_TDOA

} tommRoC_hw_devices_comm_uwb_ble_dwm1001_meas_mode_enum_t;

// UWB modes
typedef enum {

    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_MODE_OFF = 0,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_MODE_PASSIVE,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_MODE_ACTIVE

} tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_mode_enum_t;


// As tag configuration structure.
typedef struct {

    tommRoC_util_enabled_status_enum_t                          fwUpdateEn;
    tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_mode_enum_t     uwbMode;
    tommRoC_util_enabled_status_enum_t                          encEn;
    tommRoC_util_enabled_status_enum_t                          bleEn;
    tommRoC_util_enabled_status_enum_t                          ledEn;
    tommRoC_util_enabled_status_enum_t                          locEngineEn;
    tommRoC_util_enabled_status_enum_t                          lowPowerEn;
    tommRoC_util_enabled_status_enum_t                          accelEn;
    tommRoC_hw_devices_comm_uwb_ble_dwm1001_meas_mode_enum_t    measMode;

} tommRoC_hw_devices_comm_uwb_ble_dwm1001_tag_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_tag_config_t__              \
{                                                                                   \
    /* .fwUpdateEn */   TOMMRO_C_UTIL_ENABLED,                                      \
    /* .uwbMode */      TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_MODE_ACTIVE,    \
    /* .encEn */        TOMMRO_C_UTIL_DISABLED,                                     \
    /* .bleEn */        TOMMRO_C_UTIL_ENABLED,                                      \
    /* .ledEn */        TOMMRO_C_UTIL_DISABLED,                                     \
    /* .locEngineEn */  TOMMRO_C_UTIL_ENABLED,                                      \
    /* .lowPowerEn */   TOMMRO_C_UTIL_ENABLED,                                      \
    /* .accelEn */      TOMMRO_C_UTIL_ENABLED,                                      \
    /* .measMode */     TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_MEAS_MODE_TWR,      \
}


/**
 * From DW1000 manual:
 * The transmitter output power can be adjusted using this Register file: 0x1E – Transmit Power Control.
 * This contains four octets each of which specifies a separate transmit power setting.
 * These separate settings are applied by the IC in one of two ways.
 * These two alternatives are described in:
 * - section 7.2.31.2 – Smart Transmit Power Control and
 * - section 7.2.31.3 – Manual Transmit Power Control below.
 * The choice between these two alternatives is selected by the setting of the DIS_STXP bit in Register file: 0x04 – System Configuration.
 *
 * Each power control octet, in Register file: 0x1E – Transmit Power Control, specifies the power as a
 * combination of a coarse gain parameter and a fine gain parameter.
 */

typedef enum {

    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_COARSE_GAIN_15_0_DB = 0,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_COARSE_GAIN_12_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_COARSE_GAIN_10_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_COARSE_GAIN_7_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_COARSE_GAIN_5_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_COARSE_GAIN_2_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_COARSE_GAIN_0_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_COARSE_GAIN_OFF,

} tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_config_tx_power_coarse_gain_enum_t;

typedef enum {

    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_0_0_DB = 0,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_0_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_1_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_1_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_2_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_2_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_3_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_3_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_4_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_4_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_5_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_5_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_6_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_6_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_7_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_7_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_8_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_8_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_9_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_9_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_10_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_10_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_11_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_11_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_12_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_12_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_13_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_13_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_14_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_14_5_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_15_0_DB,
    TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_UWB_CONFIG_TX_POWER_FINE_GAIN_15_5_DB,

} tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_config_tx_power_fine_gain_enum_t;

typedef struct {

    tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_config_tx_power_coarse_gain_enum_t  coarseGain;
    tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_config_tx_power_fine_gain_enum_t    fineGain;

} tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_config_tx_power_gain_t;

/**
 * From DW1000 manual:
 * The gain control range is 30.5 dB consisting of 32 fine (mixer gain) control steps of 0.5 dB
 * and 7 coarse (DA gain) steps of 2.5 dB, see Figure 26.
 * For the best spectral shape the coarse gain should be adjusted first.
 */
typedef float tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_config_tx_power_gain_numeric_t;


// UWB configuration structure.
typedef struct {

    uint8_t                                                             pgDelay;        // Transmitter Calibration – Pulse Generator Delay
    tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_config_tx_power_gain_t  txPowerGain[4]; // TX Power Control

} tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_config_t;


// Chip version structure.
typedef struct {

    uint8_t fwMaj,  fwMin,  fwPatch,    fwVar;
    uint8_t cfgMaj, cfgMin, cfgPatch,   cfgVar;
    uint8_t hwMaj,  hwMin,  hwPatch,    hwVar;

} tommRoC_hw_devices_comm_uwb_ble_dwm1001_version_t;


// Chip status flag structure.
TOMMROC_BIT_FIELD_U8_8_FIELD(
        locReady,                       1,  // New location data are ready
        uwbmacJoined,                   1,  // Node is connected to UWB network
        bhDataReady,                    1,  // UWB MAC backhaul data ready
        bhStatusChanged,                1,  // UWB MAC status has changed, used in backhaul
        uwbScanReady,                   1,  // UWB scan results are ready
        usrDataReady,                   1,  // User data over UWB received
        usrDataSent,                    1,  // User data over UWB sent
        fwupInProgress,                 1,  // Firmware update is in progress
        tommRoC_hw_devices_comm_uwb_ble_dwm1001_status_flag_t);


// Position structure.
typedef struct {

    int32_t                             xCoordMm;   // X coordinate [millimeters]
    int32_t                             yCoordMm;   // Y coordinate [millimeters]
    int32_t                             zCoordMm;   // Z coordinate [millimeters]
    tommRoC_unit_measure_percentage_t   quality;    // Quality factor [%]

} tommRoC_hw_devices_comm_uwb_ble_dwm1001_position_t;

#define __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_position_t__    \
{                                                                       \
    /* .xCoordMm */ 0,                                                  \
    /* .yCoordMm */ 0,                                                  \
    /* .zCoordMm */ 0,                                                  \
    /* .quality */  0.0f,                                               \
}


// For location structure.
typedef struct {

    uint16_t                            UWBAddress; // UWB address
    uint32_t                            distance;   // Distance [millimeters]
    tommRoC_unit_measure_percentage_t   quality;    // Quality factor [%]

} tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t;

#define __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t__ \
{                                                                           \
    /* .UWBAddress */   0,                                                  \
    /* .distance */     0,                                                  \
    /* .quality */      0.0f,                                               \
}

// Location structure.
typedef struct {

    tommRoC_hw_devices_comm_uwb_ble_dwm1001_position_t          position;           // Position
    uint8_t                                                     distCnt;            // Number of distances to the anchors,
    tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t   anchorsDistPos[15]; // Anchors distances/position.

} tommRoC_hw_devices_comm_uwb_ble_dwm1001_location_t;

#define __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_location_t__                                        \
{                                                                                                           \
    /* .position */         __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_position_t__,                   \
    /* .distCnt */          0,                                                                              \
    /* .anchorsDistPos */   {   __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t__,        \
                                __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t__,        \
                                __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t__,        \
                                __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t__,        \
                                __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t__,        \
                                __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t__,        \
                                __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t__,        \
                                __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t__,        \
                                __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t__,        \
                                __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t__,        \
                                __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t__,        \
                                __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t__,        \
                                __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t__,        \
                                __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t__,        \
                                __EMPTY_tommRoC_hw_devices_comm_uwb_ble_dwm1001_anchor_distance_t__,    },  \
}


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_COMM_UWB_BLE_DWM1001_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_comm_uwb_ble_dwm1001_device_data_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init bus device as for SPI master bus.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        chipSelect              chip select function pointer.
 * param[in]        chipDeSelect            chip de-select function pointer.
 * param[in]        busHandlerPtr           bus pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       specificSlavePtr        output specific SPI slave pointer [needed as static because linked by bus device].
 * param[out]       busDevicePtr            output bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001InitSPI(
        const   tommRoC_hw_gpio_set_cb_t                                        chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                                        chipDeSelect,
        const   tommRoC_hw_bus_t*                                       const   busHandlerPtr,
        const   tommRoC_guard_t*                                        const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t*             const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001InitUART(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001AttachDeviceData(
        const   tommRoC_hw_devices_comm_uwb_ble_dwm1001_device_data_t*  const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        resetLow                set RESETn pin low function pointer.
 * param[in]        resetHigh               set RESETn pin high function pointer.
 * param[in]        btWakeUpLow             set BT_WAKE_UP pin low function pointer.
 * param[in]        btWakeUpHigh            set BT_WAKE_UP pin high function pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001Start(
        const   tommRoC_hw_gpio_set_cb_t                                        resetLow,
        const   tommRoC_hw_gpio_set_cb_t                                        resetHigh,
        const   tommRoC_hw_gpio_set_cb_t                                        btWakeUpLow,
        const   tommRoC_hw_gpio_set_cb_t                                        btWakeUpHigh,
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Config chip as TAG.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        configPtr               device configuration pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001ConfigAsTAG(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_devices_comm_uwb_ble_dwm1001_tag_config_t*   const   configPtr);

/**
 * Get TAG config.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       configPtr               device configuration pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001ConfigTAGGet(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                tommRoC_hw_devices_comm_uwb_ble_dwm1001_tag_config_t*   const   configPtr);

/**
 * Get version.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       versionPtr              version pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001GetVersion(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                tommRoC_hw_devices_comm_uwb_ble_dwm1001_version_t*      const   versionPtr);

/**
 * Set UWB configuration.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        uwbConfigPtr            device UWB configuration pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001UWBCfgSet(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_config_t*   const   uwbConfigPtr);

/**
 * Get UWB configuration.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       uwbConfigPtr            device UWB configuration pointer.
 * param[out]       uwbConfigCompensatedPtr device UWB configuration compensated pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001UWBCfgGet(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_config_t*   const   uwbConfigPtr,
                tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_config_t*   const   uwbConfigCompensatedPtr);

/**
 * Tx power gain to Tx power gain numeric conversion.
 *
 * param[in]        txPowerGainPtr          tx power gain structure pointer.
 * param[out]       txPowerGainNumericPtr   tx power gain numeric structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001TxPowerGainToTxPowerGainNumeric(
        const   tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_config_tx_power_gain_t*         const   txPowerGainPtr,
                tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_config_tx_power_gain_numeric_t* const   txPowerGainNumericPtr);

/**
 * Tx power gain to Tx power gain numeric conversion.
 *
 * param[in]       txPowerGainNumericPtr   tx power gain numeric structure pointer.
 * param[out]        txPowerGainPtr          tx power gain structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001TxPowerGainNumericToTxPowerGain(
        const   tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_config_tx_power_gain_numeric_t* const   txPowerGainNumericPtr,
                tommRoC_hw_devices_comm_uwb_ble_dwm1001_uwb_config_tx_power_gain_t*         const   txPowerGainPtr);

/**
 * Get status flag.
 * NOTE: All flags are cleared after the call.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       statusFlagPtr           status flag pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001GetStatusFlag(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                tommRoC_hw_devices_comm_uwb_ble_dwm1001_status_flag_t*  const   statusFlagPtr);

/**
 * Get position.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       positionPtr             position pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001GetPosition(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                tommRoC_hw_devices_comm_uwb_ble_dwm1001_position_t*     const   positionPtr);

/**
 * Get location.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       locationPtr             location pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001GetLocation(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                tommRoC_hw_devices_comm_uwb_ble_dwm1001_location_t*     const   locationPtr);

/**
 * Get node label.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       nodeLabelBufferPtr      output node label buffer pointer.
 * param[in]        nodeLabelBufferSize     output node label buffer size.
 * param[out]       nodeLabelLengthPtr      node label length pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001GetNodeLabel(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                char*                                                   const   nodeLabelBufferPtr,
        const   uint8_t                                                         nodeLabelBufferSize,
                uint8_t*                                                const   nodeLabelLengthPtr);

/**
 * Set node label.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        nodeLabelStrPtr         node label string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001SetNodeLabel(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   char*                                                   const   nodeLabelStrPtr);

/**
 * Get node ID (UWB address).
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       nodeIDBufferPtr         output node ID buffer pointer.
 * param[in]        nodeIDBufferSize        output node ID buffer size.
 * param[out]       nodeIDLengthPtr         node ID length pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001GetNodeID(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                uint8_t*                                                const   nodeIDBufferPtr,
        const   uint8_t                                                         nodeIDBufferSize,
                uint8_t*                                                const   nodeIDLengthPtr);

/**
 * Get network identifier.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       panIDPtr                output network identifier pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001GetPanID(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                uint16_t*                                               const   panIDPtr);

/**
 * Set network identifier.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        panID                   network identifier.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001SetPanID(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   uint16_t                                                        panID);

/**
 * Get position update rate.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       updRateMsecPtr          output update rate [msec] pointer.
 * param[out]       updRateStatMsecPtr      output update rate stationary [msec] pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001GetUpdRate(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                uint32_t*                                               const   updRateMsecPtr,
                uint32_t*                                               const   updRateStatMsecPtr);

/**
 * Set position update rate.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        updRateMsec             update rate [msec].
 * param[in]        updRateStatMsec         update rate stationary [msec].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001SetUpdRate(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   uint32_t                                                        updRateMsec,
        const   uint32_t                                                        updRateStatMsec);

/**
 * Writes user data to be sent through uplink to the network.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        writeBufferPtr          user data buffer pointer.
 * param[in]        writeBufferLen          user data buffer length.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001UsrDataWrite(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   uint8_t*                                                const   writeBufferPtr,
        const   uint8_t                                                         writeBufferLen);

/**
 * Reads downlink user data from the node.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        readBufferSize          output data buffer size.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001UsrDataRead(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
                uint8_t*                                                const   readBufferPtr,
        const   uint8_t                                                         readBufferSize,
                uint8_t*                                                const   readedAmountPtr);

/**
 * BLE Sleep/wake chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001BLESleep(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001BLEWake(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Sleep/wake chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001Sleep(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBBLEDWM1001Wake(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

#endif
