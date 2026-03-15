
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateRSAESP32Wrapper.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "mbedtls/version.h"

#include "mbedtls/ctr_drbg.h"
#include "mbedtls/md.h"
#include "mbedtls/pk.h"
#include "mbedtls/rsa.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __RSA_WRAPPER_GENERIC_ERROR__           (-1)
#define __RSA_WRAPPER_KEY_SIZE_ERROR_RESULT__   (0)

#define __RSA_WRAPPER_PUBLIC_EXPONENT__         (65537)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static mbedtls_pk_context* _pk_ctx_ptr = NULL;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static int _tommRoC_rsa_encoding_to_mbedtls_rsa_encoding(
        const   tommRoC_crypto_rsa_encoding_enum_t  encodingMode) {

    do { // Added to avoid "warning: unreachable code"
        switch (encodingMode) {

        case TOMMRO_C_CRYPTO_RSA_PKCS_V15:
            return MBEDTLS_RSA_PKCS_V15;

        case TOMMRO_C_CRYPTO_RSA_PKCS_V21:
            return MBEDTLS_RSA_PKCS_V21;

        default:
            break;
        }
    } while (0);

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    return __RSA_WRAPPER_GENERIC_ERROR__;
}

static mbedtls_md_type_t _tommRoC_rsa_hash_to_mbedtls_rsa_hash(
        const   tommRoC_crypto_rsa_hash_enum_t      hashType) {

    do { // Added to avoid "warning: unreachable code"
        switch (hashType) {

        case TOMMRO_C_CRYPTO_RSA_HASH_NONE:
            return MBEDTLS_MD_NONE;

#if (MBEDTLS_VERSION_MAJOR == 2)
        case TOMMRO_C_CRYPTO_RSA_HASH_MD2:
            return MBEDTLS_MD_MD2;
#endif

#if (MBEDTLS_VERSION_MAJOR == 2)
        case TOMMRO_C_CRYPTO_RSA_HASH_MD4:
            return MBEDTLS_MD_MD4;
#endif

        case TOMMRO_C_CRYPTO_RSA_HASH_MD5:
            return MBEDTLS_MD_MD5;

        case TOMMRO_C_CRYPTO_RSA_HASH_SHA1:
            return MBEDTLS_MD_SHA1;

        case TOMMRO_C_CRYPTO_RSA_HASH_SHA224:
            return MBEDTLS_MD_SHA224;

        case TOMMRO_C_CRYPTO_RSA_HASH_SHA256:
            return MBEDTLS_MD_SHA256;

        case TOMMRO_C_CRYPTO_RSA_HASH_SHA384:
            return MBEDTLS_MD_SHA384;

        case TOMMRO_C_CRYPTO_RSA_HASH_SHA512:
            return MBEDTLS_MD_SHA512;

        case TOMMRO_C_CRYPTO_RSA_HASH_RIPEMD160:
            return MBEDTLS_MD_RIPEMD160;

        default:
            break;
        }
    } while (0);

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    return __RSA_WRAPPER_GENERIC_ERROR__;
}

static uint16_t _get_key_size_bit(const tommRoC_crypto_rsa_key_size_enum_t keySize) {

    do { // Added to avoid "warning: unreachable code"
        switch (keySize) {

        case TOMMRO_C_CRYPTO_RSA_KEY_SIZE_512_BIT:
            return 512;

        case TOMMRO_C_CRYPTO_RSA_KEY_SIZE_1024_BIT:
            return 1024;

        case TOMMRO_C_CRYPTO_RSA_KEY_SIZE_2048_BIT:
            return 2048;

        case TOMMRO_C_CRYPTO_RSA_KEY_SIZE_4096_BIT:
            return 4096;

        default:
            break;

        }
    } while (0);

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    return __RSA_WRAPPER_KEY_SIZE_ERROR_RESULT__;
}

static int _random_funct_wrapper(void *p_rng, unsigned char *output, size_t len) {

    TOMMROC_ASSERT_NULL(p_rng);

    if (NULL != p_rng) {
        return MBEDTLS_ERR_CTR_DRBG_ENTROPY_SOURCE_FAILED;
    }

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoRNDRetrive(output, len),
            MBEDTLS_ERR_CTR_DRBG_ENTROPY_SOURCE_FAILED);

    return 0;
}

static tommRoC_err_enum_t _parse_public_key(
                mbedtls_pk_context* const   pkCtxPtr,
        const   uint8_t*            const   publicKeyPtr,
        const   uint16_t                    publicKeySize) {

    int res;

    res = mbedtls_pk_parse_public_key(
            pkCtxPtr,
            publicKeyPtr,
            publicKeySize);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    // Just for check: not needed because public key is parsed right now
    TOMMROC_ASSERT_NOT_ZERO(mbedtls_pk_can_do(pkCtxPtr, MBEDTLS_PK_RSA));
    TOMMROC_ASSERT_ZERO(mbedtls_rsa_check_pubkey(mbedtls_pk_rsa(*pkCtxPtr)));

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _parse_private_key(
                mbedtls_pk_context* const   pkCtxPtr,
        const   uint8_t*            const   privateKeyPtr,
        const   uint16_t                    privateKeySize) {

    int res;

#if (MBEDTLS_VERSION_MAJOR == 2)
    res = mbedtls_pk_parse_key(
            pkCtxPtr,
            privateKeyPtr,
            privateKeySize,
            NULL,
            0);
#else
    res = mbedtls_pk_parse_key(
            pkCtxPtr,
            privateKeyPtr,
            privateKeySize,
            NULL,
            0,
            NULL,
            0);
#endif

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    // Just for check: not needed because public key is parsed right now
    TOMMROC_ASSERT_NOT_ZERO(mbedtls_pk_can_do(pkCtxPtr, MBEDTLS_PK_RSA));
    TOMMROC_ASSERT_ZERO(mbedtls_rsa_check_privkey(mbedtls_pk_rsa(*pkCtxPtr)));

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _gen_keypair(
                mbedtls_pk_context*     const   pkCtxPtr,
        const   int                             padding,
        const   mbedtls_md_type_t               hash_id,
        const   uint16_t                        keySizeBit,
                uint8_t*                const   privateKeyPtr,
        const   uint16_t                        privateKeyMaxSize,
                uint16_t*               const   privateKeyLenPtr,
                uint8_t*                const   publicKeyPtr,
        const   uint16_t                        publicKeyMaxSize,
                uint16_t*               const   publicKeyLenPtr) {

    mbedtls_rsa_context* rsaCtxPtr;
    uint16_t tmpLen;
    int res;

    TOMMROC_ASSERT_NOT_EQUALS(padding,      __RSA_WRAPPER_GENERIC_ERROR__);
    TOMMROC_ASSERT_NOT_EQUALS(hash_id,      __RSA_WRAPPER_GENERIC_ERROR__);
    TOMMROC_ASSERT_NOT_EQUALS(keySizeBit,   __RSA_WRAPPER_KEY_SIZE_ERROR_RESULT__);

    res = mbedtls_pk_setup(
            pkCtxPtr,
            mbedtls_pk_info_from_type(MBEDTLS_PK_RSA));

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

#if (MBEDTLS_VERSION_MAJOR == 2)
    rsaCtxPtr = (mbedtls_rsa_context*) pkCtxPtr->pk_ctx;
#else
    rsaCtxPtr = (mbedtls_rsa_context*) pkCtxPtr->MBEDTLS_PRIVATE(pk_ctx);
#endif

#if (MBEDTLS_VERSION_MAJOR == 2)
    mbedtls_rsa_init(rsaCtxPtr, padding, hash_id);
#else
    mbedtls_rsa_init(rsaCtxPtr);
#endif

    res = mbedtls_rsa_gen_key(
            rsaCtxPtr,
            _random_funct_wrapper,
            NULL,
            keySizeBit,
            __RSA_WRAPPER_PUBLIC_EXPONENT__);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    // Just for check: not needed because they are generated right now
    TOMMROC_ASSERT_ZERO(mbedtls_rsa_check_pubkey(rsaCtxPtr));
    TOMMROC_ASSERT_ZERO(mbedtls_rsa_check_privkey(rsaCtxPtr));

    res = mbedtls_pk_write_key_der(
            pkCtxPtr,
            privateKeyPtr,
            privateKeyMaxSize);

    if (res < 0) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    tmpLen = (uint16_t) res;

    // memmove needed because mbedtls library write data at the end of the buffer
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(
            tommRoCUtilMemMove(
                    privateKeyPtr,
                    privateKeyPtr + privateKeyMaxSize - tmpLen,
                    tmpLen));

    *privateKeyLenPtr = tmpLen;

    res = mbedtls_pk_write_pubkey_der(
            pkCtxPtr,
            publicKeyPtr,
            publicKeyMaxSize);

    if (res < 0) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    tmpLen = (uint16_t) res;

    // memmove needed because mbedtls library write data at the end of the buffer
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(
            tommRoCUtilMemMove(
                    publicKeyPtr,
                    publicKeyPtr + publicKeyMaxSize - tmpLen,
                    tmpLen));

    *publicKeyLenPtr = tmpLen;

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _encrypt(
                mbedtls_pk_context* const   pkCtxPtr,
        const   uint8_t*            const   publicKeyPtr,
        const   uint16_t                    publicKeySize,
        const   uint8_t*            const   inputBufferPtr,
        const   uint16_t                    inputBufferLen,
                uint8_t*            const   outputBufferPtr,
        const   uint16_t                    outputBufferMaxSize,
                uint16_t*           const   outputBufferLenPtr) {

    size_t olen;
    int res;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _parse_public_key(
                    pkCtxPtr,
                    publicKeyPtr,
                    publicKeySize));

    // Encrypt
    res = mbedtls_pk_encrypt(
            pkCtxPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr,
            &olen,
            outputBufferMaxSize,
            _random_funct_wrapper,
            NULL);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    *outputBufferLenPtr = (uint16_t) olen;

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _decrypt(
                mbedtls_pk_context* const   pkCtxPtr,
        const   uint8_t*            const   privateKeyPtr,
        const   uint16_t                    privateKeySize,
        const   uint8_t*            const   inputBufferPtr,
        const   uint16_t                    inputBufferLen,
                uint8_t*            const   outputBufferPtr,
        const   uint16_t                    outputBufferMaxSize,
                uint16_t*           const   outputBufferLenPtr) {

    size_t olen;
    int res;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _parse_private_key(
                    pkCtxPtr,
                    privateKeyPtr,
                    privateKeySize));

    // Decrypt
    res = mbedtls_pk_decrypt(
            pkCtxPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr,
            &olen,
            outputBufferMaxSize,
            _random_funct_wrapper,
            NULL);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    *outputBufferLenPtr = (uint16_t) olen;

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _sign(
                mbedtls_pk_context* const   pkCtxPtr,
        const   uint8_t*            const   privateKeyPtr,
        const   uint16_t                    privateKeySize,
        const   mbedtls_md_type_t           md_alg,
        const   uint8_t*            const   hashBufferPtr,
        const   uint16_t                    hashBufferLen,
                uint8_t*            const   signatureBufferPtr,
        const   uint16_t                    signatureBufferMaxSize,
                uint16_t*           const   signatureBufferLenPtr) {

    size_t sig_len;
    int res;

#if (MBEDTLS_VERSION_MAJOR == 2)
    TOMMROC_UTIL_UNUSED_PARAM(signatureBufferMaxSize);
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _parse_private_key(
                    pkCtxPtr,
                    privateKeyPtr,
                    privateKeySize));

    // Sign
#if (MBEDTLS_VERSION_MAJOR == 2)
    res = mbedtls_pk_sign(
            pkCtxPtr,
            md_alg,
            hashBufferPtr,
            hashBufferLen,
            signatureBufferPtr,
            &sig_len,
            _random_funct_wrapper,
            NULL);
#else
    res = mbedtls_pk_sign(
            pkCtxPtr,
            md_alg,
            hashBufferPtr,
            hashBufferLen,
            signatureBufferPtr,
            signatureBufferMaxSize,
            &sig_len,
            _random_funct_wrapper,
            NULL);
#endif

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    *signatureBufferLenPtr = (uint16_t) sig_len;

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _verify(
                mbedtls_pk_context* const   pkCtxPtr,
        const   uint8_t*            const   publicKeyPtr,
        const   uint16_t                    publicKeySize,
        const   mbedtls_md_type_t           md_alg,
        const   uint8_t*            const   hashBufferPtr,
        const   uint16_t                    hashBufferLen,
        const   uint8_t*            const   signatureBufferPtr,
        const   uint16_t                    signatureBufferLen) {

    int res;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _parse_public_key(
                    pkCtxPtr,
                    publicKeyPtr,
                    publicKeySize));

    // Verify
    res = mbedtls_pk_verify(
            pkCtxPtr,
            md_alg,
            hashBufferPtr,
            hashBufferLen,
            signatureBufferPtr,
            signatureBufferLen);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateRSAESP32WrapperInit(mbedtls_pk_context* const pkCtxPtr) {

    TOMMROC_ASSERT_NOT_NULL(pkCtxPtr);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(pkCtxPtr);

    _pk_ctx_ptr = pkCtxPtr;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateRSAESP32WrapperClose(void) {

    _pk_ctx_ptr = NULL;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateRSAESP32WrapperGenKeypair(
        const   tommRoC_crypto_rsa_encoding_enum_t          encodingMode,
        const   tommRoC_crypto_rsa_hash_enum_t              hashType,
        const   tommRoC_crypto_rsa_key_size_enum_t          keySize,
                uint8_t*                            const   privateKeyPtr,
        const   uint16_t                                    privateKeyMaxSize,
                uint16_t*                           const   privateKeyLenPtr,
                uint8_t*                            const   publicKeyPtr,
        const   uint16_t                                    publicKeyMaxSize,
                uint16_t*                           const   publicKeyLenPtr) {

    mbedtls_pk_context* pkCtxPtr;
    tommRoC_err_enum_t res;

    pkCtxPtr = _pk_ctx_ptr;

    mbedtls_pk_init(pkCtxPtr);

    // NOTE: operation can use some time to compute.
    tommRoCOsDisableWDT();

    res = _gen_keypair(
            pkCtxPtr,
            _tommRoC_rsa_encoding_to_mbedtls_rsa_encoding(encodingMode),
            _tommRoC_rsa_hash_to_mbedtls_rsa_hash(hashType),
            _get_key_size_bit(keySize),
            privateKeyPtr,
            privateKeyMaxSize,
            privateKeyLenPtr,
            publicKeyPtr,
            publicKeyMaxSize,
            publicKeyLenPtr);

    tommRoCOsEnableWDT();

    mbedtls_pk_free(pkCtxPtr);

    return res;
}

tommRoC_err_enum_t tommRoCSwTemplateRSAESP32WrapperEncrypt(
        const   uint8_t*                            const   publicKeyPtr,
        const   uint16_t                                    publicKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr,
        const   uint16_t                                    outputBufferMaxSize,
                uint16_t*                           const   outputBufferLenPtr) {

    mbedtls_pk_context* pkCtxPtr;
    tommRoC_err_enum_t res;

    pkCtxPtr = _pk_ctx_ptr;

    mbedtls_pk_init(pkCtxPtr);

    // NOTE: operation can use some time to compute.
    tommRoCOsDisableWDT();

    res = _encrypt(
            pkCtxPtr,
            publicKeyPtr,
            publicKeySize,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr,
            outputBufferMaxSize,
            outputBufferLenPtr);

    tommRoCOsEnableWDT();

    mbedtls_pk_free(pkCtxPtr);

    return res;
}

tommRoC_err_enum_t tommRoCSwTemplateRSAESP32WrapperDecrypt(
        const   uint8_t*                            const   privateKeyPtr,
        const   uint16_t                                    privateKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr,
        const   uint16_t                                    outputBufferMaxSize,
                uint16_t*                           const   outputBufferLenPtr) {

    mbedtls_pk_context* pkCtxPtr;
    tommRoC_err_enum_t res;

    pkCtxPtr = _pk_ctx_ptr;

    mbedtls_pk_init(pkCtxPtr);

    // NOTE: operation can use some time to compute.
    tommRoCOsDisableWDT();

    res = _decrypt(
            pkCtxPtr,
            privateKeyPtr,
            privateKeySize,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr,
            outputBufferMaxSize,
            outputBufferLenPtr);

    tommRoCOsEnableWDT();

    mbedtls_pk_free(pkCtxPtr);

    return res;
}

tommRoC_err_enum_t tommRoCSwTemplateRSAESP32WrapperSign(
        const   uint8_t*                            const   privateKeyPtr,
        const   uint16_t                                    privateKeySize,
        const   tommRoC_crypto_rsa_hash_enum_t              hashType,
        const   uint8_t*                            const   hashBufferPtr,
        const   uint16_t                                    hashBufferLen,
                uint8_t*                            const   signatureBufferPtr,
        const   uint16_t                                    signatureBufferMaxSize,
                uint16_t*                           const   signatureBufferLenPtr) {

    mbedtls_pk_context* pkCtxPtr;
    tommRoC_err_enum_t res;

    pkCtxPtr = _pk_ctx_ptr;

    mbedtls_pk_init(pkCtxPtr);

    // NOTE: operation can use some time to compute.
    tommRoCOsDisableWDT();

    res = _sign(
            pkCtxPtr,
            privateKeyPtr,
            privateKeySize,
            _tommRoC_rsa_hash_to_mbedtls_rsa_hash(hashType),
            hashBufferPtr,
            hashBufferLen,
            signatureBufferPtr,
            signatureBufferMaxSize,
            signatureBufferLenPtr);

    tommRoCOsEnableWDT();

    mbedtls_pk_free(pkCtxPtr);

    // Check for buffer overflow
    // TODO: need to find a way to check before signing.
    TOMMROC_ASSERT_LESS_OR_EQUALS_THAN(*signatureBufferLenPtr, signatureBufferMaxSize);
    TOMMROC_PARAM_CHECK_ON_TEST_RETURN_ERR(*signatureBufferLenPtr, >, signatureBufferMaxSize);

    return res;
}

tommRoC_err_enum_t tommRoCSwTemplateRSAESP32WrapperVerify(
        const   uint8_t*                            const   publicKeyPtr,
        const   uint16_t                                    publicKeySize,
        const   tommRoC_crypto_rsa_hash_enum_t              hashType,
        const   uint8_t*                            const   hashBufferPtr,
        const   uint16_t                                    hashBufferLen,
        const   uint8_t*                            const   signatureBufferPtr,
        const   uint16_t                                    signatureBufferLen) {

    mbedtls_pk_context* pkCtxPtr;
    tommRoC_err_enum_t res;

    pkCtxPtr = _pk_ctx_ptr;

    mbedtls_pk_init(pkCtxPtr);

    // NOTE: operation can use some time to compute.
    tommRoCOsDisableWDT();

    res = _verify(
            pkCtxPtr,
            publicKeyPtr,
            publicKeySize,
            _tommRoC_rsa_hash_to_mbedtls_rsa_hash(hashType),
            hashBufferPtr,
            hashBufferLen,
            signatureBufferPtr,
            signatureBufferLen);

    tommRoCOsEnableWDT();

    mbedtls_pk_free(pkCtxPtr);

    return res;
}

#endif
