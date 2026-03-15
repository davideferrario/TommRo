
#ifndef TOMMROC_HW_TEMPLATE_LWESP_THREAD_H_
#define TOMMROC_HW_TEMPLATE_LWESP_THREAD_H_

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

/*******************************************************************************
 * functions
 ******************************************************************************/

uint32_t tommRoCHwTemplateLWEspThreadEnvGetSize(void);

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspThreadCreate(void* threadPtr, const char* threadNamePtr, void(*threadMain)(void*), void* const threadArgPtr, uint32_t threadStackSize, uint32_t threadPriority);
tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspThreadTerminate(void* threadPtr);

#endif
