
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

#include "rsa/esp32/wrapper/tommRoCSwTemplateRSAESP32Wrapper.h"
#include "memory/esp32/core/tommRoCSwTemplateMemoryESP32Core.h"

#include "mbedtls/pk.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static mbedtls_pk_context  _pk_ctx;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_sw_err_enum_t _check_tommRoC_rnd_is_init(void) {

    bool tommRoCRNDIsInit;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCCryptoRNDGetProp(TOMMRO_C_CRYPTO_RND_IS_INIT_PROP, &tommRoCRNDIsInit));

    if (!tommRoCRNDIsInit) {
        return TOMMRO_C_SW_ENVIRONMENT_NOT_INIT_ERR;
    }

    return TOMMRO_C_SW_ERR_SUCCESS;
}

static tommRoC_sw_err_enum_t _rsa_start(
        const   tommRoC_crypto_rsa_environment_config_t*    const   rsaEnvConfigPtr) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_check_tommRoC_rnd_is_init());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateRSAESP32WrapperInit(&_pk_ctx));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoRSAInitEnv(rsaEnvConfigPtr),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    return TOMMRO_C_SW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwRSAStartMinimum(void) {

    const tommRoC_crypto_rsa_environment_config_t rsaEnvConfig = {
        /*.genKeypair */    tommRoCSwTemplateRSAESP32WrapperGenKeypair,
        /*.encrypt */       tommRoCSwTemplateRSAESP32WrapperEncrypt,
        /*.decrypt */       tommRoCSwTemplateRSAESP32WrapperDecrypt,
        /*.sign */          NULL,
        /*.verify */        NULL,
    };

    return _rsa_start(&rsaEnvConfig);
}

tommRoC_sw_err_enum_t tommRoCSwRSAStartMinimumPlusSign(void) {

    const tommRoC_crypto_rsa_environment_config_t rsaEnvConfig = {
        /*.genKeypair */    tommRoCSwTemplateRSAESP32WrapperGenKeypair,
        /*.encrypt */       tommRoCSwTemplateRSAESP32WrapperEncrypt,
        /*.decrypt */       tommRoCSwTemplateRSAESP32WrapperDecrypt,
        /*.sign */          tommRoCSwTemplateRSAESP32WrapperSign,
        /*.verify */        NULL,
    };

    return _rsa_start(&rsaEnvConfig);
}

tommRoC_sw_err_enum_t tommRoCSwRSAStartMinimumPlusVerify(void) {

    const tommRoC_crypto_rsa_environment_config_t rsaEnvConfig = {
        /*.genKeypair */    tommRoCSwTemplateRSAESP32WrapperGenKeypair,
        /*.encrypt */       tommRoCSwTemplateRSAESP32WrapperEncrypt,
        /*.decrypt */       tommRoCSwTemplateRSAESP32WrapperDecrypt,
        /*.sign */          NULL,
        /*.verify */        tommRoCSwTemplateRSAESP32WrapperVerify,
    };

    return _rsa_start(&rsaEnvConfig);
}

tommRoC_sw_err_enum_t tommRoCSwRSAStart(void) {

    const tommRoC_crypto_rsa_environment_config_t rsaEnvConfig = {
        /*.genKeypair */    tommRoCSwTemplateRSAESP32WrapperGenKeypair,
        /*.encrypt */       tommRoCSwTemplateRSAESP32WrapperEncrypt,
        /*.decrypt */       tommRoCSwTemplateRSAESP32WrapperDecrypt,
        /*.sign */          tommRoCSwTemplateRSAESP32WrapperSign,
        /*.verify */        tommRoCSwTemplateRSAESP32WrapperVerify,
    };

    return _rsa_start(&rsaEnvConfig);
}

tommRoC_sw_err_enum_t tommRoCSwRSAStop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoRSACloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateRSAESP32WrapperClose());

    return TOMMRO_C_SW_ERR_SUCCESS;
}

#endif
