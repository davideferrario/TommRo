
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_Windows_h_Common.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)

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

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_CommonWaitForSingleObject(
                HANDLE  handle,
        const   DWORD   timeoutMsec) {

    DWORD res;

    res = WaitForSingleObject(handle, timeoutMsec);

    if (WAIT_TIMEOUT == res) {
        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    if (WAIT_OBJECT_0 != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_CommonWaitForMultipleObject(
        const   HANDLE* handlesPtr,
        const   DWORD   nCount,
        const   BOOL    waitAll,
        const   DWORD   timeoutMsec,
                DWORD*  signaledIndexPtr) {

    DWORD res;

    res = WaitForMultipleObjects(nCount, handlesPtr, waitAll, timeoutMsec);

    if (WAIT_TIMEOUT == res) {
        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    if (res > WAIT_OBJECT_0 + nCount - 1) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    *signaledIndexPtr = (res - WAIT_OBJECT_0);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_CommonCloseHandle(
                HANDLE  handle) {

    if (!CloseHandle(handle)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
