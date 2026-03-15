
#ifndef TOMMROC_SW_TEMPLATE_RSA_H_
#define TOMMROC_SW_TEMPLATE_RSA_H_

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
 *  - Keys size:
 *      - __TOMMROC_SW_USE_RSA_512_BIT_TEMPLATE__               TommRoCSw software RSA 512 bit key size
 *      - __TOMMROC_SW_USE_RSA_1024_BIT_TEMPLATE__              TommRoCSw software RSA 1024 bit key size
 *      - __TOMMROC_SW_USE_RSA_2048_BIT_TEMPLATE__              TommRoCSw software RSA 2048 bit key size
 *      - __TOMMROC_SW_USE_RSA_4096_BIT_TEMPLATE__              TommRoCSw software RSA 4096 bit key size
 *
 *  - RSA functionality:
 *      - <none>                                                TommRoCSw software RSA minimum (GenKeypair/Encrypt/Decrypt)
 *      - __TOMMROC_SW_USE_RSA_MINIMUM_PLUS_VERIFY_TEMPLATE__   TommRoCSw software RSA minimum (GenKeypair/Encrypt/Decrypt) + verify
 *      - __TOMMROC_SW_USE_RSA_MINIMUM_PLUS_SIGN_TEMPLATE__     TommRoCSw software RSA minimum (GenKeypair/Encrypt/Decrypt) + sign
 *      - __TOMMROC_SW_USE_RSA_COMPLETE_TEMPLATE__              TommRoCSw software RSA complete (GenKeypair/Encrypt/Decrypt/Verify/Sign)
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
 
tommRoC_sw_err_enum_t tommRoCSwTemplateRSAStart(void);
tommRoC_sw_err_enum_t tommRoCSwTemplateRSAStop(void);

#endif
