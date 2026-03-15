
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateLWEspThread.h"

#include "TOMMROC.h"
#include "TOMMROCHw.h"
#include "TOMMROCMw.h"

#include "TOMMROCMwTemplate.h"

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

uint32_t tommRoCHwTemplateLWEspThreadEnvGetSize(void) {
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
    return sizeof(tommRoC_mw_template_thread_t);
#else
    return UINT32_MAX;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspThreadCreate(void* threadPtr, const char* threadNamePtr, void(*threadMain)(void*), void* const threadArgPtr, uint32_t threadStackSize, uint32_t threadPriority) {
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
    tommRoC_mw_thread_config_t config = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_mw_thread_config_t);
    TOMMROC_UTIL_UNUSED_PARAM(threadPriority);
    config.priority     = TOMMRO_C_MW_THREAD_PRIORITY_DEFAULT;
    config.stackSize    = ((0 == threadStackSize) ? (TOMMRO_C_MW_THREAD_STACK_SIZE_DEFAULT) : (threadStackSize));
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwThreadCreate(threadMain, threadArgPtr, threadNamePtr, &config, threadPtr), TOMMRO_C_HW_LOW_LEVEL_ERR);
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(threadPtr);
    TOMMROC_UTIL_UNUSED_PARAM(threadNamePtr);
    TOMMROC_UTIL_UNUSED_PARAM(threadMain);
    TOMMROC_UTIL_UNUSED_PARAM(threadArgPtr);
    TOMMROC_UTIL_UNUSED_PARAM(threadStackSize);
    TOMMROC_UTIL_UNUSED_PARAM(threadPriority);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspThreadTerminate(void* threadPtr) {
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwThreadDestroy(threadPtr), TOMMRO_C_HW_LOW_LEVEL_ERR);
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(threadPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}
