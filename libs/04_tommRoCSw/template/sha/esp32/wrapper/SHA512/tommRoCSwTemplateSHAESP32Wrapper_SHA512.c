
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateSHAESP32Wrapper_SHA512.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "mbedtls/version.h"

#include "mbedtls/sha512.h"

#if (MBEDTLS_VERSION_MAJOR > 2)
#include "mbedtls/compat-2.x.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __MBEDTLS_SHA512_USE_SHA384__           (1)
#define __MBEDTLS_SHA512_USE_SHA512__           (0)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static mbedtls_sha512_context* _sha_ctx_ptr = NULL;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _perform(
                mbedtls_sha512_context* const   shaCtxPtr,
        const   uint8_t*                const   inputBufferPtr,
        const   uint16_t                        inputBufferLen,
                uint8_t*                const   outputBufferPtr,
        const   int                             is384) {

    int res;

    res = mbedtls_sha512_starts_ret(shaCtxPtr, is384);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    res = mbedtls_sha512_update_ret(shaCtxPtr, inputBufferPtr, inputBufferLen);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    res = mbedtls_sha512_finish_ret(shaCtxPtr, outputBufferPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _sha512_perform(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr,
        const   int                 is384) {

    mbedtls_sha512_context* shaCtxPtr;
    tommRoC_err_enum_t res;

    shaCtxPtr = _sha_ctx_ptr;

    mbedtls_sha512_init(shaCtxPtr);

    res = _perform(
            shaCtxPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr,
            is384);

    mbedtls_sha512_free(shaCtxPtr);

    return res;
}

static tommRoC_err_enum_t _sha512_start(
                void*       const   shaCtxPtr,
        const   int                 is384) {

    mbedtls_sha512_context* sha512CtxPtr = (mbedtls_sha512_context*) shaCtxPtr;

    int res;

    mbedtls_sha512_init(sha512CtxPtr);

    res = mbedtls_sha512_starts_ret(sha512CtxPtr, is384);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA512_Init(mbedtls_sha512_context* const shaCtxPtr) {

    TOMMROC_ASSERT_NOT_NULL(shaCtxPtr);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(shaCtxPtr);

    _sha_ctx_ptr = shaCtxPtr;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA512_Close(void) {

    _sha_ctx_ptr = NULL;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA384Perform(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr) {

    return _sha512_perform(
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr,
            __MBEDTLS_SHA512_USE_SHA384__);
}

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA512Perform(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr) {

    return _sha512_perform(
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr,
            __MBEDTLS_SHA512_USE_SHA512__);
}

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA384Start(
                void*       const   shaCtxPtr) {

    return _sha512_start(
            shaCtxPtr,
            __MBEDTLS_SHA512_USE_SHA384__);
}

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA512Start(
                void*       const   shaCtxPtr) {

    return _sha512_start(
            shaCtxPtr,
            __MBEDTLS_SHA512_USE_SHA512__);
}

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA384_512Update(
                void*       const   shaCtxPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen) {

    mbedtls_sha512_context* sha512CtxPtr = (mbedtls_sha512_context*) shaCtxPtr;

    int res;

    res = mbedtls_sha512_update_ret(sha512CtxPtr, inputBufferPtr, inputBufferLen);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateSHAESP32Wrapper_SHA512_SHA384_512Finish(
                void*       const   shaCtxPtr,
                uint8_t*    const   outputBufferPtr) {

    mbedtls_sha512_context* sha512CtxPtr = (mbedtls_sha512_context*) shaCtxPtr;

    int res;

    res = mbedtls_sha512_finish_ret(sha512CtxPtr, outputBufferPtr);

    mbedtls_sha512_free(sha512CtxPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

#endif
