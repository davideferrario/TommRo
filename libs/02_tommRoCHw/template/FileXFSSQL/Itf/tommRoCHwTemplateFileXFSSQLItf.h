
#ifndef TOMMROC_HW_TEMPLATE_FAT_FS_SQL_ITF_H_
#define TOMMROC_HW_TEMPLATE_FAT_FS_SQL_ITF_H_

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
#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfOpenFile(
                void*                           const   fileSystemHandlePtr,
        const   char*                           const   filePathStrPtr,
        const   uint32_t                                flags,
                void*                           const   fileHandlePtr);

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfCloseFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr);

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfSyncFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr);

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfTruncateFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr,
        const   uint32_t                                size);

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfSeekFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr,
        const   int32_t                                 offset,
        const   tommRoC_fs_itf_def_seek_whence_enum_t   whence);

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfReadFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr,
                void*                           const   readBufferPtr,
        const   uint32_t                                toReadAmount,
                uint32_t*                       const   readedAmountPtr);

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfWriteFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr,
        const   void*                           const   writeBufferPtr,
        const   uint32_t                                writeBufferLen,
                uint32_t*                       const   writtenAmountPtr);

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfDeleteFile(
                void*                           const   fileSystemHandlePtr,
        const   char*                           const   filePathStrPtr);

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfFileExists(
                void*                           const   fileSystemHandlePtr,
        const   char*                           const   filePathStrPtr,
                bool*                           const   fileExistsPtr);

uint32_t tommRoCHwTemplateFileXFSSQLItfFileSize(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr);

#endif
