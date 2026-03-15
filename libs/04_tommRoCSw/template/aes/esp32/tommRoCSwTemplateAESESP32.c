
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

#include "aes/esp32/wrapper/tommRoCSwTemplateAESESP32Wrapper.h"
#include "memory/esp32/core/tommRoCSwTemplateMemoryESP32Core.h"

#include "mbedtls/aes.h"

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
static mbedtls_aes_context _aes_ctx;

static bool _is_low_level_key_level_enabled = false;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_sw_err_enum_t _set_supported_key_size_status(const bool isSupported) {

    const tommRoC_crypto_aes_prop_enum_t supportedKeySize[] = {
            TOMMRO_C_CRYPTO_AES_KEY_128_BIT_SUPPORTED_PROP,
            TOMMRO_C_CRYPTO_AES_KEY_192_BIT_SUPPORTED_PROP,
            TOMMRO_C_CRYPTO_AES_KEY_256_BIT_SUPPORTED_PROP,
    };
    uint8_t i;

    for (i = 0; i < TOMMROC_UTIL_ARR_EAMOUNT(supportedKeySize); ++i) {

        TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
                tommRoCCryptoAESSetProp(
                        supportedKeySize[i],
                        &isSupported),
                TOMMRO_C_SW_LOW_LEVEL_ERR);
    }

    return TOMMRO_C_SW_ERR_SUCCESS;
}

static tommRoC_sw_err_enum_t _enable_supported_key_size(void) {

    if (_is_low_level_key_level_enabled) {
        return TOMMRO_C_SW_ERR_SUCCESS;
    }

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_set_supported_key_size_status(true));

    _is_low_level_key_level_enabled = true;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

static tommRoC_sw_err_enum_t _disable_supported_key_size(void) {

    if (!_is_low_level_key_level_enabled) {
        return TOMMRO_C_SW_ERR_SUCCESS;
    }

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_set_supported_key_size_status(false));

    _is_low_level_key_level_enabled = false;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwAES_CBC_Start(void) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateAESESP32Wrapper_CBC_Init(&_aes_ctx));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoAES_CBC_InitEnv(
                    tommRoCSwTemplateAESESP32Wrapper_CBC_Encrypt,
                    tommRoCSwTemplateAESESP32Wrapper_CBC_Decrypt,
                    true),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_enable_supported_key_size());

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwAES_ECB_Start(void) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateAESESP32Wrapper_ECB_Init(&_aes_ctx));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoAES_ECB_InitEnv(
                    tommRoCSwTemplateAESESP32Wrapper_ECB_Encrypt,
                    tommRoCSwTemplateAESESP32Wrapper_ECB_Decrypt),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_enable_supported_key_size());

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwAES_CBC_Stop(void) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_disable_supported_key_size());

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoAES_CBC_CloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateAESESP32Wrapper_CBC_Close());

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwAES_ECB_Stop(void) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_disable_supported_key_size());

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoAES_ECB_CloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateAESESP32Wrapper_ECB_Close());

    return TOMMRO_C_SW_ERR_SUCCESS;
}

#endif
