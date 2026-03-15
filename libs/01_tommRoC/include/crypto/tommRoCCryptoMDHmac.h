
#ifndef TOMMROC_CRYPTO_MD_HMAC_H_
#define TOMMROC_CRYPTO_MD_HMAC_H_

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
 * @defgroup tommRoCCryptoMDHmac tommRoCCryptoMDHmac
 *
 * @brief  TommRoC library crypto MD HMAC module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted crypto MD HMAC functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "crypto/tommRoCCryptoSHA.h"

#include "tommRoCErr.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/
#define TOMMROC_CRYPTO_MD_HMAC_SHA1_RESULT_SIZE_BYTE    (TOMMROC_CRYPTO_SHA1_RESULT_SIZE_BYTE)
#define TOMMROC_CRYPTO_MD_HMAC_SHA256_RESULT_SIZE_BYTE  (TOMMROC_CRYPTO_SHA256_RESULT_SIZE_BYTE)
#define TOMMROC_CRYPTO_MD_HMAC_SHA512_RESULT_SIZE_BYTE  (TOMMROC_CRYPTO_SHA512_RESULT_SIZE_BYTE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC crypto MD HMAC properties enumeration.
typedef enum {

    /**
     * MD HMAC environment guard.
     * This have to be used for simultaneous access on MD HMAC hardware and/or if
     * simultaneous access is not supported by software level.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_guard_t*.
     */
    TOMMRO_C_CRYPTO_MD_HMAC_GUARD_PROP = 0,

    /**
     * MD HMAC SHA1/SHA256/SHA512 environment is init.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_MD_HMAC_SHA1_IS_INIT_PROP,
    TOMMRO_C_CRYPTO_MD_HMAC_SHA256_IS_INIT_PROP,
    TOMMRO_C_CRYPTO_MD_HMAC_SHA512_IS_INIT_PROP,

} tommRoC_crypto_md_hmac_prop_enum_t;


// MD HMAC function type.
typedef tommRoC_err_enum_t (*tommRoC_crypto_md_hmac_funct_t)(
        const   void*       const   keyPtr,
        const   uint16_t            keySize,
        const   void*       const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                void*       const   outputBufferPtr);

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* MD HMAC environment init functs */

/**
 * MD HMAC SHA1/SHA256/SHA512 environment init.
 *
 * param[in]        mdHmac                  MD HMAC SHA256/SHA512 function.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoMDHmacSHA1InitEnv(const tommRoC_crypto_md_hmac_funct_t mdHmac);
tommRoC_err_enum_t tommRoCCryptoMDHmacSHA256InitEnv(const tommRoC_crypto_md_hmac_funct_t mdHmac);
tommRoC_err_enum_t tommRoCCryptoMDHmacSHA512InitEnv(const tommRoC_crypto_md_hmac_funct_t mdHmac);


/******************* MD HMAC environment close functs */

/**
 * MD HMAC SHA1/SHA256/SHA512 environment close.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoMDHmacSHA1CloseEnv(void);
tommRoC_err_enum_t tommRoCCryptoMDHmacSHA256CloseEnv(void);
tommRoC_err_enum_t tommRoCCryptoMDHmacSHA512CloseEnv(void);


/******************* MD HMAC environment get/set properties functs */

/**
 * Get MD HMAC SHA1/SHA256/SHA512 property.
 *
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoMDHmacGetProp(
        const   tommRoC_crypto_md_hmac_prop_enum_t          property,
                void*                               const   propValuePtr);

/**
 * Set MD HMAC SHA1/SHA256/SHA512 property.
 *
 * param[in]        property                property.
 * param[in]        propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoMDHmacSetProp(
        const   tommRoC_crypto_md_hmac_prop_enum_t          property,
        const   void*                               const   propValuePtr);


/******************* MD HMAC environment functs */

/**
 * MD HMAC SHA1/SHA256/SHA512.
 * NOTE: Output data length have to be equal/greater than:
 *          - TOMMROC_CRYPTO_MD_HMAC_SHA1_RESULT_SIZE_BYTE (20) bytes.
 *          - TOMMROC_CRYPTO_MD_HMAC_SHA256_RESULT_SIZE_BYTE (32) bytes.
 *          - TOMMROC_CRYPTO_MD_HMAC_SHA512_RESULT_SIZE_BYTE (64) bytes.
 *
 * param[in]        keyPtr                  input key buffer pointer.
 * param[in]        keySize                 input key size [byte].
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer len [byte].
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer ptr.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoMDHmacSHA1(
        const   void*       const   keyPtr,
        const   uint16_t            keySize,
        const   void*       const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
        const   uint16_t            outputBufferMaxSize,
                void*       const   outputBufferPtr);
tommRoC_err_enum_t tommRoCCryptoMDHmacSHA256(
        const   void*       const   keyPtr,
        const   uint16_t            keySize,
        const   void*       const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
        const   uint16_t            outputBufferMaxSize,
                void*       const   outputBufferPtr);
tommRoC_err_enum_t tommRoCCryptoMDHmacSHA512(
        const   void*       const   keyPtr,
        const   uint16_t            keySize,
        const   void*       const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
        const   uint16_t            outputBufferMaxSize,
                void*       const   outputBufferPtr);

/**
 * @}
 */

#endif
