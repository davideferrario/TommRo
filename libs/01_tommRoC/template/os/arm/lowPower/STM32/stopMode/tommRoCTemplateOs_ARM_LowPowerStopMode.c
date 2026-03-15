
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs_ARM_LowPowerStopMode.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)
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

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__) && defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    HAL_NVIC_SetPriority(TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE, 0, 0);
    HAL_NVIC_EnableIRQ(TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE);
#endif
}

static void _pre_restore_funct(void) {

#if defined (__TOMMROC_USE_HW_CALENDAR_OS_TEMPLATE__) && defined (__TOMMROC_USE_HW_CALENDAR_FOR_SLEEP_FOR_MSEC_OS_TEMPLATE__)
    HAL_NVIC_DisableIRQ(TOMMROC_TEMPLATE_OS__ARM__RTC_USED_IRQn_TYPE);
#endif
}

/*******************************************************************************
 * functions
 ******************************************************************************/

void tommRoCTemplateOs_ARM_LowPowerStopModePreEnter(void) {

    tommRoCTemplateOs_ARM_LowPowerCommonNVICStatusSave(NULL, _in_save_funct, NULL);
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_LowPowerStopModeEnter(void) {

    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

    return TOMMRO_C_ERR_SUCCESS;
}

void tommRoCTemplateOs_ARM_LowPowerStopModePostExit(void) {

    tommRoCTemplateOs_ARM_LowPowerCommonNVICStatusRestore(_pre_restore_funct, NULL, NULL);
}

#endif

#endif
