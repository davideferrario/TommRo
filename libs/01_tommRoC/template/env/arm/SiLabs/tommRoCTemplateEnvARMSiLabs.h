
#ifndef TOMMROC_TEMPLATE_ENV_ARM_SILABS_H_
#define TOMMROC_TEMPLATE_ENV_ARM_SILABS_H_

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

// EFM32G Section
#if defined (EFM32G200F16)          ||  \
    defined (EFM32G200F32)          ||  \
    defined (EFM32G200F64)          ||  \
    defined (EFM32G210F128)         ||  \
    defined (EFM32G222F128)         ||  \
    defined (EFM32G222F32)          ||  \
    defined (EFM32G222F64)          ||  \
    defined (EFM32G230F128)         ||  \
    defined (EFM32G230F32)          ||  \
    defined (EFM32G230F64)          ||  \
    defined (EFM32G232F128)         ||  \
    defined (EFM32G232F32)          ||  \
    defined (EFM32G232F64)          ||  \
    defined (EFM32G280F128)         ||  \
    defined (EFM32G280F32)          ||  \
    defined (EFM32G280F64)          ||  \
    defined (EFM32G290F128)         ||  \
    defined (EFM32G290F32)          ||  \
    defined (EFM32G290F64)          ||  \
    defined (EFM32G800F128)         ||  \
    defined (EFM32G840F128)         ||  \
    defined (EFM32G840F32)          ||  \
    defined (EFM32G840F64)          ||  \
    defined (EFM32G842F128)         ||  \
    defined (EFM32G842F32)          ||  \
    defined (EFM32G842F64)          ||  \
    defined (EFM32G880F128)         ||  \
    defined (EFM32G880F32)          ||  \
    defined (EFM32G880F64)          ||  \
    defined (EFM32G890F128)         ||  \
    defined (EFM32G890F32)          ||  \
    defined (EFM32G890F64)

#define __TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_EFM32_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_EFM32_EFM32G_IS_USED__
#endif

// EFM32GG Section
#if defined (EFM32GG230F1024)       ||  \
    defined (EFM32GG230F512)        ||  \
    defined (EFM32GG232F1024)       ||  \
    defined (EFM32GG232F512)        ||  \
    defined (EFM32GG280F1024)       ||  \
    defined (EFM32GG280F512)        ||  \
    defined (EFM32GG290F1024)       ||  \
    defined (EFM32GG290F512)        ||  \
    defined (EFM32GG295F1024)       ||  \
    defined (EFM32GG295F512)        ||  \
    defined (EFM32GG330F1024)       ||  \
    defined (EFM32GG330F512)        ||  \
    defined (EFM32GG332F1024)       ||  \
    defined (EFM32GG332F512)        ||  \
    defined (EFM32GG380F1024)       ||  \
    defined (EFM32GG380F512)        ||  \
    defined (EFM32GG390F1024)       ||  \
    defined (EFM32GG390F512)        ||  \
    defined (EFM32GG395F1024)       ||  \
    defined (EFM32GG395F512)        ||  \
    defined (EFM32GG840F1024)       ||  \
    defined (EFM32GG840F512)        ||  \
    defined (EFM32GG842F1024)       ||  \
    defined (EFM32GG842F512)        ||  \
    defined (EFM32GG880F1024)       ||  \
    defined (EFM32GG880F512)        ||  \
    defined (EFM32GG890F1024)       ||  \
    defined (EFM32GG890F512)        ||  \
    defined (EFM32GG895F1024)       ||  \
    defined (EFM32GG895F512)        ||  \
    defined (EFM32GG900F1024)       ||  \
    defined (EFM32GG900F512)        ||  \
    defined (EFM32GG940F1024)       ||  \
    defined (EFM32GG940F512)        ||  \
    defined (EFM32GG942F1024)       ||  \
    defined (EFM32GG942F512)        ||  \
    defined (EFM32GG980F1024)       ||  \
    defined (EFM32GG980F512)        ||  \
    defined (EFM32GG990F1024)       ||  \
    defined (EFM32GG990F512)        ||  \
    defined (EFM32GG995F1024)       ||  \
    defined (EFM32GG995F512)

#define __TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_EFM32_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_EFM32_EFM32GG_IS_USED__
#endif

// MGM21 Section
#if defined (MGM210L022JIF)         ||  \
    defined (MGM210L022JNF)         ||  \
    defined (MGM210LA22JIF)         ||  \
    defined (MGM210LA22JNF)         ||  \
    defined (MGM210P022JIA)         ||  \
    defined (MGM210P022JNA)         ||  \
    defined (MGM210P032JIA)         ||  \
    defined (MGM210P032JNA)         ||  \
    defined (MGM210PA22JIA)         ||  \
    defined (MGM210PA22JNA)         ||  \
    defined (MGM210PA32JIA)         ||  \
    defined (MGM210PA32JNA)

#define __TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_EFR32_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_MGM21_IS_USED__
#endif


#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_IS_USED__) || defined (__TOMMROC_TEMPLATE_ARM_EFR32_IS_USED__)
#define TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE  (2 * TOMMROC_UTIL_U32_SIZE)
#endif


// SiLabs platform include section
#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)
#include "em_cmu.h"
#include "em_device.h"
#include "em_emu.h"
#include "em_system.h"
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif

#endif
