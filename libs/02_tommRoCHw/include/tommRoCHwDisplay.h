
#ifndef TOMMROC_HW_DISPLAY_H_
#define TOMMROC_HW_DISPLAY_H_

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

// Enumeration of tommRoC hardware display properties.
typedef enum {

    /**
     * Available columns amount.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be uint16_t*
     */
    TOMMRO_C_HW_DISPLAY_COLUMNS_AMOUNT_PROP = 0,

    /**
     * Available rows amount.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be uint16_t*
     */
    TOMMRO_C_HW_DISPLAY_ROWS_AMOUNT_PROP,

} tommRoC_hw_display_prop_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
