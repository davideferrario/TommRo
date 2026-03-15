
#if defined (__TOMMROC_MW_USE_MUTEX_NXP_OSA_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_NXP_OSA_MutexCb.h"

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

    if (LOCK_MUTEX_NO_WAIT_TIMEOUT == waitTimeoutMs) {
        return 0;
    }

    if (LOCK_MUTEX_INFINITE_TIMEOUT == waitTimeoutMs) {
        return osaWaitForever_c;
    }

    return waitTimeoutMs;
}

static bool _in_handler_mode(void) {
    bool isFromISR;
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsIsFromISR(&isFromISR));
    return isFromISR;
}

static osaStatus_t _OSA_MutexLock_FromISR(osaMutexId_t mutexId) {

    BaseType_t taskWoken = pdFALSE;

    if (pdFALSE == xSemaphoreTakeFromISR(mutexId, &taskWoken)) {
        return osaStatus_Timeout;
    }

    portEND_SWITCHING_ISR(taskWoken);

    return osaStatus_Success;
}

static osaStatus_t _OSA_MutexUnlock_FromISR(osaMutexId_t mutexId) {

    BaseType_t taskWoken = pdFALSE;

    if (pdFALSE == xSemaphoreGiveFromISR((mutex_t) mutexId, &taskWoken)) {
        return osaStatus_Error;
    }

    portEND_SWITCHING_ISR(taskWoken);

    return osaStatus_Success;
}

static osaStatus_t _OSA_MutexLock(osaMutexId_t mutexId, uint32_t millisec) {

    if (!_in_handler_mode()) {
        return OSA_MutexLock(mutexId, millisec);
    }

    return _OSA_MutexLock_FromISR(mutexId);
}

static osaStatus_t _OSA_MutexUnlock(osaMutexId_t mutexId) {

    if (!_in_handler_mode()) {
        return OSA_MutexUnlock(mutexId);
    }

    return _OSA_MutexUnlock_FromISR(mutexId);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_MutexCb_Create(
                void*       const   inputMutexPtr) {

    tommRoC_mw_template_mutex_t* mutexPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(osaMutexId_t, ((tommRoC_mw_template_mutex_t*)NULL)->osaMutexId);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    mutexPtr->osaMutexId = OSA_MutexCreate();

    if (__NXP_OSA_MUTEX_CREATE_ON_ERROR_RESULT__ == mutexPtr->osaMutexId) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_MutexCb_CreateRecursive(
                void*       const   inputMutexPtr) {

    tommRoC_mw_template_mutex_t* mutexPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(osaMutexId_t, ((tommRoC_mw_template_mutex_t*)NULL)->osaMutexId);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    mutexPtr->osaMutexId = (osaMutexId_t) xSemaphoreCreateRecursiveMutex();

    if (__NXP_OSA_MUTEX_CREATE_ON_ERROR_RESULT__ == mutexPtr->osaMutexId) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_MutexCb_Lock(
                void*       const   inputMutexPtr,
        const   uint32_t            waitTimeoutMs) {

    uint32_t millisec;
    tommRoC_mw_template_mutex_t* mutexPtr;
    osaStatus_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osaMutexId_t, ((tommRoC_mw_template_mutex_t*)NULL)->osaMutexId);

    TOMMROC_CTA_SIZE_OF_EQUALS(osaWaitForever_c, millisec);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    millisec = _get_timeout(waitTimeoutMs);

    res = _OSA_MutexLock(mutexPtr->osaMutexId, millisec);

    if (osaStatus_Timeout == res) {
        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    if (__NXP_OSA_MUTEX_LOCK_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_MutexCb_UnLock(
                void*       const   inputMutexPtr) {

    tommRoC_mw_template_mutex_t* mutexPtr;
    osaStatus_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osaMutexId_t, ((tommRoC_mw_template_mutex_t*)NULL)->osaMutexId);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    res = _OSA_MutexUnlock(mutexPtr->osaMutexId);

    if (__NXP_OSA_MUTEX_UNLOCK_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_MutexCb_Destroy(
                void*       const   inputMutexPtr) {

    tommRoC_mw_template_mutex_t* mutexPtr;
    osaStatus_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osaMutexId_t, ((tommRoC_mw_template_mutex_t*)NULL)->osaMutexId);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    res = OSA_MutexDestroy(mutexPtr->osaMutexId);

    if (__NXP_OSA_MUTEX_DESTROY_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
