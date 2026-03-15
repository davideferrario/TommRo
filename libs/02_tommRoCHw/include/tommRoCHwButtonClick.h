
#ifndef TOMMROC_HW_BUTTON_CLICK_H_
#define TOMMROC_HW_BUTTON_CLICK_H_

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

#include <stdbool.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

#define TOMMROC_HW_BUTTON_CLICK_HANDLE_SIZE (   TOMMROC_UTIL_U32_SIZE       +   \
                                                TOMMROC_UTIL_U32_SIZE       +   \
                                                TOMMROC_UTIL_U32_SIZE       +   \
                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                TOMMROC_UTIL_U8_SIZE        +   \
                                                TOMMROC_UTIL_U32_SIZE       +   \
                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                TOMMROC_UTIL_FUNCT_PTR_SIZE     )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC hardware button click events.
typedef enum {

    /**
     * No event.
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_NONE = 0,

    /**
     * Single short click event.
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_SHORT_CLICK,

    /**
     * Single long click event.
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_LONG_CLICK,

    /**
     * Double (short) click event.
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_DOUBLE_CLICK,

    /**
     * 3 (short) click event.
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_3_CLICK,

    /**
     * 4 (short) click event.
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_4_CLICK,

    /**
     * 5 (short) click event.
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_5_CLICK,

    /**
     * 6 (short) click event.
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_6_CLICK,

    /**
     * 7 (short) click event.
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_7_CLICK,

    /**
     * 8 (short) click event.
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_8_CLICK,

    /**
     * 9 (short) click event.
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_9_CLICK,

    /**
     * 10 (short) click event.
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_10_CLICK,

} tommRoC_hw_button_click_event_enum_t;


// Enumeration of tommRoC hardware button click properties.
typedef enum {

    /**
     * On enter single short click event callback function.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_hw_button_click_on_enter_event_funct_t
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_NONE_ON_ENTER_CB_PROP = 0,

    /**
     * On enter single short click event callback function.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_hw_button_click_on_enter_event_funct_t
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_SHORT_CLICK_ON_ENTER_CB_PROP,

    /**
     * On enter single long click event callback function.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_hw_button_click_on_enter_event_funct_t
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_LONG_CLICK_ON_ENTER_CB_PROP,

    /**
     * On enter double (short) click event callback function.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_hw_button_click_on_enter_event_funct_t
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_DOUBLE_CLICK_ON_ENTER_CB_PROP,

    /**
     * On enter 3 (short) click event callback function.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_hw_button_click_on_enter_event_funct_t
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_3_CLICK_ON_ENTER_CB_PROP,

    /**
     * On enter 4 (short) click event callback function.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_hw_button_click_on_enter_event_funct_t
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_4_CLICK_ON_ENTER_CB_PROP,

    /**
     * On enter 5 (short) click event callback function.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_hw_button_click_on_enter_event_funct_t
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_5_CLICK_ON_ENTER_CB_PROP,

    /**
     * On enter 6 (short) click event callback function.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_hw_button_click_on_enter_event_funct_t
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_6_CLICK_ON_ENTER_CB_PROP,

    /**
     * On enter 7 (short) click event callback function.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_hw_button_click_on_enter_event_funct_t
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_7_CLICK_ON_ENTER_CB_PROP,

    /**
     * On enter 8 (short) click event callback function.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_hw_button_click_on_enter_event_funct_t
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_8_CLICK_ON_ENTER_CB_PROP,

    /**
     * On enter 9 (short) click event callback function.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_hw_button_click_on_enter_event_funct_t
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_9_CLICK_ON_ENTER_CB_PROP,

    /**
     * On enter 10 (short) click event callback function.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_hw_button_click_on_enter_event_funct_t
     */
    TOMMROC_HW_BUTTON_CLICK_EVENT_10_CLICK_ON_ENTER_CB_PROP,

} tommRoC_hw_button_click_prop_enum_t;


// Get button pressed status function type.
typedef bool (*tommRoC_hw_button_click_is_button_pressed_funct_t)(void);

// On enter event function type.
typedef void (*tommRoC_hw_button_click_on_enter_event_funct_t)(void);

// tommRoC hardware button configuration structure.
typedef struct {

    /**
     *          <High Pulse>
     *          ------------                           ------------
     *          |          |                           |          |
     *          |          |                           |          |
     *          |          |                           |          |
     * ---------|          |---------------------------|          |----------
     *                     <         Low Pulse         >
     */

    uint32_t eventHighPulseMsec;
    uint32_t eventLowPulseMsec;
    uint32_t eventLongPulseMsec;

    tommRoC_hw_button_click_is_button_pressed_funct_t isButtonPressedFunct;

    tommRoC_util_enabled_status_enum_t longClickEnabled;
    tommRoC_util_enabled_status_enum_t multiClickEnabled;

} tommRoC_hw_button_click_config_t;

#define __EMPTY_tommRoC_hw_button_click_config_t__      \
{                                                       \
    /* .eventHighPulseMsec */   0,                      \
    /* .eventLowPulseMsec */    0,                      \
    /* .eventLongPulseMsec */   0,                      \
    /* .isButtonPressedFunct */ NULL,                   \
    /* .longClickEnabled */     TOMMRO_C_UTIL_ENABLED,  \
    /* .multiClickEnabled */    TOMMRO_C_UTIL_ENABLED,  \
}

// tommRoC hardware button click struct.
typedef struct {
    uint8_t data[TOMMROC_HW_BUTTON_CLICK_HANDLE_SIZE];
} tommRoC_hw_button_click_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init button click handler.
 *
 * param[in]        configPtr               button click config pointer.
 * param[out]       buttonClickHandlePtr    button click handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwButtonClickInit(
        const   tommRoC_hw_button_click_config_t*   const   configPtr,
                tommRoC_hw_button_click_t*          const   buttonClickHandlePtr);

/**
 * Set button click property.
 *
 * param[in]        property                property.
 * param[in]        propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwButtonClickSetProp(
        const   tommRoC_hw_button_click_prop_enum_t         property,
        const   void*                               const   propValuePtr,
                tommRoC_hw_button_click_t*          const   buttonClickHandlePtr);

/**
 * Check for button click events.
 *
 * param[in/out]    buttonClickHandlePtr    button click handle pointer.
 *
 * return tommRoC_hw_button_click_event_enum_t
 */
tommRoC_hw_button_click_event_enum_t tommRoCHwButtonClickCheck(
                tommRoC_hw_button_click_t*          const   buttonClickHandlePtr);

/**
 * Get if a possible sequence of button click is in progress.
 *
 * param[in]        buttonClickHandlePtr    button click handle pointer.
 * param[out]       isInProgressPtr         button click possible sequence pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwButtonClickIsInProgress(
        const   tommRoC_hw_button_click_t*          const   buttonClickHandlePtr,
                bool*                               const   isInProgressPtr);

#endif
