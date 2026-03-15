
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

#include "sha/esp32/wrapper/tommRoCSwTemplateSHAESP32Wrapper.h"
#include "memory/esp32/core/tommRoCSwTemplateMemoryESP32Core.h"

#include "mbedtls/sha1.h"
#include "mbedtls/sha256.h"
#include "mbedtls/sha512.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
TOMMROC_SCTA_SIZE_OF_EQUALS(tommRoC_sw_sha_sha1_context_t,      mbedtls_sha1_context);
TOMMROC_SCTA_SIZE_OF_EQUALS(tommRoC_sw_sha_sha224_context_t,    mbedtls_sha256_context);
TOMMROC_SCTA_SIZE_OF_EQUALS(tommRoC_sw_sha_sha256_context_t,    mbedtls_sha256_context);
TOMMROC_SCTA_SIZE_OF_EQUALS(tommRoC_sw_sha_sha384_context_t,    mbedtls_sha512_context);
TOMMROC_SCTA_SIZE_OF_EQUALS(tommRoC_sw_sha_sha512_context_t,    mbedtls_sha512_context);

/*******************************************************************************
 * local vars
 ******************************************************************************/
static mbedtls_sha1_context     _sha1_ctx;
static mbedtls_sha256_context   _sha256_ctx;
static mbedtls_sha512_context   _sha512_ctx;

/*******************************************************************************
 * local functions
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwSHA1Start(void) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateSHAESP32Wrapper_SHA1_Init(&_sha1_ctx));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoSHA1InitEnv(
                tommRoCSwTemplateSHAESP32Wrapper_SHA1_SHA1Perform,
                tommRoCSwTemplateSHAESP32Wrapper_SHA1_SHA1Start,
                tommRoCSwTemplateSHAESP32Wrapper_SHA1_SHA1Update,
                tommRoCSwTemplateSHAESP32Wrapper_SHA1_SHA1Finish),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwSHA224Start(void) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateSHAESP32Wrapper_SHA256_Init(&_sha256_ctx));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoSHA224InitEnv(
                tommRoCSwTemplateSHAESP32Wrapper_SHA256_SHA224Perform,
                tommRoCSwTemplateSHAESP32Wrapper_SHA256_SHA224Start,
                tommRoCSwTemplateSHAESP32Wrapper_SHA256_SHA224_256Update,
                tommRoCSwTemplateSHAESP32Wrapper_SHA256_SHA224_256Finish),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwSHA256Start(void) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateSHAESP32Wrapper_SHA256_Init(&_sha256_ctx));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoSHA256InitEnv(
                tommRoCSwTemplateSHAESP32Wrapper_SHA256_SHA256Perform,
                tommRoCSwTemplateSHAESP32Wrapper_SHA256_SHA256Start,
                tommRoCSwTemplateSHAESP32Wrapper_SHA256_SHA224_256Update,
                tommRoCSwTemplateSHAESP32Wrapper_SHA256_SHA224_256Finish),
            TOMMRO_C_SW_LOW_LEVEL_ERR);
    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwSHA384Start(void) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateSHAESP32Wrapper_SHA512_Init(&_sha512_ctx));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoSHA384InitEnv(
                tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA384Perform,
                tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA384Start,
                tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA384_512Update,
                tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA384_512Finish),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwSHA512Start(void) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateSHAESP32Wrapper_SHA512_Init(&_sha512_ctx));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoSHA512InitEnv(
                tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA512Perform,
                tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA512Start,
                tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA384_512Update,
                tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA384_512Finish),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwSHA1Stop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoSHA1CloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateSHAESP32Wrapper_SHA1_Close());

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwSHA224Stop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoSHA224CloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateSHAESP32Wrapper_SHA256_Close());

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwSHA256Stop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoSHA256CloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateSHAESP32Wrapper_SHA256_Close());

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwSHA384Stop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoSHA384CloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateSHAESP32Wrapper_SHA512_Close());

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwSHA512Stop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoSHA512CloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateSHAESP32Wrapper_SHA512_Close());

    return TOMMRO_C_SW_ERR_SUCCESS;
}

#endif
