
#if defined (__TOMMROC_USE_RESET_CAUSE_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/tommRoCTemplateOsResetCause.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_STM32_IS_USED__)

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

tommRoC_os_reset_cause_enum_t tommRoCTemplateOsResetCause(void) {

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)

#if defined (RCC_FLAG_LPWRRST)
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST)) {
        return TOMMRO_C_OS_RESET_CAUSE_LOW_POWER;
    }
#endif
#if defined (RCC_FLAG_WWDGRST)
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST)) {
        return TOMMRO_C_OS_RESET_CAUSE_WATCHDOG;
    }
#endif
#if defined (RCC_FLAG_IWDGRST)
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST)) {
        return TOMMRO_C_OS_RESET_CAUSE_WATCHDOG;
    }
#endif
#if defined (RCC_FLAG_SFTRST)
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST)) {
        // This reset is induced by calling the ARM CMSIS NVIC_SystemReset() function
        return TOMMRO_C_OS_RESET_CAUSE_CPU_SOFTWARE;
    }
#endif
#if defined (RCC_FLAG_PORRST)
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST)) {
        return TOMMRO_C_OS_RESET_CAUSE_POWER_ON;
    }
#endif
#if defined (RCC_FLAG_PINRST)
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST)) {
        return TOMMRO_C_OS_RESET_CAUSE_EXTERNAL_PIN;
    }
#endif
#if defined (RCC_FLAG_BORRST)
    // Needs to come *after* checking the `RCC_FLAG_PORRST` flag in order to ensure first that the reset cause is NOT a POR/PDR reset.
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST)) {
        return TOMMRO_C_OS_RESET_CAUSE_BROWN_DOWN;
    }
#endif
#if defined (RCC_FLAG_OBLRST)
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_OBLRST)) {
        return TOMMRO_C_OS_RESET_CAUSE_OPTION_BYTE_LOADER;
    }
#endif
#if defined (RCC_FLAG_V18PWRRST)
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_V18PWRRST)) {
        return TOMMRO_C_OS_RESET_CAUSE_LOW_POWER;
    }
#endif
#if defined (RCC_FLAG_FWRST)
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_FWRST)) {
        return TOMMRO_C_OS_RESET_CAUSE_CPU_SOFTWARE;
    }
#endif
#endif

    return TOMMRO_C_OS_RESET_CAUSE_UNKNOWN;
}

tommRoC_err_enum_t tommRoCTemplateOsClearResetCause(void) {

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)
    __HAL_RCC_CLEAR_RESET_FLAGS();
    return TOMMRO_C_ERR_SUCCESS;
#else
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

#endif

#endif
