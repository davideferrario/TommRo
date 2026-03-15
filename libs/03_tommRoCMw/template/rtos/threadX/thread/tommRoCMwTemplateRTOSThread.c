
#if defined (__TOMMROC_MW_USE_THREAD_THREADX_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSThread.h"

#include "rtos/threadX/thread/callback/tommRoCMwTemplateRTOS_ThreadX_ThreadCb.h"
#include "rtos/threadX/thread/os/tommRoCMwTemplateRTOS_ThreadX_Os.h"

#include "rtos/threadX/common/hook/tommRoCMwTemplateRTOS_ThreadX_Hook.h"

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

    mwThreadInit.create     = tommRoCMwTemplateRTOS_ThreadX_ThreadCb_Create;
    mwThreadInit.getID      = tommRoCMwTemplateRTOS_ThreadX_ThreadCb_GetID;
    mwThreadInit.destroy    = tommRoCMwTemplateRTOS_ThreadX_ThreadCb_Destroy;
    mwThreadInit.exit       = tommRoCMwTemplateRTOS_ThreadX_ThreadCb_Exit;
    mwThreadInit.yield      = tommRoCMwTemplateRTOS_ThreadX_ThreadCb_Yield;
    mwThreadInit.suspendAll = tommRoCMwTemplateRTOS_ThreadX_ThreadCb_SuspendAll;
    mwThreadInit.resumeAll  = tommRoCMwTemplateRTOS_ThreadX_ThreadCb_ResumeAll;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwThreadEnvironmentInit(&mwThreadInit));

#if defined(TX_ENABLE_STACK_CHECKING) || defined(TX_PORT_THREAD_STACK_ERROR_HANDLING)
    if (TX_SUCCESS != tx_thread_stack_error_notify(tommRoCMwTemplateRTOS_ThreadX_HookStackOverflowStackErrorHandler)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }
#endif

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOS_ThreadX_OsStart());

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSThreadStop(void) {

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOS_ThreadX_OsStop());

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwThreadCloseEnvironment());

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
