
#if defined (__TOMMROC_MW_USE_SEMAPHORE_CMSIS_V1_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSSemaphore.h"

#include "rtos/cmsisRTOS/V1/semaphore/callback/tommRoCMwTemplateRTOS_CMSIS_RTOS_SemaphoreCb.h"

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

    mwSemaphoreInit.create  = tommRoCMwTemplateRTOS_CMSIS_RTOS_SemaphoreCb_Create;
    mwSemaphoreInit.wait    = tommRoCMwTemplateRTOS_CMSIS_RTOS_SemaphoreCb_Wait;
    mwSemaphoreInit.release = tommRoCMwTemplateRTOS_CMSIS_RTOS_SemaphoreCb_Release;
    mwSemaphoreInit.destroy = tommRoCMwTemplateRTOS_CMSIS_RTOS_SemaphoreCb_Destroy;

    return tommRoCMwSemaphoreEnvironmentInit(&mwSemaphoreInit);
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSSemaphoreStop(void) {

    return tommRoCMwSemaphoreCloseEnvironment();
}

#endif
