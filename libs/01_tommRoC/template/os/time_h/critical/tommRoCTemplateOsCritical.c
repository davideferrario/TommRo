
#if defined (__TOMMROC_USE_TIME_TIME_H_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/tommRoCTemplateOsCritical.h"

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
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalClose(void) {
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalEnter(uint32_t* const specificDataPtr) {
    TOMMROC_UTIL_UNUSED_PARAM(specificDataPtr);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalExit(uint32_t* const specificDataPtr) {
    TOMMROC_UTIL_UNUSED_PARAM(specificDataPtr);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
}

#endif
