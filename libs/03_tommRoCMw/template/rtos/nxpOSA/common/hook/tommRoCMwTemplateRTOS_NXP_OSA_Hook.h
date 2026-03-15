
#ifndef TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_HOOK_H_
#define TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_HOOK_H_

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

#if defined (__TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "rtos/nxpOSA/common/compatibility/tommRoCMwTemplateRTOS_NXP_OSA_Compatibility.h"

#include "FreeRTOSConfig.h"
#if (configCHECK_FOR_STACK_OVERFLOW > 0)
#define __TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_CHECK_FOR_STACK_OVERFLOW_IS_USED__
#endif
#if (configUSE_MALLOC_FAILED_HOOK > 0)
#define __TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_MALLOC_FAILED_HOOK_IS_USED__
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

#if defined (__TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_CHECK_FOR_STACK_OVERFLOW_IS_USED__)
bool tommRoCMwTemplateRTOS_NXP_OSA_HookStackOverflowHasBeenDetected(void);
#endif

#if defined (__TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_MALLOC_FAILED_HOOK_IS_USED__)
bool tommRoCMwTemplateRTOS_NXP_OSA_HookMallocFailedHasBeenDetected(void);
#endif

void tommRoCMwTemplateRTOS_NXP_OSA_HookDebug(void);

#endif

#endif
