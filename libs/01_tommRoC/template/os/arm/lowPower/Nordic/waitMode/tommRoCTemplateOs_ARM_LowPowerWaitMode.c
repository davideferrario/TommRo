
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs_ARM_LowPowerWaitMode.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)
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

    /**
     * NOTE:
     *
     * on Nordic ARM Cortex MCU, SysTick's clock will only tick when the CPU is running
     * or when the system is in debug interface mode.
     * SysTick's clock is disabled in FWI instrucion
     */

    __asm("NOP");

    return TOMMRO_C_ERR_SUCCESS;
}

void tommRoCTemplateOs_ARM_LowPowerWaitModePostExit(void) {
}

#endif

#endif
