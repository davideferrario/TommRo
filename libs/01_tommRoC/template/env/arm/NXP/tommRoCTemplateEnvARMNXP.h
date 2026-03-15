
#ifndef TOMMROC_TEMPLATE_ENV_ARM_NXP_H_
#define TOMMROC_TEMPLATE_ENV_ARM_NXP_H_

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

// NXP MK22 Section
#if defined (CPU_MK22FN512CAP12)    ||  \
    defined (CPU_MK22FN512VDC12)    ||  \
    defined (CPU_MK22FN512VFX12)    ||  \
    defined (CPU_MK22FN512VLH12)    ||  \
    defined (CPU_MK22FN512VLL12)    ||  \
    defined (CPU_MK22FN512VMP12)    ||  \
                                        \
    defined (CPU_MK22FX512VLH12)    ||  \
    defined (CPU_MK22FX512VLK12)    ||  \
    defined (CPU_MK22FX512VLL12)    ||  \
    defined (CPU_MK22FX512VLQ12)    ||  \
    defined (CPU_MK22FX512VMC12)    ||  \
    defined (CPU_MK22FX512VMD12)

#define __TOMMROC_TEMPLATE_ARM_NXP_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__
#endif

// NXP MKW21Z Section
#if defined (CPU_MKW21Z256VHT4)     ||  \
    defined (CPU_MKW21Z512VHT4)

#define __TOMMROC_TEMPLATE_ARM_NXP_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_NXP_MKW21Z_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__
#endif

// NXP MKW31Z Section
#if defined (CPU_MKW31Z256CAx4)     ||  \
    defined (CPU_MKW31Z256VHT4)     ||  \
    defined (CPU_MKW31Z512CAx4)     ||  \
    defined (CPU_MKW31Z512VHT4)

#define __TOMMROC_TEMPLATE_ARM_NXP_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_NXP_MKW31Z_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__
#endif

// NXP MKW41Z Section
#if defined (CPU_MKW41Z256VHT4)     ||  \
    defined (CPU_MKW41Z512CAT4)     ||  \
    defined (CPU_MKW41Z512VHT4)

#define __TOMMROC_TEMPLATE_ARM_NXP_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_NXP_MKW41Z_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__
#endif

// NXP QN908XC Section
#if defined (CPU_QN9080C)           ||  \
    defined (CPU_QN9083C)

#define __TOMMROC_TEMPLATE_ARM_NXP_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__
#endif

// NXP MKE02Z4 Section
#if defined (CPU_MKE02Z16VFM4)      ||  \
    defined (CPU_MKE02Z16VLC4)      ||  \
    defined (CPU_MKE02Z16VLD4)      ||  \
    defined (CPU_MKE02Z32VFM4)      ||  \
    defined (CPU_MKE02Z32VLC4)      ||  \
    defined (CPU_MKE02Z32VLD4)      ||  \
    defined (CPU_MKE02Z32VLH4)      ||  \
    defined (CPU_MKE02Z32VQH4)      ||  \
    defined (CPU_MKE02Z64VFM4)      ||  \
    defined (CPU_MKE02Z64VLC4)      ||  \
    defined (CPU_MKE02Z64VLD4)      ||  \
    defined (CPU_MKE02Z64VLH4)      ||  \
    defined (CPU_MKE02Z64VQH4)

#define __TOMMROC_TEMPLATE_ARM_NXP_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__
#endif


#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__)
#define TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE  (sizeof(sim_uid_t))
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)
#define TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE  (sizeof(sim_uid_t))
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__)
#define TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE  (6)
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
#define TOMMROC_TEMPLATE_OS_UUID_SIZE_BYTE  (2 * TOMMROC_UTIL_U32_SIZE)
#endif


// NXP platform include section
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)
#include "fsl_common.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__)
#include "fsl_sim.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)
#include "fsl_sim.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__)
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif

#endif
