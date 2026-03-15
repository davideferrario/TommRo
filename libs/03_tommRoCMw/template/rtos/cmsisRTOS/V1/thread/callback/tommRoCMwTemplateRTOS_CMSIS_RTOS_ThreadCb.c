
#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V1_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_CMSIS_RTOS_ThreadCb.h"

#include "rtos/cmsisRTOS/V1/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_EXTERNAL_IS_USED__)
#include "rtos/cmsisRTOS/V1/common/critical/tommRoCMwTemplateRTOS_CMSIS_RTOS_Critical.h"
#endif

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
static osPriority _convert_priority(const tommRoC_mw_thread_priority_enum_t priority) {

    switch (priority) {

    case TOMMRO_C_MW_THREAD_PRIORITY_IDLE:          return osPriorityIdle;
    case TOMMRO_C_MW_THREAD_PRIORITY_LOW:           return osPriorityLow;
    case TOMMRO_C_MW_THREAD_PRIORITY_BELOW_NORMAL:  return osPriorityBelowNormal;
    case TOMMRO_C_MW_THREAD_PRIORITY_NORMAL:        return osPriorityNormal;
    case TOMMRO_C_MW_THREAD_PRIORITY_ABOVE_NORMAL:  return osPriorityAboveNormal;
    case TOMMRO_C_MW_THREAD_PRIORITY_HIGH:          return osPriorityHigh;
    case TOMMRO_C_MW_THREAD_PRIORITY_REALTIME:      return osPriorityRealtime;
    case TOMMRO_C_MW_THREAD_PRIORITY_DEFAULT:       return osPriorityNormal;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;

    }

    return osPriorityError;
}

static uint32_t _convert_stack_size(const uint32_t stackSize) {

    if (TOMMRO_C_MW_THREAD_STACK_SIZE_DEFAULT == stackSize) {
        return (uint32_t) __CMSIS_RTOS_THREAD_STACK_SIZE_DEFAULT__;
    }

    return (uint32_t) stackSize;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_ThreadCb_Create(
        const   tommRoC_mw_thread_main_funct_t          mainThread,
                void*                           const   mainThreadArgPtr,
        const   char*                           const   threadNameStrPtr,
        const   tommRoC_mw_thread_config_t*     const   configPtr,
                void*                           const   inputThreadPtr) {

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
    static const char defaultThreadNameStr[] = "thread";
    TOMMROC_CTA_LESS_THAN(TOMMROC_UTIL_STRING_ARR_LENGTH(defaultThreadNameStr), configMAX_TASK_NAME_LEN);
#endif

    tommRoC_mw_template_thread_t* threadPtr;
    osPriority priority;
    uint32_t stackSize;

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
    uint16_t threadNameStrLen;
#endif

    TOMMROC_CTA_SIZE_OF_EQUALS(osThreadId, ((tommRoC_mw_template_thread_t*)NULL)->osThreadId);

#if !defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
    TOMMROC_UTIL_UNUSED_PARAM(threadNameStrPtr);
#endif

    threadPtr = (tommRoC_mw_template_thread_t*) inputThreadPtr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(threadPtr, 0x00, sizeof(tommRoC_mw_template_thread_t)));

    priority    = _convert_priority(configPtr->priority);
    stackSize   = _convert_stack_size(configPtr->stackSize);

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
    if (NULL != threadNameStrPtr) {
        threadNameStrLen = tommRoCStringStrLen(threadNameStrPtr);
        if (threadNameStrLen >= configMAX_TASK_NAME_LEN) {
            return TOMMRO_C_MW_PARAM_ERR;
        }
    }
    threadPtr->osThreadDef.name = (char*) ((NULL != threadNameStrPtr) ? (threadNameStrPtr) : (defaultThreadNameStr));
#endif

    threadPtr->osThreadDef.pthread      = (os_pthread) mainThread;
    threadPtr->osThreadDef.tpriority    = priority;
    threadPtr->osThreadDef.instances    = 0;
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
    threadPtr->osThreadDef.stacksize    = stackSize * sizeof(uint16_t) * sizeof(uint32_t);
#else
    threadPtr->osThreadDef.stacksize    = stackSize;
#endif

    threadPtr->osThreadId = osThreadCreate(&threadPtr->osThreadDef, (void*) mainThreadArgPtr);

    if (__CMSIS_RTOS_THREAD_CREATE_ON_ERROR_RESULT__ == threadPtr->osThreadId) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_ThreadCb_GetID(
                void*   const   inputThreadIDPtr) {

    tommRoC_mw_template_thread_id_t* threadIDPtr;
    osThreadId res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osThreadId, tommRoC_mw_template_thread_id_t);

    threadIDPtr = (tommRoC_mw_template_thread_id_t*) inputThreadIDPtr;

    res = osThreadGetId();

    if (__CMSIS_RTOS_THREAD_GET_ID_ON_ERROR_RESULT__ == res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopySafe(threadIDPtr, sizeof(tommRoC_mw_template_thread_id_t), &res, sizeof(osThreadId), sizeof(res)));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_ThreadCb_Destroy(
                void*   const   inputThreadPtr) {

    tommRoC_mw_template_thread_t* threadPtr;
    osStatus res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osThreadId, ((tommRoC_mw_template_thread_t*)NULL)->osThreadId);

    threadPtr = (tommRoC_mw_template_thread_t*) inputThreadPtr;

    res = osThreadTerminate(threadPtr->osThreadId);

    if (__CMSIS_RTOS_THREAD_TERMINATE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_ThreadCb_Exit(void) {

    osThreadTerminate(NULL);

    // NOTE: it will never get here because pthread_exit is no-return function.
    TOMMROC_ASSERT_TRUE(false);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

void tommRoCMwTemplateRTOS_CMSIS_RTOS_ThreadCb_Yield(void) {

    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(osThreadYield(), __CMSIS_RTOS_THREAD_YIELD_SUCCESS_RESULT__);
}

void tommRoCMwTemplateRTOS_CMSIS_RTOS_ThreadCb_SuspendAll(void) {

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_EXTERNAL_IS_USED__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCMwTemplateRTOS_CMSIS_RTOS_CriticalEnter());

#elif defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(osThreadSuspendAll(), __CMSIS_RTOS_THREAD_SUSPEND_ALL_SUCCESS_RESULT__);

#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_INTERNAL_TEMPLATE_IS_USED__)
    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(osThreadSuspendAll(), __CMSIS_RTOS_THREAD_SUSPEND_ALL_SUCCESS_RESULT__);
#endif
}

void tommRoCMwTemplateRTOS_CMSIS_RTOS_ThreadCb_ResumeAll(void) {

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_EXTERNAL_IS_USED__)
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCMwTemplateRTOS_CMSIS_RTOS_CriticalExit());

#elif defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
    osThreadResumeAll();

#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_INTERNAL_TEMPLATE_IS_USED__)
    osThreadResumeAll();
#endif
}

#endif
