
#if defined (__TOMMROC_MW_USE_QUEUE_THREADX_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_ThreadX_FreeRTOSCellularPort.h"

#include "rtos/threadX/common/util/tommRoCMwTemplateRTOS_ThreadX_Util.h"

#include "tommRoCMwTemplateRTOSQueue.h"

#include "TOMMROC.h"
#include "TOMMROCMw.h"

#include "tx_api.h"
#include "tx_port.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define pdFALSE ((uint32_t) 0)
#define pdTRUE  ((uint32_t) 1)
#define pdPASS  (pdTRUE)
#define pdFAIL  (pdFALSE)

#define __SUPPORTED_QUEUE_ITEM_SIZE_BYTE__  (TOMMROC_UTIL_U8_SIZE)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

PlatformEventGroupHandle_t xEventGroupCreate(void) {

    TX_BYTE_POOL* appStackBytePoolPtr;
    VOID* pointer;
    UINT res;

    appStackBytePoolPtr = tommRoCMwTemplateRTOS_ThreadX_Util_GetAppStackBytePoolPtr();

    // Allocate stack for event flags object
    pointer = TX_NULL;
    res = tx_byte_allocate(appStackBytePoolPtr, &pointer, sizeof(TX_EVENT_FLAGS_GROUP), TX_NO_WAIT);

    if (TX_SUCCESS != res) {
        if (TX_NULL != pointer) {
            tx_byte_release(pointer);
        }
        return NULL;
    }

    res = tx_event_flags_create((TX_EVENT_FLAGS_GROUP*) pointer, TX_NULL);
    if (TX_SUCCESS != res) {
        if (TX_NULL != pointer) {
            tx_byte_release(pointer);
        }
        return NULL;
    }

    return pointer;
}

void vEventGroupDelete(PlatformEventGroupHandle_t xEventGroup) {

    tx_event_flags_delete((TX_EVENT_FLAGS_GROUP*) xEventGroup);

    if (NULL != xEventGroup) {
        tx_byte_release(xEventGroup);
    }

    xEventGroup = NULL;
}

EventBits_t xEventGroupClearBits(PlatformEventGroupHandle_t xEventGroup, const EventBits_t uxBitsToClear) {
    ((TX_EVENT_FLAGS_GROUP*) xEventGroup)->tx_event_flags_group_current &= ~uxBitsToClear;
    return ((TX_EVENT_FLAGS_GROUP*) xEventGroup)->tx_event_flags_group_current;
}

EventBits_t xEventGroupSetBits(PlatformEventGroupHandle_t xEventGroup, const EventBits_t uxBitsToSet) {

    UINT res;

    res = tx_event_flags_set((TX_EVENT_FLAGS_GROUP*) xEventGroup, uxBitsToSet, TX_OR);
    if (TX_SUCCESS != res) {
        return 0;
    }

    return uxBitsToSet;
}

EventBits_t xEventGroupWaitBits(PlatformEventGroupHandle_t xEventGroup, const EventBits_t uxBitsToWaitFor, const BaseType_t xClearOnExit, const BaseType_t xWaitForAllBits, TickType_t xTicksToWait) {

    UINT get_option;
    ULONG event;

    UINT res;

    if (0 == xClearOnExit) {
        if (0 == xWaitForAllBits) {
            get_option = TX_OR;
        }
        else {
            get_option = TX_AND;
        }
    }
    else {
        if (0 == xWaitForAllBits) {
            get_option = TX_OR_CLEAR;
        }
        else {
            get_option = TX_AND_CLEAR;
        }
    }

    res = tx_event_flags_get((TX_EVENT_FLAGS_GROUP*) xEventGroup, uxBitsToWaitFor, get_option, &event, (0 == xTicksToWait) ? (1) : (xTicksToWait));
    if (TX_SUCCESS != res) {
        return 0;
    }

    return event;
}

QueueHandle_t xQueueGenericCreate(const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize, const uint8_t ucQueueType) {

    TX_BYTE_POOL* appStackBytePoolPtr;
    VOID* pointer;
    tommRoC_mw_template_threadx_free_rtos_cellular_port_queue_t* freeRTOSCellularPortQueuePtr;
    UINT res;

    uint32_t msgSizeByte;
    uint32_t queueSizeByte;

    TOMMROC_UTIL_UNUSED_PARAM(ucQueueType);

    if (__SUPPORTED_QUEUE_ITEM_SIZE_BYTE__ != uxItemSize) {
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        return NULL;
    }

    // NOTE: for ThreadX queue, msg size MUST be multiple of ULONG size.
    msgSizeByte     = ((0 == ((uint32_t) uxItemSize % sizeof(ULONG))) ? ((uint32_t) uxItemSize) : ((uint32_t) uxItemSize + sizeof(ULONG) - (uint32_t) uxItemSize % sizeof(ULONG)));
    queueSizeByte   = msgSizeByte * (uint32_t) uxQueueLength;

    appStackBytePoolPtr = tommRoCMwTemplateRTOS_ThreadX_Util_GetAppStackBytePoolPtr();

    // Allocate stack for queue object
    pointer = TX_NULL;
    res = tx_byte_allocate(appStackBytePoolPtr, &pointer, sizeof(tommRoC_mw_template_threadx_free_rtos_cellular_port_queue_t), TX_NO_WAIT);

    if (TX_SUCCESS != res) {
        if (TX_NULL != pointer) {
            tx_byte_release(pointer);
        }
        return NULL;
    }

    freeRTOSCellularPortQueuePtr = (tommRoC_mw_template_threadx_free_rtos_cellular_port_queue_t*) pointer;

    if (TOMMRO_C_MW_ERR_SUCCESS != tommRoCMwQueueCreate(&freeRTOSCellularPortQueuePtr->mwQueue, msgSizeByte, queueSizeByte)) {
        if (TX_NULL != pointer) {
            tx_byte_release(pointer);
        }
        return NULL;
    }

    freeRTOSCellularPortQueuePtr->msgSizeByte = uxItemSize;

    TOMMROC_ASSERT_EQUALS(freeRTOSCellularPortQueuePtr->msgSizeByte, __SUPPORTED_QUEUE_ITEM_SIZE_BYTE__);

    return (QueueHandle_t) freeRTOSCellularPortQueuePtr;
}

void vQueueDelete(QueueHandle_t xQueue) {

    TOMMROC_ASSERT_EQUALS(((tommRoC_mw_template_threadx_free_rtos_cellular_port_queue_t*) xQueue)->msgSizeByte, __SUPPORTED_QUEUE_ITEM_SIZE_BYTE__);

    tommRoCMwQueueDestroy(&((tommRoC_mw_template_threadx_free_rtos_cellular_port_queue_t*) xQueue)->mwQueue);

    if (NULL != xQueue) {
        tx_byte_release(xQueue);
    }

    xQueue = NULL;
}

BaseType_t xQueueGenericSend(QueueHandle_t xQueue, const void* const pvItemToQueue, TickType_t xTicksToWait, const BaseType_t xCopyPosition) {

    uint8_t tmpBuffer[sizeof(ULONG)];

    TOMMROC_UTIL_UNUSED_PARAM(xCopyPosition);

    TOMMROC_ASSERT_EQUALS(((tommRoC_mw_template_threadx_free_rtos_cellular_port_queue_t*) xQueue)->msgSizeByte, __SUPPORTED_QUEUE_ITEM_SIZE_BYTE__);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(tmpBuffer, pvItemToQueue, ((tommRoC_mw_template_threadx_free_rtos_cellular_port_queue_t*) xQueue)->msgSizeByte));

    if (TOMMRO_C_MW_ERR_SUCCESS != tommRoCMwQueuePut(xQueue, tmpBuffer, (0 == xTicksToWait) ? (1) : (xTicksToWait))) {
        return pdFAIL;
    }

    return pdPASS;
}

BaseType_t xQueueReceive(QueueHandle_t xQueue, void* const pvBuffer, TickType_t xTicksToWait) {

    uint8_t tmpBuffer[sizeof(ULONG)];

    TOMMROC_ASSERT_EQUALS(((tommRoC_mw_template_threadx_free_rtos_cellular_port_queue_t*) xQueue)->msgSizeByte, __SUPPORTED_QUEUE_ITEM_SIZE_BYTE__);

    if (TOMMRO_C_MW_ERR_SUCCESS != tommRoCMwQueueGet(xQueue, tmpBuffer, (0 == xTicksToWait) ? (1) : (xTicksToWait))) {
        return pdFAIL;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(pvBuffer, tmpBuffer, ((tommRoC_mw_template_threadx_free_rtos_cellular_port_queue_t*) xQueue)->msgSizeByte));

    return pdPASS;
}

void* pvPortMalloc(size_t xSize) {

    TX_BYTE_POOL* appStackBytePoolPtr;
    VOID* pointer;
    UINT res;

    appStackBytePoolPtr = tommRoCMwTemplateRTOS_ThreadX_Util_GetAppStackBytePoolPtr();

    // Allocate stack for Thread
    pointer = TX_NULL;
    res = tx_byte_allocate(appStackBytePoolPtr, &pointer, xSize, TX_NO_WAIT);

    if (TX_SUCCESS != res) {
        if (TX_NULL != pointer) {
            tx_byte_release(pointer);
        }
        return NULL;
    }

    return (void*) pointer;
}

void vPortFree(void* pv) {
    if (NULL != pv) {
        tx_byte_release(pv);
    }
}

#endif
