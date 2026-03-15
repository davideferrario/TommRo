
#ifndef TOMMROC_HW_DEVICES_COMM_NFC_NT3H2x11_H_
#define TOMMROC_HW_DEVICES_COMM_NFC_NT3H2x11_H_

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
#define TOMMROC_HW_DEVICES_COMM_NFC_NT3H2x11_I2C_7_BIT_ADDRESS  (0b1010101)


// NT3H2x11 UID size [byte]
#define TOMMROC_HW_DEVICES_COMM_NFC_NT3H2x11_UID_SIZE_BYTE                  (7)

/**
 * From the NFC perspective, user EEPROM memory is composed by 222 (0xDE)
 * 4 bytes size pages (for a total of 888 bytes), starting at page address
 * 0x04 and ending at page address 0xE1 (refer to datasheet).
 */
#define TOMMROC_HW_DEVICES_COMM_NFC_NT3H2x11_USER_MEMORY_START_PAGE_ADDRESS (0x04)
#define TOMMROC_HW_DEVICES_COMM_NFC_NT3H2x11_USER_MEMORY_END_PAGE_ADDRESS   (0xE1)

// Device data.
#define TOMMROC_HW_DEVICES_COMM_NFC_NT3H2x11_DEVICE_DATA_SIZE   (   TOMMROC_UTIL_U8_SIZE    +   \
                                                                    16                          )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Device (NT3H2111 or NT3H2211) type.
typedef enum {

    // Device is NT3H2111 (1k memory) type
    TOMMROC_HW_DEVICES_COMM_NFC_NT3H2x11_NT3H2111_TYPE = 0,

    // Device is NT3H2211 (2k memory) type
    TOMMROC_HW_DEVICES_COMM_NFC_NT3H2x11_NT3H2211_TYPE,

} tommRoC_hw_devices_comm_nfc_nt3h2x11_type_enum_t;


// Configuration structure.
typedef struct {

    // Device (NT3H2111 or NT3H2211) type.
    tommRoC_hw_devices_comm_nfc_nt3h2x11_type_enum_t    type;

} tommRoC_hw_devices_comm_nfc_nt3h2x11_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_nfc_nt3h2x11_config_t__     \
{                                                                   \
    /* .type */ TOMMROC_HW_DEVICES_COMM_NFC_NT3H2x11_NT3H2111_TYPE, \
}


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_COMM_NFC_NT3H2x11_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_comm_nfc_nt3h2x11_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCNT3H2x11InitI2C(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCNT3H2x11AttachDeviceData(
        const   tommRoC_hw_devices_comm_nfc_nt3h2x11_device_data_t* const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        configPtr               chip configuration pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCNT3H2x11Start(
        const   tommRoC_hw_devices_comm_nfc_nt3h2x11_config_t*      const   configPtr,
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Get tag UID.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       uidBufferPtr            UID buffer pointer.
 * param[in]        uidBufferSize           UID buffer size [has to be >= 7].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCNT3H2x11GetUID(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                uint8_t*                                            const   uidBufferPtr,
        const   uint8_t                                                     uidBufferSize);

/**
 * Set AUTH0 value (refer to datasheet).
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        auth0                   AUTH0 value.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCNT3H2x11SetAUTH0(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   uint8_t                                                     auth0);












tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCNT3H2x11GetCC(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
                uint8_t*                    const   CCPtr,
        const   uint16_t                            CCSize);
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCNT3H2x11GetAUTH0(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
                uint8_t*                    const   auth0Ptr);
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCNT3H2x11GetRfLocked(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
                bool*                       const   isRfLockedPtr);
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCNT3H2x11GetRfFieldPresent(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
                bool*                       const   isRfFieldPresentPtr);
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCNT3H2x11SetPWDPACK(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   uint32_t                            PWD,
        const   uint16_t                            PACK);










/******************* Memory EEPROM management */

/**
 * Write buffer to EEPROM.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        startAddress            EEPROM start address to write [start from address 0].
 * param[in]        writeBufferPtr          data buffer.
 * param[in]        writeBufferLen          data buffer length.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCNT3H2x11EEPROMWriteBuffer(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   uint32_t                                                    startAddress,
        const   uint8_t*                                            const   writeBufferPtr,
        const   uint16_t                                                    writeBufferLen);

/**
 * Read buffer from EEPROM.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        startAddress            EEPROM start address to read [start from address 0].
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCNT3H2x11EEPROMReadBuffer(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   uint32_t                                                    startAddress,
                uint8_t*                                            const   readBufferPtr,
        const   uint16_t                                                    toReadAmount);

#endif
