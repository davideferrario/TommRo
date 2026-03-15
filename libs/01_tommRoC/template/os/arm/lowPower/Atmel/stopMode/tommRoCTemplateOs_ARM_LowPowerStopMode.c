
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs_ARM_LowPowerStopMode.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_ATMEL_IS_USED__)
#include "os/arm/lowPower/common/tommRoCTemplateOs_ARM_LowPowerCommon.h"

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
static void _in_save_funct(void) {

    // If HW calendar used and it is interrupt based
#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
    NVIC_EnableIRQ(RTC_IRQn);
#endif
}

static void _pre_restore_funct(void) {

    // If HW calendar used and it is interrupt based
#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__)
    NVIC_DisableIRQ(RTC_IRQn);
#endif
}

/*******************************************************************************
 * functions
 ******************************************************************************/

void tommRoCTemplateOs_ARM_LowPowerStopModePreEnter(void) {

    tommRoCTemplateOs_ARM_LowPowerCommonNVICStatusSave(NULL, _in_save_funct, NULL);
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_LowPowerStopModeEnter(void) {

    // Configure Stop Wait mode (enable deep sleep - SLEEPDEEP=1)
    SCB->SCR |= (uint32_t)(SCB_SCR_SLEEPDEEP_Msk);
    // Disable sleep on exit mode
    SCB->SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPONEXIT_Msk);

    // WFI instruction will start entry into sleep mode
    __DSB();
    __WFI();
    __ISB();

    return TOMMRO_C_ERR_SUCCESS;
}

void tommRoCTemplateOs_ARM_LowPowerStopModePostExit(void) {

    tommRoCTemplateOs_ARM_LowPowerCommonNVICStatusRestore(_pre_restore_funct, NULL, NULL);
}

#endif

#endif
