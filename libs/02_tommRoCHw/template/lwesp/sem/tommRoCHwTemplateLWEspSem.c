
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateLWEspSem.h"

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
#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
static tommRoC_mw_err_enum_t _wait(void* semPtr, uint32_t waitTimeoutMs) {

    tommRoC_mw_err_enum_t res;

#if defined (__TOMMROC_MW_USE_SEMAPHORE_CMSIS_V1_RTOS_TEMPLATE__)
    res = tommRoCMwSemaphoreWait(semPtr, waitTimeoutMs);

#elif defined (__TOMMROC_MW_USE_SEMAPHORE_CMSIS_V2_RTOS_TEMPLATE__)
    res = tommRoCMwSemaphoreWait(semPtr, waitTimeoutMs);

#elif defined (__TOMMROC_MW_USE_SEMAPHORE_NXP_OSA_TEMPLATE__)
    res = tommRoCMwSemaphoreWait(semPtr, waitTimeoutMs);

#elif defined (__TOMMROC_MW_USE_SEMAPHORE_SEMAPHORE_H_TEMPLATE__)
    if (WAIT_SEMAPHORE_INFINITE_TIMEOUT == waitTimeoutMs) {
        for (;;) {
            if (TOMMRO_C_MW_ERR_SUCCESS == tommRoCMwSemaphoreTryWait(semPtr)) {
                return TOMMRO_C_MW_ERR_SUCCESS;
            }
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(0));
        }
    }
    else {
        res = tommRoCMwSemaphoreWait(semPtr, waitTimeoutMs);
    }

#elif defined (__TOMMROC_MW_USE_SEMAPHORE_THREADX_TEMPLATE__)
    res = tommRoCMwSemaphoreWait(semPtr, waitTimeoutMs);

#elif defined (__TOMMROC_MW_USE_SEMAPHORE_WINDOWS_H_TEMPLATE__)
    res = tommRoCMwSemaphoreWait(semPtr, waitTimeoutMs);

#else
    TOMMROC_UTIL_UNUSED_PARAM(semPtr);
    TOMMROC_UTIL_UNUSED_PARAM(waitTimeoutMs);
    res  = TOMMRO_C_MW_ENVIRONMENT_NOT_INIT_ERR;
#endif

    return res;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

uint32_t tommRoCHwTemplateLWEspSemEnvGetSize(void) {
#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    return sizeof(tommRoC_mw_template_semaphore_t);
#else
    return UINT32_MAX;
#endif
}


tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspSemCreate(void* semPtr, uint8_t cnt) {
#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwSemaphoreCreate(semPtr, cnt), TOMMRO_C_HW_LOW_LEVEL_ERR);
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(semPtr);
    TOMMROC_UTIL_UNUSED_PARAM(cnt);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspSemDestroy(void* semPtr) {
#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwSemaphoreDestroy(semPtr), TOMMRO_C_HW_LOW_LEVEL_ERR);
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(semPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspSemWait(void* semPtr, uint32_t timeout) {
#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(_wait(semPtr, ((0 == timeout) ? (WAIT_SEMAPHORE_INFINITE_TIMEOUT) : (timeout))), TOMMRO_C_HW_LOW_LEVEL_ERR);
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(semPtr);
    TOMMROC_UTIL_UNUSED_PARAM(timeout);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspSemRelease(void* semPtr) {
#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCMwSemaphoreRelease(semPtr), TOMMRO_C_HW_LOW_LEVEL_ERR);
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(semPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}
