
#ifndef TOMMROC_SOFT_CALENDAR_H_
#define TOMMROC_SOFT_CALENDAR_H_

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
 * @defgroup tommRoCSoftCalendar tommRoCSoftCalendar
 *
 * @brief  TommRoC library software calendar module
 * @author TommRo Software Department
 *
 * This module is providing software calendar functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/
#define TOMMROC_SOFT_CALENDAR_MIN_VALID_YEAR    ((uint16_t) 1970)
#define TOMMROC_SOFT_CALENDAR_MAX_VALID_YEAR    ((uint16_t) 2105)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Set current software calendar from timestamp - seconds from UTC 00:00:00 01/01/1970.
 *
 * param[in]        timestamp               timestamp.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCSoftCalendarSetTimestamp(const uint32_t timestamp);

/**
 * Get current software calendar as timestamp - seconds from UTC 00:00:00 01/01/1970.
 *
 * param[out]       timestampPtr            timestamp pointer.
 *
 * return tommRoC_err_enum_t
 */
uint32_t tommRoCSoftCalendarGetTimestamp(void);

/**
 * Increment internal software calendar of some seconds.
 *
 * param[in]        value                   incremental value.
 *
 * return
 */
void tommRoCSoftCalendarIncSec(const uint32_t value);

/**
 * Increment internal software calendar of some milli seconds.
 *
 * param[in]        value                   incremental value.
 *
 * return
 */
void tommRoCSoftCalendarIncMSec(const uint32_t value);

/**
 * Increment internal calendar of some micro seconds.
 *
 * param[in]        value                   incremental value.
 *
 * return
 */
void tommRoCSoftCalendarIncUSec(const uint32_t value);

/**
 * @}
 */

#endif
