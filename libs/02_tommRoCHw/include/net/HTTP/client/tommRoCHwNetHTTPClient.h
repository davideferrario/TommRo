
#ifndef TOMMROC_HW_NET_HTTP_CLIENT_H_
#define TOMMROC_HW_NET_HTTP_CLIENT_H_

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
#include "net/HTTP/tommRoCHwNetHTTPDEF.h"

#include "comm/tommRoCHwComm.h"

#include "tommRoCHwErr.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

#if defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_8_BIT_SIZE)
#define TOMMROC_HW_NET_MQTT_CLIENT_HANDLE_SIZE  ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMROC_HW_NET_MQTT_CLIENT_HANDLE_SIZE  ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE)
#define TOMMROC_HW_NET_HTTP_CLIENT_HANDLE_SIZE  (12)
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMROC_HW_NET_HTTP_CLIENT_HANDLE_SIZE  (16)
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// HTTP client.
typedef struct {
    uint8_t data[TOMMROC_HW_NET_HTTP_CLIENT_HANDLE_SIZE];
} tommRoC_hw_net_http_client_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init a HTTP client for communication.
 *
 * param[in]        guardPtr                HTTP client guard (NULL if none).
 * param[out]       httpClientPtr           output HTTP client pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetHTTPClientInit(
        const   tommRoC_guard_t*                        const   guardPtr,
                tommRoC_hw_net_http_client_t*           const   httpClientPtr);

/**
 * Connect a HTTP client to the IPv4 address server.
 *
 * param[in/out]    httpClientPtr           HTTP client pointer.
 * param[in]        ipV4AddPtr              IPv4 address HTTP server to connect pointer.
 * param[in]        port                    HTTP server TCP port.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetHTTPClientConnect(
                tommRoC_hw_net_http_client_t*           const   httpClientPtr,
        const   tommRoC_hw_comm_ip_v4_add_t*            const   ipV4AddPtr,
        const   uint16_t                                        tcpPort);

/**
 * Connect a HTTP client to the string host address server.
 *
 * param[in/out]    httpClientPtr           HTTP client pointer.
 * param[in]        hostStrPtr              host address HTTP server as string to connect pointer.
 * param[in]        port                    HTTP server TCP port.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetHTTPClientConnectHost(
                tommRoC_hw_net_http_client_t*           const   httpClientPtr,
        const   char*                                   const   hostStrPtr,
        const   uint16_t                                        tcpPort);

/**
 * Disconnect a HTTP client.
 *
 * param[in/out]    httpClientPtr           HTTP client pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetHTTPClientClose(
                tommRoC_hw_net_http_client_t*           const   httpClientPtr);

/**
 * Check if a HTTP client is connected to a HTTP server.
 *
 * param[in/out]    httpClientPtr           HTTP client pointer.
 * param[out]       isConnectedPtr          is connected boolean pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetHTTPClientIsConnected(
                tommRoC_hw_net_http_client_t*           const   httpClientPtr,
                bool*                                   const   isConnectedPtr);

/**
 * Perform HTTP GET request.
 *
 * param[in/out]    httpClientPtr           HTTP client pointer.
 * param[in]        httpTargetStrPtr        HTTP request target string pointer.
 * param[in]        httpVersion             HTTP request version.
 * param[in]        httpHostNameStrPtr      HTTP request host name string pointer (NULL if note).
 * param[in]        httpHeaderStrPtr        HTTP request header string pointer (NULL if note).
 * param[in]        httpBodyStrPtr          HTTP request body string pointer (NULL if note).
 * param[out]       responseBufferPtr       HTTP response data buffer pointer.
 * param[in]        responseBufferSize      HTTP response data buffer to read size [byte].
 * param[out]       responseLenPtr          HTTP response amount of data readed size pointer [byte].
 * param[in]        writeTimeoutMsec        timeout of low level (socket) write operation [msec].
 * param[in]        waitResponseTimeoutMsec timeout of wait response operation [msec].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetHTTPClientGet(
                tommRoC_hw_net_http_client_t*           const   httpClientPtr,
        const   char*                                   const   httpTargetStrPtr,
        const   tommRoC_hw_net_http_def_version_enum_t          httpVersion,
        const   char*                                   const   httpHostNameStrPtr,
        const   char*                                   const   httpHeaderStrPtr,
        const   char*                                   const   httpBodyStrPtr,
                void*                                   const   responseBufferPtr,
        const   uint32_t                                        responseBufferSize,
                uint32_t*                               const   responseLenPtr,
        const   uint32_t                                        writeTimeoutMsec,
        const   uint32_t                                        waitResponseTimeoutMsec);

/**
 * Perform HTTP POST request.
 *
 * param[in/out]    httpClientPtr           HTTP client pointer.
 * param[in]        httpTargetStrPtr        HTTP request target string pointer.
 * param[in]        httpVersion             HTTP request version.
 * param[in]        httpHostNameStrPtr      HTTP request host name string pointer (NULL if note).
 * param[in]        httpHeaderStrPtr        HTTP request header string pointer (NULL if note).
 * param[in]        httpBodyStrPtr          HTTP request body string pointer (NULL if note).
 * param[out]       responseBufferPtr       HTTP response data buffer pointer.
 * param[in]        responseBufferSize      HTTP response data buffer to read size [byte].
 * param[out]       responseLenPtr          HTTP response amount of data readed size pointer [byte].
 * param[in]        writeTimeoutMsec        timeout of low level (socket) write operation [msec].
 * param[in]        waitResponseTimeoutMsec timeout of wait response operation [msec].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetHTTPClientPost(
                tommRoC_hw_net_http_client_t*           const   httpClientPtr,
        const   char*                                   const   httpTargetStrPtr,
        const   tommRoC_hw_net_http_def_version_enum_t          httpVersion,
        const   char*                                   const   httpHostNameStrPtr,
        const   char*                                   const   httpHeaderStrPtr,
        const   char*                                   const   httpBodyStrPtr,
                void*                                   const   responseBufferPtr,
        const   uint32_t                                        responseBufferSize,
                uint32_t*                               const   responseLenPtr,
        const   uint32_t                                        writeTimeoutMsec,
        const   uint32_t                                        waitResponseTimeoutMsec);

#endif
