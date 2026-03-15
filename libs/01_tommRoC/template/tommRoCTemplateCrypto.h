
#ifndef TOMMROC_TEMPLATE_CRYPTO_H_
#define TOMMROC_TEMPLATE_CRYPTO_H_

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
 *  - AES:
 *      - __TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__       hardware AES CBC
 *      - __TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__       hardware AES ECB
 *  - DES:
 *      - __TOMMROC_USE_CRYPTO_DES_CBC_TEMPLATE__       hardware DES CBC
 *      - __TOMMROC_USE_CRYPTO_DES_ECB_TEMPLATE__       hardware DES ECB
 *  - DES3:
 *      - __TOMMROC_USE_CRYPTO_DES3_CBC_TEMPLATE__      hardware DES3 CBC
 *      - __TOMMROC_USE_CRYPTO_DES3_ECB_TEMPLATE__      hardware DES3 ECB
 *  - RND:
 *      - __TOMMROC_USE_CRYPTO_RND_TEMPLATE__           hardware random
 *      - __TOMMROC_USE_CRYPTO_PRNG_AS_RND_TEMPLATE__   TommRoC software PRNG as random
 *  - SHA:
 *      - __TOMMROC_USE_CRYPTO_SHA1_TEMPLATE__          hardware SHA1
 *      - __TOMMROC_USE_CRYPTO_SHA224_TEMPLATE__        hardware SHA224
 *      - __TOMMROC_USE_CRYPTO_SHA256_TEMPLATE__        hardware SHA256
 *      - __TOMMROC_USE_CRYPTO_SHA384_TEMPLATE__        hardware SHA384
 *      - __TOMMROC_USE_CRYPTO_SHA512_TEMPLATE__        hardware SHA512
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"

/******************** Crypto AES template */
#if defined (__TOMMROC_USE_CRYPTO_AES_CBC_TEMPLATE__)
#define __TOMMROC_CRYPTO_TEMPLATE_IS_USED__
#elif defined (__TOMMROC_USE_CRYPTO_AES_ECB_TEMPLATE__)
#define __TOMMROC_CRYPTO_TEMPLATE_IS_USED__

/******************** Crypto DES template */
#elif defined (__TOMMROC_USE_CRYPTO_DES_CBC_TEMPLATE__)
#define __TOMMROC_CRYPTO_TEMPLATE_IS_USED__
#elif defined (__TOMMROC_USE_CRYPTO_DES_ECB_TEMPLATE__)
#define __TOMMROC_CRYPTO_TEMPLATE_IS_USED__

/******************** Crypto DES3 template */
#elif defined (__TOMMROC_USE_CRYPTO_DES3_CBC_TEMPLATE__)
#define __TOMMROC_CRYPTO_TEMPLATE_IS_USED__
#elif defined (__TOMMROC_USE_CRYPTO_DES3_ECB_TEMPLATE__)
#define __TOMMROC_CRYPTO_TEMPLATE_IS_USED__

/******************** Crypto RND template */
#elif defined (__TOMMROC_USE_CRYPTO_RND_TEMPLATE__)
#define __TOMMROC_CRYPTO_TEMPLATE_IS_USED__
#elif defined (__TOMMROC_USE_CRYPTO_PRNG_AS_RND_TEMPLATE__)
#define __TOMMROC_CRYPTO_TEMPLATE_IS_USED__

/******************** Crypto SHA template */
#elif defined (__TOMMROC_USE_CRYPTO_SHA1_TEMPLATE__)
#define __TOMMROC_CRYPTO_TEMPLATE_IS_USED__
#elif defined (__TOMMROC_USE_CRYPTO_SHA224_TEMPLATE__)
#define __TOMMROC_CRYPTO_TEMPLATE_IS_USED__
#elif defined (__TOMMROC_USE_CRYPTO_SHA256_TEMPLATE__)
#define __TOMMROC_CRYPTO_TEMPLATE_IS_USED__
#elif defined (__TOMMROC_USE_CRYPTO_SHA384_TEMPLATE__)
#define __TOMMROC_CRYPTO_TEMPLATE_IS_USED__
#elif defined (__TOMMROC_USE_CRYPTO_SHA512_TEMPLATE__)
#define __TOMMROC_CRYPTO_TEMPLATE_IS_USED__
#endif

/******************** Check template deprecated error */
#if defined (__TOMMROC_USE_CRYPTO_AES_TEMPLATE__)
#error "__TOMMROC_USE_CRYPTO_AES_TEMPLATE__ is deprecated"
#endif

/******************** Check template config error */
#if defined (__TOMMROC_USE_CRYPTO_RND_TEMPLATE__) && defined (__TOMMROC_USE_CRYPTO_PRNG_AS_RND_TEMPLATE__)
#error "Double tommRoC RND Crypto template used"
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateCryptoStart(void);
tommRoC_err_enum_t tommRoCTemplateCryptoStop(void);

#endif
