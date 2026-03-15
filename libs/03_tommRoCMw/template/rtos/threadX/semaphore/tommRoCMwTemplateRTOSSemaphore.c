
#if defined (__TOMMROC_MW_USE_SEMAPHORE_THREADX_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSSemaphore.h"

#include "rtos/threadX/semaphore/callback/tommRoCMwTemplateRTOS_ThreadX_SemaphoreCb.h"

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

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSSemaphoreStart(void) {

    tommRoC_mw_semaphore_environment_init_t mwSemaphoreInit = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_mw_semaphore_environment_init_t);

    mwSemaphoreInit.create  = tommRoCMwTemplateRTOS_ThreadX_SemaphoreCb_Create;
    mwSemaphoreInit.wait    = tommRoCMwTemplateRTOS_ThreadX_SemaphoreCb_Wait;
    mwSemaphoreInit.release = tommRoCMwTemplateRTOS_ThreadX_SemaphoreCb_Release;
    mwSemaphoreInit.destroy = tommRoCMwTemplateRTOS_ThreadX_SemaphoreCb_Destroy;

    return tommRoCMwSemaphoreEnvironmentInit(&mwSemaphoreInit);
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSSemaphoreStop(void) {

    return tommRoCMwSemaphoreCloseEnvironment();
}

#endif
