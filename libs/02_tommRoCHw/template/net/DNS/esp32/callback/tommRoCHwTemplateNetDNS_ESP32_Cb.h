
#ifndef TOMMROC_HW_TEMPLATE_NET_DNS__ESP32__CB_H_
#define TOMMROC_HW_TEMPLATE_NET_DNS__ESP32__CB_H_

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
#if defined (__TOMMROC_HW_USE_DNS_NET_TEMPLATE__)
#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "lwip/dns.h"

#include <stdbool.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef struct {

    bool        validHostIP;
    ip_addr_t*  hostIPAddPtr;
    bool        hasBeenCalled;

} tommRoC_hw_template_net_dns__esp32__cb_found_cb_arg_t;

#define __EMPTY_tommRoC_hw_template_net_dns__esp32__cb_found_cb_arg_t__ \
{                                                                       \
    /* .validHostIP */      false,                                      \
    /* .hostIPAddPtr */     NULL,                                       \
    /* .hasBeenCalled */    false,                                      \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

void tommRoCHwTemplateNetDNS_ESP32_CbFoundCb(const char *name, const ip_addr_t *ipaddr, void *callback_arg);

#endif

#endif

#endif
