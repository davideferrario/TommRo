
#ifndef TOMMROC_TEMPLATE_ENV_H_
#define TOMMROC_TEMPLATE_ENV_H_

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
 
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#include "env/arm/tommRoCTemplateEnvARM.h"

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "env/esp32/tommRoCTemplateEnvESP32.h"

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)
#include "env/armLinux/tommRoCTemplateEnvARMLinux.h"

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#include "env/linux/tommRoCTemplateEnvLinux.h"

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)
#include "env/win/tommRoCTemplateEnvWin.h"

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#include "env/xc/xc8/tommRoCTemplateEnvXC8.h"

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16)
#include "env/xc/xc16/tommRoCTemplateEnvXC16.h"

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)
#include "env/xc/xc32/tommRoCTemplateEnvXC32.h"

#else
    #error "Not supported compiler"
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/
#if defined (TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE)
#define TOMMROC_TEMPLATE_OS_UUID_AS_STR_SIZE_BYTE   ((TOMMROC_STRING_U8_HEX_AS_STRING_MAX_LENGTH_BYTE * TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE) + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
