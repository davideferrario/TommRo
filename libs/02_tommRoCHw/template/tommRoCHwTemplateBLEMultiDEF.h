
#ifndef TOMMROC_HW_TEMPLATE_BLE_MULTI_DEF_H_
#define TOMMROC_HW_TEMPLATE_BLE_MULTI_DEF_H_

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

/**
 *  - Disable BLE template
 *      - __TOMMROC_HW_DISABLE_BLE_TEMPLATE__           disable library BLE template implementation.
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROCHw.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#if defined (CONFIG_BT_NIMBLE_ENABLED)
#define TOMMROC_HW_TEMPLATE_BLE_MULTI_DEF_CONN_HANDLE_NOT_CONNECTED_VALUE   (-1)
#elif defined (CONFIG_BT_BLUEDROID_ENABLED)
#endif
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC Hw template BLE multi Connection handler
typedef struct {

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#if defined (CONFIG_BT_NIMBLE_ENABLED)
    int32_t connHandle;
#elif defined (CONFIG_BT_BLUEDROID_ENABLED)
#endif
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)
#endif

} tommRoC_hw_template_ble_multi_def_conn_handler_t;

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#if defined (CONFIG_BT_NIMBLE_ENABLED)
#define __EMPTY_tommRoC_hw_template_ble_multi_def_conn_handler_t__                          \
{                                                                                           \
    /* .connHandle */   TOMMROC_HW_TEMPLATE_BLE_MULTI_DEF_CONN_HANDLE_NOT_CONNECTED_VALUE,  \
}
#elif defined (CONFIG_BT_BLUEDROID_ENABLED)
#endif
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)
#endif

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_ble_multi_def_on_connect_funct_t)(
        const   tommRoC_hw_template_ble_multi_def_conn_handler_t*   const   connHandlerPtr);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_ble_multi_def_on_disconnect_funct_t)(
        const   tommRoC_hw_template_ble_multi_def_conn_handler_t*   const   connHandlerPtr);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_ble_multi_def_on_receive_funct_t)(
        const   tommRoC_hw_template_ble_multi_def_conn_handler_t*   const   connHandlerPtr,
        const   uint16_t                                                    chrValHandle,
        const   void*                                               const   dataPtr,
        const   uint16_t                                                    dataSize);

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
