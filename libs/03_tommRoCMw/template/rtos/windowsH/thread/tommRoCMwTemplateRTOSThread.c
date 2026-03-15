
#if defined (__TOMMROC_MW_USE_THREAD_WINDOWS_H_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSThread.h"

#include "rtos/windowsH/thread/callback/tommRoCMwTemplateRTOS_Windows_h_ThreadCb.h"
#include "rtos/windowsH/thread/os/tommRoCMwTemplateRTOS_Windows_h_Os.h"

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

    mwThreadInit.create     = tommRoCMwTemplateRTOS_Windows_h_ThreadCb_Create;
    mwThreadInit.destroy    = tommRoCMwTemplateRTOS_Windows_h_ThreadCb_Destroy;
    mwThreadInit.exit       = tommRoCMwTemplateRTOS_Windows_h_ThreadCb_Exit;
    mwThreadInit.join       = tommRoCMwTemplateRTOS_Windows_h_ThreadCb_Join;
    mwThreadInit.tryJoin    = tommRoCMwTemplateRTOS_Windows_h_ThreadCb_TryJoin;
    mwThreadInit.yield      = tommRoCMwTemplateRTOS_Windows_h_ThreadCb_Yield;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwThreadEnvironmentInit(&mwThreadInit));

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOS_Windows_h_OsStart());

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSThreadStop(void) {

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOS_Windows_h_OsStop());

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwThreadCloseEnvironment());

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
