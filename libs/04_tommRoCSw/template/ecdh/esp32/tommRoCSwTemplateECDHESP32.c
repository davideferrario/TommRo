
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

#include "ecdh/esp32/context/tommRoCSwTemplateECDHESP32Context.h"
#include "ecdh/esp32/wrapper/tommRoCSwTemplateECDHESP32Wrapper.h"
#include "memory/esp32/core/tommRoCSwTemplateMemoryESP32Core.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static tommRoC_sw_template_ecdh_esp32_context_t _ecdh_ctx;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_sw_err_enum_t _check_tommRoC_rnd_is_init(void) {

    bool tommRoCRNDIsInit;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCCryptoRNDGetProp(TOMMRO_C_CRYPTO_RND_IS_INIT_PROP, &tommRoCRNDIsInit));

    if (!tommRoCRNDIsInit) {
        return TOMMRO_C_SW_ENVIRONMENT_NOT_INIT_ERR;
    }

    return TOMMRO_C_SW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/


tommRoC_sw_err_enum_t tommRoCSwECDHStart(void) {

    const tommRoC_crypto_ecdh_environment_config_t ecdhEnvConfig = {
        /* .genKeypair */           tommRoCSwTemplateECDHESP32WrapperGenKeypair,
        /* .computeShared */        tommRoCSwTemplateECDHESP32WrapperComputeShared,
        /* .isEcpGroupAvailable */  tommRoCSwTemplateECDHESP32WrapperIsEcpGroupAvailable,
    };

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateMemoryESP32CoreIsInit());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_check_tommRoC_rnd_is_init());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateECDHESP32WrapperInit(&_ecdh_ctx));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoECDHInitEnv(&ecdhEnvConfig),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwECDHStop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCCryptoECDHCloseEnv(),
            TOMMRO_C_SW_LOW_LEVEL_ERR);

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateECDHESP32WrapperClose());

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwECDHEnableProtectionTimingAttacks(void) {

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_check_tommRoC_rnd_is_init());

    tommRoCSwTemplateECDHESP32WrapperEnableProtectionTimingAttacks();

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwECDHDisableProtectionTimingAttacks(void) {

    tommRoCSwTemplateECDHESP32WrapperDisableProtectionTimingAttacks();

    return TOMMRO_C_SW_ERR_SUCCESS;
}

#endif
