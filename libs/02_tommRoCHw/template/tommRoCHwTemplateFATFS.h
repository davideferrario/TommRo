
#ifndef TOMMROC_HW_TEMPLATE_FAT_FS_H_
#define TOMMROC_HW_TEMPLATE_FAT_FS_H_

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
 *  - __TOMMROC_HW_USE_FAT_FS_TEMPLATE__            to use FAT FS template
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"
#include "TOMMROCHw.h"

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)
#include "fatfs.h"
#endif

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// File access mode and open method flags (argument of file open function)
#define TOMMROC_HW_TEMPLATE_FAT_FS_FA_READ                  (0b00000001)
#define TOMMROC_HW_TEMPLATE_FAT_FS_FA_WRITE                 (0b00000010)
#define TOMMROC_HW_TEMPLATE_FAT_FS_FA_OPEN_EXISTING         (0b00000000)
#define TOMMROC_HW_TEMPLATE_FAT_FS_FA_CREATE_NEW            (0b00000100)
#define TOMMROC_HW_TEMPLATE_FAT_FS_FA_CREATE_ALWAYS         (0b00001000)
#define TOMMROC_HW_TEMPLATE_FAT_FS_FA_OPEN_ALWAYS           (0b00010000)
#define TOMMROC_HW_TEMPLATE_FAT_FS_FA_OPEN_APPEND           (0b00110000)


// Maximum file name length [bytes].
#if (0 == _USE_LFN)
#define TOMMROC_HW_TEMPLATE_FAT_FS_FILENAME_MAX_LEN_BYTE    (8 + TOMMROC_STRING_DOT_CHAR_SIZE + 3)  // NOTE: used 8.3 notation for filename
#else
#define TOMMROC_HW_TEMPLATE_FAT_FS_FILENAME_MAX_LEN_BYTE    (_MAX_LFN)
#endif
// Maximum file name size [bytes].
#define TOMMROC_HW_TEMPLATE_FAT_FS_FILENAME_MAX_SIZE_BYTE   (TOMMROC_HW_TEMPLATE_FAT_FS_FILENAME_MAX_LEN_BYTE + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)

// Directories separator char.
// NOTE: to open files into directory, the file path need to be specified using "dirName1/dirName2/fileName"
#define TOMMROC_HW_TEMPLATE_FAT_FS_DIR_SEPARATOR_CHAR       (TOMMROC_STRING_SLASH_CHAR)
#define TOMMROC_HW_TEMPLATE_FAT_FS_DIR_SEPARATOR_CHAR_SIZE  (TOMMROC_STRING_SLASH_CHAR_SIZE)
#define TOMMROC_HW_TEMPLATE_FAT_FS_DIR_SEPARATOR_STR        (TOMMROC_STRING_SLASH_STR)
#define TOMMROC_HW_TEMPLATE_FAT_FS_DIR_SEPARATOR_STR_SIZE   (TOMMROC_STRING_SLASH_STR_SIZE)
#define TOMMROC_HW_TEMPLATE_FAT_FS_DIR_SEPARATOR_STR_LENGTH (TOMMROC_STRING_SLASH_STR_LENGTH)


#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)
#if _FS_READONLY && _USE_FASTSEEK && _FS_TINY
#define TOMMROC_HW_TEMPLATE_FAT_FS_FILE_HANDLE_SIZE         ()
#elif _FS_READONLY && _USE_FASTSEEK && !_FS_TINY
#define TOMMROC_HW_TEMPLATE_FAT_FS_FILE_HANDLE_SIZE         ()
#elif _FS_READONLY && !_USE_FASTSEEK && _FS_TINY
#define TOMMROC_HW_TEMPLATE_FAT_FS_FILE_HANDLE_SIZE         ()
#elif _FS_READONLY && !_USE_FASTSEEK && !_FS_TINY
#define TOMMROC_HW_TEMPLATE_FAT_FS_FILE_HANDLE_SIZE         ()
#elif !_FS_READONLY && _USE_FASTSEEK && _FS_TINY
#define TOMMROC_HW_TEMPLATE_FAT_FS_FILE_HANDLE_SIZE         ()
#elif !_FS_READONLY && _USE_FASTSEEK && !_FS_TINY
#define TOMMROC_HW_TEMPLATE_FAT_FS_FILE_HANDLE_SIZE         (556)
#elif !_FS_READONLY && !_USE_FASTSEEK && _FS_TINY
#define TOMMROC_HW_TEMPLATE_FAT_FS_FILE_HANDLE_SIZE         ()
#elif !_FS_READONLY && !_USE_FASTSEEK && !_FS_TINY
#define TOMMROC_HW_TEMPLATE_FAT_FS_FILE_HANDLE_SIZE         ()
#endif

#if _USE_LFN != 0 && _USE_FIND
#define TOMMROC_HW_TEMPLATE_FAT_FS_DIR_HANDLE_SIZE          ()
#elif _USE_LFN == 0 && _USE_FIND
#define TOMMROC_HW_TEMPLATE_FAT_FS_DIR_HANDLE_SIZE          ()
#elif _USE_LFN != 0 && !_USE_FIND
#define TOMMROC_HW_TEMPLATE_FAT_FS_DIR_HANDLE_SIZE          (48)
#elif _USE_LFN == 0 && !_USE_FIND
#define TOMMROC_HW_TEMPLATE_FAT_FS_DIR_HANDLE_SIZE          ()
#endif
#endif

// NOTE: if FAT_FS_TEMPLATE not defined, define faked size
#if !defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)
#define TOMMROC_HW_TEMPLATE_FAT_FS_FILE_HANDLE_SIZE         (1)
#define TOMMROC_HW_TEMPLATE_FAT_FS_DIR_HANDLE_SIZE          (1)
#endif


// Wait forever timeout for Mkfs (disk format)
#define TOMMROC_HW_TEMPLATE_FAT_FS_DISK_FORMAT_WAIT_FOREVER_TIMEOUT (UINT32_MIN)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of FATFS type (file or directory).
typedef enum {

    // Element is a file.
     TOMMROC_HW_TEMPLATE_FAT_FS_TYPE_FILE = 0,

    // Element is a directory
     TOMMROC_HW_TEMPLATE_FAT_FS_TYPE_DIR,

} tommRoC_hw_template_fat_fs_type_enum_t;


// Enumeration of FATFS directory element availability.
typedef enum {

    // A valid element is available in directory and it is returned by function.
    TOMMROC_HW_TEMPLATE_FAT_FS_AVAILABILITY_ELEMENT = 0,

    // No more element is available in directory.
    TOMMROC_HW_TEMPLATE_FAT_FS_AVAILABILITY_NO_ELEMENT,

} tommRoC_hw_template_fat_fs_availability_enum_t;


// FATFS file/directory info struct.
typedef struct {

    tommRoC_hw_template_fat_fs_type_enum_t  type;                                                       // Type (file or directory)
    uint32_t                                size;                                                       // Size
    char                                    name[TOMMROC_HW_TEMPLATE_FAT_FS_FILENAME_MAX_SIZE_BYTE];    // Name

} tommRoC_hw_template_fat_fs_info;


// FATFS file struct
typedef struct {
    uint8_t data[TOMMROC_HW_TEMPLATE_FAT_FS_FILE_HANDLE_SIZE];
} tommRoC_hw_template_fat_fs_file_t;

// FATFS dir struct
typedef struct {
    uint8_t data[TOMMROC_HW_TEMPLATE_FAT_FS_DIR_HANDLE_SIZE];
} tommRoC_hw_template_fat_fs_dir_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Start FATFS environment (mount logical drive).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSStart(void);

/**
 * Stop FATFS environment (unmount logical drive).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSStop(void);

/**
 * Set guard to FATFS environment.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSSetGuard(const tommRoC_guard_t* const guardPtr);


/**
 * Check if SD card is available.
 *
 * param[out]       sdCardAvailablePtr      boolean SD card is available pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSSDCardAvailable(
                bool*                                           const   sdCardAvailablePtr);


/**
 * Get is busy (one operation is in execution) status of FATFS environment.
 *
 * return bool
 */
bool tommRoCHwTemplateFATFSGetIsBusy(void);


/**
 * Open or create a file.
 *
 * param[in]        pathStrPtr              file name string pointer.
 * param[in]        mode                    access mode and file open mode flags. OR of TOMMROC_HW_TEMPLATE_FAT_FS_FA define
 * param[out]       filePtr                 file struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFOpen(
        const   char*                                           const   pathStrPtr,
        const   uint8_t                                                 mode,
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr);

/**
 * Close file.
 *
 * param[in/out]    filePtr                 file struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFClose(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr);

/**
 * Read data from a a file.
 *
 * param[in/out]    filePtr                 file struct pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 * NOTE: TOMMRO_C_HW_ERR_SUCCESS in case of read success. Effective readed byte amount is returned in readedAmountPtr parameter (it can be different from requested "to read byte amount").
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFRead(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr,
                void*                                           const   readBufferPtr,
        const   uint32_t                                                toReadAmount,
                uint32_t*                                       const   readedAmountPtr);

/**
 * Write data to a a file.
 *
 * param[in/out]    filePtr                 file struct pointer.
 * param[in]        writeBufferPtr          data buffer pointer.
 * param[in]        writeBufferLen          data buffer length.
 * param[out]       writtenAmountPtr        written byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 * NOTE: TOMMRO_C_HW_ERR_SUCCESS in case of write success. Effective written byte amount is returned in writtenAmountPtr parameter (it can be different from requested "data buffer length").
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFWrite(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr,
        const   void*                                           const   writeBufferPtr,
        const   uint32_t                                                writeBufferLen,
                uint32_t*                                       const   writtenAmountPtr);

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
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFReadRP(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr,
                void*                                           const   readBufferPtr,
        const   uint32_t                                                toReadAmount);

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
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFWriteRP(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr,
        const   void*                                           const   writeBufferPtr,
        const   uint32_t                                                writeBufferLen);

/**
 * Seek file pointer.
 *
 * param[in/out]    filePtr                 file struct pointer.
 * param[in]        offsetByte              file offset from top of file.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFLSeek(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr,
        const   uint32_t                                                offsetByte);

/**
 * Delete file or directory.
 *
 * param[in]        pathStrPtr              file or directory path string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFDelete(
        const   char*                                           const   pathStrPtr);

/**
 * Rename/Move file or directory.
 *
 * param[in]        pathOldStrPtr           old file or directory path string pointer.
 * param[in]        pathNewStrPtr           new file or directory path string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFRename(
        const   char*                                           const   pathOldStrPtr,
        const   char*                                           const   pathNewStrPtr);

/**
 * Get file status.
 *
 * param[in]        pathStrPtr              file or directory path string pointer.
 * param[out]       fileInfoPtr             file information struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFStat(
        const   char*                                           const   pathStrPtr,
                tommRoC_hw_template_fat_fs_info*                const   fileInfoPtr);

/**
 * Create an FAT/exFAT volume.
 * NOTE: the format is executed only when there are no opened files/directories.
 *
 * param[in]        timeoutMsec             wait for no opened files/directories timeout [msec]. TOMMROC_HW_TEMPLATE_FAT_FS_DISK_FORMAT_WAIT_FOREVER_TIMEOUT for wait forever.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFMkfs(
        const   uint32_t                                                timeoutMsec);

/**
 * Get file size.
 *
 * param[in/out]    filePtr                 file struct pointer.
 *
 * return uint32_t
 */
uint32_t tommRoCHwTemplateFATFSFSize(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr);

/**
 * Rewind file.
 *
 * param[in/out]    filePtr                 file struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFRewind(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr);

/**
 * Check if file exists.
 *
 * param[in]        pathStrPtr              file path string pointer.
 * param[out]       fileExistsPtr           boolean file exists pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFExists(
        const   char*                                           const   pathStrPtr,
                bool*                                           const   fileExistsPtr);

/**
 * Create a sub directory.
 *
 * param[in]        pathStrPtr              directory path string pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFMkDir(
        const   char*                                           const   pathStrPtr);

/**
 * Open a directory.
 *
 * param[in]        pathStrPtr              directory name string pointer.
 * param[out]       dirPtr                  directory struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFOpenDir(
        const   char*                                           const   pathStrPtr,
                tommRoC_hw_template_fat_fs_dir_t*               const   dirPtr);

/**
 * Close an open directory.
 *
 * param[in/out]    dirPtr                  directory struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFCloseDir(
                tommRoC_hw_template_fat_fs_dir_t*               const   dirPtr);

/**
 * Read Directory Entries in Sequence.
 *
 * param[in/out]    dirPtr                  directory struct pointer.
 * param[out]       dirInfoPtr              directory information struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFReadDir(
                tommRoC_hw_template_fat_fs_dir_t*               const   dirPtr,
                tommRoC_hw_template_fat_fs_info*                const   dirInfoPtr,
                tommRoC_hw_template_fat_fs_availability_enum_t* const   availabilityPtr);

/**
 * Change the position of the directory to the beginning of the directory.
 *
 * param[in/out]    dirPtr                  directory struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFRewindDir(
                tommRoC_hw_template_fat_fs_dir_t*               const   dirPtr);

/**
 * Get disk free size.
 *
 * param[out]       freeSizeBytePtr         disk free size [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFGetFree(
                uint32_t*                                       const   freeSizeBytePtr);

#endif
