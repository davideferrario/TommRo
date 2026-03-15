
#if defined (__TOMMROC_MW_USE_QUEUE_NXP_OSA_TEMPLATE__)

/**
 * NOTE:
 *
 * implement using directly FreeRTOS function because NXP implementation
 * is limited (only void* for queue object type).
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_NXP_OSA_QueueCb.h"

#include "rtos/nxpOSA/common/compatibility/tommRoCMwTemplateRTOS_NXP_OSA_Compatibility.h"

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

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_QueueCb_Create(
                void*       const   inputQueuePtr,
        const   uint32_t            msgSizeByte,
        const   uint32_t            queueSizeByte) {

}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_QueueCb_Put(
                void*       const   inputQueuePtr,
        const   void*       const   dataPtr,
        const   uint32_t            waitTimeoutMs) {

}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_QueueCb_Get(
                void*       const   inputQueuePtr,
                void*       const   dataPtr,
        const   uint32_t            waitTimeoutMs) {

}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_QueueCb_InsideAmount(
                void*       const   inputQueuePtr,
                uint32_t*   const   amountPtr) {

}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_QueueCb_FreeAmount(
                void*       const   inputQueuePtr,
                uint32_t*   const   amountPtr) {

}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_QueueCb_Destroy(
                void*       const   inputQueuePtr) {

}

#endif
