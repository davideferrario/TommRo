
#ifndef TOMMROC_SW_CTR_DRBG_H_
#define TOMMROC_SW_CTR_DRBG_H_

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
 * CTR DRBG (Counter mode Deterministic Random Byte Generator) is based on AES-256, as defined in:
 * NIST SP 800-90A - Recommendation for Random Number Generation Using Deterministic Random Bit Generators.
 */
 
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwErr.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Start CTR DRBG software framework.
 *
 * return tommRoC_sw_err_enum_t
 */
tommRoC_sw_err_enum_t tommRoCSwCtrDrbgStart(void);

/**
 * Stop CTR DRBG software framework.
 *
 * return tommRoC_sw_err_enum_t
 */
tommRoC_sw_err_enum_t tommRoCSwCtrDrbgStop(void);

/**
 * Seeds and sets up the CTR DRBG entropy source for future reseeds.
 * NOTE: have to be called after CTR DRBG Start.
 *
 * param[in]        personalDataPtr         CTR DRBG personalization data (can be NULL).
 * param[in]        personalDataLen         CTR DRBG personalization data length.
 *
 * return tommRoC_sw_err_enum_t
 */
tommRoC_sw_err_enum_t tommRoCSwCtrDrbgSeed(
        const   uint8_t*    const   personalDataPtr,
        const   uint8_t             personalDataLen);

#endif
