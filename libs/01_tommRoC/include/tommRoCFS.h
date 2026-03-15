
#ifndef TOMMROC_FS_H_
#define TOMMROC_FS_H_

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
 * @defgroup tommRoCFS tommRoCFS
 *
 * @brief  TommRoC library file system module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted file system functionality.
 * Please note that it is based on littleFS (https://github.com/littlefs-project/littlefs) library.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCEnv.h"
#include "tommRoCGuard.h"
#include "tommRoCMath.h"
#include "tommRoCString.h"
#include "tommRoCUtil.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// Maximum file name size [bytes].
#define TOMMROC_FS_FILENAME_MAX_SIZE_BYTE       (TOMMROC_STRING_U32_DEC_AS_STRING_MAX_LENGTH_BYTE + TOMMROC_UTIL_STRING_ARR_LENGTH(".dat") + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)
#define TOMMROC_FS_FILENAME_MAX_LENGTH_BYTE     (TOMMROC_STRING_U32_DEC_AS_STRING_MAX_LENGTH_BYTE + TOMMROC_UTIL_STRING_ARR_LENGTH(".dat"))

// Max file size [bytes].
#define TOMMROC_FS_FILE_MAX_SIZE_BYTE           (INT32_MAX)

// Directories separator char.
// NOTE: to open files into directory, the file path need to be specified using "dirName1/dirName2/fileName"
#define TOMMROC_FS_DIR_SEPARATOR_CHAR           (TOMMROC_STRING_SLASH_CHAR)
#define TOMMROC_FS_DIR_SEPARATOR_CHAR_SIZE      (TOMMROC_STRING_SLASH_CHAR_SIZE)
#define TOMMROC_FS_DIR_SEPARATOR_STR            (TOMMROC_STRING_SLASH_STR)
#define TOMMROC_FS_DIR_SEPARATOR_STR_SIZE       (TOMMROC_STRING_SLASH_STR_SIZE)
#define TOMMROC_FS_DIR_SEPARATOR_STR_LENGTH     (TOMMROC_STRING_SLASH_STR_LENGTH)

// Library internal file system/file struct size (architecture common).
#define TOMMROC_FS_GUARD_PTR_SIZE               (TOMMROC_UTIL_PTR_SIZE)
#define TOMMROC_FS_READ_BUFFER_SIZE             (256)
#define TOMMROC_FS_PROG_BUFFER_SIZE             (256)
#define TOMMROC_FS_LOOKAHEAD_BUFFER_SIZE        (256)
#define TOMMROC_FS_LAST_OP_RES_SIZE             (TOMMROC_UTIL_I8_SIZE)
#define TOMMROC_FS_IS_BUSY_SIZE                 (TOMMROC_UTIL_BOOL_SIZE)
#define TOMMROC_FS_OPENE_FILE_DIR_COUNTER_SIZE  (TOMMROC_UTIL_U8_SIZE)

#define TOMMROC_FS_LFS_CONFIG_BUFFER_SIZE       (256)

// Library internal file system/file struct size (architecture dependent).
#if defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_8_BIT_SIZE)
#define TOMMROC_FS_STRUCT_LFS_CONFIG_SIZE       ()
#define TOMMROC_FS_LFS_T_SIZE                   ()

#define TOMMROC_FS_LFS_FILE_T_SIZE              ()
#define TOMMROC_FS_STRUCT_LFS_FILE_CONFIG_SIZE  ()

#define TOMMROC_FS_LFS_DIR_T_SIZE               ()

#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMROC_FS_STRUCT_LFS_CONFIG_SIZE       (60)
#define TOMMROC_FS_LFS_T_SIZE                   (110)

#define TOMMROC_FS_LFS_FILE_T_SIZE              (77)
#define TOMMROC_FS_STRUCT_LFS_FILE_CONFIG_SIZE  (8)

#define TOMMROC_FS_LFS_DIR_T_SIZE               ()

#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE)
#define TOMMROC_FS_STRUCT_LFS_CONFIG_SIZE       (84)
#define TOMMROC_FS_LFS_T_SIZE                   (128)

#define TOMMROC_FS_LFS_FILE_T_SIZE              (84)
#define TOMMROC_FS_STRUCT_LFS_FILE_CONFIG_SIZE  (12)

#define TOMMROC_FS_LFS_DIR_T_SIZE               (52)

#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMROC_FS_STRUCT_LFS_CONFIG_SIZE       (120)
#define TOMMROC_FS_LFS_T_SIZE                   (160)

#define TOMMROC_FS_LFS_FILE_T_SIZE              (104)
#define TOMMROC_FS_STRUCT_LFS_FILE_CONFIG_SIZE  (24)

#define TOMMROC_FS_LFS_DIR_T_SIZE               (56)
#endif


// File system struct size.
#if !defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#define TOMMROC_FS_FILE_SYSTEM_HANDLE_SIZE      (   (TOMMROC_MATH_INT_BY_EXCESS_APPROX(TOMMROC_FS_STRUCT_LFS_CONFIG_SIZE, TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE))                                                              +   \
                                                    (TOMMROC_MATH_INT_BY_EXCESS_APPROX(TOMMROC_FS_LFS_T_SIZE, TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE))                                                                          +   \
                                                    (TOMMROC_MATH_INT_BY_EXCESS_APPROX(TOMMROC_FS_GUARD_PTR_SIZE, TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE))                                                                      +   \
                                                    (TOMMROC_MATH_INT_BY_EXCESS_APPROX(TOMMROC_FS_READ_BUFFER_SIZE, TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE))                                                                    +   \
                                                    (TOMMROC_MATH_INT_BY_EXCESS_APPROX(TOMMROC_FS_PROG_BUFFER_SIZE, TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE))                                                                    +   \
                                                    (TOMMROC_MATH_INT_BY_EXCESS_APPROX(TOMMROC_FS_LOOKAHEAD_BUFFER_SIZE, TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE))                                                               +   \
                                                    (TOMMROC_MATH_INT_BY_EXCESS_APPROX(TOMMROC_FS_LAST_OP_RES_SIZE + TOMMROC_FS_IS_BUSY_SIZE + TOMMROC_FS_OPENE_FILE_DIR_COUNTER_SIZE, TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE))     )
#else
#define TOMMROC_FS_FILE_SYSTEM_HANDLE_SIZE      (   TOMMROC_FS_STRUCT_LFS_CONFIG_SIZE                                                               +   \
                                                    TOMMROC_FS_LFS_T_SIZE                                                                           +   \
                                                    TOMMROC_FS_GUARD_PTR_SIZE                                                                       +   \
                                                    TOMMROC_FS_READ_BUFFER_SIZE                                                                     +   \
                                                    TOMMROC_FS_PROG_BUFFER_SIZE                                                                     +   \
                                                    TOMMROC_FS_LOOKAHEAD_BUFFER_SIZE                                                                +   \
                                                    TOMMROC_FS_LAST_OP_RES_SIZE + TOMMROC_FS_IS_BUSY_SIZE + TOMMROC_FS_OPENE_FILE_DIR_COUNTER_SIZE      )
#endif

// File struct size.
#if !defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#define TOMMROC_FS_FILE_HANDLE_SIZE             (   (TOMMROC_MATH_INT_BY_EXCESS_APPROX(TOMMROC_FS_LFS_FILE_T_SIZE, TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE))             +   \
                                                    (TOMMROC_MATH_INT_BY_EXCESS_APPROX(TOMMROC_FS_STRUCT_LFS_FILE_CONFIG_SIZE, TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE)) +   \
                                                    (TOMMROC_MATH_INT_BY_EXCESS_APPROX(TOMMROC_FS_LFS_CONFIG_BUFFER_SIZE, TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE))          )
#else
#define TOMMROC_FS_FILE_HANDLE_SIZE             (   TOMMROC_FS_LFS_FILE_T_SIZE              +   \
                                                    TOMMROC_FS_STRUCT_LFS_FILE_CONFIG_SIZE  +   \
                                                    TOMMROC_FS_LFS_CONFIG_BUFFER_SIZE           )
#endif

// Directory struct size.
#if !defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#define TOMMROC_FS_DIR_HANDLE_SIZE              (TOMMROC_MATH_INT_BY_EXCESS_APPROX(TOMMROC_FS_LFS_DIR_T_SIZE, TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE))
#else
#define TOMMROC_FS_DIR_HANDLE_SIZE              (TOMMROC_FS_LFS_DIR_T_SIZE)
#endif


// Wait forever timeout for disk format
#define TOMMROC_FS_DISK_FORMAT_WAIT_FOREVER_TIMEOUT (UINT32_MIN)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC file system init type.
typedef enum {

    // Init file system keeping previously saved data.
    TOMMROC_FS_INIT_KEEP_DATA = 0,

    // Init file system forcing device format.
    TOMMROC_FS_INIT_FORCE_FORMAT,

} tommRoC_fs_init_type_enum_t;


// Enumeration of tommRoC file system opening file type.
typedef enum {

    // Open a file as read only.
    TOMMROC_FS_OPEN_FILE_FOR_READ = 0,

    // Open a file as write only AND create if it does not exist.
    TOMMROC_FS_OPEN_FILE_FOR_WRITE,

    // Open a file as read and write AND create if it does not exist.
    TOMMROC_FS_OPEN_FILE_FOR_READ_WRITE,

    // Open a file as read and write AND create if it does not exist AND move to end of file on every write.
    // NOTE: the file offset is set to the end of the file prior to each write.
    TOMMROC_FS_OPEN_FILE_FOR_APPEND,

} tommRoC_fs_file_open_type_enum_t;


// Enumeration of tommRoC file system seek file type.
typedef enum {

    /**
     * Seek file from start of file.
     * NOTE: offset have to be positive or zero.
     */
    TOMMROC_FS_SEEK_FILE_SET = 0,

    /**
     * Seek file from current position of file.
     * NOTE: offset can be negative, positive or zero.
     */
    TOMMROC_FS_SEEK_FILE_CUR,

    /**
     * Seek file from end of file.
     * NOTE: offset have to be negative or zero.
     */
    TOMMROC_FS_SEEK_FILE_END,

} tommRoC_fs_seek_whence_enum_t;


// Enumeration of tommRoC file system type (file or directory).
typedef enum {

    // Element is a file.
    TOMMROC_FS_TYPE_FILE = 0,

    // Element is a directory
    TOMMROC_FS_TYPE_DIR,

} tommRoC_fs_type_enum_t;


// Enumeration of tommRoC file system directory element availability.
typedef enum {

    // A valid element is available in directory and it is returned by function.
    TOMMROC_FS_AVAILABILITY_ELEMENT = 0,

    // No more element is available in directory.
    TOMMROC_FS_AVAILABILITY_NO_ELEMENT,

} tommRoC_fs_availability_enum_t;


// tommRoC file system first parameter of block device callback functions struct.
typedef struct {

    // Opaque user provided context that can be used to pass information to the block device callback functions.
    void*       contextPtr;

    // Unused data
    void (*unusedData1)(void);
    void (*unusedData2)(void);
    void (*unusedData3)(void);
    void (*unusedData4)(void);
    uint32_t    unusedData5[2];

    // Size of an erasable block.
    uint32_t    erasableBlockSize;
    // Number of erasable blocks on the device.
    uint32_t    erasableBlockCount;

    // Unused data
    int32_t     unusedData6;
    uint32_t    unusedData7[3];
    void*       unusedData8[3];
    uint32_t    unusedData9[5];

} tommRoC_fs_param_cb_t;


// Possible error codes for block callback function.
typedef enum {

    TOMMROC_FS_ERR_OK           = 0,    // No error
    TOMMROC_FS_ERR_IO           = -5,   // Error during device operation
    TOMMROC_FS_ERR_CORRUPT      = -84,  // Corrupted
    TOMMROC_FS_ERR_NOENT        = -2,   // No directory entry
    TOMMROC_FS_ERR_EXIST        = -17,  // Entry already exists
    TOMMROC_FS_ERR_NOTDIR       = -20,  // Entry is not a dir
    TOMMROC_FS_ERR_ISDIR        = -21,  // Entry is a dir
    TOMMROC_FS_ERR_NOTEMPTY     = -39,  // Dir is not empty
    TOMMROC_FS_ERR_BADF         = -9,   // Bad file number
    TOMMROC_FS_ERR_FBIG         = -27,  // File too large
    TOMMROC_FS_ERR_INVAL        = -22,  // Invalid parameter
    TOMMROC_FS_ERR_NOSPC        = -28,  // No space left on device
    TOMMROC_FS_ERR_NOMEM        = -12,  // No more memory available
    TOMMROC_FS_ERR_NOATTR       = -61,  // No data/attr available
    TOMMROC_FS_ERR_NAMETOOLONG  = -36,  // File name too long

} tommRoC_fs_error_enum_t;


// Read a data region in a block callback function type definition.
// NOTE: Have to return TOMMROC_FS_ERR_OK value if success; negative results are error codes.
// NOTE: May return TOMMROC_FS_ERR_CORRUPT if the block should be considered bad.
typedef int (*tommRoC_fs_read_funct_t)(
                tommRoC_fs_param_cb_t*  const   paramPtr,
        const   uint32_t                        blockIdx,
        const   uint32_t                        blockOffset,
                void*                   const   readBufferPtr,
        const   uint32_t                        toReadAmount);

// Write a data region in a block callback function type definition.
// NOTE: Have to return TOMMROC_FS_ERR_OK value if success; negative results are error codes.
// NOTE: May return TOMMROC_FS_ERR_CORRUPT if the block should be considered bad.
typedef int (*tommRoC_fs_write_funct_t)(
                tommRoC_fs_param_cb_t*  const   paramPtr,
        const   uint32_t                        blockIdx,
        const   uint32_t                        blockOffset,
        const   void*                   const   writeBufferPtr,
        const   uint32_t                        writeBufferLen);

// Erase a block callback function type definition.
// NOTE: Have to return TOMMROC_FS_ERR_OK value if success; negative results are error codes.
// NOTE: May return TOMMROC_FS_ERR_CORRUPT if the block should be considered bad.
typedef int (*tommRoC_fs_erase_funct_t)(
                tommRoC_fs_param_cb_t*  const   paramPtr,
        const   uint32_t                        blockIdx);


// tommRoC file system config struct.
typedef struct {

    // Opaque user provided context that can be used to pass information to the block device callback functions.
    void*                       contextPtr;

    // Read a data region in a block.
    tommRoC_fs_read_funct_t     readCb;

    // Write a data region in a block.
    tommRoC_fs_write_funct_t    writeCb;

    // Erase a block.
    tommRoC_fs_erase_funct_t    eraseCb;

    // Size of an erasable block on the device.
    // NOTE: this should be kept small as each file currently takes up an entire block.
    uint32_t                    erasableBlockSize;

    // Number of erasable blocks on the device.
    uint32_t                    erasableBlockCount;

} tommRoC_fs_file_system_config_t;

#define __EMPTY_tommRoC_fs_file_system_config_t__   \
{                                                   \
    /* .contextPtr */           NULL,               \
    /* .readCb */               NULL,               \
    /* .writeCb */              NULL,               \
    /* .eraseCb */              NULL,               \
    /* .erasableBlockSize */    0,                  \
    /* .erasableBlockCount */   0,                  \
}


// tommRoC file system file/directory info struct.
typedef struct {

    tommRoC_fs_type_enum_t  type;                                       // Type (file or directory)
    uint32_t                size;                                       // Size
    char                    name[TOMMROC_FS_FILENAME_MAX_SIZE_BYTE];    // Name

} tommRoC_fs_info;

#define __EMPTY_tommRoC_fs_info__                                                                   \
{                                                                                                   \
    /* .type */ TOMMROC_FS_TYPE_FILE,                                                               \
    /* .size */ 0,                                                                                  \
    /* .name */ TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_FS_FILENAME_MAX_SIZE_BYTE - 1, 0), \
}


// tommRoC file system file system struct.
typedef struct {
    uint8_t data[TOMMROC_FS_FILE_SYSTEM_HANDLE_SIZE];
} tommRoC_fs_file_system_t;

#define __EMPTY_tommRoC_fs_file_system_t_data_field__           TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_FS_FILE_SYSTEM_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_fs_file_system_t__                      \
{                                                               \
    /* .data */ __EMPTY_tommRoC_fs_file_system_t_data_field__,  \
}


// tommRoC file system file struct.
typedef struct {
    uint8_t data[TOMMROC_FS_FILE_HANDLE_SIZE];
} tommRoC_fs_file_t;

#define __EMPTY_tommRoC_fs_file_t_data_field__          TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_FS_FILE_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_fs_file_t__                     \
{                                                       \
    /* .data */ __EMPTY_tommRoC_fs_file_t_data_field__, \
}


// tommRoC file system directory struct.
typedef struct {
    uint8_t data[TOMMROC_FS_DIR_HANDLE_SIZE];
} tommRoC_fs_dir_t;

#define __EMPTY_tommRoC_fs_dir_t_data_field__           TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_FS_DIR_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_fs_dir_t__                      \
{                                                       \
    /* .data */ __EMPTY_tommRoC_fs_dir_t_data_field__,  \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* File system management functions */

/**
 * Init (mount) a file system.
 *
 * param[in]        fsInitType              file system init type.
 * param[in]        fsConfigPtr             file system configuration pointer.
 * param[in]        guardPtr                file system guard pointer (set to NULL to disable).
 * param[out]       fsHandlePtr             file system handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSInit(
        const   tommRoC_fs_init_type_enum_t                 fsInitType,
        const   tommRoC_fs_file_system_config_t*    const   fsConfigPtr,
        const   tommRoC_guard_t*                    const   guardPtr,
                tommRoC_fs_file_system_t*           const   fsHandlePtr);

/**
 * Close (un-mount) a file system.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSClose(
                tommRoC_fs_file_system_t*           const   fsHandlePtr);

/**
 * Get last file system operation result.
 *
 * param[in]        fsHandlePtr             file system handle pointer.
 *
 * return tommRoC_fs_error_enum_t
 */
tommRoC_fs_error_enum_t tommRoCFSGetLastOpResult(
        const   tommRoC_fs_file_system_t*           const   fsHandlePtr);

/**
 * Get is busy (one operation is in execution) status of file system.
 *
 * param[in]        fsHandlePtr             file system handle pointer.
 *
 * return bool
 */
bool tommRoCFSGetIsBusy(
        const   tommRoC_fs_file_system_t*           const   fsHandlePtr);


/******************* Disk functions */

/**
 * Format the disk (file system).
 * NOTE: the format is executed only when there are no opened files/directories.
 *
 * param[in]        fsHandlePtr             file system handle pointer.
 * param[in]        timeoutMsec             wait for no opened files/directories timeout [msec]. TOMMROC_FS_DISK_FORMAT_WAIT_FOREVER_TIMEOUT for wait forever.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSDiskFormat(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
        const   uint32_t                                    timeoutMsec);

/**
 * Get size of the disk [byte].
 *
 * param[in]        fsHandlePtr             file system handle pointer.
 * param[out]       totalSizeBytePtr        size of the disk [byte] pointer.
 * param[out]       usedSizeBytePtr         current used size [byte] in the disk.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSDiskGetSize(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
                uint32_t*                           const   totalSizeBytePtr,
                uint32_t*                           const   usedSizeBytePtr);


/******************* File system functions */

/**
 * Get info about a file or directory.
 *
 * param[in]        fsHandlePtr             file system handle pointer.
 * param[in]        pathStrPtr              path/file name string pointer.
 * param[out]       infoPtr                 file or directory info structure pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSStat(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
        const   char*                               const   pathStrPtr,
                tommRoC_fs_info*                    const   infoPtr);

/**
 * Removes a file or directory.
 * NOTE: if removing a directory, the directory must be empty.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in]        pathStrPtr              path/file name string pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSRemove(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
        const   char*                               const   pathStrPtr);

/**
 * Rename or move a file or directory.
 * NOTE: if the destination exists, it must match the source in type.
 * NOTE: if the destination is a directory, the directory must be empty.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in]        oldPathStrPtr           old path/file name string pointer.
 * param[in]        newPathStrPtr           new path/file name string pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSRename(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
        const   char*                               const   oldPathStrPtr,
        const   char*                               const   newPathStrPtr);

/**
 * Check if a file or directory exists.
 * NOTE: on low level function, the type of file or directory is not checked.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in]        pathStrPtr              path/file name string pointer.
 * param[out]       existsPtr               output file/directory exists pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSExists(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
        const   char*                               const   pathStrPtr,
                bool*                               const   existsPtr);


/******************* File operations functions */

/**
 * Check if a file exists.
 * NOTE: on low level function, it is checked that it MUST BE a file; not a directory.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in]        pathStrPtr              path/file name string pointer.
 * param[out]       fileExistsPtr           output file exists pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSFileExists(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
        const   char*                               const   pathStrPtr,
                bool*                               const   fileExistsPtr);

/**
 * Open a file.
 * NOTE: if opening in write/readWrite mode and file does not exist, a new one is always created.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in]        filePathStrPtr          path/file name string pointer.
 * param[in]        openType                opening type.
 * param[out]       fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSFileOpen(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
        const   char*                               const   filePathStrPtr,
        const   tommRoC_fs_file_open_type_enum_t            openType,
                tommRoC_fs_file_t*                  const   fileHandlePtr);

/**
 * Close a file.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSFileClose(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
                tommRoC_fs_file_t*                  const   fileHandlePtr);

/**
 * Synchronize a file on storage.
 * NOTE: Any pending writes are written out to storage.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSFileSync(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
                tommRoC_fs_file_t*                  const   fileHandlePtr);

/**
 * Read data from a file.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_err_enum_t
 * NOTE: TOMMRO_C_ERR_SUCCESS in case of read success. Effective readed byte amount is returned in readedAmountPtr parameter (it can be different from requested "to read byte amount").
 */
tommRoC_err_enum_t tommRoCFSFileRead(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
                tommRoC_fs_file_t*                  const   fileHandlePtr,
                void*                               const   readBufferPtr,
        const   uint32_t                                    toReadAmount,
                uint32_t*                           const   readedAmountPtr);

/**
 * Write data to a file.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[in]        writeBufferPtr          data buffer.
 * param[in]        writeBufferLen          data buffer length.
 * param[out]       writtenAmountPtr        written byte count pointer.
 *
 * return tommRoC_err_enum_t
 * NOTE: TOMMRO_C_ERR_SUCCESS in case of write success. Effective written byte amount is returned in writtenAmountPtr parameter (it can be different from requested "data buffer length").
 */
tommRoC_err_enum_t tommRoCFSFileWrite(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
                tommRoC_fs_file_t*                  const   fileHandlePtr,
        const   void*                               const   writeBufferPtr,
        const   uint32_t                                    writeBufferLen,
                uint32_t*                           const   writtenAmountPtr);

/**
 * Read data from a file.
 * NOTE: reduced parameters (RP) version.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSFileReadRP(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
                tommRoC_fs_file_t*                  const   fileHandlePtr,
                void*                               const   readBufferPtr,
        const   uint32_t                                    toReadAmount);

/**
 * Write data to a file.
 * NOTE: reduced parameters (RP) version.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[in]        writeBufferPtr          data buffer.
 * param[in]        writeBufferLen          data buffer length.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSFileWriteRP(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
                tommRoC_fs_file_t*                  const   fileHandlePtr,
        const   void*                               const   writeBufferPtr,
        const   uint32_t                                    writeBufferLen);

/**
 * Sets the file position to the given offset.
 * NOTE: the argument offset signifies the number of bytes to seek from the given whence position.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[in]        offset                  number of bytes to seek.
 * param[in]        whence                  whence position.
 *
 * NOTE:
 *  if whence = TOMMROC_FS_SEEK_FILE_SET    -> offset have to be positive or zero.
 *  if whence = TOMMROC_FS_SEEK_FILE_CUR    -> offset can be negative, positive or zero.
 *  if whence = TOMMROC_FS_SEEK_FILE_END    -> offset have to be negative or zero.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSFileSeek(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
                tommRoC_fs_file_t*                  const   fileHandlePtr,
        const   int32_t                                     offset,
        const   tommRoC_fs_seek_whence_enum_t               whence);

/**
 * Sets the file position to the beginning of the file.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSFileRewind(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
                tommRoC_fs_file_t*                  const   fileHandlePtr);

/**
 * Sets the file position to the end of the file.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSFileMoveToEnd(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
                tommRoC_fs_file_t*                  const   fileHandlePtr);

/**
 * Truncates the size of the file to the specified param size.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[in]        size                    file size to be truncated [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSFileTruncate(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
                tommRoC_fs_file_t*                  const   fileHandlePtr,
        const   uint32_t                                    size);

/**
 * Get the size of the file.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return uint32_t (UINT32_MAX in case of error)
 */
uint32_t tommRoCFSFileSize(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
                tommRoC_fs_file_t*                  const   fileHandlePtr);


/******************* Directory operations functions */

/**
 * Check if a directory exists.
 * NOTE: on low level function, it is checked that it MUST BE a directory; not a file.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in]        pathStrPtr              path/file name string pointer.
 * param[out]       dirExistsPtr            output directory exists pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSDirExists(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
        const   char*                               const   pathStrPtr,
                bool*                               const   dirExistsPtr);

/**
 * Create a directory.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in]        pathStrPtr              path string pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSDirMkDir(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
        const   char*                               const   pathStrPtr);

/**
 * Open a directory.
 * NOTE: once open, a directory can be used with read to iterate over files.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in]        dirPathStrPtr           path/directory name string pointer.
 * param[out]       dirHandlePtr            directory handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSDirOpen(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
        const   char*                               const   dirPathStrPtr,
                tommRoC_fs_dir_t*                   const   dirHandlePtr);

/**
 * Close a directory.
 * NOTE: releases any allocated resources.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in/out]    dirHandlePtr            directory handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSDirClose(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
                tommRoC_fs_dir_t*                   const   dirHandlePtr);

/**
 * Read an entry in the directory.
 * NOTE: Fills out the info structure, based on the specified file or directory.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in/out]    dirHandlePtr            directory handle pointer.
 * param[out]       infoPtr                 file or directory info structure pointer.
 * param[out]       availabilityPtr         element availability pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSDirRead(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
                tommRoC_fs_dir_t*                   const   dirHandlePtr,
                tommRoC_fs_info*                    const   infoPtr,
                tommRoC_fs_availability_enum_t*     const   availabilityPtr);

/**
 * Change the position of the directory to the beginning of the directory.
 *
 * param[in/out]    fsHandlePtr             file system handle pointer.
 * param[in/out]    dirHandlePtr            directory handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFSDirRewind(
                tommRoC_fs_file_system_t*           const   fsHandlePtr,
                tommRoC_fs_dir_t*                   const   dirHandlePtr);

/**
 * @}
 */

#endif
