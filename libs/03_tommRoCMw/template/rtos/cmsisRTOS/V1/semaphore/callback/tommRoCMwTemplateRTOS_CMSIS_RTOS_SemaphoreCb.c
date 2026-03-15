
#if defined (__TOMMROC_MW_USE_SEMAPHORE_CMSIS_V1_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_CMSIS_RTOS_SemaphoreCb.h"

#include "rtos/cmsisRTOS/V1/common/CMSIS_RTOS/tommRoCMwTemplateRTOS_cmsis_os.h"
#include "rtos/cmsisRTOS/V1/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"

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

    TOMMROC_CTA_SIZE_OF_EQUALS(osSemaphoreDef_t,    ((tommRoC_mw_template_semaphore_t*)NULL)->osSemaphoreDef);
    TOMMROC_CTA_SIZE_OF_EQUALS(osSemaphoreId,       ((tommRoC_mw_template_semaphore_t*)NULL)->osSemaphoreId);

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&semaphorePtr->osSemaphoreDef, 0x00, sizeof(semaphorePtr->osSemaphoreDef)));

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
        semaphorePtr->osSemaphoreId = osSemaphoreCreate(&semaphorePtr->osSemaphoreDef, availableRes);
    }
#else
#if defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
    // NOTE: ESP32 does not support native 0-count semaphote. Use this workaround.
    if (0 != availableRes) {
        semaphorePtr->osSemaphoreId = osSemaphoreCreate(&semaphorePtr->osSemaphoreDef, availableRes);
    }
    else {
        semaphorePtr->osSemaphoreId = osSemaphoreCreate(&semaphorePtr->osSemaphoreDef, 1);
        if (__CMSIS_RTOS_SEMAPHORE_CREATE_ON_ERROR_RESULT__ == semaphorePtr->osSemaphoreId) {
            return TOMMRO_C_MW_LOW_LEVEL_ERR;
        }
        if (osOK != osSemaphoreWait(semaphorePtr->osSemaphoreId, 0)) {
            return TOMMRO_C_MW_LOW_LEVEL_ERR;
        }
    }
#else
    semaphorePtr->osSemaphoreId = osSemaphoreCreate(&semaphorePtr->osSemaphoreDef, availableRes);
#endif
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
    int32_t res;
    uint32_t millisec;
#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
    osStatus convertedRes;
#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
    int32_t convertedRes;
#endif

    TOMMROC_CTA_SIZE_OF_EQUALS(osSemaphoreId, ((tommRoC_mw_template_semaphore_t*)NULL)->osSemaphoreId);

    TOMMROC_CTA_SIZE_OF_EQUALS(osWaitForever, millisec);

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    millisec = _get_timeout(waitTimeoutMs);

    res = osSemaphoreWait(semaphorePtr->osSemaphoreId, millisec);

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
    convertedRes = (osStatus) res;
#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
    convertedRes = res;
#endif

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
    if (osOK != convertedRes) {
#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
    if (convertedRes < 1) {
#endif
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_SemaphoreCb_Release(
                void*       const   inputSemaphorePtr) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;
    osStatus res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osSemaphoreId, ((tommRoC_mw_template_semaphore_t*)NULL)->osSemaphoreId);

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    res = osSemaphoreRelease(semaphorePtr->osSemaphoreId);

    if (osOK != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_SemaphoreCb_Destroy(
                void*       const   inputSemaphorePtr) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;
    osStatus res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osSemaphoreId, ((tommRoC_mw_template_semaphore_t*)NULL)->osSemaphoreId);

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    res = osSemaphoreDelete(semaphorePtr->osSemaphoreId);

    if (__CMSIS_RTOS_SEMAPHORE_DELETE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
