
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "entropy/env/tommRoCSwTemplateEntropyEnv.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#include "tommRoCSwTemplateEntropy.h"

#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)
#include "os/arm/DWT/tommRoCTemplateOs_ARM_DWT.h"
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
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)
static tommRoC_sw_err_enum_t _entropy_dwt_funct(uint8_t* const bufferPtr, const uint32_t maxSize, uint32_t* const outLenPtr) {

    return tommRoCSwTemplateEntropyU32BaseFunct(
            bufferPtr,
            maxSize,
            outLenPtr,
            tommRoCTemplateOs_ARM_DWTGetCYCCNT);
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyEnvStart(void) {

#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

    if (tommRoCTemplateOs_ARM_DWTIsAvailable()) {

        TOMMROC_SW_ASSERT_TOMMROC_SW_LIB_FUNCT_SUCCESS(tommRoCSwEntropyAddSource(_entropy_dwt_funct, sizeof(uint32_t), TOMMRO_C_SW_ENTROPY_SOURCE_STRONG));

        return TOMMRO_C_SW_ERR_SUCCESS;
    }
#endif

    return TOMMRO_C_SW_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyEnvStop(void) {

    return TOMMRO_C_SW_ERR_SUCCESS;
}

#endif
