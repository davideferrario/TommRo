
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/tommRoCTemplateOsCritical.h"

#include "env/tommRoCTemplateEnv.h"

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

    uint32_t uwPRIMASK_Bit;

    uwPRIMASK_Bit = __get_PRIMASK();    // Backup PRIMASK bit
    __disable_irq();                    // Disable all interrupts by setting PRIMASK bit on Cortex
    __DMB();

    *specificDataPtr = uwPRIMASK_Bit;

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsCriticalExit(uint32_t* const specificDataPtr) {

    uint32_t uwPRIMASK_Bit;

    uwPRIMASK_Bit = *specificDataPtr;

    __DMB();
    __set_PRIMASK(uwPRIMASK_Bit);       // Restore PRIMASK bit
    if (0U == uwPRIMASK_Bit) {
        __enable_irq();                 // Enable all interrupts by setting PRIMASK bit on Cortex
    }
    __ISB();

    return TOMMRO_C_ERR_SUCCESS;
}

#endif
