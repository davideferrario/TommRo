
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "crypto/tommRoCTemplateCryptoAES.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#include "crypto/env/esp32/aes/wrapper/tommRoCTemplateCryptoAESWrapper.h"

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
            TOMMRO_C_CRYPTO_AES_KEY_192_BIT_SUPPORTED_PROP,
            TOMMRO_C_CRYPTO_AES_KEY_256_BIT_SUPPORTED_PROP,
    };
    uint8_t i;

    for (i = 0; i < TOMMROC_UTIL_ARR_EAMOUNT(supportedKeySize); ++i) {
        TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoAESSetProp(supportedKeySize[i], &isSupported));
    }

    return TOMMRO_C_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateCryptoAESStart(void) {

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCCryptoAES_CBC_InitEnv(
                    tommRoCTemplateCryptoAESWrapper_CBC_Encrypt,
                    tommRoCTemplateCryptoAESWrapper_CBC_Decrypt,
                    true));
#endif

#if defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCCryptoAES_ECB_InitEnv(
                    tommRoCTemplateCryptoAESWrapper_ECB_Encrypt,
                    tommRoCTemplateCryptoAESWrapper_ECB_Decrypt));
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_set_supported_key_size_status(true));

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateCryptoAESStop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_set_supported_key_size_status(false));

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoAES_CBC_CloseEnv());
#endif

#if defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoAES_ECB_CloseEnv());
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

#endif
