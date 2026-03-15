
#ifndef TOMMROC_SW_TEMPLATE_SHA_H_
#define TOMMROC_SW_TEMPLATE_SHA_H_

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

/**
 *  - __TOMMROC_SW_USE_SHA1_TEMPLATE__      TommRoCSw software SHA1
 *  - __TOMMROC_SW_USE_SHA224_TEMPLATE__    TommRoCSw software SHA224
 *  - __TOMMROC_SW_USE_SHA256_TEMPLATE__    TommRoCSw software SHA256
 *  - __TOMMROC_SW_USE_SHA384_TEMPLATE__    TommRoCSw software SHA384
 *  - __TOMMROC_SW_USE_SHA512_TEMPLATE__    TommRoCSw software SHA512
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROCSw.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/
 
tommRoC_sw_err_enum_t tommRoCSwTemplateSHAStart(void);
tommRoC_sw_err_enum_t tommRoCSwTemplateSHAStop(void);

#endif
