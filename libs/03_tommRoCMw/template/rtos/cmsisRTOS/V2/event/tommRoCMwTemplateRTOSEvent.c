
#if defined (__TOMMROC_MW_USE_EVENT_CMSIS_V2_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSEvent.h"

#include "rtos/cmsisRTOS/V2/event/callback/tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb.h"

#include "rtos/cmsisRTOS/V2/event/enumeration/tommRoCMwTemplateRTOSCmsisRTOSEventEnumeration.h"
#include "rtos/cmsisRTOS/V2/event/threadEventTable/tommRoCMwTemplateRTOSCmsisRTOSEventThreadEventTable.h"

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

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOSCmsisRTOSEventEnumerationStart());

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOSCmsisRTOSEventThreadEventTableStart());

    mwEventInit.create      = tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Create;
    mwEventInit.signal      = tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Signal;
    mwEventInit.waitForAll  = tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_WaitForAll;
    mwEventInit.waitForAny  = tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_WaitForAny;
    mwEventInit.clear       = tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Clear;
    mwEventInit.destroy     = tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Destroy;

    return tommRoCMwEventEnvironmentInit(&mwEventInit);
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSEventStop(void) {

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOSCmsisRTOSEventEnumerationStop());

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOSCmsisRTOSEventThreadEventTableStop());

    return tommRoCMwEventCloseEnvironment();
}

#endif
