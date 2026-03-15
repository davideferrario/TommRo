
#ifndef TOMMROC_HW_NET_SOCKET_DEF_H_
#define TOMMROC_HW_NET_SOCKET_DEF_H_

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

/*******************************************************************************
 * defines
 ******************************************************************************/

// Non Blocking I/O
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#define TOMMROC_HW_NET_SOCKET_DEF_O_NONBLOCK    (1)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#define TOMMROC_HW_NET_SOCKET_DEF_O_NONBLOCK    (0x4000)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)
#define TOMMROC_HW_NET_SOCKET_DEF_O_NONBLOCK    (04000)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#define TOMMROC_HW_NET_SOCKET_DEF_O_NONBLOCK    (04000)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC Hw Net Socket type.
typedef int tommRoC_hw_net_socket_def_t;

#define __EMPTY_tommRoC_hw_net_socket_def_t__   ((int) -1)


// Enumeration of tommRoC Hw Net Socket device type.
typedef enum {

    TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_HW_ETHERNET_WIFI = 0,     // Socket device type is hardware ethernet and/or WiFi (fast connection)
    TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_SPI_BUS_ETHERNET,         // Socket device type is SPI bus ethernet
    TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_SPI_BUS_WIFI,             // Socket device type is SPI bus WiFi
    TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_ETHERNET,      // Socket device type is ethernet over AT command (UART bus)
    TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_WIFI,          // Socket device type is WiFi over AT command (UART bus)
    TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_GSM_MODEM,     // Socket device type is GSM modem over AT command (UART bus)
    TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_LTE_MODEM_OVER_LWIP,      // Socket device type is LTE modem over LWIP (UART bus)

} tommRoC_hw_net_socket_def_device_type_enum_t;

// Enumeration of tommRoC Hw Net Socket domain.
typedef enum {

    TOMMROC_HW_NET_SOCKET_DEF_DOMAIN_PF_UNSPEC = 0, // Any supported Internet protocols.

    TOMMROC_HW_NET_SOCKET_DEF_DOMAIN_PF_INET,       // IPv4 Internet protocols.
    TOMMROC_HW_NET_SOCKET_DEF_DOMAIN_PF_INET6,      // IPv6 Internet protocols.

    TOMMROC_HW_NET_SOCKET_DEF_DOMAIN_AF_INET,       // IPv4 Internet address.
    TOMMROC_HW_NET_SOCKET_DEF_DOMAIN_AF_INET6,      // IPv6 Internet address.

} tommRoC_hw_net_socket_def_domain_enum_t;


// Enumeration of tommRoC Hw Net Socket type.
typedef enum {

    TOMMROC_HW_NET_SOCKET_DEF_TYPE_SOCK_STREAM = 0, // Sequenced, reliable, two-way, connection-based byte streams (TCP).
                                                    // TCP is a connection-based protocol.
                                                    // The connection is established and the two endpoints have a conversation until the connection
                                                    // is terminated by one of the parties or by a network error.
    TOMMROC_HW_NET_SOCKET_DEF_TYPE_SOCK_DGRAM,      // Datagrams (connectionless, unreliable messages of a fixed maximum length - UDP).
                                                    // UDP is a datagram-based protocol.
                                                    // You send one datagram and get one reply and then the connection terminates.
    TOMMROC_HW_NET_SOCKET_DEF_TYPE_SOCK_RAW,        // Raw network protocol access.

} tommRoC_hw_net_socket_def_type_enum_t;


// Enumeration of tommRoC Hw Net Socket protocol.
typedef enum {

    TOMMROC_HW_NET_SOCKET_DEF_PROTOCOL_IP = 0,      // Internet Protocol.
    TOMMROC_HW_NET_SOCKET_DEF_PROTOCOL_ICMP,        // Internet Control Message Protocol.
    TOMMROC_HW_NET_SOCKET_DEF_PROTOCOL_TCP,         // Transmission Control Protocol.
    TOMMROC_HW_NET_SOCKET_DEF_PROTOCOL_UDP,         // User Datagram Protocol.
    TOMMROC_HW_NET_SOCKET_DEF_PROTOCOL_UDPLITE,     // UDP-Lite protocol.
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX) || defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
    TOMMROC_HW_NET_SOCKET_DEF_PROTOCOL_SCTP,        // Stream Control Transmission Protocol.
#endif
    TOMMROC_HW_NET_SOCKET_DEF_PROTOCOL_RAW,         // Raw IP packets.

} tommRoC_hw_net_socket_def_protocol_enum_t;


// Enumeration of tommRoC Hw Net how for shutdown function.
typedef enum {

    TOMMROC_HW_NET_SOCKET_DEF_SHUTDOWN_HOW_SHUT_RD = 0, // No more receptions.
    TOMMROC_HW_NET_SOCKET_DEF_SHUTDOWN_HOW_SHUT_WR,     // No more transmissions.
    TOMMROC_HW_NET_SOCKET_DEF_SHUTDOWN_HOW_SHUT_RDWR,   // No more receptions or transmissions.

} tommRoC_hw_net_socket_def_shutdown_how_enum_t;


// Enumeration of tommRoC Hw Net level for sock opt function.
typedef enum {

    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_LEVEL_SOL_SOCKET = 0,        // Options for socket level
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_LEVEL_IPPROTO_IP,            // Options for IP protocol level
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_LEVEL_IPPROTO_TCP,           // Options for TCP protocol level

} tommRoC_hw_net_socket_def_sock_opt_level_enum_t;

// Enumeration of tommRoC Hw Net opt name for sock opt function.
typedef enum {

    // Options for socket level (TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_LEVEL_SOL_SOCKET)

    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_DEBUG = 0,       // Unimplemented: turn on debugging info recording
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_ACCEPTCONN,      // socket has had listen()
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_DONTROUTE,       // Unimplemented: just use interface addresses
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_USELOOPBACK,     // Unimplemented: bypass hardware when possible
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_LINGER,          // linger on close if data present
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_DONTLINGER,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_OOBINLINE,       // Unimplemented: leave received OOB data in line
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_REUSEPORT,       // Unimplemented: allow local address & port reuse
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_SNDBUF,          // Unimplemented: send buffer size
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_RCVBUF,          // receive buffer size
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_SNDLOWAT,        // Unimplemented: send low-water mark
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_RCVLOWAT,        // Unimplemented: receive low-water mark
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_SNDTIMEO,        // send timeout
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_RCVTIMEO,        // receive timeout
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_ERROR,           // get error status and clear
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_TYPE,            // get socket type
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_CONTIMEO,        // Unimplemented: connect timeout
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_NO_CHECK,        // don't create UDP checksum
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_BINDTODEVICE,    // bind to device
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_REUSEADDR,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_BROADCAST,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_SNDBUFFORCE,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_RCVBUFFORCE,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_KEEPALIVE,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_PRIORITY,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_BSDCOMPAT,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_PASSCRED,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_PEERCRED,


    // Options for IP protocol level (TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_LEVEL_IPPROTO_IP)

    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_TOS,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_TTL,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_HDRINCL,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_OPTIONS,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_PKTINFO,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_RECVOPTS,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_RECVRETOPTS,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_RETOPTS,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_MULTICAST_IF,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_MULTICAST_TTL,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_MULTICAST_LOOP,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_ADD_MEMBERSHIP,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_DROP_MEMBERSHIP,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_UNBLOCK_SOURCE,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_BLOCK_SOURCE,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_ADD_SOURCE_MEMBERSHIP,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_DROP_SOURCE_MEMBERSHIP,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_MSFILTER,

    // Options for TCP protocol level (TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_LEVEL_IPPROTO_TCP)

    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_NODELAY,                // Don't delay send to coalesce packets
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_MAXSEG,                 // Set maximum segment size
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_CORK,                   // Control sending of partial frames
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_KEEPALIVE,              // send KEEPALIVE probes when idle for pcb->keep_idle milliseconds
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_KEEPIDLE,               // Start keeplives after this period
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_KEEPINTVL,              // Interval between keepalives
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_KEEPCNT,                // Number of keepalives before death
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_SYNCNT,                 // Number of SYN retransmits
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_LINGER2,                // Life time of orphaned FIN-WAIT-2 state
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_DEFER_ACCEPT,           // Wake up listener only when data arrive
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_WINDOW_CLAMP,           // Bound advertised window
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_INFO,                   // Information about this connection.
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_QUICKACK,               // Bock/reenable quick ACKs.
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_CONGESTION,             // Congestion control algorithm.
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_MD5SIG,                 // TCP MD5 Signature (RFC2385)
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_COOKIE_TRANSACTIONS,    // TCP Cookie Transactions
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_THIN_LINEAR_TIMEOUTS,   // Use linear timeouts for thin streams
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_THIN_DUPACK,            // Fast retrans. after 1 dupack
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_USER_TIMEOUT,           // How long for loss retry before timeout
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_REPAIR,                 // TCP sock is under repair right now
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_REPAIR_QUEUE,           // Set TCP queue to repair
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_QUEUE_SEQ,              // Set sequence number of repaired queue.
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_REPAIR_OPTIONS,         // Repair TCP connection options
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_FASTOPEN,               // Enable FastOpen on listeners
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_TIMESTAMP,              // TCP time stamp
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_NOTSENT_LOWAT,          // Limit number of unsent bytes in write queue.
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_CC_INFO,                // Get Congestion Control (optional) info.
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_SAVE_SYN,               // Record SYN headers for new connections.
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_SAVED_SYN,              // Get SYN headers recorded for connection.
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_REPAIR_WINDOW,          // Get/set window parameters.
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_FASTOPEN_CONNECT,       // Attempt FastOpen with connect.
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_ULP,                    // Attach a ULP to a TCP connection.
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_MD5SIG_EXT,             // TCP MD5 Signature with extensions.
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_FASTOPEN_KEY,           // Set the key for Fast Open (cookie).
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_FASTOPEN_NO_COOKIE,     // Enable TFO without a TFO cookie.
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_ZEROCOPY_RECEIVE,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_INQ,                    // Notify bytes available to read as a cmsg on read.
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_CM_INQ,
    TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_TX_DELAY,               // Delay outgoing packets by XX usec.

} tommRoC_hw_net_socket_def_sock_opt_opt_name_enum_t;

// Enumeration of tommRoC Hw Net commands for fnctl function.
typedef enum {

    TOMMROC_HW_NET_SOCKET_DEF_FCNTL_CMD_F_DUPFD = 0,    // Duplicate file descriptor.
    TOMMROC_HW_NET_SOCKET_DEF_FCNTL_CMD_F_GETFD,        // Get file descriptor flags.
    TOMMROC_HW_NET_SOCKET_DEF_FCNTL_CMD_F_SETFD,        // Set file descriptor flags.
    TOMMROC_HW_NET_SOCKET_DEF_FCNTL_CMD_F_GETFL,        // Get file status flags.
    TOMMROC_HW_NET_SOCKET_DEF_FCNTL_CMD_F_SETFL,        // Set file status flags.

} tommRoC_hw_net_socket_def_fcntl_cmd_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
