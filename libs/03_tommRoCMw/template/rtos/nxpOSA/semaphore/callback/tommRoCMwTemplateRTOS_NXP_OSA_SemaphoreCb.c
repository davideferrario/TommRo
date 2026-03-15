
#if defined (__TOMMROC_MW_USE_SEMAPHORE_NXP_OSA_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_NXP_OSA_SemaphoreCb.h"

#include "rtos/nxpOSA/common/compatibility/tommRoCMwTemplateRTOS_NXP_OSA_Compatibility.h"

#include "TOMMROC.h"

#include "TOMMROCMwTemplate.h"

#include <stdbool.h>

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
static uint32_t _get_timeout(const uint32_t waitTimeoutMs) {

    if (WAIT_SEMAPHORE_NO_WAIT_TIMEOUT == waitTimeoutMs) {
        return 0;
    }

    if (WAIT_SEMAPHORE_INFINITE_TIMEOUT == waitTimeoutMs) {
        return osaWaitForever_c;
    }

    return waitTimeoutMs;
}

static bool _in_handler_mode(void) {
    bool isFromISR;
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsIsFromISR(&isFromISR));
    return isFromISR;
}

static osaStatus_t _OSA_SemaphoreWait_FromISR(osaSemaphoreId_t semId) {

    BaseType_t taskWoken = pdFALSE;

    if (pdFALSE == xSemaphoreTakeFromISR(semId, &taskWoken)) {
        return osaStatus_Timeout;
    }

    portEND_SWITCHING_ISR(taskWoken);

    return osaStatus_Success;
}

static osaStatus_t _OSA_SemaphorePost_FromISR(osaSemaphoreId_t semId) {

    BaseType_t taskWoken = pdFALSE;

    if (pdFALSE == xSemaphoreGiveFromISR(semId, &taskWoken)) {
        return osaStatus_Error;
    }

    portEND_SWITCHING_ISR(taskWoken);

    return osaStatus_Success;
}

static osaStatus_t _OSA_SemaphoreWait(osaSemaphoreId_t semId, uint32_t millisec) {

    if (!_in_handler_mode()) {
        return OSA_SemaphoreWait(semId, millisec);
    }

    return _OSA_SemaphoreWait_FromISR(semId);
}

static osaStatus_t _OSA_SemaphorePost(osaSemaphoreId_t semId) {

    if (!_in_handler_mode()) {
        return OSA_SemaphorePost(semId);
    }

    return _OSA_SemaphorePost_FromISR(semId);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_SemaphoreCb_Create(
                void*       const   inputSemaphorePtr,
        const   uint32_t            availableRes) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(osaSemaphoreId_t, ((tommRoC_mw_template_semaphore_t*)NULL)->osaSemaphoreId);

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    semaphorePtr->osaSemaphoreId = OSA_SemaphoreCreate(availableRes);

    if (__NXP_OSA_SEMAPHORE_CREATE_ON_ERROR_RESULT__ == semaphorePtr->osaSemaphoreId) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_SemaphoreCb_Wait(
                void*       const   inputSemaphorePtr,
        const   uint32_t            waitTimeoutMs) {

    uint32_t millisec;
    tommRoC_mw_template_semaphore_t* semaphorePtr;
    osaStatus_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osaSemaphoreId_t, ((tommRoC_mw_template_semaphore_t*)NULL)->osaSemaphoreId);

    TOMMROC_CTA_SIZE_OF_EQUALS(osaWaitForever_c, millisec);

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    millisec = _get_timeout(waitTimeoutMs);

    res = _OSA_SemaphoreWait(semaphorePtr->osaSemaphoreId, millisec);

    if (osaStatus_Timeout == res) {
        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    if (__NXP_OSA_SEMAPHORE_WAIT_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_SemaphoreCb_Release(
                void*       const   inputSemaphorePtr) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;
    osaStatus_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osaSemaphoreId_t, ((tommRoC_mw_template_semaphore_t*)NULL)->osaSemaphoreId);

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    res = _OSA_SemaphorePost(semaphorePtr->osaSemaphoreId);

    if (__NXP_OSA_SEMAPHORE_POST_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_SemaphoreCb_Destroy(
                void*       const   inputSemaphorePtr) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;
    osaStatus_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osaSemaphoreId_t, ((tommRoC_mw_template_semaphore_t*)NULL)->osaSemaphoreId);

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    res = OSA_SemaphoreDestroy(semaphorePtr->osaSemaphoreId);

    if (__NXP_OSA_SEMAPHORE_DESTROY_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
