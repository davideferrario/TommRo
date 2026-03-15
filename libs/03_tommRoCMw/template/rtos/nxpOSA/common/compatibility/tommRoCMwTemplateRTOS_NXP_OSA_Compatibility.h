
#ifndef TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_COMMON_COMPATIBILITY_H_
#define TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_COMMON_COMPATIBILITY_H_

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
#include "TOMMROC.h"

#include "fsl_os_abstraction.h"
#include "fsl_os_abstraction_free_rtos.h"

#include "FreeRTOSConfig.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************** Common define */


/******************** Specific Event define */
#define __NXP_OSA_OS_SIGNAL_SET_ON_ERROR_RESULT__           ((int32_t) 0x80000000)
#define __NXP_OSA_OS_SIGNAL_WAIT_SUCCESS_RESULT__           (osaStatus_Success)
#define __NXP_OSA_OS_SIGNAL_CLEAR_ON_ERROR_RESULT__         ((int32_t) 0x80000000)


/******************** Specific Mutex define */
#define __NXP_OSA_MUTEX_CREATE_ON_ERROR_RESULT__            (NULL)
#define __NXP_OSA_MUTEX_LOCK_SUCCESS_RESULT__               (osaStatus_Success)
#define __NXP_OSA_MUTEX_UNLOCK_SUCCESS_RESULT__             (osaStatus_Success)
#define __NXP_OSA_MUTEX_DESTROY_SUCCESS_RESULT__            (osaStatus_Success)


/******************** Specific Semaphore define */
#define __NXP_OSA_SEMAPHORE_CREATE_ON_ERROR_RESULT__        (NULL)
#define __NXP_OSA_SEMAPHORE_WAIT_SUCCESS_RESULT__           (osaStatus_Success)
#define __NXP_OSA_SEMAPHORE_POST_SUCCESS_RESULT__           (osaStatus_Success)
#define __NXP_OSA_SEMAPHORE_DESTROY_SUCCESS_RESULT__        (osaStatus_Success)


/******************** Specific Thread define */
#define __NXP_OSA_TASK_CREATE_ON_ERROR_RESULT__             (NULL)
#define __NXP_OSA_TASK_GET_ID_ON_ERROR_RESULT__             (NULL)
#define __NXP_OSA_TASK_DESTROY_SUCCESS_RESULT__             (osaStatus_Success)
#define __NXP_OSA_TASK_YIELD_SUCCESS_RESULT__               (osaStatus_Success)

#if defined (configMINIMAL_STACK_SIZE)
#define __NXP_OSA_THREAD_STACK_SIZE_DEFAULT__               (configMINIMAL_STACK_SIZE)
#else
#error "FreeRTOS config file error"
#endif


/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif

#endif
