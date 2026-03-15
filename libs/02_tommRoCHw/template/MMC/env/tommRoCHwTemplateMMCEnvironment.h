
#ifndef TOMMROC_HW_TEMPLATE_MMC_ENVIRONMENT_H_
#define TOMMROC_HW_TEMPLATE_MMC_ENVIRONMENT_H_

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

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROCHw.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_HW_USE_MMC_0_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateMMCEnvironment0Start(
                tommRoC_hw_mmc_cb_funct_t*  const   cbFunctPtr);
#endif

#if defined (__TOMMROC_HW_USE_MMC_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateMMCEnvironment1Start(
                tommRoC_hw_mmc_cb_funct_t*  const   cbFunctPtr);
#endif

#if defined (__TOMMROC_HW_USE_MMC_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateMMCEnvironment2Start(
                tommRoC_hw_mmc_cb_funct_t*  const   cbFunctPtr);
#endif

#if defined (__TOMMROC_HW_USE_MMC_3_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateMMCEnvironment3Start(
                tommRoC_hw_mmc_cb_funct_t*  const   cbFunctPtr);
#endif

#if defined (__TOMMROC_HW_USE_MMC_4_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateMMCEnvironment4Start(
                tommRoC_hw_mmc_cb_funct_t*  const   cbFunctPtr);
#endif

#if defined (__TOMMROC_HW_USE_MMC_5_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateMMCEnvironment5Start(
                tommRoC_hw_mmc_cb_funct_t*  const   cbFunctPtr);
#endif

#endif
