
#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/arm/RTC/tommRoCTemplateOs_ARM_RTC.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__)

#include "TOMMROC.h"

#include "fsl_rtc.h"

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
// RTC alarm IRQ handler
__attribute__((weak))
void RTC_IRQHandler(void) {

    const uint32_t status = RTC_GetStatusFlags(RTC);

    if (status & kRTC_TimeInvalidFlag) {
        RTC_ClearStatusFlags(RTC, kRTC_TimeInvalidFlag);
    }

    if (status & kRTC_TimeOverflowFlag) {
        RTC_ClearStatusFlags(RTC, kRTC_TimeOverflowFlag);
    }

    if (status & kRTC_AlarmFlag) {
        RTC_ClearStatusFlags(RTC, kRTC_AlarmFlag);
        RTC_DisableInterrupts(RTC, kRTC_AlarmInterruptEnable);
    }

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCInit(void) {

    rtc_config_t rtcConfig;

    RTC_GetDefaultConfig(&rtcConfig);

    // Start RTC
    RTC_Init(RTC, &rtcConfig);

    // Enable the RTC 32KHz oscillator
    RTC->CR |= RTC_CR_OSCE_MASK;

    // Little delay before enable time counter to allow the 32.768 kHz clock time to stabilize.
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCTemplateOs_ARM_RTCSetTimestamp(
                    tommRoCTemplateOs_ARM_RTCGetTimestamp()));

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCClose(void) {

    // Disable the RTC 32KHz oscillator
    RTC->CR &= ~RTC_CR_OSCE_MASK;

    // Stop RTC
    RTC_Deinit(RTC);

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCSetTimestamp(const uint32_t timestamp) {

    // RTC time counter has to be stopped before setting the date and time in the TSR register
    RTC_StopTimer(RTC);

    RTC->TSR = timestamp;

    // Start the RTC time counter
    RTC_StartTimer(RTC);

    return TOMMRO_C_ERR_SUCCESS;
}

uint32_t tommRoCTemplateOs_ARM_RTCGetTimestamp(void) {

    uint32_t timestamp;

    timestamp = RTC->TSR;

    return timestamp;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCSetDateTime(const tommRoC_date_time_t* const dateTimePtr) {

    TOMMROC_UTIL_UNUSED_PARAM(dateTimePtr);

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCGetDateTime(tommRoC_date_time_t* const dateTimePtr) {

    TOMMROC_UTIL_UNUSED_PARAM(dateTimePtr);

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTC_SetAlarmCallback(const tommRoC_template_os_arm_rtc_alarm_callback_t alarmCb) {

    TOMMROC_UTIL_UNUSED_PARAM(alarmCb);

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCAlarmInit(const uint32_t toSecond) {

    uint32_t currentTimestamp;

    TOMMROC_ASSERT_NOT_ZERO(toSecond);

    currentTimestamp = tommRoCOsGetTimestamp();

    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(toSecond + currentTimestamp, toSecond);
    TOMMROC_ASSERT_MORE_THAN(toSecond + currentTimestamp, currentTimestamp);

    TOMMROC_PARAM_CHECK_ON_TEST_RETURN_ERR(toSecond + currentTimestamp, <, toSecond);
    TOMMROC_PARAM_CHECK_ON_TEST_RETURN_ERR(toSecond + currentTimestamp, <=, currentTimestamp);

    // Set alarm time in seconds
    RTC->TAR = RTC->TSR + toSecond - 1;

    NVIC_ClearPendingIRQ(RTC_IRQn);
    EnableIRQ(RTC_IRQn);
    RTC_EnableInterrupts(RTC, kRTC_AlarmInterruptEnable);

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCAlarmClose(void) {

    RTC_DisableInterrupts(RTC, kRTC_AlarmInterruptEnable);
    DisableIRQ(RTC_IRQn);
    NVIC_ClearPendingIRQ(RTC_IRQn);

    return TOMMRO_C_ERR_SUCCESS;
}

#endif
#endif

#endif
