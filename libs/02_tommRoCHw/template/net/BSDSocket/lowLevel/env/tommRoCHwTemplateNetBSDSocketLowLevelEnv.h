
#ifndef TOMMROC_HW_TEMPLATE_NET_BSD_SOCKET_LOW_LEVEL_ENV_H_
#define TOMMROC_HW_TEMPLATE_NET_BSD_SOCKET_LOW_LEVEL_ENV_H_

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
#include "net/BSDSocket/lowLevel/env/arm/tommRoCHwTemplateNetBSDSocketLowLevelEnvARM.h"

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "net/BSDSocket/lowLevel/env/esp32/tommRoCHwTemplateNetBSDSocketLowLevelEnvESP32.h"

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)
#include "net/BSDSocket/lowLevel/env/armLinux/tommRoCHwTemplateNetBSDSocketLowLevelEnvARMLinux.h"

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#include "net/BSDSocket/lowLevel/env/linux/tommRoCHwTemplateNetBSDSocketLowLevelEnvLinux.h"

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)
#include "net/BSDSocket/lowLevel/env/win/tommRoCHwTemplateNetBSDSocketLowLevelEnvWin.h"
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
