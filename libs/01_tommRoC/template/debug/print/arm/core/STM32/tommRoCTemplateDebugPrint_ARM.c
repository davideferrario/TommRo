
#if defined (__TOMMROC_USE_ARM_DEBUG_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "debug/print/arm/core/tommRoCTemplateDebugPrint_ARM.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __SWO_SPEED_HZ__            (640000)

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

void tommRoCTemplateDebugPrint_ARM_OnEnterSetupITM(void) {

    // STM32 specific configuration to enable the TRACESWO IO pin
    DBGMCU->CR |= DBGMCU_CR_TRACE_IOEN; // Enable IO trace pins

    if (!(DBGMCU->CR & DBGMCU_CR_TRACE_IOEN)) {
        // Some (all?) STM32s don't allow writes to DBGMCU register until
        // C_DEBUGEN in CoreDebug->DHCSR is set. This cannot be set by the
        // CPU itself, so in practice you need to connect to the CPU with
        // a debugger once before resetting it.
        return;
   }
}

uint32_t tommRoCTemplateDebugPrint_ARM_GetCpuDebugFreqHz(void) {

    return HAL_RCC_GetSysClockFreq();
}

uint32_t tommRoCTemplateDebugPrint_ARM_GetSWOSpeedHz(void) {

    return (uint32_t) __SWO_SPEED_HZ__;
}

#endif

#endif
