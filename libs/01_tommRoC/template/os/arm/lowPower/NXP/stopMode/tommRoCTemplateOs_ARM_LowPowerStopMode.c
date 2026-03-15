
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs_ARM_LowPowerStopMode.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)
#include "os/arm/lowPower/tommRoCTemplateOs_ARM_TMR.h"
#include "os/arm/RTC/tommRoCTemplateOs_ARM_RTC.h"

#include "os/arm/lowPower/common/tommRoCTemplateOs_ARM_LowPowerCommon.h"

#include "TOMMROC.h"

#include "fsl_flash.h"

#if defined (FSL_FEATURE_SOC_SMC_COUNT) && FSL_FEATURE_SOC_SMC_COUNT
#include "fsl_smc.h"
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

/*******************************************************************************
 * local functions
 ******************************************************************************/
static void _pre_save_funct(void) {

#if defined (FSL_FEATURE_SOC_SMC_COUNT) && FSL_FEATURE_SOC_SMC_COUNT
    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);
#endif
}

static void _in_save_funct(void) {

    // If HW calendar used and it is interrupt based
#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__) && defined (TOMMROC_TEMPLATE_OS__ARM__RTC_INTERRUPT_BASED_IS_USED)
    NVIC_EnableIRQ(TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE);
#endif

    // Enable interrupt used to wake
#if defined (__TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    NVIC_EnableIRQ(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE);
#endif
#if defined (FSL_FEATURE_SOC_LLWU_COUNT) && FSL_FEATURE_SOC_LLWU_COUNT
    NVIC_EnableIRQ(LLWU_IRQn);
#endif
}

static void _post_save_funct(void) {

#if (FSL_FLASH_DRIVER_VERSION != (MAKE_VERSION(2, 0, 0)))
    flash_prefetch_speculation_status_t speculationStatus = {
            kFLASH_prefetchSpeculationOptionDisable, /* Disable instruction speculation.*/
            kFLASH_prefetchSpeculationOptionDisable, /* Disable data speculation.*/
    };

    /*
     * Before enter stop modes, the flash cache prefetch should be disabled.
     * Otherwise the prefetch might be interrupted by stop, then the data and
     * and instruction from flash are wrong.
     */
    FLASH_PflashSetPrefetchSpeculation(&speculationStatus);
#endif
}

static void _pre_restore_funct(void) {

#if (FSL_FLASH_DRIVER_VERSION != (MAKE_VERSION(2, 0, 0)))
    flash_prefetch_speculation_status_t speculationStatus = {
            kFLASH_prefetchSpeculationOptionEnable, /* Enable instruction speculation.*/
            kFLASH_prefetchSpeculationOptionEnable, /* Enable data speculation.*/
    };

    FLASH_PflashSetPrefetchSpeculation(&speculationStatus);
#endif

    // If HW calendar used and it is interrupt based
#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__) && defined (TOMMROC_TEMPLATE_OS__ARM__RTC_INTERRUPT_BASED_IS_USED)
    NVIC_DisableIRQ(TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE);
#endif

    // Enable interrupt used to wake
#if defined (__TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    NVIC_DisableIRQ(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE);
#endif
#if defined (FSL_FEATURE_SOC_LLWU_COUNT) && FSL_FEATURE_SOC_LLWU_COUNT
    NVIC_DisableIRQ(LLWU_IRQn);
#endif
}

/*******************************************************************************
 * functions
 ******************************************************************************/

void tommRoCTemplateOs_ARM_LowPowerStopModePreEnter(void) {

    tommRoCTemplateOs_ARM_LowPowerCommonNVICStatusSave(_pre_save_funct, _in_save_funct, _post_save_funct);
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_LowPowerStopModeEnter(void) {

#if defined (FSL_FEATURE_SOC_SMC_COUNT) && FSL_FEATURE_SOC_SMC_COUNT

#if ((defined (FSL_FEATURE_SMC_HAS_LLS_SUBMODE) && FSL_FEATURE_SMC_HAS_LLS_SUBMODE) || \
     (defined (FSL_FEATURE_SMC_HAS_LPOPO) && FSL_FEATURE_SMC_HAS_LPOPO))

    const smc_power_mode_lls_config_t llsConfig = {
#if defined (FSL_FEATURE_SMC_HAS_LLS_SUBMODE) && FSL_FEATURE_SMC_HAS_LLS_SUBMODE
            // Low-leakage Stop sub-mode
            .subMode = kSMC_StopSub3,
#endif
#if defined (FSL_FEATURE_SMC_HAS_LPOPO) && FSL_FEATURE_SMC_HAS_LPOPO
            .enableLpoClock = true,
#endif /* FSL_FEATURE_SMC_HAS_LPOPO */
    };
#endif

    status_t res;

#if ((defined (FSL_FEATURE_SMC_HAS_LLS_SUBMODE) && FSL_FEATURE_SMC_HAS_LLS_SUBMODE) || \
     (defined (FSL_FEATURE_SMC_HAS_LPOPO) && FSL_FEATURE_SMC_HAS_LPOPO))
    res = SMC_SetPowerModeLls(SMC, &llsConfig);
#else
    res = SMC_SetPowerModeLls(SMC);
#endif

    if (kStatus_Success != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

#else
    // Configure Stop Wait mode (enable deep sleep - SLEEPDEEP=1)
    SCB->SCR |= (uint32_t)(SCB_SCR_SLEEPDEEP_Msk);
    // Disable sleep on exit mode
    SCB->SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPONEXIT_Msk);

    // WFI instruction will start entry into sleep mode
    __DSB();
    __WFI();
    __ISB();
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

void tommRoCTemplateOs_ARM_LowPowerStopModePostExit(void) {

    tommRoCTemplateOs_ARM_LowPowerCommonNVICStatusRestore(_pre_restore_funct, NULL, NULL);
}

#endif

#endif
