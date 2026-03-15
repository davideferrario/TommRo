
#ifndef TOMMROC_CRYPTO_SHA_H_
#define TOMMROC_CRYPTO_SHA_H_

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
 * @defgroup tommRoCCryptoSHA tommRoCCryptoSHA
 *
 * @brief  TommRoC library crypto SHA module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted crypto SHA functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCUnitMeasure.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/
#define TOMMROC_CRYPTO_SHA1_RESULT_SIZE_BYTE        (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(160))
#define TOMMROC_CRYPTO_SHA224_RESULT_SIZE_BYTE      (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(224))
#define TOMMROC_CRYPTO_SHA256_RESULT_SIZE_BYTE      (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(256))
#define TOMMROC_CRYPTO_SHA384_RESULT_SIZE_BYTE      (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(384))
#define TOMMROC_CRYPTO_SHA512_RESULT_SIZE_BYTE      (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(512))

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC crypto SHA properties enumeration.
typedef enum {

    /**
     * SHA environment guard.
     * This have to be used for simultaneous access on SHA hardware and/or if
     * simultaneous access is not supported by software level.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_guard_t*.
     */
    TOMMRO_C_CRYPTO_SHA_GUARD_PROP = 0,

    /**
     * SHA1/SHA224/SHA256/SHA384/SHA512 environment is init.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_SHA1_IS_INIT_PROP,
    TOMMRO_C_CRYPTO_SHA224_IS_INIT_PROP,
    TOMMRO_C_CRYPTO_SHA256_IS_INIT_PROP,
    TOMMRO_C_CRYPTO_SHA384_IS_INIT_PROP,
    TOMMRO_C_CRYPTO_SHA512_IS_INIT_PROP,

} tommRoC_crypto_sha_prop_enum_t;


// SHA function type.
typedef tommRoC_err_enum_t (*tommRoC_crypto_sha_funct_t)(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr);

// SHA start function type.
typedef tommRoC_err_enum_t (*tommRoC_crypto_sha_start_funct_t)(
                void*       const   shaCtxPtr);

// SHA update function type.
typedef tommRoC_err_enum_t (*tommRoC_crypto_sha_update_funct_t)(
                void*       const   shaCtxPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen);

// SHA finish function type.
typedef tommRoC_err_enum_t (*tommRoC_crypto_sha_finish_funct_t)(
                void*       const   shaCtxPtr,
                uint8_t*    const   outputBufferPtr);

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* SHA environment init functs */

/**
 * SHA1/SHA224/SHA256/SHA384/SHA512 environment init.
 *
 * param[in]        shaFunctPtr             SHA1/224/256/384/512 function.
 * param[in]        shaStartFunctPtr        SHA1/224/256/384/512 start function.
 * param[in]        shaUpdateFunctPtr       SHA1/224/256/384/512 update function.
 * param[in]        shaFinishFunctPtr       SHA1/224/256/384/512 finish function.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoSHA1InitEnv(
        const   tommRoC_crypto_sha_funct_t          shaFunctPtr,
        const   tommRoC_crypto_sha_start_funct_t    shaStartFunctPtr,
        const   tommRoC_crypto_sha_update_funct_t   shaUpdateFunctPtr,
        const   tommRoC_crypto_sha_finish_funct_t   shaFinishFunctPtr);
tommRoC_err_enum_t tommRoCCryptoSHA224InitEnv(
        const   tommRoC_crypto_sha_funct_t          shaFunctPtr,
        const   tommRoC_crypto_sha_start_funct_t    shaStartFunctPtr,
        const   tommRoC_crypto_sha_update_funct_t   shaUpdateFunctPtr,
        const   tommRoC_crypto_sha_finish_funct_t   shaFinishFunctPtr);
tommRoC_err_enum_t tommRoCCryptoSHA256InitEnv(
        const   tommRoC_crypto_sha_funct_t          shaFunctPtr,
        const   tommRoC_crypto_sha_start_funct_t    shaStartFunctPtr,
        const   tommRoC_crypto_sha_update_funct_t   shaUpdateFunctPtr,
        const   tommRoC_crypto_sha_finish_funct_t   shaFinishFunctPtr);
tommRoC_err_enum_t tommRoCCryptoSHA384InitEnv(
        const   tommRoC_crypto_sha_funct_t          shaFunctPtr,
        const   tommRoC_crypto_sha_start_funct_t    shaStartFunctPtr,
        const   tommRoC_crypto_sha_update_funct_t   shaUpdateFunctPtr,
        const   tommRoC_crypto_sha_finish_funct_t   shaFinishFunctPtr);
tommRoC_err_enum_t tommRoCCryptoSHA512InitEnv(
        const   tommRoC_crypto_sha_funct_t          shaFunctPtr,
        const   tommRoC_crypto_sha_start_funct_t    shaStartFunctPtr,
        const   tommRoC_crypto_sha_update_funct_t   shaUpdateFunctPtr,
        const   tommRoC_crypto_sha_finish_funct_t   shaFinishFunctPtr);


/******************* SHA environment close functs */

/**
 * SHA1/SHA224/SHA256/SHA384/SHA512 environment close.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoSHA1CloseEnv(void);
tommRoC_err_enum_t tommRoCCryptoSHA224CloseEnv(void);
tommRoC_err_enum_t tommRoCCryptoSHA256CloseEnv(void);
tommRoC_err_enum_t tommRoCCryptoSHA384CloseEnv(void);
tommRoC_err_enum_t tommRoCCryptoSHA512CloseEnv(void);


/******************* SHA environment get/set properties functs */

/**
 * Get SHA1/SHA224/SHA256/SHA384/SHA512 property.
 *
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoSHAGetProp(
        const   tommRoC_crypto_sha_prop_enum_t          property,
                void*                           const   propValuePtr);

/**
 * Set SHA1/SHA224/SHA256/SHA384/SHA512 property.
 *
 * param[in]        property                property.
 * param[in]        propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoSHASetProp(
        const   tommRoC_crypto_sha_prop_enum_t          property,
        const   void*                           const   propValuePtr);


/******************* SHA environment functs */

/**
 * SHA1/SHA224/SHA256/SHA384/SHA512.
 * NOTE: Output data length have to be equal/greater than:
 *          - TOMMROC_CRYPTO_SHA1_RESULT_SIZE_BYTE (20) bytes.
 *          - TOMMROC_CRYPTO_SHA224_RESULT_SIZE_BYTE (28) bytes.
 *          - TOMMROC_CRYPTO_SHA256_RESULT_SIZE_BYTE (32) bytes.
 *          - TOMMROC_CRYPTO_SHA384_RESULT_SIZE_BYTE (48) bytes.
 *          - TOMMROC_CRYPTO_SHA512_RESULT_SIZE_BYTE (64) bytes.
 *
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer len [byte].
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer ptr.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoSHA1(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
        const   uint16_t            outputBufferMaxSize,
                uint8_t*    const   outputBufferPtr);
tommRoC_err_enum_t tommRoCCryptoSHA224(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
        const   uint16_t            outputBufferMaxSize,
                uint8_t*    const   outputBufferPtr);
tommRoC_err_enum_t tommRoCCryptoSHA256(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
        const   uint16_t            outputBufferMaxSize,
                uint8_t*    const   outputBufferPtr);
tommRoC_err_enum_t tommRoCCryptoSHA384(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
        const   uint16_t            outputBufferMaxSize,
                uint8_t*    const   outputBufferPtr);
tommRoC_err_enum_t tommRoCCryptoSHA512(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
        const   uint16_t            outputBufferMaxSize,
                uint8_t*    const   outputBufferPtr);

/**
 * Start SHA1/SHA224/SHA256/SHA384/SHA512 context.
 *
 * param[in/out]    shaCtxPtr               SHA opaque context pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoSHA1Start(
                void*       const   shaCtxPtr);
tommRoC_err_enum_t tommRoCCryptoSHA224Start(
                void*       const   shaCtxPtr);
tommRoC_err_enum_t tommRoCCryptoSHA256Start(
                void*       const   shaCtxPtr);
tommRoC_err_enum_t tommRoCCryptoSHA384Start(
                void*       const   shaCtxPtr);
tommRoC_err_enum_t tommRoCCryptoSHA512Start(
                void*       const   shaCtxPtr);

/**
 * Update SHA1/SHA224/SHA256/SHA384/SHA512 context.
 *
 * param[in/out]    shaCtxPtr               SHA opaque context pointer.
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer len [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoSHA1Update(
                void*       const   shaCtxPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen);
tommRoC_err_enum_t tommRoCCryptoSHA224Update(
                void*       const   shaCtxPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen);
tommRoC_err_enum_t tommRoCCryptoSHA256Update(
                void*       const   shaCtxPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen);
tommRoC_err_enum_t tommRoCCryptoSHA384Update(
                void*       const   shaCtxPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen);
tommRoC_err_enum_t tommRoCCryptoSHA512Update(
                void*       const   shaCtxPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen);

/**
 * Finish SHA1/SHA224/SHA256/SHA384/SHA512 context.
 *
 * param[in/out]    shaCtxPtr               SHA opaque context pointer.
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer ptr.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoSHA1Finish(
                void*       const   shaCtxPtr,
        const   uint16_t            outputBufferMaxSize,
                uint8_t*    const   outputBufferPtr);
tommRoC_err_enum_t tommRoCCryptoSHA224Finish(
                void*       const   shaCtxPtr,
        const   uint16_t            outputBufferMaxSize,
                uint8_t*    const   outputBufferPtr);
tommRoC_err_enum_t tommRoCCryptoSHA256Finish(
                void*       const   shaCtxPtr,
        const   uint16_t            outputBufferMaxSize,
                uint8_t*    const   outputBufferPtr);
tommRoC_err_enum_t tommRoCCryptoSHA384Finish(
                void*       const   shaCtxPtr,
        const   uint16_t            outputBufferMaxSize,
                uint8_t*    const   outputBufferPtr);
tommRoC_err_enum_t tommRoCCryptoSHA512Finish(
                void*       const   shaCtxPtr,
        const   uint16_t            outputBufferMaxSize,
                uint8_t*    const   outputBufferPtr);

/**
 * @}
 */

#endif
