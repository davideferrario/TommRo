
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateMDESP32Wrapper_MD2.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#if (MBEDTLS_VERSION_MAJOR == 2)
#include "mbedtls/md2.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static mbedtls_md2_context* _md_ctx_ptr = NULL;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _perform(
                mbedtls_md2_context*    const   mdCtxPtr,
        const   void*                   const   inputBufferPtr,
        const   uint16_t                        inputBufferLen,
                void*                   const   outputBufferPtr) {

    int res;

    res = mbedtls_md2_starts_ret(mdCtxPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    res = mbedtls_md2_update_ret(mdCtxPtr, (const unsigned char*) inputBufferPtr, (size_t) inputBufferLen);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    res = mbedtls_md2_finish_ret(mdCtxPtr, (unsigned char*) outputBufferPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateMDESP32Wrapper_MD2_Init(mbedtls_md2_context* const mdCtxPtr) {

    TOMMROC_ASSERT_NOT_NULL(mdCtxPtr);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(mdCtxPtr);

    _md_ctx_ptr = mdCtxPtr;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateMDESP32Wrapper_MD2_Close(void) {

    _md_ctx_ptr = NULL;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateMDESP32Wrapper_MD2_MD2Perform(
        const   void*       const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                void*       const   outputBufferPtr) {

    mbedtls_md2_context* mdCtxPtr;
    tommRoC_err_enum_t res;

    mdCtxPtr = _md_ctx_ptr;

    mbedtls_md2_init(mdCtxPtr);

    res = _perform(
            mdCtxPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);

    mbedtls_md2_free(mdCtxPtr);

    return res;
}

#endif

#endif
