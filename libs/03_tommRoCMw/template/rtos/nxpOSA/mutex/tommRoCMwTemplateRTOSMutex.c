
#if defined (__TOMMROC_MW_USE_MUTEX_NXP_OSA_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSMutex.h"

#include "rtos/nxpOSA/mutex/callback/tommRoCMwTemplateRTOS_NXP_OSA_MutexCb.h"

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

    mwMutexInit.create          = tommRoCMwTemplateRTOS_NXP_OSA_MutexCb_Create;
    mwMutexInit.createRecursive = tommRoCMwTemplateRTOS_NXP_OSA_MutexCb_CreateRecursive;
    mwMutexInit.lock            = tommRoCMwTemplateRTOS_NXP_OSA_MutexCb_Lock;
    mwMutexInit.unLock          = tommRoCMwTemplateRTOS_NXP_OSA_MutexCb_UnLock;
    mwMutexInit.destroy         = tommRoCMwTemplateRTOS_NXP_OSA_MutexCb_Destroy;

    return tommRoCMwMutexEnvironmentInit(&mwMutexInit);
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSMutexStop(void) {

    return tommRoCMwMutexCloseEnvironment();
}

#endif
