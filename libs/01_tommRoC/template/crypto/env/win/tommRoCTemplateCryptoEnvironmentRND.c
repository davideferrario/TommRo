
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "crypto/env/tommRoCTemplateCryptoEnvironmentRND.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)

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

    // Use timestamp to add PRNG seed
    uint32_t timestamp;

    timestamp = tommRoCOsGetTimestamp();

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilPrngAddSeed((uint8_t*) &timestamp, sizeof(timestamp)));
}

#endif
