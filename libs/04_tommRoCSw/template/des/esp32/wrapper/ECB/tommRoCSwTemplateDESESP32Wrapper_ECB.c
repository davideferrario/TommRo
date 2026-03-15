
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateDESESP32Wrapper_ECB.h"

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
static mbedtls_des_context* _des_ctx_ptr = NULL;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _crypt(
                mbedtls_des_context*    const   desCtxPtr,
        const   uint8_t*                const   inputBufferPtr,
        const   uint16_t                        inputBufferLen,
                uint8_t*                const   outputBufferPtr) {

    uint16_t length     = inputBufferLen;
    uint8_t* inputPtr   = (uint8_t*) inputBufferPtr;
    uint8_t* outputPtr  = outputBufferPtr;
    int res;

    while (length > 0) {

        res = mbedtls_des_crypt_ecb(
                desCtxPtr,
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
                mbedtls_des_context*    const   desCtxPtr,
        const   uint8_t*                const   desKeyPtr,
        const   uint8_t*                const   inputBufferPtr,
        const   uint16_t                        inputBufferLen,
                uint8_t*                const   outputBufferPtr) {

    int res;

    res = mbedtls_des_setkey_enc(
            desCtxPtr,
            desKeyPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return _crypt(
            desCtxPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);
}

static tommRoC_err_enum_t _decrypt(
                mbedtls_des_context*    const   desCtxPtr,
        const   uint8_t*                const   desKeyPtr,
        const   uint8_t*                const   inputBufferPtr,
        const   uint16_t                        inputBufferLen,
                uint8_t*                const   outputBufferPtr) {

    int res;

    res = mbedtls_des_setkey_dec(
            desCtxPtr,
            desKeyPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return _crypt(
            desCtxPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateDESESP32Wrapper_ECB_Init(mbedtls_des_context* const desCtxPtr) {

    TOMMROC_ASSERT_NOT_NULL(desCtxPtr);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(desCtxPtr);

    _des_ctx_ptr = desCtxPtr;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateDESESP32Wrapper_ECB_Close(void) {

    _des_ctx_ptr = NULL;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateDESESP32Wrapper_ECB_Encrypt(
        const   uint8_t*    const   desKeyPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr) {

    mbedtls_des_context* desCtxPtr;
    tommRoC_err_enum_t res;

    desCtxPtr = _des_ctx_ptr;

    mbedtls_des_init(desCtxPtr);

    res = _encrypt(
            desCtxPtr,
            desKeyPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);

    mbedtls_des_free(desCtxPtr);

    return res;
}

tommRoC_err_enum_t tommRoCSwTemplateDESESP32Wrapper_ECB_Decrypt(
        const   uint8_t*    const   desKeyPtr,
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr) {

    mbedtls_des_context* desCtxPtr;
    tommRoC_err_enum_t res;

    desCtxPtr = _des_ctx_ptr;

    mbedtls_des_init(desCtxPtr);

    res = _decrypt(
            desCtxPtr,
            desKeyPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);

    mbedtls_des_free(desCtxPtr);

    return res;
}

#endif
