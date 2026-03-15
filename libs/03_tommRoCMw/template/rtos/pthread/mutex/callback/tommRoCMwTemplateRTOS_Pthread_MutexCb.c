
#if defined (__TOMMROC_MW_USE_MUTEX_PTHREAD_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_Pthread_MutexCb.h"

#include "TOMMROC.h"

#include "TOMMROCMwTemplate.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __PTHREAD_MUTEX_SUCCESS_RESULT__                (0)

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

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_MutexCb_Create(
                void*       const   inputMutexPtr) {

    tommRoC_mw_template_mutex_t* mutexPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(pthread_mutex_t, ((tommRoC_mw_template_mutex_t*)NULL)->pThreadMutex);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    if (__PTHREAD_MUTEX_SUCCESS_RESULT__ != pthread_mutex_init(&mutexPtr->pThreadMutex, NULL)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_MutexCb_CreateRecursive(
                void*       const   inputMutexPtr) {

    tommRoC_mw_template_mutex_t* mutexPtr;

    pthread_mutexattr_t mutexattr;

    TOMMROC_CTA_SIZE_OF_EQUALS(pthread_mutex_t, ((tommRoC_mw_template_mutex_t*)NULL)->pThreadMutex);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    if (0 != pthread_mutexattr_init(&mutexattr)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    if (0 != pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    if (__PTHREAD_MUTEX_SUCCESS_RESULT__ != pthread_mutex_init(&mutexPtr->pThreadMutex, &mutexattr)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_MutexCb_Lock(
                void*       const   inputMutexPtr,
        const   uint32_t            waitTimeoutMs) {

    tommRoC_timer_t waitTimer;
    tommRoC_mw_template_mutex_t* mutexPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(pthread_mutex_t, ((tommRoC_mw_template_mutex_t*)NULL)->pThreadMutex);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    if (LOCK_MUTEX_NO_WAIT_TIMEOUT == waitTimeoutMs) {

        if (__PTHREAD_MUTEX_SUCCESS_RESULT__ == pthread_mutex_trylock(&mutexPtr->pThreadMutex)) {
            return TOMMRO_C_MW_ERR_SUCCESS;
        }

        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    if (LOCK_MUTEX_INFINITE_TIMEOUT == waitTimeoutMs) {

        if (__PTHREAD_MUTEX_SUCCESS_RESULT__ != pthread_mutex_lock(&mutexPtr->pThreadMutex)) {
            return TOMMRO_C_MW_LOW_LEVEL_ERR;
        }

        return TOMMRO_C_MW_ERR_SUCCESS;
    }

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCTimerStart(&waitTimer, waitTimeoutMs),
            TOMMRO_C_MW_ENVIRONMENT_NOT_INIT_ERR);

    do {

        if (__PTHREAD_MUTEX_SUCCESS_RESULT__ == pthread_mutex_trylock(&mutexPtr->pThreadMutex)) {
            return TOMMRO_C_MW_ERR_SUCCESS;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(0));

    } while (TOMMRO_C_TIMER_NOT_EXPIRED_ERR == tommRoCTimerIsExpired(&waitTimer));

    return TOMMRO_C_MW_TIMEOUT_ERR;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_MutexCb_UnLock(
                void*       const   inputMutexPtr) {

    tommRoC_mw_template_mutex_t* mutexPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(pthread_mutex_t, ((tommRoC_mw_template_mutex_t*)NULL)->pThreadMutex);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    if (__PTHREAD_MUTEX_SUCCESS_RESULT__ != pthread_mutex_unlock(&mutexPtr->pThreadMutex)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_MutexCb_Destroy(
                void*       const   inputMutexPtr) {

    tommRoC_mw_template_mutex_t* mutexPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(pthread_mutex_t, ((tommRoC_mw_template_mutex_t*)NULL)->pThreadMutex);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    if (__PTHREAD_MUTEX_SUCCESS_RESULT__ != pthread_mutex_destroy(&mutexPtr->pThreadMutex)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
