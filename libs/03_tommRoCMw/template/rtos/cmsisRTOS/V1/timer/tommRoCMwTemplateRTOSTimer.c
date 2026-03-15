
#if defined (__TOMMROC_MW_USE_TIMER_CMSIS_V1_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSTimer.h"

#include "rtos/cmsisRTOS/V1/timer/callback/tommRoCMwTemplateRTOS_CMSIS_RTOS_TimerCb.h"

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

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSTimerStart(void) {

    tommRoC_mw_timer_environment_init_t mwTimerInit = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_mw_timer_environment_init_t);

    mwTimerInit.create  = tommRoCMwTemplateRTOS_CMSIS_RTOS_TimerCb_Create;
    mwTimerInit.destroy = tommRoCMwTemplateRTOS_CMSIS_RTOS_TimerCb_Destroy;
    mwTimerInit.start   = tommRoCMwTemplateRTOS_CMSIS_RTOS_TimerCb_Start;
    mwTimerInit.stop    = tommRoCMwTemplateRTOS_CMSIS_RTOS_TimerCb_Stop;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTimerEnvironmentInit(&mwTimerInit));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSTimerStop(void) {

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTimerCloseEnvironment());

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
