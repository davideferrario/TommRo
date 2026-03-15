
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs_ARM_LowPowerStopMode.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)
#include "os/arm/lowPower/tommRoCTemplateOs_ARM_TMR.h"
#include "os/arm/RTC/tommRoCTemplateOs_ARM_RTC.h"

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
#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__) && defined (TOMMROC_TEMPLATE_OS__ARM__RTC_INTERRUPT_BASED_IS_USED)
    NVIC_EnableIRQ(TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE);
#endif

    // Enable interrupt used to wake
#if defined (__TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    NVIC_EnableIRQ(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE);
#endif
}

static void _pre_restore_funct(void) {

    // If HW calendar used and it is interrupt based
#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__) && defined (TOMMROC_TEMPLATE_OS__ARM__RTC_INTERRUPT_BASED_IS_USED)
    NVIC_DisableIRQ(TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE);
#endif

    // Enable interrupt used to wake
#if defined (__TOMMROC_USE_HW_TIMER_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    NVIC_DisableIRQ(TOMMROC_TEMPLATE_OS__ARM__TMR_USED_IRQn_TYPE);
#endif
}

/*******************************************************************************
 * functions
 ******************************************************************************/

void tommRoCTemplateOs_ARM_LowPowerStopModePreEnter(void) {

    tommRoCTemplateOs_ARM_LowPowerCommonNVICStatusSave(NULL, _in_save_funct, NULL);
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_LowPowerStopModeEnter(void) {

    // Go in sleep EM2
    EMU_EnterEM2(true);

    return TOMMRO_C_ERR_SUCCESS;
}

void tommRoCTemplateOs_ARM_LowPowerStopModePostExit(void) {

    tommRoCTemplateOs_ARM_LowPowerCommonNVICStatusRestore(_pre_restore_funct, NULL, NULL);
}

#endif

#endif
