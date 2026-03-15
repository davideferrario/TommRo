
#ifndef TOMMROC_CRYPTO_DES_H_
#define TOMMROC_CRYPTO_DES_H_

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
 * @defgroup tommRoCCryptoDES tommRoCCryptoDES
 *
 * @brief  TommRoC library crypto DES module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted crypto DES functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCUnitMeasure.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

#define TOMMRO_C_CRYPTO_DES_KEY_SIZE_BIT    (64)                                                                    // Crypto DES key size [bit].
#define TOMMRO_C_CRYPTO_DES_KEY_SIZE_BYTE   (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(TOMMRO_C_CRYPTO_DES_KEY_SIZE_BIT))    // Crypto DES key size [byte].

#define TOMMROC_CRYPTO_DES_BLOCK_SIZE_BYTE  (8)
#define TOMMROC_CRYPTO_DES_CBC_IV_SIZE_BYTE (TOMMROC_CRYPTO_DES_BLOCK_SIZE_BYTE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC crypto DES properties enumeration.
typedef enum {

    /**
     * DES environment guard.
     * This have to be used for simultaneous access on DES hardware and/or if
     * simultaneous access is not supported by software level.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_guard_t*.
     */
    TOMMRO_C_CRYPTO_DES_GUARD_PROP = 0,

    /**
     * DES cbc/ecb environment is init.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_DES_CBC_IS_INIT_PROP,
    TOMMRO_C_CRYPTO_DES_ECB_IS_INIT_PROP,

    /**
     * DES cbc is IV updated.
     * NOTE: if true, the content of the IV is updated so that is possible to call the
     *       same function again on the following block(s) of data and get the same
     *       result as if it was encrypted in one call.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_DES_CBC_IS_IV_UPDATED_PROP,

} tommRoC_crypto_des_prop_enum_t;


/**
 * DES-CBC encryption/decryption function type.
 */
typedef tommRoC_err_enum_t (*tommRoC_crypto_des_cbc_encrypt_funct_t)(
        const   uint8_t*                            const   desKeyPtr,
                uint8_t*                            const   desIVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr);

typedef tommRoC_err_enum_t (*tommRoC_crypto_des_cbc_decrypt_funct_t)(
        const   uint8_t*                            const   desKeyPtr,
                uint8_t*                            const   desIVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr);


/**
 * DES-ECB encryption/decryption function type.
 */
typedef tommRoC_err_enum_t (*tommRoC_crypto_des_ecb_encrypt_funct_t)(
        const   uint8_t*                            const   desKeyPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr);

typedef tommRoC_err_enum_t (*tommRoC_crypto_des_ecb_decrypt_funct_t)(
        const   uint8_t*                            const   desKeyPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr);


/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* DES environment init functs */

/**
 * DES environment init.
 * NOTE: after init environment, next step is to set supported key size properties.
 *
 * param[in]        desEncrypt              DES encrypt function.
 * param[in]        desDecrypt              DES decrypt function.
 * param[in]        isIVUpdated             is the content of IV updated, to allow a "streaming" usage.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoDES_CBC_InitEnv(
        const   tommRoC_crypto_des_cbc_encrypt_funct_t      desEncrypt,
        const   tommRoC_crypto_des_cbc_decrypt_funct_t      desDecrypt,
        const   bool                                        isIVUpdated);

tommRoC_err_enum_t tommRoCCryptoDES_ECB_InitEnv(
        const   tommRoC_crypto_des_ecb_encrypt_funct_t      desEncrypt,
        const   tommRoC_crypto_des_ecb_decrypt_funct_t      desDecrypt);


/******************* DES environment close functs */

/**
 * DES environment close.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoDES_CBC_CloseEnv(void);
tommRoC_err_enum_t tommRoCCryptoDES_ECB_CloseEnv(void);


/******************* DES environment get/set properties functs */

/**
 * Get crypto DES property.
 *
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoDESGetProp(
        const   tommRoC_crypto_des_prop_enum_t          property,
                void*                           const   propValuePtr);

/**
 * Set crypto DES property.
 *
 * param[in]        property                property.
 * param[in]        propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoDESSetProp(
        const   tommRoC_crypto_des_prop_enum_t          property,
        const   void*                           const   propValuePtr);


/******************* DES CBC encryption/decryption functs */

/**
 * DES-CBC data encryption.
 * NOTE: Input and output data length have to be multiple of the block size (16 bytes).
 *
 * param[in]        desKeyPtr               DES key.
 * param[in]        desIVPtr                DES CBC initialization vector pointer .
 * param[in]        desIVLen                DES CBC initialization vector len [byte]. Have to be equal to the block size (TOMMROC_CRYPTO_DES_BLOCK_SIZE_BYTE bytes).
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer len [byte]. Have to be multiple of the block size (16 bytes).
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer ptr [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoDES_CBC_Encrypt(
        const   uint8_t*                            const   desKeyPtr,
                uint8_t*                            const   desIVPtr,
        const   uint8_t                                     desIVLen,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
        const   uint16_t                                    outputBufferMaxSize,
                uint8_t*                            const   outputBufferPtr);

/**
 * DES-CBC data decryption.
 * NOTE: Input and output data length have to be multiple of the block size (16 bytes).
 *
 * param[in]        desKeyPtr               DES key.
 * param[in]        desIVPtr                DES CBC initialization vector pointer.
 * param[in]        desIVLen                DES CBC initialization vector len [byte]. Have to be equal to the block size (16 bytes).
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer len [byte]. Have to be multiple of the block size (16 bytes).
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer ptr [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoDES_CBC_Decrypt(
        const   uint8_t*                            const   desKeyPtr,
                uint8_t*                            const   desIVPtr,
        const   uint8_t                                     desIVLen,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
        const   uint16_t                                    outputBufferMaxSize,
                uint8_t*                            const   outputBufferPtr);


/******************* DES ECB encryption/decryption functs */

/**
 * DES-ECB data encryption.
 * NOTE: Input and output data length have to be multiple of the block size (16 bytes).
 *
 * param[in]        desKeyPtr               DES key.
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer len [byte]. Have to be multiple of the block size (16 bytes).
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer ptr [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoDES_ECB_Encrypt(
        const   uint8_t*                            const   desKeyPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
        const   uint16_t                                    outputBufferMaxSize,
                uint8_t*                            const   outputBufferPtr);

/**
 * DES-ECB data decryption.
 * NOTE: Input and output data length have to be multiple of the block size (16 bytes).
 *
 * param[in]        desKeyPtr               DES key.
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer len [byte]. Have to be multiple of the block size (16 bytes).
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer ptr [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoDES_ECB_Decrypt(
        const   uint8_t*                            const   desKeyPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
        const   uint16_t                                    outputBufferMaxSize,
                uint8_t*                            const   outputBufferPtr);

/**
 * @}
 */

#endif
