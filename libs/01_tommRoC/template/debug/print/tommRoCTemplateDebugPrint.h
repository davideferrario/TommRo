
#ifndef TOMMROC_TEMPLATE_DEBUG_PRINT_H_
#define TOMMROC_TEMPLATE_DEBUG_PRINT_H_

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
#include "tommRoCTemplateDebug.h"

#if defined (__TOMMROC_PRINT_DEBUG_TEMPLATE_IS_USED__)

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

tommRoC_err_enum_t tommRoCTemplateDebugPrintStart(void);

const char* tommRoCTemplateDebugPrintNewLineStr(void);
tommRoC_err_enum_t tommRoCTemplateDebugPrintStr(const tommRoC_debug_level_enum_t debugLevel, const char* const stringPtr);
tommRoC_err_enum_t tommRoCTemplateDebugPrintStrLen(const tommRoC_debug_level_enum_t debugLevel, const char* const stringPtr, const uint16_t stringLen);

tommRoC_err_enum_t tommRoCTemplateDebugPrintIsPending(bool* const isPendingPtr);

#endif

#endif
