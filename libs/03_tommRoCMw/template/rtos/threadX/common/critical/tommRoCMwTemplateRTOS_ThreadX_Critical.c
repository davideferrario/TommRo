
#if defined (__TOMMROC_MW_USE_THREAD_THREADX_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_ThreadX_Critical.h"

#include "rtos/threadX/common/compatibility/tommRoCMwTemplateRTOS_ThreadX_Compatibility.h"

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

tommRoC_err_enum_t tommRoCMwTemplateRTOS_ThreadX_CriticalEnter(uint32_t* const specificDataPtr) {
    TX_INTERRUPT_SAVE_AREA;
    TX_DISABLE;
    *specificDataPtr = (uint32_t) interrupt_save;
    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCMwTemplateRTOS_ThreadX_CriticalExit(uint32_t* const specificDataPtr) {
    TX_INTERRUPT_SAVE_AREA;
    interrupt_save = (UINT) (*specificDataPtr);
    TX_RESTORE;
    return TOMMRO_C_ERR_SUCCESS;
}

#endif
