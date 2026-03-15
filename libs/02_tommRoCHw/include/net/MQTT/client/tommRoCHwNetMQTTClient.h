
#ifndef TOMMROC_HW_NET_MQTT_CLIENT_H_
#define TOMMROC_HW_NET_MQTT_CLIENT_H_

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
#include "net/MQTT/client/tommRoCHwNetMQTTClientDEF.h"

#include "net/MQTT/tommRoCHwNetMQTTDEF.h"

#include "comm/tommRoCHwComm.h"

#include "tommRoCHwErr.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Default cache buffer size [byte] for a plain MQTT client object.
#define TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_DEFAULT_CACHE_SEND_BUFFER_SIZE (256)
#define TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_DEFAULT_CACHE_READ_BUFFER_SIZE (256)

// Default cache buffer size [byte] for a SSL MQTT client object.
#define TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_SEND_BUFFER_SIZE   (512)
#define TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_READ_BUFFER_SIZE   (512)


#if defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_8_BIT_SIZE)
#define TOMMROC_HW_NET_MQTT_CLIENT_HANDLE_SIZE  ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMROC_HW_NET_MQTT_CLIENT_HANDLE_SIZE  ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE)
#define TOMMROC_HW_NET_MQTT_CLIENT_HANDLE_SIZE  (160)
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMROC_HW_NET_MQTT_CLIENT_HANDLE_SIZE  (272)
#endif


/******************* Not static */

#define TOMMROC_HW_NET_MQTT_CLIENT_DECLARE(                                                                                     \
        mqttClientName,                                                                                                         \
        cacheSendBufferSize,                                                                                                    \
        cacheReadBufferSize)                                                                                                    \
        char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, mqttClientName, _, CacheSendBuffer, __)[cacheSendBufferSize];          \
        char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, mqttClientName, _, CacheReadBuffer, __)[cacheReadBufferSize];          \
        tommRoC_hw_net_mqtt_client_t mqttClientName

#define TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_DECLARE_AND_INIT(                                                                      \
        mqttClientName,                                                                                                         \
        guardPtr,                                                                                                               \
        cacheSendBufferSize,                                                                                                    \
        cacheReadBufferSize)                                                                                                    \
                                                                                                                                \
        TOMMROC_HW_NET_MQTT_CLIENT_DECLARE(mqttClientName, cacheSendBufferSize, cacheReadBufferSize);                           \
                                                                                                                                \
        do {                                                                                                                    \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                                           \
                    tommRoCHwNetMQTTClientPlainInit(                                                                            \
                            guardPtr,                                                                                           \
                            (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, mqttClientName, _, CacheSendBuffer, __),        \
                            cacheSendBufferSize,                                                                                \
                            (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, mqttClientName, _, CacheReadBuffer, __),        \
                            cacheReadBufferSize,                                                                                \
                            &mqttClientName));                                                                                  \
        } while (0)

#define TOMMROC_HW_NET_MQTT_CLIENT_SSL_DECLARE_AND_INIT(                                                                        \
        mqttClientName,                                                                                                         \
        sslCtxPtr,                                                                                                              \
        caChainDataPtr,                                                                                                         \
        caChainDataSize,                                                                                                        \
        clientCertDataPtr,                                                                                                      \
        clientCertDataSize,                                                                                                     \
        clientPrivKeyDataPtr,                                                                                                   \
        clientPrivKeyDataSize,                                                                                                  \
        sslAuthMode,                                                                                                            \
        guardPtr,                                                                                                               \
        cacheSendBufferSize,                                                                                                    \
        cacheReadBufferSize)                                                                                                    \
                                                                                                                                \
        TOMMROC_HW_NET_MQTT_CLIENT_DECLARE(mqttClientName, cacheSendBufferSize, cacheReadBufferSize);                           \
                                                                                                                                \
        do {                                                                                                                    \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                                           \
                    tommRoCHwNetMQTTClientSSLInit(                                                                              \
                            sslCtxPtr,                                                                                          \
                            caChainDataPtr,                                                                                     \
                            caChainDataSize,                                                                                    \
                            clientCertDataPtr,                                                                                  \
                            clientCertDataSize,                                                                                 \
                            clientPrivKeyDataPtr,                                                                               \
                            clientPrivKeyDataSize,                                                                              \
                            sslAuthMode,                                                                                        \
                            guardPtr,                                                                                           \
                            (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, mqttClientName, _, CacheSendBuffer, __),        \
                            cacheSendBufferSize,                                                                                \
                            (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, mqttClientName, _, CacheReadBuffer, __),        \
                            cacheReadBufferSize,                                                                                \
                            &mqttClientName));                                                                                  \
        } while (0)


/******************* Static */

#define TOMMROC_HW_NET_MQTT_CLIENT_STATIC_DECLARE(                                                                              \
        mqttClientName,                                                                                                         \
        cacheSendBufferSize,                                                                                                    \
        cacheReadBufferSize)                                                                                                    \
        static char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, mqttClientName, _, CacheSendBuffer, __)[cacheSendBufferSize];   \
        static char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, mqttClientName, _, CacheReadBuffer, __)[cacheReadBufferSize];   \
        static tommRoC_hw_net_mqtt_client_t mqttClientName

#define TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_STATIC_DECLARE_AND_INIT(                                                               \
        mqttClientName,                                                                                                         \
        guardPtr,                                                                                                               \
        cacheSendBufferSize,                                                                                                    \
        cacheReadBufferSize)                                                                                                    \
                                                                                                                                \
        TOMMROC_HW_NET_MQTT_CLIENT_STATIC_DECLARE(mqttClientName, cacheSendBufferSize, cacheReadBufferSize);                    \
                                                                                                                                \
        do {                                                                                                                    \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                                           \
                    tommRoCHwNetMQTTClientPlainInit(                                                                            \
                            guardPtr,                                                                                           \
                            (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, mqttClientName, _, CacheSendBuffer, __),        \
                            cacheSendBufferSize,                                                                                \
                            (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, mqttClientName, _, CacheReadBuffer, __),        \
                            cacheReadBufferSize,                                                                                \
                            &mqttClientName));                                                                                  \
        } while (0)

#define TOMMROC_HW_NET_MQTT_CLIENT_SSL_STATIC_DECLARE_AND_INIT(                                                                 \
        mqttClientName,                                                                                                         \
        sslCtxPtr,                                                                                                              \
        caChainDataPtr,                                                                                                         \
        caChainDataSize,                                                                                                        \
        clientCertDataPtr,                                                                                                      \
        clientCertDataSize,                                                                                                     \
        clientPrivKeyDataPtr,                                                                                                   \
        clientPrivKeyDataSize,                                                                                                  \
        sslAuthMode,                                                                                                            \
        guardPtr,                                                                                                               \
        cacheSendBufferSize,                                                                                                    \
        cacheReadBufferSize)                                                                                                    \
                                                                                                                                \
        TOMMROC_HW_NET_MQTT_CLIENT_STATIC_DECLARE(mqttClientName, cacheSendBufferSize, cacheReadBufferSize);                    \
                                                                                                                                \
        do {                                                                                                                    \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                                           \
                    tommRoCHwNetMQTTClientSSLInit(                                                                              \
                            sslCtxPtr,                                                                                          \
                            caChainDataPtr,                                                                                     \
                            caChainDataSize,                                                                                    \
                            clientCertDataPtr,                                                                                  \
                            clientCertDataSize,                                                                                 \
                            clientPrivKeyDataPtr,                                                                               \
                            clientPrivKeyDataSize,                                                                              \
                            sslAuthMode,                                                                                        \
                            guardPtr,                                                                                           \
                            (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, mqttClientName, _, CacheSendBuffer, __),        \
                            cacheSendBufferSize,                                                                                \
                            (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, mqttClientName, _, CacheReadBuffer, __),        \
                            cacheReadBufferSize,                                                                                \
                            &mqttClientName));                                                                                  \
        } while (0)


/******************* Not static default size */

#define TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_DECLARE_DEFAULT_CACHE_BUFFER_SIZE(mqttClientName)                                      \
        TOMMROC_HW_NET_MQTT_CLIENT_DECLARE(                                                                                     \
                mqttClientName,                                                                                                 \
                TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_DEFAULT_CACHE_SEND_BUFFER_SIZE,                                                \
                TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_DEFAULT_CACHE_READ_BUFFER_SIZE)

#define TOMMROC_HW_NET_MQTT_CLIENT_SSL_DECLARE_DEFAULT_CACHE_BUFFER_SIZE(mqttClientName)                                        \
        TOMMROC_HW_NET_MQTT_CLIENT_DECLARE(                                                                                     \
                mqttClientName,                                                                                                 \
                TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_SEND_BUFFER_SIZE,                                                  \
                TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_READ_BUFFER_SIZE)

#define TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_DECLARE_AND_INIT_DEFAULT_CACHE_BUFFER_SIZE(                                            \
        mqttClientName,                                                                                                         \
        guardPtr)                                                                                                               \
        TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_DECLARE_AND_INIT(                                                                      \
                mqttClientName,                                                                                                 \
                guardPtr,                                                                                                       \
                TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_DEFAULT_CACHE_SEND_BUFFER_SIZE,                                                \
                TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_DEFAULT_CACHE_READ_BUFFER_SIZE)

#define TOMMROC_HW_NET_MQTT_CLIENT_SSL_DECLARE_AND_INIT_DEFAULT_CACHE_BUFFER_SIZE(                                              \
        mqttClientName,                                                                                                         \
        sslCtxPtr,                                                                                                              \
        caChainDataPtr,                                                                                                         \
        caChainDataSize,                                                                                                        \
        clientCertDataPtr,                                                                                                      \
        clientCertDataSize,                                                                                                     \
        clientPrivKeyDataPtr,                                                                                                   \
        clientPrivKeyDataSize,                                                                                                  \
        sslAuthMode,                                                                                                            \
        guardPtr)                                                                                                               \
        TOMMROC_HW_NET_MQTT_CLIENT_SSL_DECLARE_AND_INIT(                                                                        \
                mqttClientName,                                                                                                 \
                sslCtxPtr,                                                                                                      \
                caChainDataPtr,                                                                                                 \
                caChainDataSize,                                                                                                \
                clientCertDataPtr,                                                                                              \
                clientCertDataSize,                                                                                             \
                clientPrivKeyDataPtr,                                                                                           \
                clientPrivKeyDataSize,                                                                                          \
                sslAuthMode,                                                                                                    \
                guardPtr,                                                                                                       \
                TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_SEND_BUFFER_SIZE,                                                  \
                TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_READ_BUFFER_SIZE)


/******************* Static default size */

#define TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_STATIC_DECLARE_DEFAULT_CACHE_BUFFER_SIZE(mqttClientName)                               \
        TOMMROC_HW_NET_MQTT_CLIENT_STATIC_DECLARE(                                                                              \
                mqttClientName,                                                                                                 \
                TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_DEFAULT_CACHE_SEND_BUFFER_SIZE,                                                \
                TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_DEFAULT_CACHE_READ_BUFFER_SIZE)

#define TOMMROC_HW_NET_MQTT_CLIENT_SSL_STATIC_DECLARE_DEFAULT_CACHE_BUFFER_SIZE(mqttClientName)                                 \
        TOMMROC_HW_NET_MQTT_CLIENT_STATIC_DECLARE(                                                                              \
                mqttClientName,                                                                                                 \
                TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_SEND_BUFFER_SIZE,                                                  \
                TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_READ_BUFFER_SIZE)

#define TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_STATIC_DECLARE_AND_INIT_DEFAULT_CACHE_BUFFER_SIZE(                                     \
        mqttClientName,                                                                                                         \
        guardPtr)                                                                                                               \
        TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_STATIC_DECLARE_AND_INIT(                                                               \
                mqttClientName,                                                                                                 \
                guardPtr,                                                                                                       \
                TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_DEFAULT_CACHE_SEND_BUFFER_SIZE,                                                \
                TOMMROC_HW_NET_MQTT_CLIENT_PLAIN_DEFAULT_CACHE_READ_BUFFER_SIZE)

#define TOMMROC_HW_NET_MQTT_CLIENT_SSL_STATIC_DECLARE_AND_INIT_DEFAULT_CACHE_BUFFER_SIZE(                                       \
        mqttClientName,                                                                                                         \
        sslCtxPtr,                                                                                                              \
        caChainDataPtr,                                                                                                         \
        caChainDataSize,                                                                                                        \
        clientCertDataPtr,                                                                                                      \
        clientCertDataSize,                                                                                                     \
        clientPrivKeyDataPtr,                                                                                                   \
        clientPrivKeyDataSize,                                                                                                  \
        sslAuthMode,                                                                                                            \
        guardPtr)                                                                                                               \
        TOMMROC_HW_NET_MQTT_CLIENT_SSL_STATIC_DECLARE_AND_INIT(                                                                 \
                mqttClientName,                                                                                                 \
                sslCtxPtr,                                                                                                      \
                caChainDataPtr,                                                                                                 \
                caChainDataSize,                                                                                                \
                clientCertDataPtr,                                                                                              \
                clientCertDataSize,                                                                                             \
                clientPrivKeyDataPtr,                                                                                           \
                clientPrivKeyDataSize,                                                                                          \
                sslAuthMode,                                                                                                    \
                guardPtr,                                                                                                       \
                TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_SEND_BUFFER_SIZE,                                                  \
                TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_READ_BUFFER_SIZE)


/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef struct {

    tommRoC_hw_net_mqtt_def_version_enum_t  MQTTVersion;        // MQTT Version (3.1 or 3.1.1)
    char*                                   clientIDStrPtr;     // Client ID string pointer.
    char*                                   usernameStrPtr;     // Username string pointer (NULL if not used).
    char*                                   passwordStrPtr;     // Password string pointer (NULL if not used).

} tommRoC_hw_net_mqtt_client_info_t;

#define __EMPTY_tommRoC_hw_net_mqtt_client_info_t__                 \
{                                                                   \
    /* .MQTTVersion */      TOMMROC_HW_NET_MQTT_DEF_VERSION_3_1,    \
    /* .clientIDStrPtr */   NULL,                                   \
    /* .usernameStrPtr */   NULL,                                   \
    /* .passwordStrPtr */   NULL,                                   \
}


// MQTT client.
typedef struct {
    uint8_t data[TOMMROC_HW_NET_MQTT_CLIENT_HANDLE_SIZE];
} tommRoC_hw_net_mqtt_client_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init a MQTT client over plain socket endpoint for communication.
 *
 * param[in]        guardPtr                MQTT client guard (NULL if none).
 * param[in]        cacheSendBufferPtr      memory buffer used for low level send operation pointer.
 * param[in]        cacheSendBufferSize     memory buffer used for low level send operation size [byte].
 * param[in]        cacheReadBufferPtr      memory buffer used for low level read operation pointer.
 * param[in]        cacheReadBufferSize     memory buffer used for low level read operation size [byte].
 * param[out]       mqttClientPtr           output MQTT client endpoint pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetMQTTClientPlainInit(
        const   tommRoC_guard_t*                                        const   guardPtr,
                void*                                                   const   cacheSendBufferPtr,
        const   uint32_t                                                        cacheSendBufferSize,
                void*                                                   const   cacheReadBufferPtr,
        const   uint32_t                                                        cacheReadBufferSize,
                tommRoC_hw_net_mqtt_client_t*                           const   mqttClientPtr);

/**
 * Init a MQTT client over SSL socket endpoint for communication.
 *
 * param[in/out]    sslCtxPtr               SSL opaque context pointer.
 * param[in]        caChainDataPtr          CA chain certificate (PEM or DER format) data buffer pointer (NULL if none).
 * param[in]        caChainDataSize         CA chain certificate (including the terminating character) size [byte] (0 if none).
 * param[in]        clientCertDataPtr       client certificate (PEM or DER format) data buffer pointer (NULL if none).
 * param[in]        clientCertDataSize      client certificate (including the terminating character) size [byte] (0 if none).
 * param[in]        clientPrivKeyDataPtr    client private key (PEM or DER format) data buffer pointer (NULL if none).
 * param[in]        clientPrivKeyDataSize   client private key (including the terminating character) size [byte] (0 if none).
 * param[in]        sslAuthMode             certificate verify mode.
 * param[in]        guardPtr                MQTT client guard (NULL if none).
 * param[in]        cacheSendBufferPtr      memory buffer used for low level send operation pointer.
 * param[in]        cacheSendBufferSize     memory buffer used for low level send operation size [byte].
 * param[in]        cacheReadBufferPtr      memory buffer used for low level read operation pointer.
 * param[in]        cacheReadBufferSize     memory buffer used for low level read operation size [byte].
 * param[out]       mqttClientPtr           output MQTT client endpoint pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetMQTTClientSSLInit(
                void*                                                   const   sslCtxPtr,
        const   void*                                                   const   caChainDataPtr,
        const   uint32_t                                                        caChainDataSize,
        const   void*                                                   const   clientCertDataPtr,
        const   uint32_t                                                        clientCertDataSize,
        const   void*                                                   const   clientPrivKeyDataPtr,
        const   uint32_t                                                        clientPrivKeyDataSize,
        const   tommRoC_crypto_ssl_auth_mode_enum_t                             sslAuthMode,
        const   tommRoC_guard_t*                                        const   guardPtr,
                void*                                                   const   cacheSendBufferPtr,
        const   uint32_t                                                        cacheSendBufferSize,
                void*                                                   const   cacheReadBufferPtr,
        const   uint32_t                                                        cacheReadBufferSize,
                tommRoC_hw_net_mqtt_client_t*                           const   mqttClientPtr);

/**
 * Connect a MQTT client endpoint to the IPv4 address MQTT broker.
 *
 * param[in/out]    mqttClientPtr           MQTT client endpoint pointer.
 * param[in]        ipV4AddPtr              IPv4 address MQTT broker to connect pointer.
 * param[in]        port                    MQTT broker TCP port.
 * param[in]        clientInfoPtr           MQTT client info pointer.
 * param[in]        cleanSession            MQTT clean session flag.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetMQTTClientConnect(
                tommRoC_hw_net_mqtt_client_t*                           const   mqttClientPtr,
        const   tommRoC_hw_comm_ip_v4_add_t*                            const   ipV4AddPtr,
        const   uint16_t                                                        port,
        const   tommRoC_hw_net_mqtt_client_info_t*                      const   clientInfoPtr,
        const   tommRoC_hw_net_mqtt_client_def_clean_session_enum_t             cleanSession);

/**
 * Connect a MQTT client endpoint to the string host address MQTT broker.
 *
 * param[in/out]    mqttClientPtr           MQTT client endpoint pointer.
 * param[in]        hostStrPtr              host address MQTT broker as string to connect pointer.
 * param[in]        port                    MQTT broker TCP port.
 * param[in]        clientInfoPtr           MQTT client info pointer.
 * param[in]        cleanSession            MQTT clean session flag.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetMQTTClientConnectHost(
                tommRoC_hw_net_mqtt_client_t*                           const   mqttClientPtr,
        const   char*                                                   const   hostStrPtr,
        const   uint16_t                                                        port,
        const   tommRoC_hw_net_mqtt_client_info_t*                      const   clientInfoPtr,
        const   tommRoC_hw_net_mqtt_client_def_clean_session_enum_t             cleanSession);

/**
 * Disconnect a MQTT client endpoint.
 *
 * param[in/out]    mqttClientPtr           MQTT client endpoint pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetMQTTClientDisconnect(
                tommRoC_hw_net_mqtt_client_t*                           const   mqttClientPtr);

/**
 * Check if a MQTT client endpoint is connected to a MQTT broker.
 *
 * param[in/out]    mqttClientPtr           MQTT client endpoint pointer.
 * param[out]       isConnectedPtr          is connected boolean pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetMQTTClientIsConnected(
                tommRoC_hw_net_mqtt_client_t*                           const   mqttClientPtr,
                bool*                                                   const   isConnectedPtr);

/**
 * Publish data to an MQTT topic.
 *
 * param[in/out]    mqttClientPtr           MQTT client endpoint pointer.
 * param[in]        topicStrPtr             MQTT topic string pointer.
 * param[in]        payloadBufferPtr        payload buffer pointer.
 * param[in]        payloadBufferLen        payload buffer length [byte].
 * param[in]        QoS                     Quality of Service.
 * param[in]        retain                  retain flag.
 * param[in]        msgId                   message ID.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetMQTTClientPublish(
                tommRoC_hw_net_mqtt_client_t*                           const   mqttClientPtr,
        const   char*                                                   const   topicStrPtr,
        const   void*                                                   const   payloadBufferPtr,
        const   uint32_t                                                        payloadBufferLen,
        const   tommRoC_hw_net_mqtt_client_def_qos_enum_t                       QoS,
        const   tommRoC_hw_net_mqtt_client_def_retain_enum_t                    retain,
        const   uint16_t                                                        msgId);

/**
 * Subscribe an MQTT client to a MQTT topic.
 *
 * param[in/out]    mqttClientPtr           MQTT client endpoint pointer.
 * param[in]        topicStrPtr             MQTT topic string pointer.
 * param[in]        QoS                     Quality of Service.
 * param[in]        incomingDataCb          notification incoming data callback function.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetMQTTClientSubscribe(
                tommRoC_hw_net_mqtt_client_t*                           const   mqttClientPtr,
        const   char*                                                   const   topicStrPtr,
        const   tommRoC_hw_net_mqtt_client_def_qos_enum_t                       QoS,
        const   tommRoC_hw_net_mqtt_client_def_incoming_data_cb_t               incomingDataCb);

/**
 * Unsubscribe an MQTT client from a MQTT topic.
 *
 * param[in/out]    mqttClientPtr           MQTT client endpoint pointer.
 * param[in]        topicStrPtr             MQTT topic string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetMQTTClientUnsubscribe(
                tommRoC_hw_net_mqtt_client_t*                           const   mqttClientPtr,
        const   char*                                                   const   topicStrPtr);

/**
 * Yield MQTT client - MQTT background.
 *
 * param[in/out]    mqttClientPtr           MQTT client endpoint pointer.
 * param[in]        timeoutSec              MQTT yield timeout [sec].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetMQTTClientYield(
                tommRoC_hw_net_mqtt_client_t*                           const   mqttClientPtr,
        const   uint32_t                                                        timeoutSec);

/**
 * Yield MQTT client - MQTT background (timeout msec version).
 *
 * param[in/out]    mqttClientPtr           MQTT client endpoint pointer.
 * param[in]        timeoutMsec             MQTT yield timeout [msec].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetMQTTClientYieldMsec(
                tommRoC_hw_net_mqtt_client_t*                           const   mqttClientPtr,
        const   uint32_t                                                        timeoutMsec);

/**
 * Convert an opaque to known message data.
 *
 * param[in/out]    messageDataCbPtr        MQTT opaque message data pointer.
 * param[in]        messagePtr              MQTT known message data pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetMQTTClientGetMessage(
        const   tommRoC_hw_net_mqtt_client_def_incoming_message_data_t* const   messageDataCbPtr,
                tommRoC_hw_net_mqtt_client_def_message_t*               const   messagePtr);

#endif
