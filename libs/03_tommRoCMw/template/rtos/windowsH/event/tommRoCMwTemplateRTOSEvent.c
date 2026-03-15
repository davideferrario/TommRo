
#if defined (__TOMMROC_MW_USE_EVENT_WINDOWS_H_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSEvent.h"

#include "rtos/windowsH/event/callback/tommRoCMwTemplateRTOS_Windows_h_EventCb.h"

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

    mwEventInit.create      = tommRoCMwTemplateRTOS_Windows_h_EventCb_Create;
    mwEventInit.signal      = tommRoCMwTemplateRTOS_Windows_h_EventCb_Signal;
    mwEventInit.waitForAll  = tommRoCMwTemplateRTOS_Windows_h_EventCb_WaitForAll;
    mwEventInit.waitForAny  = tommRoCMwTemplateRTOS_Windows_h_EventCb_WaitForAny;
    mwEventInit.clear       = tommRoCMwTemplateRTOS_Windows_h_EventCb_Clear;
    mwEventInit.destroy     = tommRoCMwTemplateRTOS_Windows_h_EventCb_Destroy;

    return tommRoCMwEventEnvironmentInit(&mwEventInit);
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSEventStop(void) {

    return tommRoCMwEventCloseEnvironment();
}

#endif
