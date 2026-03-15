
#ifndef TOMMROC_CRYPTO_ECDH_H_
#define TOMMROC_CRYPTO_ECDH_H_

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
 * @defgroup tommRoCCryptoECDH tommRoCCryptoECDH
 *
 * @brief  TommRoC library crypto ECDH module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted crypto Elliptic Curve Diffie-Hellman (ECDH) functionality.
 *
 * ECDH is an anonymous key agreement protocol allowing two parties to establish a shared secret over an insecure channel.
 * Each party must have an elliptic-curve public-private key pair.
 *
 * For more information, see:
 * NIST SP 800-56A Rev. 2 - Recommendation for Pair-Wise Key Establishment Schemes Using Discrete Logarithm Cryptography.
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC crypto ECDH domain parameters (curve, subgroup and generator) identifiers enumeration.
typedef enum {
    
    TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_SECP192R1 = 0,    // 192-bits NIST curve
    TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_SECP224R1,        // 224-bits NIST curve
    TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_SECP256R1,        // 256-bits NIST curve
    TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_SECP384R1,        // 384-bits NIST curve
    TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_SECP521R1,        // 521-bits NIST curve
    TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_BP256R1,          // 256-bits Brainpool curve
    TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_BP384R1,          // 384-bits Brainpool curve
    TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_BP512R1,          // 512-bits Brainpool curve
    TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_CURVE25519,       // Curve25519
    TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_SECP192K1,        // 192-bits "Koblitz" curve
    TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_SECP224K1,        // 224-bits "Koblitz" curve
    TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_SECP256K1,        // 256-bits "Koblitz" curve
	TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_CURVE448,			// Curve448
    
} tommRoC_crypto_ecdh_ecp_group_id_enum_t;


// tommRoC crypto ECDH properties enumeration.
typedef enum {

    /**
     * ECDH environment guard.
     * This have to be used for simultaneous access on ECDH hardware and/or if
     * simultaneous access is not supported by software level.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_guard_t*.
     */
    TOMMRO_C_CRYPTO_ECDH_GUARD_PROP = 0,

    /**
     * ECDH environment is init.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be bool*.
     */
    TOMMRO_C_CRYPTO_ECDH_IS_INIT_PROP,

} tommRoC_crypto_ecdh_prop_enum_t;


/**
 * ECDH generation of a keypair on an elliptic curve function type.
 */
typedef tommRoC_err_enum_t (*tommRoC_crypto_ecdh_gen_keypair_funct_t)(
        const   tommRoC_crypto_ecdh_ecp_group_id_enum_t         ecpGroupId,
                uint8_t*                                const   privateKeyPtr,
        const   uint16_t                                        privateKeySize,
                uint8_t*                                const   publicKeyPtr,
        const   uint16_t                                        publicKeyMaxSize,
                uint16_t*                               const   publicKeyLenPtr);

/**
 * ECDH compute shared secret function type.
 */
typedef tommRoC_err_enum_t (*tommRoC_crypto_ecdh_compute_shared_funct_t)(
        const   tommRoC_crypto_ecdh_ecp_group_id_enum_t         ecpGroupId,
        const   uint8_t*                                const   privateKeyPtr,
        const   uint16_t                                        privateKeySize,
        const   uint8_t*                                const   publicKeyPtr,
        const   uint16_t                                        publicKeySize,
                uint8_t*                                const   sharedPtr,
        const   uint16_t                                        sharedSize);

/**
 * ECDH ECP group is available function type.
 */
typedef bool (*tommRoC_crypto_ecdh_is_ecp_group_available_funct_t)(
        const   tommRoC_crypto_ecdh_ecp_group_id_enum_t         ecpGroupId);


/**
 * ECDH environment init struct.
 */
typedef struct {

    tommRoC_crypto_ecdh_gen_keypair_funct_t             genKeypair;
    tommRoC_crypto_ecdh_compute_shared_funct_t          computeShared;
    tommRoC_crypto_ecdh_is_ecp_group_available_funct_t  isEcpGroupAvailable;

} tommRoC_crypto_ecdh_environment_config_t;

#define __EMPTY_tommRoC_crypto_ecdh_environment_config_t__  \
{                                                           \
    /* .genKeyPair */           NULL,                       \
    /* .computeShared */        NULL,                       \
    /* .isEcpGroupAvailable */  NULL,                       \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* ECDH environment init functs */

/**
 * ECDH environment init.
 *
 * param[in]        ecdhEnvConfigPtr        ECDH environment configuration.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoECDHInitEnv(
        const   tommRoC_crypto_ecdh_environment_config_t*   const   ecdhEnvConfigPtr);


/******************* ECDH environment close functs */

/**
 * ECDH environment close.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoECDHCloseEnv(void);


/******************* ECDH environment get/set properties functs */

/**
 * Get crypto ECDH property.
 *
 * param[in]        property                property.
 * param[out]       propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoECDHGetProp(
        const   tommRoC_crypto_ecdh_prop_enum_t         property,
                void*                           const   propValuePtr);

/**
 * Set crypto ECDH property.
 *
 * param[in]        property                property.
 * param[in]        propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoECDHSetProp(
        const   tommRoC_crypto_ecdh_prop_enum_t         property,
        const   void*                           const   propValuePtr);


/**
 * Get ECDH ECP group is available.
 *
 * param[in]        ecpGroupID              ECP group ID.
 * param[out]       isAvailablePtr          is available pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoECDHIsECPGroupAvailable(
        const   tommRoC_crypto_ecdh_ecp_group_id_enum_t         ecpGroupID,
                bool*                                   const   isAvailablePtr);


/******************* ECDH environment functs */

/**
 * ECDH keypair generation on an elliptic curve function.
 * NOTE: keys are exported as uint8_t data buffer (big endian).
 *
 * param[in]        ecpGroupId              ECDH domain parameters (curve, subgroup and generator) ID.
 * param[out]       privateKeyPtr           private key buffer pointer.
 * param[in]        privateKeyMaxSize       private key buffer max. size [byte].
 * param[out]       privateKeyLenPtr        output private key length pointer [byte].
 * param[out]       publicKeyPtr            public key buffer pointer.
 * param[in]        publicKeyMaxSize        public key buffer max. size [byte].
 * param[out]       publicKeyLenPtr         output public key length pointer [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoECDHGenKeypair(
        const   tommRoC_crypto_ecdh_ecp_group_id_enum_t         ecpGroupId,
                uint8_t*                                const   privateKeyPtr,
        const   uint16_t                                        privateKeyMaxSize,
                uint16_t*                               const   privateKeyLenPtr,
                uint8_t*                                const   publicKeyPtr,
        const   uint16_t                                        publicKeyMaxSize,
                uint16_t*                               const   publicKeyLenPtr);

/**
 * ECDH compute shared secret on an elliptic curve function.
 * NOTE: shared is exported as uint8_t data buffer (big endian).
 *
 * param[in]        ecpGroupId              ECDH domain parameters (curve, subgroup and generator) ID.
 * param[in]        privateKeyPtr           private key buffer pointer.
 * param[in]        privateKeySize          private key length [byte].
 * param[in]        publicKeyPtr            public key buffer pointer.
 * param[in]        publicKeySize           public key length [byte].
 * param[out]       sharedPtr               shared secret buffer pointer.
 * param[in]        sharedMaxSize           shared secret buffer max. size [byte].
 * param[out]       sharedLenPtr            output shared secret length pointer [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoECDHComputeShared(
        const   tommRoC_crypto_ecdh_ecp_group_id_enum_t         ecpGroupId,
        const   uint8_t*                                const   privateKeyPtr,
        const   uint16_t                                        privateKeySize,
        const   uint8_t*                                const   publicKeyPtr,
        const   uint16_t                                        publicKeySize,
                uint8_t*                                const   sharedPtr,
        const   uint16_t                                        sharedMaxSize,
                uint16_t*                               const   sharedLenPtr);

/**
 * @}
 */

#endif
