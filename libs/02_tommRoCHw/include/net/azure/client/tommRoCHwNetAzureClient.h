
#ifndef TOMMROC_HW_NET_AZURE_CLIENT_H_
#define TOMMROC_HW_NET_AZURE_CLIENT_H_

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
#include "net/azure/client/tommRoCHwNetAzureClientDEF.h"

#include "net/MQTT/client/tommRoCHwNetMQTTClient.h"

#include "tommRoCHwErr.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Default cache buffer size [byte] for an azure client object.
#define TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_CLIENT_ID_SIZE    (128)
#define TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_USER_NAME_SIZE    (160)
#define TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_PUB_TOPIC_SIZE    (128)
#define TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_SUB_TOPIC_SIZE    (128)
#define TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_PROPS_SIZE        (128)


#if defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_8_BIT_SIZE)
#define TOMMROC_HW_NET_AZURE_CLIENT_HANDLE_MORE_SIZE    ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMROC_HW_NET_AZURE_CLIENT_HANDLE_MORE_SIZE    ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE)
#define TOMMROC_HW_NET_AZURE_CLIENT_HANDLE_MORE_SIZE    (   (5 * (TOMMROC_UTIL_PTR_SIZE + TOMMROC_UTIL_U32_SIZE))                                                   +   \
                                                            (5 * (TOMMROC_UTIL_PTR_SIZE + TOMMROC_UTIL_U32_SIZE) + TOMMROC_UTIL_PTR_SIZE + TOMMROC_UTIL_I32_SIZE)   +   \
                                                            TOMMROC_UTIL_PTR_SIZE                                                                                       )
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMROC_HW_NET_AZURE_CLIENT_HANDLE_MORE_SIZE    (   (5 * (TOMMROC_UTIL_PTR_SIZE + TOMMROC_UTIL_U32_SIZE + TOMMROC_UTIL_U32_SIZE))                                                                           +   \
                                                            (5 * (TOMMROC_UTIL_PTR_SIZE + TOMMROC_UTIL_U32_SIZE + TOMMROC_UTIL_U32_SIZE) + TOMMROC_UTIL_PTR_SIZE + TOMMROC_UTIL_I32_SIZE + TOMMROC_UTIL_U32_SIZE)   +   \
                                                            TOMMROC_UTIL_PTR_SIZE                                                                                                                                       )
#endif


#define TOMMROC_HW_NET_AZURE_CLIENT_HANDLE_SIZE         (TOMMROC_HW_NET_MQTT_CLIENT_HANDLE_SIZE + TOMMROC_HW_NET_AZURE_CLIENT_HANDLE_MORE_SIZE)


/******************* Not static */

#define TOMMROC_HW_NET_AZURE_CLIENT_DECLARE(                                                                                            \
        azureClientName,                                                                                                                \
        cacheSendBufferSize,                                                                                                            \
        cacheReadBufferSize,                                                                                                            \
        cacheClientIDBufferSize,                                                                                                        \
        cacheUserNameBufferSize,                                                                                                        \
        cachePubTopicBufferSize,                                                                                                        \
        cacheSubTopicBufferSize,                                                                                                        \
        cachePropsBufferSize)                                                                                                           \
        char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, CacheSendBuffer, __)[cacheSendBufferSize];                 \
        char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, CacheReadBuffer, __)[cacheReadBufferSize];                 \
        char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cacheClientIDBuffer, __)[cacheClientIDBufferSize];         \
        char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cacheUserNameBuffer, __)[cacheUserNameBufferSize];         \
        char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cachePubTopicBuffer, __)[cachePubTopicBufferSize];         \
        char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cacheSubTopicBuffer, __)[cacheSubTopicBufferSize];         \
        char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cachePropsBuffer, __)[cachePropsBufferSize];               \
        tommRoC_hw_net_azure_client_t azureClientName

#define TOMMROC_HW_NET_AZURE_CLIENT_DECLARE_AND_INIT(                                                                                   \
        azureClientName,                                                                                                                \
        guardPtr,                                                                                                                       \
        cacheSendBufferSize,                                                                                                            \
        cacheReadBufferSize,                                                                                                            \
        cacheClientIDBufferSize,                                                                                                        \
        cacheUserNameBufferSize,                                                                                                        \
        cachePubTopicBufferSize,                                                                                                        \
        cacheSubTopicBufferSize,                                                                                                        \
        cachePropsBufferSize)                                                                                                           \
                                                                                                                                        \
        TOMMROC_HW_NET_AZURE_CLIENT_DECLARE(                                                                                            \
                azureClientName,                                                                                                        \
                cacheSendBufferSize,                                                                                                    \
                cacheReadBufferSize,                                                                                                    \
                cacheClientIDBufferSize,                                                                                                \
                cacheUserNameBufferSize,                                                                                                \
                cachePubTopicBufferSize,                                                                                                \
                cacheSubTopicBufferSize,                                                                                                \
                cachePropsBufferSize);                                                                                                  \
                                                                                                                                        \
                do {                                                                                                                    \
                    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                                           \
                            tommRoCHwNetAzureClientInit(                                                                                \
                                    guardPtr,                                                                                           \
                                    (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, CacheSendBuffer, __),       \
                                    cacheSendBufferSize,                                                                                \
                                    (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, CacheReadBuffer, __),       \
                                    cacheSendBufferSize,                                                                                \
                                    (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cacheClientIDBuffer, __),   \
                                    cacheClientIDBufferSize,                                                                            \
                                    (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cacheUserNameBuffer, __),   \
                                    cacheUserNameBufferSize,                                                                            \
                                    (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cachePubTopicBuffer, __),   \
                                    cachePubTopicBufferSize,                                                                            \
                                    (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cacheSubTopicBuffer, __),   \
                                    cacheSubTopicBufferSize,                                                                            \
                                    (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cachePropsBuffer, __),      \
                                    cachePropsBufferSize,                                                                               \
                                    &azureClientName));                                                                                 \
                } while (0)


/******************* Static */

#define TOMMROC_HW_NET_AZURE_CLIENT_STATIC_DECLARE(                                                                                     \
        azureClientName,                                                                                                                \
        cacheSendBufferSize,                                                                                                            \
        cacheReadBufferSize,                                                                                                            \
        cacheClientIDBufferSize,                                                                                                        \
        cacheUserNameBufferSize,                                                                                                        \
        cachePubTopicBufferSize,                                                                                                        \
        cacheSubTopicBufferSize,                                                                                                        \
        cachePropsBufferSize)                                                                                                           \
        static char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, CacheSendBuffer, __)[cacheSendBufferSize];          \
        static char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, CacheReadBuffer, __)[cacheReadBufferSize];          \
        static char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cacheClientIDBuffer, __)[cacheClientIDBufferSize];  \
        static char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cacheUserNameBuffer, __)[cacheUserNameBufferSize];  \
        static char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cachePubTopicBuffer, __)[cachePubTopicBufferSize];  \
        static char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cacheSubTopicBuffer, __)[cacheSubTopicBufferSize];  \
        static char TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cachePropsBuffer, __)[cachePropsBufferSize];        \
        static tommRoC_hw_net_azure_client_t azureClientName

#define TOMMROC_HW_NET_AZURE_CLIENT_STATIC_DECLARE_AND_INIT(                                                                            \
        azureClientName,                                                                                                                \
        guardPtr,                                                                                                                       \
        cacheSendBufferSize,                                                                                                            \
        cacheReadBufferSize,                                                                                                            \
        cacheClientIDBufferSize,                                                                                                        \
        cacheUserNameBufferSize,                                                                                                        \
        cachePubTopicBufferSize,                                                                                                        \
        cacheSubTopicBufferSize,                                                                                                        \
        cachePropsBufferSize)                                                                                                           \
                                                                                                                                        \
        TOMMROC_HW_NET_AZURE_CLIENT_STATIC_DECLARE(                                                                                     \
                azureClientName,                                                                                                        \
                cacheSendBufferSize,                                                                                                    \
                cacheReadBufferSize,                                                                                                    \
                cacheClientIDBufferSize,                                                                                                \
                cacheUserNameBufferSize,                                                                                                \
                cachePubTopicBufferSize,                                                                                                \
                cacheSubTopicBufferSize,                                                                                                \
                cachePropsBufferSize);                                                                                                  \
                                                                                                                                        \
                do {                                                                                                                    \
                    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(                                                                           \
                            tommRoCHwNetAzureClientInit(                                                                                \
                                    guardPtr,                                                                                           \
                                    (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, CacheSendBuffer, __),       \
                                    cacheSendBufferSize,                                                                                \
                                    (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, CacheReadBuffer, __),       \
                                    cacheSendBufferSize,                                                                                \
                                    (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cacheClientIDBuffer, __),   \
                                    cacheClientIDBufferSize,                                                                            \
                                    (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cacheUserNameBuffer, __),   \
                                    cacheUserNameBufferSize,                                                                            \
                                    (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cachePubTopicBuffer, __),   \
                                    cachePubTopicBufferSize,                                                                            \
                                    (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cacheSubTopicBuffer, __),   \
                                    cacheSubTopicBufferSize,                                                                            \
                                    (void*) TOMMROC_UTIL_CONCAT_FIVE_ELEM_NO_EXPAND(__, azureClientName, _, cachePropsBuffer, __),      \
                                    cachePropsBufferSize,                                                                               \
                                    &azureClientName));                                                                                 \
                } while (0)


/******************* Not static default size */

#define TOMMROC_HW_NET_AZURE_CLIENT_DECLARE_DEFAULT_CACHE_BUFFER_SIZE(azureClientName)                                                  \
        TOMMROC_HW_NET_AZURE_CLIENT_DECLARE(                                                                                            \
                azureClientName,                                                                                                        \
                TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_SEND_BUFFER_SIZE,                                                          \
                TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_READ_BUFFER_SIZE,                                                          \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_CLIENT_ID_SIZE,                                                               \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_USER_NAME_SIZE,                                                               \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_PUB_TOPIC_SIZE,                                                               \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_SUB_TOPIC_SIZE,                                                               \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_PROPS_SIZE)

#define TOMMROC_HW_NET_AZURE_CLIENT_DECLARE_AND_INIT_DEFAULT_CACHE_BUFFER_SIZE(azureClientName, guardPtr)                               \
        TOMMROC_HW_NET_AZURE_CLIENT_DECLARE_AND_INIT(                                                                                   \
                azureClientName,                                                                                                        \
                guardPtr,                                                                                                               \
                TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_SEND_BUFFER_SIZE,                                                          \
                TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_READ_BUFFER_SIZE,                                                          \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_CLIENT_ID_SIZE,                                                               \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_USER_NAME_SIZE,                                                               \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_PUB_TOPIC_SIZE,                                                               \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_SUB_TOPIC_SIZE,                                                               \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_PROPS_SIZE)


/******************* Static default size */

#define TOMMROC_HW_NET_AZURE_CLIENT_STATIC_DECLARE_DEFAULT_CACHE_BUFFER_SIZE(azureClientName)                                           \
        TOMMROC_HW_NET_AZURE_CLIENT_STATIC_DECLARE(                                                                                     \
                azureClientName,                                                                                                        \
                TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_SEND_BUFFER_SIZE,                                                          \
                TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_READ_BUFFER_SIZE,                                                          \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_CLIENT_ID_SIZE,                                                               \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_USER_NAME_SIZE,                                                               \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_PUB_TOPIC_SIZE,                                                               \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_SUB_TOPIC_SIZE,                                                               \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_PROPS_SIZE)

#define TOMMROC_HW_NET_AZURE_CLIENT_STATIC_DECLARE_AND_INIT_DEFAULT_CACHE_BUFFER_SIZE(azureClientName, guardPtr)                        \
        TOMMROC_HW_NET_AZURE_CLIENT_STATIC_DECLARE_AND_INIT(                                                                            \
                azureClientName,                                                                                                        \
                guardPtr,                                                                                                               \
                TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_SEND_BUFFER_SIZE,                                                          \
                TOMMROC_HW_NET_MQTT_CLIENT_SSL_DEFAULT_CACHE_READ_BUFFER_SIZE,                                                          \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_CLIENT_ID_SIZE,                                                               \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_USER_NAME_SIZE,                                                               \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_PUB_TOPIC_SIZE,                                                               \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_SUB_TOPIC_SIZE,                                                               \
                TOMMROC_HW_NET_AZURE_CLIENT_DEFAULT_CACHE_PROPS_SIZE)


/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Azure client.
typedef struct {
    uint8_t data[TOMMROC_HW_NET_AZURE_CLIENT_HANDLE_SIZE];
} tommRoC_hw_net_azure_client_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init an Azure client for communication.
 *
 * param[in/out]    sslCtxPtr               SSL opaque context pointer.
 * param[in]        guardPtr                Azure client guard (NULL if none).
 * param[in]        cacheSendBufferPtr      memory buffer used for low level [MQTT] send operation pointer.
 * param[in]        cacheSendBufferSize     memory buffer used for low level [MQTT] send operation size [byte].
 * param[in]        cacheReadBufferPtr      memory buffer used for low level [MQTT] read operation pointer.
 * param[in]        cacheReadBufferSize     memory buffer used for low level [MQTT] read operation size [byte].
 * param[in]        cacheClientIDBufferPtr  memory buffer used for low level [MQTT] client ID pointer.
 * param[in]        cacheClientIDBufferSize memory buffer used for low level [MQTT] client ID size [byte].
 * param[in]        cacheUserNameBufferPtr  memory buffer used for low level [MQTT] user name pointer.
 * param[in]        cacheUserNameBufferSize memory buffer used for low level [MQTT] user name size [byte].
 * param[in]        cachePubTopicBufferPtr  memory buffer used for low level [MQTT] publish topic pointer.
 * param[in]        cachePubTopicBufferSize memory buffer used for low level [MQTT] publish topic size [byte].
 * param[in]        cacheSubTopicBufferPtr  memory buffer used for low level [MQTT] subscribe topic pointer.
 * param[in]        cacheSubTopicBufferSize memory buffer used for low level [MQTT] subscribe topic size [byte].
 * param[in]        cachePropsBufferPtr     memory buffer used for Azure properties pointer (NULL if none).
 * param[in]        cachePropsBufferSize    memory buffer used for Azure properties size [byte].
 * param[out]       azureClientPtr          output Azure client endpoint pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetAzureClientInit(
                void*                                                       const   sslCtxPtr,
        const   tommRoC_guard_t*                                            const   guardPtr,
                void*                                                       const   cacheSendBufferPtr,
        const   uint32_t                                                            cacheSendBufferSize,
                void*                                                       const   cacheReadBufferPtr,
        const   uint32_t                                                            cacheReadBufferSize,
                void*                                                       const   cacheClientIDBufferPtr,
        const   uint32_t                                                            cacheClientIDBufferSize,
                void*                                                       const   cacheUserNameBufferPtr,
        const   uint32_t                                                            cacheUserNameBufferSize,
                void*                                                       const   cachePubTopicBufferPtr,
        const   uint32_t                                                            cachePubTopicBufferSize,
                void*                                                       const   cacheSubTopicBufferPtr,
        const   uint32_t                                                            cacheSubTopicBufferSize,
                void*                                                       const   cachePropsBufferPtr,
        const   uint32_t                                                            cachePropsBufferSize,
                tommRoC_hw_net_azure_client_t*                              const   azureClientPtr);

/**
 * Connect an Azure client to an IoT hub.
 *
 * param[in/out]    azureClientPtr          output Azure client endpoint pointer.
 * param[in]        iotHubHostnameStrPtr    IoT hub host name string pointer.
 * param[in]        port                    IoT hub TCP port.
 * param[in]        deviceIDStrPtr          Azure device ID string pointer.
 * param[in]        passwordStrPtr          Azure password string pointer.
 * param[in]        propsKeyValuePtr        key/value array for properties pointer (NULL if none).
 * param[in]        propsKeyValueEAmount    key/value array for properties element amount (0 if none).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetAzureClientConnectHost(
                tommRoC_hw_net_azure_client_t*                              const   azureClientPtr,
        const   char*                                                       const   iotHubHostnameStrPtr,
        const   uint16_t                                                            tcpPort,
        const   char*                                                       const   deviceIDStrPtr,
        const   char*                                                       const   passwordStrPtr,
        const   tommRoC_key_value_string_t*                                 const   propsKeyValuePtr,
        const   uint8_t                                                             propsKeyValueEAmount);

/**
 * Disconnect an Azure client from IoT hub.
 *
 * param[in/out]    azureClientPtr          output Azure client endpoint pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetAzureClientDisconnect(
                tommRoC_hw_net_azure_client_t*                              const   azureClientPtr);

/**
 * Check if an Azure client is connected to an IoT hub.
 *
 * param[in/out]    azureClientPtr          output Azure client endpoint pointer.
 * param[out]       isConnectedPtr          is connected boolean pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetAzureClientIsConnected(
                tommRoC_hw_net_azure_client_t*                              const   azureClientPtr,
                bool*                                                       const   isConnectedPtr);

/**
 * Publish data to an Azure IoT hub.
 *
 * param[in/out]    azureClientPtr          output Azure client endpoint pointer.
 * param[in]        payloadBufferPtr        payload buffer pointer.
 * param[in]        payloadBufferLen        payload buffer length [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetAzureClientPublish(
                tommRoC_hw_net_azure_client_t*                              const   azureClientPtr,
        const   void*                                                       const   payloadBufferPtr,
        const   uint32_t                                                            payloadBufferLen);

/**
 * Subscribe an Azure client to an Azure IoT hub.
 *
 * param[in/out]    azureClientPtr          output Azure client endpoint pointer.
 * param[in]        incomingDataCb          notification incoming data callback function.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetAzureClientSubscribe(
                tommRoC_hw_net_azure_client_t*                              const   azureClientPtr,
        const   tommRoC_hw_net_azure_client_def_incoming_data_cb_t                  incomingDataCb);

/**
 * Unsubscribe an Azure client to an Azure IoT hub.
 *
 * param[in/out]    azureClientPtr          output Azure client endpoint pointer.
 * param[in]        topicStrPtr             MQTT topic string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetAzureClientUnsubscribe(
                tommRoC_hw_net_azure_client_t*                              const   azureClientPtr);

/**
 * Yield Azure client - MQTT background.
 *
 * param[in/out]    azureClientPtr          Azure client endpoint pointer.
 * param[in]        timeoutSec              MQTT yield timeout [sec].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetAzureClientYield(
                tommRoC_hw_net_azure_client_t*                              const   azureClientPtr,
        const   uint32_t                                                            timeoutSec);

/**
 * Yield Azure client - MQTT background (timeout msec version).
 *
 * param[in/out]    azureClientPtr          Azure client endpoint pointer.
 * param[in]        timeoutMsec             MQTT yield timeout [msec].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetAzureClientYieldMsec(
                tommRoC_hw_net_azure_client_t*                              const   azureClientPtr,
        const   uint32_t                                                            timeoutMsec);

/**
 * Convert an opaque to known message data.
 *
 * param[in/out]    messageDataCbPtr        Azure opaque message data pointer.
 * param[in]        messagePtr              Azure known message data pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetAzureClientGetMessage(
        const   tommRoC_hw_net_azure_client_def_incoming_message_data_t*    const   messageDataCbPtr,
                tommRoC_hw_net_azure_client_def_message_t*                  const   messagePtr);

#endif
