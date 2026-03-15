
#ifndef TOMMROC_MW_TEMPLATE_RTOS_CMSIS_RTOS_ENV_H_
#define TOMMROC_MW_TEMPLATE_RTOS_CMSIS_RTOS_ENV_H_

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

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "rtos/cmsisRTOS/common/env/esp32/tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_ESP32.h"
#endif

#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V1/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"
#elif defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V2/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"
#endif

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
#include "rtos/cmsisRTOS/common/env/freeRTOS/tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_FreeRTOS.h"
#endif

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
#include "rtos/cmsisRTOS/common/env/keilRTX/tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_KeilRTX.h"
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
