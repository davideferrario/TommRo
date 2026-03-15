
#ifndef TOMMROC_CRYPTO_AES_H_
#define TOMMROC_CRYPTO_AES_H_

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
 * @defgroup tommRoCCryptoAES tommRoCCryptoAES
 *
 * @brief  TommRoC library crypto AES module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted crypto AES functionality.
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

// Crypto AES key size [bit].
#define TOMMRO_C_CRYPTO_AES_KEY_128_BIT_SIZE_BIT        (128)
#define TOMMRO_C_CRYPTO_AES_KEY_192_BIT_SIZE_BIT        (192)
#define TOMMRO_C_CRYPTO_AES_KEY_256_BIT_SIZE_BIT        (256)

// Crypto AES key size [byte].
#define TOMMRO_C_CRYPTO_AES_KEY_128_BIT_SIZE_BYTE       (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(TOMMRO_C_CRYPTO_AES_KEY_128_BIT_SIZE_BIT))
#define TOMMRO_C_CRYPTO_AES_KEY_192_BIT_SIZE_BYTE       (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(TOMMRO_C_CRYPTO_AES_KEY_192_BIT_SIZE_BIT))
#define TOMMRO_C_CRYPTO_AES_KEY_256_BIT_SIZE_BYTE       (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(TOMMRO_C_CRYPTO_AES_KEY_256_BIT_SIZE_BIT))

#define TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE              (16)
#define TOMMROC_CRYPTO_AES_CBC_IV_SIZE_BYTE             (TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC crypto AES key size.
typedef enum {

    /**
     * AES 128 bit key size.
     */
    TOMMRO_C_CRYPTO_AES_KEY_128_BIT = 0,

    /**
     * AES 192 bit key size.
     */
    TOMMRO_C_CRYPTO_AES_KEY_192_BIT,

    /**
     * AES 256 bit key size.
     */
    TOMMRO_C_CRYPTO_AES_KEY_256_BIT,

} tommRoC_crypto_aes_key_size_enum_t;


// tommRoC crypto AES properties enumeration.
typedef enum {

    /**
     * AES environment guard.
     * This have to be used for simultaneous access on AES hardware and/or if
     * simultaneous access is not supported by software level.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_guard_t*.
     */
    TOMMRO_C_CRYPTO_AES_GUARD_PROP = 0,

    /**
     * AES cbc/ecb environment is init.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_AES_CBC_IS_INIT_PROP,
    TOMMRO_C_CRYPTO_AES_ECB_IS_INIT_PROP,

    /**
     * AES supported AES key size.
     *
     * Available:   get/set.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_AES_KEY_128_BIT_SUPPORTED_PROP,
    TOMMRO_C_CRYPTO_AES_KEY_192_BIT_SUPPORTED_PROP,
    TOMMRO_C_CRYPTO_AES_KEY_256_BIT_SUPPORTED_PROP,

    /**
     * AES cbc is IV updated.
     * NOTE: if true, the content of the IV is updated so that is possible to call the
     *       same function again on the following block(s) of data and get the same
     *       result as if it was encrypted in one call.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_AES_CBC_IS_IV_UPDATED_PROP,

} tommRoC_crypto_aes_prop_enum_t;


/**
 * AES-CBC encryption/decryption function type.
 */
typedef tommRoC_err_enum_t (*tommRoC_crypto_aes_cbc_encrypt_funct_t)(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
                uint8_t*                            const   aesIVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr);

typedef tommRoC_err_enum_t (*tommRoC_crypto_aes_cbc_decrypt_funct_t)(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
                uint8_t*                            const   aesIVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr);


/**
 * AES-ECB encryption/decryption function type.
 */
typedef tommRoC_err_enum_t (*tommRoC_crypto_aes_ecb_encrypt_funct_t)(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr);

typedef tommRoC_err_enum_t (*tommRoC_crypto_aes_ecb_decrypt_funct_t)(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr);


/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* AES environment init functs */

/**
 * AES environment init.
 * NOTE: after init environment, next step is to set supported key size properties.
 *
 * param[in]        aesEncrypt              AES encrypt function.
 * param[in]        aesDecrypt              AES decrypt function.
 * param[in]        isIVUpdated             is the content of IV updated, to allow a "streaming" usage.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoAES_CBC_InitEnv(
        const   tommRoC_crypto_aes_cbc_encrypt_funct_t      aesEncrypt,
        const   tommRoC_crypto_aes_cbc_decrypt_funct_t      aesDecrypt,
        const   bool                                        isIVUpdated);

tommRoC_err_enum_t tommRoCCryptoAES_ECB_InitEnv(
        const   tommRoC_crypto_aes_ecb_encrypt_funct_t      aesEncrypt,
        const   tommRoC_crypto_aes_ecb_decrypt_funct_t      aesDecrypt);


/******************* AES environment close functs */

/**
 * AES environment close.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoAES_CBC_CloseEnv(void);
tommRoC_err_enum_t tommRoCCryptoAES_ECB_CloseEnv(void);


/******************* AES environment get/set properties functs */

/**
 * Get crypto AES property.
 *
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoAESGetProp(
        const   tommRoC_crypto_aes_prop_enum_t          property,
                void*                           const   propValuePtr);

/**
 * Set crypto AES property.
 *
 * param[in]        property                property.
 * param[in]        propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoAESSetProp(
        const   tommRoC_crypto_aes_prop_enum_t          property,
        const   void*                           const   propValuePtr);


/******************* AES environment functs */

/**
 * Convert AES key size [bit] from enum to uint16_t number.
 *
 * param[in]        aesKeySize              AES key size [bit].
 *
 * return uint16_t
 */
uint16_t tommRoCCryptoAESKeySize(
        const   tommRoC_crypto_aes_key_size_enum_t  aesKeySize);

/**
 * Get AES encrypted data size for a plain text size.
 *
 * param[in]        plainDataSize           AES plain data size [byte].
 *
 * return uint16_t
 */
uint16_t tommRoCCryptoAESEncryptedSize(const uint16_t plainDataSize);


/******************* AES CBC encryption/decryption functs */

/**
 * AES-CBC data encryption.
 * NOTE: Input and output data length have to be multiple of the block size (16 bytes).
 *
 * param[in]        aesKeyPtr               AES key.
 * param[in]        aesKeySize              AES key size.
 * param[in]        aesIVPtr                AES CBC initialization vector pointer .
 * param[in]        aesIVLen                AES CBC initialization vector len [byte]. Have to be equal to the block size (TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE bytes).
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer len [byte]. Have to be multiple of the block size (16 bytes).
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer ptr [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoAES_CBC_Encrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
                uint8_t*                            const   aesIVPtr,
        const   uint8_t                                     aesIVLen,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
        const   uint16_t                                    outputBufferMaxSize,
                uint8_t*                            const   outputBufferPtr);

/**
 * AES-CBC data decryption.
 * NOTE: Input and output data length have to be multiple of the block size (16 bytes).
 *
 * param[in]        aesKeyPtr               AES key.
 * param[in]        aesKeySize              AES key size.
 * param[in]        aesIVPtr                AES CBC initialization vector pointer.
 * param[in]        aesIVLen                AES CBC initialization vector len [byte]. Have to be equal to the block size (16 bytes).
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer len [byte]. Have to be multiple of the block size (16 bytes).
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer ptr [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoAES_CBC_Decrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
                uint8_t*                            const   aesIVPtr,
        const   uint8_t                                     aesIVLen,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
        const   uint16_t                                    outputBufferMaxSize,
                uint8_t*                            const   outputBufferPtr);


/******************* AES ECB encryption/decryption functs */

/**
 * AES-ECB data encryption.
 * NOTE: Input and output data length have to be multiple of the block size (16 bytes).
 *
 * param[in]        aesKeyPtr               AES key.
 * param[in]        aesKeySize              AES key size.
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer len [byte]. Have to be multiple of the block size (16 bytes).
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer ptr [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoAES_ECB_Encrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
        const   uint16_t                                    outputBufferMaxSize,
                uint8_t*                            const   outputBufferPtr);

/**
 * AES-ECB data decryption.
 * NOTE: Input and output data length have to be multiple of the block size (16 bytes).
 *
 * param[in]        aesKeyPtr               AES key.
 * param[in]        aesKeySize              AES key size.
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer len [byte]. Have to be multiple of the block size (16 bytes).
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer ptr [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoAES_ECB_Decrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
        const   uint16_t                                    outputBufferMaxSize,
                uint8_t*                            const   outputBufferPtr);

/**
 * @}
 */

#endif
