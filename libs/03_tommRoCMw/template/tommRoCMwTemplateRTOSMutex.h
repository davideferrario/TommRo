
#ifndef TOMMROC_MW_TEMPLATE_RTOS_MUTEX_H_
#define TOMMROC_MW_TEMPLATE_RTOS_MUTEX_H_

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
 *  - __TOMMROC_MW_USE_MUTEX_CMSIS_V1_RTOS_TEMPLATE__       CMSIS V1 RTOS mutex
 *  - __TOMMROC_MW_USE_MUTEX_CMSIS_V2_RTOS_TEMPLATE__       CMSIS V2 RTOS mutex
 *  - __TOMMROC_MW_USE_MUTEX_NXP_OSA_TEMPLATE__             NXP OSA mutex
 *  - __TOMMROC_MW_USE_MUTEX_PTHREAD_TEMPLATE__             pthread library mutex
 *  - __TOMMROC_MW_USE_MUTEX_THREADX_TEMPLATE__             ThreadX library mutex
 *  - __TOMMROC_MW_USE_MUTEX_WINDOWS_H_TEMPLATE__           Windows mutex
 */

#if defined (__TOMMROC_MW_USE_MUTEX_CMSIS_RTOS_TEMPLATE__)
#error "replace __TOMMROC_MW_USE_MUTEX_CMSIS_RTOS_TEMPLATE__ with __TOMMROC_MW_USE_MUTEX_CMSIS_V1_RTOS_TEMPLATE__"
#endif

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"
#include "TOMMROCMw.h"

#if defined (__TOMMROC_MW_USE_MUTEX_CMSIS_V1_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V1/common/CMSIS_RTOS/tommRoCMwTemplateRTOS_cmsis_os.h"
#include <stdbool.h>

#elif defined (__TOMMROC_MW_USE_MUTEX_CMSIS_V2_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V2/common/CMSIS_RTOS/tommRoCMwTemplateRTOS_cmsis_os.h"

#elif defined (__TOMMROC_MW_USE_MUTEX_NXP_OSA_TEMPLATE__)
#include "fsl_os_abstraction.h"

#elif defined (__TOMMROC_MW_USE_MUTEX_PTHREAD_TEMPLATE__)
#include <pthread.h>

#elif defined (__TOMMROC_MW_USE_MUTEX_THREADX_TEMPLATE__)
#include "tx_api.h"

#elif defined (__TOMMROC_MW_USE_MUTEX_WINDOWS_H_TEMPLATE__)
#include <windows.h>

#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************** CMSIS_V1 RTOS template */
#if defined (__TOMMROC_MW_USE_MUTEX_CMSIS_V1_RTOS_TEMPLATE__)
#if !defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)
#error "tommRoCMw mutex CMSIS_V1 RTOS template NEED thread CMSIS_V1 RTOS template"
#endif

#if defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)
#error "tommRoCMw mutex template multiple definition"
#else
#define __TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__
#if (configUSE_RECURSIVE_MUTEXES == 1)
#define __TOMMROC_MW_MUTEX_RECURSIVE_MUTEXES_TEMPLATE_IS_USED__
#endif
#endif
#endif


/******************** CMSIS_V2 RTOS template */
#if defined (__TOMMROC_MW_USE_MUTEX_CMSIS_V2_RTOS_TEMPLATE__)
#if !defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)
#error "tommRoCMw mutex CMSIS_V2 RTOS template NEED thread CMSIS_V2 RTOS template"
#endif

#if defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)
#error "tommRoCMw mutex template multiple definition"
#else
#define __TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__
#if (configUSE_RECURSIVE_MUTEXES == 1)
#define __TOMMROC_MW_MUTEX_RECURSIVE_MUTEXES_TEMPLATE_IS_USED__
#endif
#endif
#endif


/******************** NXP OSA template */
#if defined (__TOMMROC_MW_USE_MUTEX_NXP_OSA_TEMPLATE__)
#if !defined (__TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__)
#error "tommRoCMw mutex NXP OSA template NEED thread NXP OSA template"
#endif

#if defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)
#error "tommRoCMw mutex template multiple definition"
#else
#define __TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__
#if (configUSE_RECURSIVE_MUTEXES == 1)
#define __TOMMROC_MW_MUTEX_RECURSIVE_MUTEXES_TEMPLATE_IS_USED__
#endif
#endif
#endif


/******************** PThread template */
#if defined (__TOMMROC_MW_USE_MUTEX_PTHREAD_TEMPLATE__)
#if defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)
#error "tommRoCMw mutex template multiple definition"
#else
#define __TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__
#define __TOMMROC_MW_MUTEX_RECURSIVE_MUTEXES_TEMPLATE_IS_USED__
#endif
#endif


/******************** ThreadX template */
#if defined (__TOMMROC_MW_USE_MUTEX_THREADX_TEMPLATE__)
#if defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)
#error "tommRoCMw mutex template multiple definition"
#else
#define __TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__
#define __TOMMROC_MW_MUTEX_RECURSIVE_MUTEXES_TEMPLATE_IS_USED__
#endif
#endif


/******************** Windows.h template */
#if defined (__TOMMROC_MW_USE_MUTEX_WINDOWS_H_TEMPLATE__)
#if defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)
#error "tommRoCMw mutex template multiple definition"
#else
#define __TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__
#define __TOMMROC_MW_MUTEX_RECURSIVE_MUTEXES_TEMPLATE_IS_USED__
#endif
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef struct {

/******************** CMSIS_V1 RTOS template */
#if defined (__TOMMROC_MW_USE_MUTEX_CMSIS_V1_RTOS_TEMPLATE__)
#if defined (osCMSIS_RTX)
    uint32_t            osMutexCb[4];
#endif
    osMutexDef_t        osMutexDef;
    osMutexId           osMutexId;
    bool                isRecursive;


/******************** CMSIS_V2 RTOS template */
#elif defined (__TOMMROC_MW_USE_MUTEX_CMSIS_V2_RTOS_TEMPLATE__)
#if defined (osCMSIS_RTX)
    uint32_t            osMutexCb[4];
#endif
    osMutexAttr_t       osMutexAttr;
    osMutexId_t         osMutexId;


/******************** NXP OSA template */
#elif defined (__TOMMROC_MW_USE_MUTEX_NXP_OSA_TEMPLATE__)
    osaMutexId_t        osaMutexId;


/******************** PThread template */
#elif defined (__TOMMROC_MW_USE_MUTEX_PTHREAD_TEMPLATE__)
    pthread_mutex_t     pThreadMutex;


/******************** ThreadX template */
#elif defined (__TOMMROC_MW_USE_MUTEX_THREADX_TEMPLATE__)
    TX_MUTEX            threadXMutex;

/******************** Windows.h template */
#elif defined (__TOMMROC_MW_USE_MUTEX_WINDOWS_H_TEMPLATE__)
    HANDLE              handle;


#endif

} tommRoC_mw_template_mutex_t;

#if defined (__TOMMROC_MW_USE_MUTEX_CMSIS_V1_RTOS_TEMPLATE__)
#if defined (osCMSIS_RTX)
#define __EMPTY_tommRoC_mw_template_mutex_t__
#else
#define __EMPTY_tommRoC_mw_template_mutex_t__   \
{                                               \
    /* .osMutexDef */   { 0, },                 \
    /* .osMutexId */    NULL,                   \
    /* .isRecursive */  false,                  \
}
#endif

#elif defined (__TOMMROC_MW_USE_MUTEX_CMSIS_V2_RTOS_TEMPLATE__)
#if defined (osCMSIS_RTX)
#define __EMPTY_tommRoC_mw_template_mutex_t__
#else
#define __EMPTY_tommRoC_mw_template_mutex_t__   \
{                                               \
    /* .osMutexAttr */  { NULL, 0, NULL, 0, },  \
    /* .osMutexId */    NULL,                   \
}
#endif

#elif defined (__TOMMROC_MW_USE_MUTEX_NXP_OSA_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_mutex_t__   \
{                                               \
    /* .osaMutexId */   NULL,                   \
}

#elif defined (__TOMMROC_MW_USE_MUTEX_PTHREAD_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_mutex_t__                                                                       \
{                                                                                                                   \
    /* .pThreadMutex */ { .__size = TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, __SIZEOF_PTHREAD_MUTEX_T - 1, 0) },    \
}

#elif defined (__TOMMROC_MW_USE_MUTEX_THREADX_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_mutex_t__   \
{                                               \
    /* .threadXMutex */ { 0 },                  \
}

#elif defined (__TOMMROC_MW_USE_MUTEX_WINDOWS_H_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_mutex_t__
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSMutexStart(void);
tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSMutexStop(void);

#endif

#endif
