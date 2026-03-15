
#ifndef TOMMROC_MW_TEMPLATE_RTOS_SEMAPHORE_H_
#define TOMMROC_MW_TEMPLATE_RTOS_SEMAPHORE_H_

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
 *  - __TOMMROC_MW_USE_SEMAPHORE_CMSIS_V1_RTOS_TEMPLATE__   CMSIS_V1 RTOS semaphore
 *  - __TOMMROC_MW_USE_SEMAPHORE_CMSIS_V2_RTOS_TEMPLATE__   CMSIS_V2 RTOS semaphore
 *  - __TOMMROC_MW_USE_SEMAPHORE_NXP_OSA_TEMPLATE__         NXP OSA semaphore
 *  - __TOMMROC_MW_USE_SEMAPHORE_SEMAPHORE_H_TEMPLATE__     semaphore.h library semaphore
 *  - __TOMMROC_MW_USE_SEMAPHORE_THREADX_TEMPLATE__         ThreadX library semaphore
 *  - __TOMMROC_MW_USE_SEMAPHORE_WINDOWS_H_TEMPLATE__       Windows semaphore
 */

#if defined (__TOMMROC_MW_USE_SEMAPHORE_CMSIS_RTOS_TEMPLATE__)
#error "replace __TOMMROC_MW_USE_SEMAPHORE_CMSIS_RTOS_TEMPLATE__ with __TOMMROC_MW_USE_SEMAPHORE_CMSIS_V1_RTOS_TEMPLATE__"
#endif

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"
#include "TOMMROCMw.h"

#if defined (__TOMMROC_MW_USE_SEMAPHORE_CMSIS_V1_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V1/common/CMSIS_RTOS/tommRoCMwTemplateRTOS_cmsis_os.h"

#elif defined (__TOMMROC_MW_USE_SEMAPHORE_CMSIS_V2_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V2/common/CMSIS_RTOS/tommRoCMwTemplateRTOS_cmsis_os.h"

#elif defined (__TOMMROC_MW_USE_SEMAPHORE_NXP_OSA_TEMPLATE__)
#include "fsl_os_abstraction.h"

#elif defined (__TOMMROC_MW_USE_SEMAPHORE_SEMAPHORE_H_TEMPLATE__)
#include <semaphore.h>

#elif defined (__TOMMROC_MW_USE_SEMAPHORE_THREADX_TEMPLATE__)
#include "tx_api.h"

#elif defined (__TOMMROC_MW_USE_SEMAPHORE_WINDOWS_H_TEMPLATE__)
#include <windows.h>

#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************** CMSIS_V1 RTOS template */
#if defined (__TOMMROC_MW_USE_SEMAPHORE_CMSIS_V1_RTOS_TEMPLATE__)
#if !defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)
#error "tommRoCMw semaphore CMSIS_V1 RTOS template NEED thread CMSIS_V1 RTOS template"
#endif

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
#error "tommRoCMw semaphore template multiple definition"
#else
#define __TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__
#if (configUSE_COUNTING_SEMAPHORES == 1)
#define __TOMMROC_MW_SEMAPHORE_COUNTING_SEMAPHORES_TEMPLATE_IS_USED__
#endif
#endif
#endif


/******************** CMSIS_V2 RTOS template */
#if defined (__TOMMROC_MW_USE_SEMAPHORE_CMSIS_V2_RTOS_TEMPLATE__)
#if !defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)
#error "tommRoCMw semaphore CMSIS_V2 RTOS template NEED thread CMSIS_V2 RTOS template"
#endif

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
#error "tommRoCMw semaphore template multiple definition"
#else
#define __TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__
#if (configUSE_COUNTING_SEMAPHORES == 1)
#define __TOMMROC_MW_SEMAPHORE_COUNTING_SEMAPHORES_TEMPLATE_IS_USED__
#endif
#endif
#endif


/******************** NXP OSA template */
#if defined (__TOMMROC_MW_USE_SEMAPHORE_NXP_OSA_TEMPLATE__)
#if !defined (__TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__)
#error "tommRoCMw semaphore NXP OSA template NEED thread NXP OSA template"
#endif

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
#error "tommRoCMw semaphore template multiple definition"
#else
#define __TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__
#if (configUSE_COUNTING_SEMAPHORES == 1)
#define __TOMMROC_MW_SEMAPHORE_COUNTING_SEMAPHORES_TEMPLATE_IS_USED__
#endif
#endif
#endif


/******************** Semaphore.h template */
#if defined (__TOMMROC_MW_USE_SEMAPHORE_SEMAPHORE_H_TEMPLATE__)
#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
#error "tommRoCMw semaphore template multiple definition"
#else
#define __TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__
#define __TOMMROC_MW_SEMAPHORE_COUNTING_SEMAPHORES_TEMPLATE_IS_USED__
#endif
#endif


/******************** ThreadX template */
#if defined (__TOMMROC_MW_USE_SEMAPHORE_THREADX_TEMPLATE__)
#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
#error "tommRoCMw semaphore template multiple definition"
#else
#define __TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__
#define __TOMMROC_MW_SEMAPHORE_COUNTING_SEMAPHORES_TEMPLATE_IS_USED__
#endif
#endif


/******************** Windows.h template */
#if defined (__TOMMROC_MW_USE_SEMAPHORE_WINDOWS_H_TEMPLATE__)
#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
#error "tommRoCMw semaphore template multiple definition"
#else
#define __TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__
#define __TOMMROC_MW_SEMAPHORE_COUNTING_SEMAPHORES_TEMPLATE_IS_USED__
#endif
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef struct {

/******************** CMSIS_V1 RTOS template */
#if defined (__TOMMROC_MW_USE_SEMAPHORE_CMSIS_V1_RTOS_TEMPLATE__)
#if defined (osCMSIS_RTX)
    uint32_t            osSemaphoreCb[2];
#endif
    osSemaphoreDef_t    osSemaphoreDef;
    osSemaphoreId       osSemaphoreId;


/******************** CMSIS_V2 RTOS template */
#elif defined (__TOMMROC_MW_USE_SEMAPHORE_CMSIS_V2_RTOS_TEMPLATE__)
    osSemaphoreAttr_t   osSemaphoreAttr;
    osSemaphoreId_t     osSemaphoreId;


/******************** NXP OSA template */
#elif defined (__TOMMROC_MW_USE_SEMAPHORE_NXP_OSA_TEMPLATE__)
    osaSemaphoreId_t    osaSemaphoreId;


/******************** Semaphore.h template */
#elif defined (__TOMMROC_MW_USE_SEMAPHORE_SEMAPHORE_H_TEMPLATE__)
    sem_t               sem;


/******************** ThreadX template */
#elif defined (__TOMMROC_MW_USE_SEMAPHORE_THREADX_TEMPLATE__)
    TX_SEMAPHORE        threadXSemaphore;


/******************** Windows.h template */
#elif defined (__TOMMROC_MW_USE_SEMAPHORE_WINDOWS_H_TEMPLATE__)
    HANDLE              handle;


#endif

} tommRoC_mw_template_semaphore_t;

#if defined (__TOMMROC_MW_USE_SEMAPHORE_CMSIS_V1_RTOS_TEMPLATE__)
#if defined (osCMSIS_RTX)
#define __EMPTY_tommRoC_mw_template_semaphore_t__
#else
#define __EMPTY_tommRoC_mw_template_semaphore_t__   \
{                                                   \
    /* .osSemaphoreDef */   { 0, },                 \
    /* .osSemaphoreId */     NULL,                  \
}
#endif

#elif defined (__TOMMROC_MW_USE_SEMAPHORE_CMSIS_V2_RTOS_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_semaphore_t__   \
{                                                   \
    /* .osSemaphoreAttr */   { NULL, 0, NULL, 0, }, \
    /* .osSemaphoreId */     NULL,                  \
}

#elif defined (__TOMMROC_MW_USE_SEMAPHORE_NXP_OSA_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_semaphore_t__   \
{                                                   \
    /* .osaSemaphoreId */   NULL,                   \
}

#elif defined (__TOMMROC_MW_USE_SEMAPHORE_SEMAPHORE_H_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_semaphore_t__                                       \
{                                                                                       \
    /* .sem */  { TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, __SIZEOF_SEM_T - 1, 0) },    \
}

#elif defined (__TOMMROC_MW_USE_SEMAPHORE_THREADX_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_semaphore_t__   \
{                                                   \
    /* .threadXSemaphore */ { 0 },                  \
}

#elif defined (__TOMMROC_MW_USE_SEMAPHORE_WINDOWS_H_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_semaphore_t__
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSSemaphoreStart(void);
tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSSemaphoreStop(void);

#endif

#endif
