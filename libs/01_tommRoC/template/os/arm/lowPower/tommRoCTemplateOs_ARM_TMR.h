
#ifndef TOMMROC_TEMPLATE_OS__ARM__TMR_H_
#define TOMMROC_TEMPLATE_OS__ARM__TMR_H_

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

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// Nordic section
#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)
#if defined (APP_TIMER_V2_RTC1_ENABLED)
#define TOMMROC_TEMPLATE_OS__ARM__TMR_USED_NRF_DRV_RTC_INSTANCE     0
#define TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE                (RTC0_IRQn)
#else
#define TOMMROC_TEMPLATE_OS__ARM__TMR_USED_NRF_DRV_RTC_INSTANCE     1
#define TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE                (RTC1_IRQn)
#endif
#endif

// SiLabs section
#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)
#define TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LETIMER_TYPE             (LETIMER0)
#define TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE                (LETIMER0_IRQn)
#endif

// NXP section
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)
#if defined (FSL_FEATURE_SOC_LPTMR_COUNT) && FSL_FEATURE_SOC_LPTMR_COUNT
#define TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LPTMR_TYPE               (LPTMR0)
#define TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE                (LPTMR0_IRQn)
#endif
#endif

// STM section
#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)
#if defined (__TOMMROC_TEMPLATE_ARM_STM32F0_IS_USED__)
#endif
#if defined (__TOMMROC_TEMPLATE_ARM_STM32F1_IS_USED__)
#endif
#if defined (__TOMMROC_TEMPLATE_ARM_STM32F4_IS_USED__)
#endif
#if defined (__TOMMROC_TEMPLATE_ARM_STM32L0_IS_USED__)
#endif
#if defined (__TOMMROC_TEMPLATE_ARM_STM32L4_IS_USED__)
#endif
#if defined (__TOMMROC_TEMPLATE_ARM_STM32U5_IS_USED__)
#endif
#if defined (__TOMMROC_TEMPLATE_ARM_STM32WB_IS_USED__)
#endif
#if defined (__TOMMROC_TEMPLATE_ARM_STM32WBA_IS_USED__)
#endif
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOs_ARM_TMRInit(const uint32_t msec);
tommRoC_err_enum_t tommRoCTemplateOs_ARM_TMRClose(void);

#endif

#endif
