
#if defined (__TOMMROC_MW_USE_THREAD_CMSIS_V2_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSThread.h"

#include "rtos/cmsisRTOS/V2/thread/callback/tommRoCMwTemplateRTOS_CMSIS_RTOS_ThreadCb.h"
#include "rtos/cmsisRTOS/V2/thread/os/tommRoCMwTemplateRTOS_CMSIS_RTOS_Os.h"

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

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSThreadStart(void) {

    tommRoC_mw_thread_environment_init_t mwThreadInit = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_mw_thread_environment_init_t);

    mwThreadInit.create     = tommRoCMwTemplateRTOS_CMSIS_RTOS_ThreadCb_Create;
    mwThreadInit.getID      = tommRoCMwTemplateRTOS_CMSIS_RTOS_ThreadCb_GetID;
    mwThreadInit.destroy    = tommRoCMwTemplateRTOS_CMSIS_RTOS_ThreadCb_Destroy;
    mwThreadInit.exit       = tommRoCMwTemplateRTOS_CMSIS_RTOS_ThreadCb_Exit;
    mwThreadInit.yield      = tommRoCMwTemplateRTOS_CMSIS_RTOS_ThreadCb_Yield;
    mwThreadInit.suspendAll = tommRoCMwTemplateRTOS_CMSIS_RTOS_ThreadCb_SuspendAll;
    mwThreadInit.resumeAll  = tommRoCMwTemplateRTOS_CMSIS_RTOS_ThreadCb_ResumeAll;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwThreadEnvironmentInit(&mwThreadInit));

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOS_CMSIS_RTOS_OsStart());

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSThreadStop(void) {

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOS_CMSIS_RTOS_OsStop());

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwThreadCloseEnvironment());

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
