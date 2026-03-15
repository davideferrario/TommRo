
#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/arm/RTC/tommRoCTemplateOs_ARM_RTC.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_ATMEL_IS_USED__)

#include "TOMMROC.h"

#include "driver_init.h"

#include <hal_calendar.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static tommRoC_template_os_arm_rtc_alarm_callback_t _alarm_cb = NULL;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static void _alarm_low_level_cb(struct calendar_descriptor *const calendar) {

    TOMMROC_ASSERT_EQUALS(calendar, &CALENDAR_0);

    if (NULL == _alarm_cb) {
        return;
    }

    _alarm_cb();
}

static tommRoC_err_enum_t _set_date_time_low_level(struct calendar_time *const calendarTimePtr, struct calendar_date *const calendarDatePtr) {

    if (ERR_NONE != calendar_set_time(&CALENDAR_0, calendarTimePtr)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    if (ERR_NONE != calendar_set_date(&CALENDAR_0, calendarDatePtr)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _set_date_time(struct calendar_time *const calendarTimePtr, struct calendar_date *const calendarDatePtr) {

    tommRoC_err_enum_t res;

    if (ERR_NONE != calendar_disable(&CALENDAR_0)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    res = _set_date_time_low_level(calendarTimePtr, calendarDatePtr);

    if (ERR_NONE != calendar_enable(&CALENDAR_0)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return res;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCInit(void) {

    if (ERR_NONE != calendar_enable(&CALENDAR_0)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCClose(void) {

    if (ERR_NONE != calendar_disable(&CALENDAR_0)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

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

    struct calendar_time calendarTime;
    struct calendar_date calendarDate;

    uint32_t criticalSpecificData;

    tommRoC_err_enum_t res;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&calendarTime, 0x00, sizeof(calendarTime)));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&calendarDate, 0x00, sizeof(calendarDate)));

    calendarTime.hour   = tommRoCDateTimeGetHour(dateTimePtr);
    calendarTime.min    = tommRoCDateTimeGetMinute(dateTimePtr);
    calendarTime.sec    = tommRoCDateTimeGetSecond(dateTimePtr);

    calendarDate.day    = tommRoCDateTimeGetDay(dateTimePtr);
    calendarDate.month  = tommRoCDateTimeGetMonth(dateTimePtr);
    calendarDate.year   = tommRoCDateTimeGetYear(dateTimePtr);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsEnterCritical(&criticalSpecificData));

    res = _set_date_time(&calendarTime, &calendarDate);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsExitCritical(&criticalSpecificData));

    return res;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCGetDateTime(tommRoC_date_time_t* const dateTimePtr) {

    struct calendar_date_time dateTime;

    if (ERR_NONE != calendar_get_date_time(&CALENDAR_0, &dateTime)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCDateTimeInit(
                    dateTime.date.day,
                    dateTime.date.month,
                    dateTime.date.year,
                    dateTime.time.hour,
                    dateTime.time.min,
                    dateTime.time.sec,
                    dateTimePtr));

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTC_SetAlarmCallback(const tommRoC_template_os_arm_rtc_alarm_callback_t alarmCb) {

    _alarm_cb = alarmCb;

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCAlarmInit(const uint32_t toSecond) {

    static struct calendar_alarm alarm;

    uint32_t alarmTimestamp;

    tommRoC_date_time_t alarmDateTime;

    TOMMROC_ASSERT_NOT_ZERO(toSecond);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&alarm, 0x00, sizeof(alarm)));

    alarmTimestamp = tommRoCOsGetTimestamp() + toSecond;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCDateTimeTimestampToDateTime(alarmTimestamp, &alarmDateTime));

    alarm.cal_alarm.datetime.time.sec   = tommRoCDateTimeGetSecond(&alarmDateTime);
    alarm.cal_alarm.datetime.time.min   = tommRoCDateTimeGetMinute(&alarmDateTime);
    alarm.cal_alarm.datetime.time.hour  = tommRoCDateTimeGetHour(&alarmDateTime);
    alarm.cal_alarm.datetime.date.day   = tommRoCDateTimeGetDay(&alarmDateTime);
    alarm.cal_alarm.datetime.date.month = tommRoCDateTimeGetMonth(&alarmDateTime);
    alarm.cal_alarm.datetime.date.year  = tommRoCDateTimeGetYear(&alarmDateTime);
    alarm.cal_alarm.option              = CALENDAR_ALARM_MATCH_YEAR;
    alarm.cal_alarm.mode                = ONESHOT;

    if (ERR_NONE != calendar_set_alarm(&CALENDAR_0, &alarm, _alarm_low_level_cb)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCAlarmClose(void) {

    static struct calendar_alarm alarm;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&alarm, 0x00, sizeof(alarm)));

    alarm.cal_alarm.option = CALENDAR_ALARM_MATCH_DISABLED;

    if (ERR_NONE != calendar_set_alarm(&CALENDAR_0, &alarm, _alarm_low_level_cb)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

#endif

#endif
