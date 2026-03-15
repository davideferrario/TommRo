
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "crypto/tommRoCTemplateCryptoSHA1.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#if defined (__TOMMROC_USE_CRYPTO_SHA1_TEMPLATE__)

#include "TOMMROC.h"

#if (0 != FSL_FEATURE_SOC_LTC_COUNT)
#include "fsl_ltc.h"

#if defined (FSL_FEATURE_LTC_HAS_SHA) && FSL_FEATURE_LTC_HAS_SHA

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
static tommRoC_err_enum_t _sha(
        const   uint8_t*    const   inputBufferPtr,
        const   uint16_t            inputBufferLen,
                uint8_t*    const   outputBufferPtr) {

    status_t res;

    res = LTC_HASH(
            LTC0,
            kLTC_Sha1,
            inputBufferPtr,
            inputBufferLen,
            NULL,
            0,
            outputBufferPtr,
            TOMMROC_CRYPTO_SHA1_RESULT_SIZE_BYTE);

    if (kStatus_Success != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

#endif

#endif

#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateCryptoSHA1Start(void) {

#if defined (__TOMMROC_USE_CRYPTO_SHA1_TEMPLATE__)                      &&  \
    defined (FSL_FEATURE_SOC_LTC_COUNT) && FSL_FEATURE_SOC_LTC_COUNT    &&  \
    defined (FSL_FEATURE_LTC_HAS_SHA) && FSL_FEATURE_LTC_HAS_SHA

    LTC_Init(LTC0);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoSHA1InitEnv(_sha));

    return TOMMRO_C_ERR_SUCCESS;

#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateCryptoSHA1Stop(void) {

#if defined (__TOMMROC_USE_CRYPTO_SHA1_TEMPLATE__)                      &&  \
    defined (FSL_FEATURE_SOC_LTC_COUNT) && FSL_FEATURE_SOC_LTC_COUNT    &&  \
    defined (FSL_FEATURE_LTC_HAS_SHA) && FSL_FEATURE_LTC_HAS_SHA

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCCryptoSHA1CloseEnv());

    LTC_Deinit(LTC0);

    return TOMMRO_C_ERR_SUCCESS;

#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

#endif
