
#ifndef TOMMROC_FS_MBED_H_
#define TOMMROC_FS_MBED_H_

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
 * @defgroup tommRoCFSMbed tommRoCFSMbed
 *
 * @brief  TommRoC library embedded file system module
 * @author TommRo Software Department
 *
 * This module is providing library embedded hardware abstracted file system functionality.
 * It can be used in case of application needs only one file system.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCFS.h"

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
 * Init Mbed file system framework.
 * Mbed file system framework is a layer build over tommRoCFS to be used when only one file system is needed by application.
 * The file system handler is hide to application by this layer.
 * NOTE: the file system framework start as disabled. Application must enable when ready.
 *
 * param[in]        fsHandlePtr             file system handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedInit(
                tommRoC_fs_file_system_t*           const   fsHandlePtr);

/**
 * Close Mbed file system framework.
 * The low layer file system is closed (un-mount) and the internal file system framework is resetted to initial value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedClose(void);

/**
 * Enable Mbed file system framework.
 * NOTE: the file system framework start ad disabled. Application must enable when ready.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedEnable(void);

/**
 * Get Mbed file system framework enabling status.
 *
 * return bool
 */
bool tommRoCFSMbedIsEnabled(void);

/**
 * Get last Mbed file system framework operation result.
 *
 * return tommRoC_fs_error_enum_t
 */
tommRoC_fs_error_enum_t tommRoCFSMbedGetLastOpResult(void);

/**
 * Get is busy (one operation is in execution) status of Mbed file system framework.
 *
 * return bool
 */
bool tommRoCFSMbedGetIsBusy(void);


/******************* Disk functions */

/**
 * Format the Mbed file system disk.
 * NOTE: format is the only operation available also if FS is not enabled.
 * NOTE: the format is executed only when there are no opened files/directories.
 *
 * param[in]        timeoutMsec             wait for no opened files/directories timeout [msec]. TOMMROC_FS_DISK_FORMAT_WAIT_FOREVER_TIMEOUT for wait forever.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedDiskFormat(
        const   uint32_t                                    timeoutMsec);

/**
 * Get size of the Mbed file system disk [byte].
 *
 * param[out]       totalSizePtr            size of the disk [byte] pointer.
 * param[out]       usedSizePtr             current used size [byte] in the disk.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedDiskGetSize(
                uint32_t*                           const   totalSizePtr,
                uint32_t*                           const   usedSizePtr);


/******************* File system functions */

/**
 * Get info about a file or directory.
 *
 * param[in]        pathStrPtr              path/file name string pointer.
 * param[out]       infoPtr                 file or directory info structure pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedStat(
        const   char*                               const   pathStrPtr,
                tommRoC_fs_info*                    const   infoPtr);

/**
 * Removes a file or directory.
 * NOTE: if removing a directory, the directory must be empty.
 *
 * param[in]        pathStrPtr              path/file name string pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedRemove(
        const   char*                               const   pathStrPtr);

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
tommRoC_err_enum_t tommRoCFSMbedRename(
        const   char*                               const   oldPathStrPtr,
        const   char*                               const   newPathStrPtr);

/**
 * Check if a file or directory exists.
 * NOTE: on low level function, the type of file or directory is not checked.
 *
 * param[in]        pathStrPtr              path/file name string pointer.
 * param[out]       existsPtr               output file/directory exists pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedExists(
        const   char*                               const   pathStrPtr,
                bool*                               const   existsPtr);


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
tommRoC_err_enum_t tommRoCFSMbedFileExists(
        const   char*                               const   pathStrPtr,
                bool*                               const   fileExistsPtr);

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
tommRoC_err_enum_t tommRoCFSMbedFileOpen(
        const   char*                               const   filePathStrPtr,
        const   tommRoC_fs_file_open_type_enum_t            openType,
                tommRoC_fs_file_t*                  const   fileHandlePtr);

/**
 * Close a file.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedFileClose(
                tommRoC_fs_file_t*                  const   fileHandlePtr);

/**
 * Synchronize a file on storage.
 * NOTE: Any pending writes are written out to storage.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedFileSync(
                tommRoC_fs_file_t*                  const   fileHandlePtr);

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
tommRoC_err_enum_t tommRoCFSMbedFileRead(
                tommRoC_fs_file_t*                  const   fileHandlePtr,
                void*                               const   readBufferPtr,
        const   uint32_t                                    toReadAmount,
                uint32_t*                           const   readedAmountPtr);

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
tommRoC_err_enum_t tommRoCFSMbedFileWrite(
                tommRoC_fs_file_t*                  const   fileHandlePtr,
        const   void*                               const   writeBufferPtr,
        const   uint32_t                                    writeBufferLen,
                uint32_t*                           const   writtenAmountPtr);

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
tommRoC_err_enum_t tommRoCFSMbedFileReadRP(
                tommRoC_fs_file_t*                  const   fileHandlePtr,
                void*                               const   readBufferPtr,
        const   uint32_t                                    toReadAmount);

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
tommRoC_err_enum_t tommRoCFSMbedFileWriteRP(
                tommRoC_fs_file_t*                  const   fileHandlePtr,
        const   void*                               const   writeBufferPtr,
        const   uint32_t                                    writeBufferLen);

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
tommRoC_err_enum_t tommRoCFSMbedFileSeek(
                tommRoC_fs_file_t*                  const   fileHandlePtr,
        const   int32_t                                     offset,
        const   tommRoC_fs_seek_whence_enum_t               whence);

/**
 * Sets the file position to the beginning of the file.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedFileRewind(
                tommRoC_fs_file_t*                  const   fileHandlePtr);

/**
 * Sets the file position to the end of the file.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedFileMoveToEnd(
                tommRoC_fs_file_t*                  const   fileHandlePtr);

/**
 * Truncates the size of the file to the specified param size.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[in]        size                    file size to be truncated.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedFileTruncate(
                tommRoC_fs_file_t*                  const   fileHandlePtr,
        const   uint32_t                                    size);

/**
 * Get the size of the file.
 *
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return uint32_t
 */
uint32_t tommRoCFSMbedFileSize(
                tommRoC_fs_file_t*                  const   fileHandlePtr);


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
tommRoC_err_enum_t tommRoCFSMbedDirExists(
        const   char*                               const   pathStrPtr,
                bool*                               const   dirExistsPtr);

/**
 * Create a directory.
 *
 * param[in]        pathStrPtr              path string pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedDirMkDir(
        const   char*                               const   pathStrPtr);

/**
 * Open a directory.
 * NOTE: once open, a directory can be used with read to iterate over files.
 *
 * param[in]        dirPathStrPtr           path/directory name string pointer.
 * param[out]       dirHandlePtr            directory handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedDirOpen(
        const   char*                               const   dirPathStrPtr,
                tommRoC_fs_dir_t*                   const   dirHandlePtr);

/**
 * Close a directory.
 * NOTE: releases any allocated resources.
 *
 * param[in/out]    dirHandlePtr            directory handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedDirClose(
                tommRoC_fs_dir_t*                   const   dirHandlePtr);

/**
 * Read an entry in the directory.
 * NOTE: Fills out the info structure, based on the specified file or directory.
 *
 * param[in/out]    dirHandlePtr            directory handle pointer.
 * param[out]       infoPtr                 file or directory info structure pointer.
 * param[out]       availabilityPtr         element availability pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedDirRead(
                tommRoC_fs_dir_t*                   const   dirHandlePtr,
                tommRoC_fs_info*                    const   infoPtr,
                tommRoC_fs_availability_enum_t*     const   availabilityPtr);

/**
 * Change the position of the directory to the beginning of the directory.
 *
 * param[in/out]    dirHandlePtr            directory handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSMbedDirRewind(
                tommRoC_fs_dir_t*                   const   dirHandlePtr);

/**
 * @}
 */

#endif
