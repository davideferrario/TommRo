
#ifndef TOMMROC_MW_TEMPLATE_RTOS_TIMER_H_
#define TOMMROC_MW_TEMPLATE_RTOS_TIMER_H_

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
 *  - __TOMMROC_MW_USE_TIMER_CMSIS_V1_RTOS_TEMPLATE__       CMSIS_V1 RTOS timer
 *  - __TOMMROC_MW_USE_TIMER_CMSIS_V2_RTOS_TEMPLATE__       CMSIS_V2 RTOS timer
 *  - __TOMMROC_MW_USE_TIMER_NXP_OSA_TEMPLATE__             NXP OSA timer
 *  - __TOMMROC_MW_USE_TIMER_PTHREAD_TEMPLATE__             pthread library timer
 *  - __TOMMROC_MW_USE_TIMER_THREADX_TEMPLATE__             ThreadX library timer
 *  - __TOMMROC_MW_USE_TIMER_WINDOWS_H_TEMPLATE__           Windows timer
 */

#if defined (__TOMMROC_MW_USE_TIMER_CMSIS_RTOS_TEMPLATE__)
#error "replace __TOMMROC_MW_USE_TIMER_CMSIS_RTOS_TEMPLATE__ with __TOMMROC_MW_USE_TIMER_CMSIS_V1_RTOS_TEMPLATE__"
#endif

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"
#include "TOMMROCMw.h"

#if defined (__TOMMROC_MW_USE_TIMER_CMSIS_V1_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V1/common/CMSIS_RTOS/tommRoCMwTemplateRTOS_cmsis_os.h"
#include "rtos/cmsisRTOS/V1/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
#if defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
#include "freertos/FreeRTOSConfig.h"
#else
#include "FreeRTOSConfig.h"
#endif
#if !defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
#if defined (configSUPPORT_STATIC_ALLOCATION) && (0 != configSUPPORT_STATIC_ALLOCATION)
#error "configSUPPORT_STATIC_ALLOCATION not supported"
#endif
#endif
#endif

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
#include "RTX_Conf_CM.h"
#endif

#elif defined (__TOMMROC_MW_USE_TIMER_CMSIS_V2_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V2/common/CMSIS_RTOS/tommRoCMwTemplateRTOS_cmsis_os.h"
#include "rtos/cmsisRTOS/V2/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
#if defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
#include "freertos/FreeRTOSConfig.h"
#else
#include "FreeRTOSConfig.h"
#endif
#endif

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
#include "RTX_Conf_CM.h"
#endif

#elif defined (__TOMMROC_MW_USE_TIMER_NXP_OSA_TEMPLATE__)
#include "fsl_os_abstraction.h"
#include "FreeRTOSConfig.h"
#if defined (configSUPPORT_STATIC_ALLOCATION) && (0 != configSUPPORT_STATIC_ALLOCATION)
#error "configSUPPORT_STATIC_ALLOCATION not supported"
#endif

#elif defined (__TOMMROC_MW_USE_TIMER_CMSIS_V2_RTOS_TEMPLATE__)

#elif defined (__TOMMROC_MW_USE_TIMER_PTHREAD_TEMPLATE__)
#include <pthread.h>

#elif defined (__TOMMROC_MW_USE_TIMER_THREADX_TEMPLATE__)
#include "tx_api.h"

#elif defined (__TOMMROC_MW_USE_TIMER_WINDOWS_H_TEMPLATE__)
#include <windows.h>

#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************** CMSIS_V1 RTOS template */
#if defined (__TOMMROC_MW_USE_TIMER_CMSIS_V1_RTOS_TEMPLATE__)
#if defined (__TOMMROC_MW_TIMER_TEMPLATE_IS_USED__)
#error "tommRoCMw timer template multiple definition"
#else
#define __TOMMROC_MW_TIMER_TEMPLATE_IS_USED__
#endif
#endif


/******************** CMSIS_V2 RTOS template */
#if defined (__TOMMROC_MW_USE_TIMER_CMSIS_V2_RTOS_TEMPLATE__)
#if defined (__TOMMROC_MW_TIMER_TEMPLATE_IS_USED__)
#error "tommRoCMw timer template multiple definition"
#else
#define __TOMMROC_MW_TIMER_TEMPLATE_IS_USED__
#endif
#endif


/******************** NXP OSA template */
#if defined (__TOMMROC_MW_USE_TIMER_NXP_OSA_TEMPLATE__)
#if defined (__TOMMROC_MW_TIMER_TEMPLATE_IS_USED__)
#error "tommRoCMw timer template multiple definition"
#else
#define __TOMMROC_MW_TIMER_TEMPLATE_IS_USED__
#endif
#endif


/******************** PThread template */
#if defined (__TOMMROC_MW_USE_TIMER_PTHREAD_TEMPLATE__)
#if defined (__TOMMROC_MW_TIMER_TEMPLATE_IS_USED__)
#error "tommRoCMw timer template multiple definition"
#else
#define __TOMMROC_MW_TIMER_TEMPLATE_IS_USED__
#endif
#endif


/******************** ThreadX template */
#if defined (__TOMMROC_MW_USE_TIMER_THREADX_TEMPLATE__)
#if defined (__TOMMROC_MW_TIMER_TEMPLATE_IS_USED__)
#error "tommRoCMw timer template multiple definition"
#else
#define __TOMMROC_MW_TIMER_TEMPLATE_IS_USED__
#endif
#endif


/******************** Windows.h template */
#if defined (__TOMMROC_MW_USE_TIMER_WINDOWS_H_TEMPLATE__)
#if defined (__TOMMROC_MW_TIMER_TEMPLATE_IS_USED__)
#error "tommRoCMw timer template multiple definition"
#else
#define __TOMMROC_MW_TIMER_TEMPLATE_IS_USED__
#endif
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef struct {

/******************** CMSIS_V1 RTOS template */
#if defined (__TOMMROC_MW_USE_TIMER_CMSIS_V1_RTOS_TEMPLATE__)


/******************** CMSIS_V2 RTOS template */
#elif defined (__TOMMROC_MW_USE_TIMER_CMSIS_V2_RTOS_TEMPLATE__)


/******************** NXP OSA template */
#elif defined (__TOMMROC_MW_USE_TIMER_NXP_OSA_TEMPLATE__)


/******************** PThread template */
#elif defined (__TOMMROC_MW_USE_TIMER_PTHREAD_TEMPLATE__)


/******************** ThreadX template */
#elif defined (__TOMMROC_MW_USE_TIMER_THREADX_TEMPLATE__)


/******************** Windows.h template */
#elif defined (__TOMMROC_MW_USE_TIMER_WINDOWS_H_TEMPLATE__)


#endif

} tommRoC_mw_template_timer_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_MW_TIMER_TEMPLATE_IS_USED__)

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSTimerStart(void);
tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSTimerStop(void);

#endif

#endif
