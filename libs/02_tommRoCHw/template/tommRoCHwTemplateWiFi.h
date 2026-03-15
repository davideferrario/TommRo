
#ifndef TOMMROC_HW_TEMPLATE_WIFI_H_
#define TOMMROC_HW_TEMPLATE_WIFI_H_

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
#include "TOMMROC.h"
#include "TOMMROCHw.h"

#include <stdbool.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// NOTE: a network name cannot be more than 32 characters long.
#define TOMMROC_HW_TEMPLATE_WIFI_SSID_STR_MIN_SIZE_BYTE         (1)
#define TOMMROC_HW_TEMPLATE_WIFI_SSID_STR_MAX_SIZE_BYTE         (32)

// NOTE: a password is a sequence of between 8 and 64 ASCII-encoded characters.
#define TOMMROC_HW_TEMPLATE_WIFI_PASSWORD_STR_MIN_SIZE_BYTE     (8)
#define TOMMROC_HW_TEMPLATE_WIFI_PASSWORD_STR_MAX_SIZE_BYTE     (64)

// NOTE: pre-defined Wi-Fi connect retry amout
#define TOMMROC_HW_TEMPLATE_WIFI_CONNECT_RETRY_AMOUNT_FOREVER   (0)                 // Retry forever. In case of disconnection, retry to connect forever.
#define TOMMROC_HW_TEMPLATE_WIFI_CONNECT_RETRY_AMOUNT_NEVER     (UINT32_MAX_VALUE)  // Never retry; try only first attempt. In case of disconnection, never try to connect again.

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init Wi-Fi.
 * NOTE: this MUST be called only once until the WiFi Stop is called.
 *
 * param[in]        wiFiSSIDStrPtr          Wi-Fi SSID string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        wiFiPASSStrPtr          Wi-Fi password string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        connectRetryAmount      Wi-Fi connect retry amount.
 *                                          TOMMROC_HW_TEMPLATE_WIFI_CONNECT_RETRY_AMOUNT_FOREVER   -> retry forever.
 *                                          TOMMROC_HW_TEMPLATE_WIFI_CONNECT_RETRY_AMOUNT_NEVER     -> never retry.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateWiFiInit(
        const   char*       const   wiFiSSIDStrPtr,
        const   char*       const   wiFiPASSStrPtr,
        const   uint32_t            connectRetryAmount);

/**
 * Close Wi-Fi.
 * NOTE: this MUST be called only once until the WiFi Init is called.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateWiFiStop(void);

/**
 * Get Wi-Fi connected status.
 *
 * return bool
 */
bool tommRoCHwTemplateWiFiIsConnected(void);

/**
 * Disconnect Wi-Fi.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateWiFiDisconnect(void);

/**
 * Connect Wi-Fi.
 *
 * param[in]        wiFiSSIDStrPtr          Wi-Fi SSID string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        wiFiPASSStrPtr          Wi-Fi password string pointer [NOTE: string have to be terminated with '\0'].
 * param[in]        connectRetryAmount      Wi-Fi connect retry amount.
 *                                          TOMMROC_HW_TEMPLATE_WIFI_CONNECT_RETRY_AMOUNT_FOREVER   -> retry forever.
 *                                          TOMMROC_HW_TEMPLATE_WIFI_CONNECT_RETRY_AMOUNT_NEVER     -> never retry.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateWiFiConnect(
        const   char*       const   wiFiSSIDStrPtr,
        const   char*       const   wiFiPASSStrPtr,
        const   uint32_t            connectRetryAmount);

#endif

