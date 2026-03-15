
#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/arm/RTC/tommRoCTemplateOs_ARM_RTC.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)

#include "TOMMROC.h"

#include "fsl_rtc.h"

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
static tommRoC_err_enum_t _tommRoCDateTime_to_rtcDatetime(
        const   tommRoC_date_time_t*    const   tommRoCDateTimePtr,
                rtc_datetime_t*         const   rtcDatetimePtr) {

    TOMMROC_ASSERT_NOT_NULL(tommRoCDateTimePtr);
    TOMMROC_ASSERT_NOT_NULL(rtcDatetimePtr);

    rtcDatetimePtr->day     = tommRoCDateTimeGetDay(tommRoCDateTimePtr);
    rtcDatetimePtr->month   = tommRoCDateTimeGetMonth(tommRoCDateTimePtr);
    rtcDatetimePtr->year    = tommRoCDateTimeGetYear(tommRoCDateTimePtr);
    rtcDatetimePtr->hour    = tommRoCDateTimeGetHour(tommRoCDateTimePtr);
    rtcDatetimePtr->minute  = tommRoCDateTimeGetMinute(tommRoCDateTimePtr);
    rtcDatetimePtr->second  = tommRoCDateTimeGetSecond(tommRoCDateTimePtr);

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _rtcDateTime_to_tommRoCDatetime(
        const   rtc_datetime_t*         const   rtcDatetimePtr,
                tommRoC_date_time_t*    const   tommRoCDateTimePtr) {

    TOMMROC_ASSERT_NOT_NULL(rtcDatetimePtr);
    TOMMROC_ASSERT_NOT_NULL(tommRoCDateTimePtr);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCDateTimeInit(
                    rtcDatetimePtr->day,
                    rtcDatetimePtr->month,
                    rtcDatetimePtr->year,
                    rtcDatetimePtr->hour,
                    rtcDatetimePtr->minute,
                    rtcDatetimePtr->second,
                    tommRoCDateTimePtr));

    return TOMMRO_C_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCInit(void) {

    tommRoC_date_time_t dateTime;

    rtc_config_t rtcConfig;

    RTC_GetDefaultConfig(&rtcConfig);

#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    rtcConfig.clockSource   = kRTC_LPOCLK;
    rtcConfig.prescaler     = kRTC_ClockDivide_32_100;
    rtcConfig.time_us       = 1000000U + 99999U;    // NOTE: fixed with oscilloscope
#endif

    // Start RTC
    RTC_Init(RTC, &rtcConfig);

    NVIC_ClearPendingIRQ(RTC_IRQn);
    EnableIRQ(RTC_IRQn);
    RTC_EnableInterrupts(RTC, kRTC_InterruptEnable);

    // Little delay before enable time counter to allow the 32.768 kHz clock time to stabilize.
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateOs_ARM_RTCGetDateTime(
                    &dateTime));
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateOs_ARM_RTCSetDateTime(
                    &dateTime));

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCClose(void) {

    // Disable RTC Interrupt
    RTC_DisableInterrupts(RTC, kRTC_InterruptEnable);
    DisableIRQ(RTC_IRQn);
    NVIC_ClearPendingIRQ(RTC_IRQn);

    // Stop RTC
    RTC_Deinit(RTC);

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCSetTimestamp(const uint32_t timestamp) {

    TOMMROC_UTIL_UNUSED_PARAM(timestamp);

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

uint32_t tommRoCTemplateOs_ARM_RTCGetTimestamp(void) {

    return 0;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCSetDateTime(const tommRoC_date_time_t* const dateTimePtr) {

    rtc_datetime_t datetime;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _tommRoCDateTime_to_rtcDatetime(
                    dateTimePtr,
                    &datetime));

    if (kStatus_Success != RTC_SetDatetime(&datetime)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCGetDateTime(tommRoC_date_time_t* const dateTimePtr) {

    rtc_datetime_t datetime;

    RTC_GetDatetime(&datetime);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _rtcDateTime_to_tommRoCDatetime(
                    &datetime,
                    dateTimePtr));

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTC_SetAlarmCallback(const tommRoC_template_os_arm_rtc_alarm_callback_t alarmCb) {

    TOMMROC_UTIL_UNUSED_PARAM(alarmCb);

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCAlarmInit(const uint32_t toSecond) {

    uint32_t currentTimestamp;

    TOMMROC_ASSERT_NOT_ZERO(toSecond);

    currentTimestamp = tommRoCOsGetTimestamp();

    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(toSecond + currentTimestamp, toSecond);
    TOMMROC_ASSERT_MORE_THAN(toSecond + currentTimestamp, currentTimestamp);

    TOMMROC_PARAM_CHECK_ON_TEST_RETURN_ERR(toSecond + currentTimestamp, <, toSecond);
    TOMMROC_PARAM_CHECK_ON_TEST_RETURN_ERR(toSecond + currentTimestamp, <=, currentTimestamp);

    RTC_SetAlarm(toSecond - 1);

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCAlarmClose(void) {

    return TOMMRO_C_ERR_SUCCESS;
}

#endif
#endif

#endif
