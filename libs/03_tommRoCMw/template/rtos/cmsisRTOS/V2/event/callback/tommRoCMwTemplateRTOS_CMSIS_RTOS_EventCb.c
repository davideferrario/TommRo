
#if defined (__TOMMROC_MW_USE_EVENT_CMSIS_V2_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb.h"

#include "rtos/cmsisRTOS/V2/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"

#include "rtos/cmsisRTOS/V2/event/enumeration/tommRoCMwTemplateRTOSCmsisRTOSEventEnumeration.h"
#include "rtos/cmsisRTOS/V2/event/threadEventTable/tommRoCMwTemplateRTOSCmsisRTOSEventThreadEventTable.h"

#include "TOMMROC.h"

#include "TOMMROCMwTemplate.h"

#include <stdbool.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __CMSIS_RTOS_OS_SIGNAL_WAIT_FOR_ANY__           (0)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
static int32_t _convert_events(
                int32_t*    const   inputEventsPtr,
        const   uint8_t             inputEventsAmount) {

    int32_t result;
    uint8_t index;
    int32_t* ptr;

    result = 0;

    for (index = 0, ptr = inputEventsPtr; index < inputEventsAmount; ++index, ++ptr) {

        TOMMROC_ASSERT_EQUALS(tommRoCMathCountBitsSet((uint32_t) *ptr), 1);

        result |= *ptr;
    }

    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(tommRoCMathCountBitsSet((uint32_t) result), 1);

    return result;
}

static uint32_t _get_timeout(const uint32_t waitTimeoutMs) {

    if (WAIT_EVENT_NO_WAIT_TIMEOUT == waitTimeoutMs) {
        return 0;
    }

    if (WAIT_EVENT_INFINITE_TIMEOUT == waitTimeoutMs) {
        return osWaitForever;
    }

    return waitTimeoutMs;
}

static bool _is_signal_wait_timeout_result(const osStatus status) {

    if ((osEventTimeout == status) || (osErrorTimeoutResource == status)) {
        return true;
    }

    return false;
}

static bool _is_signal_wait_success_result(const osStatus status) {

    if (__CMSIS_RTOS_OS_SIGNAL_WAIT_SUCCESS_RESULT__ == status) {
        return true;
    }

    return false;
}

static tommRoC_mw_err_enum_t _extract_signaled_event(
        const   int32_t*    const   eventsPtr,
        const   uint8_t             inputEventsAmount,
        const   int32_t             signaledWaitForEvents,
                int32_t**   const   signaledEventPtr) {

    uint8_t index;
    int32_t* ptr;

    for (index = 0, ptr = (int32_t*) eventsPtr; index < inputEventsAmount; ++index, ++ptr) {

        if (0 != tommRoCMathCountBitsSet(*ptr & signaledWaitForEvents)) {

            *signaledEventPtr = ptr;

            return TOMMRO_C_MW_ERR_SUCCESS;
        }
    }

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    return TOMMRO_C_MW_LOW_LEVEL_ERR;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Create(
                void*   const   inputEventPtr) {

    tommRoC_mw_template_event_t* eventPtr;
    int32_t result;

    TOMMROC_CTA_SIZE_OF_EQUALS(tommRoC_mw_template_event_t, int32_t);

    eventPtr = (tommRoC_mw_template_event_t*) inputEventPtr;

    result = tommRoCMwTemplateRTOSCmsisRTOSEventEnumerationGetFirstAvailable();

    if (TOMMROC_MW_TEMPLATE_RTOS_CMSIS_RTOS_NOT_AVAILABLE_EVENT == result) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_EQUALS(tommRoCMathCountBitsSet(result), 1);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(eventPtr, &result, sizeof(result)));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Signal(
                void*   const   inputEventPtr) {

    tommRoC_mw_template_event_t event;
    uint8_t index;
    osThreadId thread;

    event = * (tommRoC_mw_template_event_t*) inputEventPtr;

    TOMMROC_ASSERT_EQUALS(tommRoCMathCountBitsSet(event), 1);

    for (index = 0; index < TOMMROC_MW_TEMPLATE_CMSIS_RTOS_EVENT_THREAD_EVENT_TABLE_AMOUNT; ++index) {

        if (tommRoCMwTemplateRTOSCmsisRTOSEventThreadEventTableIsWaitingFor(index, event)) {

            thread = tommRoCMwTemplateRTOSCmsisRTOSEventThreadEventTableGetThread(index);

            if (__CMSIS_RTOS_OS_SIGNAL_SET_ON_ERROR_RESULT__ == osSignalSet(thread, event)) {
                return TOMMRO_C_MW_LOW_LEVEL_ERR;
            }
        }
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_WaitForAll(
                void*   const   inputEventsPtr,
        const   uint8_t         inputEventsAmount,
        const   uint32_t        waitTimeoutMs) {

    tommRoC_mw_template_event_t* eventsPtr;
    int32_t waitForEvent;
    osThreadId currentThreadID;
    osEvent res;

    eventsPtr = (tommRoC_mw_template_event_t*) inputEventsPtr;

    waitForEvent = _convert_events(eventsPtr, inputEventsAmount);

    if (0 == waitForEvent) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    currentThreadID = osThreadGetId();

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCMwTemplateRTOSCmsisRTOSEventThreadEventTableAddIsWaiting(
                    currentThreadID,
                    waitForEvent));

    res = osSignalWait(waitForEvent, _get_timeout(waitTimeoutMs));

    if (_is_signal_wait_timeout_result(res.status)) {
        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    if (!_is_signal_wait_success_result(res.status)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    if (waitForEvent != res.value.signals) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_WaitForAny(
                void*   const   inputEventsPtr,
        const   uint8_t         inputEventsAmount,
        const   uint32_t        waitTimeoutMs,
                void**  const   inputSignaledEventPtr) {

    tommRoC_mw_template_event_t* eventsPtr;
    int32_t waitForEvent;
    int32_t** signaledEventPtr;
    osThreadId currentThreadID;
    int32_t signaledWaitForEvents;
    osEvent res;

    eventsPtr = (tommRoC_mw_template_event_t*) inputEventsPtr;

    waitForEvent = _convert_events(eventsPtr, inputEventsAmount);

    if (0 == waitForEvent) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    currentThreadID = osThreadGetId();

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCMwTemplateRTOSCmsisRTOSEventThreadEventTableAddIsWaiting(
                    currentThreadID,
                    waitForEvent));

    do {

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_FREE_RTOS__)
        res = osSignalWait(waitForEvent, _get_timeout(waitTimeoutMs));

#elif defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
        res = osSignalWait(__CMSIS_RTOS_OS_SIGNAL_WAIT_FOR_ANY__, _get_timeout(waitTimeoutMs));
#endif

        if (_is_signal_wait_timeout_result(res.status)) {
            return TOMMRO_C_MW_TIMEOUT_ERR;
        }

        if (!_is_signal_wait_success_result(res.status)) {
            return TOMMRO_C_MW_LOW_LEVEL_ERR;
        }

        signaledWaitForEvents = res.value.signals & waitForEvent;

    } while (0 == signaledWaitForEvents);

    signaledEventPtr = (int32_t**) inputSignaledEventPtr;

    return _extract_signaled_event(
            eventsPtr,
            inputEventsAmount,
            signaledWaitForEvents,
            signaledEventPtr);
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Clear(
                void*   const   inputEventPtr) {

    tommRoC_mw_template_event_t* eventPtr;
    osThreadId currentThreadID;

    eventPtr = (tommRoC_mw_template_event_t*) inputEventPtr;

    TOMMROC_ASSERT_EQUALS(tommRoCMathCountBitsSet(*eventPtr), 1);

    currentThreadID = osThreadGetId();

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCMwTemplateRTOSCmsisRTOSEventThreadEventTableRemoveIsWaiting(
                    currentThreadID,
                    *eventPtr));

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_UNDERLYING_IS_KEIL_RTX__)
    if (__CMSIS_RTOS_OS_SIGNAL_CLEAR_ON_ERROR_RESULT__ == osSignalClear(currentThreadID, *eventPtr)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }
#endif

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Destroy(
                void*   const   inputEventPtr) {

    tommRoC_mw_template_event_t* eventPtr;

    eventPtr = (tommRoC_mw_template_event_t*) inputEventPtr;

    TOMMROC_ASSERT_EQUALS(tommRoCMathCountBitsSet(*eventPtr), 1);

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCMwTemplateRTOSCmsisRTOSEventEnumerationDestroy(
                    *eventPtr));

    *eventPtr = TOMMROC_MW_TEMPLATE_RTOS_CMSIS_RTOS_NOT_AVAILABLE_EVENT;

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
