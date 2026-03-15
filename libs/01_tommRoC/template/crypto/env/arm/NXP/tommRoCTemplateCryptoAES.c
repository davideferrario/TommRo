
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "crypto/tommRoCTemplateCryptoAES.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__) || defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)

#include "TOMMROC.h"

#if defined (FSL_FEATURE_SOC_LTC_COUNT) && FSL_FEATURE_SOC_LTC_COUNT
#include "fsl_ltc.h"

#include <stdbool.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _set_supported_key_size_status(const bool isSupported) {

    const tommRoC_crypto_aes_prop_enum_t supportedKeySize[] = {

            TOMMRO_C_CRYPTO_AES_KEY_128_BIT_SUPPORTED_PROP,

#if defined (FSL_FEATURE_LTC_HAS_AES192) && FSL_FEATURE_LTC_HAS_AES192
            TOMMRO_C_CRYPTO_AES_KEY_192_BIT_SUPPORTED_PROP,
#endif

#if defined (FSL_FEATURE_LTC_HAS_AES256) && FSL_FEATURE_LTC_HAS_AES256
            TOMMRO_C_CRYPTO_AES_KEY_256_BIT_SUPPORTED_PROP,
#endif

    };
    uint8_t i;

    for (i = 0; i < TOMMROC_UTIL_ARR_EAMOUNT(supportedKeySize); ++i) {
        TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoAESSetProp(supportedKeySize[i], &isSupported));
    }

    return TOMMRO_C_ERR_SUCCESS;
}

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__)
static tommRoC_err_enum_t _CBC_encrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
                uint8_t*                            const   aesIVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    TOMMROC_CTA_EQUALS(LTC_AES_IV_SIZE, TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE);

    status_t res;

    res = LTC_AES_EncryptCbc(
            LTC0,
            inputBufferPtr,
            outputBufferPtr,
            inputBufferLen,
            aesIVPtr,
            aesKeyPtr,
            tommRoCCryptoAESKeySize(aesKeySize) / 8);

    if (kStatus_Success != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _CBC_decrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
                uint8_t*                            const   aesIVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    TOMMROC_CTA_EQUALS(LTC_AES_IV_SIZE, TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE);

    status_t res;

    res = LTC_AES_DecryptCbc(
            LTC0,
            inputBufferPtr,
            outputBufferPtr,
            inputBufferLen,
            aesIVPtr,
            aesKeyPtr,
            tommRoCCryptoAESKeySize(aesKeySize) / 8,
            kLTC_EncryptKey);

    if (kStatus_Success != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
static tommRoC_err_enum_t _ECB_encrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    status_t res;

    res = LTC_AES_EncryptEcb(
            LTC0,
            inputBufferPtr,
            outputBufferPtr,
            inputBufferLen,
            aesKeyPtr,
            tommRoCCryptoAESKeySize(aesKeySize) / 8);

    if (kStatus_Success != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t _ECB_decrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    status_t res;

    res = LTC_AES_DecryptEcb(
            LTC0,
            inputBufferPtr,
            outputBufferPtr,
            inputBufferLen,
            aesKeyPtr,
            tommRoCCryptoAESKeySize(aesKeySize) / 8,
            kLTC_EncryptKey);

    if (kStatus_Success != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}
#endif

#endif

#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateCryptoAESStart(void) {

#if defined (FSL_FEATURE_SOC_LTC_COUNT) && FSL_FEATURE_SOC_LTC_COUNT && \
    (defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__) || defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__))

    LTC_Init(LTC0);

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

#if defined (FSL_FEATURE_SOC_LTC_COUNT) && FSL_FEATURE_SOC_LTC_COUNT && \
    (defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__) || defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__))

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoAES_CBC_CloseEnv());
#endif

#if defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoAES_ECB_CloseEnv());
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_set_supported_key_size_status(false));

    LTC_Deinit(LTC0);

    return TOMMRO_C_ERR_SUCCESS;

#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

#endif
