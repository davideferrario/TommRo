
#ifndef TOMMROC_HW_TEMPLATE_NET_BSD_SOCKET_LOW_LEVEL_ENV_ARM_H_
#define TOMMROC_HW_TEMPLATE_NET_BSD_SOCKET_LOW_LEVEL_ENV_ARM_H_

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
#include "tommRoCHwTemplateNet.h"

#if defined (__TOMMROC_HW_NET_BSD_SOCKET_TEMPLATE_IS_USED__)

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#include "lwip/sockets.h"

/*******************************************************************************
 * defines
 ******************************************************************************/
#define TOMMROC_HW_TEMPLATE_NET_BSD_SOCKET_LOW_LEVEL_MAX_ACTIVE_CONN    (MEMP_NUM_NETCONN)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvSocket(int domain, int type, int protocol);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvConnect(int s, const struct sockaddr *name, socklen_t namelen);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvBind(int s, const struct sockaddr *name, socklen_t namelen);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvListen(int s, int backlog);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvAccept(int s, struct sockaddr *addr, socklen_t *addrlen);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvSendTo(int s, const void *data, size_t size, int flags, const struct sockaddr *to, socklen_t tolen);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvRecvFrom(int s, void *mem, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvSend(int s, const void *data, size_t size, int flags);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvRecv(int s, void *mem, size_t len, int flags);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvShutdown(int s, int how);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvClose(int s);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvGetSockOpt(int s, int level, int optname, void *optval, socklen_t *optlen);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvSetSockOpt(int s, int level, int optname, const void *optval, socklen_t optlen);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvFcntl(int s, int cmd, int val);

#endif

#endif

#endif
