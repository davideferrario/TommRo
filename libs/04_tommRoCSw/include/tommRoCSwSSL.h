
#ifndef TOMMROC_SW_SSL_H_
#define TOMMROC_SW_SSL_H_

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
#include "tommRoCSwErr.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "mbedtls/net_sockets.h"
#include "mbedtls/pk.h"
#include "mbedtls/ssl.h"
#include "mbedtls/x509_crt.h"
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#define TOMMROC_SW_SSL_CONTEXT_HANDLE_SIZE  (1208)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#define TOMMROC_SW_SSL_CONTEXT_HANDLE_SIZE  (sizeof(tommRoC_sw_ssl_esp32_context_t))
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)
#define TOMMROC_SW_SSL_CONTEXT_HANDLE_SIZE  (2128)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#define TOMMROC_SW_SSL_CONTEXT_HANDLE_SIZE  (2128)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)
#define TOMMROC_SW_SSL_CONTEXT_HANDLE_SIZE  (1496)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
typedef struct {

    mbedtls_net_context mbedtlsNetContext;
    mbedtls_ssl_context mbedtlsSSLContext;
    mbedtls_ssl_config  mbedtlsSSLConfig;
    mbedtls_x509_crt    mbedtlsX509CaChainCrt;
    mbedtls_x509_crt    mbedtlsX509ClientCrt;
    mbedtls_pk_context  mbedtlsPkClientPrivKey;

} tommRoC_sw_ssl_esp32_context_t;
#endif

typedef struct {
    uint8_t data[TOMMROC_SW_SSL_CONTEXT_HANDLE_SIZE];
} tommRoC_sw_ssl_context_t;

#define __EMPTY_tommRoC_sw_ssl_context_t_data_field__           TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_SW_SSL_CONTEXT_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_sw_ssl_context_t__                      \
{                                                               \
    /* .data */ __EMPTY_tommRoC_sw_ssl_context_t_data_field__,  \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Start SSL software framework.
 *
 * return tommRoC_sw_err_enum_t
 */
tommRoC_sw_err_enum_t tommRoCSwSSLStart(void);

/**
 * Stop SSL software framework.
 *
 * return tommRoC_sw_err_enum_t
 */
tommRoC_sw_err_enum_t tommRoCSwSSLStop(void);

#endif
