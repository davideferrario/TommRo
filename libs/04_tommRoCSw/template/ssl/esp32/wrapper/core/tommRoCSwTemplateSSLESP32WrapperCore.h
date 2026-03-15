
#ifndef TOMMROC_SW_TEMPLATE_SSL_ESP32_WRAPPER_CORE_H_
#define TOMMROC_SW_TEMPLATE_SSL_ESP32_WRAPPER_CORE_H_

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

#include "mbedtls/net_sockets.h"
#include "mbedtls/ssl.h"
#include "mbedtls/x509.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef struct {

    mbedtls_net_context mbedtlsNetContext;
    mbedtls_ssl_context mbedtlsSSLContext;
    mbedtls_ssl_config  mbedtlsSSLConfig;
    mbedtls_x509_crt    mbedtlsX509CaChainCrt;
    mbedtls_x509_crt    mbedtlsX509ClientCrt;
    mbedtls_pk_context  mbedtlsPkClientPrivKey;

} tommRoC_sw_template_ssl_esp32_wrapper_core_context_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCSwTemplateSSLESP32WrapperCoreInitHandshakeHost(
                tommRoC_sw_template_ssl_esp32_wrapper_core_context_t*   const   sslCtxPtr,
        const   void*                                                   const   caChainDataPtr,
        const   uint32_t                                                        caChainDataSize,
        const   void*                                                   const   clientCertDataPtr,
        const   uint32_t                                                        clientCertDataSize,
        const   void*                                                   const   clientPrivKeyDataPtr,
        const   uint32_t                                                        clientPrivKeyDataSize,
        const   tommRoC_crypto_ssl_auth_mode_enum_t                             sslAuthMode,
        const   char*                                                   const   hostStrPtr,
        const   uint16_t                                                        tcpPort,
                int32_t*                                                const   caChainVerifyResPtr);

tommRoC_err_enum_t tommRoCSwTemplateSSLESP32WrapperCoreWrite(
                tommRoC_sw_template_ssl_esp32_wrapper_core_context_t*   const   sslCtxPtr,
        const   void*                                                   const   writeBufferPtr,
        const   uint32_t                                                        writeBufferLen,
                int32_t*                                                const   writtenLenPtr,
        const   uint32_t                                                        writeTimeoutMsec);

tommRoC_err_enum_t tommRoCSwTemplateSSLESP32WrapperCoreRead(
                tommRoC_sw_template_ssl_esp32_wrapper_core_context_t*   const   sslCtxPtr,
                void*                                                   const   readBufferPtr,
        const   uint32_t                                                        readBufferLen,
                int32_t*                                                const   readLenPtr,
        const   uint32_t                                                        readTimeoutMsec);

tommRoC_err_enum_t tommRoCSwTemplateSSLESP32WrapperCoreCloseNotifyFree(
                tommRoC_sw_template_ssl_esp32_wrapper_core_context_t*   const   sslCtxPtr);

#endif

#endif
