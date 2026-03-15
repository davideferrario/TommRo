
#ifndef TOMMROC_MW_TEMPLATE_RTOS_CMSIS_V2_OS_H_
#define TOMMROC_MW_TEMPLATE_RTOS_CMSIS_V2_OS_H_

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

#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_IS_USED__)
#if defined (__TOMMROC_MW_USE_CMSIS_RTOS_RTX_TEMPLATE__)
#define __TOMMROC_MW_ARM_CMSIS_RTOS_EXTERNAL_IS_USED__
#else
#define __TOMMROC_MW_ARM_CMSIS_RTOS_INTERNAL_TEMPLATE_IS_USED__
#endif
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#define __TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__
#else
#define __TOMMROC_MW_ARM_CMSIS_RTOS_INTERNAL_TEMPLATE_IS_USED__
#endif

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_EXTERNAL_IS_USED__)
#include "cmsis_os.h"

#elif defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
#include "rtos/cmsisRTOS/V2/common/CMSIS_RTOS/env/esp32/cmsis_os.h"

#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_INTERNAL_TEMPLATE_IS_USED__)
// NOTE: include FreeRTOS.h must appear in source files before include task.h
#include "FreeRTOS.h"
#include "task.h"
#if (tskKERNEL_VERSION_MAJOR == 10) && (tskKERNEL_VERSION_MINOR == 3) && (tskKERNEL_VERSION_BUILD == 1)
#include "rtos/cmsisRTOS/V2/common/CMSIS_RTOS/env/freeRTOS/v10.3.1/cmsis_os.h"
#elif (tskKERNEL_VERSION_MAJOR == 10) && (tskKERNEL_VERSION_MINOR == 5) && (tskKERNEL_VERSION_BUILD == 1)
#include "rtos/cmsisRTOS/V2/common/CMSIS_RTOS/env/freeRTOS/v10.5.1/cmsis_os.h"
#elif (tskKERNEL_VERSION_MAJOR == 10) && (tskKERNEL_VERSION_MINOR == 6) && (tskKERNEL_VERSION_BUILD == 2)
#include "rtos/cmsisRTOS/V2/common/CMSIS_RTOS/env/freeRTOS/v10.6.2/cmsis_os.h"
#else
#error "Not supported FreeRTOS version"
#endif
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

#endif
