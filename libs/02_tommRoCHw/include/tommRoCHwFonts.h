
#ifndef TOMMROC_HW_FONTS_H_
#define TOMMROC_HW_FONTS_H_

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
#define TOMMROC_HW_FONTS_POUND_ASCII_CODE           (0xFE)
#define TOMMROC_HW_FONTS_EURO_ASCII_CODE            (0xFF)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC hardware fonts.
typedef enum {

    /**
     * Basic 8x8 font.
     */
    TOMMRO_C_HW_FONTS_BASIC_8x8 = 0,
    /**
     * Basic 16x16 font.
     */
    TOMMRO_C_HW_FONTS_BASIC_16x16,
    
    /**
     * Courier 8x8 font.
     */
    TOMMRO_C_HW_FONTS_COURIER_8x8,
    /**
     * Courier 16x16 font.
     */
    TOMMRO_C_HW_FONTS_COURIER_16x16,

    /**
     * Lightdot 8x8 font.
     */
    TOMMRO_C_HW_FONTS_LIGHTDOT_8x8,

} tommRoC_hw_fonts_enum_t;


// tommRoC hardware fonts single character.
typedef struct {

    const uint8_t*  dataPtr;        // Character data pointer.
    uint8_t         widthPixel;     // Character width [pixel]
    uint8_t         heightPixel;    // Character height [pixel]

} tommRoC_hw_fonts_char_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* Init/Close library fonts structure functions */

/**
 * Init library specific font [only numeric] structure.
 * NOTE: MUST be called before use specific font into application.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwFontsBasic8x8InitAsNumeric(void);
tommRoC_hw_err_enum_t tommRoCHwFontsBasic16x16InitAsNumeric(void);

tommRoC_hw_err_enum_t tommRoCHwFontsCourier8x8InitAsNumeric(void);
tommRoC_hw_err_enum_t tommRoCHwFontsCourier16x16InitAsNumeric(void);

tommRoC_hw_err_enum_t tommRoCHwFontsLightdot8x8InitAsNumeric(void);

/**
 * Init library specific font [numeric extended] structure.
 * NOTE: MUST be called before use specific font into application.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwFontsBasic8x8InitAsNumericExtended(void);
tommRoC_hw_err_enum_t tommRoCHwFontsBasic16x16InitAsNumericExtended(void);

tommRoC_hw_err_enum_t tommRoCHwFontsCourier8x8InitAsNumericExtended(void);
tommRoC_hw_err_enum_t tommRoCHwFontsCourier16x16InitAsNumericExtended(void);

tommRoC_hw_err_enum_t tommRoCHwFontsLightdot8x8InitAsNumericExtended(void);

/**
 * Init library specific font [only alphabetical] structure.
 * NOTE: MUST be called before use specific font into application.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwFontsBasic8x8InitAsAlphabetical(void);
tommRoC_hw_err_enum_t tommRoCHwFontsBasic16x16InitAsAlphabetical(void);

tommRoC_hw_err_enum_t tommRoCHwFontsCourier8x8InitAsAlphabetical(void);
tommRoC_hw_err_enum_t tommRoCHwFontsCourier16x16InitAsAlphabetical(void);

tommRoC_hw_err_enum_t tommRoCHwFontsLightdot8x8InitAsAlphabetical(void);

/**
 * Init library specific font [complete] structure.
 * NOTE: MUST be called before use specific font into application.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwFontsBasic8x8InitAsComplete(void);
tommRoC_hw_err_enum_t tommRoCHwFontsBasic16x16InitAsComplete(void);

tommRoC_hw_err_enum_t tommRoCHwFontsCourier8x8InitAsComplete(void);
tommRoC_hw_err_enum_t tommRoCHwFontsCourier16x16InitAsComplete(void);

tommRoC_hw_err_enum_t tommRoCHwFontsLightdot8x8InitAsComplete(void);


/**
 * Close library specific font structure.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwFontsBasic8x8Close(void);
tommRoC_hw_err_enum_t tommRoCHwFontsBasic16x16Close(void);

tommRoC_hw_err_enum_t tommRoCHwFontsCourier8x8Close(void);
tommRoC_hw_err_enum_t tommRoCHwFontsCourier16x16Close(void);

tommRoC_hw_err_enum_t tommRoCHwFontsLightdot8x8Close(void);

#endif
