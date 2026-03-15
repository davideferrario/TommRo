
#ifndef TOMMROC_HW_TEMPLATE_NVS_H_
#define TOMMROC_HW_TEMPLATE_NVS_H_

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
 *  - __TOMMROC_HW_USE_NVS_TEMPLATE__               to use NVS template
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"
#include "TOMMROCHw.h"

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__) && !defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#error "NVS template can be used only for ESP32"
#endif

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)
#include "nvs_flash.h"
#endif

#include <stdbool.h>
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

/**
 * Start NVS environment.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSStart(void);

/**
 * Stop NVS environment.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSStop(void);

/**
 * Set guard to NVS environment.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetGuard(const tommRoC_guard_t* const guardPtr);


tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetU8(const char* const keyStrPtr, const uint8_t value);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetI8(const char* const keyStrPtr, const int8_t value);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetU16(const char* const keyStrPtr, const uint16_t value);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetI16(const char* const keyStrPtr, const int16_t value);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetU32(const char* const keyStrPtr, const uint32_t value);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetI32(const char* const keyStrPtr, const int32_t value);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetStr(const char* const keyStrPtr, const char* const valueStrPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSSetBlob(const char* const keyStrPtr, const void* const valueBufferPtr, const uint32_t valueBufferSize);

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSGetU8(const char* const keyStrPtr, uint8_t* const valuePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSGetI8(const char* const keyStrPtr, int8_t* const valuePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSGetU16(const char* const keyStrPtr, uint16_t* const valuePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSGetI16(const char* const keyStrPtr, int16_t* const valuePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSGetU32(const char* const keyStrPtr, uint32_t* const valuePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSGetI32(const char* const keyStrPtr, int32_t* const valuePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSGetStr(const char* const keyStrPtr, char* const valueStrPtr, const uint32_t valueStrSize);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSGetBlob(const char* const keyStrPtr, void* const valueBufferPtr, const uint32_t valueBufferSize);

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSEraseKey(const char* const keyStrPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSEraseAll(void);

#endif
