
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

#include "ssl/esp32/wrapper/tommRoCSwTemplateSSLESP32Wrapper.h"
#include "memory/esp32/core/tommRoCSwTemplateMemoryESP32Core.h"

#include "sdkconfig.h"

#include "mbedtls/version.h"

#if (MBEDTLS_VERSION_MAJOR == 2)
#include "mbedtls/config.h"
#else
#include "mbedtls/mbedtls_config.h"
#endif

#if defined (__TOMMROC_SW_USE_SSL_TEMPLATE__) && !defined (MBEDTLS_KEY_EXCHANGE_PSK_ENABLED)
#error "MBEDTLS_KEY_EXCHANGE_PSK_ENABLED must be enabled - enable in \"Component config->mbedTLS->TLS Key Exchange Methods\""
#endif

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

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwSSLStart(void) {

#if defined (__TOMMROC_SW_USE_SSL_TEMPLATE__)

    tommRoC_crypto_ssl_environment_config_t sslEnvConfig;

    sslEnvConfig.initHandshakeHostFunct = tommRoCSwTemplateSSLESP32WrapperInitHandshakeHost;
    sslEnvConfig.writeFunct             = tommRoCSwTemplateSSLESP32WrapperWrite;
    sslEnvConfig.readFunct              = tommRoCSwTemplateSSLESP32WrapperRead;
    sslEnvConfig.closeNotifyFreeFunct   = tommRoCSwTemplateSSLESP32WrapperCloseNotifyFree;

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoSSLInitEnv(&sslEnvConfig),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    return TOMMRO_C_SW_ERR_SUCCESS;
#else
    return TOMMRO_C_SW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_sw_err_enum_t tommRoCSwSSLStop(void) {

#if defined (__TOMMROC_SW_USE_SSL_TEMPLATE__)
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoSSLCloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    return TOMMRO_C_SW_ERR_SUCCESS;
#else
    return TOMMRO_C_SW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

#endif
