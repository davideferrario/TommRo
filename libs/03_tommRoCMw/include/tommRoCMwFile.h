
#ifndef TOMMROC_MW_FILE_H_
#define TOMMROC_MW_FILE_H_

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
#include "tommRoCMwErr.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

 /*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC middleware file struct.
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
typedef void*                               tommRoC_mw_file_t;
#define __EMPTY_tommRoC_mw_file_t__         NULL

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
typedef void*                               tommRoC_mw_file_t;
#define __EMPTY_tommRoC_mw_file_t__         NULL

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX) || defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#include <stdio.h>

typedef FILE*                               tommRoC_mw_file_t;
#define __EMPTY_tommRoC_mw_file_t__         NULL

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)
#include <stdio.h>

typedef FILE*                               tommRoC_mw_file_t;

#define __EMPTY_tommRoC_mw_file_t__         NULL

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8) || defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16) || defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)
typedef void*                               tommRoC_mw_file_t;

#define __EMPTY_tommRoC_mw_file_t__         NULL

#else
#error "Not supported compiler"
#endif


// Enumeration of tommRoC middleware file open mode.
typedef enum {

    /**
     * Open file for input operations.
     * NOTE: the file must exist.
     */
    TOMMRO_C_MW_FILE_OPEN_FOR_READ = 0,

    /**
     * Create and open an empty file for output operations.
     * NOTE: if a file with the same name already exists, it is over-written with a new one.
     */
    TOMMRO_C_MW_FILE_OPEN_FOR_WRITE,

    /**
     * Open file for output at the end of a file.
     */
    TOMMRO_C_MW_FILE_OPEN_FOR_APPEND,

} tommRoC_mw_file_open_mode_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Check if tommRoC middleware file environment is available.
 *
 * return tommRoC_mw_err_enum_t
 *          TOMMRO_C_MW_ERR_SUCCESS         -> file environment available.
 *          TOMMRO_C_MW_NOT_AVAILABLE_ERR   -> file environment not available.
 */
tommRoC_mw_err_enum_t tommRoCMwFileIsAvailable(void);

/**
 * Open a file.
 *
 * param[in]        fileNameStrPtr          file name string pointer.
 * param[in]        openMode                file open mode.
 * param[out]       filePtr                 file struct pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwFileOpen(
        const   char*                               const   fileNameStrPtr,
        const   tommRoC_mw_file_open_mode_enum_t            openMode,
                tommRoC_mw_file_t*                  const   filePtr);

/**
 * Close a file.
 *
 * param[in]        filePtr                 file struct pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwFileClose(
                tommRoC_mw_file_t*                  const   filePtr);

/**
 * Get the size of a file.
 * NOTE: this is the OS file size; not the available data in the file size.
 *
 * param[in]        fileNameStrPtr          file name string pointer.
 * param[out]       fileSizePtr             output file size [byte] pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwFileSize(
        const   char*                               const   fileNameStrPtr,
                uint32_t*                           const   fileSizePtr);

/**
 * Write a buffer to a file.
 *
 * param[in]        writeBufferPtr          buffer pointer.
 * param[in]        writeBufferSize         buffer size.
 * param[in]        filePtr                 file struct pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwFileWriteBuffer(
        const   uint8_t*                            const   writeBufferPtr,
        const   uint16_t                                    writeBufferSize,
                tommRoC_mw_file_t*                  const   filePtr);

/**
 * Write a string to a file.
 *
 * param[in]        stringPtr               string pointer.
 * param[in]        filePtr                 file struct pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwFileWriteString(
        const   char*                               const   stringPtr,
                tommRoC_mw_file_t*                  const   filePtr);

/**
 * Write a new line to a file.
 *
 * param[in]        filePtr                 file struct pointer.
 *
 * return tommRoC_mw_err_enum_t
 */
tommRoC_mw_err_enum_t tommRoCMwFileWriteNewLine(
                tommRoC_mw_file_t*                  const   filePtr);

/**
 * Read a buffer from a file.
 *
 * param[out]       readBufferPtr           output buffer pointer.
 * param[in]        toReadSize              to read byte size
 * param[out]       readedSizePtr           readed byte count pointer.
 * param[in]        filePtr                 file struct pointer.
 *
 * return tommRoC_mw_err_enum_t
 *          TOMMRO_C_MW_ERR_SUCCESS                     -> read all the data buffer success.
 *          TOMMRO_C_MW_FILE_READ_NOT_ENOUGH_DATA_ERR   -> read data buffer success but readed only partial data buffer.
 *          TOMMRO_C_MW_FILE_READ_EOF_ERR               -> read data buffer error (end of the file).
 */
tommRoC_mw_err_enum_t tommRoCMwFileReadBuffer(
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    toReadSize,
                uint16_t*                           const   readedSizePtr,
                tommRoC_mw_file_t*                  const   filePtr);

/**
 * Read a line from a file.
 * NOTE: output data are as string [char*]
 * NOTE: read a complete line (all the data until a "new line" char is detected).
 *
 * param[out]       stringPtr               output string pointer (on output will be terminated wirh '\0').
 * param[in]        stringArraySize         maximum size of the output string [byte]
 * param[in]        filePtr                 file struct pointer.
 *
 * return tommRoC_mw_err_enum_t
 *          TOMMRO_C_MW_ERR_SUCCESS                     -> read line success.
 *          TOMMRO_C_MW_FILE_READ_EOF_ERR               -> read data buffer error (end of the file).
 */
tommRoC_mw_err_enum_t tommRoCMwFileReadLine(
                char*                               const   stringPtr,
        const   uint16_t                                    stringArraySize,
                tommRoC_mw_file_t*                  const   filePtr);

#endif
