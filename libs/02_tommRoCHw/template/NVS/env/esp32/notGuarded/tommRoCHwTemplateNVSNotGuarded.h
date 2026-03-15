#ifndef TOMMROC_HW_TEMPLATE_NVS_NOT_GUARDED_H_
#define TOMMROC_HW_TEMPLATE_NVS_NOT_GUARDED_H_

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

#if defined (__TOMMROC_HW_USE_NVS_TEMPLATE__)

#include "TOMMROC.h"
#include "TOMMROCHw.h"

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

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedStart(void);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedStop(void);

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedSetU8(const char* const keyStrPtr, const uint8_t value);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedSetI8(const char* const keyStrPtr, const int8_t value);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedSetU16(const char* const keyStrPtr, const uint16_t value);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedSetI16(const char* const keyStrPtr, const int16_t value);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedSetU32(const char* const keyStrPtr, const uint32_t value);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedSetI32(const char* const keyStrPtr, const int32_t value);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedSetStr(const char* const keyStrPtr, const char* const valueStrPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedSetBlob(const char* const keyStrPtr, const void* const valueBufferPtr, const uint32_t valueBufferSize);

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedGetU8(const char* const keyStrPtr, uint8_t* const valuePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedGetI8(const char* const keyStrPtr, int8_t* const valuePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedGetU16(const char* const keyStrPtr, uint16_t* const valuePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedGetI16(const char* const keyStrPtr, int16_t* const valuePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedGetU32(const char* const keyStrPtr, uint32_t* const valuePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedGetI32(const char* const keyStrPtr, int32_t* const valuePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedGetStr(const char* const keyStrPtr, char* const valueStrPtr, const uint32_t valueStrSize);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedGetBlob(const char* const keyStrPtr, void* const valueBufferPtr, const uint32_t valueBufferSize);

tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedEraseKey(const char* const keyStrPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateNVSNotGuardedEraseAll(void);

#endif

#endif
