
#if defined (__TOMMROC_MW_USE_EVENT_CMSIS_V1_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSEvent.h"

#include "rtos/cmsisRTOS/V1/event/callback/tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb.h"

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

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSEventStart(void) {

    tommRoC_mw_event_environment_init_t mwEventInit = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_mw_event_environment_init_t);

    mwEventInit.create      = tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Create;
    mwEventInit.signal      = tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Signal;
    mwEventInit.wait        = tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Wait;
    mwEventInit.waitForAll  = tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_WaitForAll;
    mwEventInit.waitForAny  = tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_WaitForAny;
    mwEventInit.clear       = tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Clear;
    mwEventInit.destroy     = tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Destroy;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Init());

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwEventEnvironmentInit(&mwEventInit));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSEventStop(void) {

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwEventCloseEnvironment());

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Close());

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
