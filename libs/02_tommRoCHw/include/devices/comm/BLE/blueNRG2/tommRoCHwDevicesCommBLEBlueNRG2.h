
#ifndef TOMMROC_HW_DEVICES_COMM_BLE_BLUENRG2_H_
#define TOMMROC_HW_DEVICES_COMM_BLE_BLUENRG2_H_

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
#include "devices/comm/BLE/blueNRG2/central/tommRoCHwDevicesCommBLEBlueNRG2Central.h"
#include "devices/comm/BLE/blueNRG2/peripheral/tommRoCHwDevicesCommBLEBlueNRG2Peripheral.h"

#include "tommRoCHwBus.h"
#include "tommRoCHwBusDevice.h"
#include "tommRoCHwCommSpecificBLE.h"
#include "tommRoCHwErr.h"
#include "tommRoCHwGPIO.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Device data.
#define TOMMROC_HW_DEVICES_COMM_BLE_BLUENRG2_DEVICE_DATA_SIZE   (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE     )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/******************* Common peripheral/central BlueNRG2 for <init/start struct> definition */

typedef struct {

    tommRoC_hw_comm_ble_mac_address_t BLEMACAddress;

} tommRoC_hw_devices_comm_bluenrg2_common_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_bluenrg2_common_config_t__          \
{                                                                           \
    /* .BLEMACAddress */    __EMPTY_tommRoC_hw_comm_ble_mac_address_t__,    \
}

/******************* Peripheral specific BlueNRG2 for <init/start struct> definition */

typedef struct {

    // Common config.
    tommRoC_hw_devices_comm_bluenrg2_common_config_t commonConfig;

    // Services pointer.
    tommRoC_hw_comm_ble_private_service_t*  servicesPtr;
    // Services amount.
    uint8_t                                 servicesAmount;

} tommRoC_hw_devices_comm_bluenrg2_peripheral_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_bluenrg2_peripheral_config_t__                      \
{                                                                                           \
    /* .commonConfig */     __EMPTY_tommRoC_hw_devices_comm_bluenrg2_common_config_t__      \
    /* .servicesPtr */      NULL,                                                           \
    /* .servicesAmount */   0,                                                              \
}


/******************* Central specific BlueNRG2 for <init/start struct> definition */

typedef struct {

    // Common config.
    tommRoC_hw_devices_comm_bluenrg2_common_config_t commonConfig;

} tommRoC_hw_devices_comm_bluenrg2_central_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_bluenrg2_central_config_t__                     \
{                                                                                       \
    /* .commonConfig */     __EMPTY_tommRoC_hw_devices_comm_bluenrg2_common_config_t__  \
}


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_COMM_BLE_BLUENRG2_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_comm_bluenrg2_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommBlueNRG2InitSPI(
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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommBlueNRG2AttachDeviceData(
        const   tommRoC_hw_devices_comm_bluenrg2_device_data_t*         const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        RESETnLow               set RESETn pin low function pointer (NULL if none).
 * param[in]        RESETnHigh              set RESETn pin high function pointer (NULL if none).
 * param[in]        IRQStatus               get IRQ pin status function pointer.
 * param[in]        IRQISREnable            enable ISR on IRQ pin function pointer.
 * param[in]        IRQISRDisable           disable ISR on IRQ pin function pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommBlueNRG2Start(
        const   tommRoC_hw_gpio_set_cb_t                                        RESETnLow,
        const   tommRoC_hw_gpio_set_cb_t                                        RESETnHigh,
        const   tommRoC_hw_gpio_get_cb_t                                        IRQStatus,
        const   tommRoC_hw_gpio_common_cb_t                                     IRQISREnable,
        const   tommRoC_hw_gpio_common_cb_t                                     IRQISRDisable,
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Configure chip as BLE peripheral.
 *
 * param[in]        configPtr               peripheral configuration structure pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommBlueNRG2Peripheral(
        const   tommRoC_hw_devices_comm_bluenrg2_peripheral_config_t*   const   configPtr,
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Configure chip as BLE central.
 *
 * param[in]        configPtr               central configuration structure pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommBlueNRG2Central(
        const   tommRoC_hw_devices_comm_bluenrg2_central_config_t*      const   configPtr,
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * IRQ pin rising ISR handler.
 * NOTE: to be called directly from IRQ pin rising interrupt handler.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommBlueNRG2IRQRisingISR(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Processing chip event received from HCI interface.
 * NOTE: it must be called outside ISR.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommBlueNRG2Process(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr);

#endif
