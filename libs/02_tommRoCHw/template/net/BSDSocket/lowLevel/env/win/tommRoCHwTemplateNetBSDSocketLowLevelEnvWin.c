
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateNetBSDSocketLowLevelEnvWin.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)

#if defined (__TOMMROC_HW_NET_BSD_SOCKET_TEMPLATE_IS_USED__)

/*******************************************************************************
 * local defines
 ******************************************************************************/

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
daverificare
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvSocket(int __domain, int __type, int __protocol) {
    return (long int) socket(__domain, __type, __protocol);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvConnect(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len) {
    return (long int) connect(__fd, __addr, __len);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvBind(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len) {
    return (long int) bind(__fd, __addr, __len);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvListen(int __fd, int __n) {
    return (long int) listen(__fd, __n);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvAccept(int __fd, __SOCKADDR_ARG __addr, socklen_t * __addr_len) {
    return (long int) accept(__fd, __addr, __addr_len);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvSendTo(int __fd, const void *__buf, size_t __n, int __flags, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len) {
    return (long int) sendto(__fd, __buf, __n, __flags, __addr, __addr_len);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvRecvFrom(int __fd, void *__restrict __buf, size_t __n, int __flags, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len) {
    return (long int) recvfrom(__fd, __buf, __n, __flags, __addr, __addr_len);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvSend(int __fd, const void *__buf, size_t __n, int __flags) {
    return (long int) send(__fd, __buf, __n, __flags);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvRecv(int __fd, void *__buf, size_t __n, int __flags) {
    return (long int) recv(__fd, __buf, __n, __flags);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvShutdown(int __fd, int __how) {
    return (long int) shutdown(__fd, __how);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvClose(int __fd) {
    return (long int) close(__fd);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvGetSockOpt(int __fd, int __level, int __optname, void *__restrict __optval, socklen_t *__restrict __optlen) {
    return (long int) getsockopt(__fd, __level, __optname, __optval, __optlen);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvSetSockOpt(int __fd, int __level, int __optname, const void *__optval, socklen_t __optlen) {
    return (long int) setsockopt(__fd, __level, __optname, __optval, __optlen);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvFcntl(int __fd, int __cmd, int __val) {
    return (long int) fcntl(__fd, __cmd, __val);
}

#endif

#endif
