
#ifndef TOMMROC_SW_TEMPLATE_SSL_ESP32_WRAPPER_CORE_ALT_NET_SOCKETS_H_
#define TOMMROC_SW_TEMPLATE_SSL_ESP32_WRAPPER_CORE_ALT_NET_SOCKETS_H_

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
#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "mbedtls/ssl.h"
#include "mbedtls/net_sockets.h"

#include <stddef.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

int tommRoCSwTemplateSSLESP32WrapperCoreAltNetSocketsNetConnect(mbedtls_net_context *ctx, const char *host, const char *port, int proto);
int tommRoCSwTemplateSSLESP32WrapperCoreAltNetSocketsNetSend(void *ctx, const unsigned char *buf, size_t len);
int tommRoCSwTemplateSSLESP32WrapperCoreAltNetSocketsNetRecv(void *ctx, unsigned char *buf, size_t len);
int tommRoCSwTemplateSSLESP32WrapperCoreAltNetSocketsNetRecvTimeout(void *ctx, unsigned char *buf, size_t len, uint32_t timeout);

#endif

#endif
