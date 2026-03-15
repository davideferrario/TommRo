
#ifndef TOMMROC_HW_TEMPLATE_NET_BSD_SOCKET_LOW_LEVEL_ENV_ARM_LINUX_H_
#define TOMMROC_HW_TEMPLATE_NET_BSD_SOCKET_LOW_LEVEL_ENV_ARM_LINUX_H_

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

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>

#include <fcntl.h>
#include <unistd.h>

/*******************************************************************************
 * defines
 ******************************************************************************/
#define TOMMROC_HW_TEMPLATE_NET_BSD_SOCKET_LOW_LEVEL_MAX_ACTIVE_CONN    (16)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

long int tommRoCHwTemplateNetBSDSocketLowLevelEnvSocket(int __domain, int __type, int __protocol);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvConnect(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvBind(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvListen(int __fd, int __n);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvAccept(int __fd, __SOCKADDR_ARG __addr, socklen_t * __addr_len);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvSendTo(int __fd, const void *__buf, size_t __n, int __flags, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvRecvFrom(int __fd, void *__restrict __buf, size_t __n, int __flags, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvSend(int __fd, const void *__buf, size_t __n, int __flags);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvRecv(int __fd, void *__buf, size_t __n, int __flags);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvShutdown(int __fd, int __how);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvClose(int __fd);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvGetSockOpt(int __fd, int __level, int __optname, void *__restrict __optval, socklen_t *__restrict __optlen);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvSetSockOpt(int __fd, int __level, int __optname, const void *__optval, socklen_t __optlen);
long int tommRoCHwTemplateNetBSDSocketLowLevelEnvFcntl(int __fd, int __cmd, int __val);

#endif

#endif

#endif
