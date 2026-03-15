
#ifndef TOMMROC_CRYPTO_ENTROPY_H_
#define TOMMROC_CRYPTO_ENTROPY_H_

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
 * @defgroup tommRoCCryptoEntropy tommRoCCryptoEntropy
 *
 * @brief  TommRoC library crypto entropy module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted crypto entropy functionality.
 *
 * Entropy is the randomness collected by an application for use in cryptography.
 * This randomness is often collected from hardware sources,
 * either pre-existing ones or specially provided randomness generators.
 * A lack of entropy can have a negative impact on performance and security.
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

// tommRoC crypto entropy properties enumeration.
typedef enum {

    /**
     * Entropy environment guard.
     * This have to be used for simultaneous access on entropy hardware and/or if
     * simultaneous access is not supported by software level.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_guard_t*.
     */
    TOMMRO_C_CRYPTO_ENTROPY_GUARD_PROP = 0,

    /**
     * Entropy environment is init.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_ENTROPY_IS_INIT_PROP,

} tommRoC_crypto_entropy_prop_enum_t;

/**
 * Retrive entropy function type.
 */
typedef tommRoC_err_enum_t (*tommRoC_crypto_entropy_retrive_funct_t)(
                uint8_t*    const   bufferPtr,
        const   uint32_t            outputLen);

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* Entropy environment init functs */

/**
 * Entropy environment init.
 *
 * param[in]        entropy                 retrive entropy function.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoEntropyInitEnv(const tommRoC_crypto_entropy_retrive_funct_t entropy);


/******************* Entropy environment close functs */

/**
 * Entropy environment close.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoEntropyCloseEnv(void);


/******************* Entropy environment get/set properties functs */

/**
 * Get crypto entropy property.
 *
 * param[in]        property                    property.
 * param[out]       propValuePtr                value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoEntropyGetProp(
        const   tommRoC_crypto_entropy_prop_enum_t          property,
                void*                               const   propValuePtr);

/**
 * Set crypto entropy property.
 *
 * param[in]        property                    property.
 * param[in]        propValuePtr                value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoEntropySetProp(
        const   tommRoC_crypto_entropy_prop_enum_t          property,
        const   void*                               const   propValuePtr);


/******************* Entropy environment functs */

/**
 * Retrieve entropy data.
 *
 * param[out]       bufferPtr               output entropy data buffer.
 * param[in]        outputLen               length of entropy data buffer to retrieve.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoEntropyRetrive(
                uint8_t*    const   bufferPtr,
        const   uint32_t            outputLen);

/**
 * @}
 */

#endif
