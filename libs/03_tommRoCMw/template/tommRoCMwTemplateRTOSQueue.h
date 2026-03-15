
#ifndef TOMMROC_MW_TEMPLATE_RTOS_QUEUE_H_
#define TOMMROC_MW_TEMPLATE_RTOS_QUEUE_H_

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
 *  - __TOMMROC_MW_USE_QUEUE_CMSIS_V1_RTOS_TEMPLATE__       CMSIS_V1 RTOS queue
 *  - __TOMMROC_MW_USE_QUEUE_CMSIS_V2_RTOS_TEMPLATE__       CMSIS_V2 RTOS queue
 *  - __TOMMROC_MW_USE_QUEUE_NXP_OSA_TEMPLATE__             NXP OSA queue
 *  - __TOMMROC_MW_USE_QUEUE_PTHREAD_TEMPLATE__             pthread library queue
 *  - __TOMMROC_MW_USE_QUEUE_THREADX_TEMPLATE__             ThreadX library queue
 *  - __TOMMROC_MW_USE_QUEUE_WINDOWS_H_TEMPLATE__           Windows queue
 */

#if defined (__TOMMROC_MW_USE_QUEUE_CMSIS_RTOS_TEMPLATE__)
#error "replace __TOMMROC_MW_USE_QUEUE_CMSIS_RTOS_TEMPLATE__ with __TOMMROC_MW_USE_QUEUE_CMSIS_V1_RTOS_TEMPLATE__"
#endif

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"
#include "TOMMROCMw.h"

#if defined (__TOMMROC_MW_USE_QUEUE_CMSIS_V1_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V1/common/CMSIS_RTOS/tommRoCMwTemplateRTOS_cmsis_os.h"

#elif defined (__TOMMROC_MW_USE_QUEUE_CMSIS_V2_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V2/common/CMSIS_RTOS/tommRoCMwTemplateRTOS_cmsis_os.h"

#elif defined (__TOMMROC_MW_USE_QUEUE_NXP_OSA_TEMPLATE__)
#include "fsl_os_abstraction.h"

#elif defined (__TOMMROC_MW_USE_QUEUE_PTHREAD_TEMPLATE__)
#include "rtos/queueFIFO/tommRoCMwTemplateRTOSQueueFIFO.h"

#elif defined (__TOMMROC_MW_USE_QUEUE_THREADX_TEMPLATE__)
#include "tx_api.h"

#elif defined (__TOMMROC_MW_USE_QUEUE_WINDOWS_H_TEMPLATE__)
#include "rtos/queueFIFO/tommRoCMwTemplateRTOSQueueFIFO.h"

#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************** CMSIS_V1 RTOS template */
#if defined (__TOMMROC_MW_USE_QUEUE_CMSIS_V1_RTOS_TEMPLATE__)
#if !defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)
#error "tommRoCMw queue CMSIS_V1 RTOS template NEED thread CMSIS_V1 RTOS template"
#endif

#if defined (__TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__)
#error "tommRoCMw queue template multiple definition"
#else
#define __TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__
#endif
#endif


/******************** CMSIS_V2 RTOS template */
#if defined (__TOMMROC_MW_USE_QUEUE_CMSIS_V2_RTOS_TEMPLATE__)
#if !defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)
#error "tommRoCMw queue CMSIS_V2 RTOS template NEED thread CMSIS_V2 RTOS template"
#endif

#if defined (__TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__)
#error "tommRoCMw queue template multiple definition"
#else
#define __TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__
#endif
#endif


/******************** NXP OSA template */
#if defined (__TOMMROC_MW_USE_QUEUE_NXP_OSA_TEMPLATE__)
#if !defined (__TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__)
#error "tommRoCMw queue NXP OSA template NEED thread NXP OSA template"
#endif

#if defined (__TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__)
#error "tommRoCMw queue template multiple definition"
#else
#define __TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__
#endif
#endif


/******************** PThread template */
#if defined (__TOMMROC_MW_USE_QUEUE_PTHREAD_TEMPLATE__)
#if defined (__TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__)
#error "tommRoCMw queue template multiple definition"
#else
#define __TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__
#endif
#endif


/******************** ThreadX template */
#if defined (__TOMMROC_MW_USE_QUEUE_THREADX_TEMPLATE__)
#if defined (__TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__)
#error "tommRoCMw queue template multiple definition"
#else
#define __TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__
#endif
#endif


/******************** Windows.h template */
#if defined (__TOMMROC_MW_USE_QUEUE_WINDOWS_H_TEMPLATE__)
#if defined (__TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__)
#error "tommRoCMw queue template multiple definition"
#else
#define __TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__
#endif
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef struct {

/******************** CMSIS_V1 RTOS template */
#if defined (__TOMMROC_MW_USE_QUEUE_CMSIS_V1_RTOS_TEMPLATE__)
#if defined (osCMSIS_RTX)
    uint32_t                                osQueueCb[4];
#endif
    osMessageQDef_t                         osMessageQDef;
    osMessageQId                            osMessageQId;


/******************** CMSIS_V2 RTOS template */
#elif defined (__TOMMROC_MW_USE_QUEUE_CMSIS_V2_RTOS_TEMPLATE__)
#if defined (osCMSIS_RTX)
    uint32_t                                osQueueCb[4];
#endif
    osMessageQueueAttr_t                    osMessageQueueAttr;
    osMessageQueueId_t                      osMessageQueueId;


/******************** NXP OSA template */
#elif defined (__TOMMROC_MW_USE_QUEUE_NXP_OSA_TEMPLATE__)
    osaMsgQId_t                             osaMsgQId;


/******************** PThread template */
#elif defined (__TOMMROC_MW_USE_QUEUE_PTHREAD_TEMPLATE__)
    tommRoC_mw_template_rtos_queue_fifo_t   RTOSQueueFIFO;


/******************** ThreadX template */
#elif defined (__TOMMROC_MW_USE_QUEUE_THREADX_TEMPLATE__)
    TX_QUEUE                                threadXQueue;
    VOID*                                   queueStartPtr;

/******************** Windows.h template */
#elif defined (__TOMMROC_MW_USE_QUEUE_WINDOWS_H_TEMPLATE__)
    tommRoC_mw_template_rtos_queue_fifo_t   RTOSQueueFIFO;


#endif

} tommRoC_mw_template_queue_t;

#if defined (__TOMMROC_MW_USE_QUEUE_CMSIS_V1_RTOS_TEMPLATE__)
#if defined (osCMSIS_RTX)
#define __EMPTY_tommRoC_mw_template_queue_t__
#else
#define __EMPTY_tommRoC_mw_template_queue_t__   \
{                                               \
    /* .osMessageQDef */    { 0, 0, },          \
    /* .osMessageQId */     NULL,               \
}
#endif

#elif defined (__TOMMROC_MW_USE_QUEUE_CMSIS_V2_RTOS_TEMPLATE__)
#if defined (osCMSIS_RTX)
#define __EMPTY_tommRoC_mw_template_queue_t__
#else
#define __EMPTY_tommRoC_mw_template_queue_t__                   \
{                                                               \
    /* .osMessageQueueAttr */   { NULL, 0, NULL, 0, NULL, 0, }, \
    /* .osMessageQueueId */     NULL,                           \
}
#endif

#elif defined (__TOMMROC_MW_USE_QUEUE_NXP_OSA_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_queue_t__

#elif defined (__TOMMROC_MW_USE_QUEUE_PTHREAD_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_queue_t__

#elif defined (__TOMMROC_MW_USE_QUEUE_THREADX_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_queue_t__   \
{                                               \
    /* .threadXQueue */    { 0 },               \
    /* .queueStartPtr */    NULL,               \
}

#elif defined (__TOMMROC_MW_USE_QUEUE_WINDOWS_H_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_queue_t__
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__)

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSQueueStart(void);
tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSQueueStop(void);

#endif

#endif
