
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateSSLESP32WrapperCore.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "ssl/esp32/wrapper/core/altNetSockets/tommRoCSwTemplateSSLESP32WrapperCoreAltNetSockets.h"

#include "TOMMROCHw.h"

#include "mbedtls/version.h"

#include "mbedtls/net_sockets.h"
#include "mbedtls/ssl.h"
#include "mbedtls/x509.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
// NOTE: experimental values
#define __HW_ETHERNET_WIFI_HANDSHAKE_READ_TIMEOUT_mSEC__        (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(1UL))
#define __SPI_BUS_ETHERNET_HANDSHAKE_READ_TIMEOUT_mSEC__        (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(2UL))
#define __SPI_BUS_WIFI_HANDSHAKE_READ_TIMEOUT_mSEC__            (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(3UL))
#define __AT_COMMAND_ETHERNET_HANDSHAKE_READ_TIMEOUT_mSEC__     (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(5UL))
#define __AT_COMMAND_WIFI_HANDSHAKE_READ_TIMEOUT_mSEC__         (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(5UL))
#define __AT_COMMAND_GSM_MODEM_HANDSHAKE_READ_TIMEOUT_mSEC__    (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(5UL))
#define __LTE_MODEM_OVER_LWIP_HANDSHAKE_READ_TIMEOUT_mSEC__     (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(5UL))

#define __HW_ETHERNET_WIFI_READ_TIMEOUT_mSEC__                  (25UL)
#define __SPI_BUS_ETHERNET_READ_TIMEOUT_mSEC__                  (50UL)
#define __SPI_BUS_WIFI_READ_TIMEOUT_mSEC__                      (100UL)
#define __AT_COMMAND_ETHERNET_READ_TIMEOUT_mSEC__               (150UL)
#define __AT_COMMAND_WIFI_READ_TIMEOUT_mSEC__                   (150UL)
#define __AT_COMMAND_GSM_MODEM_READ_TIMEOUT_mSEC__              (250UL)
#define __LTE_MODEM_OVER_LWIP_READ_TIMEOUT_mSEC__               (250UL)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_CERT_SUCCESS,           0);

TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCERT_EXPIRED,        MBEDTLS_X509_BADCERT_EXPIRED);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCERT_REVOKED,        MBEDTLS_X509_BADCERT_REVOKED);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCERT_CN_MISMATCH,    MBEDTLS_X509_BADCERT_CN_MISMATCH);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCERT_NOT_TRUSTED,    MBEDTLS_X509_BADCERT_NOT_TRUSTED);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCRL_NOT_TRUSTED,     MBEDTLS_X509_BADCRL_NOT_TRUSTED);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCRL_EXPIRED,         MBEDTLS_X509_BADCRL_EXPIRED);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCERT_MISSING,        MBEDTLS_X509_BADCERT_MISSING);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCERT_SKIP_VERIFY,    MBEDTLS_X509_BADCERT_SKIP_VERIFY);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCERT_OTHER,          MBEDTLS_X509_BADCERT_OTHER);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCERT_FUTURE,         MBEDTLS_X509_BADCERT_FUTURE);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCRL_FUTURE,          MBEDTLS_X509_BADCRL_FUTURE);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCERT_KEY_USAGE,      MBEDTLS_X509_BADCERT_KEY_USAGE);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCERT_EXT_KEY_USAGE,  MBEDTLS_X509_BADCERT_EXT_KEY_USAGE);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCERT_NS_CERT_TYPE,   MBEDTLS_X509_BADCERT_NS_CERT_TYPE);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCERT_BAD_MD,         MBEDTLS_X509_BADCERT_BAD_MD);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCERT_BAD_PK,         MBEDTLS_X509_BADCERT_BAD_PK);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCERT_BAD_KEY,        MBEDTLS_X509_BADCERT_BAD_KEY);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCRL_BAD_MD,          MBEDTLS_X509_BADCRL_BAD_MD);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCRL_BAD_PK,          MBEDTLS_X509_BADCRL_BAD_PK);
TOMMROC_SCTA_EQUALS(TOMMROC_CRYPTO_SSL_X509_BADCRL_BAD_KEY,         MBEDTLS_X509_BADCRL_BAD_KEY);

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
static uint32_t _get_for_handshake_read_timeout_msec(void) {

    tommRoC_hw_net_socket_def_device_type_enum_t deviceType;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwNetSocketGetDeviceType(&deviceType));

    do { // Added to avoid "warning: unreachable code"
        switch (deviceType) {

        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_HW_ETHERNET_WIFI:        return __HW_ETHERNET_WIFI_HANDSHAKE_READ_TIMEOUT_mSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_SPI_BUS_ETHERNET:        return __SPI_BUS_ETHERNET_HANDSHAKE_READ_TIMEOUT_mSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_SPI_BUS_WIFI:            return __SPI_BUS_WIFI_HANDSHAKE_READ_TIMEOUT_mSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_ETHERNET:     return __AT_COMMAND_ETHERNET_HANDSHAKE_READ_TIMEOUT_mSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_WIFI:         return __AT_COMMAND_WIFI_HANDSHAKE_READ_TIMEOUT_mSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_GSM_MODEM:    return __AT_COMMAND_GSM_MODEM_HANDSHAKE_READ_TIMEOUT_mSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_LTE_MODEM_OVER_LWIP:     return __LTE_MODEM_OVER_LWIP_HANDSHAKE_READ_TIMEOUT_mSEC__;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            break;
        }
    } while (0);

    return __AT_COMMAND_GSM_MODEM_HANDSHAKE_READ_TIMEOUT_mSEC__;
}

static uint32_t _get_read_timeout_msec(void) {

    tommRoC_hw_net_socket_def_device_type_enum_t deviceType;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwNetSocketGetDeviceType(&deviceType));

    do { // Added to avoid "warning: unreachable code"
        switch (deviceType) {

        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_HW_ETHERNET_WIFI:        return __HW_ETHERNET_WIFI_READ_TIMEOUT_mSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_SPI_BUS_ETHERNET:        return __SPI_BUS_ETHERNET_READ_TIMEOUT_mSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_SPI_BUS_WIFI:            return __SPI_BUS_WIFI_READ_TIMEOUT_mSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_ETHERNET:     return __AT_COMMAND_ETHERNET_READ_TIMEOUT_mSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_WIFI:         return __AT_COMMAND_WIFI_READ_TIMEOUT_mSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_GSM_MODEM:    return __AT_COMMAND_GSM_MODEM_READ_TIMEOUT_mSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_LTE_MODEM_OVER_LWIP:     return __LTE_MODEM_OVER_LWIP_READ_TIMEOUT_mSEC__;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            break;
        }
    } while (0);

    return __AT_COMMAND_GSM_MODEM_READ_TIMEOUT_mSEC__;
}

static int _ssl_auth_mode_enum_To_int(const tommRoC_crypto_ssl_auth_mode_enum_t sslAuthMode) {

    switch (sslAuthMode) {

    case TOMMROC_CRYPTO_SSL_AUTH_MODE_VERIFY_NONE:      return MBEDTLS_SSL_VERIFY_NONE;
    case TOMMROC_CRYPTO_SSL_AUTH_MODE_VERIFY_OPTIONAL:  return MBEDTLS_SSL_VERIFY_OPTIONAL;
    case TOMMROC_CRYPTO_SSL_AUTH_MODE_VERIFY_REQUIRED:  return MBEDTLS_SSL_VERIFY_REQUIRED;

    }

    return MBEDTLS_SSL_VERIFY_UNSET;
}

static int _random(void* p_rng, unsigned char* output, size_t output_len) {

    TOMMROC_UTIL_UNUSED_PARAM(p_rng);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCCryptoRNDRetrive(output, (uint32_t) output_len));

    return 0;
}

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
                int32_t*                                                const   caChainVerifyResPtr) {

    char tcpPortStr[TOMMROC_STRING_U16_DEC_AS_STRING_MAX_ARRAY_SIZE_BYTE];

    uint32_t flags;

    int ret;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            TOMMROC_STRING_U16_ARRAY_TO_STRING(&tcpPort, 1, sizeof(tcpPortStr), tcpPortStr),
            TOMMRO_C_PARAM_ERR);

    // Initialize the session data
    mbedtls_net_init(&sslCtxPtr->mbedtlsNetContext);
    mbedtls_ssl_init(&sslCtxPtr->mbedtlsSSLContext);
    mbedtls_ssl_config_init(&sslCtxPtr->mbedtlsSSLConfig);
    mbedtls_x509_crt_init(&sslCtxPtr->mbedtlsX509CaChainCrt);
    mbedtls_x509_crt_init(&sslCtxPtr->mbedtlsX509ClientCrt);
    mbedtls_pk_init(&sslCtxPtr->mbedtlsPkClientPrivKey);

    // Initialize CA chain certificates
    if ((NULL != caChainDataPtr) && (0 != caChainDataSize)) {
        ret = mbedtls_x509_crt_parse(&sslCtxPtr->mbedtlsX509CaChainCrt, (const unsigned char*) caChainDataPtr, caChainDataSize);
        if (ret < 0) {
            return TOMMRO_C_LOW_LEVEL_ERR;
        }
    }

    // Initialize client certificates
    if ((NULL != clientCertDataPtr) && (0 != clientCertDataSize)) {
        ret = mbedtls_x509_crt_parse(&sslCtxPtr->mbedtlsX509ClientCrt, (const unsigned char*) clientCertDataPtr, clientCertDataSize);
        if (ret < 0) {
            return TOMMRO_C_LOW_LEVEL_ERR;
        }
    }

    // Initialize client private key
    if ((NULL != clientPrivKeyDataPtr) && (0 != clientPrivKeyDataSize)) {
#if (MBEDTLS_VERSION_MAJOR == 2)
        ret = mbedtls_pk_parse_key(&sslCtxPtr->mbedtlsPkClientPrivKey, (const unsigned char*) clientPrivKeyDataPtr, clientPrivKeyDataSize, NULL, 0);
#else
        ret = mbedtls_pk_parse_key(&sslCtxPtr->mbedtlsPkClientPrivKey, (const unsigned char*) clientPrivKeyDataPtr, clientPrivKeyDataSize, NULL, 0, NULL, 0);
#endif
        if (ret < 0) {
            return TOMMRO_C_LOW_LEVEL_ERR;
        }
    }

    // Start the connection
    ret = tommRoCSwTemplateSSLESP32WrapperCoreAltNetSocketsNetConnect(&sslCtxPtr->mbedtlsNetContext, hostStrPtr, tcpPortStr, MBEDTLS_NET_PROTO_TCP);
    if (0 != ret) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    // Setup stuff
    ret = mbedtls_ssl_config_defaults(&sslCtxPtr->mbedtlsSSLConfig, MBEDTLS_SSL_IS_CLIENT, MBEDTLS_SSL_TRANSPORT_STREAM, MBEDTLS_SSL_PRESET_DEFAULT);
    if (0 != ret) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    mbedtls_ssl_conf_authmode(&sslCtxPtr->mbedtlsSSLConfig, _ssl_auth_mode_enum_To_int(sslAuthMode));
    if ((NULL != caChainDataPtr) && (0 != caChainDataSize)) {
        mbedtls_ssl_conf_ca_chain(&sslCtxPtr->mbedtlsSSLConfig, &sslCtxPtr->mbedtlsX509CaChainCrt, NULL);
    }
    mbedtls_ssl_conf_rng(&sslCtxPtr->mbedtlsSSLConfig, _random, NULL);

    if ((NULL != clientCertDataPtr) && (0 != clientCertDataSize) && (NULL != clientPrivKeyDataPtr) && (0 != clientPrivKeyDataSize)) {
        ret = mbedtls_ssl_conf_own_cert(&sslCtxPtr->mbedtlsSSLConfig, &sslCtxPtr->mbedtlsX509ClientCrt, &sslCtxPtr->mbedtlsPkClientPrivKey);
        if (0 != ret) {
            return TOMMRO_C_LOW_LEVEL_ERR;
        }
    }
    else if ((NULL != clientCertDataPtr) && (0 != clientCertDataSize)) {
        ret = mbedtls_ssl_conf_own_cert(&sslCtxPtr->mbedtlsSSLConfig, &sslCtxPtr->mbedtlsX509ClientCrt, NULL);
        if (0 != ret) {
            return TOMMRO_C_LOW_LEVEL_ERR;
        }
    }
    else if ((NULL != clientPrivKeyDataPtr) && (0 != clientPrivKeyDataSize)) {
        ret = mbedtls_ssl_conf_own_cert(&sslCtxPtr->mbedtlsSSLConfig, NULL, &sslCtxPtr->mbedtlsPkClientPrivKey);
        if (0 != ret) {
            return TOMMRO_C_LOW_LEVEL_ERR;
        }
    }

    ret = mbedtls_ssl_setup(&sslCtxPtr->mbedtlsSSLContext, &sslCtxPtr->mbedtlsSSLConfig);
    if (0 != ret) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    ret = mbedtls_ssl_set_hostname(&sslCtxPtr->mbedtlsSSLContext, hostStrPtr);
    if (0 != ret) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    mbedtls_ssl_set_bio(&sslCtxPtr->mbedtlsSSLContext, &sslCtxPtr->mbedtlsNetContext, tommRoCSwTemplateSSLESP32WrapperCoreAltNetSocketsNetSend, tommRoCSwTemplateSSLESP32WrapperCoreAltNetSocketsNetRecv, tommRoCSwTemplateSSLESP32WrapperCoreAltNetSocketsNetRecvTimeout);
    mbedtls_ssl_conf_read_timeout(&sslCtxPtr->mbedtlsSSLConfig, _get_for_handshake_read_timeout_msec());

    // Handshake
    while ((ret = mbedtls_ssl_handshake(&sslCtxPtr->mbedtlsSSLContext)) != 0) {
        if ((ret != MBEDTLS_ERR_SSL_WANT_READ) && (ret != MBEDTLS_ERR_SSL_WANT_WRITE)) {

            flags = mbedtls_ssl_get_verify_result(&sslCtxPtr->mbedtlsSSLContext);

            *caChainVerifyResPtr = *(int32_t*)&flags;

            return TOMMRO_C_LOW_LEVEL_ERR;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));
    }

    if (TOMMROC_CRYPTO_SSL_AUTH_MODE_VERIFY_REQUIRED == sslAuthMode) {
        flags = mbedtls_ssl_get_verify_result(&sslCtxPtr->mbedtlsSSLContext);
    }
    else {
        flags = 0;
    }

    *caChainVerifyResPtr = *(int32_t*)&flags;

    if (0 != flags) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateSSLESP32WrapperCoreWrite(
                tommRoC_sw_template_ssl_esp32_wrapper_core_context_t*   const   sslCtxPtr,
        const   void*                                                   const   writeBufferPtr,
        const   uint32_t                                                        writeBufferLen,
                int32_t*                                                const   writtenLenPtr,
        const   uint32_t                                                        writeTimeoutMsec) {

    tommRoC_timer_t timer;

    uint32_t remaining;
    const void* ptr;
    uint32_t sent;

    int ret;

    ptr         = writeBufferPtr;
    remaining   = writeBufferLen;
    sent        = 0;

    mbedtls_ssl_conf_read_timeout(&sslCtxPtr->mbedtlsSSLConfig, _get_read_timeout_msec());

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, writeTimeoutMsec));

    while (remaining > 0) {

        ret = mbedtls_ssl_write(&sslCtxPtr->mbedtlsSSLContext, ptr, remaining);

        if (ret > 0) {
            ptr         += ret;
            remaining   -= ret;
            sent        += ret;
        }
        else if (ret == MBEDTLS_ERR_SSL_WANT_READ) {
        }
        else if (ret == MBEDTLS_ERR_SSL_WANT_WRITE) {
        }
        else if (ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY) {
            *writtenLenPtr = (0 != sent) ? ((int32_t) sent) : ((int32_t) -1);
            return (0 != sent) ? (TOMMRO_C_ERR_SUCCESS) : (TOMMRO_C_LOW_LEVEL_ERR);
        }
        else if (ret < 0) {
            *writtenLenPtr = (0 != sent) ? ((int32_t) sent) : ((int32_t) -1);
            return (0 != sent) ? (TOMMRO_C_ERR_SUCCESS) : (TOMMRO_C_LOW_LEVEL_ERR);
        }
        else if (ret == 0) {
            if (0 != sent) {
                *writtenLenPtr = (0 != sent) ? ((int32_t) sent) : ((int32_t) -1);
                return (0 != sent) ? (TOMMRO_C_ERR_SUCCESS) : (TOMMRO_C_LOW_LEVEL_ERR);
            }
        }

        if (remaining > 0) {
            if (TOMMRO_C_TIMER_EXPIRED_ERR == tommRoCTimerIsExpired(&timer)) {
                *writtenLenPtr = (int32_t) sent;
                return (0 != sent) ? (TOMMRO_C_ERR_SUCCESS) : (TOMMRO_C_TIMEOUT_ERR);
            }

            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));
        }
        else {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(0));
        }
    }

    *writtenLenPtr = (int32_t) sent;

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateSSLESP32WrapperCoreRead(
                tommRoC_sw_template_ssl_esp32_wrapper_core_context_t*   const   sslCtxPtr,
                void*                                                   const   readBufferPtr,
        const   uint32_t                                                        readBufferLen,
                int32_t*                                                const   readLenPtr,
        const   uint32_t                                                        readTimeoutMsec) {

    tommRoC_timer_t timer;

    uint32_t remaining;
    void* ptr;
    uint32_t recv;

    int ret;

    ptr         = readBufferPtr;
    remaining   = readBufferLen;
    recv        = 0;

    mbedtls_ssl_conf_read_timeout(&sslCtxPtr->mbedtlsSSLConfig, _get_read_timeout_msec());

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, readTimeoutMsec));

    while (remaining > 0) {

        ret = mbedtls_ssl_read(&sslCtxPtr->mbedtlsSSLContext, ptr, remaining);

        if (ret > 0) {
            ptr         += ret;
            remaining   -= ret;
            recv        += ret;
        }
        else if (ret == MBEDTLS_ERR_SSL_WANT_READ) {
        }
        else if (ret == MBEDTLS_ERR_SSL_WANT_WRITE) {
        }
        else if (ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY) {
            *readLenPtr = (0 != recv) ? ((int32_t) recv) : ((int32_t) -1);
            return (0 != recv) ? (TOMMRO_C_ERR_SUCCESS) : (TOMMRO_C_LOW_LEVEL_ERR);
        }
        else if (ret < 0) {
            *readLenPtr = (0 != recv) ? ((int32_t) recv) : ((int32_t) -1);
            return (0 != recv) ? (TOMMRO_C_ERR_SUCCESS) : (TOMMRO_C_LOW_LEVEL_ERR);
        }
        else if (ret == 0) {
            if (0 != recv) {
                *readLenPtr = (0 != recv) ? ((int32_t) recv) : ((int32_t) -1);
                return (0 != recv) ? (TOMMRO_C_ERR_SUCCESS) : (TOMMRO_C_LOW_LEVEL_ERR);
            }
        }

        if (remaining > 0) {
            if (TOMMRO_C_TIMER_EXPIRED_ERR == tommRoCTimerIsExpired(&timer)) {
                *readLenPtr = (int32_t) recv;
                return (0 != recv) ? (TOMMRO_C_ERR_SUCCESS) : (TOMMRO_C_TIMEOUT_ERR);
            }

            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));
        }
        else {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(0));
        }
    }

    *readLenPtr = (int32_t) recv;

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateSSLESP32WrapperCoreCloseNotifyFree(
                tommRoC_sw_template_ssl_esp32_wrapper_core_context_t*   const   sslCtxPtr) {

    mbedtls_ssl_close_notify(&sslCtxPtr->mbedtlsSSLContext);

    mbedtls_net_free(&sslCtxPtr->mbedtlsNetContext);
    mbedtls_x509_crt_free(&sslCtxPtr->mbedtlsX509CaChainCrt);
    mbedtls_x509_crt_free(&sslCtxPtr->mbedtlsX509ClientCrt);
    mbedtls_pk_free(&sslCtxPtr->mbedtlsPkClientPrivKey);
    mbedtls_ssl_free(&sslCtxPtr->mbedtlsSSLContext);
    mbedtls_ssl_config_free(&sslCtxPtr->mbedtlsSSLConfig);

    return TOMMRO_C_ERR_SUCCESS;
}

#endif
