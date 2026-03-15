
#ifndef TOMMROC_CRYPTO_RSA_H_
#define TOMMROC_CRYPTO_RSA_H_

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
 * @defgroup tommRoCCryptoRSA tommRoCCryptoRSA
 *
 * @brief  TommRoC library crypto RSA module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted crypto RSA functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCString.h"
#include "tommRoCUnitMeasure.h"
#include "tommRoCUtil.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// Public modulus size [byte]
#define TOMMROC_CRYPTO_RSA_512_BIT_PUBLIC_MODULUS_SIZE_BYTE             (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(512))
#define TOMMROC_CRYPTO_RSA_1024_BIT_PUBLIC_MODULUS_SIZE_BYTE            (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(1024))
#define TOMMROC_CRYPTO_RSA_2048_BIT_PUBLIC_MODULUS_SIZE_BYTE            (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(2048))
#define TOMMROC_CRYPTO_RSA_4096_BIT_PUBLIC_MODULUS_SIZE_BYTE            (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(4096))

// PKCS-1 v1.5 encoding overhead size [byte]
#define TOMMROC_CRYPTO_RSA_PKCS_V15_OVERHEAD_SIZE_BYTE                  (11)

// PKCS-1 v1.5 max. plain text size [byte]
#define TOMMROC_CRYPTO_RSA_512_BIT_PKCS_V15_PLAIN_TEXT_MAX_SIZE_BYTE    \
        (TOMMROC_CRYPTO_RSA_512_BIT_PUBLIC_MODULUS_SIZE_BYTE - TOMMROC_CRYPTO_RSA_PKCS_V15_OVERHEAD_SIZE_BYTE)
#define TOMMROC_CRYPTO_RSA_1024_BIT_PKCS_V15_PLAIN_TEXT_MAX_SIZE_BYTE   \
        (TOMMROC_CRYPTO_RSA_1024_BIT_PUBLIC_MODULUS_SIZE_BYTE - TOMMROC_CRYPTO_RSA_PKCS_V15_OVERHEAD_SIZE_BYTE)
#define TOMMROC_CRYPTO_RSA_2048_BIT_PKCS_V15_PLAIN_TEXT_MAX_SIZE_BYTE   \
        (TOMMROC_CRYPTO_RSA_2048_BIT_PUBLIC_MODULUS_SIZE_BYTE - TOMMROC_CRYPTO_RSA_PKCS_V15_OVERHEAD_SIZE_BYTE)
#define TOMMROC_CRYPTO_RSA_4096_BIT_PKCS_V15_PLAIN_TEXT_MAX_SIZE_BYTE   \
        (TOMMROC_CRYPTO_RSA_4096_BIT_PUBLIC_MODULUS_SIZE_BYTE - TOMMROC_CRYPTO_RSA_PKCS_V15_OVERHEAD_SIZE_BYTE)

// PKCS-1 v1.5 encrypted text size [byte]
#define TOMMROC_CRYPTO_RSA_512_BIT_PKCS_V15_CIPHER_TEXT_SIZE_BYTE       \
        (TOMMROC_CRYPTO_RSA_512_BIT_PUBLIC_MODULUS_SIZE_BYTE)
#define TOMMROC_CRYPTO_RSA_1024_BIT_PKCS_V15_CIPHER_TEXT_SIZE_BYTE      \
        (TOMMROC_CRYPTO_RSA_1024_BIT_PUBLIC_MODULUS_SIZE_BYTE)
#define TOMMROC_CRYPTO_RSA_2048_BIT_PKCS_V15_CIPHER_TEXT_SIZE_BYTE      \
        (TOMMROC_CRYPTO_RSA_2048_BIT_PUBLIC_MODULUS_SIZE_BYTE)
#define TOMMROC_CRYPTO_RSA_4096_BIT_PKCS_V15_CIPHER_TEXT_SIZE_BYTE      \
        (TOMMROC_CRYPTO_RSA_4096_BIT_PUBLIC_MODULUS_SIZE_BYTE)

// Private/public key min. size in both DER/PEM format [byte]
#define TOMMROC_CRYPTO_RSA_512_BIT_PRIV_KEY_DER_FORMAT_MIN_SIZE_BYTE    (1)
#define TOMMROC_CRYPTO_RSA_512_BIT_PUBL_KEY_DER_FORMAT_MIN_SIZE_BYTE    (1)
#define TOMMROC_CRYPTO_RSA_512_BIT_PRIV_KEY_PEM_FORMAT_MIN_SIZE_BYTE    (TOMMROC_UTIL_STRING_ARR_LENGTH("-----BEGIN RSA PRIVATE KEY-----\n") + 1 + TOMMROC_UTIL_STRING_ARR_LENGTH("-----END RSA PRIVATE KEY-----\n") + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)
#define TOMMROC_CRYPTO_RSA_512_BIT_PUBL_KEY_PEM_FORMAT_MIN_SIZE_BYTE    (TOMMROC_UTIL_STRING_ARR_LENGTH("-----BEGIN PUBLIC KEY-----\n") + 1 + TOMMROC_UTIL_STRING_ARR_LENGTH("-----END PUBLIC KEY-----\n") + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)

#define TOMMROC_CRYPTO_RSA_1024_BIT_PRIV_KEY_DER_FORMAT_MIN_SIZE_BYTE   (1)
#define TOMMROC_CRYPTO_RSA_1024_BIT_PUBL_KEY_DER_FORMAT_MIN_SIZE_BYTE   (1)
#define TOMMROC_CRYPTO_RSA_1024_BIT_PRIV_KEY_PEM_FORMAT_MIN_SIZE_BYTE   (TOMMROC_UTIL_STRING_ARR_LENGTH("-----BEGIN RSA PRIVATE KEY-----\n") + 1 + TOMMROC_UTIL_STRING_ARR_LENGTH("-----END RSA PRIVATE KEY-----\n") + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)
#define TOMMROC_CRYPTO_RSA_1024_BIT_PUBL_KEY_PEM_FORMAT_MIN_SIZE_BYTE   (TOMMROC_UTIL_STRING_ARR_LENGTH("-----BEGIN PUBLIC KEY-----\n") + 1 + TOMMROC_UTIL_STRING_ARR_LENGTH("-----END PUBLIC KEY-----\n") + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)

#define TOMMROC_CRYPTO_RSA_2048_BIT_PRIV_KEY_DER_FORMAT_MIN_SIZE_BYTE   (1)
#define TOMMROC_CRYPTO_RSA_2048_BIT_PUBL_KEY_DER_FORMAT_MIN_SIZE_BYTE   (1)
#define TOMMROC_CRYPTO_RSA_2048_BIT_PRIV_KEY_PEM_FORMAT_MIN_SIZE_BYTE   (TOMMROC_UTIL_STRING_ARR_LENGTH("-----BEGIN RSA PRIVATE KEY-----\n") + 1 + TOMMROC_UTIL_STRING_ARR_LENGTH("-----END RSA PRIVATE KEY-----\n") + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)
#define TOMMROC_CRYPTO_RSA_2048_BIT_PUBL_KEY_PEM_FORMAT_MIN_SIZE_BYTE   (TOMMROC_UTIL_STRING_ARR_LENGTH("-----BEGIN PUBLIC KEY-----\n") + 1 + TOMMROC_UTIL_STRING_ARR_LENGTH("-----END PUBLIC KEY-----\n") + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)

#define TOMMROC_CRYPTO_RSA_4096_BIT_PRIV_KEY_DER_FORMAT_MIN_SIZE_BYTE   (1)
#define TOMMROC_CRYPTO_RSA_4096_BIT_PUBL_KEY_DER_FORMAT_MIN_SIZE_BYTE   (1)
#define TOMMROC_CRYPTO_RSA_4096_BIT_PRIV_KEY_PEM_FORMAT_MIN_SIZE_BYTE   (TOMMROC_UTIL_STRING_ARR_LENGTH("-----BEGIN RSA PRIVATE KEY-----\n") + 1 + TOMMROC_UTIL_STRING_ARR_LENGTH("-----END RSA PRIVATE KEY-----\n") + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)
#define TOMMROC_CRYPTO_RSA_4096_BIT_PUBL_KEY_PEM_FORMAT_MIN_SIZE_BYTE   (TOMMROC_UTIL_STRING_ARR_LENGTH("-----BEGIN PUBLIC KEY-----\n") + 1 + TOMMROC_UTIL_STRING_ARR_LENGTH("-----END PUBLIC KEY-----\n") + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)


// Private/public key max. size in both DER/PEM format [byte]
#define TOMMROC_CRYPTO_RSA_512_BIT_PRIV_KEY_DER_FORMAT_MAX_SIZE_BYTE    (328)
#define TOMMROC_CRYPTO_RSA_512_BIT_PUBL_KEY_DER_FORMAT_MAX_SIZE_BYTE    (104)
#define TOMMROC_CRYPTO_RSA_512_BIT_PRIV_KEY_PEM_FORMAT_MAX_SIZE_BYTE    (517)
#define TOMMROC_CRYPTO_RSA_512_BIT_PUBL_KEY_PEM_FORMAT_MAX_SIZE_BYTE    (192)

#define TOMMROC_CRYPTO_RSA_1024_BIT_PRIV_KEY_DER_FORMAT_MAX_SIZE_BYTE   (619)
#define TOMMROC_CRYPTO_RSA_1024_BIT_PUBL_KEY_DER_FORMAT_MAX_SIZE_BYTE   (172)
#define TOMMROC_CRYPTO_RSA_1024_BIT_PRIV_KEY_PEM_FORMAT_MAX_SIZE_BYTE   (919)
#define TOMMROC_CRYPTO_RSA_1024_BIT_PUBL_KEY_PEM_FORMAT_MAX_SIZE_BYTE   (286)

#define TOMMROC_CRYPTO_RSA_2048_BIT_PRIV_KEY_DER_FORMAT_MAX_SIZE_BYTE   (1203)
#define TOMMROC_CRYPTO_RSA_2048_BIT_PUBL_KEY_DER_FORMAT_MAX_SIZE_BYTE   (304)
#define TOMMROC_CRYPTO_RSA_2048_BIT_PRIV_KEY_PEM_FORMAT_MAX_SIZE_BYTE   (1731)
#define TOMMROC_CRYPTO_RSA_2048_BIT_PUBL_KEY_PEM_FORMAT_MAX_SIZE_BYTE   (471)

#define TOMMROC_CRYPTO_RSA_4096_BIT_PRIV_KEY_DER_FORMAT_MAX_SIZE_BYTE   (2358)
#define TOMMROC_CRYPTO_RSA_4096_BIT_PUBL_KEY_DER_FORMAT_MAX_SIZE_BYTE   (560)
#define TOMMROC_CRYPTO_RSA_4096_BIT_PRIV_KEY_PEM_FORMAT_MAX_SIZE_BYTE   (3345)
#define TOMMROC_CRYPTO_RSA_4096_BIT_PUBL_KEY_PEM_FORMAT_MAX_SIZE_BYTE   (828)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC crypto RSA encoding enumeration.
typedef enum {

    TOMMRO_C_CRYPTO_RSA_PKCS_V15 = 0,       // Use PKCS-1 v1.5 encoding.
    TOMMRO_C_CRYPTO_RSA_PKCS_V21,           // Use PKCS-1 v2.1 encoding.

} tommRoC_crypto_rsa_encoding_enum_t;

// tommRoC crypto RSA base key size enumeration.
typedef enum {

    TOMMRO_C_CRYPTO_RSA_KEY_SIZE_512_BIT = 0,
    TOMMRO_C_CRYPTO_RSA_KEY_SIZE_1024_BIT,
    TOMMRO_C_CRYPTO_RSA_KEY_SIZE_2048_BIT,
    TOMMRO_C_CRYPTO_RSA_KEY_SIZE_4096_BIT,

} tommRoC_crypto_rsa_key_size_enum_t;

// tommRoC crypto RSA hash type enumeration.
typedef enum {

    TOMMRO_C_CRYPTO_RSA_HASH_NONE = 0,
    TOMMRO_C_CRYPTO_RSA_HASH_MD2,
    TOMMRO_C_CRYPTO_RSA_HASH_MD4,
    TOMMRO_C_CRYPTO_RSA_HASH_MD5,
    TOMMRO_C_CRYPTO_RSA_HASH_SHA1,
    TOMMRO_C_CRYPTO_RSA_HASH_SHA224,
    TOMMRO_C_CRYPTO_RSA_HASH_SHA256,
    TOMMRO_C_CRYPTO_RSA_HASH_SHA384,
    TOMMRO_C_CRYPTO_RSA_HASH_SHA512,
    TOMMRO_C_CRYPTO_RSA_HASH_RIPEMD160,

} tommRoC_crypto_rsa_hash_enum_t;


// tommRoC crypto RSA properties enumeration.
typedef enum {

    /**
     * RSA environment guard.
     * This have to be used for simultaneous access on RSA hardware and/or if
     * simultaneous access is not supported by software level.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_guard_t*.
     */
    TOMMRO_C_CRYPTO_RSA_GUARD_PROP = 0,

    /**
     * RSA generate keypair function is init.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_RSA_GEN_KEYPAIR_IS_INIT_PROP,

    /**
     * RSA encryption function is init.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_RSA_ENCRYPT_IS_INIT_PROP,

    /**
     * RSA decryption function is init.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_RSA_DECRYPT_IS_INIT_PROP,

    /**
     * RSA sign function is init.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_RSA_SIGN_IS_INIT_PROP,

    /**
     * RSA verify function is init.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_RSA_VERIFY_IS_INIT_PROP,

} tommRoC_crypto_rsa_prop_enum_t;


//RSA keypair generation function type.
typedef tommRoC_err_enum_t (*tommRoC_crypto_rsa_gen_keypair_funct_t)(
        const   tommRoC_crypto_rsa_encoding_enum_t          encodingMode,
        const   tommRoC_crypto_rsa_hash_enum_t              hashType,
        const   tommRoC_crypto_rsa_key_size_enum_t          keySize,
                uint8_t*                            const   privateKeyPtr,
        const   uint16_t                                    privateKeyMaxSize,
                uint16_t*                           const   privateKeyLenPtr,
                uint8_t*                            const   publicKeyPtr,
        const   uint16_t                                    publicKeyMaxSize,
                uint16_t*                           const   publicKeyLenPtr);

//RSA encryption function type.
typedef tommRoC_err_enum_t (*tommRoC_crypto_rsa_encrypt_funct_t)(
        const   uint8_t*                            const   publicKeyPtr,
        const   uint16_t                                    publicKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr,
        const   uint16_t                                    outputBufferMaxSize,
                uint16_t*                           const   outputBufferLenPtr);

// RSA decryption function type.
typedef tommRoC_err_enum_t (*tommRoC_crypto_rsa_decrypt_funct_t)(
        const   uint8_t*                            const   privateKeyPtr,
        const   uint16_t                                    privateKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr,
        const   uint16_t                                    outputBufferMaxSize,
                uint16_t*                           const   outputBufferLenPtr);

// RSA sign function type.
typedef tommRoC_err_enum_t (*tommRoC_crypto_rsa_sign_funct_t)(
        const   uint8_t*                            const   privateKeyPtr,
        const   uint16_t                                    privateKeySize,
        const   tommRoC_crypto_rsa_hash_enum_t              hashType,
        const   uint8_t*                            const   hashBufferPtr,
        const   uint16_t                                    hashBufferLen,
                uint8_t*                            const   signatureBufferPtr,
        const   uint16_t                                    signatureBufferMaxSize,
                uint16_t*                           const   signatureBufferLenPtr);

// RSA verify function type.
typedef tommRoC_err_enum_t (*tommRoC_crypto_rsa_verify_funct_t)(
        const   uint8_t*                            const   publicKeyPtr,
        const   uint16_t                                    publicKeySize,
        const   tommRoC_crypto_rsa_hash_enum_t              hashType,
        const   uint8_t*                            const   hashBufferPtr,
        const   uint16_t                                    hashBufferLen,
        const   uint8_t*                            const   signatureBufferPtr,
        const   uint16_t                                    signatureBufferLen);


// RSA environment init struct.
typedef struct {

    tommRoC_crypto_rsa_gen_keypair_funct_t      genKeypair;
    tommRoC_crypto_rsa_encrypt_funct_t          encrypt;
    tommRoC_crypto_rsa_decrypt_funct_t          decrypt;
    tommRoC_crypto_rsa_sign_funct_t             sign;
    tommRoC_crypto_rsa_verify_funct_t           verify;

} tommRoC_crypto_rsa_environment_config_t;

#define __EMPTY_tommRoC_crypto_rsa_environment_config_t__   \
{                                                           \
    /* .genKeypair */   NULL,                               \
    /* .encrypt */      NULL,                               \
    /* .decrypt */      NULL,                               \
    /* .sign */         NULL,                               \
    /* .verify */       NULL,                               \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* RSA environment init functs */

/**
 * RSA environment init.
 *
 * param[in]        rsaEnvConfigPtr         RSA environment configuration.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoRSAInitEnv(
        const   tommRoC_crypto_rsa_environment_config_t*    const   rsaEnvConfigPtr);


/******************* RSA environment close functs */

/**
 * RSA environment close.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoRSACloseEnv(void);


/******************* RSA environment get/set properties functs */

/**
 * Get crypto RSA property.
 *
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoRSAGetProp(
        const   tommRoC_crypto_rsa_prop_enum_t          property,
                void*                           const   propValuePtr);

/**
 * Set crypto RSA property.
 *
 * param[in]        property                property.
 * param[in]        propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoRSASetProp(
        const   tommRoC_crypto_rsa_prop_enum_t          property,
        const   void*                           const   propValuePtr);


/******************* RSA environment functs */

/**
 * RSA keypair generation.
 * NOTE: keys are exported as uint8_t data buffer (big endian).
 *
 * param[in]        encodingMode            RSA encoding mode.
 * param[in]        hashType                RSA hash type.
 * param[in]        keySize                 RSA key size.
 * param[out]       privateKeyPtr           private key buffer pointer.
 * param[in]        privateKeyMaxSize       private key buffer max. size [byte].
 * param[out]       privateKeyLenPtr        output private key length pointer [byte].
 * param[out]       publicKeyPtr            public key buffer pointer.
 * param[in]        publicKeyMaxSize        public key buffer max. size [byte].
 * param[out]       publicKeyLenPtr         output public key length pointer [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoRSAGenKeypair(
        const   tommRoC_crypto_rsa_encoding_enum_t          encodingMode,
        const   tommRoC_crypto_rsa_hash_enum_t              hashType,
        const   tommRoC_crypto_rsa_key_size_enum_t          keySize,
                uint8_t*                            const   privateKeyPtr,
        const   uint16_t                                    privateKeyMaxSize,
                uint16_t*                           const   privateKeyLenPtr,
                uint8_t*                            const   publicKeyPtr,
        const   uint16_t                                    publicKeyMaxSize,
                uint16_t*                           const   publicKeyLenPtr);

/**
 * RSA data encryption.
 *
 * param[in]        publicKeyPtr            public key buffer pointer.
 * param[in]        publicKeySize           public key buffer size [byte].
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer length [byte].
 * param[out]       outputBufferPtr         output data buffer pointer.
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferLenPtr      output data buffer length pointer [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoRSAEncrypt(
        const   uint8_t*                            const   publicKeyPtr,
        const   uint16_t                                    publicKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr,
        const   uint16_t                                    outputBufferMaxSize,
                uint16_t*                           const   outputBufferLenPtr);

/**
 * RSA data decryption.
 *
 * param[in]        privateKeyPtr           private key buffer pointer.
 * param[in]        privateKeySize          private key buffer size [byte].
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer length [byte].
 * param[out]       outputBufferPtr         output data buffer pointer.
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferLenPtr      output data buffer length pointer [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoRSADecrypt(
        const   uint8_t*                            const   privateKeyPtr,
        const   uint16_t                                    privateKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr,
        const   uint16_t                                    outputBufferMaxSize,
                uint16_t*                           const   outputBufferLenPtr);

/**
 * RSA sign.
 *
 * param[in]        privateKeyPtr           private key buffer pointer.
 * param[in]        privateKeySize          private key buffer size [byte].
 * param[in]        hashType                hash algorithm used.
 * param[in]        hashBufferPtr           hash of the message to sign buffer.
 * param[in]        hashBufferLen           hash of the message to sign buffer length [byte]
 * param[out]       signatureBufferPtr      output signature buffer pointer.
 * param[in]        signatureBufferMaxSize  output signature buffer max size [byte].
 * param[out]       signatureBufferLenPtr   output signature buffer length pointer [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoRSASign(
        const   uint8_t*                            const   privateKeyPtr,
        const   uint16_t                                    privateKeySize,
        const   tommRoC_crypto_rsa_hash_enum_t              hashType,
        const   uint8_t*                            const   hashBufferPtr,
        const   uint16_t                                    hashBufferLen,
                uint8_t*                            const   signatureBufferPtr,
        const   uint16_t                                    signatureBufferMaxSize,
                uint16_t*                           const   signatureBufferLenPtr);

/**
 * RSA verify.
 *
 * param[in]        publicKeyPtr            public key buffer pointer.
 * param[in]        publicKeySize           public key buffer size [byte].
 * param[in]        hashType                hash algorithm used.
 * param[in]        hashBufferPtr           hash of the message to sign buffer.
 * param[in]        hashBufferLen           hash of the message to sign buffer length [byte]
 * param[in]        signatureBufferPtr      signature to verify buffer pointer.
 * param[in]        signatureBufferLen      signature to verify buffer length [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoRSAVerify(
        const   uint8_t*                            const   publicKeyPtr,
        const   uint16_t                                    publicKeySize,
        const   tommRoC_crypto_rsa_hash_enum_t              hashType,
        const   uint8_t*                            const   hashBufferPtr,
        const   uint16_t                                    hashBufferLen,
        const   uint8_t*                            const   signatureBufferPtr,
        const   uint16_t                                    signatureBufferLen);

/**
 * @}
 */

#endif
