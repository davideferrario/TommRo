
#ifndef TOMMROC_MW_TEMPLATE_RTOS_THREADX_COMMON_COMPATIBILITY_H_
#define TOMMROC_MW_TEMPLATE_RTOS_THREADX_COMMON_COMPATIBILITY_H_

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
#include "TOMMROC.h"

#include "tx_api.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************** Common define */


/******************** Specific Event define */
#define __THREADX_EVENT_FLAGS_CREATE_SUCCESS_RESULT__       (TX_SUCCESS)
#define __THREADX_EVENT_FLAGS_DELETE_SUCCESS_RESULT__       (TX_SUCCESS)
#define __THREADX_EVENT_FLAGS_SET_SUCCESS_RESULT__          (TX_SUCCESS)
#define __THREADX_EVENT_FLAGS_GET_SUCCESS_RESULT__          (TX_SUCCESS)


/******************** Specific Mutex define */
#define __THREADX_MUTEX_CREATE_SUCCESS_RESULT__             (TX_SUCCESS)
#define __THREADX_MUTEX_GET_SUCCESS_RESULT__                (TX_SUCCESS)
#define __THREADX_MUTEX_PUT_SUCCESS_RESULT__                (TX_SUCCESS)
#define __THREADX_MUTEX_DELETE_SUCCESS_RESULT__             (TX_SUCCESS)


/******************** Specific Queue define */
#define __THREADX_QUEUE_CREATE_SUCCESS_RESULT__             (TX_SUCCESS)
#define __THREADX_QUEUE_SEND_SUCCESS_RESULT__               (TX_SUCCESS)
#define __THREADX_QUEUE_RECEIVE_SUCCESS_RESULT__            (TX_SUCCESS)
#define __THREADX_QUEUE_INFO_GET_SUCCESS_RESULT__           (TX_SUCCESS)
#define __THREADX_QUEUE_DELETE_SUCCESS_RESULT__             (TX_SUCCESS)


/******************** Specific Semaphore define */
#define __THREADX_SEMAPHORE_CREATE_SUCCESS_RESULT__         (TX_SUCCESS)
#define __THREADX_SEMAPHORE_GET_SUCCESS_RESULT__            (TX_SUCCESS)
#define __THREADX_SEMAPHORE_PUT_SUCCESS_RESULT__            (TX_SUCCESS)
#define __THREADX_SEMAPHORE_DELETE_SUCCESS_RESULT__         (TX_SUCCESS)


/******************** Specific Thread define */
#define __THREADX_THREAD_CREATE_SUCCESS_RESULT__            (TX_SUCCESS)
#define __THREADX_THREAD_IDENTIFY_ON_ERROR_RESULT__         (NULL)
#define __THREADX_THREAD_TERMINATE_SUCCESS_RESULT__         (TX_SUCCESS)
#define __THREADX_THREAD_DESTROY_SUCCESS_RESULT__           (TX_SUCCESS)

#if defined (TX_MINIMUM_STACK)
#define __THREADX_THREAD_STACK_SIZE_DEFAULT__               (TX_MINIMUM_STACK)
#else
#define __THREADX_THREAD_STACK_SIZE_DEFAULT__               (128)
#endif

// Macros to convert from milliseconds to ticks
#define TOMMROC_MW_TEMPLATE_RTOS_THREADX_COMMON_COMPATIBILITY_MS_TO_TICKS(ms)   ((ms) * (TX_TIMER_TICKS_PER_SECOND) / (1000UL))

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif

#endif
