
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "crypto/tommRoCTemplateCryptoAES.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_IS_USED__)

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__) || defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)

#include "TOMMROC.h"

#if defined (AES_COUNT) && AES_COUNT

#include "em_aes.h"
#include "em_cmu.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef void (*__decrypt_key_funct_t__)(uint8_t *out, const uint8_t *in);
typedef void (*__cbc_crypt_funct_t__)(uint8_t *out, const uint8_t *in, unsigned int len, const uint8_t *key, const uint8_t *iv, bool encrypt);
typedef void (*__ecb_crypt_funct_t__)(uint8_t *out, const uint8_t *in, unsigned int len, const uint8_t *key, bool encrypt);

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (AES_CTRL_AES256)
static uint8_t _decrypt_key_buff[32];
#else
static uint8_t _decrypt_key_buff[16];
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _set_supported_key_size_status(const bool isSupported) {

    const tommRoC_crypto_aes_prop_enum_t supportedKeySize[] = {

            TOMMRO_C_CRYPTO_AES_KEY_128_BIT_SUPPORTED_PROP,

#if defined (AES_CTRL_AES256)
            TOMMRO_C_CRYPTO_AES_KEY_256_BIT_SUPPORTED_PROP,
#endif

    };
    uint8_t i;

    for (i = 0; i < TOMMROC_UTIL_ARR_EAMOUNT(supportedKeySize); ++i) {
        TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoAESSetProp(supportedKeySize[i], &isSupported));
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static __decrypt_key_funct_t__ _get_decrypt_key_funct(const tommRoC_crypto_aes_key_size_enum_t aesKeySize) {

    if (TOMMRO_C_CRYPTO_AES_KEY_128_BIT == aesKeySize) {
        return AES_DecryptKey128;
    }

#if defined (AES_CTRL_AES256)
    else if (TOMMRO_C_CRYPTO_AES_KEY_256_BIT == aesKeySize) {
        return AES_DecryptKey256;
    }
#endif

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    return NULL;
}

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__)
static __cbc_crypt_funct_t__ _get_cbc_crypt_funct(const tommRoC_crypto_aes_key_size_enum_t aesKeySize) {

    if (TOMMRO_C_CRYPTO_AES_KEY_128_BIT == aesKeySize) {
        return AES_CBC128;
    }

#if defined (AES_CTRL_AES256)
    else if (TOMMRO_C_CRYPTO_AES_KEY_256_BIT == aesKeySize) {
        return AES_CBC256;
    }
#endif

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    return NULL;
}

static tommRoC_err_enum_t _CBC_encrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
                uint8_t*                            const   aesIVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    __cbc_crypt_funct_t__ aesCBCFunctPtr;

    aesCBCFunctPtr = _get_cbc_crypt_funct(aesKeySize);

    CMU_ClockEnable(cmuClock_AES, true);
    aesCBCFunctPtr(outputBufferPtr, inputBufferPtr, inputBufferLen, aesKeyPtr, aesIVPtr, true);
    CMU_ClockEnable(cmuClock_AES, false);

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _CBC_decrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
                uint8_t*                            const   aesIVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    __decrypt_key_funct_t__ aesDecryptKeyFunctPtr;
    __cbc_crypt_funct_t__   aesCBCFunctPtr;

    aesDecryptKeyFunctPtr   = _get_decrypt_key_funct(aesKeySize);
    aesCBCFunctPtr          = _get_cbc_crypt_funct(aesKeySize);

    CMU_ClockEnable(cmuClock_AES, true);
    aesDecryptKeyFunctPtr(_decrypt_key_buff, aesKeyPtr);
    aesCBCFunctPtr(outputBufferPtr, inputBufferPtr, inputBufferLen, _decrypt_key_buff, aesIVPtr, false);
    CMU_ClockEnable(cmuClock_AES, false);

    return TOMMRO_C_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
static __ecb_crypt_funct_t__ _get_ecb_crypt_funct(const tommRoC_crypto_aes_key_size_enum_t aesKeySize) {

    if (TOMMRO_C_CRYPTO_AES_KEY_128_BIT == aesKeySize) {
        return AES_ECB128;
    }

#if defined (AES_CTRL_AES256)
    else if (TOMMRO_C_CRYPTO_AES_KEY_256_BIT == aesKeySize) {
        return AES_ECB256;
    }
#endif

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    return NULL;
}

static tommRoC_err_enum_t _ECB_encrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    __ecb_crypt_funct_t__ aesECBFunctPtr;

    aesECBFunctPtr = _get_ecb_crypt_funct(aesKeySize);

    CMU_ClockEnable(cmuClock_AES, true);
    aesECBFunctPtr(outputBufferPtr, inputBufferPtr, inputBufferLen, aesKeyPtr, true);
    CMU_ClockEnable(cmuClock_AES, false);

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t _ECB_decrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    __decrypt_key_funct_t__ aesDecryptKeyFunctPtr;
    __ecb_crypt_funct_t__   aesECBFunctPtr;

    aesDecryptKeyFunctPtr   = _get_decrypt_key_funct(aesKeySize);
    aesECBFunctPtr           = _get_ecb_crypt_funct(aesKeySize);

    CMU_ClockEnable(cmuClock_AES, true);
    aesDecryptKeyFunctPtr(_decrypt_key_buff, aesKeyPtr);
    aesECBFunctPtr(outputBufferPtr, inputBufferPtr, inputBufferLen, _decrypt_key_buff, false);
    CMU_ClockEnable(cmuClock_AES, false);

    return TOMMRO_C_ERR_SUCCESS;
}
#endif

#endif

#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateCryptoAESStart(void) {

#if defined (AES_COUNT) && AES_COUNT &&   \
    (defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__) || defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__))

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoAES_CBC_InitEnv(_CBC_encrypt, _CBC_decrypt, false));
#endif

#if defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoAES_ECB_InitEnv(_ECB_encrypt, _ECB_decrypt));
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_set_supported_key_size_status(true));

    return TOMMRO_C_ERR_SUCCESS;

#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateCryptoAESStop(void) {

#if defined (AES_COUNT) && AES_COUNT &&   \
    (defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__) || defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__))

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoAES_CBC_CloseEnv());
#endif

#if defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoAES_ECB_CloseEnv());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_set_supported_key_size_status(false));

    return TOMMRO_C_ERR_SUCCESS;

#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

#endif
