
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateMDHmacESP32Wrapper_SHA256.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "mbedtls/version.h"

#if (MBEDTLS_VERSION_MAJOR == 2)
#include "mbedtls/md_internal.h"
#elif (MBEDTLS_VERSION_MAJOR == 3)
#include "mbedtls/md.h"
#endif

#include "mbedtls/sha256.h"

#include "mbedtls/platform.h"
#include "mbedtls/platform_util.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static mbedtls_md_context_t* _md_ctx_ptr = NULL;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _perform(
                mbedtls_md_context_t*   const   mdCtxPtr,
        const   void*                   const   keyPtr,
        const   uint16_t                        keySize,
        const   void*                   const   inputBufferPtr,
        const   uint16_t                        inputBufferLen,
                void*                   const   outputBufferPtr) {

    int res;

    res = mbedtls_md_hmac_starts(mdCtxPtr, (const unsigned char*) keyPtr, (size_t) keySize);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    res = mbedtls_md_hmac_update(mdCtxPtr, (const unsigned char*) inputBufferPtr, (size_t) inputBufferLen);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    res = mbedtls_md_hmac_finish(mdCtxPtr, (unsigned char*) outputBufferPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateMDHmacESP32Wrapper_SHA256_Init(mbedtls_md_context_t* const mdCtxPtr) {

    TOMMROC_ASSERT_NOT_NULL(mdCtxPtr);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(mdCtxPtr);

    _md_ctx_ptr = mdCtxPtr;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateMDHmacESP32Wrapper_SHA256_Close(void) {

    _md_ctx_ptr = NULL;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateMDHmacESP32Wrapper_SHA256_Perform(
        const   void*       const   keyPtr,
        const   uint16_t            keySize,
        const   void*       const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                void*       const   outputBufferPtr) {

#if (MBEDTLS_VERSION_MAJOR == 2)
    static const mbedtls_md_info_t* mdInfoPtr = &mbedtls_sha256_info;
#elif (MBEDTLS_VERSION_MAJOR == 3)
    const mbedtls_md_info_t* mdInfoPtr;
#endif

    void* paramMdCtxPtr;
    void* paramHmacCtxPtr;

    mbedtls_md_context_t* mdCtxPtr;
    tommRoC_err_enum_t res;

#if (MBEDTLS_VERSION_MAJOR == 3)
    mdInfoPtr = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
#endif

    TOMMROC_ASSERT_NOT_NULL(mdInfoPtr);
    if (NULL == mdInfoPtr) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

#if (MBEDTLS_VERSION_MAJOR == 2)
    TOMMROC_ASSERT_EQUALS(mbedtls_sha256_info.block_size, 64);
#endif

    // NOTE: used mbedtls_calloc but if static memory is used, the alloc will use that reserved memory
    paramMdCtxPtr   = mbedtls_calloc(1, sizeof(mbedtls_sha256_context));
#if (MBEDTLS_VERSION_MAJOR == 2)
    paramHmacCtxPtr = mbedtls_calloc(1, 2 * mbedtls_sha256_info.block_size);
#elif (MBEDTLS_VERSION_MAJOR == 3)
    paramHmacCtxPtr = mbedtls_calloc(1, 2 * 64);
#endif

    mdCtxPtr = _md_ctx_ptr;

    TOMMROC_ASSERT_NOT_NULL(mdCtxPtr);

    mbedtls_md_init(mdCtxPtr);

    // Link to the context
#if (MBEDTLS_VERSION_MAJOR == 2)
    mdCtxPtr->md_info   = mdInfoPtr;
    mdCtxPtr->md_ctx    = paramMdCtxPtr;
    mdCtxPtr->hmac_ctx  = paramHmacCtxPtr;
#elif (MBEDTLS_VERSION_MAJOR == 3)
    mdCtxPtr->private_md_info   = mdInfoPtr;
    mdCtxPtr->private_md_ctx    = paramMdCtxPtr;
    mdCtxPtr->private_hmac_ctx  = paramHmacCtxPtr;
#endif

    res = _perform(
            mdCtxPtr,
            keyPtr,
            keySize,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);

    // NOTE: the attached md_ctx and hmac_ctx of context are zeroize into following free function.
    mbedtls_md_free(mdCtxPtr);

    return res;
}

#endif
