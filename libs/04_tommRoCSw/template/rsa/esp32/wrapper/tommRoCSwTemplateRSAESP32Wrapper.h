
#ifndef TOMMROC_SW_TEMPLATE_RSA_ESP32_WRAPPER_H_
#define TOMMROC_SW_TEMPLATE_RSA_ESP32_WRAPPER_H_

/*
 *******************************************************************************
 * License
 * (C) Copyright 2017
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications according to the supply agreement.
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: this software is provided
 * "AS IS", with no express or implied warranties of any kind, including,
 * but not limited to, any implied warranties of merchantability or
 * fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Supplier will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 */

/**
 * Author
 * TommRo Software Department
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

#include "mbedtls/pk.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateRSAESP32WrapperInit(mbedtls_pk_context* const pkCtxPtr);
tommRoC_sw_err_enum_t tommRoCSwTemplateRSAESP32WrapperClose(void);

tommRoC_err_enum_t tommRoCSwTemplateRSAESP32WrapperGenKeypair(
        const   tommRoC_crypto_rsa_encoding_enum_t          encodingMode,
        const   tommRoC_crypto_rsa_hash_enum_t              hashType,
        const   tommRoC_crypto_rsa_key_size_enum_t          keySize,
                uint8_t*                            const   privateKeyPtr,
        const   uint16_t                                    privateKeyMaxSize,
                uint16_t*                           const   privateKeyLenPtr,
                uint8_t*                            const   publicKeyPtr,
        const   uint16_t                                    publicKeyMaxSize,
                uint16_t*                           const   publicKeyLenPtr);

tommRoC_err_enum_t tommRoCSwTemplateRSAESP32WrapperEncrypt(
        const   uint8_t*                            const   publicKeyPtr,
        const   uint16_t                                    publicKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr,
        const   uint16_t                                    outputBufferMaxSize,
                uint16_t*                           const   outputBufferLenPtr);

tommRoC_err_enum_t tommRoCSwTemplateRSAESP32WrapperDecrypt(
        const   uint8_t*                            const   privateKeyPtr,
        const   uint16_t                                    privateKeySize,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr,
        const   uint16_t                                    outputBufferMaxSize,
                uint16_t*                           const   outputBufferLenPtr);

tommRoC_err_enum_t tommRoCSwTemplateRSAESP32WrapperSign(
        const   uint8_t*                            const   privateKeyPtr,
        const   uint16_t                                    privateKeySize,
        const   tommRoC_crypto_rsa_hash_enum_t              hashType,
        const   uint8_t*                            const   hashBufferPtr,
        const   uint16_t                                    hashBufferLen,
                uint8_t*                            const   signatureBufferPtr,
        const   uint16_t                                    signatureBufferMaxSize,
                uint16_t*                           const   signatureBufferLenPtr);

tommRoC_err_enum_t tommRoCSwTemplateRSAESP32WrapperVerify(
        const   uint8_t*                            const   publicKeyPtr,
        const   uint16_t                                    publicKeySize,
        const   tommRoC_crypto_rsa_hash_enum_t              hashType,
        const   uint8_t*                            const   hashBufferPtr,
        const   uint16_t                                    hashBufferLen,
        const   uint8_t*                            const   signatureBufferPtr,
        const   uint16_t                                    signatureBufferLen);

#endif

#endif
