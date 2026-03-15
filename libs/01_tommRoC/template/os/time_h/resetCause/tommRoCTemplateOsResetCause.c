
#if defined (__TOMMROC_USE_RESET_CAUSE_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/tommRoCTemplateOsResetCause.h"

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_USE_TIME_TIME_H_OS_TEMPLATE__)

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
static tommRoC_os_reset_cause_enum_t _reset_cause = TOMMRO_C_OS_RESET_CAUSE_POWER_ON;

/*******************************************************************************
 * local functions
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_os_reset_cause_enum_t tommRoCTemplateOsResetCause(void) {
    return _reset_cause;
}

tommRoC_err_enum_t tommRoCTemplateOsClearResetCause(void) {
    _reset_cause = TOMMRO_C_OS_RESET_CAUSE_UNKNOWN;
    return TOMMRO_C_ERR_SUCCESS;
}

#endif

#endif
