
#ifndef TOMMROC_FS_ITF_DEF_H_
#define TOMMROC_FS_ITF_DEF_H_

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
 * @defgroup tommRoCFSItfDEF tommRoCFSItfDEF
 *
 * @brief  TommRoC library file system interface definition module.
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted file system interface definition functionality.
 * This module is used for all the functionalities that are in need of a file system interface.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/
#define TOMMROC_FS_ITF_DEF_OPEN_FLAG_READONLY       (0x00000001)
#define TOMMROC_FS_ITF_DEF_OPEN_FLAG_READWRITE      (0x00000002)
#define TOMMROC_FS_ITF_DEF_OPEN_FLAG_CREATE         (0x00000004)
#define TOMMROC_FS_ITF_DEF_OPEN_FLAG_WRITEONLY      (0x00000008)
#define TOMMROC_FS_ITF_DEF_OPEN_FLAG_APPEND         (0x00000010)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC file system interface seek file type.
typedef enum {

    // Seek file from start of file.
    // NOTE: offset have to be positive or zero.
    TOMMROC_FS_ITF_DEF_SEEK_FILE_SET = 0,

    // Seek file from current position of file.
    TOMMROC_FS_ITF_DEF_SEEK_FILE_CUR,

    // Seek file from end of file.
    // NOTE: offset have to be negative or zero.
    TOMMROC_FS_ITF_DEF_SEEK_FILE_END,

} tommRoC_fs_itf_def_seek_whence_enum_t;


// tommRoC file system interface file stat struct.
typedef struct {

    uint32_t fileSize;

} tommRoC_fs_itf_def_file_system_file_stat_t;

#define __EMPTY_tommRoC_fs_itf_def_file_system_file_stat_t__    \
{                                                               \
    /* .fileSize */ 0,                                          \
}

// tommRoC file system interface disk stat struct.
typedef struct {

    uint32_t totalSize;
    uint32_t usedSize;

} tommRoC_fs_itf_def_file_system_disk_stat_t;

#define __EMPTY_tommRoC_fs_itf_def_file_system_disk_stat_t__    \
{                                                               \
    /* .totalSize */    0,                                      \
    /* .usedSize */     0,                                      \
}


/**
 * tommRoC file system interface open file function type.
 *
 * param[in/out]    fileSystemHandlePtr     opaque file system handle pointer (NULL if not used).
 * param[in]        filePathStrPtr          path/file name string pointer.
 * param[in]        flags                   opening flags (OR of TOMMROC_FS_ITF_DEF_OPEN_FLAG_x bits).
 * param[out]       fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
typedef tommRoC_err_enum_t (*tommRoC_fs_itf_def_open_file_funct_t)(
                void*                                       const   fileSystemHandlePtr,
        const   char*                                       const   filePathStrPtr,
        const   uint32_t                                            flags,
                void*                                       const   fileHandlePtr);

/**
 * tommRoC file system interface close file function type.
 *
 * param[in/out]    fileSystemHandlePtr     opaque file system handle pointer (NULL if not used).
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
typedef tommRoC_err_enum_t (*tommRoC_fs_itf_def_close_file_funct_t)(
                void*                                       const   fileSystemHandlePtr,
                void*                                       const   fileHandlePtr);

/**
 * tommRoC file system interface sync file function type.
 *
 * param[in/out]    fileSystemHandlePtr     opaque file system handle pointer (NULL if not used).
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
typedef tommRoC_err_enum_t (*tommRoC_fs_itf_def_sync_file_funct_t)(
                void*                                       const   fileSystemHandlePtr,
                void*                                       const   fileHandlePtr);

/**
 * tommRoC file system interface truncate file function type.
 *
 * param[in/out]    fileSystemHandlePtr     opaque file system handle pointer (NULL if not used).
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[in]        size                    file size to be truncated.
 *
 * return tommRoC_err_enum_t
 */
typedef tommRoC_err_enum_t (*tommRoC_fs_itf_def_truncate_file_funct_t)(
                void*                                       const   fileSystemHandlePtr,
                void*                                       const   fileHandlePtr,
        const   uint32_t                                            size);

/**
 * tommRoC file system interface seek file function type.
 *
 * param[in/out]    fileSystemHandlePtr     opaque file system handle pointer (NULL if not used).
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[in]        offset                  number of bytes to seek.
 * param[in]        whence                  whence position.
 *
 * return tommRoC_err_enum_t
 */
typedef tommRoC_err_enum_t (*tommRoC_fs_itf_def_seek_file_funct_t)(
                void*                                       const   fileSystemHandlePtr,
                void*                                       const   fileHandlePtr,
        const   int32_t                                             offset,
        const   tommRoC_fs_itf_def_seek_whence_enum_t               whence);

/**
 * tommRoC file system interface read file function type.
 *
 * param[in/out]    fileSystemHandlePtr     opaque file system handle pointer (NULL if not used).
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_err_enum_t
 */
typedef tommRoC_err_enum_t (*tommRoC_fs_itf_def_read_file_funct_t)(
                void*                                       const   fileSystemHandlePtr,
                void*                                       const   fileHandlePtr,
                void*                                       const   readBufferPtr,
        const   uint32_t                                            toReadAmount,
                uint32_t*                                   const   readedAmountPtr);

/**
 * tommRoC file system interface write file function type.
 *
 * param[in/out]    fileSystemHandlePtr     opaque file system handle pointer (NULL if not used).
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[in]        writeBufferPtr          data buffer.
 * param[in]        writeBufferLen          data buffer length.
 * param[out]       writtenAmountPtr        written byte count pointer.
 *
 * return tommRoC_err_enum_t
 */
typedef tommRoC_err_enum_t (*tommRoC_fs_itf_def_write_file_funct_t)(
                void*                                       const   fileSystemHandlePtr,
                void*                                       const   fileHandlePtr,
        const   void*                                       const   writeBufferPtr,
        const   uint32_t                                            writeBufferLen,
                uint32_t*                                   const   writtenAmountPtr);

/**
 * tommRoC file system interface delete file function type.
 *
 * param[in/out]    fileSystemHandlePtr     opaque file system handle pointer (NULL if not used).
 * param[in]        filePathStrPtr          path/file name string pointer.
 *
 * return tommRoC_err_enum_t
 */
typedef tommRoC_err_enum_t (*tommRoC_fs_itf_def_delete_file_funct_t)(
                void*                                       const   fileSystemHandlePtr,
        const   char*                                       const   filePathStrPtr);

/**
 * tommRoC file system interface file exists function type.
 *
 * param[in/out]    fileSystemHandlePtr     opaque file system handle pointer (NULL if not used).
 * param[in]        filePathStrPtr          path/file name string pointer.
 * param[out]       fileExistsPtr           output file exists pointer.
 *
 * return tommRoC_err_enum_t
 */
typedef tommRoC_err_enum_t (*tommRoC_fs_itf_def_file_exists_funct_t)(
                void*                                       const   fileSystemHandlePtr,
        const   char*                                       const   filePathStrPtr,
                bool*                                       const   fileExistsPtr);

/**
 * tommRoC file system interface file size function type.
 *
 * param[in/out]    fileSystemHandlePtr     opaque file system handle pointer (NULL if not used).
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return uint32_t
 */
typedef uint32_t (*tommRoC_fs_itf_def_file_size_funct_t)(
                void*                                       const   fileSystemHandlePtr,
                void*                                       const   fileHandlePtr);

/**
 * tommRoC file system interface file stat function type.
 *
 * param[in/out]    fileSystemHandlePtr     opaque file system handle pointer (NULL if not used).
 * param[in]        filePathStrPtr          path/file name string pointer.
 * param[out]       fileStatPtr             file stat pointer.
 *
 * return tommRoC_err_enum_t
 */
typedef tommRoC_err_enum_t (*tommRoC_fs_itf_def_file_stat_funct_t)(
                void*                                       const   fileSystemHandlePtr,
        const   char*                                       const   filePathStrPtr,
                tommRoC_fs_itf_def_file_system_file_stat_t* const   fileStatPtr);

/**
 * tommRoC file system interface disk stat function type.
 *
 * param[in/out]    fileSystemHandlePtr     opaque file system handle pointer (NULL if not used).
 * param[out]       fileStatPtr             disk stat pointer.
 *
 * return tommRoC_err_enum_t
 */
typedef tommRoC_err_enum_t (*tommRoC_fs_itf_def_disk_stat_funct_t)(
                void*                                       const   fileSystemHandlePtr,
                tommRoC_fs_itf_def_file_system_disk_stat_t* const   diskStatPtr);


// tommRoC file system interface file system config struct.
typedef struct {

    void*                                       fileSystemHandlePtr;    // Opaque file system handle pointer (NULL if not used).
    tommRoC_fs_itf_def_open_file_funct_t        openFile;
    tommRoC_fs_itf_def_close_file_funct_t       closeFile;
    tommRoC_fs_itf_def_sync_file_funct_t        syncFile;
    tommRoC_fs_itf_def_truncate_file_funct_t    truncateFile;
    tommRoC_fs_itf_def_seek_file_funct_t        seekFile;
    tommRoC_fs_itf_def_read_file_funct_t        readFile;
    tommRoC_fs_itf_def_write_file_funct_t       writeFile;
    tommRoC_fs_itf_def_delete_file_funct_t      deleteFile;
    tommRoC_fs_itf_def_file_exists_funct_t      fileExists;
    tommRoC_fs_itf_def_file_size_funct_t        fileSize;
    tommRoC_fs_itf_def_file_stat_funct_t        fileStat;
    tommRoC_fs_itf_def_disk_stat_funct_t        diskStat;

} tommRoC_fs_itf_def_file_system_config_t;

#define __EMPTY_tommRoC_fs_itf_def_file_system_config_t__   \
{                                                           \
    /* .fileSystemHandlePtr */  NULL,                       \
    /* .openFile */             NULL,                       \
    /* .closeFile */            NULL,                       \
    /* .syncFile */             NULL,                       \
    /* .truncateFile */         NULL,                       \
    /* .seekFile */             NULL,                       \
    /* .readFile */             NULL,                       \
    /* .writeFile */            NULL,                       \
    /* .deleteFile */           NULL,                       \
    /* .fileExists */           NULL,                       \
    /* .fileSize */             NULL,                       \
    /* .fileStat */             NULL,                       \
    /* .diskStat */             NULL,                       \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * @}
 */

#endif
