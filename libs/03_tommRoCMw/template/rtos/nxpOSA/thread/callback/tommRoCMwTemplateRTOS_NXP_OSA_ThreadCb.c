
#if defined (__TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_NXP_OSA_ThreadCb.h"

#include "rtos/nxpOSA/common/compatibility/tommRoCMwTemplateRTOS_NXP_OSA_Compatibility.h"

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
static osaTaskPriority_t _convert_priority(const tommRoC_mw_thread_priority_enum_t priority) {

    switch (priority) {

    case TOMMRO_C_MW_THREAD_PRIORITY_IDLE:          return OSA_PRIORITY_IDLE;
    case TOMMRO_C_MW_THREAD_PRIORITY_LOW:           return OSA_PRIORITY_LOW;
    case TOMMRO_C_MW_THREAD_PRIORITY_BELOW_NORMAL:  return OSA_PRIORITY_BELOW_NORMAL;
    case TOMMRO_C_MW_THREAD_PRIORITY_NORMAL:        return OSA_PRIORITY_NORMAL;
    case TOMMRO_C_MW_THREAD_PRIORITY_ABOVE_NORMAL:  return OSA_PRIORITY_ABOVE_NORMAL;
    case TOMMRO_C_MW_THREAD_PRIORITY_HIGH:          return OSA_PRIORITY_HIGH;
    case TOMMRO_C_MW_THREAD_PRIORITY_REALTIME:      return OSA_PRIORITY_REAL_TIME;
    case TOMMRO_C_MW_THREAD_PRIORITY_DEFAULT:       return OSA_PRIORITY_NORMAL;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;

    }

    return OSA_TASK_PRIORITY_MIN;
}

static uint32_t _convert_stack_size(const uint32_t stackSize) {

    if (TOMMRO_C_MW_THREAD_STACK_SIZE_DEFAULT == stackSize) {
        return (uint32_t) __NXP_OSA_THREAD_STACK_SIZE_DEFAULT__;
    }

    return (uint32_t) stackSize;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_ThreadCb_Create(
        const   tommRoC_mw_thread_main_funct_t          mainThread,
                void*                           const   mainThreadArgPtr,
        const   char*                           const   threadNameStrPtr,
        const   tommRoC_mw_thread_config_t*     const   configPtr,
                void*                           const   inputThreadPtr) {

    static const char defaultThreadNameStr[] = "thread";
    TOMMROC_CTA_LESS_THAN(TOMMROC_UTIL_STRING_ARR_LENGTH(defaultThreadNameStr), configMAX_TASK_NAME_LEN);

    tommRoC_mw_template_thread_t* threadPtr;
    osaTaskPriority_t priority;
    uint32_t stackSize;

    uint16_t threadNameStrLen;

    TOMMROC_CTA_SIZE_OF_EQUALS(osaTaskId_t, ((tommRoC_mw_template_thread_t*)NULL)->osaTaskId);

    threadPtr = (tommRoC_mw_template_thread_t*) inputThreadPtr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(threadPtr, 0x00, sizeof(tommRoC_mw_template_thread_t)));

    priority    = _convert_priority(configPtr->priority);
    stackSize   = _convert_stack_size(configPtr->stackSize);

    if (NULL != threadNameStrPtr) {
        threadNameStrLen = tommRoCStringStrLen(threadNameStrPtr);
        if (threadNameStrLen >= configMAX_TASK_NAME_LEN) {
            return TOMMRO_C_MW_PARAM_ERR;
        }
    }

    threadPtr->osaThreadDef.pthread     = (osaTaskPtr_t) mainThread;
    threadPtr->osaThreadDef.tpriority   = (uint32_t) priority;
    threadPtr->osaThreadDef.instances   = 1;
    threadPtr->osaThreadDef.stacksize   = stackSize * sizeof(portSTACK_TYPE);
    threadPtr->osaThreadDef.tstack      = NULL;
    threadPtr->osaThreadDef.tlink       = NULL;
    threadPtr->osaThreadDef.tname       = (uint8_t*) ((NULL != threadNameStrPtr) ? (threadNameStrPtr) : (defaultThreadNameStr));
    threadPtr->osaThreadDef.useFloat    = TRUE;

    threadPtr->osaTaskId = OSA_TaskCreate(&threadPtr->osaThreadDef, (osaTaskParam_t) mainThreadArgPtr);

    if (__NXP_OSA_TASK_CREATE_ON_ERROR_RESULT__ == threadPtr->osaTaskId) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_ThreadCb_GetID(
                void*   const   inputThreadIDPtr) {

    tommRoC_mw_template_thread_id_t* threadIDPtr;
    osaTaskId_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osaTaskId_t, tommRoC_mw_template_thread_id_t);

    threadIDPtr = (tommRoC_mw_template_thread_id_t*) inputThreadIDPtr;

    res = OSA_TaskGetId();

    if (__NXP_OSA_TASK_GET_ID_ON_ERROR_RESULT__ == res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopySafe(threadIDPtr, sizeof(tommRoC_mw_template_thread_id_t), &res, sizeof(osaTaskId_t), sizeof(res)));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_ThreadCb_Destroy(
                void*   const   inputThreadPtr) {

    tommRoC_mw_template_thread_t* threadPtr;
    osaStatus_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(osaTaskId_t, ((tommRoC_mw_template_thread_t*)NULL)->osaTaskId);

    threadPtr = (tommRoC_mw_template_thread_t*) inputThreadPtr;

    res = OSA_TaskDestroy(threadPtr->osaTaskId);

    if (__NXP_OSA_TASK_DESTROY_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_ThreadCb_Exit(void) {

    osaTaskId_t osaTaskId;
    osaStatus_t res;

    osaTaskId = OSA_TaskGetId();

    if (__NXP_OSA_TASK_GET_ID_ON_ERROR_RESULT__ == osaTaskId) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    res = OSA_TaskDestroy(osaTaskId);

    if (__NXP_OSA_TASK_DESTROY_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

void tommRoCMwTemplateRTOS_NXP_OSA_ThreadCb_Yield(void) {

    TOMMROC_ASSERT_EQUALS(OSA_TaskYield(), __NXP_OSA_TASK_YIELD_SUCCESS_RESULT__);
}

void tommRoCMwTemplateRTOS_NXP_OSA_ThreadCb_SuspendAll(void) {

    vTaskSuspendAll();
}

void tommRoCMwTemplateRTOS_NXP_OSA_ThreadCb_ResumeAll(void) {

    if(!xTaskResumeAll()) {
        TOMMROC_ASSERT_EQUALS(OSA_TaskYield(), __NXP_OSA_TASK_YIELD_SUCCESS_RESULT__);
    }
}

#endif
