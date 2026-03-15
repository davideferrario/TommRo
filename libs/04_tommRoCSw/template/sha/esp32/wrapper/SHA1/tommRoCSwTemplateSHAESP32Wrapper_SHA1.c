
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateSHAESP32Wrapper_SHA1.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "mbedtls/version.h"

#include "mbedtls/sha1.h"

#if (MBEDTLS_VERSION_MAJOR > 2)
#include "mbedtls/compat-2.x.h"
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
static mbedtls_sha1_context* _sha_ctx_ptr = NULL;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _perform(
                mbedtls_sha1_context*   const   shaCtxPtr,
        const   uint8_t*                const   inputBufferPtr,
        const   uint16_t                        inputBufferLen,
                uint8_t*                const   outputBufferPtr) {

    int res;

    res = mbedtls_sha1_starts_ret(shaCtxPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    res = mbedtls_sha1_update_ret(shaCtxPtr, inputBufferPtr, inputBufferLen);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    res = mbedtls_sha1_finish_ret(shaCtxPtr, outputBufferPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA1_Init(mbedtls_sha1_context* const shaCtxPtr) {

    TOMMROC_ASSERT_NOT_NULL(shaCtxPtr);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(shaCtxPtr);

    _sha_ctx_ptr = shaCtxPtr;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA1_Close(void) {

    _sha_ctx_ptr = NULL;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA1_SHA1Perform(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr) {

    mbedtls_sha1_context* shaCtxPtr;
    tommRoC_err_enum_t res;

    shaCtxPtr = _sha_ctx_ptr;

    mbedtls_sha1_init(shaCtxPtr);

    res = _perform(
            shaCtxPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);

    mbedtls_sha1_free(shaCtxPtr);

    return res;
}

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA1_SHA1Start(
                void*       const   shaCtxPtr) {

    mbedtls_sha1_context* sha1CtxPtr = (mbedtls_sha1_context*) shaCtxPtr;

    int res;

    mbedtls_sha1_init(sha1CtxPtr);

    res = mbedtls_sha1_starts_ret(sha1CtxPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA1_SHA1Update(
                void*       const   shaCtxPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen) {

    mbedtls_sha1_context* sha1CtxPtr = (mbedtls_sha1_context*) shaCtxPtr;

    int res;

    res = mbedtls_sha1_update_ret(sha1CtxPtr, inputBufferPtr, inputBufferLen);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA1_SHA1Finish(
                void*       const   shaCtxPtr,
                uint8_t*    const   outputBufferPtr) {

    mbedtls_sha1_context* sha1CtxPtr = (mbedtls_sha1_context*) shaCtxPtr;

    int res;

    res = mbedtls_sha1_finish_ret(sha1CtxPtr, outputBufferPtr);

    mbedtls_sha1_free(sha1CtxPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

#endif
