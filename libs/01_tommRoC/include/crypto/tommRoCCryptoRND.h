
#ifndef TOMMROC_CRYPTO_RND_H_
#define TOMMROC_CRYPTO_RND_H_

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
 * @defgroup tommRoCCryptoRND tommRoCCryptoRND
 *
 * @brief  TommRoC library crypto random module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted crypto random functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC crypto random properties enumeration.
typedef enum {

    /**
     * Random environment guard.
     * This have to be used for simultaneous access on random hardware and/or if
     * simultaneous access is not supported by software level.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_guard_t*.
     */
    TOMMRO_C_CRYPTO_RND_GUARD_PROP = 0,

    /**
     * Random environment is init.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_RND_IS_INIT_PROP,

} tommRoC_crypto_rnd_prop_enum_t;

/**
 * Random retrive function type.
 */
typedef tommRoC_err_enum_t (*tommRoC_crypto_rnd_retrive_funct_t)(
                uint8_t*    const   bufferPtr,
        const   uint32_t            outputLen);

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* Random environment init functs */

/**
 * Crypto random environment init.
 *
 * param[in]        rnd                     retrive random function.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoRNDInitEnv(const tommRoC_crypto_rnd_retrive_funct_t rnd);


/******************* Random environment close functs */

/**
 * Crypto random environment close.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoRNDCloseEnv(void);


/******************* Random environment get/set properties functs */

/**
 * Get crypto random property.
 *
 * param[in]        property                    property.
 * param[out]       propValuePtr                value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoRNDGetProp(
        const   tommRoC_crypto_rnd_prop_enum_t          property,
                void*                           const   propValuePtr);

/**
 * Set crypto random property.
 *
 * param[in]        property                    property.
 * param[in]        propValuePtr                value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoRNDSetProp(
        const   tommRoC_crypto_rnd_prop_enum_t          property,
        const   void*                           const   propValuePtr);


/******************* Random environment functs */

/**
 * Retrive random generated random data.
 *
 * param[out]       bufferPtr               output random data buffer.
 * param[in]        outputLen               length of output data buffer to retrieve.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoRNDRetrive(
                uint8_t*    const   bufferPtr,
        const   uint32_t            outputLen);

/**
 * @}
 */

#endif
