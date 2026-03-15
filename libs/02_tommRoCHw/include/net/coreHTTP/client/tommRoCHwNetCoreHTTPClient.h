
#ifndef TOMMROC_HW_NET_CORE_HTTP_CLIENT_H_
#define TOMMROC_HW_NET_CORE_HTTP_CLIENT_H_

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
#include "net/coreHTTP/tommRoCHwNetCoreHTTPDEF.h"

#include "comm/tommRoCHwComm.h"

#include "tommRoCHwErr.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Flag that represents End of File byte in the range specification of a Range Request.
#define TOMMROC_HW_NET_CORE_HTTP_CLIENT_RANGE_REQUEST_END_OF_FILE   (-1)

#if defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_8_BIT_SIZE)
#define TOMMROC_HW_NET_CORE_HTTP_CLIENT_HANDLE_SIZE ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMROC_HW_NET_CORE_HTTP_CLIENT_HANDLE_SIZE ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE)
#define TOMMROC_HW_NET_CORE_HTTP_CLIENT_HANDLE_SIZE (196)
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMROC_HW_NET_CORE_HTTP_CLIENT_HANDLE_SIZE (360)
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Core HTTP client.
typedef struct {
    uint8_t data[TOMMROC_HW_NET_CORE_HTTP_CLIENT_HANDLE_SIZE];
} tommRoC_hw_net_core_http_client_t;

#define __EMPTY_tommRoC_hw_net_core_http_client_t_t_data_field__            TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_HW_NET_CORE_HTTP_CLIENT_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_hw_net_core_http_client_t_t__                       \
{                                                                           \
    /* .data */ __EMPTY_tommRoC_hw_net_core_http_client_t_t_data_field__,   \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init a core HTTP client for communication.
 *
 * param[in]        HTTPReqHeaderBufferPtr  memory buffer used for low level [coreHTTP] request header pointer.
 * param[in]        HTTPReqHeaderBufferSize memory buffer used for low level [coreHTTP] request header size [byte].
 * param[in]        HTTPResponseBufferPtr   memory buffer used for low level [coreHTTP] response pointer.
 * param[in]        HTTPResponseBufferSize  memory buffer used for low level [coreHTTP] response size [byte].
 * param[in]        guardPtr                core HTTP client guard (NULL if none).
 * param[out]       coreHTTPClientPtr       output core HTTP client pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreHTTPClientInit(
                void*                                   const   HTTPReqHeaderBufferPtr,
        const   uint32_t                                        HTTPReqHeaderBufferSize,
                void*                                   const   HTTPResponseBufferPtr,
        const   uint32_t                                        HTTPResponseBufferSize,
        const   tommRoC_guard_t*                        const   guardPtr,
                tommRoC_hw_net_core_http_client_t*      const   coreHTTPClientPtr);

/**
 * Init a core HTTP client over SSL socket endpoint for communication.
 *
 * param[in]        HTTPReqHeaderBufferPtr  memory buffer used for low level [coreHTTP] request header pointer.
 * param[in]        HTTPReqHeaderBufferSize memory buffer used for low level [coreHTTP] request header size [byte].
 * param[in]        HTTPResponseBufferPtr   memory buffer used for low level [coreHTTP] response pointer.
 * param[in]        HTTPResponseBufferSize  memory buffer used for low level [coreHTTP] response size [byte].
 * param[in/out]    sslCtxPtr               SSL opaque context pointer.
 * param[in]        caChainDataPtr          CA chain certificate (PEM or DER format) data buffer pointer (NULL if none).
 * param[in]        caChainDataSize         CA chain certificate (including the terminating character) size [byte] (0 if none).
 * param[in]        clientCertDataPtr       client certificate (PEM or DER format) data buffer pointer (NULL if none).
 * param[in]        clientCertDataSize      client certificate (including the terminating character) size [byte] (0 if none).
 * param[in]        clientPrivKeyDataPtr    client private key (PEM or DER format) data buffer pointer (NULL if none).
 * param[in]        clientPrivKeyDataSize   client private key (including the terminating character) size [byte] (0 if none).
 * param[in]        sslAuthMode             certificate verify mode.
 * param[in]        guardPtr                core HTTP client guard (NULL if none).
 * param[out]       coreHTTPClientPtr       output core HTTP client pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreHTTPClientSSLInit(
                void*                                   const   HTTPReqHeaderBufferPtr,
        const   uint32_t                                        HTTPReqHeaderBufferSize,
                void*                                   const   HTTPResponseBufferPtr,
        const   uint32_t                                        HTTPResponseBufferSize,
                void*                                   const   sslCtxPtr,
        const   void*                                   const   caChainDataPtr,
        const   uint32_t                                        caChainDataSize,
        const   void*                                   const   clientCertDataPtr,
        const   uint32_t                                        clientCertDataSize,
        const   void*                                   const   clientPrivKeyDataPtr,
        const   uint32_t                                        clientPrivKeyDataSize,
        const   tommRoC_crypto_ssl_auth_mode_enum_t             sslAuthMode,
        const   tommRoC_guard_t*                        const   guardPtr,
                tommRoC_hw_net_core_http_client_t*      const   coreHTTPClientPtr);

/**
 * Connect a core HTTP client to the IPv4 address server.
 *
 * param[in/out]    coreHTTPClientPtr       core HTTP client pointer.
 * param[in]        ipV4AddPtr              IPv4 address HTTP server to connect pointer.
 * param[in]        port                    HTTP server TCP port.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreHTTPClientConnect(
                tommRoC_hw_net_core_http_client_t*      const   coreHTTPClientPtr,
        const   tommRoC_hw_comm_ip_v4_add_t*            const   ipV4AddPtr,
        const   uint16_t                                        tcpPort);

/**
 * Connect a core HTTP client to the string host address server.
 *
 * param[in/out]    coreHTTPClientPtr       core HTTP client pointer.
 * param[in]        hostStrPtr              host/IP address as string pointer.
 * param[in]        port                    TCP port.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreHTTPClientConnectHost(
                tommRoC_hw_net_core_http_client_t*      const   coreHTTPClientPtr,
        const   char*                                   const   hostStrPtr,
        const   uint16_t                                        tcpPort);

/**
 * Close a core HTTP client connection.
 *
 * param[in/out]    coreHTTPClientPtr       core HTTP client pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreHTTPClientClose(
                tommRoC_hw_net_core_http_client_t*      const   coreHTTPClientPtr);

/**
 * Check if a core HTTP client is connected.
 *
 * param[in/out]    coreHTTPClientPtr       core HTTP client pointer.
 * param[out]       isConnectedPtr          HTTP client is connected pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreHTTPClientIsConnected(
                tommRoC_hw_net_core_http_client_t*      const   coreHTTPClientPtr,
                bool*                                   const   isConnectedPtr);

/**
 * Perform core HTTP GET request.
 *
 * param[in/out]    coreHTTPClientPtr       core HTTP client pointer.
 * param[in]        httpHostNameStrPtr      server host name string pointer.
 *                                          NOTE: does not have a "https://" or "http://" prepending.
 * param[in]        pathStrPtr              request-URI to the objects of interest string pointer.
 * param[in]        headerBufferPtr         headers buffer pointer (NULL if not used).
 * param[in]        headerBufferAmount      headers buffer element amount (0 if not used).
 * param[in]        rangeStartOrlastNbytes  starting byte for a range OR the last N number of bytes in the requested file.
 * param[in]        rangeEnd                ending range for the requested file.
 * param[in]        requestBodyBufferPtr    request body pointer (NULL if not used).
 * param[in]        requestBodyBufferLen    request body length [byte] (0 if not used).
 * param[out]       HTTPResponseStatusPtr   HTTP response status pointer.
 *
 * NOTE:
 * There are 3 different forms of range specification, determined by the
 * combination of rangeStartOrlastNbytes and rangeEnd parameter values:
 * 1. Request containing both parameters for the byte range [rangeStart, rangeEnd].
 *    Request for bytes 0 to 1023                   ->  rangeStartOrlastNbytes  = 0
 *                                                      rangeEnd                = 1023
 * 2. Request for the last N bytes, represented by @p rangeStartOrlastNbytes.
 *    Request for the last 512 bytes                ->  rangeStartOrlastNbytes  = -512
 *                                                      rangeEnd                = TOMMROC_HW_NET_CORE_HTTP_CLIENT_RANGE_REQUEST_END_OF_FILE
 * 3. Request for all bytes (till the end of byte sequence) from byte N.
 *    Request for all bytes from byte 256 onward.   ->  rangeStartOrlastNbytes  = 256
 *                                                      rangeEnd                = TOMMROC_HW_NET_CORE_HTTP_CLIENT_RANGE_REQUEST_END_OF_FILE
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreHTTPClientGet(
                tommRoC_hw_net_core_http_client_t*      const   coreHTTPClientPtr,
        const   char*                                   const   httpHostNameStrPtr,
        const   char*                                   const   pathStrPtr,
        const   tommRoC_hw_net_core_http_def_header_t*  const   headerBufferPtr,
        const   uint8_t                                         headerBufferAmount,
        const   int32_t                                         rangeStartOrlastNbytes,
        const   int32_t                                         rangeEnd,
        const   void*                                   const   requestBodyBufferPtr,
        const   uint32_t                                        requestBodyBufferLen,
                uint16_t*                               const   HTTPResponseStatusPtr);

/**
 * Perform core HTTP POST request.
 *
 * param[in/out]    coreHTTPClientPtr       core HTTP client pointer.
 * param[in]        httpHostNameStrPtr      server host name string pointer.
 *                                          NOTE: does not have a "https://" or "http://" prepending.
 * param[in]        pathStrPtr              request-URI to the objects of interest string pointer.
 * param[in]        headerBufferPtr         headers buffer pointer (NULL if not used).
 * param[in]        headerBufferAmount      headers buffer element amount (0 if not used).
 * param[in]        rangeStartOrlastNbytes  starting byte for a range OR the last N number of bytes in the requested file.
 * param[in]        rangeEnd                ending range for the requested file.
 * param[in]        requestBodyBufferPtr    request body pointer (NULL if not used).
 * param[in]        requestBodyBufferLen    request body length [byte] (0 if not used).
 * param[out]       HTTPResponseStatusPtr   HTTP response status pointer.
 *
 * NOTE:
 * There are 3 different forms of range specification, determined by the
 * combination of rangeStartOrlastNbytes and rangeEnd parameter values:
 * 1. Request containing both parameters for the byte range [rangeStart, rangeEnd].
 *    Request for bytes 0 to 1023                   ->  rangeStartOrlastNbytes  = 0
 *                                                      rangeEnd                = 1023
 * 2. Request for the last N bytes, represented by @p rangeStartOrlastNbytes.
 *    Request for the last 512 bytes                ->  rangeStartOrlastNbytes  = -512
 *                                                      rangeEnd                = TOMMROC_HW_NET_CORE_HTTP_CLIENT_RANGE_REQUEST_END_OF_FILE
 * 3. Request for all bytes (till the end of byte sequence) from byte N.
 *    Request for all bytes from byte 256 onward.   ->  rangeStartOrlastNbytes  = 256
 *                                                      rangeEnd                = TOMMROC_HW_NET_CORE_HTTP_CLIENT_RANGE_REQUEST_END_OF_FILE
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreHTTPClientPost(
                tommRoC_hw_net_core_http_client_t*      const   coreHTTPClientPtr,
        const   char*                                   const   httpHostNameStrPtr,
        const   char*                                   const   pathStrPtr,
        const   tommRoC_hw_net_core_http_def_header_t*  const   headerBufferPtr,
        const   uint8_t                                         headerBufferAmount,
        const   int32_t                                         rangeStartOrlastNbytes,
        const   int32_t                                         rangeEnd,
        const   void*                                   const   requestBodyBufferPtr,
        const   uint32_t                                        requestBodyBufferLen,
                uint16_t*                               const   HTTPResponseStatusPtr);

/**
 * Get information from a response of core HTTP.
 *
 * param[in/out]    coreHTTPClientPtr       core HTTP client pointer.
 * param[out]       HTTPHeadersPtrPtr       response headers pointer.
 * param[out]       HTTPHeadersLenPtr       response headers size [byte] pointer.
 * param[out]       HTTPBodyPtrPtr          response body pointer.
 * param[out]       HTTPBodyLenPtr          response body size [byte] pointer.
 * param[out]       HTTPResponseStatusPtr   HTTP response status pointer.
 * param[out]       HTTPContentLengthPtr    "Content-Length" header value pointer.
 * param[out]       HTTPHeaderCountPtr      count of the headers sent by the server pointer
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreHTTPClientResponseGetInfo(
                tommRoC_hw_net_core_http_client_t*      const   coreHTTPClientPtr,
                void**                                  const   HTTPHeadersPtrPtr,
                uint32_t*                               const   HTTPHeadersLenPtr,
                void**                                  const   HTTPBodyPtrPtr,
                uint32_t*                               const   HTTPBodyLenPtr,
                uint16_t*                               const   HTTPResponseStatusPtr,
                uint32_t*                               const   HTTPContentLengthPtr,
                uint32_t*                               const   HTTPHeaderCountPtr);

/**
 * Read a header from a complete core HTTP response.
 *
 * param[in/out]    coreHTTPClientPtr       core HTTP client pointer.
 * param[in]        fieldNameStrPtr         header field name to read string pointer.
 * param[out]       valueStrPtr             location of response string header pointer.
 * param[out]       valueStrLenPtr          response string header length pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetCoreHTTPClientReadHeader(
                tommRoC_hw_net_core_http_client_t*      const   coreHTTPClientPtr,
        const   char*                                   const   fieldNameStrPtr,
                char**                                  const   valueStrPtr,
                uint32_t*                               const   valueStrLenPtr);

#endif
