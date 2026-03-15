
#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/arm/RTC/tommRoCTemplateOs_ARM_RTC.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)
#include "main.h"

#include "rtc.h"
#if !defined (HAL_RTC_MODULE_ENABLED)
#error "HAL_RTC_MODULE_ENABLED must be defined"
#endif

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

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCInit(void) {

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCClose(void) {

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCSetTimestamp(const uint32_t timestamp) {

    TOMMROC_UTIL_UNUSED_PARAM(timestamp);

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

uint32_t tommRoCTemplateOs_ARM_RTCGetTimestamp(void) {

    return 0;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCSetDateTime(const tommRoC_date_time_t* const dateTimePtr) {

    static const uint8_t WeekDayTable[] = {
            RTC_WEEKDAY_SUNDAY,
            RTC_WEEKDAY_MONDAY,
            RTC_WEEKDAY_TUESDAY,
            RTC_WEEKDAY_WEDNESDAY,
            RTC_WEEKDAY_THURSDAY,
            RTC_WEEKDAY_FRIDAY,
            RTC_WEEKDAY_SATURDAY,
    };

    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    sTime.Hours             = tommRoCDateTimeGetHour(dateTimePtr);
    sTime.Minutes           = tommRoCDateTimeGetMinute(dateTimePtr);
    sTime.Seconds           = tommRoCDateTimeGetSecond(dateTimePtr);
#if defined (RTC_DAYLIGHTSAVING_NONE)
    sTime.DayLightSaving    = RTC_DAYLIGHTSAVING_NONE;
#endif
#if defined (RTC_STOREOPERATION_RESET)
    sTime.StoreOperation    = RTC_STOREOPERATION_RESET;
#endif

    sDate.WeekDay           = WeekDayTable[tommRoCDateTimeGetDOW(dateTimePtr)];
    sDate.Month             = tommRoCDateTimeGetMonth(dateTimePtr);
    sDate.Date              = tommRoCDateTimeGetDay(dateTimePtr);
    sDate.Year              = tommRoCDateTimeGetYear(dateTimePtr) - TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MIN_VALID_YEAR;

    if (HAL_OK != HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }
    if (HAL_OK != HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCGetDateTime(tommRoC_date_time_t* const dateTimePtr) {

    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    if (HAL_OK != HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }
    if (HAL_OK != HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCDateTimeInit(
                    sDate.Date,
                    sDate.Month,
                    (uint16_t) sDate.Year + TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MIN_VALID_YEAR,
                    sTime.Hours,
                    sTime.Minutes,
                    sTime.Seconds,
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
