
#ifndef TOMMROC_LOG_H_
#define TOMMROC_LOG_H_

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
 * @defgroup tommRoCLog tommRoCLog
 *
 * @brief  TommRoC library file system log module
 * @author TommRo Software Department
 *
 * This module is providing library log over abstracted file system functionality.
 * It can be used in case of application needs one log system over abstracted file system.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "FSItf/tommRoCFSItfDEF.h"

#include "tommRoCDateTime.h"
#include "tommRoCFS.h"
#include "tommRoCErr.h"
#include "tommRoCGeometry.h"
#include "tommRoCGuard.h"
#include "tommRoCUtil.h"
#include "tommRoCVersion.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// Init function parameter to let tommRoC library to detect disk reserved size based on disk size.
#define TOMMROC_LOG_FOR_LOG_RESERVED_SIZE_AUTOMATIC     (-1)

// Init function parameter to let tommRoC library to detect disk reserved size based on disk size.
#define TOMMROC_LOG_GET_OFFSET_FLAG_FIRST_CALL          (-1)


/**
 * Define __TOMMROC_LOG_ENABLE__ to enable tommRoC log.
 */

#if defined (__TOMMROC_LOG_ENABLE__)

#define TOMMROC_LOG_SET_ENABLED_STATUS(enabledStatus)                                               \
        tommRoCLogSetEnabledStatus((enabledStatus))

#define TOMMROC_LOG_GET_ENABLED_STATUS(enabledStatusPtr)                                            \
        tommRoCLogGetEnabledStatus((enabledStatusPtr))

#define TOMMROC_LOG_ENABLE()                                                                        \
        tommRoCLogSetEnabledStatus(TOMMRO_C_UTIL_ENABLED)

#define TOMMROC_LOG_DISABLE()                                                                       \
        tommRoCLogSetEnabledStatus(TOMMRO_C_UTIL_DISABLED)

#define TOMMROC_LOG_CLEAR()                                                                         \
        tommRoCLogClear()

#define TOMMROC_LOG_GET(outputStrPtr, outputStrSize, outputStrLenPtr, offsetFlagPtr)                \
        tommRoCLogGet((outputStrPtr), (outputStrSize), (outputStrLenPtr), (offsetFlagPtr))

#define TOMMROC_LOG_PRINTLN(msgStrPtr)                                                              \
        tommRoCLogPrintln((__LOG_OBJ_ID__), (msgStrPtr))

#define TOMMROC_LOG_PRINTLN_PLUS_STRING(msgStrPtr, strPtr)                                          \
        tommRoCLogPrintlnPlusString((__LOG_OBJ_ID__), (msgStrPtr), (strPtr))

#define TOMMROC_LOG_PRINTLN_PLUS_STRING_LEN(msgStrPtr, strPtr, strLen)                              \
        tommRoCLogPrintlnPlusStringLen((__LOG_OBJ_ID__), (msgStrPtr), (strPtr), (strLen))

#define TOMMROC_LOG_PRINTLN_PLUS_BOOL(msgStrPtr, value)                                             \
        tommRoCLogPrintlnPlusBool((__LOG_OBJ_ID__), (msgStrPtr), (value))

#define TOMMROC_LOG_PRINTLN_PLUS_U8(msgStrPtr, value, format)                                       \
        tommRoCLogPrintlnPlusU8((__LOG_OBJ_ID__), (msgStrPtr), (value), (format))

#define TOMMROC_LOG_PRINTLN_PLUS_U16(msgStrPtr, value, format)                                      \
        tommRoCLogPrintlnPlusU16((__LOG_OBJ_ID__), (msgStrPtr), (value), (format))

#define TOMMROC_LOG_PRINTLN_PLUS_U32(msgStrPtr, value, format)                                      \
        tommRoCLogPrintlnPlusU32((__LOG_OBJ_ID__), (msgStrPtr), (value), (format))

#define TOMMROC_LOG_PRINTLN_PLUS_I8(msgStrPtr, value)                                               \
        tommRoCLogPrintlnPlusI8((__LOG_OBJ_ID__), (msgStrPtr), (value))

#define TOMMROC_LOG_PRINTLN_PLUS_I16(msgStrPtr, value)                                              \
        tommRoCLogPrintlnPlusI16((__LOG_OBJ_ID__), (msgStrPtr), (value))

#define TOMMROC_LOG_PRINTLN_PLUS_I32(msgStrPtr, value)                                              \
        tommRoCLogPrintlnPlusI32((__LOG_OBJ_ID__), (msgStrPtr), (value))

#define TOMMROC_LOG_PRINTLN_PLUS_FLOAT(msgStrPtr, value)                                            \
        tommRoCLogPrintlnPlusFloat((__LOG_OBJ_ID__), (msgStrPtr), (value))

#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_STRING(msgStrPtr, strPtr, str1Ptr)                     \
        tommRoCLogPrintlnPlusStringPlusString((__LOG_OBJ_ID__), (msgStrPtr), (strPtr), (str1Ptr))

#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_BOOL(msgStrPtr, strPtr, value)                         \
        tommRoCLogPrintlnPlusStringPlusBool((__LOG_OBJ_ID__), (msgStrPtr), (strPtr), (value))

#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_U8(msgStrPtr, strPtr, value, format)                   \
        tommRoCLogPrintlnPlusStringPlusU8((__LOG_OBJ_ID__), (msgStrPtr), (strPtr), (value), (format))

#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_U16(msgStrPtr, strPtr, value, format)                  \
        tommRoCLogPrintlnPlusStringPlusU16((__LOG_OBJ_ID__), (msgStrPtr), (strPtr), (value), (format))

#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_U32(msgStrPtr, strPtr, value, format)                  \
        tommRoCLogPrintlnPlusStringPlusU32((__LOG_OBJ_ID__), (msgStrPtr), (strPtr), (value), (format))

#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_I8(msgStrPtr, strPtr, value)                           \
        tommRoCLogPrintlnPlusStringPlusI8((__LOG_OBJ_ID__), (msgStrPtr), (strPtr), (value))

#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_I16(msgStrPtr, strPtr, value)                          \
        tommRoCLogPrintlnPlusStringPlusI16((__LOG_OBJ_ID__), (msgStrPtr), (strPtr), (value))

#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_I32(msgStrPtr, strPtr, value)                          \
        tommRoCLogPrintlnPlusStringPlusI32((__LOG_OBJ_ID__), (msgStrPtr), (strPtr), (value))

#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_FLOAT(msgStrPtr, strPtr, value)                        \
        tommRoCLogPrintlnPlusStringPlusFloat((__LOG_OBJ_ID__), (msgStrPtr), (strPtr), (value))

#define TOMMROC_LOG_PRINTLN_PLUS_I32_PLUS_SPACE_PLUS_STRING_LEN(msgStrPtr, value, strPtr, strLen)   \
        tommRoCLogPrintlnPlusI32PlusSpacePlusStringLen((__LOG_OBJ_ID__), (msgStrPtr), (value), (strPtr), (strLen))

#define TOMMROC_LOG_VERSION(msgStrPtr, version)                                                     \
        tommRoCLogVersion((__LOG_OBJ_ID__), (msgStrPtr), (&version))

#define TOMMROC_LOG_DATE_TIME(msgStrPtr, dateTime)                                                  \
        tommRoCLogDateTime((__LOG_OBJ_ID__), (msgStrPtr), (&dateTime))

#define TOMMROC_LOG_GEOMETRY_VECTOR(msgStrPtr, vector)                                              \
        tommRoCLogGeometryVector((__LOG_OBJ_ID__), (msgStrPtr), (&vector))

#else

#define TOMMROC_LOG_SET_ENABLED_STATUS(enabledStatus)
#define TOMMROC_LOG_GET_ENABLED_STATUS(enabledStatusPtr)
#define TOMMROC_LOG_ENABLE()
#define TOMMROC_LOG_DISABLE()
#define TOMMROC_LOG_CLEAR()
#define TOMMROC_LOG_GET(outputStrPtr, outputStrSize, outputStrLenPtr, offsetFlagPtr)
#define TOMMROC_LOG_PRINTLN(msgStrPtr)
#define TOMMROC_LOG_PRINTLN_PLUS_STRING(msgStrPtr, strPtr)
#define TOMMROC_LOG_PRINTLN_PLUS_STRING_LEN(msgStrPtr, strPtr, strLen)
#define TOMMROC_LOG_PRINTLN_PLUS_BOOL(msgStrPtr, value)
#define TOMMROC_LOG_PRINTLN_PLUS_U8(msgStrPtr, value, format)
#define TOMMROC_LOG_PRINTLN_PLUS_U16(msgStrPtr, value, format)
#define TOMMROC_LOG_PRINTLN_PLUS_U32(msgStrPtr, value, format)
#define TOMMROC_LOG_PRINTLN_PLUS_I8(msgStrPtr, value)
#define TOMMROC_LOG_PRINTLN_PLUS_I16(msgStrPtr, value)
#define TOMMROC_LOG_PRINTLN_PLUS_I32(msgStrPtr, value)
#define TOMMROC_LOG_PRINTLN_PLUS_FLOAT(msgStrPtr, value)
#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_STRING(msgStrPtr, strPtr, str1Ptr)
#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_BOOL(msgStrPtr, strPtr, value)
#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_U8(msgStrPtr, strPtr, value, format)
#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_U16(msgStrPtr, strPtr, value, format)
#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_U32(msgStrPtr, strPtr, value, format)
#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_I8(msgStrPtr, strPtr, value)
#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_I16(msgStrPtr, strPtr, value)
#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_I32(msgStrPtr, strPtr, value)
#define TOMMROC_LOG_PRINTLN_PLUS_STRING_PLUS_FLOAT(msgStrPtr, strPtr, value)
#define TOMMROC_LOG_PRINTLN_PLUS_I32_PLUS_SPACE_PLUS_STRING_LEN(msgStrPtr, value, strPtr, strLen)
#define TOMMROC_LOG_VERSION(msgStrPtr, version)
#define TOMMROC_LOG_DATE_TIME(msgStrPtr, dateTime)
#define TOMMROC_LOG_GEOMETRY_VECTOR(msgStrPtr, vector)

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* Log framework management functions */

/**
 * Init log framework.
 *
 * param[in]        lowLevelFileSize        low level file structure size [byte].
 * param[in]        logFSConfigPtr          log file system configuration pointer.
 * param[in]        guardPtr                log framework guard pointer (set to NULL to disable).
 * param[in]        forLogReservedSize      for log reserved disk size [byte] (set to TOMMROC_LOG_FOR_LOG_RESERVED_SIZE_AUTOMATIC to let tommRoC library to detect disk reserved size based on disk size).
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogInit(
        const   uint32_t                                            lowLevelFileSize,
        const   tommRoC_fs_itf_def_file_system_config_t*    const   logFSConfigPtr,
        const   tommRoC_guard_t*                            const   guardPtr,
        const   int32_t                                             forLogReservedSize);

/**
 * Init log framework for a tommRoCFS file system.
 *
 * param[in]        fsHandlePtr             tommRoCFS file system handle pointer.
 * param[in]        guardPtr                log framework guard pointer (set to NULL to disable).
 * param[in]        forLogReservedSize      for log reserved disk size [byte] (set to TOMMROC_LOG_FOR_LOG_RESERVED_SIZE_AUTOMATIC to let tommRoC library to detect disk reserved size based on disk size).
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogInitAsFS(
        const   tommRoC_fs_file_system_t*                   const   fsHandlePtr,
        const   tommRoC_guard_t*                            const   guardPtr,
        const   int32_t                                             forLogReservedSize);

/**
 * Init log framework for a tommRoCFSMbed file system.
 *
 * param[in]        guardPtr                log framework guard pointer (set to NULL to disable).
 * param[in]        forLogReservedSize      for log reserved disk size [byte] (set to TOMMROC_LOG_FOR_LOG_RESERVED_SIZE_AUTOMATIC to let tommRoC library to detect disk reserved size based on disk size).
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogInitAsFSMbed(
        const   tommRoC_guard_t*                            const   guardPtr,
        const   int32_t                                             forLogReservedSize);

/**
 * Close log framework.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogClose(void);

/**
 * Check if log framework is init.
 *
 * param[in]        isInitPtr               Is init boolean status.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogIsInit(bool* const isInitPtr);


/******************* Log framework functions */

/**
 * Set enabled status for log saving layer.
 * NOTE: by default log layer is enabled. This can be used to disable temporarily the functionality.
 *
 * param[in]        enabledStatus           enabled status.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogSetEnabledStatus(const tommRoC_util_enabled_status_enum_t enabledStatus);

/**
 * Get enabled status for log saving layer.
 *
 * param[out]       enabledStatusPtr        enabled status pointer
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogGetEnabledStatus(tommRoC_util_enabled_status_enum_t* const enabledStatusPtr);

/**
 * Clear the saved logs.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogClear(void);

/**
 * Get some log rows from saved.
 * NOTE: only complete log rows re returned.
 *
 * param[out]       outputStrPtr            output log string pointer.
 * param[in]        outputStrSize           output log string size [byte].
 * param[out]       outputStrLenPtr         output log string length [byte] pointer.
 * param[in/out]    offsetFlagPtr           low level offset/flag pointer.
 *                                          NOTE:   - on first call, offset/flag MUST be set to TOMMROC_LOG_GET_OFFSET_FLAG_FIRST_CALL.
 *                                                  - on next calls, MUST be passed the returned value.
 *                                                  - returned offset/flag value will be 0 when no more logs are available.
 *
 * NOTE: example application is:
 *  int32_t offsetFlag;
 *  offsetFlag = TOMMROC_LOG_GET_OFFSET_FLAG_FIRST_CALL;
 *
 *  while (0 != offsetFlag) {
 *      TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCLogGet(outputStr, sizeof(outputStr), &outputStrLen, &offsetFlag));
 *      if (outputStrLen > 0) {
 *          // Do something with log string
 *      }
 *      TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(0));
 *  }
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogGet(
                char*       const   outputStrPtr,
        const   uint32_t            outputStrSize,
                uint32_t*   const   outputStrLenPtr,
                int32_t*    const   offsetFlagPtr);

/**
 * Log a message (message parameters passed as string - [char*]).
 * Format: date + object name + message.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintln(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr);

/**
 * Log a message (string parameter passed as string pointer - [char*] - and string length).
 * Format: date + object name + message.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrLen               log message string length.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnLen(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   uint16_t                            msgStrLen);

/**
 * Log a message + string (string parameter passed as '\0' terminated string - [char*]).
 * Format: date + object name + message + string.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  log string pointer [NOTE: string have to be ended with '\0' char].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusString(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr);

/**
 * Log a message + string (string parameter passed as string pointer - [char*] - and string length).
 * Format: date + object name + message + string.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  log string pointer.
 * param[in]        strLen                  log string length.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusStringLen(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   uint16_t                            strLen);

/**
 * Log a message (message parameters passed as string - [char*]) + bool.
 * Format: date + object name + message + character.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log boolean value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusBool(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   bool                                value);

/**
 * Log a message (message parameters passed as string - [char*]) + uint8_t as string.
 * Format: date + object name + message + uint8_t as string.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log uint8_t value.
 * param[in]        format                  number format.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusU8(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   uint8_t                             value,
        const   tommRoC_util_number_format_enum_t   format);

/**
 * Log a message (message parameters passed as string - [char*]) + uint16_t as string.
 * Format: date + object name + message + uint16_t as string.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log uint16_t value.
 * param[in]        format                  number format.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusU16(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   uint16_t                            value,
        const   tommRoC_util_number_format_enum_t   format);

/**
 * Log a message (message parameters passed as string - [char*]) + uint32_t as string.
 * Format: date + object name + message + uint32_t as string.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log uint32_t value.
 * param[in]        format                  number format.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusU32(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   uint32_t                            value,
        const   tommRoC_util_number_format_enum_t   format);

/**
 * Log a message (message parameters passed as string - [char*]) + int8_t as string.
 * Format: date + object name + message + int8_t as string.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log int8_t value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusI8(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   int8_t                              value);

/**
 * Log a message (message parameters passed as string - [char*]) + int16_t as string.
 * Format: date + object name + message + int16_t as string.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log int16_t value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusI16(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   int16_t                             value);

/**
 * Log a message (message parameters passed as string - [char*]) + int32_t as string.
 * Format: date + object name + message + int32_t as string.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log int32_t value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusI32(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   int32_t                             value);

/**
 * Log a message (message parameters passed as string - [char*]) + float as string.
 * Format: date + object name + message + float as string.
 * NOTE: float number is converted as I32 + dot + 6 decimal digits.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log int32_t value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusFloat(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   float                               value);

/**
 * Log a message + string + string (string parameter passed as '\0' terminated string - [char*]).
 * Format: date + object name + message + string.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  log string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        str1Ptr                 log string 1 pointer [NOTE: string have to be ended with '\0' char].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusStringPlusString(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   char*                       const   str1Ptr);

/**
 * Log a message + string (message parameters passed as string - [char*]) + bool.
 * Format: date + object name + message + character.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  log string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log boolean value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusStringPlusBool(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   bool                                value);

/**
 * Log a message + string (message parameters passed as string - [char*]) + uint8_t as string.
 * Format: date + object name + message + uint8_t as string.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  log string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log uint8_t value.
 * param[in]        format                  number format.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusStringPlusU8(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   uint8_t                             value,
        const   tommRoC_util_number_format_enum_t   format);

/**
 * Log a message + string (message parameters passed as string - [char*]) + uint16_t as string.
 * Format: date + object name + message + uint16_t as string.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  log string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log uint16_t value.
 * param[in]        format                  number format.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusStringPlusU16(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   uint16_t                            value,
        const   tommRoC_util_number_format_enum_t   format);

/**
 * Log a message + string (message parameters passed as string - [char*]) + uint32_t as string.
 * Format: date + object name + message + uint32_t as string.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  log string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log uint32_t value.
 * param[in]        format                  number format.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusStringPlusU32(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   uint32_t                            value,
        const   tommRoC_util_number_format_enum_t   format);

/**
 * Log a message + string (message parameters passed as string - [char*]) + int8_t as string.
 * Format: date + object name + message + int8_t as string.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  log string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log int8_t value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusStringPlusI8(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   int8_t                              value);

/**
 * Log a message + string (message parameters passed as string - [char*]) + int16_t as string.
 * Format: date + object name + message + int16_t as string.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  log string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log int16_t value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusStringPlusI16(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   int16_t                             value);

/**
 * Log a message + string (message parameters passed as string - [char*]) + int32_t as string.
 * Format: date + object name + message + int32_t as string.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  log string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log int32_t value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusStringPlusI32(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   int32_t                             value);

/**
 * Log a message + string (message parameters passed as string - [char*]) + float as string.
 * Format: date + object name + message + float as string.
 * NOTE: float number is converted as I32 + dot + 6 decimal digits.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  log string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log int32_t value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusStringPlusFloat(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   float                               value);

/**
 * Log a message (message parameters passed as string - [char*]) + int32_t as string + space + string (string parameter passed as string pointer - [char*] - and string length).
 * Format: date + object name + message + int32_t as string + space + string + new line.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   log int32_t value.
 * param[in]        strPtr                  log string pointer.
 * param[in]        strLen                  log string length.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogPrintlnPlusI32PlusSpacePlusStringLen(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   int32_t                             value,
        const   char*                       const   strPtr,
        const   uint16_t                            strLen);

/**
 * Log a tommRoC version struct.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        versionPtr              version pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogVersion(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   tommRoC_version_t*          const   versionPtr);

/**
 * Log a tommRoC date time struct.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        dateTimePtr             date time structure pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogDateTime(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   tommRoC_date_time_t*        const   dateTimePtr);

/**
 * Log a tommRoC geometry 3 axes vector float structure.
 *
 * param[in]        objectIDStrPtr          log object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               log message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        vectorPtr               geometry 3 axes vector pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCLogGeometryVector(
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   tommRoC_geometry_vector_t*  const   vectorPtr);

/**
 * @}
 */

#endif
