
#ifndef TOMMROC_MW_TEMPLATE_RTOS_EVENT_H_
#define TOMMROC_MW_TEMPLATE_RTOS_EVENT_H_

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
 *  - __TOMMROC_MW_USE_EVENT_CMSIS_V1_RTOS_TEMPLATE__       CMSIS_V1 RTOS event
 *  - __TOMMROC_MW_USE_EVENT_CMSIS_V2_RTOS_TEMPLATE__       CMSIS_V2 RTOS event
 *  - __TOMMROC_MW_USE_EVENT_NXP_OSA_TEMPLATE__             NXP OSA event
 *  - __TOMMROC_MW_USE_EVENT_PTHREAD_TEMPLATE__             pthread library event
 *  - __TOMMROC_MW_USE_EVENT_THREADX_TEMPLATE__             ThreadX library event
 *  - __TOMMROC_MW_USE_EVENT_WINDOWS_H_TEMPLATE__           Windows event
 */

#if defined (__TOMMROC_MW_USE_EVENT_CMSIS_RTOS_TEMPLATE__)
#error "replace __TOMMROC_MW_USE_EVENT_CMSIS_RTOS_TEMPLATE__ with __TOMMROC_MW_USE_EVENT_CMSIS_V1_RTOS_TEMPLATE__"
#endif

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"
#include "TOMMROCMw.h"

#if defined (__TOMMROC_MW_USE_EVENT_CMSIS_V1_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V1/common/CMSIS_RTOS/tommRoCMwTemplateRTOS_cmsis_os.h"

#elif defined (__TOMMROC_MW_USE_EVENT_CMSIS_V2_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V2/common/CMSIS_RTOS/tommRoCMwTemplateRTOS_cmsis_os.h"

#elif defined (__TOMMROC_MW_USE_EVENT_NXP_OSA_TEMPLATE__)
#include "fsl_os_abstraction.h"

#elif defined (__TOMMROC_MW_USE_EVENT_PTHREAD_TEMPLATE__)
#include <pthread.h>

#elif defined (__TOMMROC_MW_USE_EVENT_THREADX_TEMPLATE__)
#include "tx_api.h"

#elif defined (__TOMMROC_MW_USE_EVENT_WINDOWS_H_TEMPLATE__)
#include <windows.h>

#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************** CMSIS_V1 RTOS template */
#if defined (__TOMMROC_MW_USE_EVENT_CMSIS_V1_RTOS_TEMPLATE__)
#if !defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)
#error "tommRoCMw event CMSIS_V1 RTOS template NEED thread CMSIS_V1 RTOS template"
#endif

#if defined (__TOMMROC_MW_EVENT_TEMPLATE_IS_USED__)
#error "tommRoCMw event template multiple definition"
#else
#define __TOMMROC_MW_EVENT_TEMPLATE_IS_USED__
#endif
#endif


/******************** CMSIS_V2 RTOS template */
#if defined (__TOMMROC_MW_USE_EVENT_CMSIS_V2_RTOS_TEMPLATE__)
#if !defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)
#error "tommRoCMw event CMSIS_V2 RTOS template NEED thread CMSIS_V2 RTOS template"
#endif

#if defined (__TOMMROC_MW_EVENT_TEMPLATE_IS_USED__)
#error "tommRoCMw event template multiple definition"
#else
#define __TOMMROC_MW_EVENT_TEMPLATE_IS_USED__
#endif
#endif


/******************** NXP OSA template */
#if defined (__TOMMROC_MW_USE_EVENT_NXP_OSA_TEMPLATE__)
#if !defined (__TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__)
#error "tommRoCMw event NXP OSA template NEED thread NXP OSA template"
#endif

#if defined (__TOMMROC_MW_EVENT_TEMPLATE_IS_USED__)
#error "tommRoCMw event template multiple definition"
#else
#define __TOMMROC_MW_EVENT_TEMPLATE_IS_USED__
#endif
#endif


/******************** PThread template */
#if defined (__TOMMROC_MW_USE_EVENT_PTHREAD_TEMPLATE__)
#if defined (__TOMMROC_MW_EVENT_TEMPLATE_IS_USED__)
#error "tommRoCMw event template multiple definition"
#else
#define __TOMMROC_MW_EVENT_TEMPLATE_IS_USED__
#endif
#endif


/******************** ThreadX template */
#if defined (__TOMMROC_MW_USE_EVENT_THREADX_TEMPLATE__)
#if defined (__TOMMROC_MW_EVENT_TEMPLATE_IS_USED__)
#error "tommRoCMw event template multiple definition"
#else
#define __TOMMROC_MW_EVENT_TEMPLATE_IS_USED__
#endif
#endif


/******************** Windows.h template */
#if defined (__TOMMROC_MW_USE_EVENT_WINDOWS_H_TEMPLATE__)
#if defined (__TOMMROC_MW_EVENT_TEMPLATE_IS_USED__)
#error "tommRoCMw event template multiple definition"
#else
#define __TOMMROC_MW_EVENT_TEMPLATE_IS_USED__
#endif
#endif

#if defined (__TOMMROC_MW_EVENT_TEMPLATE_IS_USED__)
#if defined (__TOMMROC_MW_USE_EVENT_CMSIS_V1_RTOS_TEMPLATE__)

/**
 * NOTE:
 * From event_groups.h file.
 *
 * Although event groups are not related to ticks, for internal implementation
 * reasons the number of bits available for use in an event group is dependent
 * on the configUSE_16_BIT_TICKS setting in FreeRTOSConfig.h.  If
 * configUSE_16_BIT_TICKS is 1 then each event group contains 8 usable bits (bit
 * 0 to bit 7).  If configUSE_16_BIT_TICKS is set to 0 then each event group has
 * 24 usable bits (bit 0 to bit 23).  The EventBits_t type is used to store
 * event bits within an event group.
 */

#if (configUSE_16_BIT_TICKS == 1)
#define __TOMMROC_MW_EVENT_TEMPLATE_MAX_EVENT_AMOUNT__  (8)
#else
#define __TOMMROC_MW_EVENT_TEMPLATE_MAX_EVENT_AMOUNT__  (24)
#endif
#endif

#if defined (__TOMMROC_MW_USE_EVENT_CMSIS_V2_RTOS_TEMPLATE__)
#define __TOMMROC_MW_EVENT_TEMPLATE_MAX_EVENT_AMOUNT__  ()
#endif

#if defined (__TOMMROC_MW_USE_EVENT_NXP_OSA_TEMPLATE__)
#define __TOMMROC_MW_EVENT_TEMPLATE_MAX_EVENT_AMOUNT__  ()
#endif

#if defined (__TOMMROC_MW_USE_EVENT_PTHREAD_TEMPLATE__)
// NOTE: -1 means infinite events
#define __TOMMROC_MW_EVENT_TEMPLATE_MAX_EVENT_AMOUNT__  (-1)
#endif

#if defined (__TOMMROC_MW_USE_EVENT_THREADX_TEMPLATE__)
#define __TOMMROC_MW_EVENT_TEMPLATE_MAX_EVENT_AMOUNT__  (32)
#endif

#if defined (__TOMMROC_MW_USE_EVENT_WINDOWS_H_TEMPLATE__)
#define __TOMMROC_MW_EVENT_TEMPLATE_MAX_EVENT_AMOUNT__  ()
#endif
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef struct {

/******************** CMSIS_V1 RTOS template */
#if defined (__TOMMROC_MW_USE_EVENT_CMSIS_V1_RTOS_TEMPLATE__)
    EventBits_t event;


/******************** CMSIS_V2 RTOS template */
#elif defined (__TOMMROC_MW_USE_EVENT_CMSIS_V2_RTOS_TEMPLATE__)


/******************** NXP OSA template */
#elif defined (__TOMMROC_MW_USE_EVENT_NXP_OSA_TEMPLATE__)


/******************** PThread template */
#elif defined (__TOMMROC_MW_USE_EVENT_PTHREAD_TEMPLATE__)
    pthread_cond_t  pThreadCond;


/******************** ThreadX template */
#elif defined (__TOMMROC_MW_USE_EVENT_THREADX_TEMPLATE__)
    ULONG   event;


/******************** Windows.h template */
#elif defined (__TOMMROC_MW_USE_EVENT_WINDOWS_H_TEMPLATE__)
    HANDLE  handle;


#endif

} tommRoC_mw_template_event_t;

#if defined (__TOMMROC_MW_USE_EVENT_CMSIS_V1_RTOS_TEMPLATE__)
#if defined (osCMSIS_RTX)
#define __EMPTY_tommRoC_mw_template_event_t__
#else
#define __EMPTY_tommRoC_mw_template_event_t__   \
{                                               \
    /* .event */    0,                          \
}
#endif

#elif defined (__TOMMROC_MW_USE_EVENT_CMSIS_V2_RTOS_TEMPLATE__)

#elif defined (__TOMMROC_MW_USE_EVENT_NXP_OSA_TEMPLATE__)

#elif defined (__TOMMROC_MW_USE_EVENT_PTHREAD_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_event_t__                                                                   \
{                                                                                                               \
    /* .pThreadCond */ { .__size = TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, __SIZEOF_PTHREAD_COND_T - 1, 0) },  \
}

#elif defined (__TOMMROC_MW_USE_EVENT_THREADX_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_event_t__   \
{                                               \
    /* .event */    0,                          \
}

#elif defined (__TOMMROC_MW_USE_EVENT_WINDOWS_H_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_event_t__
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_MW_EVENT_TEMPLATE_IS_USED__)

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSEventStart(void);
tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSEventStop(void);

#endif

#endif
