
#ifndef TOMMROC_HW_TEMPLATE_BLE_ENV_ESP32_MULTI_CONNECTION_NIM_BLE_H_
#define TOMMROC_HW_TEMPLATE_BLE_ENV_ESP32_MULTI_CONNECTION_NIM_BLE_H_

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

#include "TOMMROCHw.h"

#include "tommRoCHwTemplateBLEMultiDEF.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* Specific NimBLE functions */

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiEnvESP32NimBLENotify(
        const   tommRoC_hw_template_ble_multi_def_conn_handler_t*   const   connHandlerPtr,
        const   uint16_t                                                    chrValHandle,
        const   void*                                               const   dataPtr,
        const   uint16_t                                                    dataSize);

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiEnvESP32NimBLEIndicate(
        const   tommRoC_hw_template_ble_multi_def_conn_handler_t*   const   connHandlerPtr,
        const   uint16_t                                                    chrValHandle,
        const   void*                                               const   dataPtr,
        const   uint16_t                                                    dataSize);

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEMultiEnvESP32NimBLEOnReceive(
        const   tommRoC_hw_template_ble_multi_def_conn_handler_t*   const   connHandlerPtr,
        const   uint16_t                                                    chrValHandle,
        const   void*                                               const   dataPtr,
        const   uint16_t                                                    dataSize);

#endif

#endif

#endif
