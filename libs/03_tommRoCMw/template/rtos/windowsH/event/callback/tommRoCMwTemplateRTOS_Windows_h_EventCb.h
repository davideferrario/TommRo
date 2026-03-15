
#ifndef TOMMROC_MW_TEMPLATE_RTOS_WINDOWS_H_EVENT_CB_H_
#define TOMMROC_MW_TEMPLATE_RTOS_WINDOWS_H_EVENT_CB_H_

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

#if defined (__TOMMROC_MW_USE_EVENT_WINDOWS_H_TEMPLATE__)

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

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_EventCb_Create(
                void*   const   inputEventPtr);

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_EventCb_Signal(
                void*   const   inputEventPtr);

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_EventCb_WaitForAll(
                void*   const   inputEventsPtr,
        const   uint8_t         inputEventsAmount,
        const   uint32_t        waitTimeoutMs);

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_EventCb_WaitForAny(
                void*   const   inputEventsPtr,
        const   uint8_t         inputEventsAmount,
        const   uint32_t        waitTimeoutMs,
                void**  const   inputSignaledEventPtr);

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_EventCb_Clear(
                void*   const   inputEventPtr);

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_EventCb_Destroy(
                void*   const   inputEventPtr);

#endif

#endif
