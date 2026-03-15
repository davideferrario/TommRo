
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateLWEspMutex.h"

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

uint32_t tommRoCHwTemplateLWEspMutexEnvGetSize(void) {
#if defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)
    return sizeof(tommRoC_mw_template_mutex_t);
#else
    return UINT32_MAX;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspMutexCreateRecursive(void* mutexPtr) {
#if defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwMutexCreateRecursive(mutexPtr), TOMMRO_C_HW_LOW_LEVEL_ERR);
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(mutexPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspMutexDestroy(void* mutexPtr) {
#if defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwMutexDestroy(mutexPtr), TOMMRO_C_HW_LOW_LEVEL_ERR);
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(mutexPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspMutexLock(void* mutexPtr) {
#if defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwMutexLock(mutexPtr, LOCK_MUTEX_INFINITE_TIMEOUT), TOMMRO_C_HW_LOW_LEVEL_ERR);
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(mutexPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspMutexUnlock(void* mutexPtr) {
#if defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwMutexUnLock(mutexPtr), TOMMRO_C_HW_LOW_LEVEL_ERR);
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(mutexPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}
