
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateSSLESP32Wrapper.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

#include "ssl/esp32/wrapper/core/tommRoCSwTemplateSSLESP32WrapperCore.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
TOMMROC_SCTA_SIZE_OF_EQUALS(tommRoC_sw_ssl_context_t, tommRoC_sw_template_ssl_esp32_wrapper_core_context_t);

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCSwTemplateSSLESP32WrapperInitHandshakeHost(
                void*                                   const   sslCtxPtr,
        const   void*                                   const   caChainDataPtr,
        const   uint32_t                                        caChainDataSize,
        const   void*                                   const   clientCertDataPtr,
        const   uint32_t                                        clientCertDataSize,
        const   void*                                   const   clientPrivKeyDataPtr,
        const   uint32_t                                        clientPrivKeyDataSize,
        const   tommRoC_crypto_ssl_auth_mode_enum_t             sslAuthMode,
        const   char*                                   const   hostStrPtr,
        const   uint16_t                                        tcpPort,
                int32_t*                                const   caChainVerifyResPtr) {

    tommRoC_sw_ssl_context_t* swSSLCtxPtr = (tommRoC_sw_ssl_context_t*) sslCtxPtr;

    return tommRoCSwTemplateSSLESP32WrapperCoreInitHandshakeHost(
            (tommRoC_sw_template_ssl_esp32_wrapper_core_context_t*) swSSLCtxPtr,
            caChainDataPtr,
            caChainDataSize,
            clientCertDataPtr,
            clientCertDataSize,
            clientPrivKeyDataPtr,
            clientPrivKeyDataSize,
            sslAuthMode,
            hostStrPtr,
            tcpPort,
            caChainVerifyResPtr);
}

tommRoC_err_enum_t tommRoCSwTemplateSSLESP32WrapperWrite(
                void*                                   const   sslCtxPtr,
        const   void*                                   const   writeBufferPtr,
        const   uint32_t                                        writeBufferLen,
                int32_t*                                const   writtenLenPtr,
        const   uint32_t                                        writeTimeoutMsec) {

    tommRoC_sw_ssl_context_t* swSSLCtxPtr = (tommRoC_sw_ssl_context_t*) sslCtxPtr;

    return tommRoCSwTemplateSSLESP32WrapperCoreWrite(
            (tommRoC_sw_template_ssl_esp32_wrapper_core_context_t*) swSSLCtxPtr,
            writeBufferPtr,
            writeBufferLen,
            writtenLenPtr,
            writeTimeoutMsec);
}

tommRoC_err_enum_t tommRoCSwTemplateSSLESP32WrapperRead(
                void*                                   const   sslCtxPtr,
                void*                                   const   readBufferPtr,
        const   uint32_t                                        readBufferLen,
                int32_t*                                const   readLenPtr,
        const   uint32_t                                        readTimeoutMsec) {

    tommRoC_sw_ssl_context_t* swSSLCtxPtr = (tommRoC_sw_ssl_context_t*) sslCtxPtr;

    return tommRoCSwTemplateSSLESP32WrapperCoreRead(
            (tommRoC_sw_template_ssl_esp32_wrapper_core_context_t*) swSSLCtxPtr,
            readBufferPtr,
            readBufferLen,
            readLenPtr,
            readTimeoutMsec);
}

tommRoC_err_enum_t tommRoCSwTemplateSSLESP32WrapperCloseNotifyFree(
                void*                                   const   sslCtxPtr) {

    tommRoC_sw_ssl_context_t* swSSLCtxPtr = (tommRoC_sw_ssl_context_t*) sslCtxPtr;

    return tommRoCSwTemplateSSLESP32WrapperCoreCloseNotifyFree(
            (tommRoC_sw_template_ssl_esp32_wrapper_core_context_t*) swSSLCtxPtr);
}

#endif
