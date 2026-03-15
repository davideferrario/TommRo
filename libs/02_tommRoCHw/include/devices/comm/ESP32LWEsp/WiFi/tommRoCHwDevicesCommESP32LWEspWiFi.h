
#ifndef TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_WIFI_H_
#define TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_WIFI_H_

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
#include "tommRoCHwDevicesCommESP32LWEspWiFiDEF.h"

#include "tommRoCHwDevicesCommESP32LWEspWiFiAP.h"
#include "tommRoCHwDevicesCommESP32LWEspWiFiSTA.h"

#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"

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
 * Set WiFi mode to either station only, access point only or both.
 * NOTE: Configuration changes will be saved in the NVS area of ESP device.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        wiFiMode                WiFi mode of operation.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32LWEspWiFiSetMode(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
        const   tommRoC_hw_devices_comm_esp32_lwesp_wifi_def_mode_enum_t            wiFiMode);

/**
 * Get WiFi mode to either station only, access point only or both.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       wiFiModePtr             WiFi mode of operation pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommESP32LWEspWiFiGetMode(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                tommRoC_hw_devices_comm_esp32_lwesp_wifi_def_mode_enum_t*   const   wiFiModePtr);

#endif
