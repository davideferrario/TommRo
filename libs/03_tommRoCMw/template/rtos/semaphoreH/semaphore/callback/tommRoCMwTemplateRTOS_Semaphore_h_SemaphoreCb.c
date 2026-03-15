
#if defined (__TOMMROC_MW_USE_SEMAPHORE_SEMAPHORE_H_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_Semaphore_h_SemaphoreCb.h"

#include "TOMMROC.h"

#include "TOMMROCMwTemplate.h"

#include <time.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __PTHREAD_SEMAPHORE_SUCCESS_RESULT__            (0)

#define __SEM_PROCESS_PRIVATE__                         (0)
#define __SEM_PROCESS_SHARED__                          (1)

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

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Semaphore_h_SemaphoreCb_Create(
                void*       const   inputSemaphorePtr,
        const   uint32_t            availableRes) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    if (__PTHREAD_SEMAPHORE_SUCCESS_RESULT__ != sem_init(&semaphorePtr->sem, __SEM_PROCESS_PRIVATE__, availableRes)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Semaphore_h_SemaphoreCb_Wait(
                void*       const   inputSemaphorePtr,
        const   uint32_t            waitTimeoutMs) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;
    struct timespec ts;
    uint32_t timeout;
    time_t timeoutSec;
    time_t timeoutNSec;

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    if (WAIT_SEMAPHORE_INFINITE_TIMEOUT == waitTimeoutMs) {

        if (__PTHREAD_SEMAPHORE_SUCCESS_RESULT__ != sem_wait(&semaphorePtr->sem)) {
            return TOMMRO_C_MW_TIMEOUT_ERR;
        }

        return TOMMRO_C_MW_ERR_SUCCESS;
    }

    if (WAIT_SEMAPHORE_NO_WAIT_TIMEOUT == waitTimeoutMs) {
        timeout = 0;
    }
    else {
        timeout = waitTimeoutMs;
    }

    // Note that timedwait requires CLOCK_REALTIME, not CLOCK_MONOTONIC
    if (0 != clock_gettime(CLOCK_REALTIME, &ts)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    // Calculate new timespec values based on timeout
    timeoutSec  = timeout / 1000;
    timeoutNSec = (timeout % 1000) * 1000000;
    ts.tv_sec   += timeoutSec;
    ts.tv_nsec  += timeoutNSec;
    if (ts.tv_nsec > 1000000000) {
        ts.tv_sec   += 1;
        ts.tv_nsec  -= 1000000000;
    }
    if (__PTHREAD_SEMAPHORE_SUCCESS_RESULT__ != sem_timedwait(&semaphorePtr->sem, &ts)) {
        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Semaphore_h_SemaphoreCb_Release(
                void*       const   inputSemaphorePtr) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    if (__PTHREAD_SEMAPHORE_SUCCESS_RESULT__ != sem_post(&semaphorePtr->sem)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Semaphore_h_SemaphoreCb_TryWait(
                void*       const   inputSemaphorePtr) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    if (__PTHREAD_SEMAPHORE_SUCCESS_RESULT__ != sem_trywait(&semaphorePtr->sem)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Semaphore_h_SemaphoreCb_Destroy(
                void*       const   inputSemaphorePtr) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    if (__PTHREAD_SEMAPHORE_SUCCESS_RESULT__ != sem_destroy(&semaphorePtr->sem)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
