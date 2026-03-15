
#ifndef TOMMROC_HW_VERSION_H_
#define TOMMROC_HW_VERSION_H_

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
#include "tommRoCHwErr.h"

#include "TOMMROC.h"

#include <stdbool.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// Library version
#define TOMMROC_HW_VERSION_MAJOR    1   // NOTE: don't use () because it is not compatible with define string conversion
#define TOMMROC_HW_VERSION_MINOR    3
#define TOMMROC_HW_VERSION_PATCH    16

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Get tommRoCHw library version.
 *
 * param[out]       libVersionPtr       pointer to library version result.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwVersionGet(
                tommRoC_version_t*  const   libVersionPtr);

/**
 * Get tommRoCHw library version as string.
 *
 * return const char*
 */
const char* tommRoCHwVersionGetAsStr(void);

/**
 * Get tommRoCHw library compiled as debug status.
 *
 * return bool
 */
bool tommRoCHwVersionIsDbg(void);

#endif
