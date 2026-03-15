
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "crypto/env/tommRoCTemplateCryptoEnvironmentRND.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)

#include "TOMMROC.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define STM32_UID_SIZE_BYTE             (3 * TOMMROC_UTIL_U32_SIZE)

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
    const uint32_t* uidPtr = (uint32_t*) UID_BASE;
    
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilPrngAddSeed((uint8_t*) uidPtr, STM32_UID_SIZE_BYTE));
}

#endif
