
#ifndef TOMMROC_TEMPLATE_ENV_ARM_NORDIC_H_
#define TOMMROC_TEMPLATE_ENV_ARM_NORDIC_H_

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

// NRF51 Section
#if defined (NRF51422_XXAA)         ||  \
    defined (NRF51422_XXAB)         ||  \
    defined (NRF51422_XXAC)         ||  \
    defined (NRF51801_XXAB)         ||  \
    defined (NRF51802_XXAA)         ||  \
    defined (NRF51822_XXAA)         ||  \
    defined (NRF51822_XXAB)         ||  \
    defined (NRF51822_XXAC)         ||  \
    defined (NRF51824_XXAA)

#define __TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_NRF51_IS_USED__
#endif

// NRF52 Section
#if defined (NRF52805_XXAA)         ||  \
    defined (NRF52810_XXAA)         ||  \
    defined (NRF52811_XXAA)         ||  \
    defined (NRF52832_XXAA)         ||  \
    defined (NRF52832_XXAB)         ||  \
    defined (NRF52833_XXAA)         ||  \
    defined (NRF52840_XXAA)

#define __TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_NRF52_IS_USED__
#endif

// NRF91 Section
#if defined (NRF9160_XXAA)

#define __TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__
#define __TOMMROC_TEMPLATE_ARM_NRF91_IS_USED__
#endif


// Nordic platform include section
#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)
#include "nrf_drv_clock.h"
#include "nrfx.h"
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif

#endif
