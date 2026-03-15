
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateEntropy.h"

#include "entropy/env/tommRoCSwTemplateEntropyEnv.h"

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
#if defined (__TOMMROC_SW_USE_ENTROPY_TEMPLATE__)
static void _u32_counter_startup(
                uint32_t*   const   counterPtr,
                uint32_t*   const   incCounterPtr) {

    const char buildTime[] = __TIME__;
    const char buildDate[] = __DATE__;

    // On start set counter as 0xssmmhhdd (better entropy)
    // ss: seconds of compile
    // mm: minutes of compile
    // hh: hours of compile
    // dd: day of compile
    *counterPtr =   ((uint32_t) ((buildTime[6] - '0') * 10 + (buildTime[7] - '0')) << 24) |
                    ((uint32_t) ((buildTime[3] - '0') * 10 + (buildTime[4] - '0')) << 16) |
                    ((uint32_t) ((buildTime[0] - '0') * 10 + (buildTime[1] - '0')) <<  8) |
                    ((uint32_t) ((buildDate[4] - '0') * 10 + (buildDate[5] - '0')) <<  0);

    // Get increment counter depending form build date month (Note: as string).
    *incCounterPtr = (uint32_t) buildDate[0] + (uint32_t) buildDate[1] + (uint32_t) buildDate[2];
}

static uint32_t _u32_counter(void) {

    static bool firstExecute = true;

    static uint32_t counter;
    static uint32_t incCounter;

    if (firstExecute) {

        _u32_counter_startup(&counter, &incCounter);

        firstExecute = false;
    }

    counter += incCounter;

    return counter;
}

static tommRoC_sw_err_enum_t _entropy_counter_funct(uint8_t* const bufferPtr, const uint32_t maxSize, uint32_t* const outLenPtr) {

    return tommRoCSwTemplateEntropyU32BaseFunct(
            bufferPtr,
            maxSize,
            outLenPtr,
            _u32_counter);
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyStart(void) {
    
#if defined (__TOMMROC_SW_USE_ENTROPY_TEMPLATE__)

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwEntropyStart());

    if (TOMMRO_C_SW_ERR_SUCCESS != tommRoCSwTemplateEntropyEnvStart()) {
        TOMMROC_SW_ASSERT_TOMMROC_SW_LIB_FUNCT_SUCCESS(tommRoCSwEntropyAddSource(_entropy_counter_funct, sizeof(uint32_t), TOMMRO_C_SW_ENTROPY_SOURCE_STRONG));
    }
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyStop(void) {
    
#if defined (__TOMMROC_SW_USE_ENTROPY_TEMPLATE__)

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwTemplateEntropyEnvStop());

    TOMMROC_SW_ERR_IF_TOMMROC_SW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCSwEntropyStop());
#endif

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyU8BaseFunct(
                uint8_t*                                            const   bufferPtr,
        const   uint32_t                                                    maxSize,
                uint32_t*                                           const   outLenPtr,
        const   tommRoC_sw_template_entropy_u8_result_base_funct_t          resultFunct) {
            
#if defined (__TOMMROC_SW_USE_ENTROPY_TEMPLATE__)

    TOMMROC_UTIL_UNUSED_PARAM(maxSize);

    TOMMROC_ASSERT_NOT_NULL(resultFunct);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(resultFunct);

    *bufferPtr = resultFunct();

    *outLenPtr = sizeof(uint8_t);

    return TOMMRO_C_SW_ERR_SUCCESS;
#else

    TOMMROC_UTIL_UNUSED_PARAM(bufferPtr);
    TOMMROC_UTIL_UNUSED_PARAM(maxSize);
    TOMMROC_UTIL_UNUSED_PARAM(outLenPtr);
    TOMMROC_UTIL_UNUSED_PARAM(resultFunct);

    return TOMMRO_C_SW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyU16BaseFunct(
                uint8_t*                                            const   bufferPtr,
        const   uint32_t                                                    maxSize,
                uint32_t*                                           const   outLenPtr,
        const   tommRoC_sw_template_entropy_u16_result_base_funct_t         resultFunct) {
            
#if defined (__TOMMROC_SW_USE_ENTROPY_TEMPLATE__)            

    uint16_t value;
    uint8_t toCopy;

    TOMMROC_ASSERT_NOT_NULL(resultFunct);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(resultFunct);

    toCopy = tommRoCMathMin(sizeof(value), maxSize);

    value = resultFunct();

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(bufferPtr, &value, toCopy));

    *outLenPtr = toCopy;

    return TOMMRO_C_SW_ERR_SUCCESS;
#else

    TOMMROC_UTIL_UNUSED_PARAM(bufferPtr);
    TOMMROC_UTIL_UNUSED_PARAM(maxSize);
    TOMMROC_UTIL_UNUSED_PARAM(outLenPtr);
    TOMMROC_UTIL_UNUSED_PARAM(resultFunct);

    return TOMMRO_C_SW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyU32BaseFunct(
                uint8_t*                                            const   bufferPtr,
        const   uint32_t                                                    maxSize,
                uint32_t*                                           const   outLenPtr,
        const   tommRoC_sw_template_entropy_u32_result_base_funct_t         resultFunct) {
            
#if defined (__TOMMROC_SW_USE_ENTROPY_TEMPLATE__)            

    uint32_t value;
    uint8_t toCopy;

    TOMMROC_ASSERT_NOT_NULL(resultFunct);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(resultFunct);

    toCopy = tommRoCMathMin(sizeof(value), maxSize);

    value = resultFunct();

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(bufferPtr, &value, toCopy));

    *outLenPtr = toCopy;

    return TOMMRO_C_SW_ERR_SUCCESS;
#else

    TOMMROC_UTIL_UNUSED_PARAM(bufferPtr);
    TOMMROC_UTIL_UNUSED_PARAM(maxSize);
    TOMMROC_UTIL_UNUSED_PARAM(outLenPtr);
    TOMMROC_UTIL_UNUSED_PARAM(resultFunct);

    return TOMMRO_C_SW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}
