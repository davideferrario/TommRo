
#if defined (__TOMMROC_MW_USE_THREAD_NXP_OSA_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_NXP_OSA_Critical.h"

#include "rtos/nxpOSA/common/compatibility/tommRoCMwTemplateRTOS_NXP_OSA_Compatibility.h"

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

tommRoC_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_CriticalEnter(uint32_t* const specificDataPtr) {
    TOMMROC_UTIL_UNUSED_PARAM(specificDataPtr);
    OSA_InterruptDisable();
    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCMwTemplateRTOS_NXP_OSA_CriticalExit(uint32_t* const specificDataPtr) {
    TOMMROC_UTIL_UNUSED_PARAM(specificDataPtr);
    OSA_InterruptEnable();
    return TOMMRO_C_ERR_SUCCESS;
}

#endif
