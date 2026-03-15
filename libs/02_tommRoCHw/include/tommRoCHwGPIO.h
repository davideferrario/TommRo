
#ifndef TOMMROC_HW_GPIO_H_
#define TOMMROC_HW_GPIO_H_

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
#include "tommRoCHwErr.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * GPIO common hardware functionality.
 */
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_gpio_common_cb_t)(const void* const);

/**
 * GPIO set direction (input or output) type.
 */
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_gpio_set_dir_cb_t)(void);

/**
 * GPIO set status (low, high, toggle) type.
 */
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_gpio_set_cb_t)(void);

/**
 * GPIO get status (low or high) type.
 */
typedef tommRoC_util_bit_status_enum_t (*tommRoC_hw_gpio_get_cb_t)(void);

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
