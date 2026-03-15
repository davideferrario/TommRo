
#if defined (__TOMMROC_MW_USE_SEMAPHORE_CMSIS_V2_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_CMSIS_RTOS_SemaphoreCb.h"

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

    if (WAIT_SEMAPHORE_NO_WAIT_TIMEOUT == waitTimeoutMs) {
        return 0;
    }

    if (WAIT_SEMAPHORE_INFINITE_TIMEOUT == waitTimeoutMs) {
        return osWaitForever;
    }

    return waitTimeoutMs;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_SemaphoreCb_Create(
                void*       const   inputSemaphorePtr,
        const   uint32_t            availableRes) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(osSemaphoreAttr_t,   ((tommRoC_mw_template_semaphore_t*)NULL)->osSemaphoreAttr);
    TOMMROC_CTA_SIZE_OF_EQUALS(osSemaphoreId_t,     ((tommRoC_mw_template_semaphore_t*)NULL)->osSemaphoreId);

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&semaphorePtr->osSemaphoreAttr, 0x00, sizeof(semaphorePtr->osSemaphoreAttr)));

#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(semaphorePtr->osSemaphoreCb, 0x00, sizeof(semaphorePtr->osSemaphoreCb)));
    semaphorePtr->osSemaphoreDef.semaphore = semaphorePtr->osSemaphoreCb;
#endif

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
#if (configSUPPORT_STATIC_ALLOCATION == 0) && (configSUPPORT_DYNAMIC_ALLOCATION == 1)
    // NOTE: FreeRTOS cmsis implementation has a bug. Handle the creation manually
    if (0 == availableRes) {
        semaphorePtr->osSemaphoreId = xSemaphoreCreateBinary();
    }
    else {
        semaphorePtr->osSemaphoreId = osSemaphoreNew(&semaphorePtr->osSemaphoreDef, availableRes);
    }
#else
    semaphorePtr->osSemaphoreId = osSemaphoreNew(availableRes, availableRes, &semaphorePtr->osSemaphoreAttr);
#endif
#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
    semaphorePtr->osSemaphoreId = osSemaphoreCreate(&semaphorePtr->osSemaphoreDef, availableRes);
#endif

    if (__CMSIS_RTOS_SEMAPHORE_CREATE_ON_ERROR_RESULT__ == semaphorePtr->osSemaphoreId) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_SemaphoreCb_Wait(
                void*       const   inputSemaphorePtr,
        const   uint32_t            waitTimeoutMs) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;
    osStatus_t res;
    uint32_t millisec;

    TOMMROC_CTA_SIZE_OF_EQUALS(osSemaphoreId_t, ((tommRoC_mw_template_semaphore_t*)NULL)->osSemaphoreId);

    TOMMROC_CTA_SIZE_OF_EQUALS(osWaitForever, millisec);

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    millisec = _get_timeout(waitTimeoutMs);

    res = osSemaphoreAcquire(semaphorePtr->osSemaphoreId, millisec);

#if (tskKERNEL_VERSION_MAJOR == 10) && (tskKERNEL_VERSION_MINOR == 3) && (tskKERNEL_VERSION_BUILD == 1)
    if (osEventTimeout == res) {
#elif (tskKERNEL_VERSION_MAJOR == 10) && (tskKERNEL_VERSION_MINOR == 5) && (tskKERNEL_VERSION_BUILD == 1)
    if (osErrorTimeout == res) {
#elif (tskKERNEL_VERSION_MAJOR == 10) && (tskKERNEL_VERSION_MINOR == 6) && (tskKERNEL_VERSION_BUILD == 2)
    if (osErrorTimeout == res) {
#endif
        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    if (__CMSIS_RTOS_SEMAPHORE_ACQUIRE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_SemaphoreCb_Release(
                void*       const   inputSemaphorePtr) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;
    osStatus_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osSemaphoreId_t, ((tommRoC_mw_template_semaphore_t*)NULL)->osSemaphoreId);

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    res = osSemaphoreRelease(semaphorePtr->osSemaphoreId);

    if (__CMSIS_RTOS_SEMAPHORE_RELEASE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_SemaphoreCb_Destroy(
                void*       const   inputSemaphorePtr) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;
    osStatus_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osSemaphoreId_t, ((tommRoC_mw_template_semaphore_t*)NULL)->osSemaphoreId);

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    res = osSemaphoreDelete(semaphorePtr->osSemaphoreId);

    if (__CMSIS_RTOS_SEMAPHORE_DELETE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
