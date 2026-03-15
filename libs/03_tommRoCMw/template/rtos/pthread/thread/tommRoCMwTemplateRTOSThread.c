
#if defined (__TOMMROC_MW_USE_THREAD_PTHREAD_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSThread.h"

#include "rtos/pthread/thread/callback/tommRoCMwTemplateRTOS_Pthread_ThreadCb.h"
#include "rtos/pthread/thread/os/tommRoCMwTemplateRTOS_Pthread_Os.h"

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

    mwThreadInit.create     = tommRoCMwTemplateRTOS_Pthread_ThreadCb_Create;
    mwThreadInit.getID      = tommRoCMwTemplateRTOS_Pthread_ThreadCb_GetID;
    mwThreadInit.destroy    = tommRoCMwTemplateRTOS_Pthread_ThreadCb_Destroy;
    mwThreadInit.exit       = tommRoCMwTemplateRTOS_Pthread_ThreadCb_Exit;
    mwThreadInit.join       = tommRoCMwTemplateRTOS_Pthread_ThreadCb_Join;
    mwThreadInit.yield      = tommRoCMwTemplateRTOS_Pthread_ThreadCb_Yield;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwThreadEnvironmentInit(&mwThreadInit));

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOS_Pthread_OsStart());

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSThreadStop(void) {

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOS_Pthread_OsStop());

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwThreadCloseEnvironment());

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
