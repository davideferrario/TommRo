
#ifndef TOMMROC_HW_TEMPLATE_FILEX_FS_H_
#define TOMMROC_HW_TEMPLATE_FILEX_FS_H_

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

/**
 *  - __TOMMROC_HW_USE_FILEX_FS_TEMPLATE__          to use FileX FS template
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"
#include "TOMMROCHw.h"

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)
#if !defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE_RAW_DISK_SIZE_BYTE__)
#error "__TOMMROC_HW_USE_FILEX_FS_TEMPLATE_RAW_DISK_SIZE_BYTE__ MUST be defined with raw disk size"
#endif
#include "fx_api.h"
#endif

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// Open method flags (argument of file open function).
#define TOMMROC_HW_TEMPLATE_FILEX_FS_OPEN_FOR_READ          (0)
#define TOMMROC_HW_TEMPLATE_FILEX_FS_OPEN_FOR_WRITE         (1)
#define TOMMROC_HW_TEMPLATE_FILEX_FS_OPEN_FOR_READ_FAST     (2)

// Relative seek from argument.
#define TOMMROC_HW_TEMPLATE_FILEX_FS_SEEK_BEGIN             (0) // Seeking from the begin of the file.
#define TOMMROC_HW_TEMPLATE_FILEX_FS_SEEK_END               (1) // Seeking from the end of the file.
#define TOMMROC_HW_TEMPLATE_FILEX_FS_SEEK_FORWARD           (2) // Seeking forward from the current position of the file.
#define TOMMROC_HW_TEMPLATE_FILEX_FS_SEEK_BACK              (3) // Seeking backward from the current position of the file.


#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#define TOMMROC_HW_TEMPLATE_FILEX_FS_FILE_HANDLE_SIZE   (272)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#define TOMMROC_HW_TEMPLATE_FILEX_FS_FILE_HANDLE_SIZE   ()
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)
#define TOMMROC_HW_TEMPLATE_FILEX_FS_FILE_HANDLE_SIZE   ()
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#define TOMMROC_HW_TEMPLATE_FILEX_FS_FILE_HANDLE_SIZE   ()
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)
#define TOMMROC_HW_TEMPLATE_FILEX_FS_FILE_HANDLE_SIZE   ()
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#define TOMMROC_HW_TEMPLATE_FILEX_FS_FILE_HANDLE_SIZE   ()
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16)
#define TOMMROC_HW_TEMPLATE_FILEX_FS_FILE_HANDLE_SIZE   ()
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)
#define TOMMROC_HW_TEMPLATE_FILEX_FS_FILE_HANDLE_SIZE   ()
#endif
#endif

// NOTE: if FILEX_FS_TEMPLATE not defined, define faked size
#if !defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)
#define TOMMROC_HW_TEMPLATE_FILEX_FS_FILE_HANDLE_SIZE   (1)
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of FileXFS file system mount type.
typedef enum {

    // Mount file system keeping previously saved data.
    TOMMROC_HW_TEMPLATE_FILEX_FS_MOUNT_KEEP_DATA = 0,

    // Mount file system forcing device format.
    TOMMROC_HW_TEMPLATE_FILEX_FS_MOUNT_FORCE_FORMAT,

} tommRoC_hw_template_filex_fs_mount_type_enum_t;


// FileXFS file struct
typedef struct {
    uint8_t data[TOMMROC_HW_TEMPLATE_FILEX_FS_FILE_HANDLE_SIZE];
} tommRoC_hw_template_filex_fs_file_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Start FileXFS environment.
 * NOTE: logical drive is still not mounted; mount function MUST be called to mount disk before using it.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSStart(void);

/**
 * Stop FileXFS environment (unmount logical drive).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSStop(void);

/**
 * Set guard to FileXFS environment.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSSetGuard(const tommRoC_guard_t* const guardPtr);

/**
 * Mount FileXFS environment (mount logical drive).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSMount(const tommRoC_hw_template_filex_fs_mount_type_enum_t mountType);


/**
 * Get is busy (one operation is in execution) status of FileXFS environment.
 *
 * return bool
 */
bool tommRoCHwTemplateFileXFSGetIsBusy(void);


/**
 * Open or create a file.
 *
 * param[in]        pathStrPtr              file name string pointer.
 * param[in]        openType                access mode and file open mode flags. OR of TOMMROC_HW_TEMPLATE_FILEX_FS_OPEN define.
 * param[in]        createIfNotExist        create file if it does not exist flag.
 * param[out]       filePtr                 file struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFOpen(
        const   char*                                   const   pathStrPtr,
        const   uint32_t                                        openType,
        const   bool                                            createIfNotExist,
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr);

/**
 * Close file.
 *
 * param[in/out]    filePtr                 file struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFClose(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr);

/**
 * Read data from a a file.
 *
 * param[in/out]    filePtr                 file struct pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFRead(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr,
                void*                                   const   readBufferPtr,
        const   uint32_t                                        toReadAmount,
                uint32_t*                               const   readedAmountPtr);

/**
 * Write data to a a file.
 *
 * param[in/out]    filePtr                 file struct pointer.
 * param[in]        writeBufferPtr          data buffer pointer.
 * param[in]        writeBufferLen          data buffer length.
 * param[out]       writtenAmountPtr        written byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFWrite(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr,
        const   void*                                   const   writeBufferPtr,
        const   uint32_t                                        writeBufferLen,
                uint32_t*                               const   writtenAmountPtr);

/**
 * Read data from a a file.
 * NOTE: reduced parameters (RP) version.
 *
 * param[in/out]    filePtr                 file struct pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFReadRP(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr,
                void*                                   const   readBufferPtr,
        const   uint32_t                                        toReadAmount);

/**
 * Write data to a a file.
 * NOTE: reduced parameters (RP) version.
 *
 * param[in/out]    filePtr                 file struct pointer.
 * param[in]        writeBufferPtr          data buffer pointer.
 * param[in]        writeBufferLen          data buffer length.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFWriteRP(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr,
        const   void*                                   const   writeBufferPtr,
        const   uint32_t                                        writeBufferLen);

/**
 * Seek file pointer.
 *
 * param[in/out]    filePtr                 file struct pointer.
 * param[in]        offsetByte              file offset from top of file.
 * param[in]        whence                  seek whence position. OR of TOMMROC_HW_TEMPLATE_FILEX_FS_SEEK define
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFSeek(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr,
        const   uint32_t                                        offsetByte,
        const   uint32_t                                        whence);

/**
 * Delete file or directory.
 *
 * param[in]        pathStrPtr              file or directory path string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFDelete(
        const   char*                                   const   pathStrPtr);

/**
 * Rename/Move file or directory.
 *
 * param[in]        pathOldStrPtr           old file or directory path string pointer.
 * param[in]        pathNewStrPtr           new file or directory path string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFRename(
        const   char*                                   const   pathOldStrPtr,
        const   char*                                   const   pathNewStrPtr);

/**
 * Set the file to the specified size, if smaller than the current file size.
 * NOTE: any unused clusters are released back to the media
 *
 * param[in/out]    filePtr                 file struct pointer.
 * param[in]        sizeByte                size [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFTruncate(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr,
        const   uint32_t                                        sizeByte);

/**
 * Get file size.
 *
 * param[in/out]    filePtr                 file struct pointer.
 *
 * return uint32_t
 */
uint32_t tommRoCHwTemplateFileXFSFSize(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr);

/**
 * Check if file exists.
 *
 * param[in]        pathStrPtr              file path string pointer.
 * param[out]       fileExistsPtr           boolean file exists pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFExists(
        const   char*                                   const   pathStrPtr,
                bool*                                   const   fileExistsPtr);

/**
 * Create a FAT12/16/32 format volume.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFormat(void);

#endif
