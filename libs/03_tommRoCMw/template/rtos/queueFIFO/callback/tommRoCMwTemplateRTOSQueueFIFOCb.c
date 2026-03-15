
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSQueueFIFOCb.h"

#include "TOMMROC.h"
#include "TOMMROCMw.h"

#include "TOMMROCMwTemplate.h"

#include <stdlib.h>

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
static tommRoC_err_enum_t _put(
        const   tommRoC_queue_t*    const   queueHandlePtr,
        const   void*               const   dataPtr,
        const   uint32_t                    msgSizeByte) {

    uint32_t freeObjAmount;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCQueueFreeObjAmount(queueHandlePtr, 0, &freeObjAmount));

    if (0 == freeObjAmount) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCQueuePush(queueHandlePtr, 0, dataPtr, msgSizeByte));

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _get(
        const   tommRoC_queue_t*    const   queueHandlePtr,
                void*               const   dataPtr,
        const   uint32_t                    msgSizeByte) {

    uint32_t insideObjAmount;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCQueueInsideObjAmount(queueHandlePtr, 0, &insideObjAmount));

    if (0 == insideObjAmount) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCQueuePop(queueHandlePtr, 0, dataPtr, msgSizeByte));

    return TOMMRO_C_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSQueueFIFOCb_Create(
                tommRoC_mw_template_rtos_queue_fifo_t*  const   inputRTOSQueueFIFOPtr,
        const   uint32_t                                        msgSizeByte,
        const   uint32_t                                        queueSizeByte) {

    void* dataBufferPtr;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwMutexCreate(&inputRTOSQueueFIFOPtr->mutex));

    // Allocate stack for queue
    dataBufferPtr = malloc(queueSizeByte);

    if (NULL == dataBufferPtr) {
        TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexDestroy(&inputRTOSQueueFIFOPtr->mutex));
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    inputRTOSQueueFIFOPtr->dataBufferPtr    = dataBufferPtr;
    inputRTOSQueueFIFOPtr->msgSizeByte      = msgSizeByte;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFIFOInit(msgSizeByte, inputRTOSQueueFIFOPtr->dataBufferPtr, queueSizeByte, NULL, &inputRTOSQueueFIFOPtr->FIFO));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCQueueInit(&inputRTOSQueueFIFOPtr->FIFO, 1, NULL, &inputRTOSQueueFIFOPtr->queue));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSQueueFIFOCb_Put(
                tommRoC_mw_template_rtos_queue_fifo_t*  const   inputRTOSQueueFIFOPtr,
        const   void*                                   const   dataPtr,
        const   uint32_t                                        waitTimeoutMs) {

    tommRoC_timer_t timer;
    uint32_t remainingMsec;

    tommRoC_err_enum_t res;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, ((0 == waitTimeoutMs) ? (1) : (waitTimeoutMs))));

    while (TOMMRO_C_TIMER_NOT_EXPIRED_ERR == tommRoCTimerIsExpired(&timer)) {

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerRemaining(&timer, &remainingMsec));

        TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwMutexLock(&inputRTOSQueueFIFOPtr->mutex, ((0 == remainingMsec) ? (1) : (remainingMsec))));
        res = _put(&inputRTOSQueueFIFOPtr->queue, dataPtr, inputRTOSQueueFIFOPtr->msgSizeByte);
        TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexUnLock(&inputRTOSQueueFIFOPtr->mutex));

        if (TOMMRO_C_ERR_SUCCESS == res) {
            return TOMMRO_C_MW_ERR_SUCCESS;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(0));
    }

    return TOMMRO_C_MW_TIMEOUT_ERR;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSQueueFIFOCb_Get(
                tommRoC_mw_template_rtos_queue_fifo_t*  const   inputRTOSQueueFIFOPtr,
                void*                                   const   dataPtr,
        const   uint32_t                                        waitTimeoutMs) {

    tommRoC_timer_t timer;
    uint32_t remainingMsec;

    tommRoC_err_enum_t res;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, ((0 == waitTimeoutMs) ? (1) : (waitTimeoutMs))));

    while (TOMMRO_C_TIMER_NOT_EXPIRED_ERR == tommRoCTimerIsExpired(&timer)) {

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerRemaining(&timer, &remainingMsec));

        TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwMutexLock(&inputRTOSQueueFIFOPtr->mutex, ((0 == remainingMsec) ? (1) : (remainingMsec))));
        res = _get(&inputRTOSQueueFIFOPtr->queue, dataPtr, inputRTOSQueueFIFOPtr->msgSizeByte);
        TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexUnLock(&inputRTOSQueueFIFOPtr->mutex));

        if (TOMMRO_C_ERR_SUCCESS == res) {
            return TOMMRO_C_MW_ERR_SUCCESS;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(0));
    }

    return TOMMRO_C_MW_TIMEOUT_ERR;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSQueueFIFOCb_InsideAmount(
                tommRoC_mw_template_rtos_queue_fifo_t*  const   inputRTOSQueueFIFOPtr,
                uint32_t*                               const   amountPtr) {
                
    tommRoC_err_enum_t res;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwMutexLock(&inputRTOSQueueFIFOPtr->mutex, LOCK_MUTEX_INFINITE_TIMEOUT));
    res = tommRoCQueueInsideObjAmount(&inputRTOSQueueFIFOPtr->queue, 0, amountPtr);
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexUnLock(&inputRTOSQueueFIFOPtr->mutex));
    
    if (TOMMRO_C_ERR_SUCCESS != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSQueueFIFOCb_FreeAmount(
                tommRoC_mw_template_rtos_queue_fifo_t*  const   inputRTOSQueueFIFOPtr,
                uint32_t*                               const   amountPtr) {
                
    tommRoC_err_enum_t res;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwMutexLock(&inputRTOSQueueFIFOPtr->mutex, LOCK_MUTEX_INFINITE_TIMEOUT));
    res = tommRoCQueueFreeObjAmount(&inputRTOSQueueFIFOPtr->queue, 0, amountPtr);
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexUnLock(&inputRTOSQueueFIFOPtr->mutex));
    
    if (TOMMRO_C_ERR_SUCCESS != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSQueueFIFOCb_Destroy(
                tommRoC_mw_template_rtos_queue_fifo_t*  const   inputRTOSQueueFIFOPtr) {

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwMutexLock(&inputRTOSQueueFIFOPtr->mutex, LOCK_MUTEX_INFINITE_TIMEOUT));
    free(inputRTOSQueueFIFOPtr->dataBufferPtr);
    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexUnLock(&inputRTOSQueueFIFOPtr->mutex));

    TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwMutexDestroy(&inputRTOSQueueFIFOPtr->mutex));

    return TOMMRO_C_MW_ERR_SUCCESS;
}
