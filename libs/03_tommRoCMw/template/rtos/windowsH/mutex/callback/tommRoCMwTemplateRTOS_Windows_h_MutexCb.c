
#if defined (__TOMMROC_MW_USE_MUTEX_WINDOWS_H_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_Windows_h_MutexCb.h"

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

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_MutexCb_Create(
                void*   const   inputMutexPtr) {

    tommRoC_mw_template_mutex_t* mutexPtr;
    HANDLE mutexResult;

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    mutexResult = CreateMutex(
            NULL,           // Default security attributes
            FALSE,          // Initially not owned
            NULL);          // Unnamed mutex

    if (NULL == mutexResult) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    TOMMROC_CTA_SIZE_OF_EQUALS(mutexPtr->handle, mutexResult);
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&mutexPtr->handle, &mutexResult, sizeof(mutexResult)));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_MutexCb_Lock(
                void*   const   inputMutexPtr,
        const   uint32_t        waitTimeoutMs) {

    tommRoC_mw_template_mutex_t* mutexPtr;
    DWORD timeout;

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    timeout = (LOCK_MUTEX_INFINITE_TIMEOUT == waitTimeoutMs) ? ((DWORD) INFINITE) : ((DWORD) waitTimeoutMs);

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCMwTemplateRTOS_Windows_h_CommonWaitForSingleObject(
                    mutexPtr->handle,
                    timeout));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_MutexCb_UnLock(
                void*   const   inputMutexPtr) {

    tommRoC_mw_template_mutex_t* mutexPtr;

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    if (!ReleaseMutex(mutexPtr->handle)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_MutexCb_Destroy(
                void*   const   inputMutexPtr) {

    tommRoC_mw_template_mutex_t* mutexPtr;

    mutexPtr = (tommRoC_mw_template_mutex_t*) inputMutexPtr;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCMwTemplateRTOS_Windows_h_CommonCloseHandle(
                    mutexPtr->handle));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
