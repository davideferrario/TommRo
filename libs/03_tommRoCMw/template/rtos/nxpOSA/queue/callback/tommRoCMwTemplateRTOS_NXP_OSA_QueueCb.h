
#ifndef TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_QUEUE_CB_H_
#define TOMMROC_MW_TEMPLATE_RTOS_NXP_OSA_QUEUE_CB_H_

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

#if defined (__TOMMROC_MW_USE_QUEUE_NXP_OSA_TEMPLATE__)

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

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_QueueCb_Create(
                void*       const   inputQueuePtr,
        const   uint32_t            msgSizeByte,
        const   uint32_t            queueSizeByte);

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_QueueCb_Put(
                void*       const   inputQueuePtr,
        const   void*       const   dataPtr,
        const   uint32_t            waitTimeoutMs);

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_QueueCb_Get(
                void*       const   inputQueuePtr,
                void*       const   dataPtr,
        const   uint32_t            waitTimeoutMs);

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_QueueCb_InsideAmount(
                void*       const   inputQueuePtr,
                uint32_t*   const   amountPtr);

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_QueueCb_FreeAmount(
                void*       const   inputQueuePtr,
                uint32_t*   const   amountPtr);

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_QueueCb_Destroy(
                void*       const   inputQueuePtr);

#endif

#endif
