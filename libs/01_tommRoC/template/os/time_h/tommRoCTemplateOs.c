
#if defined (__TOMMROC_USE_TIME_TIME_H_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs.h"

#include "os/tommRoCTemplateOsCritical.h"
#include "os/tommRoCTemplateOsIsFromISR.h"
#include "os/tommRoCTemplateOsResetCause.h"
#include "os/tommRoCTemplateOsUUID.h"

#include "TOMMROC.h"

#if !defined (_POSIX_C_SOURCE)
#error "You have to set -D_POSIX_C_SOURCE=199309L"
#endif

#if (_POSIX_C_SOURCE < 199309L)
#error "You have to set -D_POSIX_C_SOURCE>=199309L"
#endif

#include <time.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __RTC_CALENDAR_MIN_VALID_YEAR__             ((uint16_t) 1970)
#define __RTC_CALENDAR_MAX_VALID_YEAR__             ((uint16_t) 2199)

#define __TIME_H_CLOCK_GETTIME_RESULT_SUCCESS__     (0)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static uint32_t _gettime_to_u32_uptime_msec_on_start;
static uint32_t _gettime_to_u32_uptime_usec_on_start;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static uint32_t _timespec_to_u32_uptime_msec(const struct timespec* const nowPtr) {
    return (uint32_t) ((uint64_t) (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(nowPtr->tv_sec)) + (uint64_t) (TOMMROC_UNIT_MEASURE_TIME_APPROX_nSEC_TO_mSEC(nowPtr->tv_nsec)));
}

static uint32_t _timespec_to_u32_uptime_usec(const struct timespec* const nowPtr) {
    return (uint32_t) ((uint64_t) (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_uSEC(nowPtr->tv_sec)) + (uint64_t) (TOMMROC_UNIT_MEASURE_TIME_APPROX_nSEC_TO_uSEC(nowPtr->tv_nsec)));
}

static tommRoC_err_enum_t _nano_sleep(const struct timespec* const tsPtr) {

    if (0 != nanosleep(tsPtr, NULL)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _delay_msec(const uint32_t msec) {

    struct timespec ts;

    /**
     * NOTE:
     * as described in "tommRoCOsDelayMsec" function interface, in case of NOT multitasking environment, if delay param is zero, function should return SUCCESS result immediately.
     */
    if (0 == msec) {
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

static uint32_t _get_uptime_msec(void) {

    struct timespec getTimeNow;

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(clock_gettime(CLOCK_MONOTONIC, &getTimeNow), __TIME_H_CLOCK_GETTIME_RESULT_SUCCESS__);

    return (tommRoCMathRoundDiffU32(_timespec_to_u32_uptime_msec(&getTimeNow), _gettime_to_u32_uptime_msec_on_start));
}

static uint32_t _get_uptime_usec(void) {

    struct timespec getTimeNow;

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(clock_gettime(CLOCK_MONOTONIC, &getTimeNow), __TIME_H_CLOCK_GETTIME_RESULT_SUCCESS__);

    return (tommRoCMathRoundDiffU32(_timespec_to_u32_uptime_usec(&getTimeNow), _gettime_to_u32_uptime_usec_on_start));
}

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
static tommRoC_err_enum_t _get_date_time(tommRoC_date_time_t* const dateTimePtr) {

    time_t now;
    struct tm* localNowPtr;

    now         = time(NULL);
    localNowPtr = localtime(&now);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(
            tommRoCDateTimeInit(
                    localNowPtr->tm_mday,
                    localNowPtr->tm_mon + 1,
                    localNowPtr->tm_year + 1900,
                    localNowPtr->tm_hour,
                    localNowPtr->tm_min,
                    localNowPtr->tm_sec,
                    dateTimePtr));

    TOMMROC_ASSERT_EQUALS(tommRoCDateTimeGetDOW(dateTimePtr), localNowPtr->tm_wday);

    return TOMMRO_C_ERR_SUCCESS;
}
#endif

static tommRoC_err_enum_t _start_up_get_uptime_msec(void) {

    struct timespec getTimeNow;

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(clock_gettime(CLOCK_MONOTONIC, &getTimeNow), __TIME_H_CLOCK_GETTIME_RESULT_SUCCESS__);

    _gettime_to_u32_uptime_msec_on_start = _timespec_to_u32_uptime_msec(&getTimeNow);
    _gettime_to_u32_uptime_usec_on_start = _timespec_to_u32_uptime_usec(&getTimeNow);

    return TOMMRO_C_ERR_SUCCESS;
}

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
static uint32_t _get_hard_clock(void) {

    unsigned long lo, hi;
    __asm volatile( "rdtsc" : "=a" (lo), "=d" (hi) );
    return (uint32_t) lo;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/
 
tommRoC_err_enum_t tommRoCTemplateOsStart(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayMsecStart());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayUsecStart());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsUptimeMsecStart());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsUptimeUsecStart());
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsHardClockStart());
#endif

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCalendarStart());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCriticalStart());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsIsFromISRStart());

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsSleepForMsecStart());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsGetUUIDStart());

#if defined (__TOMMROC_USE_RESET_CAUSE_OS_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsResetCauseStart());
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsStop(void) {

#if defined (__TOMMROC_USE_RESET_CAUSE_OS_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsResetCauseStop());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsGetUUIDStop());

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsSleepForMsecStop());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCriticalStop());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsIsFromISRStop());

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCalendarStop());
#endif

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsHardClockStop());
#endif
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsUptimeUsecStop());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsUptimeMsecStop());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayUsecStop());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayMsecStop());

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsDelayMsecStart(void) {
    return tommRoCOsInitDelayMsec(_delay_msec);
}

tommRoC_err_enum_t tommRoCTemplateOsDelayUsecStart(void) {
    return tommRoCOsInitDelayUsec(_delay_usec);
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeMsecStart(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_start_up_get_uptime_msec());

    return tommRoCOsInitUptimeMsec(_get_uptime_msec);
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeUsecStart(void) {
    return tommRoCOsInitUptimeUsec(_get_uptime_usec);
}

tommRoC_err_enum_t tommRoCTemplateOsHardClockStart(void) {
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
    return tommRoCOsInitHardClock(_get_hard_clock);
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsCalendarStart(void) {

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)

    tommRoC_os_date_time_funct_init_t dateTimeFunctInit;

    dateTimeFunctInit.setDateTime   = NULL;
    dateTimeFunctInit.getDateTime   = _get_date_time;
    dateTimeFunctInit.minValidYear  = __RTC_CALENDAR_MIN_VALID_YEAR__;
    dateTimeFunctInit.maxValidYear  = __RTC_CALENDAR_MAX_VALID_YEAR__;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsInitDateTime(&dateTimeFunctInit));

    return TOMMRO_C_ERR_SUCCESS;
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalStart(void) {
    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsIsFromISRStart(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsIsFromISRInit());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsInitIsFromISR(tommRoCTemplateOsIsFromISR));
    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsSleepForMsecStart(void) {

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsRebootStart(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsGetUUIDStart(void) {
    return tommRoCOsInitGetUUID(tommRoCTemplateOsUUIDGet);
}

tommRoC_err_enum_t tommRoCTemplateOsResetCauseStart(void) {

#if defined (__TOMMROC_USE_RESET_CAUSE_OS_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsInitResetCause(tommRoCTemplateOsResetCause));
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsInitClearResetCause(tommRoCTemplateOsClearResetCause));
    return TOMMRO_C_ERR_SUCCESS;
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}


tommRoC_err_enum_t tommRoCTemplateOsDelayMsecStop(void) {
    return tommRoCOsCloseEnv(TOMMRO_C_OS_DELAY_MSEC_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsDelayUsecStop(void) {
    return tommRoCOsCloseEnv(TOMMRO_C_OS_DELAY_USEC_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeMsecStop(void) {
    return tommRoCOsCloseEnv(TOMMRO_C_OS_UPTIME_MSEC_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeUsecStop(void) {
    return tommRoCOsCloseEnv(TOMMRO_C_OS_UPTIME_USEC_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsHardClockStop(void) {
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
    return tommRoCOsCloseEnv(TOMMRO_C_OS_HARD_CLOCK_FUNCT);
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsCalendarStop(void) {

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsCloseEnv(TOMMRO_C_OS_DATE_TIME_FUNCT));

    return TOMMRO_C_ERR_SUCCESS;
#else

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalStop(void) {
    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsIsFromISRStop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsCloseEnv(TOMMRO_C_OS_IS_FROM_ISR_FUNCT));
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsIsFromISRClose());
    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsSleepForMsecStop(void) {

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOsRebootStop(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsGetUUIDStop(void) {
    return tommRoCOsCloseEnv(TOMMRO_C_OS_GET_UUID_FUNCT);
}

tommRoC_err_enum_t tommRoCTemplateOsResetCauseStop(void) {
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsCloseEnv(TOMMRO_C_OS_RESET_CAUSE_FUNCT));
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsCloseEnv(TOMMRO_C_OS_CLEAR_RESET_CAUSE_FUNCT));
    return TOMMRO_C_ERR_SUCCESS;
}

#endif
