
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateDESESP32Wrapper_CBC.h"

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
                uint8_t*                const   desIVPtr,
        const   int                             mode,
        const   uint8_t*                const   inputBufferPtr,
        const   uint16_t                        inputBufferLen,
                uint8_t*                const   outputBufferPtr) {

    int res;

    res = mbedtls_des_crypt_cbc(
            desCtxPtr,
            mode,
            inputBufferLen,
            desIVPtr,
            inputBufferPtr,
            outputBufferPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _encrypt(
                mbedtls_des_context*    const   desCtxPtr,
        const   uint8_t*                const   desKeyPtr,
                uint8_t*                const   desIVPtr,
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
            desIVPtr,
            MBEDTLS_DES_ENCRYPT,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);
}

static tommRoC_err_enum_t _decrypt(
                mbedtls_des_context*    const   desCtxPtr,
        const   uint8_t*                const   desKeyPtr,
                uint8_t*                const   desIVPtr,
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
            desIVPtr,
            MBEDTLS_DES_DECRYPT,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateDESESP32Wrapper_CBC_Init(mbedtls_des_context* const desCtxPtr) {

    TOMMROC_ASSERT_NOT_NULL(desCtxPtr);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(desCtxPtr);

    _des_ctx_ptr = desCtxPtr;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateDESESP32Wrapper_CBC_Close(void) {

    _des_ctx_ptr = NULL;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateDESESP32Wrapper_CBC_Encrypt(
        const   uint8_t*    const   desKeyPtr,
                uint8_t*    const   desIVPtr,
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
            desIVPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);

    mbedtls_des_free(desCtxPtr);

    return res;
}

tommRoC_err_enum_t tommRoCSwTemplateDESESP32Wrapper_CBC_Decrypt(
        const   uint8_t*    const   desKeyPtr,
                uint8_t*    const   desIVPtr,
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
            desIVPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);

    mbedtls_des_free(desCtxPtr);

    return res;
}

#endif
