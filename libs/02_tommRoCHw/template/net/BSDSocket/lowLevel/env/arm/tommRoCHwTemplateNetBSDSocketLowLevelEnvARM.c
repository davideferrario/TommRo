
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateNetBSDSocketLowLevelEnvARM.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

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

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvSocket(int domain, int type, int protocol) {
    return (long int) lwip_socket(domain, type, protocol);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvConnect(int s, const struct sockaddr *name, socklen_t namelen) {
    return (long int) lwip_connect(s, name, namelen);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvBind(int s, const struct sockaddr *name, socklen_t namelen) {
    return (long int) lwip_bind(s, name, namelen);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvListen(int s, int backlog) {
    return (long int) lwip_listen(s, backlog);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvAccept(int s, struct sockaddr *addr, socklen_t *addrlen) {
    return (long int) lwip_accept(s, addr, addrlen);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvSendTo(int s, const void *data, size_t size, int flags, const struct sockaddr *to, socklen_t tolen) {
    return (long int) lwip_sendto(s, data, size, flags, to, tolen);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvRecvFrom(int s, void *mem, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen) {
    return (long int) lwip_recvfrom(s, mem, len, flags, from, fromlen);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvSend(int s, const void *data, size_t size, int flags) {
    return (long int) lwip_send(s, data, size, flags);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvRecv(int s, void *mem, size_t len, int flags) {
    return (long int) lwip_recv(s, mem, len, flags);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvShutdown(int s, int how) {
    return (long int) lwip_shutdown(s, how);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvClose(int s) {
    return (long int) lwip_close(s);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvGetSockOpt(int s, int level, int optname, void *optval, socklen_t *optlen) {
    return (long int) lwip_getsockopt(s, level, optname, optval, optlen);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvSetSockOpt(int s, int level, int optname, const void *optval, socklen_t optlen) {
    return (long int) lwip_setsockopt(s, level, optname, optval, optlen);
}

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvFcntl(int s, int cmd, int val) {
    return (long int) lwip_fcntl(s, cmd, val);
}

#endif

#endif
