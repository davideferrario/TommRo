
#ifndef TOMMROC_MW_TEMPLATE_RTOS_THREADX_HOOK_H_
#define TOMMROC_MW_TEMPLATE_RTOS_THREADX_HOOK_H_

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

#if defined (__TOMMROC_MW_USE_THREAD_THREADX_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "rtos/threadX/common/compatibility/tommRoCMwTemplateRTOS_ThreadX_Compatibility.h"

#if defined(TX_ENABLE_STACK_CHECKING) || defined(TX_PORT_THREAD_STACK_ERROR_HANDLING)
#define __TOMMROC_MW_TEMPLATE_RTOS_THREADX_CHECK_FOR_STACK_OVERFLOW_IS_USED__
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

#if defined (__TOMMROC_MW_TEMPLATE_RTOS_THREADX_CHECK_FOR_STACK_OVERFLOW_IS_USED__)
bool tommRoCMwTemplateRTOS_ThreadX_HookStackOverflowHasBeenDetected(void);
VOID tommRoCMwTemplateRTOS_ThreadX_HookStackOverflowStackErrorHandler(TX_THREAD *thread_ptr);
#endif

void tommRoCMwTemplateRTOS_ThreadX_HookDebug(void);

#endif

#endif
