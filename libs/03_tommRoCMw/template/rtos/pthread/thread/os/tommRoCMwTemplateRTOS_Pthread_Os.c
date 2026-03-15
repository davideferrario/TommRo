
#if defined (__TOMMROC_MW_USE_THREAD_PTHREAD_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_Pthread_Os.h"

#include "TOMMROC.h"

#include <pthread.h>
#include <sched.h>
#include <time.h>

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

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _nano_sleep(const struct timespec* const tsPtr) {

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL), __PTHREAD_THREAD_SUCCESS_RESULT__);
    pthread_testcancel();
    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL), __PTHREAD_THREAD_SUCCESS_RESULT__);

    if (0 != nanosleep(tsPtr, NULL)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL), __PTHREAD_THREAD_SUCCESS_RESULT__);
    pthread_testcancel();
    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL), __PTHREAD_THREAD_SUCCESS_RESULT__);

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _delay_msec(const uint32_t msec) {

    struct timespec ts;

    /**
     * NOTE:
     * as described in "tommRoCOsDelayMsec" function interface, in case of multitasking environment, if delay param is zero, a task yield must be performed.
     */
    if (0 == msec) {
        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL), __PTHREAD_THREAD_SUCCESS_RESULT__);
        pthread_testcancel();
        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL), __PTHREAD_THREAD_SUCCESS_RESULT__);

        sched_yield();

        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL), __PTHREAD_THREAD_SUCCESS_RESULT__);
        pthread_testcancel();
        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL), __PTHREAD_THREAD_SUCCESS_RESULT__);

        return TOMMRO_C_ERR_SUCCESS;
    }

    ts.tv_sec   = msec / 1000;
    ts.tv_nsec  = (msec % 1000) * 1000000;

    return _nano_sleep(&ts);
}

static tommRoC_err_enum_t _delay_usec(const uint32_t usec) {

    struct timespec ts;

    ts.tv_sec   = usec / 1000000;
    ts.tv_nsec  = (usec % 1000000) * 1000;

    return _nano_sleep(&ts);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_OsStart(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsInitDelayMsec(_delay_msec),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsInitDelayUsec(_delay_usec),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Pthread_OsStop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsCloseEnv(TOMMRO_C_OS_DELAY_USEC_FUNCT),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsCloseEnv(TOMMRO_C_OS_DELAY_MSEC_FUNCT),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
