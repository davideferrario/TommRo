
#if defined (__TOMMROC_MW_USE_EVENT_THREADX_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_ThreadX_EventCb.h"

#include "rtos/threadX/common/compatibility/tommRoCMwTemplateRTOS_ThreadX_Compatibility.h"

#include "rtos/eventU32/tommRoCMwTemplateRTOSEventU32.h"

#include "TOMMROC.h"

#include "TOMMROCMwTemplate.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
TOMMROC_SCTA_EQUALS(__TOMMROC_MW_EVENT_TEMPLATE_MAX_EVENT_AMOUNT__, TOMMROC_UNIT_MEASURE_BYTE_TO_BIT(sizeof(ULONG)));
TOMMROC_SCTA_SIZE_OF_EQUALS(ULONG, uint32_t);

/*******************************************************************************
 * local vars
 ******************************************************************************/
static TX_EVENT_FLAGS_GROUP _event_flags_group;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static ULONG _get_timeout(const uint32_t waitTimeoutMs) {

    if (WAIT_EVENT_NO_WAIT_TIMEOUT == waitTimeoutMs) {
        return TX_NO_WAIT;
    }

    if (WAIT_EVENT_INFINITE_TIMEOUT == waitTimeoutMs) {
        return TX_WAIT_FOREVER;
    }

    return TOMMROC_MW_TEMPLATE_RTOS_THREADX_COMMON_COMPATIBILITY_MS_TO_TICKS(waitTimeoutMs);
}

static ULONG _get_requested_flags(
        const   tommRoC_mw_template_event_t*    const   eventsPtr,
        const   uint8_t                                 eventsAmount) {

    ULONG requested_flags;

    tommRoC_mw_template_event_t* eventPtr;
    uint8_t idx;

    requested_flags = (ULONG) 0;
    for (idx = 0, eventPtr = (tommRoC_mw_template_event_t*) eventsPtr; idx < eventsAmount; ++idx, ++eventPtr) {
        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(tommRoCMathCountBitsSet((uint32_t) eventPtr->event), 1);
        requested_flags |= eventPtr->event;
    }

    TOMMROC_ASSERT_NOT_ZERO(requested_flags);
    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(tommRoCMathCountBitsSet((uint32_t) requested_flags), eventsAmount);

    return requested_flags;
}

static tommRoC_mw_err_enum_t _get_signaled_events(
        const   ULONG                                   actual_flags,
        const   tommRoC_mw_template_event_t*    const   eventsPtr,
        const   uint8_t                                 eventsAmount,
                tommRoC_mw_template_event_t*    const   signaledEventsPtr,
        const   uint8_t                                 signaledEventsAmount,
                uint8_t*                        const   signaledEventsAmountPtr) {

    tommRoC_mw_template_event_t* eventPtr;
    tommRoC_mw_template_event_t* outEventPtr;

    uint8_t resAmount;

    uint8_t idx;

    if (tommRoCMathCountBitsSet((uint32_t) actual_flags) > eventsAmount) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }
    if (tommRoCMathCountBitsSet((uint32_t) actual_flags) > signaledEventsAmount) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    for (idx = 0, eventPtr = signaledEventsPtr; idx < signaledEventsAmount; ++idx, ++eventPtr) {
        eventPtr->event = (ULONG) 0;
    }

    outEventPtr = signaledEventsPtr;
    resAmount   = 0;

    for (idx = 0, eventPtr = (tommRoC_mw_template_event_t*) eventsPtr; idx < eventsAmount; ++idx, ++eventPtr) {

        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(tommRoCMathCountBitsSet((uint32_t) eventPtr->event), 1);

        if (0 != ((uint32_t) eventPtr->event & (uint32_t) actual_flags)) {

            TOMMROC_ASSERT_LESS_THAN(resAmount, signaledEventsAmount);

            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(outEventPtr, eventPtr, sizeof(tommRoC_mw_template_event_t)));

            ++outEventPtr;
            ++resAmount;

            TOMMROC_ASSERT_LESS_OR_EQUALS_THAN(resAmount, signaledEventsAmount);
        }
    }

    TOMMROC_ASSERT_NOT_ZERO(resAmount);

    *signaledEventsAmountPtr = resAmount;

    return TOMMRO_C_MW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_EventCb_Init(void) {

    if (__THREADX_EVENT_FLAGS_CREATE_SUCCESS_RESULT__ != tx_event_flags_create(&_event_flags_group, TX_NULL)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_EventCb_Close(void) {

    if (__THREADX_EVENT_FLAGS_DELETE_SUCCESS_RESULT__ != tx_event_flags_delete(&_event_flags_group)) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    if (tommRoCMwTemplateRTOSEventU32IsStarted()) {
        TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOSEventU32Stop());
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_EventCb_Create(
                void*       const   inputEventPtr) {

    static bool firstExecute = true;

    tommRoC_mw_template_event_t* eventPtr;

    bool osCriticalIsInit;
    tommRoC_mw_err_enum_t mwThreadSuspendAllIsAvailable;
    tommRoC_mw_err_enum_t mwThreadResumeAllIsAvailable;

    uint32_t criticalSpecificData;

    uint32_t newEvent;

    TOMMROC_CTA_SIZE_OF_EQUALS(ULONG, ((tommRoC_mw_template_event_t*)NULL)->event);

    eventPtr = (tommRoC_mw_template_event_t*) inputEventPtr;

    if (firstExecute) {

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsIsInitEnv(TOMMRO_C_OS_CRITICAL_FUNCT, &osCriticalIsInit));
        mwThreadSuspendAllIsAvailable   = tommRoCMwThreadIsOpAvailable(TOMMRO_C_MW_THREAD_SUSPEND_ALL);
        mwThreadResumeAllIsAvailable    = tommRoCMwThreadIsOpAvailable(TOMMRO_C_MW_THREAD_RESUME_ALL);

        if ((TOMMRO_C_MW_ERR_SUCCESS == mwThreadSuspendAllIsAvailable) && (TOMMRO_C_MW_ERR_SUCCESS == mwThreadResumeAllIsAvailable)) {
            TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwThreadSuspendAll());
        }
        else if (osCriticalIsInit) {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsEnterCritical(&criticalSpecificData));
        }

        TOMMROC_CTA_LESS_OR_EQUALS_THAN(__TOMMROC_MW_EVENT_TEMPLATE_MAX_EVENT_AMOUNT__, TOMMROC_UNIT_MEASURE_BYTE_TO_BIT(sizeof(uint32_t)));
        TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOSEventU32Start(__TOMMROC_MW_EVENT_TEMPLATE_MAX_EVENT_AMOUNT__));

        firstExecute = false;

        if ((TOMMRO_C_MW_ERR_SUCCESS == mwThreadSuspendAllIsAvailable) && (TOMMRO_C_MW_ERR_SUCCESS == mwThreadResumeAllIsAvailable)) {
            TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwThreadResumeAll());
        }
        else if (osCriticalIsInit) {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsExitCritical(&criticalSpecificData));
        }
    }

    newEvent = tommRoCMwTemplateRTOSEventU32GetFirstAvailable();

    if (TOMMROC_MW_TEMPLATE_RTOS_EVENT_U32_NOT_AVAILABLE_EVENT == newEvent) {
        return TOMMRO_C_MW_NOT_ENOUGH_RESOURCE_ERR;
    }

    TOMMROC_ASSERT_EQUALS(tommRoCMathCountBitsSet(newEvent), 1);

    eventPtr->event = (ULONG) newEvent;

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_EventCb_Signal(
                void*       const   inputEventPtr) {

    tommRoC_mw_template_event_t* eventPtr;

    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(ULONG, ((tommRoC_mw_template_event_t*)NULL)->event);

    eventPtr = (tommRoC_mw_template_event_t*) inputEventPtr;

    if (1 != tommRoCMathCountBitsSet((uint32_t) eventPtr->event)) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    res = tx_event_flags_set(&_event_flags_group, eventPtr->event, TX_OR);

    if (__THREADX_EVENT_FLAGS_SET_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_EventCb_Wait(
                void*       const   inputEventPtr,
        const   uint32_t            waitTimeoutMs) {

    tommRoC_mw_template_event_t* eventPtr;

    ULONG wait_option;
    ULONG actual_flags;

    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(ULONG, ((tommRoC_mw_template_event_t*)NULL)->event);

    eventPtr = (tommRoC_mw_template_event_t*) inputEventPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_WAIT_FOREVER, wait_option);

    if (1 != tommRoCMathCountBitsSet((uint32_t) eventPtr->event)) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    wait_option = _get_timeout(waitTimeoutMs);

    res = tx_event_flags_get(&_event_flags_group, eventPtr->event, TX_OR_CLEAR, &actual_flags, wait_option);

    if (__THREADX_EVENT_FLAGS_GET_SUCCESS_RESULT__ != res) {
        if (TX_NO_EVENTS == res) {
            return TOMMRO_C_MW_TIMEOUT_ERR;
        }

        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}
tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_EventCb_WaitForAll(
                void*       const   inputEventsPtr,
        const   uint8_t             inputEventsAmount,
        const   uint32_t            waitTimeoutMs) {

    ULONG requested_flags;
    ULONG wait_option;
    ULONG actual_flags;

    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(ULONG, ((tommRoC_mw_template_event_t*)NULL)->event);

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_WAIT_FOREVER, wait_option);

    requested_flags = _get_requested_flags((tommRoC_mw_template_event_t*) inputEventsPtr, inputEventsAmount);

    if (0 == requested_flags) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    wait_option = _get_timeout(waitTimeoutMs);

    res = tx_event_flags_get(&_event_flags_group, requested_flags, TX_AND_CLEAR, &actual_flags, wait_option);

    if (__THREADX_EVENT_FLAGS_GET_SUCCESS_RESULT__ != res) {
        if (TX_NO_EVENTS == res) {
            return TOMMRO_C_MW_TIMEOUT_ERR;
        }

        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_EventCb_WaitForAny(
                void*       const   inputEventsPtr,
        const   uint8_t             inputEventsAmount,
        const   uint32_t            waitTimeoutMs,
                void*       const   inputSignaledEventsPtr,
        const   uint8_t             inputSignaledEventsAmount,
                uint8_t*    const   inputSignaledEventsAmountPtr) {

    ULONG requested_flags;
    ULONG wait_option;
    ULONG actual_flags;

    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(ULONG, ((tommRoC_mw_template_event_t*)NULL)->event);

    TOMMROC_CTA_SIZE_OF_EQUALS(TX_WAIT_FOREVER, wait_option);

    requested_flags = _get_requested_flags((tommRoC_mw_template_event_t*) inputEventsPtr, inputEventsAmount);

    if (0 == requested_flags) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    wait_option = _get_timeout(waitTimeoutMs);

    res = tx_event_flags_get(&_event_flags_group, requested_flags, TX_OR_CLEAR, &actual_flags, wait_option);

    if (__THREADX_EVENT_FLAGS_GET_SUCCESS_RESULT__ != res) {
        if (TX_NO_EVENTS == res) {
            return TOMMRO_C_MW_TIMEOUT_ERR;
        }

        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _get_signaled_events(
                    actual_flags,
                    inputEventsPtr,
                    inputEventsAmount,
                    inputSignaledEventsPtr,
                    inputSignaledEventsAmount,
                    inputSignaledEventsAmountPtr));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_EventCb_Clear(
                void*       const   inputEventsPtr,
        const   uint8_t             inputEventsAmount) {

    ULONG requested_flags;
    ULONG actual_flags;

    UINT res;

    TOMMROC_CTA_SIZE_OF_EQUALS(ULONG, ((tommRoC_mw_template_event_t*)NULL)->event);

    requested_flags = _get_requested_flags((tommRoC_mw_template_event_t*) inputEventsPtr, inputEventsAmount);

    if (0 == requested_flags) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    // NOTE: call flags get with TX_AND_CLEAR in order to clear.
    res = tx_event_flags_get(&_event_flags_group, requested_flags, TX_AND_CLEAR, &actual_flags, TX_NO_WAIT);

    if (__THREADX_EVENT_FLAGS_GET_SUCCESS_RESULT__ != res) {
        if (TX_NO_EVENTS == res) {
            return TOMMRO_C_MW_ERR_SUCCESS;
        }

        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_ThreadX_EventCb_Destroy(
                void*       const   inputEventPtr) {

    tommRoC_mw_template_event_t* eventPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(ULONG, ((tommRoC_mw_template_event_t*)NULL)->event);

    eventPtr = (tommRoC_mw_template_event_t*) inputEventPtr;

    if (1 != tommRoCMathCountBitsSet((uint32_t) eventPtr->event)) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOSEventU32Destroy((uint32_t) eventPtr->event));

    eventPtr->event = 0;

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
