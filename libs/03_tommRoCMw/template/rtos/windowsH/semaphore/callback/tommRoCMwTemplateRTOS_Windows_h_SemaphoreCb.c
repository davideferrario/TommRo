
#if defined (__TOMMROC_MW_USE_SEMAPHORE_WINDOWS_H_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_Windows_h_SemaphoreCb.h"

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

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_SemaphoreCb_Create(
                void*       const   inputSemaphorePtr,
        const   uint8_t             maxValue) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;
    HANDLE semaphoreResult;

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    semaphoreResult = CreateSemaphore(
            NULL,                   // Default security attributes
            (LONG) maxValue,        // Initial count
            (LONG) maxValue,        // Maximum count
            NULL);                  // Unnamed semaphore

    if (NULL == semaphoreResult) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    TOMMROC_CTA_SIZE_OF_EQUALS(semaphorePtr->handle, semaphoreResult);
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&semaphorePtr->handle, &semaphoreResult, sizeof(semaphoreResult)));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_SemaphoreCb_Wait(
                void*       const   inputSemaphorePtr,
        const   uint32_t            waitTimeoutMs) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;
    DWORD timeout;

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    if (WAIT_SEMAPHORE_NO_WAIT_TIMEOUT == waitTimeoutMs) {
        timeout = (DWORD) 0;
    }
    else if (WAIT_SEMAPHORE_INFINITE_TIMEOUT == waitTimeoutMs) {
        timeout = (DWORD) INFINITE;
    }
    else {
        timeout = (DWORD) waitTimeoutMs;
    }

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCMwTemplateRTOS_Windows_h_CommonWaitForSingleObject(
                    semaphorePtr->handle,
                    timeout));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_SemaphoreCb_Signal(
                void*       const   inputSemaphorePtr) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    if (!ReleaseSemaphore(semaphorePtr->handle, 1, NULL)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_SemaphoreCb_Destroy(
                void*       const   inputSemaphorePtr) {

    tommRoC_mw_template_semaphore_t* semaphorePtr;

    semaphorePtr = (tommRoC_mw_template_semaphore_t*) inputSemaphorePtr;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCMwTemplateRTOS_Windows_h_CommonCloseHandle(
                    semaphorePtr->handle));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
