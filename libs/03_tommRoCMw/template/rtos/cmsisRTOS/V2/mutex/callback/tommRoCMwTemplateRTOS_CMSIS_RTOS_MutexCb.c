
#if defined (__TOMMROC_MW_USE_MUTEX_CMSIS_V2_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_CMSIS_RTOS_MutexCb.h"

#include "rtos/cmsisRTOS/V2/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"

#include "TOMMROC.h"

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
static uint32_t _get_timeout(const uint32_t waitTimeoutMs) {

    if (LOCK_MUTEX_NO_WAIT_TIMEOUT == waitTimeoutMs) {
        return 0;
    }

    if (LOCK_MUTEX_INFINITE_TIMEOUT == waitTimeoutMs) {
        return osWaitForever;
    }

    return waitTimeoutMs;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_MutexCb_Create(
                void*       const   inputMutexPtr) {

#if (configUSE_MUTEXES == 1)
    tommRoC_mw_template_mutex_t* mutexPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(osMutexAttr_t,   ((tommRoC_mw_template_mutex_t*)NULL)->osMutexAttr);
    TOMMROC_CTA_SIZE_OF_EQUALS(osMutexId_t,     ((tommRoC_mw_template_mutex_t*)NULL)->osMutexId);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&mutexPtr->osMutexAttr, 0x00, sizeof(mutexPtr->osMutexAttr)));

#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(mutexPtr->osMutexCb, 0x00, sizeof(mutexPtr->osMutexCb)));
    mutexPtr->osMutexDef.mutex = mutexPtr->osMutexCb;
#endif

    mutexPtr->osMutexId = osMutexNew(&mutexPtr->osMutexAttr);

    if (__CMSIS_RTOS_MUTEX_NEW_ON_ERROR_RESULT__ == mutexPtr->osMutexId) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(inputMutexPtr);
    return TOMMRO_C_MW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_MutexCb_CreateRecursive(
                void*       const   inputMutexPtr) {

#if (configUSE_RECURSIVE_MUTEXES == 1)
    tommRoC_mw_template_mutex_t* mutexPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(osMutexAttr_t,   ((tommRoC_mw_template_mutex_t*)NULL)->osMutexAttr);
    TOMMROC_CTA_SIZE_OF_EQUALS(osMutexId_t,     ((tommRoC_mw_template_mutex_t*)NULL)->osMutexId);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&mutexPtr->osMutexAttr, 0x00, sizeof(mutexPtr->osMutexAttr)));

#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(mutexPtr->osMutexCb, 0x00, sizeof(mutexPtr->osMutexCb)));
    mutexPtr->osMutexDef.mutex = mutexPtr->osMutexCb;
#endif

    // NOTE: configure mutex to be recursive
    mutexPtr->osMutexAttr.attr_bits |= osMutexRecursive;

    mutexPtr->osMutexId = osMutexNew(&mutexPtr->osMutexAttr);

    if (__CMSIS_RTOS_MUTEX_NEW_ON_ERROR_RESULT__ == mutexPtr->osMutexId) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(inputMutexPtr);
    return TOMMRO_C_MW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_MutexCb_Lock(
                void*       const   inputMutexPtr,
        const   uint32_t            waitTimeoutMs) {

    uint32_t millisec;
    tommRoC_mw_template_mutex_t* mutexPtr;
    osStatus_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osMutexId_t, ((tommRoC_mw_template_mutex_t*)NULL)->osMutexId);

    TOMMROC_CTA_SIZE_OF_EQUALS(osWaitForever, millisec);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    millisec = _get_timeout(waitTimeoutMs);

    res = osMutexAcquire(mutexPtr->osMutexId, millisec);

#if (tskKERNEL_VERSION_MAJOR == 10) && (tskKERNEL_VERSION_MINOR == 3) && (tskKERNEL_VERSION_BUILD == 1)
    if ((osEventTimeout == res) || (osErrorTimeoutResource == res)) {
#elif (tskKERNEL_VERSION_MAJOR == 10) && (tskKERNEL_VERSION_MINOR == 5) && (tskKERNEL_VERSION_BUILD == 1)
    if (osErrorTimeout == res) {
#elif (tskKERNEL_VERSION_MAJOR == 10) && (tskKERNEL_VERSION_MINOR == 6) && (tskKERNEL_VERSION_BUILD == 2)
    if (osErrorTimeout == res) {
#endif
        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    if (__CMSIS_RTOS_MUTEX_ACQUIRE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_MutexCb_UnLock(
                void*       const   inputMutexPtr) {

    tommRoC_mw_template_mutex_t* mutexPtr;
    osStatus_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osMutexId_t, ((tommRoC_mw_template_mutex_t*)NULL)->osMutexId);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    res = osMutexRelease(mutexPtr->osMutexId);

    if (__CMSIS_RTOS_MUTEX_RELEASE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_MutexCb_Destroy(
                void*       const   inputMutexPtr) {

    tommRoC_mw_template_mutex_t* mutexPtr;
    osStatus_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osMutexId_t, ((tommRoC_mw_template_mutex_t*)NULL)->osMutexId);

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    res = osMutexDelete(mutexPtr->osMutexId);

    if (__CMSIS_RTOS_MUTEX_DELETE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
