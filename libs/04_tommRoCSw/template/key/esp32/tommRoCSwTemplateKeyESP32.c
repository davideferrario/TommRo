
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

#include "memory/esp32/core/tommRoCSwTemplateMemoryESP32Core.h"

#include "mbedtls/version.h"

#include "mbedtls/pk.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static mbedtls_pk_context _pk_ctx;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_sw_err_enum_t _der_to_pem(
                mbedtls_pk_context* const   pkCtxPtr,
        const   uint8_t*            const   keyPtr,
        const   uint16_t                    keySize,
                char*               const   outputBufferPtr,
        const   uint16_t                    outputBufferMaxSize) {

#if (MBEDTLS_VERSION_MAJOR == 2)
    int (*writePEMFunct)(mbedtls_pk_context*, unsigned char*, size_t) = NULL;
#elif (MBEDTLS_VERSION_MAJOR == 3)
    int (*writePEMFunct)(const mbedtls_pk_context*, unsigned char*, size_t) = NULL;
#endif
    int res;

    // If private key
#if (MBEDTLS_VERSION_MAJOR == 2)
    if (0 == mbedtls_pk_parse_key(pkCtxPtr, keyPtr, keySize, NULL, 0)) {
        writePEMFunct = mbedtls_pk_write_key_pem;
    }
#elif (MBEDTLS_VERSION_MAJOR == 3)
    if (0 == mbedtls_pk_parse_key(pkCtxPtr, keyPtr, keySize, NULL, 0, NULL, 0)) {
        writePEMFunct = mbedtls_pk_write_key_pem;
    }
#endif
    // If public key
    else if (0 == mbedtls_pk_parse_public_key(pkCtxPtr, keyPtr, keySize)) {
        writePEMFunct = mbedtls_pk_write_pubkey_pem;
    }
    // If here, nor private nor public key
    else {
        return TOMMRO_C_SW_PARAM_ERR;
    }

    // Extract as PEM string
    res = writePEMFunct(pkCtxPtr, (unsigned char*) outputBufferPtr, outputBufferMaxSize);

    if (0 != res) {
        return TOMMRO_C_SW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_SW_ERR_SUCCESS;
}

static tommRoC_sw_err_enum_t _pem_to_der(
                mbedtls_pk_context* const   pkCtxPtr,
        const   char*               const   keyStrPtr,
                uint8_t*            const   outputBufferPtr,
        const   uint16_t                    outputBufferMaxSize,
                uint16_t*           const   outputBufferLenPtr) {

#if (MBEDTLS_VERSION_MAJOR == 2)
    int (*writeDERFunct)(mbedtls_pk_context*, unsigned char*, size_t) = NULL;
#elif (MBEDTLS_VERSION_MAJOR == 3)
    int (*writeDERFunct)(const mbedtls_pk_context*, unsigned char*, size_t) = NULL;
#endif
    uint16_t inputStrLen;
    uint16_t tmpLen;
    int res;

    inputStrLen = tommRoCStringStrLen(keyStrPtr);

    // If private key
#if (MBEDTLS_VERSION_MAJOR == 2)
    if (0 == mbedtls_pk_parse_key(pkCtxPtr, (const unsigned char*) keyStrPtr, inputStrLen + 1, NULL, 0)) {
        writeDERFunct = mbedtls_pk_write_key_der;
    }
#elif (MBEDTLS_VERSION_MAJOR == 3)
    if (0 == mbedtls_pk_parse_key(pkCtxPtr, (const unsigned char*) keyStrPtr, inputStrLen + 1, NULL, 0, NULL, 0)) {
        writeDERFunct = mbedtls_pk_write_key_der;
    }
#endif
    // If public key
    else if (0 == mbedtls_pk_parse_public_key(pkCtxPtr, (const unsigned char*) keyStrPtr, inputStrLen + 1)) {
        writeDERFunct = mbedtls_pk_write_pubkey_der;
    }
    // If here, nor private nor public key
    else {
        return TOMMRO_C_SW_PARAM_ERR;
    }

    // Extract as DER structure
    res = writeDERFunct(pkCtxPtr, outputBufferPtr, outputBufferMaxSize);

    if (res < 0) {
        return TOMMRO_C_SW_LOW_LEVEL_ERR;
    }

    tmpLen = (uint16_t) res;

    // memmove needed because mbedtls library write data at the end of the buffer
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(
            tommRoCUtilMemMove(
                    outputBufferPtr,
                    outputBufferPtr + outputBufferMaxSize - tmpLen,
                    tmpLen));

    *outputBufferLenPtr = tmpLen;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwKeyFormatDERToPEM(
        const   uint8_t*    const   keyPtr,
        const   uint16_t            keySize,
                char*       const   outputBufferPtr,
        const   uint16_t            outputBufferMaxSize) {

    mbedtls_pk_context* pkCtxPtr;
    tommRoC_sw_err_enum_t res;

    TOMMROC_ASSERT_NOT_NULL(keyPtr);
    TOMMROC_ASSERT_NOT_ZERO(keySize);
    TOMMROC_ASSERT_NOT_NULL(outputBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(outputBufferMaxSize);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyPtr);
    TOMMROC_SW_PARAM_CHECK_ON_ZERO_RETURN_ERR(keySize);
    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(outputBufferPtr);
    TOMMROC_SW_PARAM_CHECK_ON_ZERO_RETURN_ERR(outputBufferMaxSize);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    pkCtxPtr = &_pk_ctx;

    mbedtls_pk_init(pkCtxPtr);

    res = _der_to_pem(
            pkCtxPtr,
            keyPtr,
            keySize,
            outputBufferPtr,
            outputBufferMaxSize);

    mbedtls_pk_free(pkCtxPtr);

    return res;
}

tommRoC_sw_err_enum_t tommRoCSwKeyFormatPEMToDER(
        const   char*       const   keyStrPtr,
                uint8_t*    const   outputBufferPtr,
        const   uint16_t            outputBufferMaxSize,
                uint16_t*   const   outputBufferLenPtr) {

    mbedtls_pk_context* pkCtxPtr;
    tommRoC_sw_err_enum_t res;

    TOMMROC_ASSERT_NOT_NULL(keyStrPtr);
    TOMMROC_ASSERT_NOT_NULL(outputBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(outputBufferMaxSize);
    TOMMROC_ASSERT_NOT_NULL(outputBufferLenPtr);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(keyStrPtr);
    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(outputBufferPtr);
    TOMMROC_SW_PARAM_CHECK_ON_ZERO_RETURN_ERR(outputBufferMaxSize);
    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(outputBufferLenPtr);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    pkCtxPtr = &_pk_ctx;

    mbedtls_pk_init(pkCtxPtr);

    res = _pem_to_der(
            pkCtxPtr,
            keyStrPtr,
            outputBufferPtr,
            outputBufferMaxSize,
            outputBufferLenPtr);

    mbedtls_pk_free(pkCtxPtr);

    return res;
}

#endif
