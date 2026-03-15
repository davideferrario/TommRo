
#ifndef TOMMROC_MW_TEMPLATE_RTOS_CMSIS_V1_RTOS_COMMON_COMPATIBILITY_H_
#define TOMMROC_MW_TEMPLATE_RTOS_CMSIS_V1_RTOS_COMMON_COMPATIBILITY_H_

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

#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"

#include "rtos/cmsisRTOS/V1/common/CMSIS_RTOS/tommRoCMwTemplateRTOS_cmsis_os.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Check CMSIS RTOS underlying RTOS kernel/version used
#if defined (osCMSIS_KERNEL)
#define __TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__

#elif defined (osCMSIS_RTX)
#define __TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__

#else
#error "Not supported RTOS environment"
#endif


/******************** Common define */


/******************** Specific Event define */
#define __CMSIS_V1_RTOS_EVENT_GROUP_CREATE_ON_ERROR_RESULT                  (NULL)
#define __CMSIS_V1_RTOS_X_EVENT_GROUP_SET_BITS_FROM_ISR_SUCCESS_RESULT__    (pdPASS)


/******************** Specific Mutex define */
#define __CMSIS_RTOS_MUTEX_CREATE_ON_ERROR_RESULT__                         (NULL)
#define __CMSIS_RTOS_MUTEX_WAIT_SUCCESS_RESULT__                            (osOK)
#define __CMSIS_RTOS_MUTEX_RELEASE_SUCCESS_RESULT__                         (osOK)
#define __CMSIS_RTOS_MUTEX_DELETE_SUCCESS_RESULT__                          (osOK)


/******************** Specific Queue define */
#define __CMSIS_RTOS_QUEUE_CREATE_ON_ERROR_RESULT__                         (NULL)
#define __CMSIS_RTOS_QUEUE_PUT_SUCCESS_RESULT__                             (osOK)
#define __CMSIS_RTOS_QUEUE_GET_SUCCESS_RESULT__                             (osEventMessage)
#define __CMSIS_RTOS_QUEUE_DELETE_SUCCESS_RESULT__                          (osOK)


/******************** Specific Semaphore define */
#define __CMSIS_RTOS_SEMAPHORE_CREATE_ON_ERROR_RESULT__                     (NULL)
#define __CMSIS_RTOS_SEMAPHORE_DELETE_SUCCESS_RESULT__                      (osOK)


/******************** Specific Thread define */
#define __CMSIS_RTOS_THREAD_CREATE_ON_ERROR_RESULT__                        (NULL)
#define __CMSIS_RTOS_THREAD_GET_ID_ON_ERROR_RESULT__                        (NULL)
#define __CMSIS_RTOS_THREAD_TERMINATE_SUCCESS_RESULT__                      (osOK)
#define __CMSIS_RTOS_THREAD_YIELD_SUCCESS_RESULT__                          (osOK)
#define __CMSIS_RTOS_THREAD_SUSPEND_ALL_SUCCESS_RESULT__                    (osOK)
#define __CMSIS_RTOS_THREAD_RESUME_ALL_SUCCESS_RESULT__                     (osOK)

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
#if defined (configMINIMAL_STACK_SIZE)
#define __CMSIS_RTOS_THREAD_STACK_SIZE_DEFAULT__                            (configMINIMAL_STACK_SIZE)
#else
#error "FreeRTOS config file error"
#endif

#define __CMSIS_RTOS_OS_DELAY_SUCCESS_RESULT__                              (osOK)

#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
#define __CMSIS_RTOS_THREAD_STACK_SIZE_DEFAULT__                            (0)

#define __CMSIS_RTOS_OS_DELAY_SUCCESS_RESULT__                              (osEventTimeout)

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif

#endif
