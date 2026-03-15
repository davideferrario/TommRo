
#ifndef TOMMROC_HW_DEVICES_DISPLAY_E_INK_DEF_H_
#define TOMMROC_HW_DEVICES_DISPLAY_E_INK_DEF_H_

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

// Device data.
#define TOMMROC_HW_DEVICES_DISPLAY_EINK_DEF_DEVICE_DATA_SIZE    (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                    TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                    TOMMROC_UTIL_U16_SIZE       +   \
                                                                    TOMMROC_UTIL_U16_SIZE       +   \
                                                                    TOMMROC_UTIL_U8_SIZE            )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_DISPLAY_EINK_DEF_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_display_e_ink_def_device_data_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
