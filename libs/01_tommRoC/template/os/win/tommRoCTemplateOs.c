
#if defined (__TOMMROC_USE_TIME_WINDOWS_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs.h"

#include "os/tommRoCTemplateOsCritical.h"
#include "os/tommRoCTemplateOsIsFromISR.h"
#include "os/tommRoCTemplateOsResetCause.h"
#include "os/tommRoCTemplateOsUUID.h"

#include "TOMMROC.h"

#include <time.h>
#include <windows.h>
#include <limits.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __RTC_CALENDAR_MIN_VALID_YEAR__             ((uint16_t) 1970)
#define __RTC_CALENDAR_MAX_VALID_YEAR__             ((uint16_t) 2199)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static LONGLONG _freq;
static uint32_t _tick_count_on_start;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _delay_msec(const uint32_t msec) {

    /**
     * NOTE:
     * as described in "tommRoCOsDelayMsec" function interface, in case of NOT multitasking environment, if delay param is zero, function should return SUCCESS result immediately.
     */
    if (0 == msec) {
        return TOMMRO_C_ERR_SUCCESS;
    }

    Sleep(msec);

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _delay_usec(const uint32_t usec) {

    LARGE_INTEGER tcounter;
    LONGLONG onStartTickValue;
    LONGLONG tickValue;
    LONGLONG elapsedUsecs;

    if (0 == QueryPerformanceCounter(&tcounter)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    onStartTickValue = tcounter.QuadPart;

    elapsedUsecs = 0;

    while (elapsedUsecs < usec) {

        if (0 == QueryPerformanceCounter(&tcounter)) {
            return TOMMRO_C_LOW_LEVEL_ERR;
        }

        tickValue = tcounter.QuadPart;

        if (tickValue >= onStartTickValue) {
            elapsedUsecs = tickValue - onStartTickValue;
        }
        else {
            elapsedUsecs = _I64_MAX - onStartTickValue + tickValue + 1;
        }

        elapsedUsecs /= (_freq / 1000000);
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static uint32_t _get_uptime_msec(void) {
    
    return ((uint32_t) GetTickCount() - _tick_count_on_start);
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

static tommRoC_err_enum_t _start_up_delay_usec(void) {

    LARGE_INTEGER tcounter;

    if (0 == QueryPerformanceFrequency(&tcounter)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    _freq = tcounter.QuadPart;

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _start_up_get_uptime_msec(void) {

    _tick_count_on_start = (uint32_t) GetTickCount();

    return TOMMRO_C_ERR_SUCCESS;
}
    
/*******************************************************************************
 * functions
 ******************************************************************************/
 
tommRoC_err_enum_t tommRoCTemplateOsStart(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayMsecStart());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayUsecStart());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsUptimeMsecStart());

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCalendarStart());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCriticalStart());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsIsFromISRStart());

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsSleepForMsecStart());
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsStop(void) {

#if defined (__TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsSleepForMsecStop());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCriticalStop());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsIsFromISRStop());

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCalendarStop());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsUptimeMsecStop());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayUsecStop());
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsDelayMsecStop());

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsDelayMsecStart(void) {
    return tommRoCOsInitDelayMsec(_delay_msec);
}

tommRoC_err_enum_t tommRoCTemplateOsDelayUsecStart(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_start_up_delay_usec());

    return tommRoCOsInitDelayUsec(_delay_usec);
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeMsecStart(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_start_up_get_uptime_msec());

    return tommRoCOsInitUptimeMsec(_get_uptime_msec);
}

tommRoC_err_enum_t tommRoCTemplateOsUptimeUsecStart(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsHardClockStart(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
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

    tommRoC_os_critical_funct_t criticalFunct;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCriticalInit());

    criticalFunct.enterCritical = tommRoCTemplateOsCriticalEnter;
    criticalFunct.exitCritical  = tommRoCTemplateOsCriticalExit;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsInitCritical(&criticalFunct));

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
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
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
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsHardClockStop(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
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

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCOsCloseEnv(TOMMRO_C_OS_CRITICAL_FUNCT));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOsCriticalClose());

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
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

#endif
