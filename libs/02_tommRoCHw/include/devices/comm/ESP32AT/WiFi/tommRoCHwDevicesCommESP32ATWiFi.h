
#ifndef TOMMROC_HW_DEVICES_COMM_ESP32_AT_WIFI_H_
#define TOMMROC_HW_DEVICES_COMM_ESP32_AT_WIFI_H_

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
#include "tommRoCHwDevicesCommESP32ATWiFiDEF.h"

#include "comm/tommRoCHwComm.h"

#include "tommRoCHwBus.h"
#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"
#include "tommRoCHwNet.h"

#include "TOMMROC.h"

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
 * Connect to an AP.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        SSIDStrPtr              SSID string pointer.
 * param[in]        PWDStrPtr               password string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATWiFiAPConnect(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   char*                       const   SSIDStrPtr,
        const   char*                       const   PWDStrPtr);

/**
 * Disconnect from an AP.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32ATWiFiAPDisconnect(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr);

#endif
