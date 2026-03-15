
#ifndef TOMMROC_MW_TEMPLATE_RTOS_THREADX_FREERTOS_CELLULAR_PORT_H_
#define TOMMROC_MW_TEMPLATE_RTOS_THREADX_FREERTOS_CELLULAR_PORT_H_

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

#if defined (__TOMMROC_MW_USE_QUEUE_THREADX_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSQueue.h"

#include <stddef.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef void* PlatformEventGroupHandle_t;
typedef void* QueueHandle_t;

typedef uint32_t PlatformTickType;
typedef PlatformTickType TickType_t;
typedef uint32_t PlatformEventGroup_EventBits;
typedef PlatformEventGroup_EventBits EventBits_t;
typedef int32_t BaseType_t;
typedef uint32_t UBaseType_t;

// NOTE: because ThreadX queue msq size MUST be multiple of ULONG size AND FreeRTOSCellular Queue msg size is 1 byte, re-define a specific ThreadX for FreeRTOSCellular Queue
typedef struct {

    tommRoC_mw_template_queue_t mwQueue;
    uint32_t                    msgSizeByte;

} tommRoC_mw_template_threadx_free_rtos_cellular_port_queue_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

PlatformEventGroupHandle_t xEventGroupCreate(void);
void vEventGroupDelete(PlatformEventGroupHandle_t xEventGroup);
EventBits_t xEventGroupClearBits(PlatformEventGroupHandle_t xEventGroup, const EventBits_t uxBitsToClear);
EventBits_t xEventGroupSetBits(PlatformEventGroupHandle_t xEventGroup, const EventBits_t uxBitsToSet);
EventBits_t xEventGroupWaitBits(PlatformEventGroupHandle_t xEventGroup, const EventBits_t uxBitsToWaitFor, const BaseType_t xClearOnExit, const BaseType_t xWaitForAllBits, TickType_t xTicksToWait);

QueueHandle_t xQueueGenericCreate(const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize, const uint8_t ucQueueType);
void vQueueDelete(QueueHandle_t xQueue);
BaseType_t xQueueGenericSend(QueueHandle_t xQueue, const void* const pvItemToQueue, TickType_t xTicksToWait, const BaseType_t xCopyPosition);
BaseType_t xQueueReceive(QueueHandle_t xQueue, void* const pvBuffer, TickType_t xTicksToWait);

void* pvPortMalloc(size_t xSize);
void vPortFree(void* pv);

#endif

#endif
