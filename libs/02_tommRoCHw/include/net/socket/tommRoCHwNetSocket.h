
#ifndef TOMMROC_HW_NET_SOCKET_H_
#define TOMMROC_HW_NET_SOCKET_H_

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
#include "net/socket/tommRoCHwNetSocketDEF.h"

#include "comm/tommRoCHwComm.h"

#include "tommRoCHwErr.h"

#include "TOMMROC.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * tommRoC Hw Net Socket callback functions type definition.
 */

// Create a socket endpoint for communication callback type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_socket_new_funct_t)(
        const   tommRoC_hw_net_socket_def_domain_enum_t                     domain,
        const   tommRoC_hw_net_socket_def_type_enum_t                       type,
        const   tommRoC_hw_net_socket_def_protocol_enum_t                   protocol,
                tommRoC_hw_net_socket_def_t*                        const   socketPtr);

// Connect socket endpoint to the IPv4 address specified by parameters callback type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_socket_connect_funct_t)(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   tommRoC_hw_comm_ip_v4_add_t*                        const   ipV4AddPtr,
        const   uint16_t                                                    tcpPort);

// Connect socket endpoint to the host specified by parameters callback type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_socket_connect_host_funct_t)(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   char*                                               const   hostStrPtr,
        const   uint16_t                                                    tcpPort);

// Assign network port specified to the listening socket referred callback type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_socket_bind_funct_t)(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   uint16_t                                                    port);

// Mark the socket referred as a passive socket callback type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_socket_listen_funct_t)(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   uint32_t                                                    backlog);

// Extract the first connection request on the queue of pending connections for the listening socket, creates a new connected socket, and returns a new socket descriptor callback type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_socket_accept_funct_t)(
        const   tommRoC_hw_net_socket_def_t*                        const   inSocketPtr,
                tommRoC_hw_net_socket_def_t*                        const   outSocketPtr,
                tommRoC_hw_comm_ip_v4_add_t*                        const   clientIpV4AddPtr);

// Write data buffer to a connectionless socket callback type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_socket_send_to_funct_t)(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   uint8_t                                                     flags,
        const   tommRoC_hw_comm_ip_v4_add_t*                        const   remoteIPv4AddPtr,
        const   uint16_t                                                    port,
        const   void*                                               const   writeBufferPtr,
        const   uint32_t                                                    writeBufferLen,
                int32_t*                                            const   writtenLenPtr,
        const   uint32_t                                                    writeTimeoutMsec);

// Read data buffer from a connectionless socket callback type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_socket_recv_from_funct_t)(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   uint8_t                                                     flags,
                tommRoC_hw_comm_ip_v4_add_t*                        const   remoteIPv4AddPtr,
                uint16_t*                                           const   remotePortPtr,
                void*                                               const   readBufferPtr,
        const   uint32_t                                                    readBufferLen,
                int32_t*                                            const   readedLenPtr,
        const   uint32_t                                                    readTimeoutMsec);

// Write data buffer to socket callback type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_socket_send_funct_t)(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   void*                                               const   writeBufferPtr,
        const   uint32_t                                                    writeBufferLen,
                int32_t*                                            const   writtenLenPtr,
        const   uint32_t                                                    writeTimeoutMsec);

// Read data buffer from socket callback type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_socket_recv_funct_t)(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
                void*                                               const   readBufferPtr,
        const   uint32_t                                                    readBufferLen,
                int32_t*                                            const   readedLenPtr,
        const   uint32_t                                                    readTimeoutMsec);

// Shut down all or part of the socket callback type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_socket_shutdown_funct_t)(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   tommRoC_hw_net_socket_def_shutdown_how_enum_t               how);

// Close socket callback type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_socket_close_funct_t)(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr);

// Get socket option callback type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_socket_get_sock_opt_funct_t)(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   tommRoC_hw_net_socket_def_sock_opt_level_enum_t             level,
        const   tommRoC_hw_net_socket_def_sock_opt_opt_name_enum_t          optName,
                void*                                               const   optValPtr,
        const   uint32_t                                                    optSizeByte,
                uint32_t*                                           const   optLenPtr,
                int*                                                const   lowLevelResPtr);

// Set socket option callback type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_socket_set_sock_opt_funct_t)(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   tommRoC_hw_net_socket_def_sock_opt_level_enum_t             level,
        const   tommRoC_hw_net_socket_def_sock_opt_opt_name_enum_t          optName,
        const   void*                                               const   optValPtr,
        const   uint32_t                                                    optSizeByte,
                int*                                                const   lowLevelResPtr);

// Do the socket control operation callback type.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_net_socket_fcntl_funct_t)(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   tommRoC_hw_net_socket_def_fcntl_cmd_enum_t                  cmd,
        const   int                                                         val,
                int*                                                const   lowLevelResPtr);


// Enumeration of tommRoC Hw Net Socket functions.
typedef enum {

    TOMMROC_HW_NET_SOCKET_NEW = 0,
    TOMMROC_HW_NET_SOCKET_CONNECT,
    TOMMROC_HW_NET_SOCKET_CONNECT_HOST,
    TOMMROC_HW_NET_SOCKET_BIND,
    TOMMROC_HW_NET_SOCKET_LISTEN,
    TOMMROC_HW_NET_SOCKET_ACCEPT,
    TOMMROC_HW_NET_SOCKET_SEND_TO,
    TOMMROC_HW_NET_SOCKET_RECV_FROM,
    TOMMROC_HW_NET_SOCKET_SEND,
    TOMMROC_HW_NET_SOCKET_RECV,
    TOMMROC_HW_NET_SOCKET_SHUTDOWN,
    TOMMROC_HW_NET_SOCKET_CLOSE,
    TOMMROC_HW_NET_SOCKET_GET_SOCK_OPT,
    TOMMROC_HW_NET_SOCKET_SET_SOCK_OPT,
    TOMMROC_HW_NET_SOCKET_FCNTL,

} tommRoC_hw_net_socket_operations_enum_t;


// Enumeration of tommRoC Hw Net Socket init resources.
typedef enum {

    /**
     * Net socket as client interface.
     */
    TOMMROC_HW_NET_SOCKET_CLIENT = 0,

    /**
     * Net socket as server interface.
     */
    TOMMROC_HW_NET_SOCKET_SERVER,

} tommRoC_hw_net_socket_environment_resource_enum_t;


// tommRoC Hw Net Socket init complete structure.
typedef struct {

    tommRoC_hw_net_socket_def_device_type_enum_t    deviceType;
    uint8_t                                         maxActiveConn;  // Max. active connections supported by Net Socket interface.

    tommRoC_hw_net_socket_new_funct_t               newFunct;
    tommRoC_hw_net_socket_connect_funct_t           connectFunct;
    tommRoC_hw_net_socket_connect_host_funct_t      connectHostFunct;
    tommRoC_hw_net_socket_bind_funct_t              bindFunct;
    tommRoC_hw_net_socket_listen_funct_t            listenFunct;
    tommRoC_hw_net_socket_accept_funct_t            acceptFunct;
    tommRoC_hw_net_socket_send_to_funct_t           sendToFunct;
    tommRoC_hw_net_socket_recv_from_funct_t         recvFromFunct;
    tommRoC_hw_net_socket_send_funct_t              sendFunct;
    tommRoC_hw_net_socket_recv_funct_t              recvFunct;
    tommRoC_hw_net_socket_shutdown_funct_t          shutdownFunct;
    tommRoC_hw_net_socket_close_funct_t             closeFunct;
    tommRoC_hw_net_socket_get_sock_opt_funct_t      getSockOptFunct;    // NOTE: NULL if none.
    tommRoC_hw_net_socket_set_sock_opt_funct_t      setSockOptFunct;    // NOTE: NULL if none.
    tommRoC_hw_net_socket_fcntl_funct_t             fcntlFunct;         // NOTE: NULL if none.

} tommRoC_hw_net_socket_complete_init_t;

#define __EMPTY_tommRoC_hw_net_socket_complete_init_t__                             \
{                                                                                   \
    /* .deviceType */       TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_HW_ETHERNET_WIFI, \
    /* .maxActiveConn */    0,                                                      \
    /* .newFunct */         NULL,                                                   \
    /* .connectFunct */     NULL,                                                   \
    /* .connectHostFunct */ NULL,                                                   \
    /* .bindFunct */        NULL,                                                   \
    /* .listenFunct */      NULL,                                                   \
    /* .acceptFunct */      NULL,                                                   \
    /* .sendToFunct */      NULL,                                                   \
    /* .recvFromFunct */    NULL,                                                   \
    /* .sendFunct */        NULL,                                                   \
    /* .recvFunct */        NULL,                                                   \
    /* .shutdownFunct */    NULL,                                                   \
    /* .closeFunct */       NULL,                                                   \
    /* .getSockOptFunct */  NULL,                                                   \
    /* .setSockOptFunct */  NULL,                                                   \
    /* .fcntlFunct */       NULL,                                                   \
}

// tommRoC Hw Net Socket init only client structure.
typedef struct {

    tommRoC_hw_net_socket_def_device_type_enum_t    deviceType;
    uint8_t                                         maxActiveConn;  // Max. active connections supported by Net Socket interface.

    tommRoC_hw_net_socket_new_funct_t               newFunct;
    tommRoC_hw_net_socket_connect_funct_t           connectFunct;
    tommRoC_hw_net_socket_connect_host_funct_t      connectHostFunct;
    tommRoC_hw_net_socket_send_to_funct_t           sendToFunct;
    tommRoC_hw_net_socket_recv_from_funct_t         recvFromFunct;
    tommRoC_hw_net_socket_send_funct_t              sendFunct;
    tommRoC_hw_net_socket_recv_funct_t              recvFunct;
    tommRoC_hw_net_socket_shutdown_funct_t          shutdownFunct;
    tommRoC_hw_net_socket_close_funct_t             closeFunct;
    tommRoC_hw_net_socket_get_sock_opt_funct_t      getSockOptFunct;    // NOTE: NULL if none.
    tommRoC_hw_net_socket_set_sock_opt_funct_t      setSockOptFunct;    // NOTE: NULL if none.
    tommRoC_hw_net_socket_fcntl_funct_t             fcntlFunct;         // NOTE: NULL if none.

} tommRoC_hw_net_socket_only_client_init_t;

#define __EMPTY_tommRoC_hw_net_socket_only_client_init_t__                          \
{                                                                                   \
    /* .deviceType */       TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_HW_ETHERNET_WIFI, \
    /* .maxActiveConn */    0,                                                      \
    /* .newFunct */         NULL,                                                   \
    /* .connectFunct */     NULL,                                                   \
    /* .connectHostFunct */ NULL,                                                   \
    /* .sendToFunct */      NULL,                                                   \
    /* .recvFromFunct */    NULL,                                                   \
    /* .sendFunct */        NULL,                                                   \
    /* .recvFunct */        NULL,                                                   \
    /* .shutdownFunct */    NULL,                                                   \
    /* .closeFunct */       NULL,                                                   \
    /* .getSockOptFunct */  NULL,                                                   \
    /* .setSockOptFunct */  NULL,                                                   \
    /* .fcntlFunct */       NULL,                                                   \
}

// tommRoC Hw Net Socket init only server structure.
typedef struct {

    tommRoC_hw_net_socket_def_device_type_enum_t    deviceType;
    uint8_t                                         maxActiveConn;  // Max. active connections supported by Net Socket interface.

    tommRoC_hw_net_socket_new_funct_t               newFunct;
    tommRoC_hw_net_socket_bind_funct_t              bindFunct;
    tommRoC_hw_net_socket_listen_funct_t            listenFunct;
    tommRoC_hw_net_socket_accept_funct_t            acceptFunct;
    tommRoC_hw_net_socket_send_to_funct_t           sendToFunct;
    tommRoC_hw_net_socket_recv_from_funct_t         recvFromFunct;
    tommRoC_hw_net_socket_send_funct_t              sendFunct;
    tommRoC_hw_net_socket_recv_funct_t              recvFunct;
    tommRoC_hw_net_socket_shutdown_funct_t          shutdownFunct;
    tommRoC_hw_net_socket_close_funct_t             closeFunct;
    tommRoC_hw_net_socket_get_sock_opt_funct_t      getSockOptFunct;    // NOTE: NULL if none.
    tommRoC_hw_net_socket_set_sock_opt_funct_t      setSockOptFunct;    // NOTE: NULL if none.
    tommRoC_hw_net_socket_fcntl_funct_t             fcntlFunct;         // NOTE: NULL if none.

} tommRoC_hw_net_socket_only_server_init_t;

#define __EMPTY_tommRoC_hw_net_socket_only_server_init_t__                          \
{                                                                                   \
    /* .deviceType */       TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_HW_ETHERNET_WIFI, \
    /* .maxActiveConn */    0,                                                      \
    /* .newFunct */         NULL,                                                   \
    /* .bindFunct */        NULL,                                                   \
    /* .listenFunct */      NULL,                                                   \
    /* .acceptFunct */      NULL,                                                   \
    /* .sendToFunct */      NULL,                                                   \
    /* .recvFromFunct */    NULL,                                                   \
    /* .sendFunct */        NULL,                                                   \
    /* .recvFunct */        NULL,                                                   \
    /* .shutdownFunct */    NULL,                                                   \
    /* .closeFunct */       NULL,                                                   \
    /* .getSockOptFunct */  NULL,                                                   \
    /* .setSockOptFunct */  NULL,                                                   \
    /* .fcntlFunct */       NULL,                                                   \
}


/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Prepare library Hw Net Socket environment for complete/only client/only server.
 *
 * param[in]        initConfigPtr           pointer to init structure.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketInitEnvComplete(const tommRoC_hw_net_socket_complete_init_t* const initConfigPtr);
tommRoC_hw_err_enum_t tommRoCHwNetSocketInitEnvOnlyClient(const tommRoC_hw_net_socket_only_client_init_t* const initConfigPtr);
tommRoC_hw_err_enum_t tommRoCHwNetSocketInitEnvOnlyServer(const tommRoC_hw_net_socket_only_server_init_t* const initConfigPtr);

/**
 * Close library Hw Net Socket environment.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketCloseEnv(void);


/**
 * Check if a specific operation is available (has been initiated).
 *
 * param[in]        operation               operation.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation available
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketIsOpAvailable(
        const   tommRoC_hw_net_socket_operations_enum_t                     operation);


/**
 * Check if library Hw Net Socket environment is init.
 *
 * param[in]        resource                Net Socket init environment resource to check
 * param[out]       isInitPtr               Is init boolean status.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketIsInitEnv(
        const   tommRoC_hw_net_socket_environment_resource_enum_t           resource,
                bool*                                               const   isInitPtr);


/**
 * Get library Hw Net Socket environment device type.
 *
 * param[out]       deviceTypePtr           Device type pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketGetDeviceType(tommRoC_hw_net_socket_def_device_type_enum_t* const deviceTypePtr);

/**
 * Set library Hw Net Socket environment device type.
 *
 * param[in]        deviceType              Device type.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketSetDeviceType(const tommRoC_hw_net_socket_def_device_type_enum_t deviceType);

/**
 * Get library Hw Net Socket environment max. active connections.
 *
 * param[out]       maxActiveConnPtr        Max. active connections pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketGetMaxActiveConn(uint8_t* const maxActiveConnPtr);

/**
 * Set library Hw Net Socket environment max. active connections.
 *
 * param[in]        maxActiveConn           Max. active connections.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketSetMaxActiveConn(const uint8_t maxActiveConn);


/**
 * Create a socket endpoint for communication.
 *
 * param[in]        domain                  communication domain.
 * param[in]        type                    communication semantics.
 * param[in]        protocol                particular protocol to be used with the socket,
 * param[out]       socketPtr               output socket endpoint pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketNew(
        const   tommRoC_hw_net_socket_def_domain_enum_t                     domain,
        const   tommRoC_hw_net_socket_def_type_enum_t                       type,
        const   tommRoC_hw_net_socket_def_protocol_enum_t                   protocol,
                tommRoC_hw_net_socket_def_t*                        const   socketPtr);

/**
 * Connect socket endpoint to the IPv4 address specified by parameters.
 *
 * param[in/out]    socketPtr               socket endpoint pointer.
 * param[in]        ipV4AddPtr              IPv4 address to connect pointer.
 * param[in]        tcpPort                 TCP port to connect.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketConnect(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   tommRoC_hw_comm_ip_v4_add_t*                        const   ipV4AddPtr,
        const   uint16_t                                                    tcpPort);

/**
 * Connect socket endpoint to the host specified by parameters.
 *
 * param[in/out]    socketPtr               socket endpoint pointer.
 * param[in]        hostStrPtr              host address as string to connect pointer.
 * param[in]        tcpPort                 TCP port to connect.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketConnectHost(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   char*                                               const   hostStrPtr,
        const   uint16_t                                                    tcpPort);

/**
 * Assign network port specified to the listening socket referred.
 *
 * param[in]        socketPtr               socket endpoint pointer.
 * param[in]        port                    network port.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketBind(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   uint16_t                                                    port);

/**
 * Mark the socket referred as a passive socket.
 *
 * param[in]        socketPtr               socket endpoint pointer.
 * param[in]        backlog                 maximum length to which the queue of pending connections may grow.
 *                                          If a connection request arrives when the queue is full, the requested is skipped.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketListen(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   uint32_t                                                    backlog);

/**
 * Extract the first connection request on the queue of pending connections for the listening socket, creates a new connected socket,
 * and returns a new socket descriptor.
 * NOTE: this is a blocking function.
 *
 * param[in]        inSocketPtr             input socket endpoint pointer.
 * param[out]       outSocketPtr            output socket endpoint pointer.
 * param[out]       clientIpV4AddPtr        client IPv4 address of the peer socket pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketAccept(
        const   tommRoC_hw_net_socket_def_t*                        const   inSocketPtr,
                tommRoC_hw_net_socket_def_t*                        const   outSocketPtr,
                tommRoC_hw_comm_ip_v4_add_t*                        const   clientIpV4AddPtr);

/**
 * Write data buffer to a connectionless socket.
 * NOTE: MUST be used with a connectionless - UDP - socket.
 *
 * param[in]        socketPtr               socket endpoint pointer.
 * param[in]        flags                   flags (always 0).
 * param[in]        remoteIPv4AddPtr        remote IPv4 address to send data pointer.
 * param[in]        port                    port to send data.
 * param[in]        writeBufferPtr          data buffer pointer.
 * param[in]        writeBufferLen          data buffer to write size [byte].
 * param[out]       writtenLenPtr           amount of data written size [byte]. Set to negative value if error occur.
 * param[in]        writeTimeoutMsec        timeout of write operation [msec].
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_ERR_SUCCESS -> write data completed with success. Check amount of data written size [byte] variable.
 *          TOMMRO_C_HW_TIMEOUT_ERR -> write data failed because of timeout. Amount of data written size [byte] variable MUST be 0.
 *          others                  -> write data failed because of other error. Amount of data written size [byte] MUST be negative.
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketSendTo(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   uint8_t                                                     flags,
        const   tommRoC_hw_comm_ip_v4_add_t*                        const   remoteIPv4AddPtr,
        const   uint16_t                                                    port,
        const   void*                                               const   writeBufferPtr,
        const   uint32_t                                                    writeBufferLen,
                int32_t*                                            const   writtenLenPtr,
        const   uint32_t                                                    writeTimeoutMsec);

/**
 * Read data buffer from a connectionless socket.
 * NOTE: MUST be used with a connectionless - UDP - socket.
 *
 * param[in]        socketPtr               socket endpoint pointer.
 * param[in]        flags                   flags (always 0).
 * param[in]        remoteIPv4AddPtr        remote IPv4 address of the peer socket pointer.
 * param[in]        remotePortPtr           remote port of the peer socket pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        readBufferLen           data buffer to read size [byte].
 * param[out]       readedLenPtr            amount of data readed size pointer [byte]. Set to negative value if error occur.
 * param[in]        readTimeoutMsec         timeout of read operation [msec].
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_ERR_SUCCESS -> read data completed with success. Check amount of data written size [byte] variable.
 *          TOMMRO_C_HW_TIMEOUT_ERR -> read data failed because of timeout. Amount of data written size [byte] variable MUST be 0.
 *          others                  -> read data failed because of other error. Amount of data written size [byte] MUST be negative.
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketRecvFrom(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   uint8_t                                                     flags,
                tommRoC_hw_comm_ip_v4_add_t*                        const   remoteIPv4AddPtr,
                uint16_t*                                           const   remotePortPtr,
                void*                                               const   readBufferPtr,
        const   uint32_t                                                    readBufferLen,
                int32_t*                                            const   readedLenPtr,
        const   uint32_t                                                    readTimeoutMsec);

/**
 * Write data buffer to socket.
 *
 * param[in]        socketPtr               socket endpoint pointer.
 * param[in]        writeBufferPtr          data buffer pointer.
 * param[in]        writeBufferLen          data buffer to write size [byte].
 * param[out]       writtenLenPtr           amount of data written size [byte]. Set to negative value if error occur.
 * param[in]        writeTimeoutMsec        timeout of write operation [msec].
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_ERR_SUCCESS -> write data completed with success. Check amount of data written size [byte] variable.
 *          TOMMRO_C_HW_TIMEOUT_ERR -> write data failed because of timeout. Amount of data written size [byte] variable MUST be 0.
 *          others                  -> write data failed because of other error. Amount of data written size [byte] MUST be negative.
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketSend(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   void*                                               const   writeBufferPtr,
        const   uint32_t                                                    writeBufferLen,
                int32_t*                                            const   writtenLenPtr,
        const   uint32_t                                                    writeTimeoutMsec);

/**
 * Read data buffer from socket.
 *
 * param[in]        socketPtr               socket endpoint pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        readBufferLen           data buffer to read size [byte].
 * param[out]       readedLenPtr            amount of data readed size pointer [byte]. Set to negative value if error occur.
 * param[in]        readTimeoutMsec         timeout of read operation [msec].
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_ERR_SUCCESS -> read data completed with success. Check amount of data written size [byte] variable.
 *          TOMMRO_C_HW_TIMEOUT_ERR -> read data failed because of timeout. Amount of data written size [byte] variable MUST be 0.
 *          others                  -> read data failed because of other error. Amount of data written size [byte] MUST be negative.
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketRecv(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
                void*                                               const   readBufferPtr,
        const   uint32_t                                                    readBufferLen,
                int32_t*                                            const   readedLenPtr,
        const   uint32_t                                                    readTimeoutMsec);

/**
 * Shut down all or part of the socket.
 *
 * param[in]        socketPtr               socket endpoint pointer.
 * param[in]        how                     what to shut down selection.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketShutdown(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   tommRoC_hw_net_socket_def_shutdown_how_enum_t               how);

/**
 * Close socket.
 *
 * param[in]        socketPtr               socket endpoint pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketClose(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr);

/**
 * Get socket option.
 *
 * param[in]        socketPtr               socket endpoint pointer.
 * param[in]        level                   socket protocol level.
 * param[in]        optName                 socket option name.
 * param[out]       optValPtr               socket option value buffer pointer.
 * param[in]        optSizeByte             socket option value buffer max. size [byte].
 * param[out]       optLenPtr               socket option value buffer length pointer.
 * param[out]       lowLevelResPtr          operation low level result pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketGetSockOpt(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   tommRoC_hw_net_socket_def_sock_opt_level_enum_t             level,
        const   tommRoC_hw_net_socket_def_sock_opt_opt_name_enum_t          optName,
                void*                                               const   optValPtr,
        const   uint32_t                                                    optSizeByte,
                uint32_t*                                           const   optLenPtr,
                int*                                                const   lowLevelResPtr);

/**
 * Set socket option.
 *
 * param[in]        socketPtr               socket endpoint pointer.
 * param[in]        level                   socket protocol level.
 * param[in]        optName                 socket option name.
 * param[in]        optValPtr               socket option value pointer.
 * param[in]        optSizeByte             socket option value size [byte].
 * param[out]       lowLevelResPtr          operation low level result pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketSetSockOpt(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   tommRoC_hw_net_socket_def_sock_opt_level_enum_t             level,
        const   tommRoC_hw_net_socket_def_sock_opt_opt_name_enum_t          optName,
        const   void*                                               const   optValPtr,
        const   uint32_t                                                    optSizeByte,
                int*                                                const   lowLevelResPtr);

/**
 * Do the socket control operation.
 *
 * param[in]        socketPtr               socket endpoint pointer.
 * param[in]        cmd                     control operation command.
 * param[in]        val                     control operation value.
 * param[out]       lowLevelResPtr          operation low level result pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwNetSocketFcntl(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   tommRoC_hw_net_socket_def_fcntl_cmd_enum_t                  cmd,
        const   int                                                         val,
                int*                                                const   lowLevelResPtr);

#endif
