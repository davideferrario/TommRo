
#if defined (__TOMMROC_MW_USE_MUTEX_THREADX_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSMutex.h"

#include "rtos/threadX/mutex/callback/tommRoCMwTemplateRTOS_ThreadX_MutexCb.h"

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

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSMutexStart(void) {

    tommRoC_mw_mutex_environment_init_t mwMutexInit = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_mw_mutex_environment_init_t);

    mwMutexInit.create          = tommRoCMwTemplateRTOS_ThreadX_MutexCb_Create;
    mwMutexInit.createRecursive = tommRoCMwTemplateRTOS_ThreadX_MutexCb_CreateRecursive;
    mwMutexInit.lock            = tommRoCMwTemplateRTOS_ThreadX_MutexCb_Lock;
    mwMutexInit.unLock          = tommRoCMwTemplateRTOS_ThreadX_MutexCb_UnLock;
    mwMutexInit.destroy         = tommRoCMwTemplateRTOS_ThreadX_MutexCb_Destroy;

    return tommRoCMwMutexEnvironmentInit(&mwMutexInit);
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSMutexStop(void) {

    return tommRoCMwMutexCloseEnvironment();
}

#endif
