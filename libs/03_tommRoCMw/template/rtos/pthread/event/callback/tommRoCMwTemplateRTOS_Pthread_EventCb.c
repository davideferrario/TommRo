
#if defined (__TOMMROC_MW_USE_EVENT_PTHREAD_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_Pthread_EventCb.h"

#include "TOMMROC.h"

#include "TOMMROCMwTemplate.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __PTHREAD_MUTEX_SUCCESS_RESULT__                (0)
#define __PTHREAD_EVENT_SUCCESS_RESULT__                (0)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static pthread_mutex_t _needed_mutex = PTHREAD_MUTEX_INITIALIZER;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static uint64_t _get_timeout(const uint32_t waitTimeoutMs) {

    if (WAIT_EVENT_NO_WAIT_TIMEOUT == waitTimeoutMs) {
        return UINT64_MIN;
    }

    if (WAIT_EVENT_INFINITE_TIMEOUT == waitTimeoutMs) {
        return UINT64_MAX;
    }

    return (uint64_t) waitTimeoutMs;
}

static tommRoC_mw_err_enum_t _timeout_msec_To_timespec(const uint32_t waitTimeoutMs, struct timespec* const timespecPtr) {

    uint64_t timeoutMsec;

    time_t timeoutSec;
    time_t timeoutNSec;

    // Note that timedwait requires CLOCK_REALTIME, not CLOCK_MONOTONIC
    if (0 != clock_gettime(CLOCK_REALTIME, timespecPtr)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    if (WAIT_EVENT_NO_WAIT_TIMEOUT == waitTimeoutMs) {
        return TOMMRO_C_MW_ERR_SUCCESS;
    }

    timeoutMsec = _get_timeout(waitTimeoutMs);

    // Calculate new timespec values based on timeout
    timeoutSec  = (time_t) (timeoutMsec / (uint64_t) 1000);
    timeoutNSec = (time_t) ((timeoutMsec % (uint64_t) 1000) * (uint64_t) 1000000);
    timespecPtr->tv_sec     += timeoutSec;
    timespecPtr->tv_nsec    += timeoutNSec;
    if (timespecPtr->tv_nsec > 1000000000) {
        timespecPtr->tv_sec   += 1;
        timespecPtr->tv_nsec  -= 1000000000;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_EventCb_Init(void) {

    if (__PTHREAD_MUTEX_SUCCESS_RESULT__ != pthread_mutex_init(&_needed_mutex, NULL)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_EventCb_Close(void) {

    if (__PTHREAD_MUTEX_SUCCESS_RESULT__ != pthread_mutex_destroy(&_needed_mutex)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_EventCb_Create(
                void*       const   inputEventPtr) {

    tommRoC_mw_template_event_t* eventPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(pthread_cond_t, ((tommRoC_mw_template_event_t*)NULL)->pThreadCond);

    eventPtr = (tommRoC_mw_template_event_t*) inputEventPtr;

    if (__PTHREAD_EVENT_SUCCESS_RESULT__ != pthread_cond_init(&eventPtr->pThreadCond, NULL)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_EventCb_Signal(
                void*       const   inputEventPtr) {

    tommRoC_mw_template_event_t* eventPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(pthread_cond_t, ((tommRoC_mw_template_event_t*)NULL)->pThreadCond);

    eventPtr = (tommRoC_mw_template_event_t*) inputEventPtr;

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_mutex_lock(&_needed_mutex), __PTHREAD_MUTEX_SUCCESS_RESULT__);

    if (__PTHREAD_EVENT_SUCCESS_RESULT__ != pthread_cond_broadcast(&eventPtr->pThreadCond)) {
        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_mutex_unlock(&_needed_mutex), __PTHREAD_MUTEX_SUCCESS_RESULT__);
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_mutex_unlock(&_needed_mutex), __PTHREAD_MUTEX_SUCCESS_RESULT__);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_EventCb_Wait(
                void*       const   inputEventPtr,
        const   uint32_t            waitTimeoutMs) {

    tommRoC_mw_template_event_t* eventPtr;

    struct timespec timespec;

    TOMMROC_CTA_SIZE_OF_EQUALS(pthread_cond_t, ((tommRoC_mw_template_event_t*)NULL)->pThreadCond);

    eventPtr = (tommRoC_mw_template_event_t*) inputEventPtr;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_timeout_msec_To_timespec(waitTimeoutMs, &timespec));

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_mutex_lock(&_needed_mutex), __PTHREAD_MUTEX_SUCCESS_RESULT__);

    if (__PTHREAD_EVENT_SUCCESS_RESULT__ != pthread_cond_timedwait(&eventPtr->pThreadCond, &_needed_mutex, &timespec)) {
        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_mutex_unlock(&_needed_mutex), __PTHREAD_MUTEX_SUCCESS_RESULT__);
        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_mutex_unlock(&_needed_mutex), __PTHREAD_MUTEX_SUCCESS_RESULT__);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_EventCb_Clear(
                void*       const   inputEventsPtr,
        const   uint8_t             inputEventsAmount) {

    tommRoC_mw_template_event_t* eventPtr;

    struct timespec timespec;

    uint8_t idx;

    TOMMROC_CTA_SIZE_OF_EQUALS(pthread_cond_t, ((tommRoC_mw_template_event_t*)NULL)->pThreadCond);

    for (eventPtr = (tommRoC_mw_template_event_t*) inputEventsPtr, idx = 0; idx < inputEventsAmount; ++eventPtr, ++idx) {

        TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_timeout_msec_To_timespec(WAIT_EVENT_NO_WAIT_TIMEOUT, &timespec));

        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_mutex_lock(&_needed_mutex), __PTHREAD_MUTEX_SUCCESS_RESULT__);
        pthread_cond_timedwait(&eventPtr->pThreadCond, &_needed_mutex, &timespec);
        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_mutex_unlock(&_needed_mutex), __PTHREAD_MUTEX_SUCCESS_RESULT__);
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_EventCb_Destroy(
                void*       const   inputEventPtr) {

    tommRoC_mw_template_event_t* eventPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(pthread_cond_t, ((tommRoC_mw_template_event_t*)NULL)->pThreadCond);

    eventPtr = (tommRoC_mw_template_event_t*) inputEventPtr;

    if (__PTHREAD_EVENT_SUCCESS_RESULT__ != pthread_cond_destroy(&eventPtr->pThreadCond)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
