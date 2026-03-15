
#ifndef TOMMROC_HW_DEVICES_DISPLAY_UCGLIB_DEF_H_
#define TOMMROC_HW_DEVICES_DISPLAY_UCGLIB_DEF_H_

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
#define TOMMROC_HW_DEVICES_DISPLAY_UCGLIB_DEF_HANDLE_SIZE   ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMROC_HW_DEVICES_DISPLAY_UCGLIB_DEF_HANDLE_SIZE   ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE)
#define TOMMROC_HW_DEVICES_DISPLAY_UCGLIB_DEF_HANDLE_SIZE   (184)
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMROC_HW_DEVICES_DISPLAY_UCGLIB_DEF_HANDLE_SIZE   (240)
#endif

#define TOMMROC_HW_DEVICES_DISPLAY_UCGLIB_DEF_DEVICE_DATA_SIZE  (   TOMMROC_HW_DEVICES_DISPLAY_UCGLIB_DEF_HANDLE_SIZE   +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE                         +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE                         +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE                         +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE                         +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE                         +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE                         +   \
                                                                    TOMMROC_UTIL_PTR_SIZE                               +   \
                                                                    TOMMROC_UTIL_PTR_SIZE                                   )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC hardware devices display UCGLib color type.
typedef enum {

    /**
     * Foreground color.
     */
    TOMMROC_HW_DEVICES_DISPLAY_UCGLIB_DEF_COLOR_TYPE_FOREGROUND = 0,

    /**
     * Background color.
     */
    TOMMROC_HW_DEVICES_DISPLAY_UCGLIB_DEF_COLOR_TYPE_BACKGROUND,

} tommRoC_hw_devices_display_ucglib_def_color_type_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
