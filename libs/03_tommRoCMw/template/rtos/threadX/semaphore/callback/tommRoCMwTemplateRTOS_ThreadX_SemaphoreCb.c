
#if defined (__TOMMROC_MW_USE_SEMAPHORE_THREADX_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_ThreadX_SemaphoreCb.h"

#include "rtos/threadX/common/compatibility/tommRoCMwTemplateRTOS_ThreadX_Compatibility.h"

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

    if (WAIT_SEMAPHORE_NO_WAIT_TIMEOUT == waitTimeoutMs) {
        return TX_NO_WAIT;
    }

    if (WAIT_SEMAPHORE_INFINITE_TIMEOUT == waitTimeoutMs) {
        return TX_WAIT_FOREVER;
    }

    return TOMMROC_MW_TEMPLATE_RTOS_THREADX_COMMON_COMPATIBILITY_MS_TO_TICKS(waitTimeoutMs);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_SemaphoreCb_Create(
                void*       const   inputSemaphorePtr,
        const   uint32_t            availableRes) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;
    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_SEMAPHORE, ((tommRoC_mw_template_semaphore_t*)NULL)->threadXSemaphore);

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    res = tx_semaphore_create(&semaphorePtr->threadXSemaphore, TX_NULL, availableRes);

    if (__THREADX_SEMAPHORE_CREATE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_SemaphoreCb_Wait(
                void*       const   inputSemaphorePtr,
        const   uint32_t            waitTimeoutMs) {

    ULONG wait_option;
    tommRoC_mw_template_semaphore_t* semaphorePtr;
    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_SEMAPHORE, ((tommRoC_mw_template_semaphore_t*)NULL)->threadXSemaphore);

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_WAIT_FOREVER, wait_option);

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    wait_option = _get_timeout(waitTimeoutMs);

    res = tx_semaphore_get(&semaphorePtr->threadXSemaphore, wait_option);

    if (__THREADX_SEMAPHORE_GET_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_SemaphoreCb_Release(
                void*       const   inputSemaphorePtr) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;
    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_SEMAPHORE, ((tommRoC_mw_template_semaphore_t*)NULL)->threadXSemaphore);

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    res = tx_semaphore_put(&semaphorePtr->threadXSemaphore);

    if (__THREADX_SEMAPHORE_PUT_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_SemaphoreCb_Destroy(
                void*       const   inputSemaphorePtr) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;
    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_SEMAPHORE, ((tommRoC_mw_template_semaphore_t*)NULL)->threadXSemaphore);

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    res = tx_semaphore_delete(&semaphorePtr->threadXSemaphore);

    if (__THREADX_SEMAPHORE_DELETE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
