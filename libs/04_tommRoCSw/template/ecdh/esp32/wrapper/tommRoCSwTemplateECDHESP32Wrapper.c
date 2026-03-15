
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateECDHESP32Wrapper.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

#include "ecdh/esp32/context/tommRoCSwTemplateECDHESP32Context.h"

#include "key/esp32/tommRoCSwTemplateMPIESP32.h"

#include "mbedtls/bignum.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/ecdh.h"
#include "mbedtls/ecp.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static tommRoC_sw_template_ecdh_esp32_context_t* _ecdh_ctx_ptr = NULL;
static bool _is_protect_against_elaborate_timing_attacks_enabled = false;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static mbedtls_ecp_group_id _tommRoC_ecdh_ecp_group_id_to_mbedtls_ecp_group_id(
        const   tommRoC_crypto_ecdh_ecp_group_id_enum_t ecpGroupId) {

    do { // Added to avoid "warning: unreachable code"
        switch (ecpGroupId) {

#if defined (MBEDTLS_ECP_DP_SECP192R1_ENABLED)
        case TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_SECP192R1:
            return MBEDTLS_ECP_DP_SECP192R1;
#endif

#if defined (MBEDTLS_ECP_DP_SECP224R1_ENABLED)
        case TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_SECP224R1:
            return MBEDTLS_ECP_DP_SECP224R1;
#endif

#if defined (MBEDTLS_ECP_DP_SECP256R1_ENABLED)
        case TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_SECP256R1:
            return MBEDTLS_ECP_DP_SECP256R1;
#endif

#if defined (MBEDTLS_ECP_DP_SECP384R1_ENABLED)
        case TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_SECP384R1:
            return MBEDTLS_ECP_DP_SECP384R1;
#endif

#if defined (MBEDTLS_ECP_DP_SECP521R1_ENABLED)
        case TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_SECP521R1:
            return MBEDTLS_ECP_DP_SECP521R1;
#endif

#if defined (MBEDTLS_ECP_DP_BP256R1_ENABLED)
        case TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_BP256R1:
            return MBEDTLS_ECP_DP_BP256R1;
#endif

#if defined (MBEDTLS_ECP_DP_BP384R1_ENABLED)
        case TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_BP384R1:
            return MBEDTLS_ECP_DP_BP384R1;
#endif

#if defined (MBEDTLS_ECP_DP_BP512R1_ENABLED)
        case TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_BP512R1:
            return MBEDTLS_ECP_DP_BP512R1;
#endif

#if defined (MBEDTLS_ECP_DP_CURVE25519_ENABLED)
        case TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_CURVE25519:
            return MBEDTLS_ECP_DP_CURVE25519;
#endif

#if defined (MBEDTLS_ECP_DP_SECP192K1_ENABLED)
        case TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_SECP192K1:
            return MBEDTLS_ECP_DP_SECP192K1;
#endif

#if defined (MBEDTLS_ECP_DP_SECP224K1_ENABLED)
        case TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_SECP224K1:
            return MBEDTLS_ECP_DP_SECP224K1;
#endif

#if defined (MBEDTLS_ECP_DP_SECP256K1_ENABLED)
        case TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_SECP256K1:
            return MBEDTLS_ECP_DP_SECP256K1;
#endif

#if defined (MBEDTLS_ECP_DP_CURVE448_ENABLED)
        case TOMMRO_C_CRYPTO_ECDH_ECP_DOMAIN_PARAM_CURVE448:
            return MBEDTLS_ECP_DP_CURVE448;
#endif

        default:
            break;
        }
    } while (0);

    return MBEDTLS_ECP_DP_NONE;
}

static int _random_funct_wrapper(void *p_rng, unsigned char *output, size_t len) {

    TOMMROC_ASSERT_NULL(p_rng);

    if (NULL != p_rng) {
        return MBEDTLS_ERR_CTR_DRBG_ENTROPY_SOURCE_FAILED;
    }

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoRNDRetrive(output, len),
            MBEDTLS_ERR_CTR_DRBG_ENTROPY_SOURCE_FAILED);

    return 0;
}

static tommRoC_err_enum_t _gen_keypair(
                tommRoC_sw_template_ecdh_esp32_context_t*   const   ecdhCtxPtr,
        const   tommRoC_crypto_ecdh_ecp_group_id_enum_t             ecpGroupId,
                uint8_t*                                    const   privateKeyPtr,
        const   uint16_t                                            privateKeySize,
                uint8_t*                                    const   publicKeyPtr,
        const   uint16_t                                            publicKeyMaxSize,
                uint16_t*                                   const   publicKeyLenPtr) {

    mbedtls_ecp_group_id mbedtlsECPGroupID;
    size_t olen;
    int res;

    mbedtlsECPGroupID = _tommRoC_ecdh_ecp_group_id_to_mbedtls_ecp_group_id(ecpGroupId);

    if (MBEDTLS_ECP_DP_NONE == mbedtlsECPGroupID) {
        return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
    }

    res = mbedtls_ecp_group_load(&ecdhCtxPtr->grp, mbedtlsECPGroupID);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    res = mbedtls_ecdh_gen_public(
            &ecdhCtxPtr->grp,
            &ecdhCtxPtr->d,         // The destination MPI (private key)    - OUTPUT.
            &ecdhCtxPtr->Q,         // The destination point (public key)   - OUTPUT.
            _random_funct_wrapper,
            NULL);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    // Extract private key
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCSwTemplateMPIESP32WriteBinary(
                    &ecdhCtxPtr->d,
                    privateKeyPtr,
                    privateKeySize));

    // Extract public key
    res = mbedtls_ecp_point_write_binary(
            &ecdhCtxPtr->grp,
            &ecdhCtxPtr->Q,
            MBEDTLS_ECP_PF_UNCOMPRESSED,
            &olen,
            publicKeyPtr,
            publicKeyMaxSize);

    if (MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL == res) {
        return TOMMRO_C_NOT_ENOUGH_RESOURCE_ERR;
    }
    else if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    *publicKeyLenPtr = (uint16_t) olen;

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t _compute_shared(
                tommRoC_sw_template_ecdh_esp32_context_t*   const   ecdhCtxPtr,
        const   tommRoC_crypto_ecdh_ecp_group_id_enum_t             ecpGroupId,
        const   uint8_t*                                    const   privateKeyPtr,
        const   uint16_t                                            privateKeySize,
        const   uint8_t*                                    const   publicKeyPtr,
        const   uint16_t                                            publicKeySize,
                uint8_t*                                    const   sharedPtr,
        const   uint16_t                                            sharedSize) {

    int (*randomFunctPtr)(void*, unsigned char*, size_t);
    mbedtls_ecp_group_id mbedtlsECPGroupID;
    int res;

    mbedtlsECPGroupID = _tommRoC_ecdh_ecp_group_id_to_mbedtls_ecp_group_id(ecpGroupId);

    if (MBEDTLS_ECP_DP_NONE == mbedtlsECPGroupID) {
        return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
    }

    res = mbedtls_ecp_group_load(&ecdhCtxPtr->grp, mbedtlsECPGroupID);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    // Import private key
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCSwTemplateMPIESP32ReadBinary(
                    &ecdhCtxPtr->d,
                    privateKeyPtr,
                    privateKeySize));

    // Import public key from another peer.
    res = mbedtls_ecp_point_read_binary(
            &ecdhCtxPtr->grp,
            &ecdhCtxPtr->Qp,
            publicKeyPtr,
            publicKeySize);

    if (MBEDTLS_ERR_MPI_ALLOC_FAILED == res) {
        return TOMMRO_C_NOT_ENOUGH_RESOURCE_ERR;
    }
    else if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    // Check if countermeasures against elaborate timing attacks (RND function) are enabled.
    if (_is_protect_against_elaborate_timing_attacks_enabled) {
        randomFunctPtr = _random_funct_wrapper;
    }
    else {
        randomFunctPtr = NULL;
    }

    // Compute shared
    res = mbedtls_ecdh_compute_shared(
            &ecdhCtxPtr->grp,
            &ecdhCtxPtr->z,         // The destination MPI (shared secret)  - OUTPUT.
            &ecdhCtxPtr->Qp,        // The public key from another peer     - INPUT.
            &ecdhCtxPtr->d,         // Our secret exponent (private key)    - INPUT.
            randomFunctPtr,
            NULL);

    if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    // Extract shared secret
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCSwTemplateMPIESP32WriteBinary(
                    &ecdhCtxPtr->z,
                    sharedPtr,
                    sharedSize));

    return TOMMRO_C_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateECDHESP32WrapperInit(tommRoC_sw_template_ecdh_esp32_context_t* const ecdhCtxPtr) {

    TOMMROC_ASSERT_NOT_NULL(ecdhCtxPtr);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(ecdhCtxPtr);

    _ecdh_ctx_ptr = ecdhCtxPtr;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateECDHESP32WrapperClose(void) {

    _ecdh_ctx_ptr = NULL;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

bool tommRoCSwTemplateECDHESP32WrapperIsEcpGroupAvailable(
        const   tommRoC_crypto_ecdh_ecp_group_id_enum_t         ecpGroupId) {

    return (MBEDTLS_ECP_DP_NONE != _tommRoC_ecdh_ecp_group_id_to_mbedtls_ecp_group_id(ecpGroupId));
}

tommRoC_err_enum_t tommRoCSwTemplateECDHESP32WrapperGenKeypair(
        const   tommRoC_crypto_ecdh_ecp_group_id_enum_t         ecpGroupId,
                uint8_t*                                const   privateKeyPtr,
        const   uint16_t                                        privateKeySize,
                uint8_t*                                const   publicKeyPtr,
        const   uint16_t                                        publicKeyMaxSize,
                uint16_t*                               const   publicKeyLenPtr) {

    tommRoC_sw_template_ecdh_esp32_context_t* ecdhCtxPtr;
    tommRoC_err_enum_t res;

    ecdhCtxPtr = _ecdh_ctx_ptr;

    tommRoCSwTemplateECDHESP32ContextInit(ecdhCtxPtr);

    // NOTE: operation can use some time to compute.
    tommRoCOsDisableWDT();

    res = _gen_keypair(
            ecdhCtxPtr,
            ecpGroupId,
            privateKeyPtr,
            privateKeySize,
            publicKeyPtr,
            publicKeyMaxSize,
            publicKeyLenPtr);

    tommRoCOsEnableWDT();

    tommRoCSwTemplateECDHESP32ContextFree(ecdhCtxPtr);

    return res;
}

tommRoC_err_enum_t tommRoCSwTemplateECDHESP32WrapperComputeShared(
        const   tommRoC_crypto_ecdh_ecp_group_id_enum_t         ecpGroupId,
        const   uint8_t*                                const   privateKeyPtr,
        const   uint16_t                                        privateKeySize,
        const   uint8_t*                                const   publicKeyPtr,
        const   uint16_t                                        publicKeySize,
                uint8_t*                                const   sharedPtr,
        const   uint16_t                                        sharedSize) {

    tommRoC_sw_template_ecdh_esp32_context_t* ecdhCtxPtr;
    tommRoC_err_enum_t res;

    ecdhCtxPtr = _ecdh_ctx_ptr;

    tommRoCSwTemplateECDHESP32ContextInit(ecdhCtxPtr);

    // NOTE: operation can use some time to compute.
    tommRoCOsDisableWDT();

    res = _compute_shared(
            ecdhCtxPtr,
            ecpGroupId,
            privateKeyPtr,
            privateKeySize,
            publicKeyPtr,
            publicKeySize,
            sharedPtr,
            sharedSize);

    tommRoCOsEnableWDT();

    tommRoCSwTemplateECDHESP32ContextFree(ecdhCtxPtr);

    return res;
}

void tommRoCSwTemplateECDHESP32WrapperEnableProtectionTimingAttacks(void) {

    _is_protect_against_elaborate_timing_attacks_enabled = true;
}

void tommRoCSwTemplateECDHESP32WrapperDisableProtectionTimingAttacks(void) {

    _is_protect_against_elaborate_timing_attacks_enabled = false;
}

#endif
