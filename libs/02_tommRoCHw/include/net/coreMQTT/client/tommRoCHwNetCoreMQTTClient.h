
#ifndef TOMMROC_HW_NET_CORE_MQTT_CLIENT_H_
#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_H_

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
#include "net/coreMQTT/client/tommRoCHwNetCoreMQTTClientDEF.h"

#include "net/coreMQTT/tommRoCHwNetCoreMQTTDEF.h"

#include "comm/tommRoCHwComm.h"

#include "tommRoCHwErr.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Default network buffer size [byte] for a plain MQTT client object.
#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_PLAIN_DEFAULT_NETWORK_BUFFER_SIZE   (256)
// Default network buffer size [byte] for a SSL MQTT client object.
#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_SSL_DEFAULT_NETWORK_BUFFER_SIZE     (512)


#if defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_8_BIT_SIZE)
#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_HANDLE_SIZE ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_HANDLE_SIZE ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE)
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_HANDLE_SIZE (228)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_HANDLE_SIZE (312)
#endif
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_HANDLE_SIZE (456)
#endif


/******************* Not static */

#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_DECLARE(                                                                                \
        coreMQTTClientName,                                                                                                     \
        networkBufferSize)                                                                                                      \
        uint8_t TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, coreMQTTClientName, _, NetworkBuffer, __)[networkBufferSize];       \
        tommRoC_hw_net_core_mqtt_client_t coreMQTTClientName

#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_PLAIN_DECLARE_AND_INIT(                                                                 \
        coreMQTTClientName,                                                                                                     \
        networkBufferSize,                                                                                                      \
        notifyDataCb,                                                                                                           \
        guardPtr)                                                                                                               \
                                                                                                                                \
        TOMMROC_HW_NET_CORE_MQTT_CLIENT_DECLARE(coreMQTTClientName, networkBufferSize);                                         \
                                                                                                                                \
        do {                                                                                                                    \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                                           \
                    tommRoCHwNetCoreMQTTClientPlainInit(                                                                        \
                            (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, coreMQTTClientName, _, NetworkBuffer, __),      \
                            networkBufferSize,                                                                                  \
                            notifyDataCb,                                                                                       \
                            guardPtr,                                                                                           \
                            &coreMQTTClientName));                                                                              \
        } while (0)

#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_SSL_DECLARE_AND_INIT(                                                                   \
        coreMQTTClientName,                                                                                                     \
        networkBufferSize,                                                                                                      \
        notifyDataCb,                                                                                                           \
        sslCtxPtr,                                                                                                              \
        caChainDataPtr,                                                                                                         \
        caChainDataSize,                                                                                                        \
        clientCertDataPtr,                                                                                                      \
        clientCertDataSize,                                                                                                     \
        clientPrivKeyDataPtr,                                                                                                   \
        clientPrivKeyDataSize,                                                                                                  \
        sslAuthMode,                                                                                                            \
        guardPtr)                                                                                                               \
                                                                                                                                \
        TOMMROC_HW_NET_CORE_MQTT_CLIENT_DECLARE(coreMQTTClientName, networkBufferSize);                                         \
                                                                                                                                \
        do {                                                                                                                    \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                                           \
                    tommRoCHwNetCoreMQTTClientSSLInit(                                                                          \
                            (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, coreMQTTClientName, _, NetworkBuffer, __),      \
                            networkBufferSize,                                                                                  \
                            notifyDataCb,                                                                                       \
                            sslCtxPtr,                                                                                          \
                            caChainDataPtr,                                                                                     \
                            caChainDataSize,                                                                                    \
                            clientCertDataPtr,                                                                                  \
                            clientCertDataSize,                                                                                 \
                            clientPrivKeyDataPtr,                                                                               \
                            clientPrivKeyDataSize,                                                                              \
                            sslAuthMode,                                                                                        \
                            guardPtr,                                                                                           \
                            &coreMQTTClientName));                                                                              \
        } while (0)


/******************* Static */

#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_STATIC_DECLARE(                                                                         \
        coreMQTTClientName,                                                                                                     \
        networkBufferSize)                                                                                                      \
        static uint8_t TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, coreMQTTClientName, _, NetworkBuffer, __)[networkBufferSize];\
        static tommRoC_hw_net_core_mqtt_client_t coreMQTTClientName

#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_PLAIN_STATIC_DECLARE_AND_INIT(                                                          \
        coreMQTTClientName,                                                                                                     \
        networkBufferSize,                                                                                                      \
        notifyDataCb,                                                                                                           \
        guardPtr)                                                                                                               \
                                                                                                                                \
        TOMMROC_HW_NET_CORE_MQTT_CLIENT_STATIC_DECLARE(coreMQTTClientName, networkBufferSize);                                  \
                                                                                                                                \
        do {                                                                                                                    \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                                           \
                    tommRoCHwNetCoreMQTTClientPlainInit(                                                                        \
                            (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, coreMQTTClientName, _, NetworkBuffer, __),      \
                            networkBufferSize,                                                                                  \
                            notifyDataCb,                                                                                       \
                            guardPtr,                                                                                           \
                            &coreMQTTClientName));                                                                              \
        } while (0)

#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_SSL_STATIC_DECLARE_AND_INIT(                                                            \
        coreMQTTClientName,                                                                                                     \
        networkBufferSize,                                                                                                      \
        notifyDataCb,                                                                                                           \
        sslCtxPtr,                                                                                                              \
        caChainDataPtr,                                                                                                         \
        caChainDataSize,                                                                                                        \
        clientCertDataPtr,                                                                                                      \
        clientCertDataSize,                                                                                                     \
        clientPrivKeyDataPtr,                                                                                                   \
        clientPrivKeyDataSize,                                                                                                  \
        sslAuthMode,                                                                                                            \
        guardPtr)                                                                                                               \
                                                                                                                                \
        TOMMROC_HW_NET_CORE_MQTT_CLIENT_STATIC_DECLARE(coreMQTTClientName, networkBufferSize);                                  \
                                                                                                                                \
        do {                                                                                                                    \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                                           \
                    tommRoCHwNetCoreMQTTClientSSLInit(                                                                          \
                            (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, coreMQTTClientName, _, NetworkBuffer, __),      \
                            networkBufferSize,                                                                                  \
                            notifyDataCb,                                                                                       \
                            sslCtxPtr,                                                                                          \
                            caChainDataPtr,                                                                                     \
                            caChainDataSize,                                                                                    \
                            clientCertDataPtr,                                                                                  \
                            clientCertDataSize,                                                                                 \
                            clientPrivKeyDataPtr,                                                                               \
                            clientPrivKeyDataSize,                                                                              \
                            sslAuthMode,                                                                                        \
                            guardPtr,                                                                                           \
                            &coreMQTTClientName));                                                                              \
        } while (0)


/******************* Not static default size */

#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_PLAIN_DECLARE_DEFAULT_NETWORK_BUFFER_SIZE(coreMQTTClientName)                           \
        TOMMROC_HW_NET_CORE_MQTT_CLIENT_DECLARE(                                                                                \
                coreMQTTClientName,                                                                                             \
                TOMMROC_HW_NET_CORE_MQTT_CLIENT_PLAIN_DEFAULT_NETWORK_BUFFER_SIZE)

#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_SSL_DECLARE_DEFAULT_NETWORK_BUFFER_SIZE(coreMQTTClientName)                             \
        TOMMROC_HW_NET_CORE_MQTT_CLIENT_DECLARE(                                                                                \
                coreMQTTClientName,                                                                                             \
                TOMMROC_HW_NET_CORE_MQTT_CLIENT_SSL_DEFAULT_NETWORK_BUFFER_SIZE)

#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_PLAIN_DECLARE_AND_INIT_DEFAULT_NETWORK_BUFFER_SIZE(                                     \
        coreMQTTClientName,                                                                                                     \
        notifyDataCb,                                                                                                           \
        guardPtr)                                                                                                               \
        TOMMROC_HW_NET_CORE_MQTT_CLIENT_PLAIN_DECLARE_AND_INIT(                                                                 \
                coreMQTTClientName,                                                                                             \
                TOMMROC_HW_NET_CORE_MQTT_CLIENT_PLAIN_DEFAULT_NETWORK_BUFFER_SIZE,                                              \
                notifyDataCb,                                                                                                   \
                guardPtr)

#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_SSL_DECLARE_AND_INIT_DEFAULT_NETWORK_BUFFER_SIZE(                                       \
        coreMQTTClientName,                                                                                                     \
        notifyDataCb,                                                                                                           \
        sslCtxPtr,                                                                                                              \
        caChainDataPtr,                                                                                                         \
        caChainDataSize,                                                                                                        \
        clientCertDataPtr,                                                                                                      \
        clientCertDataSize,                                                                                                     \
        clientPrivKeyDataPtr,                                                                                                   \
        clientPrivKeyDataSize,                                                                                                  \
        sslAuthMode,                                                                                                            \
        guardPtr)                                                                                                               \
        TOMMROC_HW_NET_CORE_MQTT_CLIENT_SSL_DECLARE_AND_INIT(                                                                   \
                coreMQTTClientName,                                                                                             \
                TOMMROC_HW_NET_CORE_MQTT_CLIENT_SSL_DEFAULT_NETWORK_BUFFER_SIZE,                                                \
                notifyDataCb,                                                                                                   \
                sslCtxPtr,                                                                                                      \
                caChainDataPtr,                                                                                                 \
                caChainDataSize,                                                                                                \
                clientCertDataPtr,                                                                                              \
                clientCertDataSize,                                                                                             \
                clientPrivKeyDataPtr,                                                                                           \
                clientPrivKeyDataSize,                                                                                          \
                sslAuthMode,                                                                                                    \
                guardPtr)

/******************* Static default size */

#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_PLAIN_STATIC_DECLARE_DEFAULT_NETWORK_BUFFER_SIZE(coreMQTTClientName)                    \
        TOMMROC_HW_NET_CORE_MQTT_CLIENT_STATIC_DECLARE(                                                                         \
                coreMQTTClientName,                                                                                             \
                TOMMROC_HW_NET_CORE_MQTT_CLIENT_PLAIN_DEFAULT_NETWORK_BUFFER_SIZE)

#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_SSL_STATIC_DECLARE_DEFAULT_NETWORK_BUFFER_SIZE(coreMQTTClientName)                      \
        TOMMROC_HW_NET_CORE_MQTT_CLIENT_STATIC_DECLARE(                                                                         \
                coreMQTTClientName,                                                                                             \
                TOMMROC_HW_NET_CORE_MQTT_CLIENT_SSL_DEFAULT_NETWORK_BUFFER_SIZE)

#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_PLAIN_STATIC_DECLARE_AND_INIT_DEFAULT_NETWORK_BUFFER_SIZE(                              \
        coreMQTTClientName,                                                                                                     \
        guardPtr)                                                                                                               \
        TOMMROC_HW_NET_CORE_MQTT_CLIENT_PLAIN_STATIC_DECLARE_AND_INIT(                                                          \
                coreMQTTClientName,                                                                                             \
                TOMMROC_HW_NET_CORE_MQTT_CLIENT_PLAIN_DEFAULT_NETWORK_BUFFER_SIZE,                                              \
                notifyDataCb,                                                                                                   \
                guardPtr)

#define TOMMROC_HW_NET_CORE_MQTT_CLIENT_SSL_STATIC_DECLARE_AND_INIT_DEFAULT_NETWORK_BUFFER_SIZE(                                \
        coreMQTTClientName,                                                                                                     \
        notifyDataCb,                                                                                                           \
        sslCtxPtr,                                                                                                              \
        caChainDataPtr,                                                                                                         \
        caChainDataSize,                                                                                                        \
        clientCertDataPtr,                                                                                                      \
        clientCertDataSize,                                                                                                     \
        clientPrivKeyDataPtr,                                                                                                   \
        clientPrivKeyDataSize,                                                                                                  \
        sslAuthMode,                                                                                                            \
        guardPtr)                                                                                                               \
        TOMMROC_HW_NET_CORE_MQTT_CLIENT_SSL_STATIC_DECLARE_AND_INIT(                                                            \
                coreMQTTClientName,                                                                                             \
                TOMMROC_HW_NET_CORE_MQTT_CLIENT_SSL_DEFAULT_NETWORK_BUFFER_SIZE,                                                \
                notifyDataCb,                                                                                                   \
                sslCtxPtr,                                                                                                      \
                caChainDataPtr,                                                                                                 \
                caChainDataSize,                                                                                                \
                clientCertDataPtr,                                                                                              \
                clientCertDataSize,                                                                                             \
                clientPrivKeyDataPtr,                                                                                           \
                clientPrivKeyDataSize,                                                                                          \
                sslAuthMode,                                                                                                    \
                guardPtr)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef struct {

    char*   clientIDStrPtr; // Client ID string pointer.
    char*   usernameStrPtr; // Username string pointer (NULL if not used).
    char*   passwordStrPtr; // Password string pointer (NULL if not used).

} tommRoC_hw_net_core_mqtt_client_info_t;

#define __EMPTY_tommRoC_hw_net_core_mqtt_client_info_t__    \
{                                                           \
    /* .clientIDStrPtr */   NULL,                           \
    /* .usernameStrPtr */   NULL,                           \
    /* .passwordStrPtr */   NULL,                           \
}


// Core MQTT client.
typedef struct {
    uint8_t data[TOMMROC_HW_NET_CORE_MQTT_CLIENT_HANDLE_SIZE];
} tommRoC_hw_net_core_mqtt_client_t;

#define __EMPTY_tommRoC_hw_net_core_mqtt_client_t_t_data_field__            TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_HW_NET_CORE_MQTT_CLIENT_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_hw_net_core_mqtt_client_t_t__                       \
{                                                                           \
    /* .data */ __EMPTY_tommRoC_hw_net_core_mqtt_client_t_t_data_field__,   \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init a core MQTT client over plain socket endpoint for communication.
 *
 * param[in]        networkBufferPtr        network buffer pointer.
 *                                          This buffer will be used to receive incoming messages from the broker
 * param[in]        networkBufferSize       network buffer size [byte].
 * param[in]        notifyDataCb            on notify data callback function pointer.
 * param[in]        guardPtr                core MQTT client guard (NULL if none).
 * param[out]       coreMQTTClientPtr       output core MQTT client endpoint pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreMQTTClientPlainInit(
                void*                                                       const   networkBufferPtr,
        const   uint32_t                                                            networkBufferSize,
        const   tommRoC_hw_net_core_mqtt_client_def_notify_data_cb_funct_t          notifyDataCb,
        const   tommRoC_guard_t*                                            const   guardPtr,
                tommRoC_hw_net_core_mqtt_client_t*                          const   coreMQTTClientPtr);

/**
 * Init a core MQTT client over SSL socket endpoint for communication.
 *
 * param[in]        networkBufferPtr        network buffer pointer.
 *                                          This buffer will be used to receive incoming messages from the broker
 * param[in]        networkBufferSize       network buffer size [byte].
 * param[in]        notifyDataCb            on notify data callback function pointer.
 * param[in/out]    sslCtxPtr               SSL opaque context pointer.
 * param[in]        caChainDataPtr          CA chain certificate (PEM or DER format) data buffer pointer (NULL if none).
 * param[in]        caChainDataSize         CA chain certificate (including the terminating character) size [byte] (0 if none).
 * param[in]        clientCertDataPtr       client certificate (PEM or DER format) data buffer pointer (NULL if none).
 * param[in]        clientCertDataSize      client certificate (including the terminating character) size [byte] (0 if none).
 * param[in]        clientPrivKeyDataPtr    client private key (PEM or DER format) data buffer pointer (NULL if none).
 * param[in]        clientPrivKeyDataSize   client private key (including the terminating character) size [byte] (0 if none).
 * param[in]        sslAuthMode             certificate verify mode.
 * param[in]        guardPtr                core MQTT client guard (NULL if none).
 * param[out]       coreMQTTClientPtr       output core MQTT client endpoint pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreMQTTClientSSLInit(
                void*                                                       const   networkBufferPtr,
        const   uint32_t                                                            networkBufferSize,
        const   tommRoC_hw_net_core_mqtt_client_def_notify_data_cb_funct_t          notifyDataCb,
                void*                                                       const   sslCtxPtr,
        const   void*                                                       const   caChainDataPtr,
        const   uint32_t                                                            caChainDataSize,
        const   void*                                                       const   clientCertDataPtr,
        const   uint32_t                                                            clientCertDataSize,
        const   void*                                                       const   clientPrivKeyDataPtr,
        const   uint32_t                                                            clientPrivKeyDataSize,
        const   tommRoC_crypto_ssl_auth_mode_enum_t                                 sslAuthMode,
        const   tommRoC_guard_t*                                            const   guardPtr,
                tommRoC_hw_net_core_mqtt_client_t*                          const   coreMQTTClientPtr);

/**
 * Connect a core MQTT client endpoint to the IPv4 address MQTT broker.
 *
 * param[in/out]    coreMQTTClientPtr       output core MQTT client endpoint pointer.
 * param[in]        ipV4AddPtr              IPv4 address MQTT broker to connect pointer.
 * param[in]        port                    MQTT broker TCP port.
 * param[in]        clientInfoPtr           MQTT client info pointer.
 * param[in]        cleanSession            MQTT clean session flag.
 * param[in]        keepAliveSec            MQTT keep alive period.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreMQTTClientConnect(
                tommRoC_hw_net_core_mqtt_client_t*                          const   coreMQTTClientPtr,
        const   tommRoC_hw_comm_ip_v4_add_t*                                const   ipV4AddPtr,
        const   uint16_t                                                            port,
        const   tommRoC_hw_net_core_mqtt_client_info_t*                     const   clientInfoPtr,
        const   tommRoC_hw_net_core_mqtt_client_def_clean_session_enum_t            cleanSession,
        const   uint16_t                                                            keepAliveSec);

/**
 * Connect a core MQTT client endpoint to the string host address MQTT broker.
 *
 * param[in/out]    coreMQTTClientPtr       output core MQTT client endpoint pointer.
 * param[in]        hostStrPtr              host address MQTT broker as string to connect pointer.
 * param[in]        port                    MQTT broker TCP port.
 * param[in]        clientInfoPtr           MQTT client info pointer.
 * param[in]        cleanSession            MQTT clean session flag.
 * param[in]        keepAliveSec            MQTT keep alive period.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreMQTTClientConnectHost(
                tommRoC_hw_net_core_mqtt_client_t*                          const   coreMQTTClientPtr,
        const   char*                                                       const   hostStrPtr,
        const   uint16_t                                                            port,
        const   tommRoC_hw_net_core_mqtt_client_info_t*                     const   clientInfoPtr,
        const   tommRoC_hw_net_core_mqtt_client_def_clean_session_enum_t            cleanSession,
        const   uint16_t                                                            keepAliveSec);

/**
 * Disconnect a core MQTT client endpoint.
 *
 * param[in/out]    coreMQTTClientPtr       output core MQTT client endpoint pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreMQTTClientDisconnect(
                tommRoC_hw_net_core_mqtt_client_t*                          const   coreMQTTClientPtr);

/**
 * Check if a core MQTT client endpoint is connected to a MQTT broker.
 *
 * param[in/out]    coreMQTTClientPtr       output core MQTT client endpoint pointer.
 * param[out]       isConnectedPtr          is connected boolean pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreMQTTClientIsConnected(
                tommRoC_hw_net_core_mqtt_client_t*                          const   coreMQTTClientPtr,
                bool*                                                       const   isConnectedPtr);

/**
 * Publish data to a core MQTT topic.
 *
 * param[in/out]    coreMQTTClientPtr       output core MQTT client endpoint pointer.
 * param[in]        topicStrPtr             MQTT topic string pointer.
 * param[in]        payloadBufferPtr        payload buffer pointer.
 * param[in]        payloadBufferLen        payload buffer length [byte].
 * param[in]        QoS                     Quality of Service.
 * param[in]        retain                  retain flag.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreMQTTClientPublish(
                tommRoC_hw_net_core_mqtt_client_t*                          const   coreMQTTClientPtr,
        const   char*                                                       const   topicStrPtr,
        const   void*                                                       const   payloadBufferPtr,
        const   uint32_t                                                            payloadBufferLen,
        const   tommRoC_hw_net_core_mqtt_client_def_qos_enum_t                      QoS,
        const   tommRoC_hw_net_core_mqtt_client_def_retain_enum_t                   retain);

/**
 * Subscribe a core MQTT client to a MQTT topic.
 *
 * param[in/out]    coreMQTTClientPtr       output core MQTT client endpoint pointer.
 * param[in]        topicStrPtr             MQTT topic string pointer.
 * param[in]        QoS                     Quality of Service.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreMQTTClientSubscribe(
                tommRoC_hw_net_core_mqtt_client_t*                          const   coreMQTTClientPtr,
        const   char*                                                       const   topicStrPtr,
        const   tommRoC_hw_net_core_mqtt_client_def_qos_enum_t                      QoS);

/**
 * Unsubscribe a core MQTT client from a MQTT topic.
 *
 * param[in/out]    coreMQTTClientPtr       output core MQTT client endpoint pointer.
 * param[in]        topicStrPtr             MQTT topic string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreMQTTClientUnsubscribe(
                tommRoC_hw_net_core_mqtt_client_t*                          const   coreMQTTClientPtr,
        const   char*                                                       const   topicStrPtr);

/**
 * Loop to receive packets from the transport interface. Handles keep alive.
 * NOTE: this MUST be called periodically.
 *
 * param[in/out]    coreMQTTClientPtr       output core MQTT client endpoint pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreMQTTClientProcessLoop(
                tommRoC_hw_net_core_mqtt_client_t*                          const   coreMQTTClientPtr);

#endif
