
#ifndef TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_H_
#define TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_H_

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
#include "devices/comm/NFC/MFRC522/card/tommRoCHwDevicesCommNFCMFRC522Card.h"

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
#define TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_I2C_7_BIT_ADDRESS   (0b0101000)


// Device data.
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#define TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_DEVICE_DATA_SIZE    (84)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#define TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_DEVICE_DATA_SIZE    (84)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)
#define TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_DEVICE_DATA_SIZE    (160)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#define TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_DEVICE_DATA_SIZE    (160)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)
#define TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_DEVICE_DATA_SIZE    ()
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#define TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_DEVICE_DATA_SIZE    ()
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16)
#define TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_DEVICE_DATA_SIZE    ()
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)
#define TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_DEVICE_DATA_SIZE    ()
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Supported card type
typedef enum {

    TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_CARD_TYPE_MIFARE_ULTRALIGHT = 0,
    TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_CARD_TYPE_MIFARE_S50,
    TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_CARD_TYPE_MIFARE_S70,
    TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_CARD_TYPE_MIFARE_PRO_X,
    TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_CARD_TYPE_MIFARE_DESFIRE,

    TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_CARD_TYPE_UNKNOWN,

} tommRoC_hw_devices_comm_nfc_mfrc522_card_type_enum_t;


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_COMM_NFC_MFRC522_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_comm_nfc_mfrc522_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCMFRC522InitI2C(
        const   uint8_t                                                         i2c7BitSlaveAddress,
        const   tommRoC_hw_bus_t*                                       const   busHandlerPtr,
        const   tommRoC_guard_t*                                        const   guardPtr,
                tommRoC_hw_bus_device_specific_i2c_slave_t*             const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCMFRC522InitSPI(
        const   tommRoC_hw_gpio_set_cb_t                                        chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                                        chipDeSelect,
        const   tommRoC_hw_bus_t*                                       const   busHandlerPtr,
        const   tommRoC_guard_t*                                        const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t*             const   specificSlavePtr,
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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCMFRC522AttachDeviceData(
        const   tommRoC_hw_devices_comm_nfc_mfrc522_device_data_t*      const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        resetLow                set reset pin low function pointer (NULL if none).
 * param[in]        resetHigh               set reset pin high function pointer (NULL if none).
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCMFRC522Start(
        const   tommRoC_hw_gpio_set_cb_t                                        resetLow,
        const   tommRoC_hw_gpio_set_cb_t                                        resetHigh,
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);


/******************* NFC dedicated API. */

/**
 * Start card detection and wait for card.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        timeoutMsec             wait timeout [msec].
 * param[out]       cardPresentPtr          card detected flag pointer.
 * param[out]       cardTypePtr             card detected type pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommNFCMFRC522WaitForCard(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   uint32_t                                                        timeoutMsec,
                bool*                                                   const   cardPresentPtr,
                tommRoC_hw_devices_comm_nfc_mfrc522_card_type_enum_t*   const   cardTypePtr);

#endif
