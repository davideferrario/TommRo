
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateNetBSDSocketLowLevel.h"

#if defined (__TOMMROC_HW_NET_BSD_SOCKET_TEMPLATE_IS_USED__)

#include "TOMMROC.h"

#include "TOMMROCMwTemplate.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
//#define __BEFORE_OPERATION_WAIT_MSEC__  (1)
//#define __AFTER_OPERATION_WAIT_MSEC__   (1)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

long int tommRoCHwTemplateNetBSDSocketLowLevelSocket(int domain, int type, int protocol) {

    long int res;

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__BEFORE_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__BEFORE_OPERATION_WAIT_MSEC__));
#endif

    res = tommRoCHwTemplateNetBSDSocketLowLevelEnvSocket(domain, type, protocol);

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__AFTER_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__AFTER_OPERATION_WAIT_MSEC__));
#endif

    return res;
}

long int tommRoCHwTemplateNetBSDSocketLowLevelConnect(int socket, const void* addr, int len) {

    long int res;

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__BEFORE_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__BEFORE_OPERATION_WAIT_MSEC__));
#endif

    res = tommRoCHwTemplateNetBSDSocketLowLevelEnvConnect(socket, addr, len);

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__AFTER_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__AFTER_OPERATION_WAIT_MSEC__));
#endif

    return res;
}

long int tommRoCHwTemplateNetBSDSocketLowLevelBind(int socket, const void* addr, int len) {

    long int res;

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__BEFORE_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__BEFORE_OPERATION_WAIT_MSEC__));
#endif

    res = tommRoCHwTemplateNetBSDSocketLowLevelEnvBind(socket, addr, len);

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__AFTER_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__AFTER_OPERATION_WAIT_MSEC__));
#endif

    return res;
}

long int tommRoCHwTemplateNetBSDSocketLowLevelListen(int socket, int backlog) {

    long int res;

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__BEFORE_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__BEFORE_OPERATION_WAIT_MSEC__));
#endif

    res = tommRoCHwTemplateNetBSDSocketLowLevelEnvListen(socket, backlog);

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__AFTER_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__AFTER_OPERATION_WAIT_MSEC__));
#endif

    return res;
}

long int tommRoCHwTemplateNetBSDSocketLowLevelAccept(int socket, void* addr, void* len) {

    long int res;

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__BEFORE_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__BEFORE_OPERATION_WAIT_MSEC__));
#endif

    res = tommRoCHwTemplateNetBSDSocketLowLevelEnvAccept(socket, addr, len);

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__AFTER_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__AFTER_OPERATION_WAIT_MSEC__));
#endif

    return res;
}

long int tommRoCHwTemplateNetBSDSocketLowLevelSendTo(int socket, const void* data, int size, int flags, const void* to, int tolen) {

    long int res;

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__BEFORE_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__BEFORE_OPERATION_WAIT_MSEC__));
#endif

    res = tommRoCHwTemplateNetBSDSocketLowLevelEnvSendTo(socket, data, size, flags, to, tolen);

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__AFTER_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__AFTER_OPERATION_WAIT_MSEC__));
#endif

    return res;
}

long int tommRoCHwTemplateNetBSDSocketLowLevelRecvFrom(int socket, void* mem, int len, int flags, void* from, void* fromlen) {

    long int res;

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__BEFORE_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__BEFORE_OPERATION_WAIT_MSEC__));
#endif

    res = tommRoCHwTemplateNetBSDSocketLowLevelEnvRecvFrom(socket, mem, len, flags, from, fromlen);

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__AFTER_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__AFTER_OPERATION_WAIT_MSEC__));
#endif

    return res;
}

long int tommRoCHwTemplateNetBSDSocketLowLevelSend(int socket, const void* data, int size, int flags) {

    long int res;

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__BEFORE_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__BEFORE_OPERATION_WAIT_MSEC__));
#endif

    res = tommRoCHwTemplateNetBSDSocketLowLevelEnvSend(socket, data, size, flags);

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__AFTER_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__AFTER_OPERATION_WAIT_MSEC__));
#endif

    return res;
}

long int tommRoCHwTemplateNetBSDSocketLowLevelRecv(int socket, void* mem, int len, int flags) {

    long int res;

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__BEFORE_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__BEFORE_OPERATION_WAIT_MSEC__));
#endif

    res = tommRoCHwTemplateNetBSDSocketLowLevelEnvRecv(socket, mem, len, flags);

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__AFTER_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__AFTER_OPERATION_WAIT_MSEC__));
#endif

    return res;
}

long int tommRoCHwTemplateNetBSDSocketLowLevelShutdown(int socket, int how) {

    long int res;

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__BEFORE_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__BEFORE_OPERATION_WAIT_MSEC__));
#endif

    res = tommRoCHwTemplateNetBSDSocketLowLevelEnvShutdown(socket, how);

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__AFTER_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__AFTER_OPERATION_WAIT_MSEC__));
#endif

    return res;
}

long int tommRoCHwTemplateNetBSDSocketLowLevelClose(int socket) {

    long int res;

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__BEFORE_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__BEFORE_OPERATION_WAIT_MSEC__));
#endif

    res = tommRoCHwTemplateNetBSDSocketLowLevelEnvClose(socket);

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__AFTER_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__AFTER_OPERATION_WAIT_MSEC__));
#endif

    return res;
}

long int tommRoCHwTemplateNetBSDSocketLowLevelGetSockOpt(int socket, int level, int optname, void* optval, void* optlen) {

    long int res;

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__BEFORE_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__BEFORE_OPERATION_WAIT_MSEC__));
#endif

    res = tommRoCHwTemplateNetBSDSocketLowLevelEnvGetSockOpt(socket, level, optname, optval, optlen);

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__AFTER_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__AFTER_OPERATION_WAIT_MSEC__));
#endif

    return res;
}

long int tommRoCHwTemplateNetBSDSocketLowLevelSetSockOpt(int socket, int level, int optname, const void* optval, int optlen) {

    long int res;

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__BEFORE_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__BEFORE_OPERATION_WAIT_MSEC__));
#endif

    res = tommRoCHwTemplateNetBSDSocketLowLevelEnvSetSockOpt(socket, level, optname, optval, optlen);

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__AFTER_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__AFTER_OPERATION_WAIT_MSEC__));
#endif

    return res;
}

long int tommRoCHwTemplateNetBSDSocketLowLevelFcntl(int socket, int cmd, int val) {

    long int res;

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__BEFORE_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__BEFORE_OPERATION_WAIT_MSEC__));
#endif

    res = tommRoCHwTemplateNetBSDSocketLowLevelEnvFcntl(socket, cmd, val);

#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__) && defined (__AFTER_OPERATION_WAIT_MSEC__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(__AFTER_OPERATION_WAIT_MSEC__));
#endif

    return res;
}

#endif
