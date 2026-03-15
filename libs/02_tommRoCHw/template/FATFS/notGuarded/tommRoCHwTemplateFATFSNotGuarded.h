
#ifndef TOMMROC_HW_TEMPLATE_FAT_FS_NOT_GUARDED_H_
#define TOMMROC_HW_TEMPLATE_FAT_FS_NOT_GUARDED_H_

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
#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)
#include "tommRoCHwTemplateFATFS.h"

#include "TOMMROC.h"
#include "TOMMROCHw.h"

#include "fatfs.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFOpen(FIL* fp, const char* const path, const uint8_t mode);
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFClose(FIL* fp);
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFRead(FIL* fp, void* const buff, const uint32_t btr, uint32_t* const br);
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFWrite(FIL* fp, const void* const buff, const uint32_t btw, uint32_t* const bw);
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFLSeek(FIL* fp, const uint32_t ofs);
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFDelete(const char* const path);
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFRename(const char* const pathOld, const char* const pathNew);
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFStat(const char* const path, tommRoC_hw_template_fat_fs_info* const fileInfoPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFMount(FATFS* fs, const char* const path, const uint8_t opt);
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFMkfs(char* const path);

uint32_t tommRoCHwTemplateFATFSNotGuardedFSize(FIL* fp);
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFRewind(FIL* fp);
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFExists(const char* const path, bool* const fileExistsPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFMkDir(const char* const path);
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFOpenDir(DIR* dp, const char* const path);
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFCloseDir(DIR* dp);
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFReadDir(DIR* dp, tommRoC_hw_template_fat_fs_info* const dirInfoPtr, tommRoC_hw_template_fat_fs_availability_enum_t* const availabilityPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFRewindDir(DIR* dp);
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFGetFree(uint32_t* const freeSizeBytePtr);
#endif

#endif
