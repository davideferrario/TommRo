
#ifndef TOMMROC_HW_TEMPLATE_FILEX_FS_NOT_GUARDED_H_
#define TOMMROC_HW_TEMPLATE_FILEX_FS_NOT_GUARDED_H_

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
#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)
#include "tommRoCHwTemplateFileXFS.h"

#include "TOMMROC.h"
#include "TOMMROCHw.h"

#include "fx_api.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedMediaOpen(void);
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedMediaClose(void);
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedMediaFormat(const uint64_t rawDiskSize);

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFOpen(FX_FILE* filePtr, const char* const path, const uint32_t openType, const bool createIfNotExist);
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFClose(FX_FILE* filePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFRead(FX_FILE* filePtr, void* const bufferPtr, const uint32_t readSize, uint32_t* const readedAmountPtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFWrite(FX_FILE* filePtr, const void* const bufferPtr, const uint32_t writeSize);
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFRelativeSeek(FX_FILE* filePtr, const uint32_t offset, const uint32_t seekFrom);
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFDelete(const char* const path);
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFRename(const char* const pathOld, const char* const pathNew);
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFTruncate(FX_FILE* filePtr, const uint32_t size);
uint32_t tommRoCHwTemplateFileXFSNotGuardedFSize(FX_FILE* filePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFExists(const char* const path, bool* const fileExistsPtr);

#endif

#endif
