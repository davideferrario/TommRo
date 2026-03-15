
#ifndef TOMMROC_MW_TEMPLATE_RTOS_CMSIS_V1_RTOS_TIMER_CB_H_
#define TOMMROC_MW_TEMPLATE_RTOS_CMSIS_V1_RTOS_TIMER_CB_H_

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

#if defined (__TOMMROC_MW_USE_TIMER_CMSIS_V1_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROCMw.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_TimerCb_Create(
        const   uint32_t                                periodMsec,
        const   tommRoC_mw_timer_type_enum_t            type,
        const   tommRoC_mw_timer_cb_funct_t             cbFunctPtr,
                void*                           const   inputTimerPtr);

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_TimerCb_Destroy(
                void*                           const   inputTimerPtr);
                
tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_TimerCb_Start(
                void*                           const   inputTimerPtr);
                
tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_TimerCb_Stop(
                void*                           const   inputTimerPtr);

#endif

#endif
