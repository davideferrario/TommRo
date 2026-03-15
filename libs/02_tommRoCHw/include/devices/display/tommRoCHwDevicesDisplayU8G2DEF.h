
#ifndef TOMMROC_HW_DEVICES_DISPLAY_U8G2_DEF_H_
#define TOMMROC_HW_DEVICES_DISPLAY_U8G2_DEF_H_

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

#if defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_8_BIT_SIZE)
#define TOMMROC_HW_DEVICES_DISPLAY_U8G2_DEF_HANDLE_SIZE ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMROC_HW_DEVICES_DISPLAY_U8G2_DEF_HANDLE_SIZE ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE)
#define TOMMROC_HW_DEVICES_DISPLAY_U8G2_DEF_HANDLE_SIZE (152)
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMROC_HW_DEVICES_DISPLAY_U8G2_DEF_HANDLE_SIZE (216)
#endif

#define TOMMROC_HW_DEVICES_DISPLAY_U8G2_DEF_DEVICE_DATA_SIZE    (   TOMMROC_HW_DEVICES_DISPLAY_U8G2_DEF_HANDLE_SIZE +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE                     +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE                     +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE                     +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE                     +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE                     +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE                     +   \
                                                                    TOMMROC_UTIL_PTR_SIZE                           +   \
                                                                    TOMMROC_UTIL_PTR_SIZE                               )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Display rotation
typedef enum {

    TOMMROC_HW_DEVICES_DISPLAY_U8G2_DEF_DISPLAY_ROTATION_LANDSCAPE = 0,         // No rotation
    TOMMROC_HW_DEVICES_DISPLAY_U8G2_DEF_DISPLAY_ROTATION_90_DEGREE_CLOCKWISE,   // 90 degree clockwise rotation
    TOMMROC_HW_DEVICES_DISPLAY_U8G2_DEF_DISPLAY_ROTATION_180_DEGREE_CLOCKWISE,  // 180 degree clockwise rotation
    TOMMROC_HW_DEVICES_DISPLAY_U8G2_DEF_DISPLAY_ROTATION_270_DEGREE_CLOCKWISE,  // 270 degree clockwise rotation
    TOMMROC_HW_DEVICES_DISPLAY_U8G2_DEF_DISPLAY_ROTATION_MIRROR,                // Horizontal mirrored
    TOMMROC_HW_DEVICES_DISPLAY_U8G2_DEF_DISPLAY_ROTATION_MIRROR_VERTICAL,       // Vertical mirrored

} tommRoC_hw_devices_display_u8g2_def_display_rotation_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
