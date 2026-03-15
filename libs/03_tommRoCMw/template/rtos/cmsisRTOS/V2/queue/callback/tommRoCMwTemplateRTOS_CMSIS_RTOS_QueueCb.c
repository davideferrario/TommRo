
#if defined (__TOMMROC_MW_USE_QUEUE_CMSIS_V2_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_CMSIS_RTOS_QueueCb.h"

#include "rtos/cmsisRTOS/V2/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"

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
static TickType_t _msec_to_tick(const uint32_t millisec) {

    TickType_t ticks;

    if (osWaitForever == millisec) {
        return portMAX_DELAY;
    }

    if (0 == millisec) {
        return 0;
    }

    ticks = millisec / portTICK_PERIOD_MS;
    if (0 == ticks) {
        return 1;
    }

    return ticks;
}

static uint32_t _get_timeout(const uint32_t waitTimeoutMs) {

    if (QUEUE_NO_WAIT_TIMEOUT == waitTimeoutMs) {
        return 0;
    }

    if (QUEUE_INFINITE_TIMEOUT == waitTimeoutMs) {
        return osWaitForever;
    }

    return waitTimeoutMs;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_QueueCb_Create(
                void*       const   inputQueuePtr,
        const   uint32_t            msgSizeByte,
        const   uint32_t            queueSizeByte) {

    tommRoC_mw_template_queue_t* queuePtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(osMessageQueueAttr_t,    ((tommRoC_mw_template_queue_t*)NULL)->osMessageQueueAttr);
    TOMMROC_CTA_SIZE_OF_EQUALS(osMessageQueueId_t,      ((tommRoC_mw_template_queue_t*)NULL)->osMessageQueueId);

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&queuePtr->osMessageQueueAttr, 0x00, sizeof(queuePtr->osMessageQueueAttr)));

#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(queuePtr->osQueueCb, 0x00, sizeof(queuePtr->osQueueCb)));
    queuePtr->osMessageQDef.queue = queuePtr->osQueueCb;
#endif

    queuePtr->osMessageQueueId = osMessageQueueNew(queueSizeByte / msgSizeByte, msgSizeByte, &queuePtr->osMessageQueueAttr);

    if (__CMSIS_RTOS_MESSAGE_QUEUE_NEW_ON_ERROR_RESULT__ == queuePtr->osMessageQueueId) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_QueueCb_Put(
                void*       const   inputQueuePtr,
        const   void*       const   dataPtr,
        const   uint32_t            waitTimeoutMs) {

    uint32_t millisec;
    tommRoC_mw_template_queue_t* queuePtr;
    TickType_t ticks;
    osStatus_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osMessageQueueId_t, ((tommRoC_mw_template_queue_t*)NULL)->osMessageQueueId);

    TOMMROC_CTA_SIZE_OF_EQUALS(osWaitForever, uint32_t);

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    millisec = _get_timeout(waitTimeoutMs);

    ticks = _msec_to_tick(millisec);
    if (0 == ticks) {
        ticks = 1;
    }

    res = osMessageQueuePut(queuePtr->osMessageQueueId, dataPtr, 0U, ticks);

    if ((osErrorTimeout == res) || (osErrorResource == res)) {
        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    if (__CMSIS_RTOS_MESSAGE_QUEUE_PUT_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_QueueCb_Get(
                void*       const   inputQueuePtr,
                void*       const   dataPtr,
        const   uint32_t            waitTimeoutMs) {

    uint32_t millisec;
    tommRoC_mw_template_queue_t* queuePtr;
    TickType_t ticks;
    uint8_t msgPrio;
    osStatus_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osMessageQueueId_t, ((tommRoC_mw_template_queue_t*)NULL)->osMessageQueueId);

    TOMMROC_CTA_SIZE_OF_EQUALS(osWaitForever, uint32_t);

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    millisec = _get_timeout(waitTimeoutMs);

    ticks = _msec_to_tick(millisec);
    if (0 == ticks) {
        ticks = 1;
    }

    res = osMessageQueueGet(queuePtr->osMessageQueueId, dataPtr, &msgPrio, ticks);

    if ((osErrorTimeout == res) || (osErrorResource == res)) {
        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    if (__CMSIS_RTOS_MESSAGE_QUEUE_GET_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_DATA_NOT_AVAILABLE_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_QueueCb_InsideAmount(
                void*       const   inputQueuePtr,
                uint32_t*   const   amountPtr) {

    tommRoC_mw_template_queue_t* queuePtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(osMessageQueueId_t, ((tommRoC_mw_template_queue_t*)NULL)->osMessageQueueId);

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    *amountPtr = osMessageQueueGetCount(queuePtr->osMessageQueueId);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_QueueCb_FreeAmount(
                void*       const   inputQueuePtr,
                uint32_t*   const   amountPtr) {

    tommRoC_mw_template_queue_t* queuePtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(osMessageQueueId_t, ((tommRoC_mw_template_queue_t*)NULL)->osMessageQueueId);

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    *amountPtr = osMessageQueueGetSpace(queuePtr->osMessageQueueId);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_QueueCb_Destroy(
                void*       const   inputQueuePtr) {

    tommRoC_mw_template_queue_t* queuePtr;
    osStatus_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osMessageQueueId_t, ((tommRoC_mw_template_queue_t*)NULL)->osMessageQueueId);

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    res = osMessageQueueDelete(queuePtr->osMessageQueueId);

    if (__CMSIS_RTOS_MESSAGE_QUEUE_DELETE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
