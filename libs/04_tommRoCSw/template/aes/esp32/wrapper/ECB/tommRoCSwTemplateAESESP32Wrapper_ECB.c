
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateAESESP32Wrapper_ECB.h"

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
        const   int                             mode,
        const   uint8_t*                const   inputBufferPtr,
        const   uint16_t                        inputBufferLen,
                uint8_t*                const   outputBufferPtr) {

    uint16_t length     = inputBufferLen;
    uint8_t* inputPtr   = (uint8_t*) inputBufferPtr;
    uint8_t* outputPtr  = outputBufferPtr;
    int res;

    while (length > 0) {

        res = mbedtls_aes_crypt_ecb(
                aesCtxPtr,
                mode,
                inputPtr,
                outputPtr);

        if (0 != res) {
            return TOMMRO_C_LOW_LEVEL_ERR;
        }

        inputPtr    += TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE;
        outputPtr   += TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE;
        length      -= TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _encrypt(
                mbedtls_aes_context*                const   aesCtxPtr,
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
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
            MBEDTLS_AES_ENCRYPT,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);
}

static tommRoC_err_enum_t _decrypt(
                mbedtls_aes_context*                const   aesCtxPtr,
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
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
            MBEDTLS_AES_DECRYPT,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateAESESP32Wrapper_ECB_Init(mbedtls_aes_context* const aesCtxPtr) {

    TOMMROC_ASSERT_NOT_NULL(aesCtxPtr);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(aesCtxPtr);

    _aes_ctx_ptr = aesCtxPtr;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateAESESP32Wrapper_ECB_Close(void) {

    _aes_ctx_ptr = NULL;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateAESESP32Wrapper_ECB_Encrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
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
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);

    mbedtls_aes_free(aesCtxPtr);

    return res;
}

tommRoC_err_enum_t tommRoCSwTemplateAESESP32Wrapper_ECB_Decrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
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
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);

    mbedtls_aes_free(aesCtxPtr);

    return res;
}

#endif
