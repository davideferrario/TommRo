
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateEntropyESP32Core.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

#include "mbedtls/entropy.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static mbedtls_entropy_context _ctx;
static bool _is_ctx_init = false;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static int _mbedtls_entropy_funct(void *data, unsigned char *output, size_t len, size_t *olen) {

    tommRoC_sw_entropy_funct_t entropyFunct;
    uint8_t* bufferPtr;
    uint32_t maxSize;
    uint32_t outLen;
    tommRoC_sw_err_enum_t res;

    *olen = 0;

    entropyFunct    = (tommRoC_sw_entropy_funct_t) data;
    bufferPtr       = (uint8_t*) output;
    maxSize         = (uint32_t) len;

    res = entropyFunct(bufferPtr, maxSize, &outLen);

    if (TOMMRO_C_SW_ERR_SUCCESS != res) {
        return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
    }

    *olen = (size_t) outLen;

    return 0;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyESP32CoreStart(void) {

    if (_is_ctx_init) {
        return TOMMRO_C_SW_GENERIC_ERR;
    }

    mbedtls_entropy_init(&_ctx);

    _is_ctx_init = true;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyESP32CoreStop(void) {

    if (!_is_ctx_init) {
        return TOMMRO_C_SW_ENVIRONMENT_NOT_INIT_ERR;
    }

    mbedtls_entropy_free(&_ctx);

    _is_ctx_init = false;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyESP32CoreAddSource(
        const   tommRoC_sw_entropy_funct_t              sourceFunct,
        const   uint32_t                                threshold,
        const   tommRoC_sw_entropy_source_type_enum_t   sourceType) {

    int strong;
    int res;

    TOMMROC_ASSERT_NOT_NULL(sourceFunct);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(sourceFunct);

    if (!_is_ctx_init) {
        return TOMMRO_C_SW_ENVIRONMENT_NOT_INIT_ERR;
    }

    do { // Added to avoid "warning: unreachable code"
        switch (sourceType) {

        case TOMMRO_C_SW_ENTROPY_SOURCE_STRONG:
            strong = MBEDTLS_ENTROPY_SOURCE_STRONG;
            break;

        case TOMMRO_C_SW_ENTROPY_SOURCE_WEAK:
            strong = MBEDTLS_ENTROPY_SOURCE_WEAK;
            break;

        default:
            return TOMMRO_C_SW_PARAM_ERR;

        }
    } while (0);

    res = mbedtls_entropy_add_source(&_ctx, _mbedtls_entropy_funct, (void*) sourceFunct, threshold, strong);

    if (0 != res) {
        return TOMMRO_C_SW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyESP32CoreGather(void) {

    int res;

    if (!_is_ctx_init) {
        return TOMMRO_C_SW_ENVIRONMENT_NOT_INIT_ERR;
    }

    res = mbedtls_entropy_gather(&_ctx);

    if (0 != res) {
        return TOMMRO_C_SW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyESP32CoreRetrive(
                uint8_t*    const   bufferPtr,
        const   uint32_t            outputLen) {

    int res;

    if (!_is_ctx_init) {
        return TOMMRO_C_SW_ENVIRONMENT_NOT_INIT_ERR;
    }

    res = mbedtls_entropy_func(&_ctx, (unsigned char*) bufferPtr, outputLen);

    if (0 != res) {
        return TOMMRO_C_SW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_SW_ERR_SUCCESS;
}

#endif
