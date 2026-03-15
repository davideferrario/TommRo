
#if defined (__TOMMROC_MW_USE_THREAD_WINDOWS_H_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_Windows_h_Os.h"

#include "TOMMROC.h"

#include <windows.h>

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
static tommRoC_err_enum_t _delay_msec(const uint32_t msec) {

    /**
     * NOTE:
     * as described in "tommRoCOsDelayMsec" function interface, in case of multitasking environment, if delay param is zero, a task yield must be performed.
     */
    if (0 == msec) {
        SwitchToThread();
        return TOMMRO_C_ERR_SUCCESS;
    }

    Sleep(msec);

    return TOMMRO_C_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_OsStart(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsInitDelayMsec(_delay_msec),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_Windows_h_OsStop(void) {

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCOsCloseEnv(TOMMRO_C_OS_DELAY_MSEC_FUNCT),
            TOMMRO_C_MW_LOW_LEVEL_ERR);

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
