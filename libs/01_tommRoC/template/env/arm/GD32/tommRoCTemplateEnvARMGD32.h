
#ifndef TOMMROC_TEMPLATE_ENV_ARM_GD32_H_
#define TOMMROC_TEMPLATE_ENV_ARM_GD32_H_

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

/*******************************************************************************
 * defines
 ******************************************************************************/
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

// HAL Driver GD32 section
#if defined (USE_STDPERIPH_DRIVER)
#define __TOMMROC_TEMPLATE_ARM_STDPERIPH_DRIVER_IS_USED__
#endif


// GD32 platform define section
#if defined (GD32F450)

#define __TOMMROC_TEMPLATE_ARM_GD32_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_GD32Fx_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_GD32F4_IS_USED__
#endif


#if defined (__TOMMROC_TEMPLATE_ARM_GD32_IS_USED__)
#define TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE  (3 * TOMMROC_UTIL_U32_SIZE)
#endif


// GD32 platform include section
#if defined (__TOMMROC_TEMPLATE_ARM_STDPERIPH_DRIVER_IS_USED__) && defined (__TOMMROC_TEMPLATE_ARM_GD32F4_IS_USED__)
#include "gd32f4xx_libopt.h"
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif

#endif
