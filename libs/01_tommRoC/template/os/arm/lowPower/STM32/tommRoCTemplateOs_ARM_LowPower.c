
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/arm/lowPower/tommRoCTemplateOs_ARM_LowPower.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)
#include "os/arm/RTC/tommRoCTemplateOs_ARM_RTC.h"

#include "os/arm/lowPower/STM32/waitMode/tommRoCTemplateOs_ARM_LowPowerWaitMode.h"
#include "os/arm/lowPower/STM32/stopMode/tommRoCTemplateOs_ARM_LowPowerStopMode.h"

#include "os/arm/lowPower/common/tommRoCTemplateOs_ARM_LowPowerCommon.h"

#include "tommRoCTemplateOs.h"

#include "TOMMROC.h"

#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
#include "rtc.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
static uint32_t _interrupt_counter;
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
static void _handle_RTC_IRQ(void) {
    HAL_RTCEx_WakeUpTimerIRQHandler(&hrtc);
}
#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_STM32_RTC_IRQn_USED)
void RTC_IRQHandler(void) {
    _handle_RTC_IRQ();
}
#elif defined (TOMMROC_TEMPLATE_OS__ARM__RTC_STM32_RTC_WKUP_IRQn_USED)
void RTC_WKUP_IRQHandler(void) {
    _handle_RTC_IRQ();
}
#endif

void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc) {

    TOMMROC_UTIL_UNUSED_PARAM(hrtc);

    if (0 == _interrupt_counter) {
        return;
    }

    --_interrupt_counter;

    if (0 != _interrupt_counter) {
        return;
    }

    tommRoCTemplateOs_ARM_LowPowerCommonSleepStatusSet();
}

static uint32_t _get_rtc_clock(void) {

    do { // Added to avoid "warning: unreachable code"
        switch (__HAL_RCC_GET_RTC_SOURCE()) {

#if defined (RCC_RTCCLKSOURCE_NO_CLK)
        case RCC_RTCCLKSOURCE_NO_CLK:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            break;
#endif

#if defined (RCC_RTCCLKSOURCE_LSE)
        case RCC_RTCCLKSOURCE_LSE:          return LSE_VALUE;
#endif

#if defined (RCC_RTCCLKSOURCE_LSI)
        case RCC_RTCCLKSOURCE_LSI:          return LSI_VALUE;
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIVX:     return (HSE_VALUE / __HAL_RCC_GET_RTC_HSE_PRESCALER());
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV2)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV2 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV2:     return (HSE_VALUE / 2);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV3)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV3 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV3:     return (HSE_VALUE / 3);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV4)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV4 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV4:     return (HSE_VALUE / 4);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV5)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV5 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV5:     return (HSE_VALUE / 5);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV6)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV6 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV6:     return (HSE_VALUE / 6);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV7)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV7 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV7:     return (HSE_VALUE / 7);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV8)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV8 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV8:     return (HSE_VALUE / 8);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV9)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV9 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV9:     return (HSE_VALUE / 9);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV10)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV10 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV10:    return (HSE_VALUE / 10);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV11)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV11 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV11:    return (HSE_VALUE / 11);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV12)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV12 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV12:    return (HSE_VALUE / 12);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV13)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV13 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV13:    return (HSE_VALUE / 13);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV14)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV14 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV14:    return (HSE_VALUE / 14);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV15)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV15 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV15:    return (HSE_VALUE / 15);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV16)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV16 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV16:    return (HSE_VALUE / 16);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV17)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV17 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV17:    return (HSE_VALUE / 17);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV18)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV18 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV18:    return (HSE_VALUE / 18);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV19)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV19 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV19:    return (HSE_VALUE / 19);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV20)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV20 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV20:    return (HSE_VALUE / 20);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV21)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV21 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV21:    return (HSE_VALUE / 21);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV22)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV22 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV22:    return (HSE_VALUE / 22);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV23)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV23 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV23:    return (HSE_VALUE / 23);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV24)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV24 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV24:    return (HSE_VALUE / 24);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV25)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV25 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV25:    return (HSE_VALUE / 25);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV26)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV26 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV26:    return (HSE_VALUE / 26);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV27)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV27 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV27:    return (HSE_VALUE / 27);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV28)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV28 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV28:    return (HSE_VALUE / 28);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV29)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV29 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV29:    return (HSE_VALUE / 29);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV30)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV30 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV30:    return (HSE_VALUE / 30);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV31)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV31 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV31:    return (HSE_VALUE / 31);
#endif
#endif

#if defined (RCC_RTCCLKSOURCE_HSE_DIV32)
#if !defined (RCC_RTCCLKSOURCE_HSE_DIVX) || (RCC_RTCCLKSOURCE_HSE_DIV32 != RCC_RTCCLKSOURCE_HSE_DIVX)
        case RCC_RTCCLKSOURCE_HSE_DIV32:    return (HSE_VALUE / 32);
#endif
#endif

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            break;

        }
    } while (0);

    return LSE_VALUE;
}

static void _get_wake_up_params(const uint32_t msec, uint32_t* const WakeUpCounterPtr, uint32_t* const WakeUpClockPtr, uint32_t* const interruptCounterPtr) {

    const uint32_t toSecond = TOMMROC_UNIT_MEASURE_TIME_APPROX_mSEC_TO_SEC(msec);

    uint32_t RTClock;
    uint32_t WakeUpCounter;

    RTClock = _get_rtc_clock();

    /*
     * RTC Wakeup Interrupt Generation:
     * Wakeup Time Base = (RTC_WAKEUPCLOCK_RTCCLK_DIV / RTCClock)
     * Wakeup Time = Wakeup Time Base * WakeUpCounter = (RTC_WAKEUPCLOCK_RTCCLK_DIV / RTCClock) * WakeUpCounter
     * ==> WakeUpCounter = Wakeup Time / (RTC_WAKEUPCLOCK_RTCCLK_DIV / RTCClock) = (Wakeup Time * RTCClock) / RTC_WAKEUPCLOCK_RTCCLK_DIV
     */

    // If it is possible to manage wake up in MSEC resolution
    if (msec < (UINT32_MAX / RTClock)) {

#if defined (RTC_WAKEUPCLOCK_RTCCLK_DIV2)
        WakeUpCounter = TOMMROC_UNIT_MEASURE_TIME_APPROX_mSEC_TO_SEC((msec * RTClock) / 2);
        if (IS_RTC_WAKEUP_COUNTER(WakeUpCounter)) {
            *WakeUpCounterPtr       = WakeUpCounter;
            *WakeUpClockPtr         = RTC_WAKEUPCLOCK_RTCCLK_DIV2;
            *interruptCounterPtr    = 1;
            return;
        }
#endif

#if defined (RTC_WAKEUPCLOCK_RTCCLK_DIV4)
        WakeUpCounter = TOMMROC_UNIT_MEASURE_TIME_APPROX_mSEC_TO_SEC((msec * RTClock) / 4);
        if (IS_RTC_WAKEUP_COUNTER(WakeUpCounter)) {
            *WakeUpCounterPtr       = WakeUpCounter;
            *WakeUpClockPtr         = RTC_WAKEUPCLOCK_RTCCLK_DIV4;
            *interruptCounterPtr    = 1;
            return;
        }
#endif

#if defined (RTC_WAKEUPCLOCK_RTCCLK_DIV8)
        WakeUpCounter = TOMMROC_UNIT_MEASURE_TIME_APPROX_mSEC_TO_SEC((msec * RTClock) / 8);
        if (IS_RTC_WAKEUP_COUNTER(WakeUpCounter)) {
            *WakeUpCounterPtr       = WakeUpCounter;
            *WakeUpClockPtr         = RTC_WAKEUPCLOCK_RTCCLK_DIV8;
            *interruptCounterPtr    = 1;
            return;
        }
#endif

#if defined (RTC_WAKEUPCLOCK_RTCCLK_DIV16)
        WakeUpCounter = TOMMROC_UNIT_MEASURE_TIME_APPROX_mSEC_TO_SEC((msec * RTClock) / 16);
        if (IS_RTC_WAKEUP_COUNTER(WakeUpCounter)) {
            *WakeUpCounterPtr       = WakeUpCounter;
            *WakeUpClockPtr         = RTC_WAKEUPCLOCK_RTCCLK_DIV16;
            *interruptCounterPtr    = 1;
            return;
        }
    }
#endif

    // If here, manage interrupt in seconds
#if defined (RTC_WAKEUPCLOCK_CK_SPRE_16BITS)
    do {
        *WakeUpCounterPtr       = 0;
        *WakeUpClockPtr         = RTC_WAKEUPCLOCK_CK_SPRE_16BITS;
        *interruptCounterPtr    = toSecond;
        return;
    } while (0);
#endif

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);
}
#endif

static tommRoC_err_enum_t _prepare_for_stop(const uint32_t msec) {

#if !defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    TOMMROC_UTIL_UNUSED_PARAM(msec);
#endif

#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)

    uint32_t WakeUpCounter;
    uint32_t WakeUpClock;
    uint32_t interruptCounter;

    _get_wake_up_params(msec, &WakeUpCounter, &WakeUpClock, &interruptCounter);
#endif

    tommRoCTemplateOs_ARM_LowPowerCommonSleepStatusReset();

#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)

    _interrupt_counter = interruptCounter;

    // Enable WakeUp Interrupt 1Hz
    if (HAL_OK != HAL_RTCEx_DeactivateWakeUpTimer(&hrtc)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }
    __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hrtc, RTC_FLAG_WUTF);
    if (HAL_OK != HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, WakeUpCounter, WakeUpClock)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)
    HAL_SuspendTick();
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _restore_from_stop(const uint32_t msec) {

#if !defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__) || !defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)
    TOMMROC_UTIL_UNUSED_PARAM(msec);
#endif

    // NOTE: after stop mode the HSI is used as high speed clock. Call SystemClock_Config to reInit correctly all clocks
    extern void SystemClock_Config(void);
    SystemClock_Config();

#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)
    uwTick += msec;
#endif
#endif
#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)
    HAL_ResumeTick();
#endif

#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    // Deactivate WakeUp Interrupt 1Hz
    if (HAL_OK != HAL_RTCEx_DeactivateWakeUpTimer(&hrtc)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _stop(void) {

    while (!tommRoCTemplateOs_ARM_LowPowerCommonSleepStatusGet()) {
        TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOs_ARM_LowPowerStopModeEnter());
    }

    return TOMMRO_C_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOs_ARM_LowPowerWait(void) {

    tommRoC_err_enum_t result;

    tommRoCTemplateOs_ARM_LowPowerWaitModePreEnter();
    result = tommRoCTemplateOs_ARM_LowPowerWaitModeEnter();
    tommRoCTemplateOs_ARM_LowPowerWaitModePostExit();

    return result;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_LowPowerSleep(const uint32_t msec) {

    tommRoC_err_enum_t result;

    if (0 == msec) {
        return TOMMRO_C_ERR_SUCCESS;
    }

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_prepare_for_stop(msec));

    tommRoCTemplateOs_ARM_LowPowerStopModePreEnter();
    result = _stop();
    tommRoCTemplateOs_ARM_LowPowerStopModePostExit();

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_restore_from_stop(msec));

    return result;
}

#endif

#endif
