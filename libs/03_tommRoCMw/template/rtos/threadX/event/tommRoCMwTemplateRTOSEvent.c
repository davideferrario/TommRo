
#if defined (__TOMMROC_MW_USE_EVENT_THREADX_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSEvent.h"

#include "rtos/threadX/event/callback/tommRoCMwTemplateRTOS_ThreadX_EventCb.h"

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

    mwEventInit.create      = tommRoCMwTemplateRTOS_ThreadX_EventCb_Create;
    mwEventInit.signal      = tommRoCMwTemplateRTOS_ThreadX_EventCb_Signal;
    mwEventInit.wait        = tommRoCMwTemplateRTOS_ThreadX_EventCb_Wait;
    mwEventInit.waitForAll  = tommRoCMwTemplateRTOS_ThreadX_EventCb_WaitForAll;
    mwEventInit.waitForAny  = tommRoCMwTemplateRTOS_ThreadX_EventCb_WaitForAny;
    mwEventInit.clear       = tommRoCMwTemplateRTOS_ThreadX_EventCb_Clear;
    mwEventInit.destroy     = tommRoCMwTemplateRTOS_ThreadX_EventCb_Destroy;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOS_ThreadX_EventCb_Init());

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwEventEnvironmentInit(&mwEventInit));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSEventStop(void) {

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwEventCloseEnvironment());

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOS_ThreadX_EventCb_Close());

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
