
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "crypto/env/tommRoCTemplateCryptoEnvironmentRND.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_IS_USED__)

#include "TOMMROC.h"

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

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateCryptoEnvironmentRNDStart(void) {

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateCryptoEnvironmentRNDStop(void) {

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

void tommRoCTemplateCryptoEnvironmentRNDPrngAddSeed(void) {

    // Use chip unique ID to add PRNG seed
    uint64_t uid;

    uid = SYSTEM_GetUnique();
    
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilPrngAddSeed((uint8_t*) &uid, sizeof(uid)));
}

#endif
