
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/arm/lowPower/tommRoCTemplateOs_ARM_TMR.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#include "os/arm/lowPower/common/tommRoCTemplateOs_ARM_LowPowerCommon.h"

#include "TOMMROC.h"

#if defined (FSL_FEATURE_SOC_LPTMR_COUNT) && FSL_FEATURE_SOC_LPTMR_COUNT
#include "fsl_lptmr.h"
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
#if defined (__TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
#if defined (FSL_FEATURE_SOC_LPTMR_COUNT) && FSL_FEATURE_SOC_LPTMR_COUNT
// LPTMR IRQ handler
__attribute__((weak))
void LPTMR0_IRQHandler(void) {

    if (kLPTMR_TimerInterruptEnable & LPTMR_GetEnabledInterrupts(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LPTMR_TYPE)) {
        LPTMR_DisableInterrupts(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LPTMR_TYPE, kLPTMR_TimerInterruptEnable);
        LPTMR_ClearStatusFlags(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LPTMR_TYPE, kLPTMR_TimerCompareFlag);
        LPTMR_StopTimer(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LPTMR_TYPE);

        tommRoCTemplateOs_ARM_LowPowerCommonSleepStatusSet();
    }

    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
#endif
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateOs_ARM_TMRInit(const uint32_t msec) {

#if defined (FSL_FEATURE_SOC_LPTMR_COUNT) && FSL_FEATURE_SOC_LPTMR_COUNT

    lptmr_config_t lptmrConfig;

    LPTMR_GetDefaultConfig(&lptmrConfig);
//    // Use LPO as clock source.
//    lptmrConfig.prescalerClockSource = kLPTMR_PrescalerClock_1;
//    lptmrConfig.bypassPrescaler = true;
    LPTMR_Init(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LPTMR_TYPE, &lptmrConfig);

    LPTMR_SetTimerPeriod(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LPTMR_TYPE, USEC_TO_COUNT(TOMMROC_UNIT_MEASURE_TIME_mSEC_TO_uSEC(msec), CLOCK_GetFreq(kCLOCK_LpoClk)));

    NVIC_ClearPendingIRQ(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE);
    EnableIRQ(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE);
    LPTMR_EnableInterrupts(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LPTMR_TYPE, kLPTMR_TimerInterruptEnable);

    LPTMR_StartTimer(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LPTMR_TYPE);

    return TOMMRO_C_ERR_SUCCESS;

#else
    TOMMROC_UTIL_UNUSED_PARAM(msec);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_TMRClose(void) {

#if defined (FSL_FEATURE_SOC_LPTMR_COUNT) && FSL_FEATURE_SOC_LPTMR_COUNT

    LPTMR_StopTimer(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LPTMR_TYPE);

    LPTMR_DisableInterrupts(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LPTMR_TYPE, kLPTMR_TimerInterruptEnable);
    DisableIRQ(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE);
    NVIC_ClearPendingIRQ(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE);

    LPTMR_Deinit(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LPTMR_TYPE);

    return TOMMRO_C_ERR_SUCCESS;

#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

#endif

#endif
