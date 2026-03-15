
#ifndef TOMMROC_HW_DEVICES_COMM_NFC_PN71x0_H_
#define TOMMROC_HW_DEVICES_COMM_NFC_PN71x0_H_

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

#include "comm/NFC/tommRoCHwCommNFC.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Compatible device I2C addresses.
#define TOMMROC_HW_DEVICES_COMM_NFC_PN7120_I2C_7_BIT_ADDRESS_I2CADR0_PIN_GND                (0b0101000)
#define TOMMROC_HW_DEVICES_COMM_NFC_PN7120_I2C_7_BIT_ADDRESS_I2CADR0_PIN_VDD                (0b0101001)

// Compatible device I2C addresses.
#define TOMMROC_HW_DEVICES_COMM_NFC_PN7150_I2C_7_BIT_ADDRESS_I2CADR1_I2CADR0_PIN_GND_GND    (0b0101000)
#define TOMMROC_HW_DEVICES_COMM_NFC_PN7150_I2C_7_BIT_ADDRESS_I2CADR1_I2CADR0_PIN_GND_VDD    (0b0101001)
#define TOMMROC_HW_DEVICES_COMM_NFC_PN7150_I2C_7_BIT_ADDRESS_I2CADR1_I2CADR0_PIN_VDD_GND    (0b0101010)
#define TOMMROC_HW_DEVICES_COMM_NFC_PN7150_I2C_7_BIT_ADDRESS_I2CADR1_I2CADR0_PIN_VDD_VDD    (0b0101011)


// Device data.
#define TOMMROC_HW_DEVICES_COMM_NFC_PN71x0_DEVICE_DATA_SIZE                                 (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                                                TOMMROC_UTIL_BOOL_SIZE      +   \
                                                                                                TOMMROC_UTIL_BOOL_SIZE      +   \
                                                                                                TOMMROC_UTIL_BOOL_SIZE          )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Configuration structure.
typedef struct {

    // NFC card emulate mode status
    tommRoC_util_enabled_status_enum_t  cardEmuModeStatus;

    // NFC P2P mode status
    tommRoC_util_enabled_status_enum_t  p2pModeStatus;

    // Reader/Writer mode status
    tommRoC_util_enabled_status_enum_t  rwModeStatus;

} tommRoC_hw_devices_comm_nfc_pn71x0_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_nfc_pn71x0_config_t__   \
{                                                               \
    /* .cardEmuModeStatus */    TOMMRO_C_UTIL_DISABLED,         \
    /* .p2pModeStatus */        TOMMRO_C_UTIL_DISABLED,         \
    /* .rwModeStatus */         TOMMRO_C_UTIL_DISABLED,         \
}


// On discovery callback functions type definition.
typedef void (*tommRoC_hw_devices_comm_nfc_pn71x0_on_discovery_cb_funct_t)(
        const   tommRoC_hw_bus_device_t*        const   busDevicePtr,
        const   tommRoC_hw_comm_nfc_device_t*   const   nfcDevicePtr);


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_COMM_NFC_PN71x0_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_comm_nfc_pn71x0_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCPN71x0InitI2C(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCPN71x0AttachDeviceData(
        const   tommRoC_hw_devices_comm_nfc_pn71x0_device_data_t*   const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        VENLow                  set VEN pin low function pointer.
 * param[in]        VENHigh                 set VEN pin high function pointer.
 * param[in]        IRQStatus               get IRQ pin status function pointer.
 * param[in]        configPtr               chip configuration pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCPN71x0Start(
        const   tommRoC_hw_gpio_set_cb_t                                    VENLow,
        const   tommRoC_hw_gpio_set_cb_t                                    VENHigh,
        const   tommRoC_hw_gpio_get_cb_t                                    IRQStatus,
        const   tommRoC_hw_devices_comm_nfc_pn71x0_config_t*        const   configPtr,
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);


/******************* NFC dedicated API. */

/**
 * Start NFC discovery loop for remote NFC device detection.
 *
 * param[in]        modeTechPtr             NFC technologies to look for array pointer.
 * param[in]        modeTechAmount          NFC technologies to look for array elements amount.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCPN71x0StartDiscovery(
        const   tommRoC_hw_comm_nfc_mode_tech_t*                    const   modeTechPtr,
        const   uint8_t                                                     modeTechAmount,
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Stop NFC discovery loop for remote NFC device detection.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCPN71x0StopDiscovery(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Wait until remote NFC device is discovered (with callback version).
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        timeoutMsec             wait timeout [msec].
 * param[in]        cardEmuFunctCb          on NFC card emulate discovery callback pointer.
 * param[in]        p2pFunctCb              on NFC P2P discovery callback pointer.
 * param[in]        rwFunctCb               on NFC RW discovery callback pointer.
 * param[in]        wrongFunctCb            on wrong discovery callback pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCPN71x0WaitForDiscovery(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   uint32_t                                                    timeoutMsec,
        const   tommRoC_hw_devices_comm_nfc_pn71x0_on_discovery_cb_funct_t  cardEmuFunctCb,
        const   tommRoC_hw_devices_comm_nfc_pn71x0_on_discovery_cb_funct_t  p2pFunctCb,
        const   tommRoC_hw_devices_comm_nfc_pn71x0_on_discovery_cb_funct_t  rwFunctCb,
        const   tommRoC_hw_devices_comm_nfc_pn71x0_on_discovery_cb_funct_t  wrongFunctCb);

/**
 * Power OFF/wake chip.
 * NOTE: at power off, all configuration will be loosed at next wake.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCPN71x0PowerOFF(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCPN71x0Wake(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);


/******************* Reader/Writer dedicated API. */

/**
 * Write NDEF message to remote tag.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        nfcDevicePtr            NFC remote device properties pointer.
 * param[in]        ndefMessagePtr          NDEF message pointer.
 * param[in]        ndefMessageLen          NDEF message length [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCPN71x0RWWriteNDEF(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   tommRoC_hw_comm_nfc_device_t*                       const   nfcDevicePtr,
        const   uint8_t*                                            const   ndefMessagePtr,
        const   uint16_t                                                    ndefMessageLen);

/**
 * Read NDEF message from remote tag.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        nfcDevicePtr            NFC remote device properties pointer.
 * param[out]       ndefMessagePtr          output NDEF message pointer.
 * param[in]        ndefMessageMaxSize      output NDEF message buffer max size [byte].
 * param[out]       ndefMessageLenPtr       output NDEF message length pointer [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCPN71x0RWReadNDEF(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   tommRoC_hw_comm_nfc_device_t*                       const   nfcDevicePtr,
                uint8_t*                                            const   ndefMessagePtr,
        const   uint16_t                                                    ndefMessageMaxSize,
                uint16_t*                                           const   ndefMessageLenPtr);

/**
 * Write command/read answer to/from remote tag.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        commandPtr              command pointer.
 * param[in]        commandLen              command length [byte].
 * param[out]       answerPtr               output answer pointer.
 * param[in]        answerMaxSize           output answer buffer max size [byte].
 * param[out]       answerLenPtr            output answer length pointer [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCPN71x0RWTagCmd(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   uint8_t*                                            const   commandPtr,
        const   uint16_t                                                    commandLen,
                uint8_t*                                            const   answerPtr,
        const   uint16_t                                                    answerMaxSize,
                uint16_t*                                           const   answerLenPtr);

/******************* Card Emulation dedicated API. */


/******************* P2P dedicated API. */

/**
 * Write a message to remote P2P device.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        nfcDevicePtr            NFC remote device properties pointer.
 * param[in]        dataPtr                 message data pointer.
 * param[in]        dataLen                 message data length [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCPN71x0P2PWrite(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   tommRoC_hw_comm_nfc_device_t*                       const   nfcDevicePtr,
        const   uint8_t*                                            const   dataPtr,
        const   uint16_t                                                    dataLen);

/**
 * Read a message from remote P2P device.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        nfcDevicePtr            NFC remote device properties pointer.
 * param[in]        timeoutMsec             wait timeout [msec].
 * param[out]       dataPtr                 output message data pointer.
 * param[in]        dataMaxSize             output message data buffer max size [byte].
 * param[out]       dataLenPtr              output message data length pointer [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCPN71x0P2PRead(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   tommRoC_hw_comm_nfc_device_t*                       const   nfcDevicePtr,
        const   uint32_t                                                    timeoutMsec,
                uint8_t*                                            const   dataPtr,
        const   uint16_t                                                    dataMaxSize,
                uint16_t*                                           const   dataLenPtr);

#endif
