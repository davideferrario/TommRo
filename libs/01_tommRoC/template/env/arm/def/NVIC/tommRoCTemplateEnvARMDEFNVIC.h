
#ifndef TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_H_
#define TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_H_

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

// Atmel SAM section
#if defined (__TOMMROC_TEMPLATE_ARM_ATMEL_SAM_IS_USED__)
#include "sam.h"
#endif

// GD32 section
#if defined (__TOMMROC_TEMPLATE_ARM_GD32_IS_USED__)
#endif

// Nordic section
#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)
#include "nrfx.h"
#endif

// SiLabs section
#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)
#include "em_device.h"
#endif

// NXP section
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)
#include "fsl_common.h"
#endif

// STM32 section
#if defined (__TOMMROC_TEMPLATE_ARM_STM32_IS_USED__)
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

#define TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_ICER_SIZE_EAMOUNT (sizeof(((NVIC_Type*)NULL)->ICER) / sizeof(((NVIC_Type*)NULL)->ICER[0]))
#define TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_ICER_SIZE_BYTE    (TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_ICER_SIZE_EAMOUNT * TOMMROC_UTIL_U32_SIZE)

#if (__CORTEX_M == 0U)
TOMMROC_SCTA_EQUALS(TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_ICER_SIZE_EAMOUNT,    1);
TOMMROC_SCTA_EQUALS(TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_ICER_SIZE_BYTE,       4);

#elif (__CORTEX_M == 3U)
TOMMROC_SCTA_EQUALS(TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_ICER_SIZE_EAMOUNT,    8);
TOMMROC_SCTA_EQUALS(TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_ICER_SIZE_BYTE,       32);

#elif (__CORTEX_M == 4U)
TOMMROC_SCTA_EQUALS(TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_ICER_SIZE_EAMOUNT,    8);
TOMMROC_SCTA_EQUALS(TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_ICER_SIZE_BYTE,       32);

#elif (__CORTEX_M == 33U)
TOMMROC_SCTA_EQUALS(TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_ICER_SIZE_EAMOUNT,    16);
TOMMROC_SCTA_EQUALS(TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_ICER_SIZE_BYTE,       64);

#else
#error "ARM Cortex family not compatible"
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif

#endif
