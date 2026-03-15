
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs_ARM_LowPowerLLWU.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#include "TOMMROC.h"

#if defined (FSL_FEATURE_SOC_LLWU_COUNT) && FSL_FEATURE_SOC_LLWU_COUNT
#include "fsl_llwu.h"
#endif

#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
#include "fsl_rtc.h"
#endif

#if defined (__TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
#include "fsl_lptmr.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__)
#define __LLWU_WAKEUP_SOURCE_IDX_LPTMR__            (LLWU_ME_WUME0_SHIFT)
#define __LLWU_WAKEUP_SOURCE_IDX_CMP0__             (LLWU_ME_WUME1_SHIFT)
#define __LLWU_WAKEUP_SOURCE_IDX_CMP1__             (LLWU_ME_WUME2_SHIFT)
#define __LLWU_WAKEUP_SOURCE_IDX_RTC_ALARM__        (LLWU_ME_WUME5_SHIFT)
#define __LLWU_WAKEUP_SOURCE_IDX_RTC_SECONDS__      (LLWU_ME_WUME7_SHIFT)
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)
#define __LLWU_WAKEUP_SOURCE_IDX_LPTMR__            (LLWU_ME_WUME0_SHIFT)
#define __LLWU_WAKEUP_SOURCE_IDX_CMP0__             (LLWU_ME_WUME1_SHIFT)
#define __LLWU_WAKEUP_SOURCE_IDX_RADIO__            (LLWU_ME_WUME2_SHIFT)
#define __LLWU_WAKEUP_SOURCE_IDX_DCDC__             (LLWU_ME_WUME3_SHIFT)
#define __LLWU_WAKEUP_SOURCE_IDX_TSI__              (LLWU_ME_WUME4_SHIFT)
#define __LLWU_WAKEUP_SOURCE_IDX_RTC_ALARM__        (LLWU_ME_WUME5_SHIFT)
#define __LLWU_WAKEUP_SOURCE_IDX_RTC_SECONDS__      (LLWU_ME_WUME7_SHIFT)
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
#endif


#if defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
#define __LLWU_WAKEUP_MODULE_IDX__      (__LLWU_WAKEUP_SOURCE_IDX_RTC_ALARM__)
#endif

#if defined (__TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
#define __LLWU_WAKEUP_MODULE_IDX__      (__LLWU_WAKEUP_SOURCE_IDX_LPTMR__)
#endif

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (FSL_FEATURE_SOC_LLWU_COUNT) && FSL_FEATURE_SOC_LLWU_COUNT
static tommRoC_template_os_ARM_low_power_llwu_callback_t _internal_wakeup_callback = NULL;
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if defined (FSL_FEATURE_SOC_LLWU_COUNT) && FSL_FEATURE_SOC_LLWU_COUNT && defined (__LLWU_WAKEUP_MODULE_IDX__)
// LLWU IRQ handler
__attribute__((weak))
void LLWU_IRQHandler(void) {

    // If wakeup by internal module
    if (LLWU_GetInternalWakeupModuleFlag(LLWU, __LLWU_WAKEUP_MODULE_IDX__)) {

#if (__LLWU_WAKEUP_MODULE_IDX__ == __LLWU_WAKEUP_SOURCE_IDX_RTC_ALARM__)
        RTC_DisableInterrupts(RTC, kRTC_AlarmInterruptEnable);
#endif

#if (__LLWU_WAKEUP_MODULE_IDX__ == __LLWU_WAKEUP_SOURCE_IDX_LPTMR__)
        LPTMR_DisableInterrupts(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LPTMR_TYPE, kLPTMR_TimerInterruptEnable);
        LPTMR_ClearStatusFlags(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LPTMR_TYPE, kLPTMR_TimerCompareFlag);
        LPTMR_StopTimer(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_LPTMR_TYPE);
#endif

        if (NULL != _internal_wakeup_callback) {
            _internal_wakeup_callback();
        }
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

tommRoC_err_enum_t tommRoCTemplateOs_ARM_LowPowerLLWUInit(void) {

#if defined (FSL_FEATURE_SOC_LPTMR_COUNT) && FSL_FEATURE_SOC_LPTMR_COUNT && defined (__LLWU_WAKEUP_MODULE_IDX__)
    NVIC_ClearPendingIRQ(LLWU_IRQn);
    LLWU_EnableInternalModuleInterruptWakup(LLWU, __LLWU_WAKEUP_MODULE_IDX__, true);
    EnableIRQ(LLWU_IRQn);
    return TOMMRO_C_ERR_SUCCESS;
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_LowPowerLLWUClose(void) {

#if defined (FSL_FEATURE_SOC_LPTMR_COUNT) && FSL_FEATURE_SOC_LPTMR_COUNT && defined (__LLWU_WAKEUP_MODULE_IDX__)
    DisableIRQ(LLWU_IRQn);
    LLWU_EnableInternalModuleInterruptWakup(LLWU, __LLWU_WAKEUP_MODULE_IDX__, false);
    NVIC_ClearPendingIRQ(LLWU_IRQn);
    return TOMMRO_C_ERR_SUCCESS;
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

void tommRoCTemplateOs_ARM_LowPowerLLWUSetInternalWakeupCallback(const tommRoC_template_os_ARM_low_power_llwu_callback_t callback) {

#if defined (FSL_FEATURE_SOC_LPTMR_COUNT) && FSL_FEATURE_SOC_LPTMR_COUNT
    _internal_wakeup_callback = callback;
#else
    TOMMROC_UTIL_UNUSED_PARAM(callback);
#endif
}

#endif

#endif
