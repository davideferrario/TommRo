
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "entropy/env/tommRoCSwTemplateEntropyEnv.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

#include "entropy/env/esp32/core/tommRoCSwTemplateEntropyESP32Core.h"
#include "memory/esp32/core/tommRoCSwTemplateMemoryESP32Core.h"

#include "tommRoCSwTemplateEntropy.h"

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
static tommRoC_err_enum_t _entropy_retrive_funct_wrapper(
                uint8_t*    const   bufferPtr,
        const   uint32_t            outputLen) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCSwTemplateEntropyESP32CoreRetrive(bufferPtr, outputLen),
            TOMMRO_C_LOW_LEVEL_ERR);

    return TOMMRO_C_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyEnvStart(void) {

    return TOMMRO_C_SW_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyEnvStop(void) {

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwEntropyStart(void) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateEntropyESP32CoreStart());

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoEntropyInitEnv(_entropy_retrive_funct_wrapper),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwEntropyStop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoEntropyCloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateEntropyESP32CoreStop());

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwEntropyAddSource(
        const   tommRoC_sw_entropy_funct_t              sourceFunct,
        const   uint32_t                                threshold,
        const   tommRoC_sw_entropy_source_type_enum_t   sourceType) {

    return tommRoCSwTemplateEntropyESP32CoreAddSource(sourceFunct, threshold, sourceType);
}

tommRoC_sw_err_enum_t tommRoCSwEntropyGather(void) {

    return tommRoCSwTemplateEntropyESP32CoreGather();
}

#endif
