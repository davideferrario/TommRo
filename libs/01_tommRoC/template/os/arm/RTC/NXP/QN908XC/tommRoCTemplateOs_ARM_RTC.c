
#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/arm/RTC/tommRoCTemplateOs_ARM_RTC.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__)

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

    RTC_Init(RTC);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateOs_ARM_RTCGetDateTime(
                    &dateTime));
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateOs_ARM_RTCSetDateTime(
                    &dateTime));

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCClose(void) {

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

    if (kStatus_Success != RTC_SetDatetime(RTC, &datetime)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCGetDateTime(tommRoC_date_time_t* const dateTimePtr) {

    rtc_datetime_t datetime;

    RTC_GetDatetime(RTC, &datetime);

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
    TOMMROC_UTIL_UNUSED_PARAM(toSecond);

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCAlarmClose(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

#endif
#endif

#endif
