
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateOs_ARM_LowPowerCommonNVICStatus.h"

#include "env/tommRoCTemplateEnv.h"

#include "TOMMROC.h"

#include <stdint.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __CHECK_EXECUTE_FUNCT__(functName)  \
        do {                                \
            if (NULL != functName) {        \
                functName();                \
            }                               \
        } while (0)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static uint32_t _backup_NVIC_int_reg[TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_ICER_SIZE_EAMOUNT];

/*******************************************************************************
 * local functions
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

void tommRoCTemplateOs_ARM_LowPowerCommonNVICStatusSave(
        const   tommRoC_hw_template_os_arm_low_power_common_nvic_status_funct_t preSaveFunct,
        const   tommRoC_hw_template_os_arm_low_power_common_nvic_status_funct_t inSaveFunct,
        const   tommRoC_hw_template_os_arm_low_power_common_nvic_status_funct_t postSaveFunct) {

    uint32_t criticalSpecificData;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsEnterCritical(&criticalSpecificData));

    __CHECK_EXECUTE_FUNCT__(preSaveFunct);

    // Save enabled NVIC interrupt
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy((void*) _backup_NVIC_int_reg, (void*) NVIC->ICER, TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_ICER_SIZE_BYTE));
    // Disable all interrupt
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet((void*) NVIC->ICER, 0xFF, TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_ICER_SIZE_BYTE));

    __CHECK_EXECUTE_FUNCT__(inSaveFunct);

    __ISB();

    __CHECK_EXECUTE_FUNCT__(postSaveFunct);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsExitCritical(&criticalSpecificData));
}

void tommRoCTemplateOs_ARM_LowPowerCommonNVICStatusRestore(
        const   tommRoC_hw_template_os_arm_low_power_common_nvic_status_funct_t preRestoreFunct,
        const   tommRoC_hw_template_os_arm_low_power_common_nvic_status_funct_t inRestoreFunct,
        const   tommRoC_hw_template_os_arm_low_power_common_nvic_status_funct_t postRestoreFunct) {

    uint32_t criticalSpecificData;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsEnterCritical(&criticalSpecificData));

    __CHECK_EXECUTE_FUNCT__(preRestoreFunct);

    // Restore saved enabled NVIC interrupt
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy((void*) NVIC->ISER, (void*) _backup_NVIC_int_reg, TOMMROC_TEMPLATE_ENV_ARM_DEF_NVIC_ICER_SIZE_BYTE));

    __CHECK_EXECUTE_FUNCT__(inRestoreFunct);

    __ISB();

    __CHECK_EXECUTE_FUNCT__(postRestoreFunct);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsExitCritical(&criticalSpecificData));
}

#endif
