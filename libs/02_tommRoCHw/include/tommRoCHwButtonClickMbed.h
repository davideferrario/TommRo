
#ifndef TOMMROC_HW_BUTTON_CLICK_MBED_H_
#define TOMMROC_HW_BUTTON_CLICK_MBED_H_

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
#include "tommRoCHwButtonClick.h"
#include "tommRoCHwErr.h"

#include <stdbool.h>

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
 * Init Mbed button click framework.
 * Mbed button click framework is a layer build over tommRoCHwButtonClick to be used when only one button click is needed by application.
 * The button click handler is hide to application by this layer.
 *
 * param[in/out]    buttonClickHandlePtr    button click handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwButtonClickMbedInit(tommRoC_hw_button_click_t* const buttonClickHandlePtr);

/**
 * Close Mbed button click framework.
 * The internal button click framework is resetted to initial value.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwButtonClickMbedClose(void);

/**
 * Get Mbed button click framework init status.
 *
 * return bool
 */
bool tommRoCHwButtonClickMbedIsInit(void);


/**
 * Check for Mbed button click events.
 *
 * return tommRoC_hw_button_click_event_enum_t
 */
tommRoC_hw_button_click_event_enum_t tommRoCHwButtonClickMbedCheck(void);

/**
 * Get if a possible sequence of Mbed button click is in progress.
 *
 * param[out]       isInProgressPtr         button click possible sequence pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwButtonClickMbedIsInProgress(bool* const isInProgressPtr);

#endif
