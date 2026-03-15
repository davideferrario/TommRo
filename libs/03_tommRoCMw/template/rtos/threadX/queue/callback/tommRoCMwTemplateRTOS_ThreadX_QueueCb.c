
#if defined (__TOMMROC_MW_USE_QUEUE_THREADX_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_ThreadX_QueueCb.h"

#include "rtos/threadX/common/compatibility/tommRoCMwTemplateRTOS_ThreadX_Compatibility.h"
#include "rtos/threadX/common/util/tommRoCMwTemplateRTOS_ThreadX_Util.h"

#include "TOMMROC.h"

#include "TOMMROCMwTemplate.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
static ULONG _get_timeout(const uint32_t waitTimeoutMs) {

    if (QUEUE_NO_WAIT_TIMEOUT == waitTimeoutMs) {
        return TX_NO_WAIT;
    }

    if (QUEUE_INFINITE_TIMEOUT == waitTimeoutMs) {
        return TX_WAIT_FOREVER;
    }

    return TOMMROC_MW_TEMPLATE_RTOS_THREADX_COMMON_COMPATIBILITY_MS_TO_TICKS(waitTimeoutMs);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_QueueCb_Create(
                void*       const   inputQueuePtr,
        const   uint32_t            msgSizeByte,
        const   uint32_t            queueSizeByte) {

    tommRoC_mw_template_queue_t* queuePtr;
    TX_BYTE_POOL* appStackBytePoolPtr;
    VOID* pointer;
    UINT res;

    uint32_t queueSizeTXByte;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_QUEUE, ((tommRoC_mw_template_queue_t*)NULL)->threadXQueue);

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;
    
    // NOTE: msg size MUST be multiple of ULONG size.
    if (0 != msgSizeByte % sizeof(ULONG)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;   
    }

    queueSizeTXByte = ((0 == (queueSizeByte % sizeof(ULONG))) ? (queueSizeByte) : (queueSizeByte + sizeof(ULONG) - queueSizeByte % sizeof(ULONG)));
    
    // NOTE: queue size MUST be multiple of message size.
    if (0 != queueSizeTXByte % msgSizeByte) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;   
    }

    appStackBytePoolPtr = tommRoCMwTemplateRTOS_ThreadX_Util_GetAppStackBytePoolPtr();

    // Allocate stack for queue
    pointer = TX_NULL;
    res = tx_byte_allocate(appStackBytePoolPtr, &pointer, queueSizeTXByte, TX_NO_WAIT);

    if (TX_SUCCESS != res) {
        if (TX_NULL != pointer) {
            tx_byte_release(pointer);
        }
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    queuePtr->queueStartPtr = pointer;

    // NOTE: message_size parameter is expressed as words (ULONG) size
    res = tx_queue_create(&queuePtr->threadXQueue, TX_NULL, msgSizeByte / sizeof(ULONG), pointer, queueSizeTXByte);

    if (__THREADX_QUEUE_CREATE_SUCCESS_RESULT__ != res) {
        if (TX_NULL != pointer) {
            tx_byte_release(pointer);
        }
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_QueueCb_Put(
                void*       const   inputQueuePtr,
        const   void*       const   dataPtr,
        const   uint32_t            waitTimeoutMs) {

    ULONG wait_option;
    tommRoC_mw_template_queue_t* queuePtr;
    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_QUEUE, ((tommRoC_mw_template_queue_t*)NULL)->threadXQueue);

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_WAIT_FOREVER, wait_option);

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    wait_option = _get_timeout(waitTimeoutMs);

    res = tx_queue_send(&queuePtr->threadXQueue, (VOID*) dataPtr, wait_option);

    if (__THREADX_QUEUE_SEND_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_QueueCb_Get(
                void*       const   inputQueuePtr,
                void*       const   dataPtr,
        const   uint32_t            waitTimeoutMs) {

    ULONG wait_option;
    tommRoC_mw_template_queue_t* queuePtr;
    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_QUEUE, ((tommRoC_mw_template_queue_t*)NULL)->threadXQueue);

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_WAIT_FOREVER, wait_option);

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    wait_option = _get_timeout(waitTimeoutMs);

    res = tx_queue_receive(&queuePtr->threadXQueue, dataPtr, wait_option);

    if (__THREADX_QUEUE_RECEIVE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_QueueCb_InsideAmount(
                void*       const   inputQueuePtr,
                uint32_t*   const   amountPtr) {

    tommRoC_mw_template_queue_t* queuePtr;
    ULONG enqueued;
    ULONG available_storage;
    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_QUEUE, ((tommRoC_mw_template_queue_t*)NULL)->threadXQueue);

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    // NOTE: some parameters are TX_NULL because not interesting informations
    res = tx_queue_info_get(&queuePtr->threadXQueue, TX_NULL, &enqueued, &available_storage, TX_NULL, TX_NULL, TX_NULL);

    if (__THREADX_QUEUE_INFO_GET_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    *amountPtr = (uint32_t) enqueued;

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_QueueCb_FreeAmount(
                void*       const   inputQueuePtr,
                uint32_t*   const   amountPtr) {

    tommRoC_mw_template_queue_t* queuePtr;
    ULONG enqueued;
    ULONG available_storage;
    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_QUEUE, ((tommRoC_mw_template_queue_t*)NULL)->threadXQueue);

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    // NOTE: some parameters are TX_NULL because not interesting informations
    res = tx_queue_info_get(&queuePtr->threadXQueue, TX_NULL, &enqueued, &available_storage, TX_NULL, TX_NULL, TX_NULL);

    if (__THREADX_QUEUE_INFO_GET_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    *amountPtr = (uint32_t) available_storage;

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_QueueCb_Destroy(
                void*       const   inputQueuePtr) {

    tommRoC_mw_template_queue_t* queuePtr;
    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_QUEUE, ((tommRoC_mw_template_queue_t*)NULL)->threadXQueue);

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    res = tx_queue_delete(&queuePtr->threadXQueue);

    if (__THREADX_QUEUE_DELETE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    // Release stack for queue
    res = tx_byte_release(queuePtr->queueStartPtr);

    if (TX_SUCCESS != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
