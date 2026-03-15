
#ifndef TOMMROC_TEMPLATE_OS__ARM__SYS_TICK_H_
#define TOMMROC_TEMPLATE_OS__ARM__SYS_TICK_H_

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
#if defined (__TOMMROC_TEMPLATE_ARM_ATMEL_IS_USED__)
#define TOMMROC_TEMPLATE_OS__ARM__SYSTICK_IS_USED
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_GD32_IS_USED__)
#define TOMMROC_TEMPLATE_OS__ARM__SYSTICK_IS_USED
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)
#define TOMMROC_TEMPLATE_OS__ARM__SYSTICK_IS_USED
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)
#define TOMMROC_TEMPLATE_OS__ARM__SYSTICK_IS_USED
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)
#define TOMMROC_TEMPLATE_OS__ARM__SYSTICK_IS_USED
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (TOMMROC_TEMPLATE_OS__ARM__SYSTICK_IS_USED)

tommRoC_err_enum_t tommRoCTemplateOs_ARM_SysTickInit(void);
void tommRoCTemplateOs_ARM_SysTickClose(void);

void tommRoCTemplateOs_ARM_SysTickEnable(void);
void tommRoCTemplateOs_ARM_SysTickDisable(void);

tommRoC_err_enum_t tommRoCTemplateOs_ARM_SysTickDelayMsec(const uint32_t msec);
uint32_t tommRoCTemplateOs_ARM_SysTickGetUptimeMsec(void);

void tommRoCTemplateOs_ARM_SysTickIncMSec(const uint32_t msec);

#endif

#endif

#endif
