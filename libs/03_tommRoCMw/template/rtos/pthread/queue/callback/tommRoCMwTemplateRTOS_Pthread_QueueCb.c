
#if defined (__TOMMROC_MW_USE_QUEUE_PTHREAD_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_Pthread_QueueCb.h"

#include "rtos/queueFIFO/callback/tommRoCMwTemplateRTOSQueueFIFOCb.h"

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

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_QueueCb_Create(
                void*       const   inputQueuePtr,
        const   uint32_t            msgSizeByte,
        const   uint32_t            queueSizeByte) {

    tommRoC_mw_template_queue_t* queuePtr;

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    return tommRoCMwTemplateRTOSQueueFIFOCb_Create(
            &queuePtr->RTOSQueueFIFO,
            msgSizeByte,
            queueSizeByte);
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_QueueCb_Put(
                void*       const   inputQueuePtr,
        const   void*       const   dataPtr,
        const   uint32_t            waitTimeoutMs) {

    tommRoC_mw_template_queue_t* queuePtr;

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    return tommRoCMwTemplateRTOSQueueFIFOCb_Put(
            &queuePtr->RTOSQueueFIFO,
            dataPtr,
            waitTimeoutMs);
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_QueueCb_Get(
                void*       const   inputQueuePtr,
                void*       const   dataPtr,
        const   uint32_t            waitTimeoutMs) {

    tommRoC_mw_template_queue_t* queuePtr;

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    return tommRoCMwTemplateRTOSQueueFIFOCb_Get(
            &queuePtr->RTOSQueueFIFO,
            dataPtr,
            waitTimeoutMs);
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_QueueCb_InsideAmount(
                void*       const   inputQueuePtr,
                uint32_t*   const   amountPtr) {

    tommRoC_mw_template_queue_t* queuePtr;

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    return tommRoCMwTemplateRTOSQueueFIFOCb_InsideAmount(
            &queuePtr->RTOSQueueFIFO,
            amountPtr);
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_QueueCb_FreeAmount(
                void*       const   inputQueuePtr,
                uint32_t*   const   amountPtr) {

    tommRoC_mw_template_queue_t* queuePtr;

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    return tommRoCMwTemplateRTOSQueueFIFOCb_FreeAmount(
            &queuePtr->RTOSQueueFIFO,
            amountPtr);
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_QueueCb_Destroy(
                void*       const   inputQueuePtr) {

    tommRoC_mw_template_queue_t* queuePtr;

    queuePtr = (tommRoC_mw_template_queue_t*) inputQueuePtr;

    return tommRoCMwTemplateRTOSQueueFIFOCb_Destroy(
            &queuePtr->RTOSQueueFIFO);
}

#endif
