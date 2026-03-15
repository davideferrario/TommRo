
#ifndef TOMMROC_MW_TEMPLATE_RTOS_THREAD_H_
#define TOMMROC_MW_TEMPLATE_RTOS_THREAD_H_

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
 *  - __TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__      CMSIS_V1 RTOS thread
 *                                                          NOTE: define __TOMMROC_MW_USE_CMSIS_RTOS_RTX_TEMPLATE__ if RTX is used.
 *  - __TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__      CMSIS_V2 RTOS thread
 *  - __TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__            NXP OSA thread
 *  - __TOMMROC_MW_USE_THREAD_PTHREAD_TEMPLATE__            pthread library thread
 *  - __TOMMROC_MW_USE_THREAD_THREADX_TEMPLATE__            ThreadX library thread
 *  - __TOMMROC_MW_USE_THREAD_WINDOWS_H_TEMPLATE__          Windows thread
 */

#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_RTOS_TEMPLATE__)
#error "replace __TOMMROC_MW_USE_THREAD_CMSIS_RTOS_TEMPLATE__ with __TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__"
#endif

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"
#include "TOMMROCMw.h"

#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/common/tommRoCMwTemplateRTOS_CMSIS_RTOS_Common.h"
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

#elif defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/common/tommRoCMwTemplateRTOS_CMSIS_RTOS_Common.h"
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

#elif defined (__TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__)
#include "fsl_os_abstraction.h"
#include "FreeRTOSConfig.h"
#if defined (configSUPPORT_STATIC_ALLOCATION) && (0 != configSUPPORT_STATIC_ALLOCATION)
#error "configSUPPORT_STATIC_ALLOCATION not supported"
#endif

#elif defined (__TOMMROC_MW_USE_THREAD_PTHREAD_TEMPLATE__)
#include <pthread.h>

#elif defined (__TOMMROC_MW_USE_THREAD_THREADX_TEMPLATE__)
#include "rtos/threadX/common/util/tommRoCMwTemplateRTOS_ThreadX_Util.h"

#include "app_threadx.h"

#include "tx_api.h"

#elif defined (__TOMMROC_MW_USE_THREAD_WINDOWS_H_TEMPLATE__)
#include <windows.h>

#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************** CMSIS_V1 RTOS template */
#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
#error "tommRoCMw thread template multiple definition"
#else
#define __TOMMROC_MW_THREAD_TEMPLATE_IS_USED__
#endif
#endif


/******************** CMSIS_V2 RTOS template */
#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
#error "tommRoCMw thread template multiple definition"
#else
#define __TOMMROC_MW_THREAD_TEMPLATE_IS_USED__
#endif
#endif


/******************** NXP OSA template */
#if defined (__TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__)
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
#error "tommRoCMw thread template multiple definition"
#else
#define __TOMMROC_MW_THREAD_TEMPLATE_IS_USED__
#endif
#endif


/******************** PThread template */
#if defined (__TOMMROC_MW_USE_THREAD_PTHREAD_TEMPLATE__)
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
#error "tommRoCMw thread template multiple definition"
#else
#define __TOMMROC_MW_THREAD_TEMPLATE_IS_USED__
#endif
#endif


/******************** ThreadX template */
#if defined (__TOMMROC_MW_USE_THREAD_THREADX_TEMPLATE__)
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
#error "tommRoCMw thread template multiple definition"
#else
#define __TOMMROC_MW_THREAD_TEMPLATE_IS_USED__
#endif
#endif


/******************** Windows.h template */
#if defined (__TOMMROC_MW_USE_THREAD_WINDOWS_H_TEMPLATE__)
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
#error "tommRoCMw thread template multiple definition"
#else
#define __TOMMROC_MW_THREAD_TEMPLATE_IS_USED__
#endif
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/******************** CMSIS_V1 RTOS template */
#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)
typedef osThreadId      tommRoC_mw_template_thread_id_t;

/******************** CMSIS_V2 RTOS template */
#elif defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)
typedef osThreadId_t    tommRoC_mw_template_thread_id_t;

/******************** NXP OSA template */
#elif defined (__TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__)
typedef osaTaskId_t     tommRoC_mw_template_thread_id_t;

/******************** PThread template */
#elif defined (__TOMMROC_MW_USE_THREAD_PTHREAD_TEMPLATE__)
typedef pthread_t       tommRoC_mw_template_thread_id_t;

/******************** ThreadX template */
#elif defined (__TOMMROC_MW_USE_THREAD_THREADX_TEMPLATE__)
typedef TX_THREAD*      tommRoC_mw_template_thread_id_t;

/******************** Windows.h template */
#elif defined (__TOMMROC_MW_USE_THREAD_WINDOWS_H_TEMPLATE__)

#endif


typedef struct {

/******************** CMSIS_V1 RTOS template */
#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)
    osThreadDef_t       osThreadDef;
    osThreadId          osThreadId;


/******************** CMSIS_V2 RTOS template */
#elif defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)
    osThreadAttr_t      osThreadAttr;
    osThreadId_t        osThreadId;


/******************** NXP OSA template */
#elif defined (__TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__)
    osaThreadDef_t      osaThreadDef;
    osaTaskId_t         osaTaskId;


/******************** PThread template */
#elif defined (__TOMMROC_MW_USE_THREAD_PTHREAD_TEMPLATE__)
    pthread_t           pThread;
    void*               handleArgPtr;


/******************** ThreadX template */
#elif defined (__TOMMROC_MW_USE_THREAD_THREADX_TEMPLATE__)
    TX_THREAD           threadXThread;
    VOID*               threadStackPtr;
    struct {
        tommRoC_mw_thread_main_funct_t  mainThread;
        void*                           mainThreadArgPtr;
    } entryFunctionParam;


/******************** Windows.h template */
#elif defined (__TOMMROC_MW_USE_THREAD_WINDOWS_H_TEMPLATE__)
    HANDLE              handle;


#endif

} tommRoC_mw_template_thread_t;

#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_thread_t__                      \
{                                                                   \
    /* .osThreadDef */  { NULL, NULL, osPriorityNormal, 0, 0, },    \
    /* .osThreadId */     NULL,                                     \
}

#elif defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_thread_t__                                  \
{                                                                               \
    /* .osThreadAttr */ { NULL, 0, NULL, 0, NULL, 0, osPriorityNormal, 0, 0, }, \
    /* .osThreadId */   NULL,                                                   \
}

#elif defined (__TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_thread_t__              \
{                                                           \
    /* .osaThreadDef */ {                                   \
                        /* .pthread */      NULL,           \
                        /* .tpriority */    0,              \
                        /* .instances */    0,              \
                        /* .stacksize */    0,              \
                        /* .tstack */       NULL,           \
                        /* .tlink */        NULL,           \
                        /* .tname */        NULL,           \
                        /* .useFloat */,    (bool_t) false, \
                        },                                  \
    /* .osaTaskId */    NULL,                               \
}

#elif defined (__TOMMROC_MW_USE_THREAD_PTHREAD_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_thread_t__  \
{                                               \
    /* .pThread */      0,                      \
    /* .handleArgPtr */ NULL,                   \
}

#elif defined (__TOMMROC_MW_USE_THREAD_THREADX_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_thread_t__  \
{                                               \
    /* .threadXThread */    { 0 },              \
    /* .threadStackPtr */   NULL,               \
    {                                           \
        /* .mainThread */       NULL,           \
        /* .mainThreadArgPtr */ NULL,           \
    },                                          \
}

#elif defined (__TOMMROC_MW_USE_THREAD_WINDOWS_H_TEMPLATE__)
#define __EMPTY_tommRoC_mw_template_thread_t__
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSThreadStart(void);
tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSThreadStop(void);

#endif

#endif
