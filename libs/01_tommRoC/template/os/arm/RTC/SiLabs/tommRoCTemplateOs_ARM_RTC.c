
#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/arm/RTC/tommRoCTemplateOs_ARM_RTC.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)

#include "TOMMROC.h"

#if (!((defined(RTCC_COUNT) && (RTCC_COUNT > 0)) || (defined(RTC_COUNT) && (RTC_COUNT > 0)) || (defined(BURTC_COUNT) && (BURTC_COUNT > 0))))
#error "It is not possible to use tommRoC Os hardware calendar template on this hardware"
#endif

#if defined (RTCC_PRESENT) && RTCC_COUNT
#include "em_rtcc.h"

#elif defined (RTC_PRESENT) && RTC_COUNT
#include "em_rtc.h"

#elif defined (BURTC_PRESENT) && BURTC_COUNT
#include "em_burtc.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_INTERRUPT_BASED_IS_USED)
#define __WAKEUP_INTERVAL_SEC__         (1)
#define __WAKEUP_INTERVAL_MSEC__        (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(__WAKEUP_INTERVAL_SEC__))

#define __CHANNEL_ID_CALENDAR__         (0)
#endif

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_INTERRUPT_BASED_IS_USED)
static uint32_t _count_between_wakeup;
#endif

static tommRoC_template_os_arm_rtc_alarm_callback_t _alarm_cb = NULL;
static uint32_t _alarm_interrupt_counter = 0;
static uint32_t _to_reach_alarm_interrupt_counter = 0;

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_INTERRUPT_BASED_IS_USED)
static void _rtc_handler(void) {

    tommRoCSoftCalendarIncSec(__WAKEUP_INTERVAL_SEC__);

    if (NULL == _alarm_cb) {
        return;
    }

    ++_alarm_interrupt_counter;

    if (_to_reach_alarm_interrupt_counter == _alarm_interrupt_counter) {
        _alarm_cb();
    }
}
#endif

#if defined (RTCC_PRESENT) && RTCC_COUNT
__attribute__((weak))
void RTCC_IRQHandler(void) {

    uint32_t irq;

    irq = RTCC_IntGet();
    RTCC_IntClear(irq);

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

#elif defined (RTC_PRESENT) && RTC_COUNT
__attribute__((weak))
void RTC_IRQHandler(void) {

    uint32_t irq;

    irq = RTC_IntGet();
    RTC_IntClear(irq);

    // Interrupt source: compare match 0
    if (irq & RTC_IF_COMP0) {

        // Restart compare
        RTC_CompareSet(__CHANNEL_ID_CALENDAR__, RTC_CompareGet(__CHANNEL_ID_CALENDAR__) + _count_between_wakeup);

        _rtc_handler();
    }

    // Interrupt source: compare match 1
    if (irq & RTC_IF_COMP1) {
    }

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

#elif defined (BURTC_PRESENT) && BURTC_COUNT
__attribute__((weak))
void BURTC_IRQHandler(void) {

    uint32_t irq;

    irq = BURTC_IntGet();
    BURTC_IntClear(irq);

    // Interrupt source: compare match 0
    if (irq & BURTC_IF_COMP0) {

        // Restart compare
        BURTC_CompareSet(__CHANNEL_ID_CALENDAR__, BURTC_CompareGet(__CHANNEL_ID_CALENDAR__) + _count_between_wakeup);

        _rtc_handler();
    }

    // Interrupt source: counter overflow
    if (irq & BURTC_IF_OF) {
    }

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCInit(void) {

#if defined (RTCC_PRESENT) && RTCC_COUNT

    RTCC_Init_TypeDef rtccInit = RTCC_INIT_DEFAULT;
    CMU_LFXOInit_TypeDef lfxoInit = CMU_LFXOINIT_DEFAULT;

    // Initialize LFXO with specific parameters
    CMU_LFXOInit(&lfxoInit);

    // Setting RTCC clock source
    CMU_ClockSelectSet(cmuClock_RTCCCLK, cmuSelect_LFXO);

    CMU_ClockEnable(cmuClock_RTCCCLK, true);
    CMU_ClockEnable(cmuClock_RTCC, true);
    CMU_ClockDivSet(cmuClock_RTCC, 1);

    // Ensure RTCC reset
    RTCC_Reset();

    /**
     * In calendar mode, the pre-counter should be configured to give ticks with a period of
     * one second, i.e. RTCC_CTRL_CNTTICK should be set to PRESC, and the CNTPRESC bitfield
     * of the RTCC_CTRL register should be set to DIV32768 if a 32768 Hz clock source is used.
     */
    rtccInit.enable = false;
    rtccInit.presc  = rtccCntPresc_32768;

    // Initialize RTCC
    RTCC_Init(&rtccInit);

    // Enable required interrupt
    RTCC_IntEnable(RTCC_IEN_CNTTICK);

    // Enable RTCC interrupt
    RTCC_IntClear(RTCC_IntGet());
    NVIC_ClearPendingIRQ(RTCC_IRQn);
    NVIC_EnableIRQ(RTCC_IRQn);

    // Start Counter
    RTCC_Enable(true);

    return TOMMRO_C_ERR_SUCCESS;

#elif defined (RTC_PRESENT) && RTC_COUNT

    RTC_Init_TypeDef rtcInit = RTC_INIT_DEFAULT;

    // Enabling clock to the interface of the low energy modules
    CMU_ClockEnable(cmuClock_CORELE, true);

    CMU_ClockEnable(cmuClock_RTC, true);
    CMU_ClockDivSet(cmuClock_RTC, cmuClkDiv_1);

    _count_between_wakeup = CMU_ClockFreqGet(cmuClock_RTC) * __WAKEUP_INTERVAL_SEC__;

    // Ensure RTC reset
    RTC_Reset();

    // Configure RTC
    rtcInit.debugRun    = false;
    rtcInit.comp0Top    = false;
    rtcInit.enable      = false;

    // Initialize RTC
    RTC_Init(&rtcInit);

    // Setting the compare value of the RTC
    RTC_CompareSet(__CHANNEL_ID_CALENDAR__, RTC_CompareGet(__CHANNEL_ID_CALENDAR__) + _count_between_wakeup);

    // Enable Interrupt from RTC
    RTC_IntClear(RTC_IntGet());
    RTC_IntEnable(RTC_IEN_COMP0);
    NVIC_ClearPendingIRQ(TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE);
    NVIC_EnableIRQ(TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE);

    // Start Counter
    RTC_Enable(true);

    return TOMMRO_C_ERR_SUCCESS;

#elif defined (BURTC_PRESENT) && BURTC_COUNT

    BURTC_Init_TypeDef burtcInit = BURTC_INIT_DEFAULT;

    // Enabling clock to the interface of the low energy modules
    CMU_ClockEnable(cmuClock_CORELE, true);

    _count_between_wakeup = CMU_ClockFreqGet(cmuClock_LFA) * __WAKEUP_INTERVAL_SEC__;

    // Ensure BURTC reset
    BURTC_Reset();

    // Configure RTC
    burtcInit.enable        = false;                                                            // BURTC disabled after initialization
    burtcInit.mode          = burtcModeEM4;                                                     // BURTC is enabled in EM0-EM4
    burtcInit.debugRun      = false;                                                            // Counter shall keep running during debug halt.
    burtcInit.clkSel        = (SystemLFXOClockGet() > 0) ? burtcClkSelLFXO : burtcClkSelLFRCO;  // Select LFXO or LFRCO as clock source
    burtcInit.clkDiv        = burtcClkDiv_1;                                                    // Clock prescaler
    burtcInit.lowPowerComp  = 0;                                                                // Number of least significantt clock bits to ignore in low power mode
    burtcInit.timeStamp     = true;                                                             // Enable time stamp on entering backup power domain
    burtcInit.compare0Top   = true;                                                             // Clear counter on compare match
    burtcInit.lowPowerMode  = burtcLPDisable;                                                   // Low power operation mode, requires LFXO or LFRCO

    // Initialize BURTC
    BURTC_Init(&burtcInit);

    // Setting the compare value of the RTC
    BURTC_CompareSet(__CHANNEL_ID_CALENDAR__, BURTC_CompareGet(__CHANNEL_ID_CALENDAR__) + _count_between_wakeup);

    // Enable Interrupt from BURTC
    BURTC_IntClear(BURTC_IntGet());
    BURTC_IntEnable(BURTC_IEN_COMP0);
    NVIC_ClearPendingIRQ(BURTC_IRQn);
    NVIC_EnableIRQ(BURTC_IRQn);

    // Start Counter
    BURTC_Enable(true);

    return TOMMRO_C_ERR_SUCCESS;

#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCClose(void) {

#if defined (RTCC_PRESENT) && RTCC_COUNT

    // Disable RTCC
    RTCC_Enable(false);

    // Disable RTCC interrupt
    NVIC_ClearPendingIRQ(RTCC_IRQn);
    NVIC_DisableIRQ(RTCC_IRQn);
    RTCC_IntClear(RTCC_IntGet());

    // RTCC reset
    RTCC_Reset();

    CMU_ClockEnable(cmuClock_RTCC, false);
    CMU_ClockEnable(cmuClock_RTCCCLK, false);

    return TOMMRO_C_ERR_SUCCESS;

#elif defined (RTC_PRESENT) && RTC_COUNT

    // Disable RTC
    RTC_Enable(false);

    // Disable Interrupt from RTC
    NVIC_ClearPendingIRQ(TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE);
    NVIC_DisableIRQ(TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE);
    RTC_IntClear(RTC_IntGet());

    // Reset RTC
    RTC_Reset();

    CMU_ClockEnable(cmuClock_RTC, false);

    return TOMMRO_C_ERR_SUCCESS;

#elif defined (BURTC_PRESENT) && BURTC_COUNT

    // Disable BURTC
    BURTC_Enable(false);

    // Disable Interrupt from BURTC
    NVIC_ClearPendingIRQ(BURTC_IRQn);
    NVIC_DisableIRQ(BURTC_IRQn);
    BURTC_IntClear(BURTC_IntGet());

    // Reset BURTC
    BURTC_Reset();

    return TOMMRO_C_ERR_SUCCESS;

#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCSetTimestamp(const uint32_t timestamp) {

#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_TIMESTAMP_BASED_IS_USED)
#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_HW_BASED_IS_USED)

#if defined (RTCC_PRESENT) && RTCC_COUNT
    RTCC_CounterSet(timestamp);
    return TOMMRO_C_ERR_SUCCESS;

#elif defined (RTC_PRESENT) && RTC_COUNT
#endif

#elif defined (TOMMROC_TEMPLATE_OS__ARM__RTC_INTERRUPT_BASED_IS_USED)
    return tommRoCSoftCalendarSetTimestamp(timestamp);
#endif

#else
    TOMMROC_UTIL_UNUSED_PARAM(timestamp);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

uint32_t tommRoCTemplateOs_ARM_RTCGetTimestamp(void) {

#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_TIMESTAMP_BASED_IS_USED)
#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_HW_BASED_IS_USED)

#if defined (RTCC_PRESENT) && RTCC_COUNT
    return RTCC_CounterGet();

#elif defined (RTC_PRESENT) && RTC_COUNT
#endif

#elif defined (TOMMROC_TEMPLATE_OS__ARM__RTC_INTERRUPT_BASED_IS_USED)
    return tommRoCSoftCalendarGetTimestamp();
#endif

#else
    return 0;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCSetDateTime(const tommRoC_date_time_t* const dateTimePtr) {

#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_DATE_TIME_BASED_IS_USED)

#else
    TOMMROC_UTIL_UNUSED_PARAM(dateTimePtr);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCGetDateTime(tommRoC_date_time_t* const dateTimePtr) {

#if defined (TOMMROC_TEMPLATE_OS__ARM__RTC_DATE_TIME_BASED_IS_USED)

#else
    TOMMROC_UTIL_UNUSED_PARAM(dateTimePtr);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTC_SetAlarmCallback(const tommRoC_template_os_arm_rtc_alarm_callback_t alarmCb) {

    _alarm_cb = alarmCb;

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCAlarmInit(const uint32_t toSecond) {

    TOMMROC_ASSERT_NOT_ZERO(toSecond);

    _alarm_interrupt_counter            = 0;
    _to_reach_alarm_interrupt_counter   = toSecond;

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_RTCAlarmClose(void) {

    _alarm_interrupt_counter            = 0;
    _to_reach_alarm_interrupt_counter   = 0;

    return TOMMRO_C_ERR_SUCCESS;
}

#endif

#endif
