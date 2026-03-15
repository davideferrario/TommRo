
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs_ARM_SysTick.h"

#include "os/arm/lowPower/tommRoCTemplateOs_ARM_LowPower.h"

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
#if defined (TOMMROC_TEMPLATE_OS__ARM__SYSTICK_IS_USED)
static void _inc_msec(const uint32_t msec) {

    tommRoCSoftUptimeIncMSec(msec);

#if defined (__TOMMROC_USE_SOFT_CALENDAR_OS_TEMPLATE__)
    tommRoCSoftCalendarIncMSec(msec);
#endif
}

// SysTick IRQ handler
__attribute__((weak))
void SysTick_Handler(void) {
    _inc_msec(1);
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (TOMMROC_TEMPLATE_OS__ARM__SYSTICK_IS_USED)

tommRoC_err_enum_t tommRoCTemplateOs_ARM_SysTickInit(void) {

#if defined (__TOMMROC_TEMPLATE_ARM_ATMEL_IS_USED__)
    const uint32_t sysTickTicks = SystemCoreClock;
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_GD32_IS_USED__)
    const uint32_t sysTickTicks = SystemCoreClock;
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)
    const uint32_t sysTickTicks = SystemCoreClock;
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)
    const uint32_t sysTickTicks = CLOCK_GetFreq(kCLOCK_CoreSysClk);
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)
    const uint32_t sysTickTicks = CMU_ClockFreqGet(cmuClock_CORE);
#endif

    if (0 != SysTick_Config(sysTickTicks / 1000U)) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

void tommRoCTemplateOs_ARM_SysTickClose(void) {
    tommRoCTemplateOs_ARM_SysTickDisable();
}

void tommRoCTemplateOs_ARM_SysTickEnable(void) {
    // Enable SysTick timer
    SysTick->CTRL |= (SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
}

void tommRoCTemplateOs_ARM_SysTickDisable(void) {
    // Disable SysTick timer
    SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
}

tommRoC_err_enum_t tommRoCTemplateOs_ARM_SysTickDelayMsec(const uint32_t msec) {

    tommRoC_timer_t timer;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTimerStart(&timer, msec));

    while (TOMMRO_C_TIMER_NOT_EXPIRED_ERR == tommRoCTimerIsExpired(&timer)) {

        TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCTemplateOs_ARM_LowPowerWait());
    }

    return TOMMRO_C_ERR_SUCCESS;
}

uint32_t tommRoCTemplateOs_ARM_SysTickGetUptimeMsec(void) {
    return tommRoCSoftUptimeGetMSec();
}

void tommRoCTemplateOs_ARM_SysTickIncMSec(const uint32_t msec) {
    _inc_msec(msec);
}

#endif

#endif
