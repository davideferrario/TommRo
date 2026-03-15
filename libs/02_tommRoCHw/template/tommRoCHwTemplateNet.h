
#ifndef TOMMROC_HW_TEMPLATE_NET_H_
#define TOMMROC_HW_TEMPLATE_NET_H_

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

/**
 *  - BSD Socket:
 *      - __TOMMROC_HW_USE_BSD_SOCKET_COMPLETE_NET_TEMPLATE__               BSD socket complete (both client and server) interface.
 *      - __TOMMROC_HW_USE_BSD_SOCKET_ONLY_CLIENT_NET_TEMPLATE__            BSD socket only client interface.
 *      - __TOMMROC_HW_USE_BSD_SOCKET_ONLY_SERVER_NET_TEMPLATE__            BSD socket only server interface.
 *
 *  - DHCP:
 *      - __TOMMROC_HW_USE_DHCP_NET_TEMPLATE__                              DHCP.
 *
 *  - DNS:
 *      - __TOMMROC_HW_USE_DNS_NET_TEMPLATE__                               DNS.
 *
 *  - SNTP:
 *      - __TOMMROC_HW_USE_SNTP_NET_TEMPLATE__                              SNTP.
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "net/SNTP/tommRoCHwTemplateNetSNTP.h"
#include "net/util/tommRoCHwTemplateNetUtil.h"

#include "TOMMROCHw.h"

/********************  BSD Socket Net Os template */
#if defined (__TOMMROC_HW_USE_BSD_SOCKET_COMPLETE_NET_TEMPLATE__)
#if defined (__TOMMROC_HW_NET_BSD_SOCKET_TEMPLATE_IS_USED__)
#error "tommRoC Net BSD socket template multiple definition"
#else
#define __TOMMROC_HW_NET_BSD_SOCKET_TEMPLATE_IS_USED__
#endif
#endif

#if defined (__TOMMROC_HW_USE_BSD_SOCKET_ONLY_CLIENT_NET_TEMPLATE__)
#if defined (__TOMMROC_HW_NET_BSD_SOCKET_TEMPLATE_IS_USED__)
#error "tommRoC Net BSD socket template multiple definition"
#else
#define __TOMMROC_HW_NET_BSD_SOCKET_TEMPLATE_IS_USED__
#endif
#endif

#if defined (__TOMMROC_HW_USE_BSD_SOCKET_ONLY_SERVER_NET_TEMPLATE__)
#if defined (__TOMMROC_HW_NET_BSD_SOCKET_TEMPLATE_IS_USED__)
#error "tommRoC Net BSD socket template multiple definition"
#else
#define __TOMMROC_HW_NET_BSD_SOCKET_TEMPLATE_IS_USED__
#endif
#endif

#if defined (__TOMMROC_HW_NET_BSD_SOCKET_TEMPLATE_IS_USED__)
#include "net/BSDSocket/tommRoCHwTemplateNetBSDSocket.h"
#endif


/*******************************************************************************
 * defines
 ******************************************************************************/
#if defined (__TOMMROC_HW_NET_BSD_SOCKET_TEMPLATE_IS_USED__)    ||  \
    defined (__TOMMROC_HW_USE_DHCP_NET_TEMPLATE__)              ||  \
    defined (__TOMMROC_HW_USE_DNS_NET_TEMPLATE__)               ||  \
    defined (__TOMMROC_HW_USE_SNTP_NET_TEMPLATE__)
#define __TOMMROC_HW_NET_TEMPLATE_IS_USED__
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateNetStart(void);
tommRoC_hw_err_enum_t tommRoCHwTemplateNetStop(void);

#endif
