
#ifndef TOMMROC_HW_COLOR_H_
#define TOMMROC_HW_COLOR_H_

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

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// RGB 8 bit color structure.
typedef struct {

    /**
     * Red color component.
     */
    uint8_t r;

    /**
     * Green color component.
     */
    uint8_t g;

    /**
     * Blue color component.
     */
    uint8_t b;

} tommRoC_hw_color_rgb_8bit_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init a RGB 8 bit color structure.
 *
 * param[in]        r                       Red color component.
 * param[in]        g                       Green color component.
 * param[in]        b                       Blue color component.
 * param[out]       colorPtr                RGB 8 bit color structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwColorRGB8BitInit(
        const   uint8_t                                 r,
        const   uint8_t                                 g,
        const   uint8_t                                 b,
                tommRoC_hw_color_rgb_8bit_t*    const   colorPtr);

#endif
