
#ifndef TOMMROC_FILE_X_MBED_H_
#define TOMMROC_FILE_X_MBED_H_

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
 * @defgroup tommRoCFileXMbed tommRoCFileXMbed
 *
 * @brief  TommRoC library embedded file system fileX module
 * @author TommRo Software Department
 *
 * This module is providing library embedded hardware abstracted file system fileX functionality.
 * It can be used in case of application needs only one file system.
 * Please note that it is based on FileX (https://github.com/eclipse-threadx/filex) library.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCFileX.h"

#include <stdbool.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* File system framework management functions */

/**
 * Init Mbed file system fileX framework.
 * Mbed file system fileX framework is a layer build over tommRoCFileX to be used when only one file system fileX is needed by application.
 * The file system handler is hide to application by this layer.
 * NOTE: the file system framework start as disabled. Application must enable when ready.
 *
 * param[in]        fileXHandlePtr          file system handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedInit(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr);

/**
 * Close Mbed file system fileX framework.
 * The low layer file system is closed (un-mount) and the internal file system fileX framework is resetted to initial value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedClose(void);

/**
 * Enable Mbed file system fileX framework.
 * NOTE: the file system framework start ad disabled. Application must enable when ready.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedEnable(void);

/**
 * Get Mbed file system fileX framework enabling status.
 *
 * return bool
 */
bool tommRoCFileXMbedIsEnabled(void);

/**
 * Get last Mbed file system fileX framework operation result.
 *
 * return tommRoC_file_x_error_enum_t
 */
tommRoC_file_x_error_enum_t tommRoCFileXMbedGetLastOpResult(void);

/**
 * Get is busy (one operation is in execution) status of Mbed file system fileX framework.
 *
 * return bool
 */
bool tommRoCFileXMbedGetIsBusy(void);


/******************* Disk functions */

/**
 * Format the Mbed file system fileX disk.
 * NOTE: format is the only operation available also if FileX is not enabled.
 * NOTE: the format is executed only when there are no opened files/directories.
 *
 * param[in]        timeoutMsec             wait for no opened files/directories timeout [msec]. TOMMROC_FILE_X_DISK_FORMAT_WAIT_FOREVER_TIMEOUT for wait forever.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedDiskFormat(
        const   uint32_t                                        timeoutMsec);

/**
 * Get size of the Mbed file system fileX disk [byte].
 *
 * param[out]       totalSizePtr            size of the disk [byte] pointer.
 * param[out]       usedSizePtr             current used size [byte] in the disk.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedDiskGetSize(
                uint32_t*                               const   totalSizePtr,
                uint32_t*                               const   usedSizePtr);


/******************* File system functions */

/**
 * Get info about a file or directory.
 *
 * param[in]        pathStrPtr              path/file name string pointer.
 * param[out]       infoPtr                 file or directory info structure pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedStat(
        const   char*                                   const   pathStrPtr,
                tommRoC_file_x_info*                    const   infoPtr);

/**
 * Removes a file or directory.
 * NOTE: if removing a directory, the directory must be empty.
 *
 * param[in]        pathStrPtr              path/file name string pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedRemove(
        const   char*                                   const   pathStrPtr);

/**
 * Rename or move a file or directory.
 * NOTE: if the destination exists, it must match the source in type.
 * NOTE: if the destination is a directory, the directory must be empty.
 *
 * param[in]        oldPathStrPtr           old path/file name string pointer.
 * param[in]        newPathStrPtr           new path/file name string pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedRename(
        const   char*                                   const   oldPathStrPtr,
        const   char*                                   const   newPathStrPtr);

/**
 * Check if a file or directory exists.
 * NOTE: on low level function, the type of file or directory is not checked.
 *
 * param[in]        pathStrPtr              path/file name string pointer.
 * param[out]       existsPtr               output file/directory exists pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedExists(
        const   char*                                   const   pathStrPtr,
                bool*                                   const   existsPtr);


/******************* File operations functions */

/**
 * Check if a file exists.
 * NOTE: on low level function, it is checked that it MUST BE a file; not a directory.
 *
 * param[in]        pathStrPtr              path/file name string pointer.
 * param[out]       fileExistsPtr           output file exists pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedFileExists(
        const   char*                                   const   pathStrPtr,
                bool*                                   const   fileExistsPtr);

/**
 * Open a file.
 * NOTE: if opening in write/readWrite mode and file does not exist, a new one is always created.
 *
 * param[in]        filePathStrPtr          path/file name string pointer.
 * param[in]        openType                opening type.
 * param[out]       fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedFileOpen(
        const   char*                                   const   filePathStrPtr,
        const   tommRoC_file_x_file_open_type_enum_t            openType,
                tommRoC_file_x_file_t*                  const   fileHandlePtr);

/**
 * Close a file.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedFileClose(
                tommRoC_file_x_file_t*                  const   fileHandlePtr);

/**
 * Synchronize a file on storage.
 * NOTE: Any pending writes are written out to storage.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedFileSync(
                tommRoC_file_x_file_t*                  const   fileHandlePtr);

/**
 * Read data from a file.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_err_enum_t
 * NOTE: TOMMRO_C_ERR_SUCCESS in case of read success. Effective readed byte amount is returned in readedAmountPtr parameter (it can be different from requested "to read byte amount").
 */
tommRoC_err_enum_t tommRoCFileXMbedFileRead(
                tommRoC_file_x_file_t*                  const   fileHandlePtr,
                void*                                   const   readBufferPtr,
        const   uint32_t                                        toReadAmount,
                uint32_t*                               const   readedAmountPtr);

/**
 * Write data to a file.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[in]        writeBufferPtr          data buffer.
 * param[in]        writeBufferLen          data buffer length.
 * param[out]       writtenAmountPtr        written byte count pointer.
 *
 * return tommRoC_err_enum_t
 * NOTE: TOMMRO_C_ERR_SUCCESS in case of write success. Effective written byte amount is returned in writtenAmountPtr parameter (it can be different from requested "data buffer length").
 */
tommRoC_err_enum_t tommRoCFileXMbedFileWrite(
                tommRoC_file_x_file_t*                  const   fileHandlePtr,
        const   void*                                   const   writeBufferPtr,
        const   uint32_t                                        writeBufferLen,
                uint32_t*                               const   writtenAmountPtr);

/**
 * Read data from a file.
 * NOTE: reduced parameters (RP) version.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedFileReadRP(
                tommRoC_file_x_file_t*                  const   fileHandlePtr,
                void*                                   const   readBufferPtr,
        const   uint32_t                                        toReadAmount);

/**
 * Write data to a file.
 * NOTE: reduced parameters (RP) version.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[in]        writeBufferPtr          data buffer.
 * param[in]        writeBufferLen          data buffer length.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedFileWriteRP(
                tommRoC_file_x_file_t*                  const   fileHandlePtr,
        const   void*                                   const   writeBufferPtr,
        const   uint32_t                                        writeBufferLen);

/**
 * Sets the file position to the given offset.
 * NOTE: the argument offset signifies the number of bytes to seek from the given whence position.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[in]        offset                  number of bytes to seek.
 * param[in]        whence                  whence position.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedFileSeek(
                tommRoC_file_x_file_t*                  const   fileHandlePtr,
        const   int32_t                                         offset,
        const   tommRoC_file_x_seek_whence_enum_t               whence);

/**
 * Sets the file position to the beginning of the file.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedFileRewind(
                tommRoC_file_x_file_t*                  const   fileHandlePtr);

/**
 * Sets the file position to the end of the file.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedFileMoveToEnd(
                tommRoC_file_x_file_t*                  const   fileHandlePtr);

/**
 * Truncates the size of the file to the specified param size.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[in]        size                    file size to be truncated.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedFileTruncate(
                tommRoC_file_x_file_t*                  const   fileHandlePtr,
        const   uint32_t                                        size);

/**
 * Get the size of the file.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return uint32_t
 */
uint32_t tommRoCFileXMbedFileSize(
                tommRoC_file_x_file_t*                  const   fileHandlePtr);


/******************* Directory operations functions */

/**
 * Check if a directory exists.
 * NOTE: on low level function, it is checked that it MUST BE a directory; not a file.
 *
 * param[in]        pathStrPtr              path/file name string pointer.
 * param[out]       dirExistsPtr            output directory exists pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedDirExists(
        const   char*                                   const   pathStrPtr,
                bool*                                   const   dirExistsPtr);

/**
 * Create a directory.
 *
 * param[in]        pathStrPtr              path string pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXMbedDirMkDir(
        const   char*                                   const   pathStrPtr);

///**
// * Open a directory.
// * NOTE: once open, a directory can be used with read to iterate over files.
// *
// * param[in]        dirPathStrPtr           path/directory name string pointer.
// * param[out]       dirHandlePtr            directory handle pointer.
// *
// * return tommRoC_err_enum_t
// */
//tommRoC_err_enum_t tommRoCFileXMbedDirOpen(
//        const   char*                               const   dirPathStrPtr,
//                tommRoC_fs_dir_t*                   const   dirHandlePtr);
//
///**
// * Close a directory.
// * NOTE: releases any allocated resources.
// *
// * param[in/out]    dirHandlePtr            directory handle pointer.
// *
// * return tommRoC_err_enum_t
// */
//tommRoC_err_enum_t tommRoCFileXMbedDirClose(
//                tommRoC_fs_dir_t*                   const   dirHandlePtr);
//
///**
// * Read an entry in the directory.
// * NOTE: Fills out the info structure, based on the specified file or directory.
// *
// * param[in/out]    dirHandlePtr            directory handle pointer.
// * param[out]       infoPtr                 file or directory info structure pointer.
// * param[out]       availabilityPtr         element availability pointer.
// *
// * return tommRoC_err_enum_t
// */
//tommRoC_err_enum_t tommRoCFileXMbedDirRead(
//                tommRoC_fs_dir_t*                   const   dirHandlePtr,
//                tommRoC_fs_info*                    const   infoPtr,
//                tommRoC_fs_availability_enum_t*     const   availabilityPtr);
//
///**
// * Change the position of the directory to the beginning of the directory.
// *
// * param[in/out]    dirHandlePtr            directory handle pointer.
// *
// * return tommRoC_err_enum_t
// */
//tommRoC_err_enum_t tommRoCFileXMbedDirRewind(
//                tommRoC_fs_dir_t*                   const   dirHandlePtr);

/**
 * @}
 */

#endif
