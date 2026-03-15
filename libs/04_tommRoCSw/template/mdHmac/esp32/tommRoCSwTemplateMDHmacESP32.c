
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

#include "mdHmac/esp32/wrapper/tommRoCSwTemplateMDHmacESP32Wrapper.h"
#include "memory/esp32/core/tommRoCSwTemplateMemoryESP32Core.h"

#include "mbedtls/version.h"

#if (MBEDTLS_VERSION_MAJOR == 2)
#include "mbedtls/md_internal.h"
#elif (MBEDTLS_VERSION_MAJOR == 3)
#endif

#include "mbedtls/sha1.h"
#include "mbedtls/sha256.h"
#include "mbedtls/sha512.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static mbedtls_md_context_t _md_ctx;

/*******************************************************************************
 * local functions
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwMDHmacSHA1Start(void) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMDHmacESP32Wrapper_SHA1_Init(&_md_ctx));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoMDHmacSHA1InitEnv(tommRoCSwTemplateMDHmacESP32Wrapper_SHA1_Perform),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwMDHmacSHA256Start(void) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMDHmacESP32Wrapper_SHA256_Init(&_md_ctx));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoMDHmacSHA256InitEnv(tommRoCSwTemplateMDHmacESP32Wrapper_SHA256_Perform),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwMDHmacSHA512Start(void) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMDHmacESP32Wrapper_SHA512_Init(&_md_ctx));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoMDHmacSHA512InitEnv(tommRoCSwTemplateMDHmacESP32Wrapper_SHA512_Perform),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    return TOMMRO_C_SW_ERR_SUCCESS;
}


tommRoC_sw_err_enum_t tommRoCSwMDHmacSHA1Stop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoMDHmacSHA1CloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMDHmacESP32Wrapper_SHA1_Close());

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwMDHmacSHA256Stop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoMDHmacSHA256CloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMDHmacESP32Wrapper_SHA256_Close());

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwMDHmacSHA512Stop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoMDHmacSHA512CloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMDHmacESP32Wrapper_SHA512_Close());

    return TOMMRO_C_SW_ERR_SUCCESS;
}

#endif
