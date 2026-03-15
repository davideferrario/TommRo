
#if defined (__TOMMROC_MW_USE_QUEUE_CMSIS_V1_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_CMSIS_RTOS_QueueCb.h"

#include "rtos/cmsisRTOS/V1/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"

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
static bool _in_handler_mode(void) {
    bool isFromISR;
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsIsFromISR(&isFromISR));
    return isFromISR;
}

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

static osStatus _put(
                osMessageQId            queue_id,
        const   void*           const   dataPtr,
        const   uint32_t                millisec) {

    portBASE_TYPE taskWoken = pdFALSE;
    TickType_t ticks;

    ticks = _msec_to_tick(millisec);
    if (0 == ticks) {
        ticks = 1;
    }

    if (_in_handler_mode()) {
        if (pdTRUE != xQueueSendFromISR(queue_id, dataPtr, &taskWoken)) {
            return osErrorOS;
        }
        portEND_SWITCHING_ISR(taskWoken);
    }
    else {
        if (pdTRUE != xQueueSend(queue_id, dataPtr, ticks)) {
            return osErrorOS;
        }
    }

    return osOK;
}

static osStatus _get(
                osMessageQId            queue_id,
                void*           const   dataPtr,
        const   uint32_t                millisec) {

    portBASE_TYPE taskWoken = pdFALSE;
    TickType_t ticks;

    osStatus res;

    ticks = _msec_to_tick(millisec);

    if (_in_handler_mode()) {
        if (pdTRUE == xQueueReceiveFromISR(queue_id, dataPtr, &taskWoken)) {
            res = osEventMessage;   // We have data
        }
        else {
            res = osOK;
        }
        portEND_SWITCHING_ISR(taskWoken);
    }
    else {
        if (xQueueReceive(queue_id, dataPtr, ticks) == pdTRUE) {
            res = osEventMessage;   // We have data
        }
        else {
            res = ((0 == ticks) ? (osOK) : (osEventTimeout));
        }
    }

    return res;
}

static uint32_t _inside_amount(const osMessageQId queue_id) {
    return (uint32_t) uxQueueMessagesWaiting((const QueueHandle_t) queue_id);
}

static uint32_t _free_amount(const osMessageQId queue_id) {
    return (uint32_t) uxQueueSpacesAvailable((const QueueHandle_t) queue_id);
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

    TOMMROC_CTA_SIZE_OF_EQUALS(osMessageQId,    ((tommRoC_mw_template_queue_t*)NULL)->osMessageQId);
    TOMMROC_CTA_SIZE_OF_EQUALS(osMessageQDef_t, ((tommRoC_mw_template_queue_t*)NULL)->osMessageQDef);

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&queuePtr->osMessageQDef, 0x00, sizeof(queuePtr->osMessageQDef)));

#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(queuePtr->osQueueCb, 0x00, sizeof(queuePtr->osQueueCb)));
    queuePtr->osMessageQDef.pool = queuePtr->osQueueCb;
#endif

    queuePtr->osMessageQDef.queue_sz    = queueSizeByte / msgSizeByte;
    queuePtr->osMessageQDef.item_sz     = msgSizeByte;

    queuePtr->osMessageQId = osMessageCreate(&queuePtr->osMessageQDef, NULL);

    if (__CMSIS_RTOS_QUEUE_CREATE_ON_ERROR_RESULT__ == queuePtr->osMessageQId) {
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
    osStatus res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osMessageQId, ((tommRoC_mw_template_queue_t*)NULL)->osMessageQId);

    TOMMROC_CTA_SIZE_OF_EQUALS(osWaitForever, uint32_t);

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    millisec = _get_timeout(waitTimeoutMs);

    res = _put(queuePtr->osMessageQId, dataPtr, millisec);

    if ((osEventTimeout == res) || (osErrorTimeoutResource == res)) {
        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    if (__CMSIS_RTOS_QUEUE_PUT_SUCCESS_RESULT__ != res) {
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
    osStatus res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osMessageQId, ((tommRoC_mw_template_queue_t*)NULL)->osMessageQId);

    TOMMROC_CTA_SIZE_OF_EQUALS(osWaitForever, uint32_t);

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    millisec = _get_timeout(waitTimeoutMs);

    res = _get(queuePtr->osMessageQId, dataPtr, millisec);

    if ((osEventTimeout == res) || (osErrorTimeoutResource == res)) {
        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    if (__CMSIS_RTOS_QUEUE_GET_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_DATA_NOT_AVAILABLE_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_QueueCb_InsideAmount(
                void*       const   inputQueuePtr,
                uint32_t*   const   amountPtr) {

    tommRoC_mw_template_queue_t* queuePtr;

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    *amountPtr = _inside_amount(queuePtr->osMessageQId);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_QueueCb_FreeAmount(
                void*       const   inputQueuePtr,
                uint32_t*   const   amountPtr) {

    tommRoC_mw_template_queue_t* queuePtr;

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    *amountPtr = _free_amount(queuePtr->osMessageQId);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_QueueCb_Destroy(
                void*       const   inputQueuePtr) {

    tommRoC_mw_template_queue_t* queuePtr;
    osStatus res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osMessageQId, ((tommRoC_mw_template_queue_t*)NULL)->osMessageQId);

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    if (0 != osMessageWaiting(queuePtr->osMessageQId)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    res = osMessageDelete(queuePtr->osMessageQId);

    if (__CMSIS_RTOS_QUEUE_DELETE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
