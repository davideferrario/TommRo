
#ifndef TOMMROC_TEMPLATE_OS_H_
#define TOMMROC_TEMPLATE_OS_H_

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
 * Author
 * TommRo Software Department
 */

/**
 *  - Time (delay, uptime):
 *      - __TOMMROC_USE_TIME_ARM_OS_TEMPLATE__                              hardware ARM (SysTick)
 *      - __TOMMROC_USE_TIME_ESP32_OS_TEMPLATE__                            hardware ESP32
 *      - __TOMMROC_USE_TIME_TIME_H_OS_TEMPLATE__                           time.h library
 *      - __TOMMROC_USE_TIME_WINDOWS_OS_TEMPLATE__                          Windows time.h library
 *      - __TOMMROC_USE_TIME_XC_OS_TEMPLATE__                               Microchip XC compiler
 *  - Calendar:
 *      - __TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__                           hardware (or time.h library) calendar
 *      - __TOMMROC_USE_SOFT_CALENDAR_OS_TEMPLATE__                         TommRoC software calendar
 *  - Sleep:
 *      - __TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__        hardware calendar (RTC) is used for wake up sleep for msec.
 *      - __TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__           hardware timer (low power timer if available) is used for wake up sleep for msec.
 *  - Reset cause:
 *      - __TOMMROC_USE_RESET_CAUSE_OS_TEMPLATE__                           reset cause.
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#if defined (__TOMMROC_USE_LOW_POWER_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
#error "__TOMMROC_USE_LOW_POWER_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__ is deprecated. Use __TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__ instead"
#endif

#include "env/tommRoCTemplateEnv.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************** ARM Os template */
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)
#if defined (__TOMMROC_OS_TEMPLATE_IS_USED__)
#error "tommRoC Os template multiple definition"
#else
#define __TOMMROC_OS_TEMPLATE_IS_USED__
#endif
#endif

/******************** ESP32 Os template */
#if defined (__TOMMROC_USE_TIME_ESP32_OS_TEMPLATE__)
#if defined (__TOMMROC_OS_TEMPLATE_IS_USED__)
#error "tommRoC Os template multiple definition"
#else
#define __TOMMROC_OS_TEMPLATE_IS_USED__
#endif
#endif

/******************** Time.h Os template */
#if defined (__TOMMROC_USE_TIME_TIME_H_OS_TEMPLATE__)
#if defined (__TOMMROC_OS_TEMPLATE_IS_USED__)
#error "tommRoC Os template multiple definition"
#else
#define __TOMMROC_OS_TEMPLATE_IS_USED__
#endif
#endif

/******************** Win Os template */
#if defined (__TOMMROC_USE_TIME_WINDOWS_OS_TEMPLATE__)
#if defined (__TOMMROC_OS_TEMPLATE_IS_USED__)
#error "tommRoC Os template multiple definition"
#else
#define __TOMMROC_OS_TEMPLATE_IS_USED__
#endif
#endif

/******************** XC time Os template */
#if defined (__TOMMROC_USE_TIME_XC_OS_TEMPLATE__)
#if defined (__TOMMROC_OS_TEMPLATE_IS_USED__)
#error "tommRoC Os template multiple definition"
#else
#define __TOMMROC_OS_TEMPLATE_IS_USED__
#endif
#endif


/******************** Check template is used */
#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__) && defined (__TOMMROC_USE_SOFT_CALENDAR_OS_TEMPLATE__)
#error "It is not possible to use both tommRoC Os hardware and software calendar template"
#endif
#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__) || defined (__TOMMROC_USE_SOFT_CALENDAR_OS_TEMPLATE__)
#define __TOMMROC_OS_CALENDAR_TEMPLATE_IS_USED__
#endif


#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__) && defined (__TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
#error "Use only one wake up source for tommRoC Os sleep for template"
#endif
#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__) && !defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
#error "It is not possible to use tommRoC Os sleep for without hardware calendar template"
#endif
#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__) || defined (__TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
#define __TOMMROC_OS_SLEEP_FOR_MSEC_TEMPLATE_IS_USED__
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOsStart(void);
tommRoC_err_enum_t tommRoCTemplateOsStop(void);

tommRoC_err_enum_t tommRoCTemplateOsDelayMsecStart(void);
tommRoC_err_enum_t tommRoCTemplateOsDelayUsecStart(void);
tommRoC_err_enum_t tommRoCTemplateOsUptimeMsecStart(void);
tommRoC_err_enum_t tommRoCTemplateOsUptimeUsecStart(void);
tommRoC_err_enum_t tommRoCTemplateOsHardClockStart(void);
tommRoC_err_enum_t tommRoCTemplateOsCalendarStart(void);
tommRoC_err_enum_t tommRoCTemplateOsCriticalStart(void);
tommRoC_err_enum_t tommRoCTemplateOsIsFromISRStart(void);
tommRoC_err_enum_t tommRoCTemplateOsSleepForMsecStart(void);
tommRoC_err_enum_t tommRoCTemplateOsRebootStart(void);
tommRoC_err_enum_t tommRoCTemplateOsGetUUIDStart(void);
tommRoC_err_enum_t tommRoCTemplateOsResetCauseStart(void);

tommRoC_err_enum_t tommRoCTemplateOsDelayMsecStop(void);
tommRoC_err_enum_t tommRoCTemplateOsDelayUsecStop(void);
tommRoC_err_enum_t tommRoCTemplateOsUptimeMsecStop(void);
tommRoC_err_enum_t tommRoCTemplateOsUptimeUsecStop(void);
tommRoC_err_enum_t tommRoCTemplateOsHardClockStop(void);
tommRoC_err_enum_t tommRoCTemplateOsCalendarStop(void);
tommRoC_err_enum_t tommRoCTemplateOsCriticalStop(void);
tommRoC_err_enum_t tommRoCTemplateOsIsFromISRStop(void);
tommRoC_err_enum_t tommRoCTemplateOsSleepForMsecStop(void);
tommRoC_err_enum_t tommRoCTemplateOsRebootStop(void);
tommRoC_err_enum_t tommRoCTemplateOsGetUUIDStop(void);
tommRoC_err_enum_t tommRoCTemplateOsResetCauseStop(void);

#endif
