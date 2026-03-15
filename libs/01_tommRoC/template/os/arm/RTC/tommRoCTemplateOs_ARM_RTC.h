
#ifndef TOMMROC_TEMPLATE_OS__ARM__RTC_H_
#define TOMMROC_TEMPLATE_OS__ARM__RTC_H_

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

#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "env/tommRoCTemplateEnv.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

#define TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_TIMESTAMP_U32_MIN_VALID_YEAR ((uint16_t) 1970)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_TIMESTAMP_U32_MAX_VALID_YEAR ((uint16_t) 2099)

// Atmel section
#if defined (__TOMMROC_TEMPLATE_ARM_ATMEL_IS_USED__)

#define TOMMROC_TEMPLATE_OS__ARM__RTC_HW_BASED_IS_USED
#define TOMMROC_TEMPLATE_OS__ARM__RTC_DATE_TIME_BASED_IS_USED
#define TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MIN_VALID_YEAR       (TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_TIMESTAMP_U32_MIN_VALID_YEAR)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MAX_VALID_YEAR       (TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_TIMESTAMP_U32_MAX_VALID_YEAR)
#endif

// Nordic section
#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)

#define TOMMROC_TEMPLATE_OS__ARM__RTC_INTERRUPT_BASED_IS_USED
#define TOMMROC_TEMPLATE_OS__ARM__RTC_TIMESTAMP_BASED_IS_USED

#if (defined (RTC_PRESENT) && RTC_COUNT)
#if (0 == (RTC_COUNT - 1))
#define TOMMROC_TEMPLATE_OS__ARM__RTC_USED_NRF_DRV_RTC_INSTANCE     0
#define TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE                (RTC0_IRQn)
#elif (1 == (RTC_COUNT - 1))
#define TOMMROC_TEMPLATE_OS__ARM__RTC_USED_NRF_DRV_RTC_INSTANCE     1
#define TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE                (RTC1_IRQn)
#elif (2 == (RTC_COUNT - 1))
#define TOMMROC_TEMPLATE_OS__ARM__RTC_USED_NRF_DRV_RTC_INSTANCE     2
#define TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE                (RTC2_IRQn)
#endif
#endif
#endif

// SiLabs section
#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)

#if defined (RTCC_PRESENT) && RTCC_COUNT
#define TOMMROC_TEMPLATE_OS__ARM__RTC_HW_BASED_IS_USED
#define TOMMROC_TEMPLATE_OS__ARM__RTC_TIMESTAMP_BASED_IS_USED

#define TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE                (RTCC_IRQn)

#elif defined (RTC_PRESENT) && RTC_COUNT
#define TOMMROC_TEMPLATE_OS__ARM__RTC_INTERRUPT_BASED_IS_USED
#define TOMMROC_TEMPLATE_OS__ARM__RTC_TIMESTAMP_BASED_IS_USED

#define TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE                (RTC_IRQn)

#elif defined (BURTC_PRESENT) && BURTC_COUNT

#define TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE                (BURTC_IRQn)
#endif
#endif

// NXP section
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__)     ||  \
    defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_HW_BASED_IS_USED
#define TOMMROC_TEMPLATE_OS__ARM__RTC_TIMESTAMP_BASED_IS_USED
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_HW_BASED_IS_USED
#define TOMMROC_TEMPLATE_OS__ARM__RTC_DATE_TIME_BASED_IS_USED
#define TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MIN_VALID_YEAR       (TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_TIMESTAMP_U32_MIN_VALID_YEAR)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MAX_VALID_YEAR       (TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_TIMESTAMP_U32_MAX_VALID_YEAR)
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_INTERRUPT_BASED_IS_USED
#define TOMMROC_TEMPLATE_OS__ARM__RTC_DATE_TIME_BASED_IS_USED
#define TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MIN_VALID_YEAR       (TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_TIMESTAMP_U32_MIN_VALID_YEAR)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MAX_VALID_YEAR       (TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_TIMESTAMP_U32_MAX_VALID_YEAR)
#endif

#define TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE                (RTC_IRQn)
#endif

// STM section
#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_HW_BASED_IS_USED
#define TOMMROC_TEMPLATE_OS__ARM__RTC_DATE_TIME_BASED_IS_USED
#define TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MIN_VALID_YEAR       ((uint16_t) 2000)   // NOTE: set min year as 2000 (divisible by 4) because there is a bug in STM32 leap years
#define TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MAX_VALID_YEAR       (TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MIN_VALID_YEAR + (uint16_t) 99)

#if defined (__TOMMROC_TEMPLATE_ARM_STM32F0_IS_USED__)
#elif defined (__TOMMROC_TEMPLATE_ARM_STM32F1_IS_USED__)
#elif defined (__TOMMROC_TEMPLATE_ARM_STM32F4_IS_USED__)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE                (RTC_WKUP_IRQn)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_STM32_RTC_WKUP_IRQn_USED

#elif defined (__TOMMROC_TEMPLATE_ARM_STM32L0_IS_USED__)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE                (RTC_IRQn)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_STM32_RTC_IRQn_USED

#elif defined (__TOMMROC_TEMPLATE_ARM_STM32L4_IS_USED__)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE                (RTC_WKUP_IRQn)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_STM32_RTC_IRQn_USED

#elif defined (__TOMMROC_TEMPLATE_ARM_STM32WB_IS_USED__)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE                (RTC_WKUP_IRQn)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_STM32_RTC_WKUP_IRQn_USED

#elif defined (__TOMMROC_TEMPLATE_ARM_STM32WBA_IS_USED__)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE                (RTC_IRQn)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_STM32_RTC_IRQn_USED
#endif
#endif

/******************** Check errors */
#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__) && defined (TOMMROC_TEMPLATE_OS__ARM__RTC_NOT_AVAILABLE)
#error "It is not possible to use tommRoC Os hardware calendar template on this hardware"
#endif

#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_TIMESTAMP_BASED_IS_USED)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MIN_VALID_YEAR       (TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_TIMESTAMP_U32_MIN_VALID_YEAR)
#define TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_MAX_VALID_YEAR       (TOMMROC_TEMPLATE_OS__ARM__RTC_CALENDAR_TIMESTAMP_U32_MAX_VALID_YEAR)
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef void (*tommRoC_template_os_arm_rtc_alarm_callback_t)(void);

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCInit(void);
tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCClose(void);

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCSetTimestamp(const uint32_t timestamp);
uint32_t tommRoCTemplateOs_ARM_RTCGetTimestamp(void);

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCSetDateTime(const tommRoC_date_time_t* const dateTimePtr);
tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCGetDateTime(tommRoC_date_time_t* const dateTimePtr);

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTC_SetAlarmCallback(const tommRoC_template_os_arm_rtc_alarm_callback_t alarmCb);
tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCAlarmInit(const uint32_t toSecond);
tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCAlarmClose(void);

#endif

#endif
