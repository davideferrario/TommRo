
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateSHAESP32Wrapper_SHA256.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "mbedtls/version.h"

#include "mbedtls/sha256.h"

#if (MBEDTLS_VERSION_MAJOR > 2)
#include "mbedtls/compat-2.x.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __MBEDTLS_SHA256_USE_SHA224__           (1)
#define __MBEDTLS_SHA256_USE_SHA256__           (0)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static mbedtls_sha256_context* _sha_ctx_ptr = NULL;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _perform(
                mbedtls_sha256_context* const   shaCtxPtr,
        const   uint8_t*                const   inputBufferPtr,
        const   uint16_t                        inputBufferLen,
                uint8_t*                const   outputBufferPtr,
        const   int                             is224) {

    int res;

    res = mbedtls_sha256_starts_ret(shaCtxPtr, is224);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    res = mbedtls_sha256_update_ret(shaCtxPtr, inputBufferPtr, inputBufferLen);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    res = mbedtls_sha256_finish_ret(shaCtxPtr, outputBufferPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _sha256_perform(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr,
        const   int                 is224) {

    mbedtls_sha256_context* shaCtxPtr;
    tommRoC_err_enum_t res;

    shaCtxPtr = _sha_ctx_ptr;

    mbedtls_sha256_init(shaCtxPtr);

    res = _perform(
            shaCtxPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr,
            is224);

    mbedtls_sha256_free(shaCtxPtr);

    return res;
}

static tommRoC_err_enum_t _sha256_start(
                void*       const   shaCtxPtr,
        const   int                 is224) {

    mbedtls_sha256_context* sha256CtxPtr = (mbedtls_sha256_context*) shaCtxPtr;

    int res;

    mbedtls_sha256_init(sha256CtxPtr);

    res = mbedtls_sha256_starts_ret(sha256CtxPtr, is224);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA256_Init(mbedtls_sha256_context* const shaCtxPtr) {

    TOMMROC_ASSERT_NOT_NULL(shaCtxPtr);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(shaCtxPtr);

    _sha_ctx_ptr = shaCtxPtr;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA256_Close(void) {

    _sha_ctx_ptr = NULL;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA256_SHA224Perform(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr) {

    return _sha256_perform(
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr,
            __MBEDTLS_SHA256_USE_SHA224__);
}

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA256_SHA256Perform(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr) {

    return _sha256_perform(
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr,
            __MBEDTLS_SHA256_USE_SHA256__);
}

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA256_SHA224Start(
                void*       const   shaCtxPtr) {

    return _sha256_start(
            shaCtxPtr,
            __MBEDTLS_SHA256_USE_SHA224__);
}

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA256_SHA256Start(
                void*       const   shaCtxPtr) {

    return _sha256_start(
            shaCtxPtr,
            __MBEDTLS_SHA256_USE_SHA256__);
}

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA256_SHA224_256Update(
                void*       const   shaCtxPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen) {

    mbedtls_sha256_context* sha256CtxPtr = (mbedtls_sha256_context*) shaCtxPtr;

    int res;

    res = mbedtls_sha256_update_ret(sha256CtxPtr, inputBufferPtr, inputBufferLen);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA256_SHA224_256Finish(
                void*       const   shaCtxPtr,
                uint8_t*    const   outputBufferPtr) {

    mbedtls_sha256_context* sha256CtxPtr = (mbedtls_sha256_context*) shaCtxPtr;

    int res;

    res = mbedtls_sha256_finish_ret(sha256CtxPtr, outputBufferPtr);

    mbedtls_sha256_free(sha256CtxPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

#endif
