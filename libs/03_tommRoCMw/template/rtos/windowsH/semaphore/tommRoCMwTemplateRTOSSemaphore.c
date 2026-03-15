
#if defined (__TOMMROC_MW_USE_SEMAPHORE_WINDOWS_H_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSSemaphore.h"

#include "rtos/windowsH/semaphore/callback/tommRoCMwTemplateRTOS_Windows_h_SemaphoreCb.h"

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

    mwSemaphoreInit.create  = tommRoCMwTemplateRTOS_Windows_h_SemaphoreCb_Create;
    mwSemaphoreInit.wait    = tommRoCMwTemplateRTOS_Windows_h_SemaphoreCb_Wait;
    mwSemaphoreInit.signal  = tommRoCMwTemplateRTOS_Windows_h_SemaphoreCb_Signal;
    mwSemaphoreInit.destroy = tommRoCMwTemplateRTOS_Windows_h_SemaphoreCb_Destroy;

    return tommRoCMwSemaphoreEnvironmentInit(&mwSemaphoreInit);
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSSemaphoreStop(void) {

    return tommRoCMwSemaphoreCloseEnvironment();
}

#endif
