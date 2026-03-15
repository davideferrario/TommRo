
#ifndef TOMMROC_HW_TEMPLATE_BLE_ENV_ESP32_SINGLE_CONNECTION_BLUE_DROID_H_
#define TOMMROC_HW_TEMPLATE_BLE_ENV_ESP32_SINGLE_CONNECTION_BLUE_DROID_H_

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
#include "TOMMROCHw.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef enum {

    /**
     * Notify function callback.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_hw_template_ble_env_esp32_blueDroid_notify_funct_t.
     */
    TOMMROC_HW_TEMPLATE_BLE_ENV_ESP32_BLUE_DROID_NOTIFY_FUNCT = 0,

} tommRoC_hw_template_ble_env_esp32_bluedroid_prop_enum_t;

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_ble_env_esp32_blueDroid_notify_funct_t)(
        const   uint16_t            connID,
        const   uint16_t            chHandle,
        const   void*       const   dataPtr,
        const   uint16_t            dataLen);

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32BlueDroidGetProp(
        const   tommRoC_hw_template_ble_env_esp32_bluedroid_prop_enum_t         property,
                void*                                                   const   propValuePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateBLEEnvESP32BlueDroidSetProp(
        const   tommRoC_hw_template_ble_env_esp32_bluedroid_prop_enum_t         property,
        const   void*                                                   const   propValuePtr);

#endif
