
#if defined (__TOMMROC_MW_USE_THREAD_WINDOWS_H_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_Windows_h_ThreadCb.h"

#include "rtos/windowsH/common/tommRoCMwTemplateRTOS_Windows_h_Common.h"

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
static int _convert_priority(const tommRoC_mw_thread_priority_enum_t priority) {

    switch (priority) {

    case TOMMRO_C_MW_THREAD_PRIORITY_IDLE:
        return THREAD_PRIORITY_IDLE;

    case TOMMRO_C_MW_THREAD_PRIORITY_LOW:
        return THREAD_PRIORITY_LOWEST;

    case TOMMRO_C_MW_THREAD_PRIORITY_BELOW_NORMAL:
        return THREAD_PRIORITY_BELOW_NORMAL;

    case TOMMRO_C_MW_THREAD_PRIORITY_NORMAL:
        return THREAD_PRIORITY_NORMAL;

    case TOMMRO_C_MW_THREAD_PRIORITY_ABOVE_NORMAL:
        return THREAD_PRIORITY_ABOVE_NORMAL;

    case TOMMRO_C_MW_THREAD_PRIORITY_HIGH:
        return THREAD_PRIORITY_HIGHEST;

    case TOMMRO_C_MW_THREAD_PRIORITY_REALTIME:
        return THREAD_PRIORITY_TIME_CRITICAL;

    case TOMMRO_C_MW_THREAD_PRIORITY_DEFAULT:
        return THREAD_PRIORITY_NORMAL;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);

        break;

    }

    return THREAD_PRIORITY_NORMAL;
}

static DWORD _convert_stack_size(const uint32_t stackSize) {

    if (TOMMRO_C_MW_THREAD_STACK_SIZE_DEFAULT == stackSize) {
        return (DWORD) 0;
    }

    return (DWORD) stackSize;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_ThreadCb_Create(
        const   tommRoC_mw_thread_main_funct_t          mainThread,
        const   void*                           const   mainThreadArgPtr,
        const   char*                           const   threadNameStrPtr,
        const   tommRoC_mw_thread_config_t*     const   configPtr,
                void*                           const   inputThreadPtr) {

    tommRoC_mw_template_thread_t* threadPtr;
    int priority;
    DWORD stackSize;
    HANDLE threadResult;

    threadPtr = (tommRoC_mw_template_thread_t*) inputThreadPtr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(threadPtr, 0x00, sizeof(tommRoC_mw_template_thread_t)));

    priority    = _convert_priority(configPtr->priority);
    stackSize   = _convert_stack_size(configPtr->stackSize);

    threadResult = CreateThread(
            NULL,           // Default security attributes
            stackSize,
            (LPTHREAD_START_ROUTINE) mainThread,
            (PVOID) mainThreadArgPtr,
            0,              // Use default creation flags
            NULL);          // Thread identifier not used

    if (NULL == threadResult) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    if (NULL != threadNameStrPtr) {
        if (FAILED(SetThreadDescription(threadResult, (PCWSTR) threadNameStrPtr))) {
            return TOMMRO_C_MW_LOW_LEVEL_ERR;
        }
    }

    if (!SetThreadPriority(threadResult, priority)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    TOMMROC_CTA_SIZE_OF_EQUALS(threadPtr->handle, threadResult);
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&threadPtr->handle, &threadResult, sizeof(threadResult)));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_ThreadCb_Destroy(
                void*   const   inputThreadPtr) {

    tommRoC_mw_template_thread_t* threadPtr;

    threadPtr = (tommRoC_mw_template_thread_t*) inputThreadPtr;

    if (!TerminateThread(threadPtr->handle, 0)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCMwTemplateRTOS_Windows_h_CommonCloseHandle(
                    threadPtr->handle));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_ThreadCb_Exit(void) {
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_ThreadCb_Join(
        const   void*   const   inputThreadPtr) {

    tommRoC_mw_template_thread_t* threadPtr;

    threadPtr = (tommRoC_mw_template_thread_t*) inputThreadPtr;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCMwTemplateRTOS_Windows_h_CommonWaitForSingleObject(
                    threadPtr->handle,
                    INFINITE));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_ThreadCb_TryJoin(
        const   void*   const   inputThreadPtr) {

    tommRoC_mw_template_thread_t* threadPtr;

    threadPtr = (tommRoC_mw_template_thread_t*) inputThreadPtr;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCMwTemplateRTOS_Windows_h_CommonWaitForSingleObject(
                    threadPtr->handle,
                    0));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

void tommRoCMwTemplateRTOS_Windows_h_ThreadCb_Yield(void) {

    SwitchToThread();
}

#endif
