
#ifndef TOMMROC_MW_TEMPLATE_RTOS_EVENT_U32_H_
#define TOMMROC_MW_TEMPLATE_RTOS_EVENT_U32_H_

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
#include "tommRoCMwTemplateRTOSEvent.h"

#if defined (__TOMMROC_MW_EVENT_TEMPLATE_IS_USED__)
#include "TOMMROCMw.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/
#define TOMMROC_MW_TEMPLATE_RTOS_EVENT_U32_NOT_AVAILABLE_EVENT  (0)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSEventU32Start(const uint8_t maxEventAmount);
tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSEventU32Stop(void);

bool tommRoCMwTemplateRTOSEventU32IsStarted(void);

uint32_t tommRoCMwTemplateRTOSEventU32GetFirstAvailable(void);
tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSEventU32Destroy(const uint32_t event);

#endif

#endif
