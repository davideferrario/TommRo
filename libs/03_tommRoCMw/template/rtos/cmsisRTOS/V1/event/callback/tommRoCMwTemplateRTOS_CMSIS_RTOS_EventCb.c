
#if defined (__TOMMROC_MW_USE_EVENT_CMSIS_V1_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb.h"

#include "rtos/cmsisRTOS/V1/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"

#include "rtos/eventU32/tommRoCMwTemplateRTOSEventU32.h"

#include "TOMMROC.h"

#include "TOMMROCMwTemplate.h"

#if defined (__TOMMROC_MW_ARM_ESP32_RTOS_INTERNAL_TEMPLATE_IS_USED__)
#include "freertos/event_groups.h"
#else
#include "event_groups.h"
#endif

#include "FreeRTOSConfig.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
#if !defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#if (   (!defined (configUSE_TIMERS) || (configUSE_TIMERS != 1))                                ||  \
        (!defined (INCLUDE_xTimerPendFunctionCall) || (INCLUDE_xTimerPendFunctionCall != 1))    ||  \
        (!defined (INCLUDE_xEventGroupSetBitFromISR) || (INCLUDE_xEventGroupSetBitFromISR != 1))    )
#error "All configUSE_TIMERS, INCLUDE_xTimerPendFunctionCall and INCLUDE_xEventGroupSetBitFromISR MUST be defined and set to 1"
#endif
#else
#endif

/**
 * NOTE:
 * From event_groups.h file.
 *
 * Although event groups are not related to ticks, for internal implementation
 * reasons the number of bits available for use in an event group is dependent
 * on the configUSE_16_BIT_TICKS setting in FreeRTOSConfig.h.  If
 * configUSE_16_BIT_TICKS is 1 then each event group contains 8 usable bits (bit
 * 0 to bit 7).  If configUSE_16_BIT_TICKS is set to 0 then each event group has
 * 24 usable bits (bit 0 to bit 23).  The EventBits_t type is used to store
 * event bits within an event group.
 */

#if (configUSE_16_BIT_TICKS == 1)
TOMMROC_SCTA_EQUALS(__TOMMROC_MW_EVENT_TEMPLATE_MAX_EVENT_AMOUNT__, 8);
#else
TOMMROC_SCTA_EQUALS(__TOMMROC_MW_EVENT_TEMPLATE_MAX_EVENT_AMOUNT__, 24);
#endif
TOMMROC_SCTA_SIZE_OF_EQUALS(EventBits_t, uint32_t);

/*******************************************************************************
 * local vars
 ******************************************************************************/
static EventGroupHandle_t _event_group_handle = NULL;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static TickType_t _msec_to_ticks(const uint32_t millisec) {

    TOMMROC_CTA_SIZE_OF_EQUALS(osWaitForever, millisec);

    TickType_t ticks;

    if (osWaitForever == millisec) {
        return portMAX_DELAY;
    }

    if (0 == millisec) {
        return 0;
    }

    ticks = millisec / portTICK_PERIOD_MS;
    if (0 == ticks) {
        return 1;
    }

    return ticks;
}

static uint32_t _get_timeout(const uint32_t waitTimeoutMs) {

    TOMMROC_CTA_SIZE_OF_EQUALS(osWaitForever, uint32_t);

    if (WAIT_EVENT_NO_WAIT_TIMEOUT == waitTimeoutMs) {
        return 0;
    }

    if (WAIT_EVENT_INFINITE_TIMEOUT == waitTimeoutMs) {
        return osWaitForever;
    }

    return waitTimeoutMs;
}

static TickType_t _get_ticks(const uint32_t waitTimeoutMs) {

    return _msec_to_ticks(_get_timeout(waitTimeoutMs));
}

static EventBits_t _convert_events(
        const   tommRoC_mw_template_event_t*    const   eventsPtr,
        const   uint8_t                                 eventsAmount) {

    EventBits_t flags;

    tommRoC_mw_template_event_t* eventPtr;
    uint8_t idx;

    flags = (EventBits_t) 0;
    for (idx = 0, eventPtr = (tommRoC_mw_template_event_t*) eventsPtr; idx < eventsAmount; ++idx, ++eventPtr) {
        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(tommRoCMathCountBitsSet((uint32_t) eventPtr->event), 1);
        flags |= eventPtr->event;
    }

    TOMMROC_ASSERT_NOT_ZERO(flags);
    TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(tommRoCMathCountBitsSet((uint32_t) flags), eventsAmount);

    return flags;
}

static tommRoC_mw_err_enum_t _signal(
        const   tommRoC_mw_template_event_t*    const   eventPtr) {

    // NOTE: donìt check function result because it is not clear the function return.
    xEventGroupSetBits(_event_group_handle, eventPtr->event);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

static tommRoC_mw_err_enum_t _signal_from_ISR(
        const   tommRoC_mw_template_event_t*    const   eventPtr) {

    BaseType_t xHigherPriorityTaskWoken;
    BaseType_t res;

    // xHigherPriorityTaskWoken must be initialised to pdFALSE.
    xHigherPriorityTaskWoken = pdFALSE;

    res = xEventGroupSetBitsFromISR(_event_group_handle, eventPtr->event, &xHigherPriorityTaskWoken);

    // If the message not posted successfully
    if (__CMSIS_V1_RTOS_X_EVENT_GROUP_SET_BITS_FROM_ISR_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    // If xHigherPriorityTaskWoken is now set to pdTRUE then a context
    // switch should be requested.  The macro used is port specific and
    // will be either portYIELD_FROM_ISR() or portEND_SWITCHING_ISR() -
    // refer to the documentation page for the port being used.
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

static tommRoC_mw_err_enum_t _clear(const EventBits_t bitsToClear) {

    xEventGroupClearBits(_event_group_handle, bitsToClear);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

static tommRoC_mw_err_enum_t _clear_from_ISR(const EventBits_t bitsToClear) {

    xEventGroupClearBitsFromISR(_event_group_handle, bitsToClear);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

static tommRoC_mw_err_enum_t _get_signaled_events(
        const   EventBits_t                             actualEventBits,
        const   tommRoC_mw_template_event_t*    const   eventsPtr,
        const   uint8_t                                 eventsAmount,
                tommRoC_mw_template_event_t*    const   signaledEventsPtr,
        const   uint8_t                                 signaledEventsAmount,
                uint8_t*                        const   signaledEventsAmountPtr) {

    tommRoC_mw_template_event_t* eventPtr;
    tommRoC_mw_template_event_t* outEventPtr;

    uint8_t resAmount;

    uint8_t idx;

    if (tommRoCMathCountBitsSet((uint32_t) actualEventBits) > eventsAmount) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }
    if (tommRoCMathCountBitsSet((uint32_t) actualEventBits) > signaledEventsAmount) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    for (idx = 0, eventPtr = signaledEventsPtr; idx < signaledEventsAmount; ++idx, ++eventPtr) {
        eventPtr->event = (EventBits_t) 0;
    }

    outEventPtr = signaledEventsPtr;
    resAmount   = 0;

    for (idx = 0, eventPtr = (tommRoC_mw_template_event_t*) eventsPtr; idx < eventsAmount; ++idx, ++eventPtr) {

        TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(tommRoCMathCountBitsSet((uint32_t) eventPtr->event), 1);

        if (0 != ((uint32_t) eventPtr->event & (uint32_t) actualEventBits)) {

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

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Init(void) {

    _event_group_handle = xEventGroupCreate();

    if (__CMSIS_V1_RTOS_EVENT_GROUP_CREATE_ON_ERROR_RESULT == _event_group_handle) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Close(void) {

    vEventGroupDelete(_event_group_handle);
    _event_group_handle = NULL;

    if (tommRoCMwTemplateRTOSEventU32IsStarted()) {
        TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOSEventU32Stop());
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Create(
                void*       const   inputEventPtr) {

    static bool firstExecute = true;

    tommRoC_mw_template_event_t* eventPtr;

    bool osCriticalIsInit;
    tommRoC_mw_err_enum_t mwThreadSuspendAllIsAvailable;
    tommRoC_mw_err_enum_t mwThreadResumeAllIsAvailable;

    uint32_t criticalSpecificData;

    uint32_t newEvent;

    TOMMROC_CTA_SIZE_OF_EQUALS(EventBits_t, ((tommRoC_mw_template_event_t*)NULL)->event);

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

    eventPtr->event = (EventBits_t) newEvent;

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Signal(
                void*       const   inputEventPtr) {

    tommRoC_mw_template_event_t* eventPtr;

    bool isFromISR;

    TOMMROC_CTA_SIZE_OF_EQUALS(EventBits_t, ((tommRoC_mw_template_event_t*)NULL)->event);

    eventPtr = (tommRoC_mw_template_event_t*) inputEventPtr;

    if (1 != tommRoCMathCountBitsSet((uint32_t) eventPtr->event)) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsIsFromISR(&isFromISR));

    if (!isFromISR) {
        TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_signal(eventPtr));
    }
    else {
        TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_signal_from_ISR(eventPtr));
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Wait(
                void*       const   inputEventPtr,
        const   uint32_t            waitTimeoutMs) {

    tommRoC_mw_template_event_t* eventPtr;

    bool isFromISR;

    TickType_t ticksToWait;
    EventBits_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(EventBits_t, ((tommRoC_mw_template_event_t*)NULL)->event);

    eventPtr = (tommRoC_mw_template_event_t*) inputEventPtr;

    if (1 != tommRoCMathCountBitsSet((uint32_t) eventPtr->event)) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    // NOTE: it is not possible to call xEventGroupWaitBits from ISR
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsIsFromISR(&isFromISR));
    if (isFromISR) {
        return TOMMRO_C_MW_GENERIC_ERR;
    }

    ticksToWait = _get_ticks(waitTimeoutMs);

    res = xEventGroupWaitBits(_event_group_handle, eventPtr->event, pdTRUE, pdFALSE, ticksToWait);

    if ((EventBits_t) 0 == (res & eventPtr->event)) {
        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_WaitForAll(
                void*       const   inputEventsPtr,
        const   uint8_t             inputEventsAmount,
        const   uint32_t            waitTimeoutMs) {

    bool isFromISR;

    EventBits_t bitsToWaitFor;
    TickType_t ticksToWait;
    EventBits_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(EventBits_t, ((tommRoC_mw_template_event_t*)NULL)->event);

    bitsToWaitFor = _convert_events((tommRoC_mw_template_event_t*) inputEventsPtr, inputEventsAmount);

    if ((EventBits_t) 0 == bitsToWaitFor) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    // NOTE: it is not possible to call xEventGroupWaitBits from ISR
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsIsFromISR(&isFromISR));
    if (isFromISR) {
        return TOMMRO_C_MW_GENERIC_ERR;
    }

    ticksToWait = _get_ticks(waitTimeoutMs);

    res = xEventGroupWaitBits(_event_group_handle, bitsToWaitFor, pdTRUE, pdTRUE, ticksToWait);

    if (bitsToWaitFor != res) {
        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_WaitForAny(
                void*       const   inputEventsPtr,
        const   uint8_t             inputEventsAmount,
        const   uint32_t            waitTimeoutMs,
                void*       const   inputSignaledEventsPtr,
        const   uint8_t             inputSignaledEventsAmount,
                uint8_t*    const   inputSignaledEventsAmountPtr) {

    bool isFromISR;

    EventBits_t bitsToWaitFor;
    TickType_t ticksToWait;
    EventBits_t res;

    TOMMROC_CTA_SIZE_OF_EQUALS(EventBits_t, ((tommRoC_mw_template_event_t*)NULL)->event);

    bitsToWaitFor = _convert_events((tommRoC_mw_template_event_t*) inputEventsPtr, inputEventsAmount);

    if ((EventBits_t) 0 == bitsToWaitFor) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    // NOTE: it is not possible to call xEventGroupWaitBits from ISR
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsIsFromISR(&isFromISR));
    if (isFromISR) {
        return TOMMRO_C_MW_GENERIC_ERR;
    }

    ticksToWait = _get_ticks(waitTimeoutMs);

    res = xEventGroupWaitBits(_event_group_handle, bitsToWaitFor, pdTRUE, pdFALSE, ticksToWait);

    if ((EventBits_t) 0 == (res & bitsToWaitFor)) {
        return TOMMRO_C_MW_TIMEOUT_ERR;
    }

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _get_signaled_events(
                    res,
                    inputEventsPtr,
                    inputEventsAmount,
                    inputSignaledEventsPtr,
                    inputSignaledEventsAmount,
                    inputSignaledEventsAmountPtr));

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Clear(
                void*       const   inputEventsPtr,
        const   uint8_t             inputEventsAmount) {

    bool isFromISR;

    EventBits_t bitsToClear;

    TOMMROC_CTA_SIZE_OF_EQUALS(EventBits_t, ((tommRoC_mw_template_event_t*)NULL)->event);

    bitsToClear = _convert_events((tommRoC_mw_template_event_t*) inputEventsPtr, inputEventsAmount);

    if ((EventBits_t) 0 == bitsToClear) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsIsFromISR(&isFromISR));

    if (!isFromISR) {
        TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_clear(bitsToClear));
    }
    else {
        TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_clear_from_ISR(bitsToClear));
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_EventCb_Destroy(
                void*       const   inputEventPtr) {

    tommRoC_mw_template_event_t* eventPtr;

    TOMMROC_CTA_SIZE_OF_EQUALS(EventBits_t, ((tommRoC_mw_template_event_t*)NULL)->event);

    eventPtr = (tommRoC_mw_template_event_t*) inputEventPtr;

    if (1 != tommRoCMathCountBitsSet((uint32_t) eventPtr->event)) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCMwTemplateRTOSEventU32Destroy((uint32_t) eventPtr->event));

    eventPtr->event = 0;

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
