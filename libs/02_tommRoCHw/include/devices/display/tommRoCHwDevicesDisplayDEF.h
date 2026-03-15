
#ifndef TOMMROC_HW_DEVICES_DISPLAY_DEF_H_
#define TOMMROC_HW_DEVICES_DISPLAY_DEF_H_

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

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC hardware devices display placement.
typedef enum {

    /**
     * Display is placed to be used as vertical.
     */
    TOMMROC_HW_DEVICES_DISPLAY_DEF_ORIENTATION_VERTICAL = 0,

    /**
     * Display is placed to be used as horizontal.
     */
    TOMMROC_HW_DEVICES_DISPLAY_DEF_ORIENTATION_HORIZONTAL,


    /**
     * Display is placed to be used as vertical 180° rotated.
     */
    TOMMROC_HW_DEVICES_DISPLAY_DEF_ORIENTATION_VERTICAL_180_ROTATED,


    /**
     * Display is placed to be used as horizontal 180° rotated.
     */
    TOMMROC_HW_DEVICES_DISPLAY_DEF_ORIENTATION_HORIZONTAL_180_ROTATED,

} tommRoC_hw_devices_display_def_orientation_enum_t;


// Enumeration of tommRoC hardware devices display color.
typedef enum {

    /**
     * Frame is print as original color.
     */
    TOMMROC_HW_DEVICES_DISPLAY_DEF_COLOR_TYPE_ORIGINAL = 0,

    /**
     * Frame is print as inverted color.
     */
    TOMMROC_HW_DEVICES_DISPLAY_DEF_COLOR_TYPE_INVERTED,

} tommRoC_hw_devices_display_def_color_type_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
