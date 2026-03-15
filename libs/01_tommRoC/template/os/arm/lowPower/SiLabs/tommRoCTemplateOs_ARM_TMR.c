
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/arm/lowPower/tommRoCTemplateOs_ARM_TMR.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)
#include "os/arm/lowPower/common/tommRoCTemplateOs_ARM_LowPowerCommon.h"

#include "TOMMROC.h"

#if defined (LETIMER_PRESENT) && LETIMER_COUNT
#include "em_letimer.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __CHANNEL_ID__      (0)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if defined (__TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__) && \
    defined (LETIMER_PRESENT) && LETIMER_COUNT
__attribute__((weak))
void LETIMER0_IRQHandler(void) {

    uint32_t irq;

    irq = LETIMER_IntGet(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LETIMER_TYPE);
    LETIMER_IntClear(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LETIMER_TYPE, irq);

    // Interrupt source: compare match 0
    if (irq & LETIMER_IF_COMP0) {

        tommRoCTemplateOs_ARM_LowPowerCommonSleepStatusSet();
    }

    // Interrupt source: compare match 1
    if (irq & LETIMER_IF_COMP1) {
    }

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

static tommRoC_err_enum_t _get_compatible_clk_div(const uint32_t msec, CMU_ClkDiv_TypeDef* const cmuClkDivPtr) {

    static const CMU_ClkDiv_TypeDef supportedClkDiv[] = {
            cmuClkDiv_1,
            cmuClkDiv_2,
            cmuClkDiv_4,
            cmuClkDiv_8,
            cmuClkDiv_16,
            cmuClkDiv_32,
            cmuClkDiv_64,
            cmuClkDiv_128,
            cmuClkDiv_256,
            cmuClkDiv_512,
            cmuClkDiv_1024,
            cmuClkDiv_2048,
            cmuClkDiv_4096,
            cmuClkDiv_8192,
            cmuClkDiv_16384,
            cmuClkDiv_32768,
    };

    uint8_t clkDivIdx;

    // Starting from low ClkDiv value (max. resolution), find the ClkDiv that can be compatible with sleep period
    for (clkDivIdx = 0; clkDivIdx < TOMMROC_UTIL_ARR_EAMOUNT(supportedClkDiv); ++clkDivIdx) {

        CMU_ClockDivSet(cmuClock_LETIMER0, supportedClkDiv[clkDivIdx]);

        if (TOMMROC_UNIT_MEASURE_TIME_APPROX_mSEC_TO_SEC(CMU_ClockFreqGet(cmuClock_LETIMER0) * msec) < UINT16_MAX) {
            *cmuClkDivPtr = supportedClkDiv[clkDivIdx];
            return TOMMRO_C_ERR_SUCCESS;
        }
    }

    return TOMMRO_C_PARAM_ERR;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOs_ARM_TMRInit(const uint32_t msec) {

#if defined (__TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__) && \
    defined (LETIMER_PRESENT) && LETIMER_COUNT

    LETIMER_Init_TypeDef leTimerInit = LETIMER_INIT_DEFAULT;
    CMU_ClkDiv_TypeDef compatibleClkDiv;
    uint32_t countBetweenWakeup;

    // Enabling clock to the interface of the low energy modules
    CMU_ClockEnable(cmuClock_CORELE, true);
    CMU_ClockEnable(cmuClock_LETIMER0, true);

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_get_compatible_clk_div(msec, &compatibleClkDiv));

    CMU_ClockDivSet(cmuClock_LETIMER0, compatibleClkDiv);
    countBetweenWakeup = UINT16_MAX - TOMMROC_UNIT_MEASURE_TIME_APPROX_mSEC_TO_SEC(CMU_ClockFreqGet(cmuClock_LETIMER0) * msec);

    // Ensure LETIMER reset
    LETIMER_Reset(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LETIMER_TYPE);

    // Configure LETIMER
    leTimerInit.debugRun    = false;
    leTimerInit.comp0Top    = false;
    leTimerInit.enable      = false;
    leTimerInit.repMode     = letimerRepeatOneshot;

    // Initialize LETIMER
    LETIMER_Init(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LETIMER_TYPE, &leTimerInit);

    // Setting the compare value of the LETIMER
    LETIMER_CompareSet(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LETIMER_TYPE, __CHANNEL_ID__, LETIMER_CompareGet(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LETIMER_TYPE, __CHANNEL_ID__) + countBetweenWakeup);

    LETIMER_RepeatSet(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LETIMER_TYPE, __CHANNEL_ID__, 0x01);

    // Enable Interrupt from LETIMER
    LETIMER_IntClear(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LETIMER_TYPE, LETIMER_IntGet(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LETIMER_TYPE));
    LETIMER_IntEnable(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LETIMER_TYPE, LETIMER_IEN_COMP0);
    NVIC_ClearPendingIRQ(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE);
    NVIC_EnableIRQ(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE);

    // Start Counter
    LETIMER_Enable(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LETIMER_TYPE, true);

    return TOMMRO_C_ERR_SUCCESS;

#else
    TOMMROC_UTIL_UNUSED_PARAM(msec);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_TMRClose(void) {

#if defined (__TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__) && \
    defined (LETIMER_PRESENT) && LETIMER_COUNT

    // Disable LETIMER
    LETIMER_Enable(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LETIMER_TYPE, false);

    // Disable Interrupt from LETIMER
    NVIC_ClearPendingIRQ(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE);
    NVIC_DisableIRQ(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE);
    LETIMER_IntClear(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LETIMER_TYPE, LETIMER_IntGet(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LETIMER_TYPE));

    // LETIMER reset
    LETIMER_Reset(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LETIMER_TYPE);

    CMU_ClockEnable(cmuClock_LETIMER0, false);

    return TOMMRO_C_ERR_SUCCESS;
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

#endif

#endif
