
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs_ARM_LowPowerWaitMode.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)
#include "TOMMROC.h"

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
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_LowPowerWaitModeEnter(void) {

    // Configure Normal Wait mode (disable deep sleep - SLEEPDEEP=0)
    SCB->SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPDEEP_Msk);
    // Disable sleep on exit mode
    SCB->SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPONEXIT_Msk);

    // WFI instruction will start entry into sleep mode
    __DSB();
    __WFI();
    __ISB();

    return TOMMRO_C_ERR_SUCCESS;
}

void tommRoCTemplateOs_ARM_LowPowerWaitModePostExit(void) {
}

#endif

#endif
