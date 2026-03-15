
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateNetBSDSocket.h"

#if defined (__TOMMROC_HW_NET_BSD_SOCKET_TEMPLATE_IS_USED__)
#include "TOMMROC.h"
#include "TOMMROCHw.h"
#include "TOMMROCMw.h"

#include "net/BSDSocket/lowLevel/tommRoCHwTemplateNetBSDSocketLowLevel.h"

#include <sys/time.h>
#include <errno.h>

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#include "main.h"
#if !defined (HAL_ETH_MODULE_ENABLED)
#error "HAL_ETH_MODULE_ENABLED must be defined"
#endif

#if (!LWIP_SO_SNDTIMEO) || (!LWIP_SO_RCVTIMEO)
#error "LWIP_SO_SNDTIMEO and LWIP_SO_RCVTIMEO are needed"
#endif

#if !defined(LWIP_PROVIDE_ERRNO)
#error "LWIP_PROVIDE_ERRNO is needed"
#endif

#if (LWIP_POSIX_SOCKETS_IO_NAMES != 0)
#error "LWIP_POSIX_SOCKETS_IO_NAMES must be set to 0 (in lwipopts.h) for FreeRTOS otherwise names like 'read' and 'write' conflict"
#endif
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __RES_SUCCESS_VALUE__       (0)
#define __NOT_VALID_SOCKET_VALUE__  (TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_hw_net_socket_def_t))

#define __TO_INT_ERROR_VALUE__      (-1)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
TOMMROC_SCTA_SIZE_OF_EQUALS(tommRoC_hw_net_socket_def_t, int);
TOMMROC_SCTA_EQUALS(TOMMROC_HW_NET_SOCKET_DEF_O_NONBLOCK, O_NONBLOCK);

/*******************************************************************************
 * local vars
 ******************************************************************************/
static tommRoC_guard_t* _guard_ptr = NULL;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static int _domain_enum_to_INT(const tommRoC_hw_net_socket_def_domain_enum_t domain) {

#if defined (PF_UNSPEC)
    TOMMROC_CTA_NOT_EQUALS(PF_UNSPEC, __TO_INT_ERROR_VALUE__);
#endif

#if defined (PF_INET)
    TOMMROC_CTA_NOT_EQUALS(PF_INET, __TO_INT_ERROR_VALUE__);
#endif
#if defined (PF_INET6)
    TOMMROC_CTA_NOT_EQUALS(PF_INET6, __TO_INT_ERROR_VALUE__);
#endif

#if defined (AF_INET)
    TOMMROC_CTA_NOT_EQUALS(AF_INET, __TO_INT_ERROR_VALUE__);
#endif
#if defined (AF_INET6)
    TOMMROC_CTA_NOT_EQUALS(AF_INET6, __TO_INT_ERROR_VALUE__);
#endif

    switch (domain) {

#if defined (PF_UNSPEC)
    case TOMMROC_HW_NET_SOCKET_DEF_DOMAIN_PF_UNSPEC:    return PF_UNSPEC;
#endif

#if defined (PF_INET)
    case TOMMROC_HW_NET_SOCKET_DEF_DOMAIN_PF_INET:      return PF_INET;
#endif
#if defined (PF_INET6)
    case TOMMROC_HW_NET_SOCKET_DEF_DOMAIN_PF_INET6:     return PF_INET6;
#endif

#if defined (AF_INET)
    case TOMMROC_HW_NET_SOCKET_DEF_DOMAIN_AF_INET:      return AF_INET;
#endif
#if defined (AF_INET6)
    case TOMMROC_HW_NET_SOCKET_DEF_DOMAIN_AF_INET6:     return AF_INET6;
#endif

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;

    }

    return __TO_INT_ERROR_VALUE__;
}

static int _type_enum_to_INT(const tommRoC_hw_net_socket_def_type_enum_t type) {

#if defined (SOCK_STREAM)
    TOMMROC_CTA_NOT_EQUALS(SOCK_STREAM, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SOCK_DGRAM)
    TOMMROC_CTA_NOT_EQUALS(SOCK_DGRAM, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SOCK_RAW)
    TOMMROC_CTA_NOT_EQUALS(SOCK_RAW, __TO_INT_ERROR_VALUE__);
#endif

    switch (type) {

#if defined (SOCK_STREAM)
    case TOMMROC_HW_NET_SOCKET_DEF_TYPE_SOCK_STREAM:    return SOCK_STREAM;
#endif
#if defined (SOCK_DGRAM)
    case TOMMROC_HW_NET_SOCKET_DEF_TYPE_SOCK_DGRAM:     return SOCK_DGRAM;
#endif
#if defined (SOCK_RAW)
    case TOMMROC_HW_NET_SOCKET_DEF_TYPE_SOCK_RAW:       return SOCK_RAW;
#endif

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;

    }

    return __TO_INT_ERROR_VALUE__;
}

static int _protocol_enum_to_INT(const tommRoC_hw_net_socket_def_protocol_enum_t protocol) {

#if defined (IPPROTO_IP)
    TOMMROC_CTA_NOT_EQUALS(IPPROTO_IP, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IPPROTO_ICMP)
    TOMMROC_CTA_NOT_EQUALS(IPPROTO_ICMP, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IPPROTO_TCP)
    TOMMROC_CTA_NOT_EQUALS(IPPROTO_TCP, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IPPROTO_UDP)
    TOMMROC_CTA_NOT_EQUALS(IPPROTO_UDP, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IPPROTO_UDPLITE)
    TOMMROC_CTA_NOT_EQUALS(IPPROTO_UDPLITE, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IPPROTO_SCTP)
    TOMMROC_CTA_NOT_EQUALS(IPPROTO_SCTP, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IPPROTO_RAW)
    TOMMROC_CTA_NOT_EQUALS(IPPROTO_RAW, __TO_INT_ERROR_VALUE__);
#endif

    switch (protocol) {

#if defined (IPPROTO_IP)
    case TOMMROC_HW_NET_SOCKET_DEF_PROTOCOL_IP:         return IPPROTO_IP;
#endif
#if defined (IPPROTO_ICMP)
    case TOMMROC_HW_NET_SOCKET_DEF_PROTOCOL_ICMP:       return IPPROTO_ICMP;
#endif
#if defined (IPPROTO_TCP)
    case TOMMROC_HW_NET_SOCKET_DEF_PROTOCOL_TCP:        return IPPROTO_TCP;
#endif
#if defined (IPPROTO_UDP)
    case TOMMROC_HW_NET_SOCKET_DEF_PROTOCOL_UDP:        return IPPROTO_UDP;
#endif
#if defined (IPPROTO_UDPLITE)
    case TOMMROC_HW_NET_SOCKET_DEF_PROTOCOL_UDPLITE:    return IPPROTO_UDPLITE;
#endif
#if defined (IPPROTO_SCTP)
    case TOMMROC_HW_NET_SOCKET_DEF_PROTOCOL_SCTP:       return IPPROTO_SCTP;
#endif
#if defined (IPPROTO_RAW)
    case TOMMROC_HW_NET_SOCKET_DEF_PROTOCOL_RAW:        return IPPROTO_RAW;
#endif

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;

    }

    return __TO_INT_ERROR_VALUE__;
}

static int _shutdown_how_enum_to_INT(const tommRoC_hw_net_socket_def_shutdown_how_enum_t how) {

#if defined (SHUT_RD)
    TOMMROC_CTA_NOT_EQUALS(SHUT_RD, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SHUT_WR)
    TOMMROC_CTA_NOT_EQUALS(SHUT_WR, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SHUT_RDWR)
    TOMMROC_CTA_NOT_EQUALS(SHUT_RDWR, __TO_INT_ERROR_VALUE__);
#endif

    switch (how) {

#if defined (SHUT_RD)
    case TOMMROC_HW_NET_SOCKET_DEF_SHUTDOWN_HOW_SHUT_RD:    return SHUT_RD;
#endif
#if defined (SHUT_WR)
    case TOMMROC_HW_NET_SOCKET_DEF_SHUTDOWN_HOW_SHUT_WR:    return SHUT_WR;
#endif
#if defined (SHUT_RDWR)
    case TOMMROC_HW_NET_SOCKET_DEF_SHUTDOWN_HOW_SHUT_RDWR:  return SHUT_RDWR;
#endif

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;

    }

    return __TO_INT_ERROR_VALUE__;
}

static int _sock_opt_level_enum_to_INT(const tommRoC_hw_net_socket_def_sock_opt_level_enum_t level) {

#if defined (SOL_SOCKET)
    TOMMROC_CTA_NOT_EQUALS(SOL_SOCKET, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IPPROTO_IP)
    TOMMROC_CTA_NOT_EQUALS(IPPROTO_IP, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IPPROTO_TCP)
    TOMMROC_CTA_NOT_EQUALS(IPPROTO_TCP, __TO_INT_ERROR_VALUE__);
#endif

    switch (level) {

#if defined (SOL_SOCKET)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_LEVEL_SOL_SOCKET:   return SOL_SOCKET;
#endif
#if defined (IPPROTO_IP)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_LEVEL_IPPROTO_IP:   return IPPROTO_IP;
#endif
#if defined (IPPROTO_TCP)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_LEVEL_IPPROTO_TCP:  return IPPROTO_TCP;
#endif

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;

    }

    return __TO_INT_ERROR_VALUE__;
}

static int _sock_opt_opt_name_enum_to_INT(const tommRoC_hw_net_socket_def_sock_opt_opt_name_enum_t optName) {

    // Options for socket level (TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_LEVEL_SOL_SOCKET)

#if defined (SO_DEBUG)
    TOMMROC_CTA_NOT_EQUALS(SO_DEBUG, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_ACCEPTCONN)
    TOMMROC_CTA_NOT_EQUALS(SO_ACCEPTCONN, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_DONTROUTE)
    TOMMROC_CTA_NOT_EQUALS(SO_DONTROUTE, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_USELOOPBACK)
    TOMMROC_CTA_NOT_EQUALS(SO_USELOOPBACK, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_LINGER)
    TOMMROC_CTA_NOT_EQUALS(SO_LINGER, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_DONTLINGER)
    TOMMROC_CTA_NOT_EQUALS(SO_DONTLINGER, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_OOBINLINE)
    TOMMROC_CTA_NOT_EQUALS(SO_OOBINLINE, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_REUSEPORT)
    TOMMROC_CTA_NOT_EQUALS(SO_REUSEPORT, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_SNDBUF)
    TOMMROC_CTA_NOT_EQUALS(SO_SNDBUF, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_RCVBUF)
    TOMMROC_CTA_NOT_EQUALS(SO_RCVBUF, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_SNDLOWAT)
    TOMMROC_CTA_NOT_EQUALS(SO_SNDLOWAT, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_RCVLOWAT)
    TOMMROC_CTA_NOT_EQUALS(SO_RCVLOWAT, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_SNDTIMEO)
    TOMMROC_CTA_NOT_EQUALS(SO_SNDTIMEO, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_RCVTIMEO)
    TOMMROC_CTA_NOT_EQUALS(SO_RCVTIMEO, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_ERROR)
    TOMMROC_CTA_NOT_EQUALS(SO_ERROR, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_TYPE)
    TOMMROC_CTA_NOT_EQUALS(SO_TYPE, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_CONTIMEO)
    TOMMROC_CTA_NOT_EQUALS(SO_CONTIMEO, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_NO_CHECK)
    TOMMROC_CTA_NOT_EQUALS(SO_NO_CHECK, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_BINDTODEVICE)
    TOMMROC_CTA_NOT_EQUALS(SO_BINDTODEVICE, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_REUSEADDR)
    TOMMROC_CTA_NOT_EQUALS(SO_REUSEADDR, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_BROADCAST)
    TOMMROC_CTA_NOT_EQUALS(SO_BROADCAST, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_SNDBUFFORCE)
    TOMMROC_CTA_NOT_EQUALS(SO_SNDBUFFORCE, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_RCVBUFFORCE)
    TOMMROC_CTA_NOT_EQUALS(SO_RCVBUFFORCE, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_KEEPALIVE)
    TOMMROC_CTA_NOT_EQUALS(SO_KEEPALIVE, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_PRIORITY)
    TOMMROC_CTA_NOT_EQUALS(SO_PRIORITY, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_BSDCOMPAT)
    TOMMROC_CTA_NOT_EQUALS(SO_BSDCOMPAT, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_PASSCRED)
    TOMMROC_CTA_NOT_EQUALS(SO_PASSCRED, __TO_INT_ERROR_VALUE__);
#endif
#if defined (SO_PEERCRED)
    TOMMROC_CTA_NOT_EQUALS(SO_PEERCRED, __TO_INT_ERROR_VALUE__);
#endif

    // Options for IP protocol level (TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_LEVEL_IPPROTO_IP)

#if defined (IP_TOS)
    TOMMROC_CTA_NOT_EQUALS(IP_TOS, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_TTL)
    TOMMROC_CTA_NOT_EQUALS(IP_TTL, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_HDRINCL)
    TOMMROC_CTA_NOT_EQUALS(IP_HDRINCL, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_OPTIONS)
    TOMMROC_CTA_NOT_EQUALS(IP_OPTIONS, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_PKTINFO)
    TOMMROC_CTA_NOT_EQUALS(IP_PKTINFO, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_RECVOPTS)
    TOMMROC_CTA_NOT_EQUALS(IP_RECVOPTS, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_RECVRETOPTS)
    TOMMROC_CTA_NOT_EQUALS(IP_RECVRETOPTS, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_RETOPTS)
    TOMMROC_CTA_NOT_EQUALS(IP_RETOPTS, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_MULTICAST_IF)
    TOMMROC_CTA_NOT_EQUALS(IP_MULTICAST_IF, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_MULTICAST_TTL)
    TOMMROC_CTA_NOT_EQUALS(IP_MULTICAST_TTL, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_MULTICAST_LOOP)
    TOMMROC_CTA_NOT_EQUALS(IP_MULTICAST_LOOP, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_ADD_MEMBERSHIP)
    TOMMROC_CTA_NOT_EQUALS(IP_ADD_MEMBERSHIP, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_DROP_MEMBERSHIP)
    TOMMROC_CTA_NOT_EQUALS(IP_DROP_MEMBERSHIP, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_UNBLOCK_SOURCE)
    TOMMROC_CTA_NOT_EQUALS(IP_UNBLOCK_SOURCE, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_BLOCK_SOURCE)
    TOMMROC_CTA_NOT_EQUALS(IP_BLOCK_SOURCE, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_ADD_SOURCE_MEMBERSHIP)
    TOMMROC_CTA_NOT_EQUALS(IP_ADD_SOURCE_MEMBERSHIP, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_DROP_SOURCE_MEMBERSHIP)
    TOMMROC_CTA_NOT_EQUALS(IP_DROP_SOURCE_MEMBERSHIP, __TO_INT_ERROR_VALUE__);
#endif
#if defined (IP_MSFILTER)
    TOMMROC_CTA_NOT_EQUALS(IP_MSFILTER, __TO_INT_ERROR_VALUE__);
#endif

    // Options for TCP protocol level (TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_LEVEL_IPPROTO_TCP)

#if defined (TCP_NODELAY)
    TOMMROC_CTA_NOT_EQUALS(TCP_NODELAY, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_MAXSEG)
    TOMMROC_CTA_NOT_EQUALS(TCP_MAXSEG, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_CORK)
    TOMMROC_CTA_NOT_EQUALS(TCP_CORK, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_KEEPALIVE)
    TOMMROC_CTA_NOT_EQUALS(TCP_KEEPALIVE, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_KEEPIDLE)
    TOMMROC_CTA_NOT_EQUALS(TCP_KEEPIDLE, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_KEEPINTVL)
    TOMMROC_CTA_NOT_EQUALS(TCP_KEEPINTVL, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_KEEPCNT)
    TOMMROC_CTA_NOT_EQUALS(TCP_KEEPCNT, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_SYNCNT)
    TOMMROC_CTA_NOT_EQUALS(TCP_SYNCNT, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_LINGER2)
    TOMMROC_CTA_NOT_EQUALS(TCP_LINGER2, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_DEFER_ACCEPT)
    TOMMROC_CTA_NOT_EQUALS(TCP_DEFER_ACCEPT, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_WINDOW_CLAMP)
    TOMMROC_CTA_NOT_EQUALS(TCP_WINDOW_CLAMP, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_INFO)
    TOMMROC_CTA_NOT_EQUALS(TCP_INFO, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_QUICKACK)
    TOMMROC_CTA_NOT_EQUALS(TCP_QUICKACK, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_CONGESTION)
    TOMMROC_CTA_NOT_EQUALS(TCP_CONGESTION, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_MD5SIG)
    TOMMROC_CTA_NOT_EQUALS(TCP_MD5SIG, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_COOKIE_TRANSACTIONS)
    TOMMROC_CTA_NOT_EQUALS(TCP_COOKIE_TRANSACTIONS, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_THIN_LINEAR_TIMEOUTS)
    TOMMROC_CTA_NOT_EQUALS(TCP_THIN_LINEAR_TIMEOUTS, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_THIN_DUPACK)
    TOMMROC_CTA_NOT_EQUALS(TCP_THIN_DUPACK, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_USER_TIMEOUT)
    TOMMROC_CTA_NOT_EQUALS(TCP_USER_TIMEOUT, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_REPAIR)
    TOMMROC_CTA_NOT_EQUALS(TCP_REPAIR, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_REPAIR_QUEUE)
    TOMMROC_CTA_NOT_EQUALS(TCP_REPAIR_QUEUE, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_QUEUE_SEQ)
    TOMMROC_CTA_NOT_EQUALS(TCP_QUEUE_SEQ, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_REPAIR_OPTIONS)
    TOMMROC_CTA_NOT_EQUALS(TCP_REPAIR_OPTIONS, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_FASTOPEN)
    TOMMROC_CTA_NOT_EQUALS(TCP_FASTOPEN, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_TIMESTAMP)
    TOMMROC_CTA_NOT_EQUALS(TCP_TIMESTAMP, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_NOTSENT_LOWAT)
    TOMMROC_CTA_NOT_EQUALS(TCP_NOTSENT_LOWAT, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_CC_INFO)
    TOMMROC_CTA_NOT_EQUALS(TCP_CC_INFO, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_SAVE_SYN)
    TOMMROC_CTA_NOT_EQUALS(TCP_SAVE_SYN, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_SAVED_SYN)
    TOMMROC_CTA_NOT_EQUALS(TCP_SAVED_SYN, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_REPAIR_WINDOW)
    TOMMROC_CTA_NOT_EQUALS(TCP_REPAIR_WINDOW, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_FASTOPEN_CONNECT)
    TOMMROC_CTA_NOT_EQUALS(TCP_FASTOPEN_CONNECT, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_ULP)
    TOMMROC_CTA_NOT_EQUALS(TCP_ULP, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_MD5SIG_EXT)
    TOMMROC_CTA_NOT_EQUALS(TCP_MD5SIG_EXT, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_FASTOPEN_KEY)
    TOMMROC_CTA_NOT_EQUALS(TCP_FASTOPEN_KEY, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_FASTOPEN_NO_COOKIE)
    TOMMROC_CTA_NOT_EQUALS(TCP_FASTOPEN_NO_COOKIE, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_ZEROCOPY_RECEIVE)
    TOMMROC_CTA_NOT_EQUALS(TCP_ZEROCOPY_RECEIVE, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_INQ)
    TOMMROC_CTA_NOT_EQUALS(TCP_INQ, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_CM_INQ)
    TOMMROC_CTA_NOT_EQUALS(TCP_CM_INQ, __TO_INT_ERROR_VALUE__);
#endif
#if defined (TCP_TX_DELAY)
    TOMMROC_CTA_NOT_EQUALS(TCP_TX_DELAY, __TO_INT_ERROR_VALUE__);
#endif

    switch (optName) {

    // Options for socket level (TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_LEVEL_SOL_SOCKET)

#if defined (SO_DEBUG)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_DEBUG:          return SO_DEBUG;
#endif
#if defined (SO_ACCEPTCONN)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_ACCEPTCONN:     return SO_ACCEPTCONN;
#endif
#if defined (SO_DONTROUTE)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_DONTROUTE:      return SO_DONTROUTE;
#endif
#if defined (SO_USELOOPBACK)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_USELOOPBACK:    return SO_USELOOPBACK;
#endif
#if defined (SO_LINGER)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_LINGER:         return SO_LINGER;
#endif
#if defined (SO_DONTLINGER)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_DONTLINGER:     return SO_DONTLINGER;
#endif
#if defined (SO_OOBINLINE)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_OOBINLINE:      return SO_OOBINLINE;
#endif
#if defined (SO_REUSEPORT)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_REUSEPORT:      return SO_REUSEPORT;
#endif
#if defined (SO_SNDBUF)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_SNDBUF:         return SO_SNDBUF;
#endif
#if defined (SO_RCVBUF)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_RCVBUF:         return SO_RCVBUF;
#endif
#if defined (SO_SNDLOWAT)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_SNDLOWAT:       return SO_SNDLOWAT;
#endif
#if defined (SO_RCVLOWAT)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_RCVLOWAT:       return SO_RCVLOWAT;
#endif
#if defined (SO_SNDTIMEO)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_SNDTIMEO:       return SO_SNDTIMEO;
#endif
#if defined (SO_RCVTIMEO)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_RCVTIMEO:       return SO_RCVTIMEO;
#endif
#if defined (SO_ERROR)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_ERROR:          return SO_ERROR;
#endif
#if defined (SO_TYPE)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_TYPE:           return SO_TYPE;
#endif
#if defined (SO_CONTIMEO)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_CONTIMEO:       return SO_CONTIMEO;
#endif
#if defined (SO_NO_CHECK)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_NO_CHECK:       return SO_NO_CHECK;
#endif
#if defined (SO_BINDTODEVICE)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_BINDTODEVICE:   return SO_BINDTODEVICE;
#endif
#if defined (SO_REUSEADDR)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_REUSEADDR:      return SO_REUSEADDR;
#endif
#if defined (SO_BROADCAST)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_BROADCAST:      return SO_BROADCAST;
#endif
#if defined (SO_SNDBUFFORCE)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_SNDBUFFORCE:    return SO_SNDBUFFORCE;
#endif
#if defined (SO_RCVBUFFORCE)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_RCVBUFFORCE:    return SO_RCVBUFFORCE;
#endif
#if defined (SO_KEEPALIVE)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_KEEPALIVE:      return SO_KEEPALIVE;
#endif
#if defined (SO_PRIORITY)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_PRIORITY:       return SO_PRIORITY;
#endif
#if defined (SO_BSDCOMPAT)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_BSDCOMPAT:      return SO_BSDCOMPAT;
#endif
#if defined (SO_PASSCRED)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_PASSCRED:       return SO_PASSCRED;
#endif
#if defined (SO_PEERCRED)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_SO_PEERCRED:       return SO_PEERCRED;
#endif

    // Options for IP protocol level (TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_LEVEL_IPPROTO_IP)

#if defined (IP_TOS)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_TOS:                    return IP_TOS;
#endif
#if defined (IP_TTL)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_TTL:                    return IP_TTL;
#endif
#if defined (IP_HDRINCL)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_HDRINCL:                return IP_HDRINCL;
#endif
#if defined (IP_OPTIONS)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_OPTIONS:                return IP_OPTIONS;
#endif
#if defined (IP_PKTINFO)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_PKTINFO:                return IP_PKTINFO;
#endif
#if defined (IP_RECVOPTS)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_RECVOPTS:               return IP_RECVOPTS;
#endif
#if defined (IP_RECVRETOPTS)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_RECVRETOPTS:            return IP_RECVRETOPTS;
#endif
#if defined (IP_RETOPTS)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_RETOPTS:                return IP_RETOPTS;
#endif
#if defined (IP_MULTICAST_IF)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_MULTICAST_IF:           return IP_MULTICAST_IF;
#endif
#if defined (IP_MULTICAST_TTL)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_MULTICAST_TTL:          return IP_MULTICAST_TTL;
#endif
#if defined (IP_MULTICAST_LOOP)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_MULTICAST_LOOP:         return IP_MULTICAST_LOOP;
#endif
#if defined (IP_ADD_MEMBERSHIP)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_ADD_MEMBERSHIP:         return IP_ADD_MEMBERSHIP;
#endif
#if defined (IP_DROP_MEMBERSHIP)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_DROP_MEMBERSHIP:        return IP_DROP_MEMBERSHIP;
#endif
#if defined (IP_UNBLOCK_SOURCE)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_UNBLOCK_SOURCE:         return IP_UNBLOCK_SOURCE;
#endif
#if defined (IP_BLOCK_SOURCE)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_BLOCK_SOURCE:           return IP_BLOCK_SOURCE;
#endif
#if defined (IP_ADD_SOURCE_MEMBERSHIP)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_ADD_SOURCE_MEMBERSHIP:  return IP_ADD_SOURCE_MEMBERSHIP;
#endif
#if defined (IP_DROP_SOURCE_MEMBERSHIP)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_DROP_SOURCE_MEMBERSHIP: return IP_DROP_SOURCE_MEMBERSHIP;
#endif
#if defined (IP_MSFILTER)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_IP_MSFILTER:               return IP_MSFILTER;
#endif

    // Options for TCP protocol level (TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_LEVEL_IPPROTO_TCP)

#if defined (TCP_NODELAY)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_NODELAY:               return TCP_NODELAY;
#endif
#if defined (TCP_MAXSEG)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_MAXSEG:                return TCP_MAXSEG;
#endif
#if defined (TCP_CORK)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_CORK:                  return TCP_CORK;
#endif
#if defined (TCP_KEEPALIVE)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_KEEPALIVE:             return TCP_KEEPALIVE;
#endif
#if defined (TCP_KEEPIDLE)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_KEEPIDLE:              return TCP_KEEPIDLE;
#endif
#if defined (TCP_KEEPINTVL)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_KEEPINTVL:             return TCP_KEEPINTVL;
#endif
#if defined (TCP_KEEPCNT)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_KEEPCNT:               return TCP_KEEPCNT;
#endif
#if defined (TCP_SYNCNT)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_SYNCNT:                return TCP_SYNCNT;
#endif
#if defined (TCP_LINGER2)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_LINGER2:               return TCP_LINGER2;
#endif
#if defined (TCP_DEFER_ACCEPT)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_DEFER_ACCEPT:          return TCP_DEFER_ACCEPT;
#endif
#if defined (TCP_WINDOW_CLAMP)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_WINDOW_CLAMP:          return TCP_WINDOW_CLAMP;
#endif
#if defined (TCP_INFO)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_INFO:                  return TCP_INFO;
#endif
#if defined (TCP_QUICKACK)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_QUICKACK:              return TCP_QUICKACK;
#endif
#if defined (TCP_CONGESTION)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_CONGESTION:            return TCP_CONGESTION;
#endif
#if defined (TCP_MD5SIG)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_MD5SIG:                return TCP_MD5SIG;
#endif
#if defined (TCP_COOKIE_TRANSACTIONS)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_COOKIE_TRANSACTIONS:   return TCP_COOKIE_TRANSACTIONS;
#endif
#if defined (TCP_THIN_LINEAR_TIMEOUTS)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_THIN_LINEAR_TIMEOUTS:  return TCP_THIN_LINEAR_TIMEOUTS;
#endif
#if defined (TCP_THIN_DUPACK)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_THIN_DUPACK:           return TCP_THIN_DUPACK;
#endif
#if defined (TCP_USER_TIMEOUT)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_USER_TIMEOUT:          return TCP_USER_TIMEOUT;
#endif
#if defined (TCP_REPAIR)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_REPAIR:                return TCP_REPAIR;
#endif
#if defined (TCP_REPAIR_QUEUE)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_REPAIR_QUEUE:          return TCP_REPAIR_QUEUE;
#endif
#if defined (TCP_QUEUE_SEQ)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_QUEUE_SEQ:             return TCP_QUEUE_SEQ;
#endif
#if defined (TCP_REPAIR_OPTIONS)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_REPAIR_OPTIONS:        return TCP_REPAIR_OPTIONS;
#endif
#if defined (TCP_FASTOPEN)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_FASTOPEN:              return TCP_FASTOPEN;
#endif
#if defined (TCP_TIMESTAMP)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_TIMESTAMP:             return TCP_TIMESTAMP;
#endif
#if defined (TCP_NOTSENT_LOWAT)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_NOTSENT_LOWAT:         return TCP_NOTSENT_LOWAT;
#endif
#if defined (TCP_CC_INFO)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_CC_INFO:               return TCP_CC_INFO;
#endif
#if defined (TCP_SAVE_SYN)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_SAVE_SYN:              return TCP_SAVE_SYN;
#endif
#if defined (TCP_SAVED_SYN)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_SAVED_SYN:             return TCP_SAVED_SYN;
#endif
#if defined (TCP_REPAIR_WINDOW)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_REPAIR_WINDOW:         return TCP_REPAIR_WINDOW;
#endif
#if defined (TCP_FASTOPEN_CONNECT)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_FASTOPEN_CONNECT:      return TCP_FASTOPEN_CONNECT;
#endif
#if defined (TCP_ULP)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_ULP:                   return TCP_ULP;
#endif
#if defined (TCP_MD5SIG_EXT)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_MD5SIG_EXT:            return TCP_MD5SIG_EXT;
#endif
#if defined (TCP_FASTOPEN_KEY)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_FASTOPEN_KEY:          return TCP_FASTOPEN_KEY;
#endif
#if defined (TCP_FASTOPEN_NO_COOKIE)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_FASTOPEN_NO_COOKIE:    return TCP_FASTOPEN_NO_COOKIE;
#endif
#if defined (TCP_ZEROCOPY_RECEIVE)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_ZEROCOPY_RECEIVE:      return TCP_ZEROCOPY_RECEIVE;
#endif
#if defined (TCP_INQ)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_INQ:                   return TCP_INQ;
#endif
#if defined (TCP_CM_INQ)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_CM_INQ:                return TCP_CM_INQ;
#endif
#if defined (TCP_TX_DELAY)
    case TOMMROC_HW_NET_SOCKET_DEF_SOCK_OPT_OPT_NAME_TCP_TX_DELAY:              return TCP_TX_DELAY;
#endif

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;

    }

    return __TO_INT_ERROR_VALUE__;
}

static int _fcntl_cmd_enum_to_INT(const tommRoC_hw_net_socket_def_fcntl_cmd_enum_t cmd) {

#if defined (F_DUPFD)
    TOMMROC_CTA_NOT_EQUALS(F_DUPFD, __TO_INT_ERROR_VALUE__);
#endif
#if defined (F_GETFD)
    TOMMROC_CTA_NOT_EQUALS(F_GETFD, __TO_INT_ERROR_VALUE__);
#endif
#if defined (F_SETFD)
    TOMMROC_CTA_NOT_EQUALS(F_SETFD, __TO_INT_ERROR_VALUE__);
#endif
#if defined (F_GETFL)
    TOMMROC_CTA_NOT_EQUALS(F_GETFL, __TO_INT_ERROR_VALUE__);
#endif
#if defined (F_SETFL)
    TOMMROC_CTA_NOT_EQUALS(F_SETFL, __TO_INT_ERROR_VALUE__);
#endif

    switch (cmd) {

#if defined (F_DUPFD)
    case TOMMROC_HW_NET_SOCKET_DEF_FCNTL_CMD_F_DUPFD:   return F_DUPFD;
#endif
#if defined (F_GETFD)
    case TOMMROC_HW_NET_SOCKET_DEF_FCNTL_CMD_F_GETFD:   return F_GETFD;
#endif
#if defined (F_SETFD)
    case TOMMROC_HW_NET_SOCKET_DEF_FCNTL_CMD_F_SETFD:   return F_SETFD;
#endif
#if defined (F_GETFL)
    case TOMMROC_HW_NET_SOCKET_DEF_FCNTL_CMD_F_GETFL:   return F_GETFL;
#endif
#if defined (F_SETFL)
    case TOMMROC_HW_NET_SOCKET_DEF_FCNTL_CMD_F_SETFL:   return F_SETFL;
#endif

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;

    }

    return __TO_INT_ERROR_VALUE__;
}

static in_addr_t _ipV4_add_to_in_addr_t(const tommRoC_hw_comm_ip_v4_add_t* const ipV4AddPtr) {

    uint8_t ipV4AddAsArray[TOMMROC_HW_COMM_IP_IPv4_ITF_EAMOUNT];
    uint32_t iPv4AddAsU32;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwCommIPv4ItfToU8Array(ipV4AddPtr, ipV4AddAsArray));

    iPv4AddAsU32 = tommRoCMathMake32(ipV4AddAsArray[0], ipV4AddAsArray[1], ipV4AddAsArray[2], ipV4AddAsArray[3]);

    return (in_addr_t) tommRoCHwNetHToNL(((in_addr_t) iPv4AddAsU32));
}

static void _in_addr_t_to_ipV4_add(const in_addr_t sAddr, tommRoC_hw_comm_ip_v4_add_t* const ipV4AddPtr) {

    uint32_t iPv4AddAsU32;
    uint8_t iPv4AddA1;
    uint8_t iPv4AddA2;
    uint8_t iPv4AddA3;
    uint8_t iPv4AddA4;

    iPv4AddAsU32 = tommRoCHwNetNToHL(sAddr);
    iPv4AddA1 = tommRoCMathMake8(iPv4AddAsU32, 3);
    iPv4AddA2 = tommRoCMathMake8(iPv4AddAsU32, 2);
    iPv4AddA3 = tommRoCMathMake8(iPv4AddAsU32, 1);
    iPv4AddA4 = tommRoCMathMake8(iPv4AddAsU32, 0);

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwCommIPv4ItfInit(iPv4AddA1, iPv4AddA2, iPv4AddA3, iPv4AddA4, ipV4AddPtr));
}

static long int ___close__(tommRoC_hw_net_socket_def_t* const socketPtr) {

    long int res;

    if (__NOT_VALID_SOCKET_VALUE__ == *socketPtr) {
        return __RES_SUCCESS_VALUE__;
    }

    res = tommRoCHwTemplateNetBSDSocketLowLevelClose(*(int*)socketPtr);

    *socketPtr = __NOT_VALID_SOCKET_VALUE__;

    return res;
}

static tommRoC_hw_err_enum_t _not_guarded_new(
        const   tommRoC_hw_net_socket_def_domain_enum_t                     domain,
        const   tommRoC_hw_net_socket_def_type_enum_t                       type,
        const   tommRoC_hw_net_socket_def_protocol_enum_t                   protocol,
                tommRoC_hw_net_socket_def_t*                        const   socketPtr) {

    long int res;

    int domainINT;
    int typeINT;
    int protocolINT;

    domainINT   = _domain_enum_to_INT(domain);
    typeINT     = _type_enum_to_INT(type);
    protocolINT = _protocol_enum_to_INT(protocol);

    TOMMROC_HW_PARAM_CHECK_ON_TEST_RETURN_ERR(domainINT,    ==, __TO_INT_ERROR_VALUE__);
    TOMMROC_HW_PARAM_CHECK_ON_TEST_RETURN_ERR(typeINT,      ==, __TO_INT_ERROR_VALUE__);
    TOMMROC_HW_PARAM_CHECK_ON_TEST_RETURN_ERR(protocolINT,  ==, __TO_INT_ERROR_VALUE__);

    res = tommRoCHwTemplateNetBSDSocketLowLevelSocket(
            domainINT,
            typeINT,
            protocolINT);

    if (res < __RES_SUCCESS_VALUE__) {
        ___close__((void*) socketPtr);
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    *socketPtr = (tommRoC_hw_net_socket_def_t) res;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _new(
        const   tommRoC_hw_net_socket_def_domain_enum_t                     domain,
        const   tommRoC_hw_net_socket_def_type_enum_t                       type,
        const   tommRoC_hw_net_socket_def_protocol_enum_t                   protocol,
                tommRoC_hw_net_socket_def_t*                        const   socketPtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            _not_guarded_new(
                    domain,
                    type,
                    protocol,
                    socketPtr));
}

static tommRoC_hw_err_enum_t _connect(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   tommRoC_hw_comm_ip_v4_add_t*                        const   ipV4AddPtr,
        const   uint16_t                                                    tcpPort) {

    struct sockaddr_in serverAdd;

    long int res;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&serverAdd, 0, sizeof(serverAdd)));

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
    serverAdd.sin_len           = sizeof(serverAdd);
#endif
    serverAdd.sin_family        = AF_INET;
    serverAdd.sin_addr.s_addr   = _ipV4_add_to_in_addr_t(ipV4AddPtr);
    serverAdd.sin_port          = tommRoCHwNetHToNS(tcpPort);

    res = tommRoCHwTemplateNetBSDSocketLowLevelConnect(
            *(int*)socketPtr,
            (struct sockaddr *) &serverAdd,
            sizeof(serverAdd));

    if (res < __RES_SUCCESS_VALUE__) {
        ___close__((void*) socketPtr);
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _connect_host(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   char*                                               const   hostStrPtr,
        const   uint16_t                                                    tcpPort) {

    tommRoC_hw_comm_ip_v4_add_t hostIPv4Add;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwNetDNSGetHostByName(
                    hostStrPtr,
                    &hostIPv4Add));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _connect(
                    socketPtr,
                    &hostIPv4Add,
                    tcpPort));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#if defined (__TOMMROC_HW_USE_BSD_SOCKET_COMPLETE_NET_TEMPLATE__) || defined (__TOMMROC_HW_USE_BSD_SOCKET_ONLY_SERVER_NET_TEMPLATE__)
static tommRoC_hw_err_enum_t _bind(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   uint16_t                                                    port) {

    struct sockaddr_in serverAdd;

    long int res;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&serverAdd, 0, sizeof(serverAdd)));

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
    serverAdd.sin_len           = sizeof(serverAdd);
#endif
    serverAdd.sin_family        = AF_INET;
    serverAdd.sin_addr.s_addr   = INADDR_ANY;
    serverAdd.sin_port          = tommRoCHwNetHToNS(port);

    res = tommRoCHwTemplateNetBSDSocketLowLevelBind(
            *(int*)socketPtr,
            (struct sockaddr *) &serverAdd,
            sizeof(serverAdd));

    if (res < __RES_SUCCESS_VALUE__) {
        ___close__((void*) socketPtr);
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _listen(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   uint32_t                                                    backlog) {

    long int res;

    res = tommRoCHwTemplateNetBSDSocketLowLevelListen(
            *(int*)socketPtr,
            backlog);

    if (res < __RES_SUCCESS_VALUE__) {
        ___close__((void*) socketPtr);
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _accept(
        const   tommRoC_hw_net_socket_def_t*                        const   inSocketPtr,
                tommRoC_hw_net_socket_def_t*                        const   outSocketPtr,
                tommRoC_hw_comm_ip_v4_add_t*                        const   clientIpV4AddPtr) {

    struct sockaddr_in clientAdd;
    socklen_t clientAddLen;

    long int res;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&clientAdd, 0, sizeof(clientAdd)));

    clientAddLen = sizeof(clientAdd);

    res = tommRoCHwTemplateNetBSDSocketLowLevelAccept(
            *(int*)inSocketPtr,
            (struct sockaddr *) &clientAdd,
            &clientAddLen);

    if (res < __RES_SUCCESS_VALUE__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    _in_addr_t_to_ipV4_add(
            clientAdd.sin_addr.s_addr,
            clientIpV4AddPtr);

    *outSocketPtr = (tommRoC_hw_net_socket_def_t) res;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

static tommRoC_hw_err_enum_t _send_to(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   uint8_t                                                     flags,
        const   tommRoC_hw_comm_ip_v4_add_t*                        const   remoteIPv4AddPtr,
        const   uint16_t                                                    port,
        const   void*                                               const   writeBufferPtr,
        const   uint32_t                                                    writeBufferLen,
                int32_t*                                            const   writtenLenPtr,
        const   uint32_t                                                    writeTimeoutMsec) {

    struct sockaddr_in remoteAdd;

    struct timeval tv;
    long int res;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&remoteAdd, 0, sizeof(remoteAdd)));

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
    remoteAdd.sin_len           = sizeof(remoteAdd);
#endif
    remoteAdd.sin_family        = AF_INET;
    remoteAdd.sin_addr.s_addr   = _ipV4_add_to_in_addr_t(remoteIPv4AddPtr);
    remoteAdd.sin_port          = tommRoCHwNetHToNS(port);

    tv.tv_sec   = TOMMROC_UNIT_MEASURE_TIME_mSEC_TO_SEC(writeTimeoutMsec);
    tv.tv_usec  = TOMMROC_UNIT_MEASURE_TIME_mSEC_TO_uSEC(writeTimeoutMsec % 1000);

    res = tommRoCHwTemplateNetBSDSocketLowLevelSetSockOpt(  // Set write timeout
            *(int*)socketPtr,
            SOL_SOCKET,
            SO_SNDTIMEO,
            &tv,
            sizeof(tv));

    if (res < __RES_SUCCESS_VALUE__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    res = tommRoCHwTemplateNetBSDSocketLowLevelSendTo(
            *(int*)socketPtr,
            writeBufferPtr,
            writeBufferLen,
            flags,
            (struct sockaddr *) &remoteAdd,
            sizeof(remoteAdd));

    *writtenLenPtr = (int32_t) res;

    if (res < __RES_SUCCESS_VALUE__) {

        if (EPIPE == errno) {
            return TOMMRO_C_HW_NET_SOCKET_PIPE_ERR;
        }
        else if (ECONNRESET == errno) {
            return TOMMRO_C_HW_NET_SOCKET_CONN_RESET_ERR;
        }
        else if (EINTR == errno) {
            return TOMMRO_C_HW_NET_SOCKET_INTR_ERR;
        }

        return TOMMRO_C_HW_DISCONNECTED_ERR;
    }
    else if (res == 0) {
        return TOMMRO_C_HW_DISCONNECTED_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _recv_from(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   uint8_t                                                     flags,
                tommRoC_hw_comm_ip_v4_add_t*                        const   remoteIPv4AddPtr,
                uint16_t*                                           const   remotePortPtr,
                void*                                               const   readBufferPtr,
        const   uint32_t                                                    readBufferLen,
                int32_t*                                            const   readedLenPtr,
        const   uint32_t                                                    readTimeoutMsec) {

    struct sockaddr_in remoteAdd;
    socklen_t remoteAddLen;

    struct timeval tv;
    long int res;

    tv.tv_sec   = TOMMROC_UNIT_MEASURE_TIME_mSEC_TO_SEC(readTimeoutMsec);
    tv.tv_usec  = TOMMROC_UNIT_MEASURE_TIME_mSEC_TO_uSEC(readTimeoutMsec % 1000);

    res = tommRoCHwTemplateNetBSDSocketLowLevelSetSockOpt(  // Set read timeout
            *(int*)socketPtr,
            SOL_SOCKET,
            SO_RCVTIMEO,
            &tv,
            sizeof(tv));

    if (res < __RES_SUCCESS_VALUE__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    remoteAddLen = sizeof(remoteAdd);

    res = tommRoCHwTemplateNetBSDSocketLowLevelRecvFrom(
            *(int*)socketPtr,
            readBufferPtr,
            readBufferLen,
            flags,
            (struct sockaddr *) &remoteAdd,
            &remoteAddLen);

    *readedLenPtr = (int32_t) res;

    if (res < __RES_SUCCESS_VALUE__) {

        if (EPIPE == errno) {
            return TOMMRO_C_HW_NET_SOCKET_PIPE_ERR;
        }
        else if (ECONNRESET == errno) {
            return TOMMRO_C_HW_NET_SOCKET_CONN_RESET_ERR;
        }
        else if (EINTR == errno) {
            return TOMMRO_C_HW_NET_SOCKET_INTR_ERR;
        }

        return TOMMRO_C_HW_TIMEOUT_ERR;
    }
    else if (res == 0) {
        return TOMMRO_C_HW_DISCONNECTED_ERR;
    }

    _in_addr_t_to_ipV4_add(
            remoteAdd.sin_addr.s_addr,
            remoteIPv4AddPtr);

    *remotePortPtr = tommRoCHwNetNToHS(remoteAdd.sin_port);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _send(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   void*                                               const   writeBufferPtr,
        const   uint32_t                                                    writeBufferLen,
                int32_t*                                            const   writtenLenPtr,
        const   uint32_t                                                    writeTimeoutMsec) {

    struct timeval tv;
    long int res;

    tv.tv_sec   = TOMMROC_UNIT_MEASURE_TIME_mSEC_TO_SEC(writeTimeoutMsec);
    tv.tv_usec  = TOMMROC_UNIT_MEASURE_TIME_mSEC_TO_uSEC(writeTimeoutMsec % 1000);

    res = tommRoCHwTemplateNetBSDSocketLowLevelSetSockOpt(  // Set write timeout
            *(int*)socketPtr,
            SOL_SOCKET,
            SO_SNDTIMEO,
            &tv,
            sizeof(tv));

    if (res < __RES_SUCCESS_VALUE__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    res = tommRoCHwTemplateNetBSDSocketLowLevelSend(
            *(int*)socketPtr,
            writeBufferPtr,
            writeBufferLen,
            0);

    *writtenLenPtr = (int32_t) res;

    if (res < __RES_SUCCESS_VALUE__) {

        if (EPIPE == errno) {
            return TOMMRO_C_HW_NET_SOCKET_PIPE_ERR;
        }
        else if (ECONNRESET == errno) {
            return TOMMRO_C_HW_NET_SOCKET_CONN_RESET_ERR;
        }
        else if (EINTR == errno) {
            return TOMMRO_C_HW_NET_SOCKET_INTR_ERR;
        }

        return TOMMRO_C_HW_DISCONNECTED_ERR;
    }
    else if (res == 0) {
        return TOMMRO_C_HW_DISCONNECTED_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _recv(
        const   tommRoC_hw_net_socket_def_t*                        const   socketPtr,
                void*                                               const   readBufferPtr,
        const   uint32_t                                                    readBufferLen,
                int32_t*                                            const   readedLenPtr,
        const   uint32_t                                                    readTimeoutMsec) {

    struct timeval tv;
    long int res;

    tv.tv_sec   = TOMMROC_UNIT_MEASURE_TIME_mSEC_TO_SEC(readTimeoutMsec);
    tv.tv_usec  = TOMMROC_UNIT_MEASURE_TIME_mSEC_TO_uSEC(readTimeoutMsec % 1000);

    res = tommRoCHwTemplateNetBSDSocketLowLevelSetSockOpt(  // Set read timeout
            *(int*)socketPtr,
            SOL_SOCKET,
            SO_RCVTIMEO,
            &tv,
            sizeof(tv));

    if (res < __RES_SUCCESS_VALUE__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    res = tommRoCHwTemplateNetBSDSocketLowLevelRecv(
            *(int*)socketPtr,
            readBufferPtr,
            readBufferLen,
            0);

    *readedLenPtr = (int32_t) res;

    if (res < __RES_SUCCESS_VALUE__) {

        if (EPIPE == errno) {
            return TOMMRO_C_HW_NET_SOCKET_PIPE_ERR;
        }
        else if (ECONNRESET == errno) {
            return TOMMRO_C_HW_NET_SOCKET_CONN_RESET_ERR;
        }
        else if (EINTR == errno) {
            return TOMMRO_C_HW_NET_SOCKET_INTR_ERR;
        }

        return TOMMRO_C_HW_TIMEOUT_ERR;
    }
    else if (res == 0) {
        return TOMMRO_C_HW_DISCONNECTED_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _shutdown(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   tommRoC_hw_net_socket_def_shutdown_how_enum_t               how) {

    long int res;

    int howINT;

    howINT = _shutdown_how_enum_to_INT(how);

    TOMMROC_HW_PARAM_CHECK_ON_TEST_RETURN_ERR(howINT, ==, __TO_INT_ERROR_VALUE__);

    res = tommRoCHwTemplateNetBSDSocketLowLevelShutdown(
            *(int*)socketPtr,
            howINT);

    if (res < __RES_SUCCESS_VALUE__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _close(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr) {

    long int res;

    res = ___close__(socketPtr);

    if (res < __RES_SUCCESS_VALUE__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _get_sock_opt(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   tommRoC_hw_net_socket_def_sock_opt_level_enum_t             level,
        const   tommRoC_hw_net_socket_def_sock_opt_opt_name_enum_t          optName,
                void*                                               const   optValPtr,
        const   uint32_t                                                    optSizeByte,
                uint32_t*                                           const   optLenPtr,
                int*                                                const   lowLevelResPtr) {

    socklen_t optlen;
    long int res;

    int levelINT;
    int optNameINT;

    levelINT    = _sock_opt_level_enum_to_INT(level);
    optNameINT  = _sock_opt_opt_name_enum_to_INT(optName);

    TOMMROC_HW_PARAM_CHECK_ON_TEST_RETURN_ERR(levelINT,     ==, __TO_INT_ERROR_VALUE__);
    TOMMROC_HW_PARAM_CHECK_ON_TEST_RETURN_ERR(optNameINT,   ==, __TO_INT_ERROR_VALUE__);

    res = tommRoCHwTemplateNetBSDSocketLowLevelGetSockOpt(
            *(int*)socketPtr,
            levelINT,
            optNameINT,
            optValPtr,
            &optlen);

    *lowLevelResPtr = (int) res;

    *optLenPtr = (uint32_t) optlen;

    TOMMROC_ASSERT_LESS_OR_EQUALS_THAN((uint32_t) optlen, optSizeByte);

    if ((uint32_t) optlen > optSizeByte) {
        return TOMMRO_C_HW_PARAM_ERR;
    }

    if (res < __RES_SUCCESS_VALUE__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _set_sock_opt(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   tommRoC_hw_net_socket_def_sock_opt_level_enum_t             level,
        const   tommRoC_hw_net_socket_def_sock_opt_opt_name_enum_t          optName,
        const   void*                                               const   optValPtr,
        const   uint32_t                                                    optSizeByte,
                int*                                                const   lowLevelResPtr) {

    long int res;

    int levelINT;
    int optNameINT;

    levelINT    = _sock_opt_level_enum_to_INT(level);
    optNameINT  = _sock_opt_opt_name_enum_to_INT(optName);

    TOMMROC_HW_PARAM_CHECK_ON_TEST_RETURN_ERR(levelINT,     ==, __TO_INT_ERROR_VALUE__);
    TOMMROC_HW_PARAM_CHECK_ON_TEST_RETURN_ERR(optNameINT,   ==, __TO_INT_ERROR_VALUE__);

    res = tommRoCHwTemplateNetBSDSocketLowLevelSetSockOpt(
            *(int*)socketPtr,
            levelINT,
            optNameINT,
            optValPtr,
            optSizeByte);

    *lowLevelResPtr = (int) res;

    if (res < __RES_SUCCESS_VALUE__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _fcntl(
                tommRoC_hw_net_socket_def_t*                        const   socketPtr,
        const   tommRoC_hw_net_socket_def_fcntl_cmd_enum_t                  cmd,
        const   int                                                         val,
                int*                                                const   lowLevelResPtr) {

    long int res;

    int cmdINT;

    cmdINT = _fcntl_cmd_enum_to_INT(cmd);

    TOMMROC_HW_PARAM_CHECK_ON_TEST_RETURN_ERR(cmdINT, ==, __TO_INT_ERROR_VALUE__);

    res = tommRoCHwTemplateNetBSDSocketLowLevelFcntl(
            *(int*)socketPtr,
            cmdINT,
            val);

    *lowLevelResPtr = (int) res;

    if (res < __RES_SUCCESS_VALUE__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateNetBSDSocketCompleteStart(void) {

#if defined (__TOMMROC_HW_USE_BSD_SOCKET_COMPLETE_NET_TEMPLATE__)

    tommRoC_hw_net_socket_complete_init_t netSocketInit = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_hw_net_socket_complete_init_t);

    netSocketInit.deviceType        = TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_HW_ETHERNET_WIFI;
    netSocketInit.maxActiveConn     = TOMMROC_HW_TEMPLATE_NET_BSD_SOCKET_LOW_LEVEL_MAX_ACTIVE_CONN;

    netSocketInit.newFunct          = _new;
    netSocketInit.connectFunct      = _connect;
    netSocketInit.connectHostFunct  = _connect_host;
    netSocketInit.bindFunct         = _bind;
    netSocketInit.listenFunct       = _listen;
    netSocketInit.acceptFunct       = _accept;
    netSocketInit.sendToFunct       = _send_to;
    netSocketInit.recvFromFunct     = _recv_from;
    netSocketInit.sendFunct         = _send;
    netSocketInit.recvFunct         = _recv;
    netSocketInit.shutdownFunct     = _shutdown;
    netSocketInit.closeFunct        = _close;
    netSocketInit.getSockOptFunct   = _get_sock_opt;
    netSocketInit.setSockOptFunct   = _set_sock_opt;
    netSocketInit.fcntlFunct        = _fcntl;

    return tommRoCHwNetSocketInitEnvComplete(&netSocketInit);
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNetBSDSocketOnlyClientStart(void) {

#if defined (__TOMMROC_HW_USE_BSD_SOCKET_ONLY_CLIENT_NET_TEMPLATE__)

    tommRoC_hw_net_socket_only_client_init_t netSocketInit = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_hw_net_socket_only_client_init_t);

    netSocketInit.deviceType        = TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_HW_ETHERNET_WIFI;
    netSocketInit.maxActiveConn     = TOMMROC_HW_TEMPLATE_NET_BSD_SOCKET_LOW_LEVEL_MAX_ACTIVE_CONN;

    netSocketInit.newFunct          = _new;
    netSocketInit.connectFunct      = _connect;
    netSocketInit.connectHostFunct  = _connect_host;
    netSocketInit.sendToFunct       = _send_to;
    netSocketInit.recvFromFunct     = _recv_from;
    netSocketInit.sendFunct         = _send;
    netSocketInit.recvFunct         = _recv;
    netSocketInit.shutdownFunct     = _shutdown;
    netSocketInit.closeFunct        = _close;
    netSocketInit.getSockOptFunct   = _get_sock_opt;
    netSocketInit.setSockOptFunct   = _set_sock_opt;
    netSocketInit.fcntlFunct        = _fcntl;

    return tommRoCHwNetSocketInitEnvOnlyClient(&netSocketInit);
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNetBSDSocketOnlyServerStart(void) {

#if defined (__TOMMROC_HW_USE_BSD_SOCKET_ONLY_SERVER_NET_TEMPLATE__)

    tommRoC_hw_net_socket_only_server_init_t netSocketInit = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_hw_net_socket_only_server_init_t);

    netSocketInit.deviceType        = TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_HW_ETHERNET_WIFI;
    netSocketInit.maxActiveConn     = TOMMROC_HW_TEMPLATE_NET_BSD_SOCKET_LOW_LEVEL_MAX_ACTIVE_CONN;

    netSocketInit.newFunct          = _new;
    netSocketInit.bindFunct         = _bind;
    netSocketInit.listenFunct       = _listen;
    netSocketInit.acceptFunct       = _accept;
    netSocketInit.sendToFunct       = _send_to;
    netSocketInit.recvFromFunct     = _recv_from;
    netSocketInit.sendFunct         = _send;
    netSocketInit.recvFunct         = _recv;
    netSocketInit.shutdownFunct     = _shutdown;
    netSocketInit.closeFunct        = _close;
    netSocketInit.getSockOptFunct   = _get_sock_opt;
    netSocketInit.setSockOptFunct   = _set_sock_opt;
    netSocketInit.fcntlFunct        = _fcntl;

    return tommRoCHwNetSocketInitEnvOnlyServer(&netSocketInit);
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNetBSDSocketStop(void) {

#if defined (__TOMMROC_HW_NET_BSD_SOCKET_TEMPLATE_IS_USED__)

    _guard_ptr = NULL;

    return tommRoCHwNetSocketCloseEnv();
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateNetBSDSocketSetGuard(const tommRoC_guard_t* const guardPtr) {

#if defined (__TOMMROC_HW_NET_BSD_SOCKET_TEMPLATE_IS_USED__)

    if (NULL != guardPtr) {
        TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCGuardCheck(guardPtr), TOMMRO_C_HW_PARAM_ERR);
    }

    _guard_ptr = (tommRoC_guard_t*) guardPtr;

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}
