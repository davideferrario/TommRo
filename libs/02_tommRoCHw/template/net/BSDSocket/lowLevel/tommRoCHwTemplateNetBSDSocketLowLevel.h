
#ifndef TOMMROC_HW_TEMPLATE_NET_BSD_SOCKET_LOW_LEVEL_H_
#define TOMMROC_HW_TEMPLATE_NET_BSD_SOCKET_LOW_LEVEL_H_

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

#include "net/BSDSocket/lowLevel/env/tommRoCHwTemplateNetBSDSocketLowLevelEnv.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

long int tommRoCHwTemplateNetBSDSocketLowLevelSocket(int domain, int type, int protocol);
long int tommRoCHwTemplateNetBSDSocketLowLevelConnect(int socket, const void* addr, int len);
long int tommRoCHwTemplateNetBSDSocketLowLevelBind(int socket, const void* addr, int len);
long int tommRoCHwTemplateNetBSDSocketLowLevelListen(int socket, int backlog);
long int tommRoCHwTemplateNetBSDSocketLowLevelAccept(int socket, void* addr, void* len);
long int tommRoCHwTemplateNetBSDSocketLowLevelSendTo(int socket, const void* data, int size, int flags, const void* to, int tolen);
long int tommRoCHwTemplateNetBSDSocketLowLevelRecvFrom(int socket, void* mem, int len, int flags, void* from, void* fromlen);
long int tommRoCHwTemplateNetBSDSocketLowLevelSend(int socket, const void* data, int size, int flags);
long int tommRoCHwTemplateNetBSDSocketLowLevelRecv(int socket, void* mem, int len, int flags);
long int tommRoCHwTemplateNetBSDSocketLowLevelShutdown(int socket, int how);
long int tommRoCHwTemplateNetBSDSocketLowLevelClose(int socket);
long int tommRoCHwTemplateNetBSDSocketLowLevelGetSockOpt(int socket, int level, int optname, void* optval, void* optlen);
long int tommRoCHwTemplateNetBSDSocketLowLevelSetSockOpt(int socket, int level, int optname, const void* optval, int optlen);
long int tommRoCHwTemplateNetBSDSocketLowLevelFcntl(int socket, int cmd, int val);

#endif

#endif
