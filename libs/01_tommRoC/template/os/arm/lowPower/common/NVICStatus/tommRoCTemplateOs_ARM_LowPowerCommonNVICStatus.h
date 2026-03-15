
#ifndef TOMMROC_TEMPLATE_OS__ARM__LOW_POWER_COMMON_NVIC_STATUS_H_
#define TOMMROC_TEMPLATE_OS__ARM__LOW_POWER_COMMON_NVIC_STATUS_H_

/*
 *******************************************************************************
 * License
 * (C) Copyright 2017
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications according to the supply agreement.
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: this software is provided
 * "AS IS", with no express or implied warranties of any kind, including,
 * but not limited to, any implied warranties of merchantability or
 * fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Supplier will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 */

/**
 * Author
 * TommRo Software Department
 */

#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
// tommRoC hardware layer bus callback functions type definition.
typedef void (*tommRoC_hw_template_os_arm_low_power_common_nvic_status_funct_t)(void);

/*******************************************************************************
 * functions
 ******************************************************************************/

void tommRoCTemplateOs_ARM_LowPowerCommonNVICStatusSave(
        const   tommRoC_hw_template_os_arm_low_power_common_nvic_status_funct_t preSaveFunct,
        const   tommRoC_hw_template_os_arm_low_power_common_nvic_status_funct_t inSaveFunct,
        const   tommRoC_hw_template_os_arm_low_power_common_nvic_status_funct_t postSaveFunct);

void tommRoCTemplateOs_ARM_LowPowerCommonNVICStatusRestore(
        const   tommRoC_hw_template_os_arm_low_power_common_nvic_status_funct_t preRestoreFunct,
        const   tommRoC_hw_template_os_arm_low_power_common_nvic_status_funct_t inRestoreFunct,
        const   tommRoC_hw_template_os_arm_low_power_common_nvic_status_funct_t postRestoreFunct);

#endif

#endif
