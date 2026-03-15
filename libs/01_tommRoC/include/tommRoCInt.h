
#ifndef TOMMROC_INT_H_
#define TOMMROC_INT_H_

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
 * @defgroup tommRoCInt tommRoCInt
 *
 * @brief  TommRoC library integer module
 * @author TommRo Software Department
 *
 * This module is providing (standard) integer functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/
#if defined (UINT8_MAX)
#define TOMMROC_INT_UINT8_SUPPORTED
#endif
#if defined (UINT16_MAX)
#define TOMMROC_INT_UINT16_SUPPORTED
#endif
#if defined (UINT32_MAX)
#define TOMMROC_INT_UINT32_SUPPORTED
#endif
#if defined (UINT64_MAX)
#define TOMMROC_INT_UINT64_SUPPORTED
#endif

#if defined (INT8_MAX)
#define TOMMROC_INT_INT8_SUPPORTED
#endif
#if defined (INT16_MAX)
#define TOMMROC_INT_INT16_SUPPORTED
#endif
#if defined (INT32_MAX)
#define TOMMROC_INT_INT32_SUPPORTED
#endif
#if defined (INT64_MAX)
#define TOMMROC_INT_INT64_SUPPORTED
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * @}
 */

#endif
