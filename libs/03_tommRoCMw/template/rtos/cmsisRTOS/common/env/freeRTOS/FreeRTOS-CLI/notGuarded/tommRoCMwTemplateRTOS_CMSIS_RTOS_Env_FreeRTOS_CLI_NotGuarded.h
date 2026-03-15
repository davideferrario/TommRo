
#ifndef TOMMROC_MW_TEMPLATE_RTOS_CMSIS_RTOS_ENV_FREE_RTOS_CLI_NOT_GUARDED_H_
#define TOMMROC_MW_TEMPLATE_RTOS_CMSIS_RTOS_ENV_FREE_RTOS_CLI_NOT_GUARDED_H_

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

#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V1/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"
#elif defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)
#include "rtos/cmsisRTOS/V2/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"
#endif

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)

#include "rtos/cmsisRTOS/common/env/freeRTOS/FreeRTOS-CLI/lib/FreeRTOS_CLI.h"

#include "TOMMROCMw.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_FreeRTOS_CLINotGuardedRegisterCommand(const CLI_Command_Definition_t* const commandToRegisterPtr);

bool tommRoCMwTemplateRTOS_CMSIS_RTOS_Env_FreeRTOS_CLINotGuardedProcessCommand(const char* const commandInputStrPtr, char* writeBufferStrPtr, uint32_t writeBufferStrSize);

#endif

#endif
