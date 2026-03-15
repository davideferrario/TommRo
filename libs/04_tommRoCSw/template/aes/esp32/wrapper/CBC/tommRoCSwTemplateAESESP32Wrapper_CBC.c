
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateAESESP32Wrapper_CBC.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "mbedtls/aes.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static mbedtls_aes_context* _aes_ctx_ptr = NULL;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_err_enum_t _crypt(
                mbedtls_aes_context*    const   aesCtxPtr,
                uint8_t*                const   aesIVPtr,
        const   int                             mode,
        const   uint8_t*                const   inputBufferPtr,
        const   uint16_t                        inputBufferLen,
                uint8_t*                const   outputBufferPtr) {

    int res;

    res = mbedtls_aes_crypt_cbc(
            aesCtxPtr,
            mode,
            inputBufferLen,
            aesIVPtr,
            inputBufferPtr,
            outputBufferPtr);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _encrypt(
                mbedtls_aes_context*                const   aesCtxPtr,
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
                uint8_t*                            const   aesIVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    int res;

    res = mbedtls_aes_setkey_enc(
            aesCtxPtr,
            aesKeyPtr,
            tommRoCCryptoAESKeySize(aesKeySize));

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return _crypt(
            aesCtxPtr,
            aesIVPtr,
            MBEDTLS_AES_ENCRYPT,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);
}

static tommRoC_err_enum_t _decrypt(
                mbedtls_aes_context*                const   aesCtxPtr,
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
                uint8_t*                            const   aesIVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    int res;

    res = mbedtls_aes_setkey_dec(
            aesCtxPtr,
            aesKeyPtr,
            tommRoCCryptoAESKeySize(aesKeySize));

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return _crypt(
            aesCtxPtr,
            aesIVPtr,
            MBEDTLS_AES_DECRYPT,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateAESESP32Wrapper_CBC_Init(mbedtls_aes_context* const aesCtxPtr) {

    TOMMROC_ASSERT_NOT_NULL(aesCtxPtr);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(aesCtxPtr);

    _aes_ctx_ptr = aesCtxPtr;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateAESESP32Wrapper_CBC_Close(void) {

    _aes_ctx_ptr = NULL;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateAESESP32Wrapper_CBC_Encrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
                uint8_t*                            const   aesIVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    mbedtls_aes_context* aesCtxPtr;
    tommRoC_err_enum_t res;

    aesCtxPtr = _aes_ctx_ptr;

    mbedtls_aes_init(aesCtxPtr);

    res = _encrypt(
            aesCtxPtr,
            aesKeyPtr,
            aesKeySize,
            aesIVPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);

    mbedtls_aes_free(aesCtxPtr);

    return res;
}

tommRoC_err_enum_t tommRoCSwTemplateAESESP32Wrapper_CBC_Decrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
                uint8_t*                            const   aesIVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    mbedtls_aes_context* aesCtxPtr;
    tommRoC_err_enum_t res;

    aesCtxPtr = _aes_ctx_ptr;

    mbedtls_aes_init(aesCtxPtr);

    res = _decrypt(
            aesCtxPtr,
            aesKeyPtr,
            aesKeySize,
            aesIVPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);

    mbedtls_aes_free(aesCtxPtr);

    return res;
}

#endif
