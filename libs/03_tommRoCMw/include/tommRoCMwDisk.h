
#ifndef TOMMROC_MW_DISK_H_
#define TOMMROC_MW_DISK_H_

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
#include "tommRoCMwErr.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

 /*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Check if tommRoC middleware disk environment is available.
 *
 * return tommRoC_mw_err_enum_t
 *          TOMMRO_C_MW_ERR_SUCCESS         -> disk environment available.
 *          TOMMRO_C_MW_NOT_AVAILABLE_ERR   -> disk environment not available.
 */
tommRoC_mw_err_enum_t tommRoCMwDiskIsAvailable(void);

/**
 * Make a folder.
 *
 * param[in]    folderNameStrPtr        new folder name string.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwDiskMakeFolder(
        const   char*   const   folderNameStrPtr);

/**
 * Remove a file or folder.
 * NOTE: not empty folder will be removed too.
 *
 * param[in]    nameStrPtr              file or folder name string.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwDiskRemove(
        const   char*   const   nameStrPtr);

#endif
