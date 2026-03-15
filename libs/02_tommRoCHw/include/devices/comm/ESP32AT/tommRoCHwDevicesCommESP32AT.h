
#ifndef TOMMROC_HW_DEVICES_COMM_ESP32_AT_H_
#define TOMMROC_HW_DEVICES_COMM_ESP32_AT_H_

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
#include "devices/comm/ESP32AT/BLE/tommRoCHwDevicesCommESP32ATBLE.h"
#include "devices/comm/ESP32AT/bluetooth/tommRoCHwDevicesCommESP32ATBluetooth.h"
#include "devices/comm/ESP32AT/HTTP/tommRoCHwDevicesCommESP32ATHTTP.h"
#include "devices/comm/ESP32AT/MQTT/tommRoCHwDevicesCommESP32ATMQTT.h"
#include "devices/comm/ESP32AT/TCPIP/tommRoCHwDevicesCommESP32ATTCPIP.h"
#include "devices/comm/ESP32AT/WiFi/tommRoCHwDevicesCommESP32ATWiFi.h"

#include "comm/tommRoCHwComm.h"

#include "tommRoCHwBus.h"
#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"
#include "tommRoCHwNet.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Device data.
#define TOMMROC_HW_DEVICES_COMM_ESP32_AT_DEVICE_DATA_SIZE   (TOMMROC_UTIL_FUNCT_PTR_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_COMM_ESP32_AT_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_comm_esp32_at_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATInitUART(
        const   tommRoC_hw_bus_t*                               const   busHandlerPtr,
        const   tommRoC_guard_t*                                const   guardPtr,
                tommRoC_hw_bus_device_specific_uart_t*          const   specificPtr,
                tommRoC_hw_bus_device_t*                        const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATAttachDeviceData(
        const   tommRoC_hw_devices_comm_esp32_at_device_data_t* const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                        const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATStart(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr);


/******************* TommRoC Hw Net Socket Interface */

/**
 * Init library Hw Net Socket for only client using this device.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        guardPtr                bus device Net Socket guard (NULL if none).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATNetSocketOnlyClient(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr,
        const   tommRoC_guard_t*                                const   guardPtr);

/**
 * Close library Hw Net Socket for only client using this device.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATNetSocketClose(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr);

#endif
