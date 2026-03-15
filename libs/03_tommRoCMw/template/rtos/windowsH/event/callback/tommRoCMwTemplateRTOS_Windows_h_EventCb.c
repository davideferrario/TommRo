
#if defined (__TOMMROC_MW_USE_EVENT_WINDOWS_H_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_Windows_h_EventCb.h"

#include "rtos/windowsH/common/tommRoCMwTemplateRTOS_Windows_h_Common.h"

#include "TOMMROC.h"

#include "TOMMROCMwTemplate.h"

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
static tommRoC_mw_err_enum_t _event_wait(
        const   void*   const   inputEventsPtr,
        const   uint8_t         inputEventsAmount,
        const   BOOL            waitForAll,
        const   uint32_t        waitTimeoutMs,
                DWORD*          signaledIndexPtr) {

    HANDLE* eventsPtr;
    DWORD timeout;

    eventsPtr = (HANDLE*) inputEventsPtr;

    if (WAIT_EVENT_INFINITE_TIMEOUT == waitTimeoutMs) {
        timeout = (DWORD) INFINITE;
    }
    else {
        timeout = (DWORD) waitTimeoutMs;
    }

    return tommRoCMwTemplateRTOS_Windows_h_CommonWaitForMultipleObject(
            eventsPtr,
            (DWORD) inputEventsAmount,
            waitForAll,
            timeout,
            signaledIndexPtr);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_EventCb_Create(
                void*   const   inputEventPtr) {

    HANDLE* eventPtr;
    HANDLE eventResult;

    TOMMROC_CTA_SIZE_OF_EQUALS(tommRoC_mw_template_event_t, HANDLE);

    eventPtr = (HANDLE*) inputEventPtr;

    eventResult = CreateEvent(
            NULL,           // Default security attributes
            TRUE,           // Manual-reset event
            FALSE,          // Initial state is nonsignaled
            NULL);          // Unnamed event

    if (NULL == eventResult) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(eventPtr, &eventResult, sizeof(eventResult)));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_EventCb_Signal(
                void*   const   inputEventPtr) {

    HANDLE* eventPtr;

    eventPtr = (HANDLE*) inputEventPtr;

    if (!SetEvent(*eventPtr)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_EventCb_WaitForAll(
                void*   const   inputEventsPtr,
        const   uint8_t         inputEventsAmount,
        const   uint32_t        waitTimeoutMs) {

    DWORD signaledIndex;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _event_wait(
                    inputEventsPtr,
                    inputEventsAmount,
                    TRUE,
                    waitTimeoutMs,
                    &signaledIndex));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_EventCb_WaitForAny(
                void*   const   inputEventsPtr,
        const   uint8_t         inputEventsAmount,
        const   uint32_t        waitTimeoutMs,
                void**  const   inputSignaledEventPtr) {

    DWORD signaledIndex;
    HANDLE** signaledEventPtr;

    signaledEventPtr = (HANDLE**) inputSignaledEventPtr;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _event_wait(
                    inputEventsPtr,
                    inputEventsAmount,
                    FALSE,
                    waitTimeoutMs,
                    &signaledIndex));

    *signaledEventPtr = (HANDLE*) inputEventsPtr + signaledIndex;

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_EventCb_Clear(
                void*   const   inputEventPtr) {

    HANDLE* eventPtr;

    eventPtr = (HANDLE*) inputEventPtr;

    if (!ResetEvent(*eventPtr)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_EventCb_Destroy(
                void*   const   inputEventPtr) {

    HANDLE* eventPtr;

    eventPtr = (HANDLE*) inputEventPtr;

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCMwTemplateRTOS_Windows_h_CommonCloseHandle(
                    *eventPtr));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
