
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "crypto/env/tommRoCTemplateCryptoEnvironmentRND.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#include "TOMMROC.h"

#if defined (FSL_FEATURE_SOC_SIM_COUNT) && FSL_FEATURE_SOC_SIM_COUNT
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__) || defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)
#include "fsl_sim.h"
#endif
#endif

#if defined (FSL_FEATURE_SOC_TRNG_COUNT) && FSL_FEATURE_SOC_TRNG_COUNT
#include "fsl_trng.h"
#endif

#if defined (FSL_FEATURE_SOC_RNG_COUNT) && FSL_FEATURE_SOC_RNG_COUNT
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__)
#include "fsl_rnga.h"
#elif defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__)
#include "fsl_rng.h"
#endif
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if defined (__TOMMROC_USE_CRYPTO_RND_TEMPLATE__)
#if (defined (FSL_FEATURE_SOC_TRNG_COUNT) && FSL_FEATURE_SOC_TRNG_COUNT) || \
    (defined (FSL_FEATURE_SOC_RNG_COUNT) && FSL_FEATURE_SOC_RNG_COUNT)
static tommRoC_err_enum_t _rnd_retrive(
                uint8_t*    const   bufferPtr,
        const   uint32_t            outputLen) {

    status_t res;

#if (defined (FSL_FEATURE_SOC_TRNG_COUNT) && FSL_FEATURE_SOC_TRNG_COUNT)
    res = TRNG_GetRandomData(TRNG0, bufferPtr, outputLen);
#elif (defined (FSL_FEATURE_SOC_RNG_COUNT) && FSL_FEATURE_SOC_RNG_COUNT)
    res = RNG_GetRandomData(RNG, bufferPtr, outputLen);
#endif

    if (kStatus_Success != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}
#endif
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateCryptoEnvironmentRNDStart(void) {

#if defined (__TOMMROC_USE_CRYPTO_RND_TEMPLATE__)

#if (defined (FSL_FEATURE_SOC_TRNG_COUNT) && FSL_FEATURE_SOC_TRNG_COUNT)

    trng_config_t trngConfig;

    // Initialize TRNG configuration structure to default.
    if (kStatus_Success != TRNG_GetDefaultConfig(&trngConfig)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }
    
    // Set sample mode of the TRNG ring oscillator to von Neumann.
    trngConfig.sampleMode = kTRNG_SampleModeVonNeumann;

    if (kStatus_Success != TRNG_Init(TRNG0, &trngConfig)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

#elif (defined (FSL_FEATURE_SOC_RNG_COUNT) && FSL_FEATURE_SOC_RNG_COUNT)

    if (kStatus_Success != RNG_Init(RNG)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }
#endif

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoRNDInitEnv(_rnd_retrive));

    return TOMMRO_C_ERR_SUCCESS;
#else

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateCryptoEnvironmentRNDStop(void) {

#if defined (__TOMMROC_USE_CRYPTO_RND_TEMPLATE__)

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoRNDCloseEnv());

#if (defined (FSL_FEATURE_SOC_TRNG_COUNT) && FSL_FEATURE_SOC_TRNG_COUNT)
    TRNG_Deinit(TRNG0);
#elif (defined (FSL_FEATURE_SOC_RNG_COUNT) && FSL_FEATURE_SOC_RNG_COUNT)
    RNG_Deinit(RNG);
#endif

    return TOMMRO_C_ERR_SUCCESS;

#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

void tommRoCTemplateCryptoEnvironmentRNDPrngAddSeed(void) {

#if defined (FSL_FEATURE_SOC_SIM_COUNT) && FSL_FEATURE_SOC_SIM_COUNT

    // Use chip unique ID to add PRNG seed
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__) || defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)

    sim_uid_t uid;
    const uint8_t uidSize = sizeof(uid);
    const uint8_t* uidPtr = (uint8_t*) &uid;
    
    SIM_GetUniqueId(&uid);

#elif defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)

    const uint32_t uid[] = { SIM->UUIDH, SIM->UUIDL };
    const uint8_t uidSize = sizeof(uid);
    const uint8_t* uidPtr = (uint8_t*) uid;
#endif

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilPrngAddSeed(uidPtr, uidSize));

    // Use Vendor bluetooth address(MAC) (6 Bytes)
#elif defined (FSL_FEATURE_FLASH_ADDR_OF_VENDOR_BD_ADDR)

    const uint8_t uidSize = 6;
    const uint8_t* uidPtr = (uint8_t*) FSL_FEATURE_FLASH_ADDR_OF_VENDOR_BD_ADDR;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilPrngAddSeed(uidPtr, uidSize));
#endif
}

#endif
