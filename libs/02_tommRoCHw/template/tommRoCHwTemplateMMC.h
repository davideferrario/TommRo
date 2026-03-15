
#ifndef TOMMROC_HW_TEMPLATE_MMC_H_
#define TOMMROC_HW_TEMPLATE_MMC_H_

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

/**
 *  - Hardware MMC
 *      - __TOMMROC_HW_USE_MMC_x_TEMPLATE__             hardware MMC device
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROCHw.h"

/*******************************************************************************
 * defines
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_MMC_0_TEMPLATE__) ||  \
    defined (__TOMMROC_HW_USE_MMC_1_TEMPLATE__) ||  \
    defined (__TOMMROC_HW_USE_MMC_2_TEMPLATE__)     \

#define __TOMMROC_HW_TEMPLATE_MMC_AT_LEAST_ONE_IS_USED__
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Generic bus start function prototype.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_mmc_start_funct_t)(tommRoC_hw_mmc_t* const MMCHandlePtr);

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateMMC0Start(tommRoC_hw_mmc_t* const MMCHandlePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateMMC1Start(tommRoC_hw_mmc_t* const MMCHandlePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateMMC2Start(tommRoC_hw_mmc_t* const MMCHandlePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateMMC3Start(tommRoC_hw_mmc_t* const MMCHandlePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateMMC4Start(tommRoC_hw_mmc_t* const MMCHandlePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateMMC5Start(tommRoC_hw_mmc_t* const MMCHandlePtr);

#endif
