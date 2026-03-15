
#ifndef TOMMROC_HW_TEMPLATE_BLE_ENV_ESP32_MULTI_CONNECTION_NIM_BLE_CONN_HANDLE_MTU_VALUE_H_
#define TOMMROC_HW_TEMPLATE_BLE_ENV_ESP32_MULTI_CONNECTION_NIM_BLE_CONN_HANDLE_MTU_VALUE_H_

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

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#include "sdkconfig.h"

#if defined (CONFIG_BT_NIMBLE_MAX_CONNECTIONS) && (CONFIG_BT_NIMBLE_MAX_CONNECTIONS > 1)
#include "tommRoCHwTemplateBLEMulti.h"

#include "TOMMROCHw.h"

/*******************************************************************************
 * defines
 ******************************************************************************/
#define TOMMROC_HW_TEMPLATE_BLE_ENV_ESP32_MULTI_CONNECTION_NIM_BLE_CONN_HANDLE_MTU_VALUE_CONN_HANDLE_NOT_CONNECTED_VALUE    (TOMMROC_HW_TEMPLATE_BLE_MULTI_DEF_CONN_HANDLE_NOT_CONNECTED_VALUE)
#define TOMMROC_HW_TEMPLATE_BLE_ENV_ESP32_MULTI_CONNECTION_NIM_BLE_CONN_HANDLE_MTU_VALUE_MTU_VALUE_DEFAULT                  (20)

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef struct {

    int32_t connHandle;
    uint16_t mtuValue;
    bool isEmpty;

} esp32_multi_nimble_conn_handle_mtu_value_t;

#define __EMPTY_esp32_multi_nimble_conn_handle_mtu_value_t__                                                                                \
{                                                                                                                                           \
    /* .connHandle */   TOMMROC_HW_TEMPLATE_BLE_ENV_ESP32_MULTI_CONNECTION_NIM_BLE_CONN_HANDLE_MTU_VALUE_CONN_HANDLE_NOT_CONNECTED_VALUE,   \
    /* .mtuValue */     TOMMROC_HW_TEMPLATE_BLE_ENV_ESP32_MULTI_CONNECTION_NIM_BLE_CONN_HANDLE_MTU_VALUE_MTU_VALUE_DEFAULT,                 \
    /* .isEmpty */      true,                                                                                                               \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueInit(void);

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueAdd(const esp32_multi_nimble_conn_handle_mtu_value_t* const connHandleMTUValuePtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueRemove(const esp32_multi_nimble_conn_handle_mtu_value_t* const connHandleMTUValuePtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueUpdate(const esp32_multi_nimble_conn_handle_mtu_value_t* const connHandleMTUValuePtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueGetFromConnHandle(const uint16_t connHandle, esp32_multi_nimble_conn_handle_mtu_value_t* const connHandleMTUValuePtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueIsEmpty(bool* const isEmptyPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32MultiConnectionNimBLEConnHandleMTUValueIsFull(bool* const isFullPtr);

#endif

#endif

#endif
