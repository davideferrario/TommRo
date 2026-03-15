
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs_ARM_LowPowerStopMode.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)
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
#if defined (__FPU_PRESENT) && __FPU_PRESENT
static inline void _fpu_sleep_prepare(void) {

    uint32_t criticalSpecificData;

    uint32_t original_fpscr;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsEnterCritical(&criticalSpecificData));
    original_fpscr = __get_FPSCR();

    /*
     * Clear FPU exceptions.
     * Without this step, the FPU interrupt is marked as pending,
     * preventing system from sleeping. Exceptions cleared:
     * - IOC - Invalid Operation cumulative exception bit.
     * - DZC - Division by Zero cumulative exception bit.
     * - OFC - Overflow cumulative exception bit.
     * - UFC - Underflow cumulative exception bit.
     * - IXC - Inexact cumulative exception bit.
     * - IDC - Input Denormal cumulative exception bit.
     */
    __set_FPSCR(original_fpscr & ~0x9Fu);
    __DMB();
    NVIC_ClearPendingIRQ(FPU_IRQn);
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsExitCritical(&criticalSpecificData));

    /*
     * The last chance to indicate an error in FPU to the user
     * as the FPSCR is now cleared
     *
     * This assert is related to previous FPU operations
     * and not power management.
     *
     * Critical FPU exceptions signaled:
     * - IOC - Invalid Operation cumulative exception bit.
     * - DZC - Division by Zero cumulative exception bit.
     * - OFC - Overflow cumulative exception bit.
     */
    TOMMROC_ASSERT_ZERO(original_fpscr & 0x7);
}
#endif

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

#if defined (__FPU_PRESENT) && __FPU_PRESENT
    _fpu_sleep_prepare();
#endif

    // Configure Stop Wait mode (enable deep sleep - SLEEPDEEP=1)
    SCB->SCR |= (uint32_t)(SCB_SCR_SLEEPDEEP_Msk);
    // Disable sleep on exit mode
    SCB->SCR &= (uint32_t)~(uint32_t)(SCB_SCR_SLEEPONEXIT_Msk);

    // WFI instruction will start entry into sleep mode
    __DSB();
    __WFI();
    __ISB();






/*
    // Wait for an event.
    __WFE();
    // Clear the internal event register.
    __SEV();
    __WFE();
*/

    return TOMMRO_C_ERR_SUCCESS;
}

void tommRoCTemplateOs_ARM_LowPowerStopModePostExit(void) {

    tommRoCTemplateOs_ARM_LowPowerCommonNVICStatusRestore(_pre_restore_funct, NULL, NULL);
}

#endif

#endif
