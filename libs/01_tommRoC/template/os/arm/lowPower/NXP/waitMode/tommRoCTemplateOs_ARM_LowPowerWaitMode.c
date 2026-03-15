
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs_ARM_LowPowerWaitMode.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)
#include "TOMMROC.h"

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

/*******************************************************************************
 * functions
 ******************************************************************************/

void tommRoCTemplateOs_ARM_LowPowerWaitModePreEnter(void) {

#if defined (FSL_SMC_DRIVER_VERSION)
    SMC_PreEnterWaitModes();
#endif
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_LowPowerWaitModeEnter(void) {

#if defined (FSL_SMC_DRIVER_VERSION)
    if (kStatus_Success != SMC_SetPowerModeWait(SMC)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

#else
    // Configure Normal Wait mode (disable deep sleep - SLEEPDEEP=0)
    SCB->SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPDEEP_Msk);
    // Disable sleep on exit mode
    SCB->SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPONEXIT_Msk);

    // WFI instruction will start entry into sleep mode
    __DSB();
    __WFI();
    __ISB();
#endif

    return TOMMRO_C_ERR_SUCCESS;
}

void tommRoCTemplateOs_ARM_LowPowerWaitModePostExit(void) {

#if defined (FSL_SMC_DRIVER_VERSION)
    SMC_PostExitWaitModes();
#endif
}

#endif

#endif
