
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

#include "md/esp32/wrapper/tommRoCSwTemplateMDESP32Wrapper.h"
#include "memory/esp32/core/tommRoCSwTemplateMemoryESP32Core.h"

#include "mbedtls/version.h"

#if (MBEDTLS_VERSION_MAJOR == 2)
#include "mbedtls/md2.h"
#include "mbedtls/md4.h"
#endif
#include "mbedtls/md5.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if (MBEDTLS_VERSION_MAJOR == 2)
static mbedtls_md2_context  _md2_ctx;
static mbedtls_md4_context  _md4_ctx;
#endif
static mbedtls_md5_context  _md5_ctx;

/*******************************************************************************
 * local functions
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwMD2Start(void) {

#if (MBEDTLS_VERSION_MAJOR == 2)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMDESP32Wrapper_MD2_Init(&_md2_ctx));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoMD2InitEnv(tommRoCSwTemplateMDESP32Wrapper_MD2_MD2Perform),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    return TOMMRO_C_SW_ERR_SUCCESS;
#else
    return TOMMRO_C_SW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_sw_err_enum_t tommRoCSwMD4Start(void) {

#if (MBEDTLS_VERSION_MAJOR == 2)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMDESP32Wrapper_MD4_Init(&_md4_ctx));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoMD4InitEnv(tommRoCSwTemplateMDESP32Wrapper_MD4_MD4Perform),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    return TOMMRO_C_SW_ERR_SUCCESS;
#else
    return TOMMRO_C_SW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_sw_err_enum_t tommRoCSwMD5Start(void) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMDESP32Wrapper_MD5_Init(&_md5_ctx));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoMD5InitEnv(tommRoCSwTemplateMDESP32Wrapper_MD5_MD5Perform),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    return TOMMRO_C_SW_ERR_SUCCESS;
}


tommRoC_sw_err_enum_t tommRoCSwMD2Stop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoMD2CloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

#if (MBEDTLS_VERSION_MAJOR == 2)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMDESP32Wrapper_MD2_Close());
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwMD4Stop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoMD4CloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

#if (MBEDTLS_VERSION_MAJOR == 2)
    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMDESP32Wrapper_MD4_Close());
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwMD5Stop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoMD5CloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMDESP32Wrapper_MD5_Close());

    return TOMMRO_C_SW_ERR_SUCCESS;
}

#endif
