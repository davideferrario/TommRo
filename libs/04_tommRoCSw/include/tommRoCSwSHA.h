
#ifndef TOMMROC_SW_SHA_H_
#define TOMMROC_SW_SHA_H_

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
#include "mbedtls/sha1.h"
#include "mbedtls/sha256.h"
#include "mbedtls/sha512.h"
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#define TOMMROC_SW_SHA_SHA1_CONTEXT_HANDLE_SIZE     (sizeof(mbedtls_sha1_context))
#define TOMMROC_SW_SHA_SHA224_CONTEXT_HANDLE_SIZE   (sizeof(mbedtls_sha256_context))
#define TOMMROC_SW_SHA_SHA256_CONTEXT_HANDLE_SIZE   (sizeof(mbedtls_sha256_context))
#define TOMMROC_SW_SHA_SHA384_CONTEXT_HANDLE_SIZE   (sizeof(mbedtls_sha512_context))
#define TOMMROC_SW_SHA_SHA512_CONTEXT_HANDLE_SIZE   (sizeof(mbedtls_sha512_context))
#else
#if defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_8_BIT_SIZE)
#define TOMMROC_SW_SHA_SHA1_CONTEXT_HANDLE_SIZE     ()
#define TOMMROC_SW_SHA_SHA224_CONTEXT_HANDLE_SIZE   ()
#define TOMMROC_SW_SHA_SHA256_CONTEXT_HANDLE_SIZE   ()
#define TOMMROC_SW_SHA_SHA384_CONTEXT_HANDLE_SIZE   ()
#define TOMMROC_SW_SHA_SHA512_CONTEXT_HANDLE_SIZE   ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMROC_SW_SHA_SHA1_CONTEXT_HANDLE_SIZE     ()
#define TOMMROC_SW_SHA_SHA224_CONTEXT_HANDLE_SIZE   ()
#define TOMMROC_SW_SHA_SHA256_CONTEXT_HANDLE_SIZE   ()
#define TOMMROC_SW_SHA_SHA384_CONTEXT_HANDLE_SIZE   ()
#define TOMMROC_SW_SHA_SHA512_CONTEXT_HANDLE_SIZE   ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE)
#define TOMMROC_SW_SHA_SHA1_CONTEXT_HANDLE_SIZE     (92)
#define TOMMROC_SW_SHA_SHA224_CONTEXT_HANDLE_SIZE   (108)
#define TOMMROC_SW_SHA_SHA256_CONTEXT_HANDLE_SIZE   (108)
#define TOMMROC_SW_SHA_SHA384_CONTEXT_HANDLE_SIZE   (216)
#define TOMMROC_SW_SHA_SHA512_CONTEXT_HANDLE_SIZE   (216)
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMROC_SW_SHA_SHA1_CONTEXT_HANDLE_SIZE     (92)
#define TOMMROC_SW_SHA_SHA224_CONTEXT_HANDLE_SIZE   (108)
#define TOMMROC_SW_SHA_SHA256_CONTEXT_HANDLE_SIZE   (108)
#define TOMMROC_SW_SHA_SHA384_CONTEXT_HANDLE_SIZE   (216)
#define TOMMROC_SW_SHA_SHA512_CONTEXT_HANDLE_SIZE   (216)
#endif
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// SHA1 context
typedef struct {
    uint8_t data[TOMMROC_SW_SHA_SHA1_CONTEXT_HANDLE_SIZE];
} tommRoC_sw_sha_sha1_context_t;

#define __EMPTY_tommRoC_sw_sha_sha1_context_t_data_field__              TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_SW_SHA_SHA1_CONTEXT_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_sw_sha_sha1_context_t__                         \
{                                                                       \
    /* .data */ __EMPTY_tommRoC_sw_sha_sha1_context_t_data_field__,     \
}


// SHA224 context
typedef struct {
    uint8_t data[TOMMROC_SW_SHA_SHA224_CONTEXT_HANDLE_SIZE];
} tommRoC_sw_sha_sha224_context_t;

#define __EMPTY_tommRoC_sw_sha_sha224_context_t_data_field__            TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_SW_SHA_SHA224_CONTEXT_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_sw_sha_sha224_context_t__                       \
{                                                                       \
    /* .data */ __EMPTY_tommRoC_sw_sha_sha224_context_t_data_field__,   \
}


// SHA256 context
typedef struct {
    uint8_t data[TOMMROC_SW_SHA_SHA256_CONTEXT_HANDLE_SIZE];
} tommRoC_sw_sha_sha256_context_t;

#define __EMPTY_tommRoC_sw_sha_sha256_context_t_data_field__            TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_SW_SHA_SHA256_CONTEXT_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_sw_sha_sha256_context_t__                       \
{                                                                       \
    /* .data */ __EMPTY_tommRoC_sw_sha_sha256_context_t_data_field__,   \
}


// SHA384 context
typedef struct {
    uint8_t data[TOMMROC_SW_SHA_SHA384_CONTEXT_HANDLE_SIZE];
} tommRoC_sw_sha_sha384_context_t;

#define __EMPTY_tommRoC_sw_sha_sha384_context_t_data_field__            TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_SW_SHA_SHA384_CONTEXT_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_sw_sha_sha384_context_t__                       \
{                                                                       \
    /* .data */ __EMPTY_tommRoC_sw_sha_sha384_context_t_data_field__,   \
}


// SHA512 context
typedef struct {
    uint8_t data[TOMMROC_SW_SHA_SHA512_CONTEXT_HANDLE_SIZE];
} tommRoC_sw_sha_sha512_context_t;

#define __EMPTY_tommRoC_sw_sha_sha512_context_t_data_field__            TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_SW_SHA_SHA512_CONTEXT_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_sw_sha_sha512_context_t__                       \
{                                                                       \
    /* .data */ __EMPTY_tommRoC_sw_sha_sha512_context_t_data_field__,   \
}


/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Start SHA software framework.
 * NOTE: tommRoC library SHA environment will be init to use tommRoCSw software SHA functions.
 *
 * return tommRoC_sw_err_enum_t
 */
tommRoC_sw_err_enum_t tommRoCSwSHA1Start(void);
tommRoC_sw_err_enum_t tommRoCSwSHA224Start(void);
tommRoC_sw_err_enum_t tommRoCSwSHA256Start(void);
tommRoC_sw_err_enum_t tommRoCSwSHA384Start(void);
tommRoC_sw_err_enum_t tommRoCSwSHA512Start(void);

/**
 * Stop SHA software framework.
 *
 * return tommRoC_sw_err_enum_t
 */
tommRoC_sw_err_enum_t tommRoCSwSHA1Stop(void);
tommRoC_sw_err_enum_t tommRoCSwSHA224Stop(void);
tommRoC_sw_err_enum_t tommRoCSwSHA256Stop(void);
tommRoC_sw_err_enum_t tommRoCSwSHA384Stop(void);
tommRoC_sw_err_enum_t tommRoCSwSHA512Stop(void);
 
#endif
