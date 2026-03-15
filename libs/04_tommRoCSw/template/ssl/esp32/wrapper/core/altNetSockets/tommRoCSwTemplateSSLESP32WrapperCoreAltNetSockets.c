
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateSSLESP32WrapperCoreAltNetSockets.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCHw.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

// NOTE: experimental values
#define __HW_ETHERNET_WIFI_RECV_TIMEOUT_MSEC__              (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(1UL))
#define __SPI_BUS_ETHERNET_RECV_TIMEOUT_MSEC__              (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(2UL))
#define __SPI_BUS_WIFI_RECV_TIMEOUT_MSEC__                  (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(2UL))
#define __AT_COMMAND_ETHERNET_RECV_TIMEOUT_MSEC__           (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(3UL))
#define __AT_COMMAND_WIFI_RECV_TIMEOUT_MSEC__               (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(3UL))
#define __AT_COMMAND_GSM_MODEM_RECV_TIMEOUT_MSEC__          (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(5UL))
#define __LTE_MODEM_OVER_LWIP_RECV_TIMEOUT_MSEC__           (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(5UL))

#define __HW_ETHERNET_WIFI_SEND_TIMEOUT_MSEC__              (__HW_ETHERNET_WIFI_RECV_TIMEOUT_MSEC__)
#define __SPI_BUS_ETHERNET_SEND_TIMEOUT_MSEC__              (__SPI_BUS_ETHERNET_RECV_TIMEOUT_MSEC__)
#define __SPI_BUS_WIFI_SEND_TIMEOUT_MSEC__                  (__SPI_BUS_WIFI_RECV_TIMEOUT_MSEC__)
#define __AT_COMMAND_ETHERNET_SEND_TIMEOUT_MSEC__           (__AT_COMMAND_ETHERNET_RECV_TIMEOUT_MSEC__)
#define __AT_COMMAND_WIFI_SEND_TIMEOUT_MSEC__               (__AT_COMMAND_WIFI_RECV_TIMEOUT_MSEC__)
#define __AT_COMMAND_GSM_MODEM_SEND_TIMEOUT_MSEC__          (__AT_COMMAND_GSM_MODEM_RECV_TIMEOUT_MSEC__)
#define __LTE_MODEM_OVER_LWIP_SEND_TIMEOUT_MSEC__           (__LTE_MODEM_OVER_LWIP_RECV_TIMEOUT_MSEC__)


#define __HW_ETHERNET_WIFI_RECV_SINGLE_TIMEOUT_MSEC__       (10UL)
#define __SPI_BUS_ETHERNET_RECV_SINGLE_TIMEOUT_MSEC__       (25UL)
#define __SPI_BUS_WIFI_RECV_SINGLE_TIMEOUT_MSEC__           (25UL)
#define __AT_COMMAND_ETHERNET_RECV_SINGLE_TIMEOUT_MSEC__    (30UL)
#define __AT_COMMAND_WIFI_RECV_SINGLE_TIMEOUT_MSEC__        (50UL)
#define __AT_COMMAND_GSM_MODEM_RECV_SINGLE_TIMEOUT_MSEC__   (100UL)
#define __LTE_MODEM_OVER_LWIP_RECV_SINGLE_TIMEOUT_MSEC__    (100UL)

#define __HW_ETHERNET_WIFI_SEND_SINGLE_TIMEOUT_MSEC__       (__HW_ETHERNET_WIFI_RECV_SINGLE_TIMEOUT_MSEC__)
#define __SPI_BUS_ETHERNET_SEND_SINGLE_TIMEOUT_MSEC__       (__SPI_BUS_ETHERNET_RECV_SINGLE_TIMEOUT_MSEC__)
#define __SPI_BUS_WIFI_SEND_SINGLE_TIMEOUT_MSEC__           (__SPI_BUS_WIFI_RECV_SINGLE_TIMEOUT_MSEC__)
#define __AT_COMMAND_ETHERNET_SEND_SINGLE_TIMEOUT_MSEC__    (__AT_COMMAND_ETHERNET_RECV_SINGLE_TIMEOUT_MSEC__)
#define __AT_COMMAND_WIFI_SEND_SINGLE_TIMEOUT_MSEC__        (__AT_COMMAND_WIFI_RECV_SINGLE_TIMEOUT_MSEC__)
#define __AT_COMMAND_GSM_MODEM_SEND_SINGLE_TIMEOUT_MSEC__   (__AT_COMMAND_GSM_MODEM_RECV_SINGLE_TIMEOUT_MSEC__)
#define __LTE_MODEM_OVER_LWIP_SEND_SINGLE_TIMEOUT_MSEC__    (__LTE_MODEM_OVER_LWIP_RECV_SINGLE_TIMEOUT_MSEC__)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
TOMMROC_SCTA_SIZE_OF_EQUALS(((mbedtls_net_context*)NULL)->fd, tommRoC_hw_net_socket_def_t);

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_DEBUG_ENABLE__)
static const char __DEBUG_OBJ_ID__[] = "swAltNetSkt";
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
static uint32_t _get_recv_timeout_msec(void) {

    tommRoC_hw_net_socket_def_device_type_enum_t deviceType;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwNetSocketGetDeviceType(&deviceType));

    do { // Added to avoid "warning: unreachable code"
        switch (deviceType) {

        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_HW_ETHERNET_WIFI:        return __HW_ETHERNET_WIFI_RECV_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_SPI_BUS_ETHERNET:        return __SPI_BUS_ETHERNET_RECV_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_SPI_BUS_WIFI:            return __SPI_BUS_WIFI_RECV_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_ETHERNET:     return __AT_COMMAND_ETHERNET_RECV_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_WIFI:         return __AT_COMMAND_WIFI_RECV_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_GSM_MODEM:    return __AT_COMMAND_GSM_MODEM_RECV_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_LTE_MODEM_OVER_LWIP:     return __LTE_MODEM_OVER_LWIP_RECV_TIMEOUT_MSEC__;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            break;
        }
    } while (0);

    return __AT_COMMAND_GSM_MODEM_RECV_TIMEOUT_MSEC__;
}

static uint32_t _get_send_timeout_msec(void) {

    tommRoC_hw_net_socket_def_device_type_enum_t deviceType;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwNetSocketGetDeviceType(&deviceType));

    do { // Added to avoid "warning: unreachable code"
        switch (deviceType) {

        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_HW_ETHERNET_WIFI:        return __HW_ETHERNET_WIFI_SEND_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_SPI_BUS_ETHERNET:        return __SPI_BUS_ETHERNET_SEND_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_SPI_BUS_WIFI:            return __SPI_BUS_WIFI_SEND_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_ETHERNET:     return __AT_COMMAND_ETHERNET_SEND_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_WIFI:         return __AT_COMMAND_WIFI_SEND_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_GSM_MODEM:    return __AT_COMMAND_GSM_MODEM_SEND_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_LTE_MODEM_OVER_LWIP:     return __LTE_MODEM_OVER_LWIP_SEND_TIMEOUT_MSEC__;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            break;
        }
    } while (0);

    return __AT_COMMAND_GSM_MODEM_SEND_TIMEOUT_MSEC__;
}

static uint32_t _get_recv_single_timeout_msec(void) {

    tommRoC_hw_net_socket_def_device_type_enum_t deviceType;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwNetSocketGetDeviceType(&deviceType));

    do { // Added to avoid "warning: unreachable code"
        switch (deviceType) {

        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_HW_ETHERNET_WIFI:        return __HW_ETHERNET_WIFI_RECV_SINGLE_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_SPI_BUS_ETHERNET:        return __SPI_BUS_ETHERNET_RECV_SINGLE_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_SPI_BUS_WIFI:            return __SPI_BUS_WIFI_RECV_SINGLE_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_ETHERNET:     return __AT_COMMAND_ETHERNET_RECV_SINGLE_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_WIFI:         return __AT_COMMAND_WIFI_RECV_SINGLE_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_GSM_MODEM:    return __AT_COMMAND_GSM_MODEM_RECV_SINGLE_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_LTE_MODEM_OVER_LWIP:     return __LTE_MODEM_OVER_LWIP_RECV_SINGLE_TIMEOUT_MSEC__;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            break;
        }
    } while (0);

    return __AT_COMMAND_GSM_MODEM_RECV_SINGLE_TIMEOUT_MSEC__;
}

static uint32_t _get_send_single_timeout_msec(void) {

    tommRoC_hw_net_socket_def_device_type_enum_t deviceType;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwNetSocketGetDeviceType(&deviceType));

    do { // Added to avoid "warning: unreachable code"
        switch (deviceType) {

        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_HW_ETHERNET_WIFI:        return __HW_ETHERNET_WIFI_SEND_SINGLE_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_SPI_BUS_ETHERNET:        return __SPI_BUS_ETHERNET_SEND_SINGLE_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_SPI_BUS_WIFI:            return __SPI_BUS_WIFI_SEND_SINGLE_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_ETHERNET:     return __AT_COMMAND_ETHERNET_SEND_SINGLE_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_WIFI:         return __AT_COMMAND_WIFI_SEND_SINGLE_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_AT_COMMAND_GSM_MODEM:    return __AT_COMMAND_GSM_MODEM_SEND_SINGLE_TIMEOUT_MSEC__;
        case TOMMROC_HW_NET_SOCKET_DEF_DEVICE_TYPE_LTE_MODEM_OVER_LWIP:     return __LTE_MODEM_OVER_LWIP_SEND_SINGLE_TIMEOUT_MSEC__;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            break;
        }
    } while (0);

    return __AT_COMMAND_GSM_MODEM_SEND_SINGLE_TIMEOUT_MSEC__;
}

/*
 * Check if the requested operation would be blocking on a non-blocking socket
 * and thus 'failed' with a negative return value.
 *
 * Note: on a blocking socket this function always returns 0!
 */
static int net_would_block(const mbedtls_net_context *ctx) {

    int* fdPtr = &(((mbedtls_net_context*) ctx)->fd);

    tommRoC_hw_net_socket_def_t* socketPtr = (tommRoC_hw_net_socket_def_t*) fdPtr;

    int lowLevelRes;

    if (*fdPtr < 0) {
        return MBEDTLS_ERR_NET_INVALID_CONTEXT;
    }

    // If socket FCNTL is not available
    if (TOMMRO_C_HW_ERR_SUCCESS != tommRoCHwNetSocketIsOpAvailable(TOMMROC_HW_NET_SOCKET_FCNTL)) {
        // Return generic error
        return MBEDTLS_ERR_NET_INVALID_CONTEXT;
    }

    if (TOMMRO_C_HW_ERR_SUCCESS != tommRoCHwNetSocketFcntl(socketPtr, TOMMROC_HW_NET_SOCKET_DEF_FCNTL_CMD_F_GETFL, 0, &lowLevelRes)) {
        return MBEDTLS_ERR_NET_BAD_INPUT_DATA;
    }

    /*
     * Never return 'WOULD BLOCK' on a blocking socket
     */
    if (TOMMROC_HW_NET_SOCKET_DEF_O_NONBLOCK != (lowLevelRes & TOMMROC_HW_NET_SOCKET_DEF_O_NONBLOCK)) {
        return 0;
    }

    return 0;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

int tommRoCSwTemplateSSLESP32WrapperCoreAltNetSocketsNetConnect(mbedtls_net_context *ctx, const char *host, const char *port, int proto) {

    tommRoC_hw_comm_ip_v4_add_as_string_t ipV4AsString;
    tommRoC_hw_comm_ip_v4_add_t ipV4;

    tommRoC_hw_net_socket_def_t socket;
    uint16_t tcpPort;

    tommRoC_hw_err_enum_t hwRes;

    if (NULL == ctx) {
        return MBEDTLS_ERR_NET_INVALID_CONTEXT;
    }

    if (TOMMRO_C_ERR_SUCCESS != tommRoCStringStringToU16(port, tommRoCStringStrLen(port), 10, &tcpPort)) {
        TOMMROC_DEBUG_E("connect port to string error!!!");
        return MBEDTLS_ERR_NET_UNKNOWN_HOST;
    }

    hwRes = tommRoCHwNetSocketNew(
            TOMMROC_HW_NET_SOCKET_DEF_DOMAIN_PF_INET,
            (MBEDTLS_NET_PROTO_UDP == proto) ? (TOMMROC_HW_NET_SOCKET_DEF_TYPE_SOCK_DGRAM) : (TOMMROC_HW_NET_SOCKET_DEF_TYPE_SOCK_STREAM),
            (MBEDTLS_NET_PROTO_UDP == proto) ? (TOMMROC_HW_NET_SOCKET_DEF_PROTOCOL_UDP) : (TOMMROC_HW_NET_SOCKET_DEF_PROTOCOL_TCP),
            &socket);

    if (TOMMRO_C_HW_ERR_SUCCESS != hwRes) {
        TOMMROC_DEBUG_E("connect socket new error!!!");
        return MBEDTLS_ERR_NET_SOCKET_FAILED;
    }

    // If host name is IpV4 format (xxx.xxx.xxx.xxx)
    if (TOMMRO_C_HW_ERR_SUCCESS == tommRoCHwCommIPv4AsStringItfInit(host, &ipV4AsString)) {

        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwCommIPv4AsStringToItf(&ipV4AsString, &ipV4));

        hwRes = tommRoCHwNetSocketConnect(
                &socket,
                &ipV4,
                tcpPort);
    }
    else {

        hwRes = tommRoCHwNetSocketConnectHost(
                &socket,
                host,
                tcpPort);
    }

    if (TOMMRO_C_HW_ERR_SUCCESS != hwRes) {
        TOMMROC_DEBUG_E("connect connect host error!!!");
        tommRoCHwNetSocketClose(&socket);
        return MBEDTLS_ERR_NET_CONNECT_FAILED;
    }

    ctx->fd = (int) socket;

    return 0;
}

int tommRoCSwTemplateSSLESP32WrapperCoreAltNetSocketsNetSend(void *ctx, const unsigned char *buf, size_t len) {

    int* fdPtr = &(((mbedtls_net_context*) ctx)->fd);

    tommRoC_hw_net_socket_def_t* socketPtr = (tommRoC_hw_net_socket_def_t*) fdPtr;

    uint32_t sendTimeoutMsec;
    uint32_t sendSingleTimeoutMsec;

    tommRoC_timer_t timer;

    uint32_t remaining;
    const void* ptr;
    uint32_t sent;

    uint32_t remainingMsec;

    int32_t writtenLen;

    tommRoC_hw_err_enum_t hwRes;

    if (NULL == ctx) {
        return MBEDTLS_ERR_NET_INVALID_CONTEXT;
    }

    if (*fdPtr < 0) {
        TOMMROC_DEBUG_E("send (*fdPtr < 0) error!!!");
        return MBEDTLS_ERR_NET_INVALID_CONTEXT;
    }

    sendTimeoutMsec         = _get_send_timeout_msec();
    sendSingleTimeoutMsec   = _get_send_single_timeout_msec();

    remaining   = (uint32_t) len;
    ptr         = buf;
    sent        = 0;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, sendTimeoutMsec));

    while (remaining > 0) {

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerRemaining(&timer, &remainingMsec));

        hwRes = tommRoCHwNetSocketSend(
                socketPtr,
                ptr,
                remaining,
                &writtenLen,
                tommRoCMathMin(sendSingleTimeoutMsec, ((0 == remainingMsec) ? (1) : (remainingMsec))));

        if (TOMMRO_C_HW_ERR_SUCCESS == hwRes) {
            if (0 != writtenLen) {
                remaining   -= writtenLen;
                ptr         += writtenLen;
                sent        += writtenLen;
            }
        }
        else if (TOMMRO_C_HW_TIMEOUT_ERR == hwRes) {
            if (0 != sent) {
                return (int) sent;
            }
        }
        else {
            // If socket FCNTL is available
            if (TOMMRO_C_HW_ERR_SUCCESS == tommRoCHwNetSocketIsOpAvailable(TOMMROC_HW_NET_SOCKET_FCNTL)) {

                if (net_would_block(ctx) != 0) {
                    TOMMROC_DEBUG_E("send (net_would_block(ctx) != 0) error!!!");
                    return MBEDTLS_ERR_SSL_WANT_WRITE;
                }
            }

            if ((TOMMRO_C_HW_NET_SOCKET_PIPE_ERR == hwRes) || (TOMMRO_C_HW_NET_SOCKET_CONN_RESET_ERR == hwRes)) {
                TOMMROC_DEBUG_E("send ((TOMMRO_C_HW_NET_SOCKET_PIPE_ERR == hwRes) || (TOMMRO_C_HW_NET_SOCKET_CONN_RESET_ERR == hwRes)) error!!!");
                return MBEDTLS_ERR_NET_CONN_RESET;
            }
            else if (TOMMRO_C_HW_NET_SOCKET_INTR_ERR == hwRes) {
                TOMMROC_DEBUG_E("send (TOMMRO_C_HW_NET_SOCKET_INTR_ERR == hwRes) error!!!");
                return MBEDTLS_ERR_SSL_WANT_WRITE;
            }

            TOMMROC_DEBUG_E("send (writtenLen < 0) error!!!");

            return MBEDTLS_ERR_NET_SEND_FAILED;
        }

        if (remaining > 0) {
            if (TOMMRO_C_TIMER_EXPIRED_ERR == tommRoCTimerIsExpired(&timer)) {
                return (int) sent;
            }

            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));
        }
        else {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(0));
        }
    }

    return (int) sent;
}

int tommRoCSwTemplateSSLESP32WrapperCoreAltNetSocketsNetRecv(void *ctx, unsigned char *buf, size_t len) {

    return tommRoCSwTemplateSSLESP32WrapperCoreAltNetSocketsNetRecvTimeout(
            ctx,
            buf,
            len,
            _get_recv_timeout_msec());
}

int tommRoCSwTemplateSSLESP32WrapperCoreAltNetSocketsNetRecvTimeout(void *ctx, unsigned char *buf, size_t len, uint32_t timeout) {

    int* fdPtr = &(((mbedtls_net_context*) ctx)->fd);

    tommRoC_hw_net_socket_def_t* socketPtr = (tommRoC_hw_net_socket_def_t*) fdPtr;

    uint32_t recvSingleTimeoutMsec;

    tommRoC_timer_t timer;

    uint32_t remaining;
    void* ptr;
    uint32_t recv;

    uint32_t remainingMsec;

    int32_t readLen;

    tommRoC_hw_err_enum_t hwRes;

    if (NULL == ctx) {
        return MBEDTLS_ERR_NET_INVALID_CONTEXT;
    }

    if (*fdPtr < 0) {
        TOMMROC_DEBUG_E("recv_timeout (*fdPtr < 0) error!!!");
        return MBEDTLS_ERR_NET_INVALID_CONTEXT;
    }

    recvSingleTimeoutMsec = _get_recv_single_timeout_msec();

    remaining   = (uint32_t) len;
    ptr         = buf;
    recv        = 0;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, timeout));

    while (remaining > 0) {
    
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerRemaining(&timer, &remainingMsec));

        // NOTE: single receive timeout is minimum between recvSingleTimeoutMsec and remaining timeout
        hwRes = tommRoCHwNetSocketRecv(
                socketPtr,
                ptr,
                remaining,
                &readLen,
                tommRoCMathMin(recvSingleTimeoutMsec, ((0 == remainingMsec) ? (1) : (remainingMsec))));

        if (TOMMRO_C_HW_ERR_SUCCESS == hwRes) {
            if (0 != readLen) {
                remaining   -= readLen;
                ptr         += readLen;
                recv        += readLen;
            }
        }
        else if (TOMMRO_C_HW_TIMEOUT_ERR == hwRes) {
            if (0 != recv) {
                return (int) recv;
            }
        }
        else {
            // If socket FCNTL is available
            if (TOMMRO_C_HW_ERR_SUCCESS == tommRoCHwNetSocketIsOpAvailable(TOMMROC_HW_NET_SOCKET_FCNTL)) {

                if (net_would_block(ctx) != 0) {
                    TOMMROC_DEBUG_E("recv_timeout (net_would_block(ctx) != 0) error!!!");
                    return MBEDTLS_ERR_SSL_WANT_READ;
                }
            }

            if ((TOMMRO_C_HW_NET_SOCKET_PIPE_ERR == hwRes) || (TOMMRO_C_HW_NET_SOCKET_CONN_RESET_ERR == hwRes)) {
                TOMMROC_DEBUG_E("recv_timeout ((TOMMRO_C_HW_NET_SOCKET_PIPE_ERR == hwRes) || (TOMMRO_C_HW_NET_SOCKET_CONN_RESET_ERR == hwRes)) error!!!");
                return MBEDTLS_ERR_NET_CONN_RESET;
            }
            else if (TOMMRO_C_HW_NET_SOCKET_INTR_ERR == hwRes) {
                TOMMROC_DEBUG_E("recv_timeout (TOMMRO_C_HW_NET_SOCKET_INTR_ERR == hwRes) error!!!");
                return MBEDTLS_ERR_SSL_WANT_READ;
            }

            TOMMROC_DEBUG_E("recv_timeout (readLen < 0) error!!!");

            return MBEDTLS_ERR_NET_RECV_FAILED;
        }

        if (remaining > 0) {
            if (TOMMRO_C_TIMER_EXPIRED_ERR == tommRoCTimerIsExpired(&timer)) {
                return (int) recv;
            }

            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));
        }
        else {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(0));
        }
    }

    return (int) recv;
}

#endif
