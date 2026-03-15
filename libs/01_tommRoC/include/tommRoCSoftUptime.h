
#ifndef TOMMROC_SOFT_UPTIME_H_
#define TOMMROC_SOFT_UPTIME_H_

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
 * @defgroup tommRoCSoftUptime tommRoCSoftUptime
 *
 * @brief  TommRoC library software uptime module
 * @author TommRo Software Department
 *
 * This module is providing software uptime functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
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

/**
 * Get current internal milliseconds status.
 *
 * return uint32_t
 */
uint32_t tommRoCSoftUptimeGetMSec(void);

/**
 * Get current internal microseconds status.
 *
 * return uint32_t
 */
uint32_t tommRoCSoftUptimeGetUSec(void);

/**
 * Increment internal status of some milli seconds.
 *
 * param[in]        value                   incremental value.
 *
 * return
 */
void tommRoCSoftUptimeIncMSec(const uint32_t value);

/**
 * Increment internal status of some micro seconds.
 *
 * param[in]        value                   incremental value.
 *
 * return
 */
void tommRoCSoftUptimeIncUSec(const uint32_t value);

/**
 * @}
 */

#endif
