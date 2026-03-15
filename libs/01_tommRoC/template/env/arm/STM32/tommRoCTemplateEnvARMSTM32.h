
#ifndef TOMMROC_TEMPLATE_ENV_ARM_STM32_H_
#define TOMMROC_TEMPLATE_ENV_ARM_STM32_H_

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

// HAL Driver STM32 section
#if defined (USE_HAL_DRIVER)
#define __TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__
#endif


// STM32 platform define section
#if defined (STM32F030x6)   ||  \
    defined (STM32F030xC)   ||  \
    defined (STM32F072xB)
#define __TOMMROC_TEMPLATE_ARM_STM32_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32Fx_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32F0_IS_USED__
#endif

#if defined (STM32F103xB)
#define __TOMMROC_TEMPLATE_ARM_STM32_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32Fx_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32F1_IS_USED__
#endif

#if defined (STM32F429xx)
#define __TOMMROC_TEMPLATE_ARM_STM32_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32Fx_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32F4_IS_USED__
#endif

#if defined (STM32G071xx)
#define __TOMMROC_TEMPLATE_ARM_STM32_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32Gx_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32G0_IS_USED__
#endif

#if defined (STM32G491xx)
#define __TOMMROC_TEMPLATE_ARM_STM32_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32Gx_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32G4_IS_USED__
#endif

#if defined (STM32L011xx)   ||  \
    defined (STM32L071xx)   ||  \
    defined (STM32L072xx)
#define __TOMMROC_TEMPLATE_ARM_STM32_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32Lx_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32L0_IS_USED__
#endif

#if defined (STM32L471xx)   ||  \
    defined (STM32L4S5xx)   ||  \
    defined (STM32L4R9xx)
#define __TOMMROC_TEMPLATE_ARM_STM32_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32Lx_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32L4_IS_USED__
#endif

#if defined(STM32U356xx)    ||  \
    defined(STM32U366xx)    ||  \
    defined(STM32U385xx)    ||  \
    defined(STM32U375xx)    ||  \
    defined(STM32U3B5xx)    ||  \
    defined(STM32U3C5xx)
#define __TOMMROC_TEMPLATE_ARM_STM32_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32U3_IS_USED__
#endif

#if defined(STM32U575xx)    ||  \
    defined(STM32U585xx)    ||  \
    defined(STM32U595xx)    ||  \
    defined(STM32U599xx)    ||  \
    defined(STM32U5A5xx)    ||  \
    defined(STM32U5A9xx)
#define __TOMMROC_TEMPLATE_ARM_STM32_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32U5_IS_USED__
#endif

#if defined (STM32WB55xx)   ||  \
    defined (STM32WB5Mxx)
#define __TOMMROC_TEMPLATE_ARM_STM32_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32WB_IS_USED__
#endif

#if defined(STM32WBA50xx) ||    \
    defined(STM32WBA52xx) ||    \
    defined(STM32WBA54xx) ||    \
    defined(STM32WBA55xx) ||    \
    defined(STM32WBA5Mxx) ||    \
    defined(STM32WBA62xx) ||    \
    defined(STM32WBA63xx) ||    \
    defined(STM32WBA64xx) ||    \
    defined(STM32WBA65xx) ||    \
    defined(STM32WBA6Mxx)
#define __TOMMROC_TEMPLATE_ARM_STM32_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_STM32WBA_IS_USED__
#endif


#if defined (__TOMMROC_TEMPLATE_ARM_STM32_IS_USED__)
#define TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE  (3 * TOMMROC_UTIL_U32_SIZE)
#endif


// STM32 platform include section
#if defined (__TOMMROC_TEMPLATE_ARM_STM32F0_IS_USED__)
#include "stm32f0xx.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_STM32F1_IS_USED__)
#include "stm32f1xx.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_STM32F4_IS_USED__)
#include "stm32f4xx.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_STM32G0_IS_USED__)
#include "stm32g0xx.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_STM32G4_IS_USED__)
#include "stm32g4xx.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_STM32L0_IS_USED__)
#include "stm32l0xx.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_STM32L4_IS_USED__)
#include "stm32l4xx.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_STM32U3_IS_USED__)
#include "stm32u3xx.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_STM32U5_IS_USED__)
#include "stm32u5xx.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_STM32WB_IS_USED__)
#include "stm32wbxx.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_STM32WBA_IS_USED__)
#include "stm32wbaxx.h"
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif

#endif
