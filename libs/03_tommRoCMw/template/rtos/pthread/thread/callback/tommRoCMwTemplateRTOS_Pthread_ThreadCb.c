
#if defined (__TOMMROC_MW_USE_THREAD_PTHREAD_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_Pthread_ThreadCb.h"

#include "TOMMROC.h"

#include "TOMMROCMwTemplate.h"

#include <pthread.h>
#include <sched.h>

#include <stdbool.h>
#include <stdlib.h>

#if !defined (_GNU_SOURCE)
#error "_GNU_SOURCE is needed"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __PTHREAD_THREAD_SUCCESS_RESULT__               (0)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    tommRoC_mw_thread_main_funct_t  mainThread;
    void*                           mainThreadArgPtr;

} __start_routine_arg__;

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
static int _convert_priority(const tommRoC_mw_thread_priority_enum_t priority) {

    static bool firstExecute = true;
    static int minPriorityForPolicy = 0;
    static int maxPriorityForPolicy = 0;

    pthread_attr_t thAttr;
    int policy = 0;

    int weightMin;

    if (firstExecute) {

        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_attr_init(&thAttr), __PTHREAD_THREAD_SUCCESS_RESULT__);
        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_attr_getschedpolicy(&thAttr, &policy), __PTHREAD_THREAD_SUCCESS_RESULT__);

        minPriorityForPolicy = sched_get_priority_min(policy);
        maxPriorityForPolicy = sched_get_priority_max(policy);

        firstExecute = false;
    }

    switch (priority) {

    case TOMMRO_C_MW_THREAD_PRIORITY_IDLE:
        weightMin = 100;
        break;

    case TOMMRO_C_MW_THREAD_PRIORITY_LOW:
        weightMin = 83;
        break;

    case TOMMRO_C_MW_THREAD_PRIORITY_BELOW_NORMAL:
        weightMin = 67;
        break;

    case TOMMRO_C_MW_THREAD_PRIORITY_NORMAL:
        weightMin = 50;
        break;

    case TOMMRO_C_MW_THREAD_PRIORITY_ABOVE_NORMAL:
        weightMin = 33;
        break;

    case TOMMRO_C_MW_THREAD_PRIORITY_HIGH:
        weightMin = 17;
        break;

    case TOMMRO_C_MW_THREAD_PRIORITY_REALTIME:
        weightMin = 0;
        break;

    case TOMMRO_C_MW_THREAD_PRIORITY_DEFAULT:
        weightMin = 50;
        break;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);

        weightMin = 50;
        break;

    }

    return (int) ((((uint32_t) weightMin * (uint32_t) minPriorityForPolicy) + (((uint32_t) 100 - (uint32_t) weightMin) * (uint32_t) maxPriorityForPolicy)) / (uint32_t) 100);
}

static void* _start_routine(void* arg) {

    __start_routine_arg__* startRoutineArgPtr = (__start_routine_arg__*) arg;

    /**
     * NOTE:
     * from documentation: https://man7.org/linux/man-pages/man3/pthread_cancel.3.html
     *
     * A thread's cancelability state can be enabled (the default for new threads) or disabled.
     * If a thread has disabled cancellation, then a cancellation request remains queued until the thread enables cancellation.
     * If a thread has enabled cancellation, then its cancelability type determines when cancellation occurs.
     */
    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL), __PTHREAD_THREAD_SUCCESS_RESULT__);

    /**
     * NOTE:
     * from documentation: https://man7.org/linux/man-pages/man3/pthread_cancel.3.html
     *
     * A thread's cancellation type may be either asynchronous or deferred (the default for new threads).
     * Asynchronous cancelability means that the thread can be canceled at any time (usually immediately, but the system does not guarantee this).
     * Deferred cancelability means that cancellation will be delayed until the thread next calls a function that is a cancellation point.
     * A list of functions that are or may be cancellation points is provided in https://man7.org/linux/man-pages/man7/pthreads.7.html
     */
    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL), __PTHREAD_THREAD_SUCCESS_RESULT__);

    startRoutineArgPtr->mainThread(startRoutineArgPtr->mainThreadArgPtr);

    if (NULL != startRoutineArgPtr) {
        free(startRoutineArgPtr);
    }

    return NULL;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_ThreadCb_Create(
        const   tommRoC_mw_thread_main_funct_t          mainThread,
                void*                           const   mainThreadArgPtr,
        const   char*                           const   threadNameStrPtr,
        const   tommRoC_mw_thread_config_t*     const   configPtr,
                void*                           const   inputThreadPtr) {

    pthread_attr_t* threadAttrPtr = NULL;
    pthread_attr_t threadAttr;
    struct sched_param schedParam;
    tommRoC_mw_template_thread_t* threadPtr;
    __start_routine_arg__* startRoutineArgPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(pthread_t, ((tommRoC_mw_template_thread_t*)NULL)->pThread);

    threadPtr = (tommRoC_mw_template_thread_t*) inputThreadPtr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(threadPtr, 0x00, sizeof(tommRoC_mw_template_thread_t)));

    threadPtr->handleArgPtr = NULL;

    if (TOMMRO_C_MW_THREAD_PRIORITY_DEFAULT != configPtr->priority) {

        if (__PTHREAD_THREAD_SUCCESS_RESULT__ != pthread_attr_init(&threadAttr)) {
            return TOMMRO_C_MW_LOW_LEVEL_ERR;
        }
        if (__PTHREAD_THREAD_SUCCESS_RESULT__ != pthread_attr_getschedparam(&threadAttr, &schedParam)) {
            return TOMMRO_C_MW_LOW_LEVEL_ERR;
        }

        schedParam.sched_priority = _convert_priority(configPtr->priority);
        if (__PTHREAD_THREAD_SUCCESS_RESULT__ != pthread_attr_setschedparam(&threadAttr, &schedParam)) {
            return TOMMRO_C_MW_LOW_LEVEL_ERR;
        }

        threadAttrPtr = &threadAttr;
    }

    startRoutineArgPtr = malloc(sizeof(__start_routine_arg__));

    TOMMROC_ASSERT_NOT_NULL(startRoutineArgPtr);

    if (NULL == startRoutineArgPtr) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    startRoutineArgPtr->mainThread          = mainThread;
    startRoutineArgPtr->mainThreadArgPtr    = mainThreadArgPtr;

    if (__PTHREAD_THREAD_SUCCESS_RESULT__ != pthread_create(&threadPtr->pThread, threadAttrPtr, _start_routine, (void*) startRoutineArgPtr)) {
        free(startRoutineArgPtr);
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    threadPtr->handleArgPtr = (void*) startRoutineArgPtr;

    if (NULL != threadNameStrPtr) {
        if (__PTHREAD_THREAD_SUCCESS_RESULT__ != pthread_setname_np(threadPtr->pThread, threadNameStrPtr)) {
            return TOMMRO_C_MW_LOW_LEVEL_ERR;
        }    
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_ThreadCb_GetID(
                void*   const   inputThreadIDPtr) {

    tommRoC_mw_template_thread_id_t* threadIDPtr;
    pthread_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(pthread_t, tommRoC_mw_template_thread_id_t);

    threadIDPtr = (tommRoC_mw_template_thread_id_t*) inputThreadIDPtr;

    res = pthread_self();

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopySafe(threadIDPtr, sizeof(tommRoC_mw_template_thread_id_t), &res, sizeof(pthread_t), sizeof(res)));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_ThreadCb_Destroy(
                void*   const   inputThreadPtr) {

    tommRoC_mw_template_thread_t* threadPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(pthread_t, ((tommRoC_mw_template_thread_t*)NULL)->pThread);

    threadPtr = (tommRoC_mw_template_thread_t*) inputThreadPtr;

    if (__PTHREAD_THREAD_SUCCESS_RESULT__ != pthread_cancel(threadPtr->pThread)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    if (NULL != threadPtr->handleArgPtr) {
        free(threadPtr->handleArgPtr);
    }

    threadPtr->handleArgPtr = NULL;

    if (__PTHREAD_THREAD_SUCCESS_RESULT__ != pthread_join(threadPtr->pThread, NULL)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_ThreadCb_Exit(void) {

    pthread_exit(NULL);

    // NOTE: it will never get here because pthread_exit is no-return function.
    TOMMROC_ASSERT_TRUE(false);
    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_ThreadCb_Join(
        const   void*   const   inputThreadPtr) {

    tommRoC_mw_template_thread_t* threadPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(pthread_t, ((tommRoC_mw_template_thread_t*)NULL)->pThread);

    threadPtr = (tommRoC_mw_template_thread_t*) inputThreadPtr;

    if (__PTHREAD_THREAD_SUCCESS_RESULT__ != pthread_join(threadPtr->pThread, NULL)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    if (NULL != threadPtr->handleArgPtr) {
        free(threadPtr->handleArgPtr);
    }

    threadPtr->handleArgPtr = NULL;

    return TOMMRO_C_MW_ERR_SUCCESS;
}

void tommRoCMwTemplateRTOS_Pthread_ThreadCb_Yield(void) {

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL), __PTHREAD_THREAD_SUCCESS_RESULT__);
    pthread_testcancel();
    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL), __PTHREAD_THREAD_SUCCESS_RESULT__);

    sched_yield();

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL), __PTHREAD_THREAD_SUCCESS_RESULT__);
    pthread_testcancel();
    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL), __PTHREAD_THREAD_SUCCESS_RESULT__);
}

#endif
