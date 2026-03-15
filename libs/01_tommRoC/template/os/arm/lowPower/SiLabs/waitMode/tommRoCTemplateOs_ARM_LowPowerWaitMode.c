
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs_ARM_LowPowerWaitMode.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)
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

    // Go in sleep EM1
    EMU_EnterEM1();

    return TOMMRO_C_ERR_SUCCESS;
}

void tommRoCTemplateOs_ARM_LowPowerWaitModePostExit(void) {
}

#endif

#endif
