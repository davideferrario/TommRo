
#ifndef TOMMROC_CRYPTO_MD_H_
#define TOMMROC_CRYPTO_MD_H_

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
 * @defgroup tommRoCCryptoMD tommRoCCryptoMD
 *
 * @brief  TommRoC library crypto MD module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted crypto MD functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCUnitMeasure.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/
#define TOMMROC_CRYPTO_MD2_RESULT_SIZE_BYTE     (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(128))
#define TOMMROC_CRYPTO_MD4_RESULT_SIZE_BYTE     (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(128))
#define TOMMROC_CRYPTO_MD5_RESULT_SIZE_BYTE     (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(128))

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC crypto MD properties enumeration.
typedef enum {

    /**
     * MD environment guard.
     * This have to be used for simultaneous access on MD hardware and/or if
     * simultaneous access is not supported by software level.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_guard_t*.
     */
    TOMMRO_C_CRYPTO_MD_GUARD_PROP = 0,

    /**
     * MD2/MD4/MD5 environment is init.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_MD2_IS_INIT_PROP,
    TOMMRO_C_CRYPTO_MD4_IS_INIT_PROP,
    TOMMRO_C_CRYPTO_MD5_IS_INIT_PROP,

} tommRoC_crypto_md_prop_enum_t;


// MD function type.
typedef tommRoC_err_enum_t (*tommRoC_crypto_md_funct_t)(
        const   void*       const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                void*       const   outputBufferPtr);

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* MD environment init functs */

/**
 * MD2/MD4/MD5 environment init.
 *
 * param[in]        md                      MD2/MD4/MD5 function.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoMD2InitEnv(const tommRoC_crypto_md_funct_t md);
tommRoC_err_enum_t tommRoCCryptoMD4InitEnv(const tommRoC_crypto_md_funct_t md);
tommRoC_err_enum_t tommRoCCryptoMD5InitEnv(const tommRoC_crypto_md_funct_t md);


/******************* MD environment close functs */

/**
 * MD2/MD4/MD5 environment close.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoMD2CloseEnv(void);
tommRoC_err_enum_t tommRoCCryptoMD4CloseEnv(void);
tommRoC_err_enum_t tommRoCCryptoMD5CloseEnv(void);


/******************* MD environment get/set properties functs */

/**
 * Get MD2/MD4/MD5 property.
 *
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoMDGetProp(
        const   tommRoC_crypto_md_prop_enum_t           property,
                void*                           const   propValuePtr);

/**
 * Set MD2/MD4/MD5 property.
 *
 * param[in]        property                property.
 * param[in]        propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoMDSetProp(
        const   tommRoC_crypto_md_prop_enum_t           property,
        const   void*                           const   propValuePtr);


/******************* MD environment functs */

/**
 * MD2/MD4/MD5.
 * NOTE: Output data length have to be equal/greater than:
 *          - TOMMROC_CRYPTO_MD2_RESULT_SIZE_BYTE (16) bytes.
 *          - TOMMROC_CRYPTO_MD4_RESULT_SIZE_BYTE (16) bytes.
 *          - TOMMROC_CRYPTO_MD5_RESULT_SIZE_BYTE (16) bytes.
 *
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer len [byte].
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer ptr.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoMD2(
        const   void*       const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
        const   uint16_t            outputBufferMaxSize,
                void*       const   outputBufferPtr);
tommRoC_err_enum_t tommRoCCryptoMD4(
        const   void*       const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
        const   uint16_t            outputBufferMaxSize,
                void*       const   outputBufferPtr);
tommRoC_err_enum_t tommRoCCryptoMD5(
        const   void*       const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
        const   uint16_t            outputBufferMaxSize,
                void*       const   outputBufferPtr);

/**
 * @}
 */

#endif
