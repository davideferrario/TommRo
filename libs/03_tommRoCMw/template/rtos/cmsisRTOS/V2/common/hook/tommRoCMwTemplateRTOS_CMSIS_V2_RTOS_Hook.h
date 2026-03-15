
#ifndef TOMMROC_MW_TEMPLATE_RTOS_CMSIS_V2_RTOS_HOOK_H_
#define TOMMROC_MW_TEMPLATE_RTOS_CMSIS_V2_RTOS_HOOK_H_

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

#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "rtos/cmsisRTOS/V2/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
#if defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
#include "freertos/FreeRTOSConfig.h"
#else
#include "FreeRTOSConfig.h"
#endif
#if (configCHECK_FOR_STACK_OVERFLOW > 0)
#define __TOMMROC_MW_TEMPLATE_RTOS_CMSIS_RTOS_CHECK_FOR_STACK_OVERFLOW_IS_USED__
#endif
#if (configUSE_MALLOC_FAILED_HOOK > 0)
#define __TOMMROC_MW_TEMPLATE_RTOS_CMSIS_RTOS_MALLOC_FAILED_HOOK_IS_USED__
#endif
#endif

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
#endif

#include <stdbool.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_MW_TEMPLATE_RTOS_CMSIS_RTOS_CHECK_FOR_STACK_OVERFLOW_IS_USED__)
bool tommRoCMwTemplateRTOS_CMSIS_RTOS_HookStackOverflowHasBeenDetected(void);
#endif

#if defined (__TOMMROC_MW_TEMPLATE_RTOS_CMSIS_RTOS_MALLOC_FAILED_HOOK_IS_USED__)
bool tommRoCMwTemplateRTOS_CMSIS_RTOS_HookMallocFailedHasBeenDetected(void);
#endif

void tommRoCMwTemplateRTOS_CMSIS_RTOS_HookDebug(void);

#endif

#endif
