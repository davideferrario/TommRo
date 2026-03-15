
#ifndef TOMMROC_FILE_X_H_
#define TOMMROC_FILE_X_H_

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
 * @defgroup tommRoCFileX tommRoCFileX
 *
 * @brief  TommRoC library file system fileX module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted file system fileX functionality.
 * Please note that it is based on FileX (https://github.com/eclipse-threadx/filex) library.
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
// NOTE: in the end added 2 * TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE because of compatibility with tommRoCFS.
#define TOMMROC_FILE_X_FILENAME_MAX_SIZE_BYTE           (TOMMROC_UTIL_STRING_ARR_LENGTH("longFileNameTest1234567890") + TOMMROC_UTIL_STRING_ARR_LENGTH(".dat") + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)
#define TOMMROC_FILE_X_FILENAME_MAX_LENGTH_BYTE         (TOMMROC_UTIL_STRING_ARR_LENGTH("longFileNameTest1234567890") + TOMMROC_UTIL_STRING_ARR_LENGTH(".dat") + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)

// Maximum complete path name size [bytes].
#define TOMMROC_FILE_X_COMPLETE_PATH_MAX_SIZE_BYTE      (TOMMROC_UTIL_STRING_ARR_LENGTH("longDirNameTest1234567890/longDirNameTest1234567890/") + TOMMROC_FILE_X_FILENAME_MAX_SIZE_BYTE)
#define TOMMROC_FILE_X_COMPLETE_PATH_MAX_LENGTH_BYTE    (TOMMROC_UTIL_STRING_ARR_LENGTH("longDirNameTest1234567890/longDirNameTest1234567890/") + TOMMROC_FILE_X_FILENAME_MAX_LENGTH_BYTE)


// Max file size [bytes].
#define TOMMROC_FILE_X_FILE_MAX_SIZE_BYTE       (INT32_MAX)

// Directories separator char.
// NOTE: to open files into directory, the file path need to be specified using "dirName1/dirName2/fileName"
#define TOMMROC_FILE_X_DIR_SEPARATOR_CHAR       (TOMMROC_STRING_SLASH_CHAR)
#define TOMMROC_FILE_X_DIR_SEPARATOR_CHAR_SIZE  (TOMMROC_STRING_SLASH_CHAR_SIZE)
#define TOMMROC_FILE_X_DIR_SEPARATOR_STR        (TOMMROC_STRING_SLASH_STR)
#define TOMMROC_FILE_X_DIR_SEPARATOR_STR_SIZE   (TOMMROC_STRING_SLASH_STR_SIZE)
#define TOMMROC_FILE_X_DIR_SEPARATOR_STR_LENGTH (TOMMROC_STRING_SLASH_STR_LENGTH)


// File system struct size.
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#define TOMMROC_FILE_X_FILE_SYSTEM_HANDLE_SIZE  (7640)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#define TOMMROC_FILE_X_FILE_SYSTEM_HANDLE_SIZE  (7640)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)
#define TOMMROC_FILE_X_FILE_SYSTEM_HANDLE_SIZE  (9808)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#define TOMMROC_FILE_X_FILE_SYSTEM_HANDLE_SIZE  (9808)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)
#endif


// File struct size.
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#define TOMMROC_FILE_X_FILE_HANDLE_SIZE         (256)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#define TOMMROC_FILE_X_FILE_HANDLE_SIZE         (256)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)
#define TOMMROC_FILE_X_FILE_HANDLE_SIZE         (288)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#define TOMMROC_FILE_X_FILE_HANDLE_SIZE         (288)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16)
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)
#endif


// Minimum media memory buffer size.
#define TOMMROC_FILE_X_MINIMUM_MEDIA_MEMORY_SIZE_BYTE   (512)


// Wait forever timeout for disk format
#define TOMMROC_FILE_X_DISK_FORMAT_WAIT_FOREVER_TIMEOUT (UINT32_MIN)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC fileX init type.
typedef enum {

    // Init file system keeping previously saved data.
    TOMMROC_FILE_X_INIT_KEEP_DATA = 0,

    // Init file system forcing device format.
    TOMMROC_FILE_X_INIT_FORCE_FORMAT,

} tommRoC_file_x_init_type_enum_t;


// Enumeration of tommRoC fileX system opening file type.
typedef enum {

    // Open a file as read only.
    TOMMROC_FILE_X_OPEN_FILE_FOR_READ = 0,

    // Open a file as write only AND create if it does not exist.
    TOMMROC_FILE_X_OPEN_FILE_FOR_WRITE,

    // Open a file as read and write AND create if it does not exist.
    TOMMROC_FILE_X_OPEN_FILE_FOR_READ_WRITE,

    // Open a file as read and write AND create if it does not exist AND move to end of file on every write.
    // NOTE: the file offset is set to the end of the file prior to each write.
    TOMMROC_FILE_X_OPEN_FILE_FOR_APPEND,

} tommRoC_file_x_file_open_type_enum_t;


// Enumeration of tommRoC fileX system seek file type.
typedef enum {

    /**
     * Seek file from start of file.
     * NOTE: offset have to be positive or zero.
     */
    TOMMROC_FILE_X_SEEK_FILE_SET = 0,

    /**
     * Seek file from current position of file.
     * NOTE: offset can be negative, positive or zero.
     */
    TOMMROC_FILE_X_SEEK_FILE_CUR,

    /**
     * Seek file from end of file.
     * NOTE: offset have to be negative or zero.
     */
    TOMMROC_FILE_X_SEEK_FILE_END,

} tommRoC_file_x_seek_whence_enum_t;


// Enumeration of tommRoC fileX system type (file or directory).
typedef enum {

    // Element is a file.
    TOMMROC_FILE_X_TYPE_FILE = 0,

    // Element is a directory
    TOMMROC_FILE_X_TYPE_DIR,

} tommRoC_file_x_type_enum_t;


// Enumeration of tommRoC fileX system directory element availability.
typedef enum {

    // A valid element is available in directory and it is returned by function.
    TOMMROC_FILE_X_AVAILABILITY_ELEMENT = 0,

    // No more element is available in directory.
    TOMMROC_FILE_X_AVAILABILITY_NO_ELEMENT,

} tommRoC_file_x_availability_enum_t;


// Possible error codes for block callback function.
typedef enum {

    TOMMROC_FILE_X_SUCCESS              = 0x00, // No error
    TOMMROC_FILE_X_BOOT_ERROR           = 0x01,
    TOMMROC_FILE_X_MEDIA_INVALID        = 0x02,
    TOMMROC_FILE_X_FAT_READ_ERROR       = 0x03,
    TOMMROC_FILE_X_NOT_FOUND            = 0x04,
    TOMMROC_FILE_X_NOT_A_FILE           = 0x05,
    TOMMROC_FILE_X_ACCESS_ERROR         = 0x06,
    TOMMROC_FILE_X_NOT_OPEN             = 0x07,
    TOMMROC_FILE_X_FILE_CORRUPT         = 0x08,
    TOMMROC_FILE_X_END_OF_FILE          = 0x09,
    TOMMROC_FILE_X_NO_MORE_SPACE        = 0x0A,
    TOMMROC_FILE_X_ALREADY_CREATED      = 0x0B,
    TOMMROC_FILE_X_INVALID_NAME         = 0x0C,
    TOMMROC_FILE_X_INVALID_PATH         = 0x0D,
    TOMMROC_FILE_X_NOT_DIRECTORY        = 0x0E,
    TOMMROC_FILE_X_NO_MORE_ENTRIES      = 0x0F,
    TOMMROC_FILE_X_DIR_NOT_EMPTY        = 0x10,
    TOMMROC_FILE_X_MEDIA_NOT_OPEN       = 0x11,
    TOMMROC_FILE_X_INVALID_YEAR         = 0x12,
    TOMMROC_FILE_X_INVALID_MONTH        = 0x13,
    TOMMROC_FILE_X_INVALID_DAY          = 0x14,
    TOMMROC_FILE_X_INVALID_HOUR         = 0x15,
    TOMMROC_FILE_X_INVALID_MINUTE       = 0x16,
    TOMMROC_FILE_X_INVALID_SECOND       = 0x17,
    TOMMROC_FILE_X_PTR_ERROR            = 0x18,
    TOMMROC_FILE_X_INVALID_ATTR         = 0x19,
    TOMMROC_FILE_X_CALLER_ERROR         = 0x20,
    TOMMROC_FILE_X_BUFFER_ERROR         = 0x21,
    TOMMROC_FILE_X_NOT_IMPLEMENTED      = 0x22,
    TOMMROC_FILE_X_WRITE_PROTECT        = 0x23,
    TOMMROC_FILE_X_INVALID_OPTION       = 0x24,
    TOMMROC_FILE_X_SECTOR_INVALID       = 0x89,
    TOMMROC_FILE_X_IO_ERROR             = 0x90,
    TOMMROC_FILE_X_NOT_ENOUGH_MEMORY    = 0x91,
    TOMMROC_FILE_X_ERROR_FIXED          = 0x92,
    TOMMROC_FILE_X_ERROR_NOT_FIXED      = 0x93,
    TOMMROC_FILE_X_NOT_AVAILABLE        = 0x94,
    TOMMROC_FILE_X_INVALID_CHECKSUM     = 0x95,
    TOMMROC_FILE_X_READ_CONTINUE        = 0x96,
    TOMMROC_FILE_X_INVALID_STATE        = 0x97,

} tommRoC_file_x_error_enum_t;


// Read a data region callback function type definition.
typedef tommRoC_err_enum_t (*tommRoC_file_x_read_funct_t)(
                void*       const   fxMediaDriverInfoPtr,
        const   uint32_t            logicalAddStart,
                void*       const   dataBufferPtr,
        const   uint32_t            dataBufferSize,
                uint32_t*   const   readedLenghtPtr);

// Write a data region callback function type definition.
typedef tommRoC_err_enum_t (*tommRoC_file_x_write_funct_t)(
                void*       const   fxMediaDriverInfoPtr,
        const   uint32_t            logicalAddStart,
        const   void*       const   dataBufferPtr,
        const   uint32_t            dataBufferSize,
                uint32_t*   const   writtenLenghtPtr);

// Release (erase) a data region callback function type definition.
typedef tommRoC_err_enum_t (*tommRoC_file_x_release_funct_t)(
                void*       const   fxMediaDriverInfoPtr,
        const   uint32_t            logicalAddStart,
        const   uint32_t            dataSize,
                uint32_t*   const   releasedLenghtPtr);


// tommRoC fileX system config struct.
typedef struct {

    // Opaque user provided context (media driver) that can be used to pass information to the block device callback functions.
    void*                           fxMediaDriverInfoPtr;

    // Read a data region.
    tommRoC_file_x_read_funct_t     readCb;

    // Write a data region.
    tommRoC_file_x_write_funct_t    writeCb;

    // Release a data region.
    tommRoC_file_x_release_funct_t  releaseCb;

    // Pointer to media memory buffer used by the low level FileX for this media.
    void*                           mediaMemoryPtr;
    // Size of media memory buffer - MUST be at least TOMMROC_FILE_X_MINIMUM_MEDIA_MEMORY_SIZE_BYTE - 512 - bytes and one sector size.
    uint32_t                        mediaMemorySizeByte;

    // Disk total number of sectors.
    uint32_t                        diskTotalSectors;
    // Size [byte] per disk sector.
    uint32_t                        diskBytesPerSector;

} tommRoC_file_x_file_system_config_t;

#define __EMPTY_tommRoC_file_x_file_system_config_t__   \
{                                                       \
    /* .fxMediaDriverInfoPtr */ NULL,                   \
    /* .readCb */               NULL,                   \
    /* .writeCb */              NULL,                   \
    /* .releaseCb */            NULL,                   \
    /* .mediaMemoryPtr */       NULL,                   \
    /* .mediaMemorySizeByte */  0,                      \
    /* .diskTotalSectors */     0,                      \
    /* .diskBytesPerSector */   0,                      \
}


// tommRoC fileX system file/directory info struct.
typedef struct {

    tommRoC_file_x_type_enum_t  type;                                           // Type (file or directory)
    uint32_t                    size;                                           // Size
    char                        name[TOMMROC_FILE_X_FILENAME_MAX_SIZE_BYTE];    // Name

} tommRoC_file_x_info;

#define __EMPTY_tommRoC_file_x_info__                                                                   \
{                                                                                                       \
    /* .type */ TOMMROC_FILE_X_TYPE_FILE,                                                               \
    /* .size */ 0,                                                                                      \
    /* .name */ TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_FILE_X_FILENAME_MAX_SIZE_BYTE - 1, 0), \
}


// tommRoC fileX system file system struct.
typedef struct {
    uint8_t data[TOMMROC_FILE_X_FILE_SYSTEM_HANDLE_SIZE];
} tommRoC_file_x_file_system_t;

#define __EMPTY_tommRoC_file_x_file_system_t_data_field__           TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_FILE_X_FILE_SYSTEM_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_file_x_file_system_t__                      \
{                                                                   \
    /* .data */ __EMPTY_tommRoC_file_x_file_system_t_data_field__,  \
}


// tommRoC fileX system file struct.
typedef struct {
    uint8_t data[TOMMROC_FILE_X_FILE_HANDLE_SIZE];
} tommRoC_file_x_file_t;

#define __EMPTY_tommRoC_file_x_file_t_data_field__          TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_FILE_X_FILE_HANDLE_SIZE - 1, 0)
#define __EMPTY_tommRoC_file_x_file_t__                     \
{                                                           \
    /* .data */ __EMPTY_tommRoC_file_x_file_t_data_field__, \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* File system management functions */

/**
 * Init (mount) a fileX file system.
 *
 * param[in]        fileXInitType           file system init type.
 * param[in]        fileXConfigPtr          file system configuration pointer.
 * param[in]        guardPtr                file system guard pointer (set to NULL to disable).
 * param[out]       fileXHandlePtr          file system handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXInit(
        const   tommRoC_file_x_init_type_enum_t                 fileXInitType,
        const   tommRoC_file_x_file_system_config_t*    const   fileXConfigPtr,
        const   tommRoC_guard_t*                        const   guardPtr,
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr);

/**
 * Close (un-mount) a fileX file system.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXClose(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr);

/**
 * Get last fileX file system operation result.
 *
 * param[in]        fileXHandlePtr          file system handle pointer.
 *
 * return tommRoC_file_x_error_enum_t
 */
tommRoC_file_x_error_enum_t tommRoCFileXGetLastOpResult(
        const   tommRoC_file_x_file_system_t*           const   fileXHandlePtr);

/**
 * Get is busy (one operation is in execution) status of fileX file system.
 *
 * param[in]        fileXHandlePtr          file system handle pointer.
 *
 * return bool
 */
bool tommRoCFileXGetIsBusy(
        const   tommRoC_file_x_file_system_t*           const   fileXHandlePtr);


/******************* Disk functions */

/**
 * Format the disk (file system).
 * NOTE: the format is executed only when there are no opened files/directories.
 *
 * param[in]        fileXHandlePtr          file system handle pointer.
 * param[in]        timeoutMsec             wait for no opened files/directories timeout [msec]. TOMMROC_FILE_X_DISK_FORMAT_WAIT_FOREVER_TIMEOUT for wait forever.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXDiskFormat(
                tommRoC_file_x_file_system_t*       const   fileXHandlePtr,
        const   uint32_t                                    timeoutMsec);

/**
 * Get size of the disk [byte].
 *
 * param[in]        fileXHandlePtr          file system handle pointer.
 * param[out]       totalSizeBytePtr        size of the disk [byte] pointer.
 * param[out]       usedSizeBytePtr         current used size [byte] in the disk.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXDiskGetSize(
                tommRoC_file_x_file_system_t*       const   fileXHandlePtr,
                uint32_t*                           const   totalSizeBytePtr,
                uint32_t*                           const   usedSizeBytePtr);


/******************* File system functions */

/**
 * Get info about a file or directory.
 *
 * param[in]        fileXHandlePtr          file system handle pointer.
 * param[in]        pathStrPtr              path/file name string pointer.
 * param[out]       infoPtr                 file or directory info structure pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXStat(
                tommRoC_file_x_file_system_t*       const   fileXHandlePtr,
        const   char*                               const   pathStrPtr,
                tommRoC_file_x_info*                const   infoPtr);

/**
 * Removes a file or directory.
 * NOTE: if removing a directory, the directory must be empty.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in]        pathStrPtr              path/file name string pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXRemove(
                tommRoC_file_x_file_system_t*       const   fileXHandlePtr,
        const   char*                               const   pathStrPtr);

/**
 * Rename or move a file or directory.
 * NOTE: if the destination exists, it must match the source in type.
 * NOTE: if the destination is a directory, the directory must be empty.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in]        oldPathStrPtr           old path/file name string pointer.
 * param[in]        newPathStrPtr           new path/file name string pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXRename(
                tommRoC_file_x_file_system_t*       const   fileXHandlePtr,
        const   char*                               const   oldPathStrPtr,
        const   char*                               const   newPathStrPtr);

/**
 * Check if a file or directory exists.
 * NOTE: on low level function, the type of file or directory is not checked.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in]        pathStrPtr              path/file name string pointer.
 * param[out]       existsPtr               output file/directory exists pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXExists(
                tommRoC_file_x_file_system_t*       const   fileXHandlePtr,
        const   char*                               const   pathStrPtr,
                bool*                               const   existsPtr);


/******************* File operations functions */

/**
 * Check if a file exists.
 * NOTE: on low level function, it is checked that it MUST BE a file; not a directory.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in]        pathStrPtr              path/file name string pointer.
 * param[out]       fileExistsPtr           output file exists pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXFileExists(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
        const   char*                                   const   pathStrPtr,
                bool*                                   const   fileExistsPtr);

/**
 * Open a file.
 * NOTE: if opening in write/readWrite mode and file does not exist, a new one is always created.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in]        filePathStrPtr          path/file name string pointer.
 * param[in]        openType                opening type.
 * param[out]       fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXFileOpen(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
        const   char*                                   const   filePathStrPtr,
        const   tommRoC_file_x_file_open_type_enum_t            openType,
                tommRoC_file_x_file_t*                  const   fileHandlePtr);

/**
 * Close a file.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXFileClose(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
                tommRoC_file_x_file_t*                  const   fileHandlePtr);

/**
 * Synchronize a file on storage.
 * NOTE: Any pending writes are written out to storage.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXFileSync(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
                tommRoC_file_x_file_t*                  const   fileHandlePtr);

/**
 * Read data from a file.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_err_enum_t
 * NOTE: TOMMRO_C_ERR_SUCCESS in case of read success. Effective readed byte amount is returned in readedAmountPtr parameter (it can be different from requested "to read byte amount").
 */
tommRoC_err_enum_t tommRoCFileXFileRead(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
                tommRoC_file_x_file_t*                  const   fileHandlePtr,
                void*                                   const   readBufferPtr,
        const   uint32_t                                        toReadAmount,
                uint32_t*                               const   readedAmountPtr);

/**
 * Write data to a file.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[in]        writeBufferPtr          data buffer.
 * param[in]        writeBufferLen          data buffer length.
 * param[out]       writtenAmountPtr        written byte count pointer.
 *
 * return tommRoC_err_enum_t
 * NOTE: TOMMRO_C_ERR_SUCCESS in case of write success. Effective written byte amount is returned in writtenAmountPtr parameter (it can be different from requested "data buffer length").
 */
tommRoC_err_enum_t tommRoCFileXFileWrite(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
                tommRoC_file_x_file_t*                  const   fileHandlePtr,
        const   void*                                   const   writeBufferPtr,
        const   uint32_t                                        writeBufferLen,
                uint32_t*                               const   writtenAmountPtr);

/**
 * Read data from a file.
 * NOTE: reduced parameters (RP) version.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXFileReadRP(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
                tommRoC_file_x_file_t*                  const   fileHandlePtr,
                void*                                   const   readBufferPtr,
        const   uint32_t                                        toReadAmount);

/**
 * Write data to a file.
 * NOTE: reduced parameters (RP) version.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[in]        writeBufferPtr          data buffer.
 * param[in]        writeBufferLen          data buffer length.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXFileWriteRP(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
                tommRoC_file_x_file_t*                  const   fileHandlePtr,
        const   void*                                   const   writeBufferPtr,
        const   uint32_t                                        writeBufferLen);

/**
 * Sets the file position to the given offset.
 * NOTE: the argument offset signifies the number of bytes to seek from the given whence position.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[in]        offset                  number of bytes to seek.
 * param[in]        whence                  whence position.
 *
 * NOTE:
 *  if whence = TOMMROC_FILE_X_SEEK_FILE_SET    -> offset have to be positive or zero.
 *  if whence = TOMMROC_FILE_X_SEEK_FILE_CUR    -> offset can be negative, positive or zero.
 *  if whence = TOMMROC_FILE_X_SEEK_FILE_END    -> offset have to be negative or zero.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXFileSeek(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
                tommRoC_file_x_file_t*                  const   fileHandlePtr,
        const   int32_t                                         offset,
        const   tommRoC_file_x_seek_whence_enum_t               whence);

/**
 * Sets the file position to the beginning of the file.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXFileRewind(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
                tommRoC_file_x_file_t*                  const   fileHandlePtr);

/**
 * Sets the file position to the end of the file.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXFileMoveToEnd(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
                tommRoC_file_x_file_t*                  const   fileHandlePtr);

/**
 * Truncates the size of the file to the specified param size.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 * param[in]        size                    file size to be truncated [byte].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXFileTruncate(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
                tommRoC_file_x_file_t*                  const   fileHandlePtr,
        const   uint32_t                                        size);

/**
 * Get the size of the file.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in/out]    fileHandlePtr           file handle pointer.
 *
 * return uint32_t (UINT32_MAX in case of error)
 */
uint32_t tommRoCFileXFileSize(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
                tommRoC_file_x_file_t*                  const   fileHandlePtr);


/******************* Directory operations functions */

/**
 * Check if a directory exists.
 * NOTE: on low level function, it is checked that it MUST BE a directory; not a file.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in]        pathStrPtr              path/file name string pointer.
 * param[out]       dirExistsPtr            output directory exists pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXDirExists(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
        const   char*                                   const   pathStrPtr,
                bool*                                   const   dirExistsPtr);

/**
 * Create a directory.
 *
 * param[in/out]    fileXHandlePtr          file system handle pointer.
 * param[in]        pathStrPtr              path string pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCFileXDirMkDir(
                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
        const   char*                                   const   pathStrPtr);

///**
// * Open a directory.
// * NOTE: once open, a directory can be used with read to iterate over files.
// *
// * param[in/out]    fileXHandlePtr          file system handle pointer.
// * param[in]        dirPathStrPtr           path/directory name string pointer.
// * param[out]       dirHandlePtr            directory handle pointer.
// *
// * return tommRoC_err_enum_t
// */
//tommRoC_err_enum_t tommRoCFileXDirOpen(
//                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
//        const   char*                                   const   dirPathStrPtr,
//                tommRoC_fs_dir_t*                       const   dirHandlePtr);
//
///**
// * Close a directory.
// *
// * param[in/out]    fileXHandlePtr          file system handle pointer.
// * param[in/out]    dirHandlePtr            directory handle pointer.
// *
// * return tommRoC_err_enum_t
// */
//tommRoC_err_enum_t tommRoCFileXDirClose(
//                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
//                tommRoC_fs_dir_t*                       const   dirHandlePtr);
//
///**
// * Read an entry in the directory.
// * NOTE: Fills out the info structure, based on the specified file or directory.
// *
// * param[in/out]    fileXHandlePtr          file system handle pointer.
// * param[in/out]    dirHandlePtr            directory handle pointer.
// * param[out]       infoPtr                 file or directory info structure pointer.
// * param[out]       availabilityPtr         element availability pointer.
// *
// * return tommRoC_err_enum_t
// */
//tommRoC_err_enum_t tommRoCFileXDirRead(
//                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
//                tommRoC_fs_dir_t*                       const   dirHandlePtr,
//                tommRoC_fs_info*                        const   infoPtr,
//                tommRoC_file_x_availability_enum_t*     const   availabilityPtr);
//
///**
// * Change the position of the directory to the beginning of the directory.
// *
// * param[in/out]    fileXHandlePtr          file system handle pointer.
// * param[in/out]    dirHandlePtr            directory handle pointer.
// *
// * return tommRoC_err_enum_t
// */
//tommRoC_err_enum_t tommRoCFileXDirRewind(
//                tommRoC_file_x_file_system_t*           const   fileXHandlePtr,
//                tommRoC_fs_dir_t*                       const   dirHandlePtr);

/**
 * @}
 */

#endif
