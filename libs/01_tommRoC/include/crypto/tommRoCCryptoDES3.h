
#ifndef TOMMROC_CRYPTO_DES3_H_
#define TOMMROC_CRYPTO_DES3_H_

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
 * @defgroup tommRoCCryptoDES3 tommRoCCryptoDES3
 *
 * @brief  TommRoC library crypto DES3 module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted crypto DES3 functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCUnitMeasure.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

#define TOMMRO_C_CRYPTO_DES3_KEY_SIZE_BIT       (64 * 2)                                                                // Crypto DES3 key size [bit].
#define TOMMRO_C_CRYPTO_DES3_KEY_SIZE_BYTE      (TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(TOMMRO_C_CRYPTO_DES3_KEY_SIZE_BIT))   // Crypto DES3 key size [byte].

#define TOMMROC_CRYPTO_DES3_BLOCK_SIZE_BYTE     (8)
#define TOMMROC_CRYPTO_DES3_CBC_IV_SIZE_BYTE    (TOMMROC_CRYPTO_DES3_BLOCK_SIZE_BYTE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC crypto DES3 properties enumeration.
typedef enum {

    /**
     * DES3 environment guard.
     * This have to be used for simultaneous access on DES3 hardware and/or if
     * simultaneous access is not supported by software level.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_guard_t*.
     */
    TOMMRO_C_CRYPTO_DES3_GUARD_PROP = 0,

    /**
     * DES3 cbc/ecb environment is init.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_DES3_CBC_IS_INIT_PROP,
    TOMMRO_C_CRYPTO_DES3_ECB_IS_INIT_PROP,

    /**
     * DES3 cbc is IV updated.
     * NOTE: if true, the content of the IV is updated so that is possible to call the
     *       same function again on the following block(s) of data and get the same
     *       result as if it was encrypted in one call.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_DES3_CBC_IS_IV_UPDATED_PROP,

} tommRoC_crypto_des3_prop_enum_t;


/**
 * DES3-CBC encryption/decryption function type.
 */
typedef tommRoC_err_enum_t (*tommRoC_crypto_des3_cbc_encrypt_funct_t)(
        const   uint8_t*                            const   des3KeyPtr,
                uint8_t*                            const   des3IVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr);

typedef tommRoC_err_enum_t (*tommRoC_crypto_des3_cbc_decrypt_funct_t)(
        const   uint8_t*                            const   des3KeyPtr,
                uint8_t*                            const   des3IVPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr);


/**
 * DES3-ECB encryption/decryption function type.
 */
typedef tommRoC_err_enum_t (*tommRoC_crypto_des3_ecb_encrypt_funct_t)(
        const   uint8_t*                            const   des3KeyPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr);

typedef tommRoC_err_enum_t (*tommRoC_crypto_des3_ecb_decrypt_funct_t)(
        const   uint8_t*                            const   des3KeyPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
                uint8_t*                            const   outputBufferPtr);


/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* DES3 environment init functs */

/**
 * DES3 environment init.
 * NOTE: after init environment, next step is to set supported key size properties.
 *
 * param[in]        des3Encrypt             DES3 encrypt function.
 * param[in]        des3Decrypt             DES3 decrypt function.
 * param[in]        isIVUpdated             is the content of IV updated, to allow a "streaming" usage.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoDES3_CBC_InitEnv(
        const   tommRoC_crypto_des3_cbc_encrypt_funct_t     des3Encrypt,
        const   tommRoC_crypto_des3_cbc_decrypt_funct_t     des3Decrypt,
        const   bool                                        isIVUpdated);

tommRoC_err_enum_t tommRoCCryptoDES3_ECB_InitEnv(
        const   tommRoC_crypto_des3_ecb_encrypt_funct_t     des3Encrypt,
        const   tommRoC_crypto_des3_ecb_decrypt_funct_t     des3Decrypt);


/******************* DES3 environment close functs */

/**
 * DES3 environment close.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoDES3_CBC_CloseEnv(void);
tommRoC_err_enum_t tommRoCCryptoDES3_ECB_CloseEnv(void);


/******************* DES3 environment get/set properties functs */

/**
 * Get crypto DES3 property.
 *
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoDES3GetProp(
        const   tommRoC_crypto_des3_prop_enum_t         property,
                void*                           const   propValuePtr);

/**
 * Set crypto DES3 property.
 *
 * param[in]        property                property.
 * param[in]        propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoDES3SetProp(
        const   tommRoC_crypto_des3_prop_enum_t         property,
        const   void*                           const   propValuePtr);


/******************* DES3 CBC encryption/decryption functs */

/**
 * DES3-CBC data encryption.
 * NOTE: Input and output data length have to be multiple of the block size (16 bytes).
 *
 * param[in]        des3KeyPtr              DES3 key.
 * param[in]        des3IVPtr               DES3 CBC initialization vector pointer .
 * param[in]        des3IVLen               DES3 CBC initialization vector len [byte]. Have to be equal to the block size (TOMMROC_CRYPTO_DES3_BLOCK_SIZE_BYTE bytes).
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer len [byte]. Have to be multiple of the block size (16 bytes).
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer ptr [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoDES3_CBC_Encrypt(
        const   uint8_t*                            const   des3KeyPtr,
                uint8_t*                            const   des3IVPtr,
        const   uint8_t                                     des3IVLen,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
        const   uint16_t                                    outputBufferMaxSize,
                uint8_t*                            const   outputBufferPtr);

/**
 * DES3-CBC data decryption.
 * NOTE: Input and output data length have to be multiple of the block size (16 bytes).
 *
 * param[in]        des3KeyPtr              DES3 key.
 * param[in]        des3IVPtr               DES3 CBC initialization vector pointer.
 * param[in]        des3IVLen               DES3 CBC initialization vector len [byte]. Have to be equal to the block size (16 bytes).
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer len [byte]. Have to be multiple of the block size (16 bytes).
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer ptr [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoDES3_CBC_Decrypt(
        const   uint8_t*                            const   des3KeyPtr,
                uint8_t*                            const   des3IVPtr,
        const   uint8_t                                     des3IVLen,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
        const   uint16_t                                    outputBufferMaxSize,
                uint8_t*                            const   outputBufferPtr);


/******************* DES3 ECB encryption/decryption functs */

/**
 * DES3-ECB data encryption.
 * NOTE: Input and output data length have to be multiple of the block size (16 bytes).
 *
 * param[in]        des3KeyPtr              DES3 key.
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer len [byte]. Have to be multiple of the block size (16 bytes).
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer ptr [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoDES3_ECB_Encrypt(
        const   uint8_t*                            const   des3KeyPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
        const   uint16_t                                    outputBufferMaxSize,
                uint8_t*                            const   outputBufferPtr);

/**
 * DES3-ECB data decryption.
 * NOTE: Input and output data length have to be multiple of the block size (16 bytes).
 *
 * param[in]        des3KeyPtr              DES3 key.
 * param[in]        inputBufferPtr          input data buffer pointer.
 * param[in]        inputBufferLen          input data buffer len [byte]. Have to be multiple of the block size (16 bytes).
 * param[in]        outputBufferMaxSize     output data buffer max size [byte].
 * param[out]       outputBufferPtr         output data buffer ptr [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoDES3_ECB_Decrypt(
        const   uint8_t*                            const   des3KeyPtr,
        const   uint8_t*                            const   inputBufferPtr,
        const   uint16_t                                    inputBufferLen,
        const   uint16_t                                    outputBufferMaxSize,
                uint8_t*                            const   outputBufferPtr);

/**
 * @}
 */

#endif
