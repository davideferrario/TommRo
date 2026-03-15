
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateCryptoAESWrapper.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__) || defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
#include <freertos/FreeRTOS.h>

#include "soc/hwcrypto_periph.h"
#include "soc/periph_defs.h"
#include "driver/periph_ctrl.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__) || defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
#define __ESP_AES_ENCRYPT__     (1)
#define __ESP_AES_DECRYPT__     (0)
#endif

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__) || defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
static portMUX_TYPE _aes_mux = portMUX_INITIALIZER_UNLOCKED;
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__) || defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
static void _acquire_hardware(void) {

    portENTER_CRITICAL(&_aes_mux);

    // Enable AES hardware
    periph_module_enable(PERIPH_AES_MODULE);
}

static void _release_hardware(void) {

    // Disable AES hardware
    periph_module_disable(PERIPH_AES_MODULE);

    portEXIT_CRITICAL(&_aes_mux);
}

/*
 * Helper function to copy key from esp_aes_context buffer
 * to hardware key registers.
 */
static inline void _set_key_hardware(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
        const   int                                         mode) {

    const uint32_t MODE_DECRYPT_BIT = 4;
    unsigned mode_reg_base = (mode == __ESP_AES_ENCRYPT__) ? 0 : MODE_DECRYPT_BIT;

    const uint16_t keyBytes = tommRoCCryptoAESKeySize(aesKeySize) / 8;
	uint8_t i;

    for (i = 0; i < keyBytes / TOMMROC_UTIL_U32_SIZE; ++i) {
        DPORT_REG_WRITE(AES_KEY_BASE + i * TOMMROC_UTIL_U32_SIZE, *(((uint32_t*)aesKeyPtr) + i));
    }

    DPORT_REG_WRITE(AES_MODE_REG, mode_reg_base + ((keyBytes / 8) - 2));
}

/* Run a single 16 byte block of AES, using the hardware engine.
 */
static void _block(const void *input, void *output) {

    const uint32_t* inputWordsPtr = (const uint32_t*) input;
    uint32_t i0, i1, i2, i3;
    uint32_t* outputWordsPtr = (uint32_t*) output;

    /* Storing i0,i1,i2,i3 in registers not an array
       helps a lot with optimisations at -Os level */
    i0 = inputWordsPtr[0];
    DPORT_REG_WRITE(AES_TEXT_BASE, i0);

    i1 = inputWordsPtr[1];
    DPORT_REG_WRITE(AES_TEXT_BASE + 4, i1);

    i2 = inputWordsPtr[2];
    DPORT_REG_WRITE(AES_TEXT_BASE + 8, i2);

    i3 = inputWordsPtr[3];
    DPORT_REG_WRITE(AES_TEXT_BASE + 12, i3);

    DPORT_REG_WRITE(AES_START_REG, 1);

    while (DPORT_REG_READ(AES_IDLE_REG) != 1) { }

    esp_dport_access_read_buffer(outputWordsPtr, AES_TEXT_BASE, 4);

    /* Physical security check: Verify the AES accelerator actually ran, and wasn't
       skipped due to external fault injection while starting the peripheral.

       Note that i0,i1,i2,i3 are copied from input buffer in case input==output.

       Bypassing this check requires at least one additional fault.
    */
    if(i0 == outputWordsPtr[0] && i1 == outputWordsPtr[1] && i2 == outputWordsPtr[2] && i3 == outputWordsPtr[3]) {

        // calling two zeroing functions to narrow the
        // window for a double-fault here
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(output, 0, 16));
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(output, 0, 16));
    }
}
#endif

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__)
/*
 * AES-CBC buffer encryption/decryption
 */
static tommRoC_err_enum_t _crypt_cbc(
        const   int                                         mode,
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
                uint8_t*                            const   aesIVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    uint8_t temp[TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE];

    uint16_t length             = inputBufferLen;
    uint32_t* IVWordsPtr        = (uint32_t*) aesIVPtr;
    uint32_t* inputWordsPtr     = (uint32_t*) inputBufferPtr;
    uint32_t* outputWordsPtr    = (uint32_t*) outputBufferPtr;
	
	uint8_t i;

    _acquire_hardware();

    _set_key_hardware(aesKeyPtr, aesKeySize, mode);

    if (__ESP_AES_DECRYPT__ == mode) {

        while (length > 0) {

            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(temp, inputWordsPtr, TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE));
            _block(inputWordsPtr, outputWordsPtr);

            for (i = 0; i < TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE / TOMMROC_UTIL_U32_SIZE; ++i) {
                outputWordsPtr[i] = outputWordsPtr[i] ^ IVWordsPtr[i];
            }

            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(IVWordsPtr, temp, TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE));

            inputWordsPtr   += TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE / TOMMROC_UTIL_U32_SIZE;
            outputWordsPtr  += TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE / TOMMROC_UTIL_U32_SIZE;
            length          -= TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE;
        }
    }
    else {

        while (length > 0) {

            for (i = 0; i < TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE / TOMMROC_UTIL_U32_SIZE; ++i) {
                outputWordsPtr[i] = inputWordsPtr[i] ^ IVWordsPtr[i];
            }

            _block(outputWordsPtr, outputWordsPtr);
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(IVWordsPtr, outputWordsPtr, TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE));

            inputWordsPtr   += TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE / TOMMROC_UTIL_U32_SIZE;
            outputWordsPtr  += TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE / TOMMROC_UTIL_U32_SIZE;
            length          -= TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE;
        }
    }

    _release_hardware();

    return TOMMRO_C_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
/*
 * AES-ECB block encryption/decryption
 */
static tommRoC_err_enum_t _crypt_ecb(
        const   int                                         mode,
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    uint16_t length     = inputBufferLen;
    uint8_t* inputPtr   = (uint8_t*) inputBufferPtr;
    uint8_t* outputPtr  = outputBufferPtr;

    _acquire_hardware();

    _set_key_hardware(aesKeyPtr, aesKeySize, mode);

    while (length > 0) {

        _block(inputPtr, outputPtr);

        inputPtr    += TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE;
        outputPtr   += TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE;
        length      -= TOMMROC_CRYPTO_AES_BLOCK_SIZE_BYTE;
    }

    _release_hardware();

    return TOMMRO_C_ERR_SUCCESS;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__)
tommRoC_err_enum_t tommRoCTemplateCryptoAESWrapper_CBC_Encrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
                uint8_t*                            const   aesIVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    return _crypt_cbc(
            __ESP_AES_ENCRYPT__,
            aesKeyPtr,
            aesKeySize,
            aesIVPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);
}

tommRoC_err_enum_t tommRoCTemplateCryptoAESWrapper_CBC_Decrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
                uint8_t*                            const   aesIVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    return _crypt_cbc(
            __ESP_AES_DECRYPT__,
            aesKeyPtr,
            aesKeySize,
            aesIVPtr,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);
}
#endif

#if defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
tommRoC_err_enum_t tommRoCTemplateCryptoAESWrapper_ECB_Encrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    return _crypt_ecb(
            __ESP_AES_ENCRYPT__,
            aesKeyPtr,
            aesKeySize,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);
}

tommRoC_err_enum_t tommRoCTemplateCryptoAESWrapper_ECB_Decrypt(
        const   uint8_t*                            const   aesKeyPtr,
        const   tommRoC_crypto_aes_key_size_enum_t          aesKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr) {

    return _crypt_ecb(
            __ESP_AES_DECRYPT__,
            aesKeyPtr,
            aesKeySize,
            inputBufferPtr,
            inputBufferLen,
            outputBufferPtr);
}
#endif

#endif
