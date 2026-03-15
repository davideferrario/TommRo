
#if defined (__TOMMROC_USE_TIME_XC_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/tommRoCTemplateOsCritical.h"

#include "mcc.h"

#include <xc.h>

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

tommRoC_err_enum_t tommRoCTemplateOsCriticalInit(void) {
    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalClose(void) {
    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalEnter(uint32_t* const specificDataPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(specificDataPtr);

    // Disable the global interrupt
    INTCONbits.GIE = 0;

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalExit(uint32_t* const specificDataPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(specificDataPtr);

    // Enable the global interrupt
    INTCONbits.GIE = 1;

    return TOMMRO_C_ERR_SUCCESS;
}

#endif
