
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateDES3ESP32Wrapper_ECB.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "mbedtls/des.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static mbedtls_des3_context* _des3_ctx_ptr = NULL;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _crypt(
                mbedtls_des3_context*   const   des3CtxPtr,
        const   uint8_t*                const   inputBufferPtr,
        const   uint16_t                        inputBufferLen,
                uint8_t*                const   outputBufferPtr) {

    uint16_t length     = inputBufferLen;
    uint8_t* inputPtr   = (uint8_t*) inputBufferPtr;
    uint8_t* outputPtr  = outputBufferPtr;
    int res;

    while (length > 0) {

        res = mbedtls_des3_crypt_ecb(
                des3CtxPtr,
                inputPtr,
                outputPtr);

        if (0 != res) {
            return TOMMRO_C_LOW_LEVEL_ERR;
        }

        inputPtr    += TOMMROC_CRYPTO_DES_BLOCK_SIZE_BYTE;
        outputPtr   += TOMMROC_CRYPTO_DES_BLOCK_SIZE_BYTE;
        length      -= TOMMROC_CRYPTO_DES_BLOCK_SIZE_BYTE;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _encrypt(
                mbedtls_des3_context*   const   des3CtxPtr,
        const   uint8_t*                const   des3KeyPtr,
        const   uint8_t*                const   inputBufferPtr,
        const   uint16_t                        inputBufferLen,
                uint8_t*                const   outputBufferPtr) {

    int res;

    res = mbedtls_des3_set2key_enc(
            des3CtxPtr,
            des3KeyPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return _crypt(
            des3CtxPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);
}

static tommRoC_err_enum_t _decrypt(
                mbedtls_des3_context*   const   des3CtxPtr,
        const   uint8_t*                const   des3KeyPtr,
        const   uint8_t*                const   inputBufferPtr,
        const   uint16_t                        inputBufferLen,
                uint8_t*                const   outputBufferPtr) {

    int res;

    res = mbedtls_des3_set2key_dec(
            des3CtxPtr,
            des3KeyPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return _crypt(
            des3CtxPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateDES3ESP32Wrapper_ECB_Init(mbedtls_des3_context* const des3CtxPtr) {

    TOMMROC_ASSERT_NOT_NULL(des3CtxPtr);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(des3CtxPtr);

    _des3_ctx_ptr = des3CtxPtr;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateDES3ESP32Wrapper_ECB_Close(void) {

    _des3_ctx_ptr = NULL;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateDES3ESP32Wrapper_ECB_Encrypt(
        const   uint8_t*    const   des3KeyPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr) {

    mbedtls_des3_context* des3CtxPtr;
    tommRoC_err_enum_t res;

    des3CtxPtr = _des3_ctx_ptr;

    mbedtls_des3_init(des3CtxPtr);

    res = _encrypt(
            des3CtxPtr,
            des3KeyPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);

    mbedtls_des3_free(des3CtxPtr);

    return res;
}

tommRoC_err_enum_t tommRoCSwTemplateDES3ESP32Wrapper_ECB_Decrypt(
        const   uint8_t*    const   des3KeyPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr) {

    mbedtls_des3_context* des3CtxPtr;
    tommRoC_err_enum_t res;

    des3CtxPtr = _des3_ctx_ptr;

    mbedtls_des3_init(des3CtxPtr);

    res = _decrypt(
            des3CtxPtr,
            des3KeyPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);

    mbedtls_des3_free(des3CtxPtr);

    return res;
}

#endif
