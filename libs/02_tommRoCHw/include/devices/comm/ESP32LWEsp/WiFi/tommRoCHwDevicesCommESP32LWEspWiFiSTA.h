
#ifndef TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_WIFI_STA_H_
#define TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_WIFI_STA_H_

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
#include "tommRoCHwDevicesCommESP32LWEspWiFiSTADEF.h"

#include "comm/tommRoCHwComm.h"

#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"

#include <stdbool.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Connect to WiFi as station to access point.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        SSIDStrPtr              SSID string pointer.
 * param[in]        PWDStrPtr               password string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32LWEspWiFiSTAJoin(
        const   tommRoC_hw_bus_device_t*            const   busDevicePtr,
        const   char*                               const   SSIDStrPtr,
        const   char*                               const   PWDStrPtr);

/**
 * Disconnect from access point.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32LWEspWiFiSTAQuit(
        const   tommRoC_hw_bus_device_t*            const   busDevicePtr);

/**
 * Check if WiFi is connected to an access point.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       isJoinedPtr             is joined pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32LWEspWiFiSTAIsJoined(
        const   tommRoC_hw_bus_device_t*            const   busDevicePtr,
                bool*                               const   isJoinedPtr);

/**
 * Get STA IP address.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       ipV4AddPtr              output IPv4 address structure pointer.
 * param[out]       ipV4MaskPtr             output IPv4 subnet mask structure pointer.
 * param[out]       ipV4GatewayPtr          output IPv4 gateway structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32LWEspWiFiSTAGetIP(
        const   tommRoC_hw_bus_device_t*            const   busDevicePtr,
                tommRoC_hw_comm_ip_v4_add_t*        const   ipV4AddPtr,
                tommRoC_hw_comm_ip_v4_mask_t*       const   ipV4MaskPtr,
                tommRoC_hw_comm_ip_v4_gateway_t*    const   ipV4GatewayPtr);

/**
 * Set STA IP address.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        ipV4AddPtr              input IPv4 address structure pointer.
 * param[in]        ipV4MaskPtr             input IPv4 subnet mask structure pointer.
 * param[in]        ipV4GatewayPtr          input IPv4 gateway structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32LWEspWiFiSTASetIP(
        const   tommRoC_hw_bus_device_t*            const   busDevicePtr,
        const   tommRoC_hw_comm_ip_v4_add_t*        const   ipV4AddPtr,
        const   tommRoC_hw_comm_ip_v4_mask_t*       const   ipV4MaskPtr,
        const   tommRoC_hw_comm_ip_v4_gateway_t*    const   ipV4GatewayPtr);

/**
 * Check if device got IP from access point.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       hasIPPtr                device has IP pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32LWEspWiFiSTAHasIP(
        const   tommRoC_hw_bus_device_t*            const   busDevicePtr,
                bool*                               const   hasIPPtr);

#endif
