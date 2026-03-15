
#ifndef TOMMROC_DATE_TIME_H_
#define TOMMROC_DATE_TIME_H_

/*
 *******************************************************************************
 * License
 * (C) Copyright 2017
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications according to the supply agreement.
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: this software is provided
 * "AS IS", with no express or implied warranties of any kind, including,
 * but not limited to, any implied warranties of merchantability or
 * fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Supplier will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 */

/**
 * @defgroup tommRoCDateTime tommRoCDateTime
 *
 * @brief  TommRoC library date/time module
 * @author TommRo Software Department
 *
 * This module is providing date/time functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCUtil.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// tommRoC date time.
#define TOMMROC_DATE_TIME_HANDLE_SIZE       (   TOMMROC_UTIL_U8_SIZE    +   \
                                                TOMMROC_UTIL_U8_SIZE    +   \
                                                TOMMROC_UTIL_U8_SIZE    +   \
                                                TOMMROC_UTIL_U8_SIZE    +   \
                                                TOMMROC_UTIL_U8_SIZE    +   \
                                                TOMMROC_UTIL_U8_SIZE    +   \
                                                TOMMROC_UTIL_U8_SIZE        )

// Format of string of date time to string function
#define TOMMROC_DATE_TIME_TO_STRING_FORMAT                              "xxx dd/mm/yyyy hh:mm:ss"
#define TOMMROC_DATE_TIME_TO_STRING_FORMAT_SIZE_BYTE                    (sizeof(TOMMROC_DATE_TIME_TO_STRING_FORMAT))
#define TOMMROC_DATE_TIME_TO_STRING_FORMAT_STR_LENGTH                   (TOMMROC_UTIL_STRING_ARR_LENGTH(TOMMROC_DATE_TIME_TO_STRING_FORMAT))

// Format of string of date time - only date - to string function
#define TOMMROC_DATE_TIME_ONLY_DATE_TO_STRING_FORMAT                    "xxx dd/mm/yyyy"
#define TOMMROC_DATE_TIME_ONLY_DATE_TO_STRING_FORMAT_SIZE_BYTE          (sizeof(TOMMROC_DATE_TIME_ONLY_DATE_TO_STRING_FORMAT))
#define TOMMROC_DATE_TIME_ONLY_DATE_TO_STRING_FORMAT_STR_LENGTH         (TOMMROC_UTIL_STRING_ARR_LENGTH(TOMMROC_DATE_TIME_ONLY_DATE_TO_STRING_FORMAT))

// Format of string of date time - only partial date - to string function
#define TOMMROC_DATE_TIME_ONLY_DATE_PARTIAL_TO_STRING_FORMAT            "dd/mm/yyyy"
#define TOMMROC_DATE_TIME_ONLY_DATE_PARTIAL_TO_STRING_FORMAT_SIZE_BYTE  (sizeof(TOMMROC_DATE_TIME_ONLY_DATE_PARTIAL_TO_STRING_FORMAT))
#define TOMMROC_DATE_TIME_ONLY_DATE_PARTIAL_TO_STRING_FORMAT_STR_LENGTH (TOMMROC_UTIL_STRING_ARR_LENGTH(TOMMROC_DATE_TIME_ONLY_DATE_PARTIAL_TO_STRING_FORMAT))

// Format of string of date time - only time - to string function
#define TOMMROC_DATE_TIME_ONLY_TIME_TO_STRING_FORMAT                    "hh:mm:ss"
#define TOMMROC_DATE_TIME_ONLY_TIME_TO_STRING_FORMAT_SIZE_BYTE          (sizeof(TOMMROC_DATE_TIME_ONLY_TIME_TO_STRING_FORMAT))
#define TOMMROC_DATE_TIME_ONLY_TIME_TO_STRING_FORMAT_STR_LENGTH         (TOMMROC_UTIL_STRING_ARR_LENGTH(TOMMROC_DATE_TIME_ONLY_TIME_TO_STRING_FORMAT))

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC Date Time weekday.
typedef enum {

    TOMMRO_C_DATE_TIME_SUNDAY = 0,
    TOMMRO_C_DATE_TIME_MONDAY,
    TOMMRO_C_DATE_TIME_TUESDAY,
    TOMMRO_C_DATE_TIME_WEDNESDAY,
    TOMMRO_C_DATE_TIME_THURSDAY,
    TOMMRO_C_DATE_TIME_FRIDAY,
    TOMMRO_C_DATE_TIME_SATURDAY,

} tommRoC_date_time_weekday_enum_t;

// tommRoC date time.
typedef struct {
    uint8_t data[TOMMROC_DATE_TIME_HANDLE_SIZE];
} tommRoC_date_time_t;

#define __EMPTY_tommRoC_date_time_t_data_field__            TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_DATE_TIME_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_date_time_t__                       \
{                                                           \
    /* .data */ __EMPTY_tommRoC_date_time_t_data_field__,   \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init a new date time structure.
 *
 * param[in]        dayOfMonth              calendar day of month [1-31].
 * param[in]        month                   calendar month [1-12].
 * param[in]        year                    calendar year [1970,....].
 * param[in]        hour                    calendar hours [0-23].
 * param[in]        minute                  calendar minutes [0-59].
 * param[in]        second                  calendar seconds [0-59].
 * param[out]       dateTimePtr             output date time structure pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDateTimeInit(
        const   uint8_t                         dayOfMonth,
        const   uint8_t                         month,
        const   uint16_t                        year,
        const   uint8_t                         hour,
        const   uint8_t                         minute,
        const   uint8_t                         second,
                tommRoC_date_time_t*    const   dateTimePtr);

/**
 * Get a value (day/month/year/hour/minute/second/day of week/DOW as U8) from a date time structure.
 *
 * param[in]        dateTimePtr             input date time structure pointer.
 *
 * return uint8_t for day. (1-31).
 * return uint8_t for month. (1-12).
 * return uint16_t for year. (1970,....).
 * return uint8_t for hour. (0-23).
 * return uint8_t for minute. (0-59).
 * return uint8_t for second. (0-59).
 * return tommRoC_date_time_weekday_enum_t for day of week.
 * return uint8_t for DOW. Days since Sunday (0-6) - Sunday = 0.
 */
uint8_t tommRoCDateTimeGetDay(
        const   tommRoC_date_time_t*    const   dateTimePtr);
uint8_t tommRoCDateTimeGetMonth(
        const   tommRoC_date_time_t*    const   dateTimePtr);
uint16_t tommRoCDateTimeGetYear(
        const   tommRoC_date_time_t*    const   dateTimePtr);
uint8_t tommRoCDateTimeGetHour(
        const   tommRoC_date_time_t*    const   dateTimePtr);
uint8_t tommRoCDateTimeGetMinute(
        const   tommRoC_date_time_t*    const   dateTimePtr);
uint8_t tommRoCDateTimeGetSecond(
        const   tommRoC_date_time_t*    const   dateTimePtr);
tommRoC_date_time_weekday_enum_t tommRoCDateTimeGetDayOfWeek(
        const   tommRoC_date_time_t*    const   dateTimePtr);
uint8_t tommRoCDateTimeGetDOW(
        const   tommRoC_date_time_t*    const   dateTimePtr);

/**
 * Convert timestamp (epoch time - seconds from UTC 00:00:00 01/01/1970) to date time structure.
 *
 * param[in]        timestamp               timestamp.
 * param[out]       dateTimePtr             output date time structure pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDateTimeTimestampToDateTime(
        const   uint32_t                        timestamp,
                tommRoC_date_time_t*    const   dateTimePtr);

/**
 * Convert date time structure to timestamp (epoch time - seconds from UTC 00:00:00 01/01/1970).
 *
 * param[in]        dateTimePtr             input date time structure pointer.
 * param[out]       timestampPtr            timestamp pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDateTimeDateTimeToTimestamp(
        const   tommRoC_date_time_t*    const   dateTimePtr,
                uint32_t*               const   timestampPtr);

/**
 * Get round difference (seconds of difference) value of date time params.
 *
 * param[in]        dateTimeMinusPtr        date time minus pointer.
 * param[in]        dateTimeSubtractingPtr  date time subtracting pointer.
 *
 * return uint32_t
 */
uint32_t tommRoCDateTimeDateTimeRoundDiff(
        const   tommRoC_date_time_t*    const   dateTimeMinusPtr,
        const   tommRoC_date_time_t*    const   dateTimeSubtractingPtr);

/**
 * Get abs difference (seconds of difference) value of date time params.
 *
 * param[in]        dateTime1Ptr            date time minus pointer.
 * param[in]        dateTime2Ptr            date time subtracting pointer.
 *
 * return uint32_t
 */
uint32_t tommRoCDateTimeDateTimeABSDiff(
        const   tommRoC_date_time_t*    const   dateTime1Ptr,
        const   tommRoC_date_time_t*    const   dateTime2Ptr);

/**
 * Convert date time structure to string.
 * NOTE: string format is "xxx dd/mm/yyyy hh:mm:ss"
 *
 * param[in]        dateTimePtr             input date time structure pointer.
 * param[out]       dateTimeStrPtr          date time string pointer.
 * param[in]        dateTimeStrSize         date time string size [byte]. MUST be large enough to keep "xxx dd/mm/yyyy hh:mm:ss" string.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDateTimeDateTimeToString(
        const   tommRoC_date_time_t*    const   dateTimePtr,
                char*                   const   dateTimeStrPtr,
        const   uint16_t                        dateTimeStrSize);

/**
 * Convert string to date time structure.
 * NOTE: string format MUST be "xxx dd/mm/yyyy hh:mm:ss"
 *
 * param[in]        dateTimeStrPtr          date time string pointer.
 * param[in]        dateTimeStrLen          date time string length [byte].
 * param[out]       dateTimePtr             output date time structure pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDateTimeStringToDateTime(
        const   char*                   const   dateTimeStrPtr,
        const   uint16_t                        dateTimeStrLen,
                tommRoC_date_time_t*    const   dateTimePtr);

/**
 * Convert only date - complete part - of a date time structure to string.
 * NOTE: string format is "xxx dd/mm/yyyy"
 *
 * param[in]        dateTimePtr             input date time structure pointer.
 * param[out]       dateTimeStrPtr          date time string pointer.
 * param[in]        dateTimeStrSize         date time string size [byte]. MUST be large enough to keep "xxx dd/mm/yyyy" string.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDateTimeDateTimeOnlyDateToString(
        const   tommRoC_date_time_t*    const   dateTimePtr,
                char*                   const   dateTimeStrPtr,
        const   uint16_t                        dateTimeStrSize);

/**
 * Convert only date - partial part (day of week is skipped) - of a date time structure to string.
 * NOTE: string format is "dd/mm/yyyy"
 *
 * param[in]        dateTimePtr             input date time structure pointer.
 * param[out]       dateTimeStrPtr          date time string pointer.
 * param[in]        dateTimeStrSize         date time string size [byte]. MUST be large enough to keep "dd/mm/yyyy" string.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDateTimeDateTimeOnlyDatePartialToString(
        const   tommRoC_date_time_t*    const   dateTimePtr,
                char*                   const   dateTimeStrPtr,
        const   uint16_t                        dateTimeStrSize);

/**
 * Convert only time of a date time structure to string.
 * NOTE: string format is "hh:mm:ss"
 *
 * param[in]        dateTimePtr             input date time structure pointer.
 * param[out]       dateTimeStrPtr          date time string pointer.
 * param[in]        dateTimeStrSize         date time string size [byte]. MUST be large enough to keep "hh:mm:ss" string.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDateTimeDateTimeOnlyTimeToString(
        const   tommRoC_date_time_t*    const   dateTimePtr,
                char*                   const   dateTimeStrPtr,
        const   uint16_t                        dateTimeStrSize);

/**
 * @}
 */

#endif
