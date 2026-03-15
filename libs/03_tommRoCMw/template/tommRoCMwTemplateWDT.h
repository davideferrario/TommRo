
#ifndef TOMMROC_MW_TEMPLATE_WDT_H_
#define TOMMROC_MW_TEMPLATE_WDT_H_

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
#include "TOMMROCMw.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateWDTInit(
        const   void*                           const   appThreadIDTablePtr,
        const   uint8_t                                 appThreadIDTableAmount,
        const   tommRoC_mw_wdt_refresh_funct_t          refreshFunctPtr,
                void*                           const   refreshFunctInOutPtr,
                tommRoC_mw_wdt_t*               const   WDTArrayPtr,
        const   uint8_t                                 WDTArrayAmount,
        const   uint32_t                                WDTTimeoutMsec);

tommRoC_mw_err_enum_t tommRoCMwTemplateWDTClose(void);

tommRoC_mw_err_enum_t tommRoCMwTemplateWDTCheck(
                uint8_t*                        const   wdtExpiredAmountPtr,
                uint8_t*                        const   expiredTaskIDArrayPtr,
        const   uint8_t                                 expiredTaskIDArraySize);

tommRoC_mw_err_enum_t tommRoCMwTemplateWDTDisable(void);
tommRoC_mw_err_enum_t tommRoCMwTemplateWDTEnable(void);

tommRoC_mw_err_enum_t tommRoCMwTemplateWDTTaskDisable(void);
tommRoC_mw_err_enum_t tommRoCMwTemplateWDTTaskEnable(void);

#endif
