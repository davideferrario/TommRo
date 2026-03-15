
#if defined (__TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSThread.h"

#include "rtos/nxpOSA/thread/callback/tommRoCMwTemplateRTOS_NXP_OSA_ThreadCb.h"
#include "rtos/nxpOSA/thread/os/tommRoCMwTemplateRTOS_NXP_OSA_Os.h"

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

    mwThreadInit.create     = tommRoCMwTemplateRTOS_NXP_OSA_ThreadCb_Create;
    mwThreadInit.getID      = tommRoCMwTemplateRTOS_NXP_OSA_ThreadCb_GetID;
    mwThreadInit.destroy    = tommRoCMwTemplateRTOS_NXP_OSA_ThreadCb_Destroy;
    mwThreadInit.exit       = tommRoCMwTemplateRTOS_NXP_OSA_ThreadCb_Exit;
    mwThreadInit.yield      = tommRoCMwTemplateRTOS_NXP_OSA_ThreadCb_Yield;
    mwThreadInit.suspendAll = tommRoCMwTemplateRTOS_NXP_OSA_ThreadCb_SuspendAll;
    mwThreadInit.resumeAll  = tommRoCMwTemplateRTOS_NXP_OSA_ThreadCb_ResumeAll;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwThreadEnvironmentInit(&mwThreadInit));

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOS_NXP_OSA_OsStart());

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSThreadStop(void) {

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOS_NXP_OSA_OsStop());

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwThreadCloseEnvironment());

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
