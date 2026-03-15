
#ifndef TOMMROC_DEBUG_H_
#define TOMMROC_DEBUG_H_

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
 * @defgroup tommRoCDebug tommRoCDebug
 *
 * @brief  TommRoC library debug module
 * @author TommRo Software Department
 *
 * This module is providing debug functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCAssert.h"
#include "tommRoCDateTime.h"
#include "tommRoCErr.h"
#include "tommRoCGeometry.h"
#include "tommRoCGuard.h"
#include "tommRoCUtil.h"
#include "tommRoCVersion.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * Define __TOMMROC_DEBUG_ENABLE__ to enable tommRoC debug.
 *
 * Define __TOMMROC_DEBUG_PRINT_USE_ENV_DEFAULT__ to use library environment default debug print.
 *  - RTT for ARM
 *  - stdout for ESP32
 *  - stdout for Linux
 *
 * NOTE: remember to disable __TOMMROC_DEBUG_ENABLE__ in your release version.
 * This avoid internal library and/or high level application debug string
 * messages RAM and/or ROM occupancy if debug is not used.
 */

#if defined (__TOMMROC_DEBUG_ENABLE__)

#define TOMMROC_DEBUG_RAW_TYPE_ENABLE()                                                                                                             \
        do {                                                                                                                                        \
            const bool rawType = true;                                                                                                              \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCDebugSetProp(TOMMRO_C_DEBUG_RAW_TYPE_PROP, &rawType));                                  \
        } while (0)

#define TOMMROC_DEBUG_RAW_TYPE_DISABLE()                                                                                                            \
        do {                                                                                                                                        \
            const bool rawType = false;                                                                                                             \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCDebugSetProp(TOMMRO_C_DEBUG_RAW_TYPE_PROP, &rawType));                                  \
        } while (0)

#define TOMMROC_DEBUG_PRINT_ONLY_PRINTABLE_ENABLE()                                                                                                 \
        do {                                                                                                                                        \
            const tommRoC_util_enabled_status_enum_t onlyPrintable = TOMMRO_C_UTIL_ENABLED;                                                         \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCDebugSetProp(TOMMRO_C_DEBUG_PRINT_ONLY_PRINTABLE_ENABLED_STATUS_PROP, &onlyPrintable)); \
        } while (0)

#define TOMMROC_DEBUG_PRINT_ONLY_PRINTABLE_DISABLE()                                                                                                \
        do {                                                                                                                                        \
            const tommRoC_util_enabled_status_enum_t onlyPrintable = TOMMRO_C_UTIL_DISABLED;                                                        \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCDebugSetProp(TOMMRO_C_DEBUG_PRINT_ONLY_PRINTABLE_ENABLED_STATUS_PROP, &onlyPrintable)); \
        } while (0)

#define TOMMROC_DEBUG_SAVE_ONLY_PRINTABLE_ENABLE()                                                                                                  \
        do {                                                                                                                                        \
            const tommRoC_util_enabled_status_enum_t onlyPrintable = TOMMRO_C_UTIL_ENABLED;                                                         \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCDebugSetProp(TOMMRO_C_DEBUG_SAVE_ONLY_PRINTABLE_ENABLED_STATUS_PROP, &onlyPrintable));  \
        } while (0)

#define TOMMROC_DEBUG_SAVE_ONLY_PRINTABLE_DISABLE()                                                                                                 \
        do {                                                                                                                                        \
            const tommRoC_util_enabled_status_enum_t onlyPrintable = TOMMRO_C_UTIL_DISABLED;                                                        \
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCDebugSetProp(TOMMRO_C_DEBUG_SAVE_ONLY_PRINTABLE_ENABLED_STATUS_PROP, &onlyPrintable));  \
        } while (0)

#define TOMMROC_DEBUG_PRINTLN(debugLevel, msgStrPtr)                                                                                                \
        tommRoCDebugPrintln((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr))

#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING(debugLevel, msgStrPtr, strPtr)                                                                            \
        tommRoCDebugPrintlnPlusString((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (strPtr))

#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_LEN(debugLevel, msgStrPtr, strPtr, strLen)                                                                \
        tommRoCDebugPrintlnPlusStringLen((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (strPtr), (strLen))

#define TOMMROC_DEBUG_PRINTLN_PLUS_BOOL(debugLevel, msgStrPtr, value)                                                                               \
        tommRoCDebugPrintlnPlusBool((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (value))

#define TOMMROC_DEBUG_PRINTLN_PLUS_CH(debugLevel, msgStrPtr, ch)                                                                                    \
        tommRoCDebugPrintlnPlusCh((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (ch))

#define TOMMROC_DEBUG_PRINTLN_PLUS_U8(debugLevel, msgStrPtr, value, format)                                                                         \
        tommRoCDebugPrintlnPlusU8((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (value), (format))

#define TOMMROC_DEBUG_PRINTLN_PLUS_U16(debugLevel, msgStrPtr, value, format)                                                                        \
        tommRoCDebugPrintlnPlusU16((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (value), (format))

#define TOMMROC_DEBUG_PRINTLN_PLUS_U32(debugLevel, msgStrPtr, value, format)                                                                        \
        tommRoCDebugPrintlnPlusU32((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (value), (format))

#define TOMMROC_DEBUG_PRINTLN_PLUS_I8(debugLevel, msgStrPtr, value)                                                                                 \
        tommRoCDebugPrintlnPlusI8((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (value))

#define TOMMROC_DEBUG_PRINTLN_PLUS_I16(debugLevel, msgStrPtr, value)                                                                                \
        tommRoCDebugPrintlnPlusI16((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (value))

#define TOMMROC_DEBUG_PRINTLN_PLUS_I32(debugLevel, msgStrPtr, value)                                                                                \
        tommRoCDebugPrintlnPlusI32((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (value))

#define TOMMROC_DEBUG_PRINTLN_PLUS_FLOAT(debugLevel, msgStrPtr, value)                                                                              \
        tommRoCDebugPrintlnPlusFloat((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (value))
        
#define TOMMROC_DEBUG_PRINTLN_PLUS_BUFFER(debugLevel, msgStrPtr, bufPtr, bufSize)                                                                   \
        tommRoCDebugPrintlnPlusBuffer((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (bufPtr), (bufSize))

#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_STRING(debugLevel, msgStrPtr, strPtr, str1Ptr)                                                       \
        tommRoCDebugPrintlnPlusStringPlusString((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (strPtr), (str1Ptr))

#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_BOOL(debugLevel, msgStrPtr, strPtr, value)                                                           \
        tommRoCDebugPrintlnPlusStringPlusBool((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (strPtr), (value))

#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_CH(debugLevel, msgStrPtr, strPtr, ch)                                                                \
        tommRoCDebugPrintlnPlusStringPlusCh((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (strPtr), (ch))

#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_U8(debugLevel, msgStrPtr, strPtr, value, format)                                                     \
        tommRoCDebugPrintlnPlusStringPlusU8((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (strPtr), (value), (format))

#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_U16(debugLevel, msgStrPtr, strPtr, value, format)                                                    \
        tommRoCDebugPrintlnPlusStringPlusU16((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (strPtr), (value), (format))

#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_U32(debugLevel, msgStrPtr, strPtr, value, format)                                                    \
        tommRoCDebugPrintlnPlusStringPlusU32((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (strPtr), (value), (format))

#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_I8(debugLevel, msgStrPtr, strPtr, value)                                                             \
        tommRoCDebugPrintlnPlusStringPlusI8((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (strPtr), (value))

#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_I16(debugLevel, msgStrPtr, strPtr, value)                                                            \
        tommRoCDebugPrintlnPlusStringPlusI16((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (strPtr), (value))

#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_I32(debugLevel, msgStrPtr, strPtr, value)                                                            \
        tommRoCDebugPrintlnPlusStringPlusI32((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (strPtr), (value))

#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_FLOAT(debugLevel, msgStrPtr, strPtr, value)                                                          \
        tommRoCDebugPrintlnPlusStringPlusFloat((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (strPtr), (value))

#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_BUFFER(debugLevel, msgStrPtr, strPtr, bufPtr, bufSize)                                               \
        tommRoCDebugPrintlnPlusStringPlusBuffer((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (strPtr), (bufPtr), (bufSize))

#define TOMMROC_DEBUG_PRINTLN_PLUS_I32_PLUS_SPACE_PLUS_BUFFER(debugLevel, msgStrPtr, value, bufPtr, bufSize)                                        \
        tommRoCDebugPrintlnPlusI32PlusSpacePlusBuffer((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (value), (bufPtr), (bufSize))

#define TOMMROC_DEBUG_PRINTLN_PLUS_I32_PLUS_SPACE_PLUS_STRING_LEN(debugLevel, msgStrPtr, value, strPtr, strLen)                                     \
        tommRoCDebugPrintlnPlusI32PlusSpacePlusStringLen((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (value), (strPtr), (strLen))

#define TOMMROC_DEBUG_VERSION(debugLevel, msgStrPtr, version)                                                                                       \
        tommRoCDebugVersion((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (&version))

#define TOMMROC_DEBUG_DATE_TIME(debugLevel, msgStrPtr, dateTime)                                                                                    \
        tommRoCDebugDateTime((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (&dateTime))

#define TOMMROC_DEBUG_GEOMETRY_VECTOR(debugLevel, msgStrPtr, vector)                                                                                \
        tommRoCDebugGeometryVector((debugLevel), (__DEBUG_OBJ_ID__), (msgStrPtr), (&vector))

#define TOMMROC_DEBUG_D(msgStrPtr)                                                                                                                  \
        TOMMROC_DEBUG_PRINTLN((TOMMRO_C_DEBUG_D_LEVEL), (msgStrPtr))

#define TOMMROC_DEBUG_E(msgStrPtr)                                                                                                                  \
        TOMMROC_DEBUG_PRINTLN((TOMMRO_C_DEBUG_E_LEVEL), (msgStrPtr))

#define TOMMROC_DEBUG_I(msgStrPtr)                                                                                                                  \
        TOMMROC_DEBUG_PRINTLN((TOMMRO_C_DEBUG_I_LEVEL), (msgStrPtr))

#define TOMMROC_DEBUG_V(msgStrPtr)                                                                                                                  \
        TOMMROC_DEBUG_PRINTLN((TOMMRO_C_DEBUG_V_LEVEL), (msgStrPtr))

#define TOMMROC_DEBUG_W(msgStrPtr)                                                                                                                  \
        TOMMROC_DEBUG_PRINTLN((TOMMRO_C_DEBUG_W_LEVEL), (msgStrPtr))

#else

#define TOMMROC_DEBUG_RAW_TYPE_ENABLE()
#define TOMMROC_DEBUG_RAW_TYPE_DISABLE()
#define TOMMROC_DEBUG_PRINT_ONLY_PRINTABLE_ENABLE()
#define TOMMROC_DEBUG_PRINT_ONLY_PRINTABLE_DISABLE()
#define TOMMROC_DEBUG_SAVE_ONLY_PRINTABLE_ENABLE()
#define TOMMROC_DEBUG_SAVE_ONLY_PRINTABLE_DISABLE()
#define TOMMROC_DEBUG_PRINTLN(debugLevel, msgStrPtr)
#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING(debugLevel, msgStrPtr, strPtr)
#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_LEN(debugLevel, msgStrPtr, strPtr, strLen)
#define TOMMROC_DEBUG_PRINTLN_PLUS_BOOL(debugLevel, msgStrPtr, value)
#define TOMMROC_DEBUG_PRINTLN_PLUS_CH(debugLevel, msgStrPtr, ch)
#define TOMMROC_DEBUG_PRINTLN_PLUS_U8(debugLevel, msgStrPtr, value, format)
#define TOMMROC_DEBUG_PRINTLN_PLUS_U16(debugLevel, msgStrPtr, value, format)
#define TOMMROC_DEBUG_PRINTLN_PLUS_U32(debugLevel, msgStrPtr, value, format)
#define TOMMROC_DEBUG_PRINTLN_PLUS_I8(debugLevel, msgStrPtr, value)
#define TOMMROC_DEBUG_PRINTLN_PLUS_I16(debugLevel, msgStrPtr, value)
#define TOMMROC_DEBUG_PRINTLN_PLUS_I32(debugLevel, msgStrPtr, value)
#define TOMMROC_DEBUG_PRINTLN_PLUS_FLOAT(debugLevel, msgStrPtr, value)
#define TOMMROC_DEBUG_PRINTLN_PLUS_BUFFER(debugLevel, msgStrPtr, bufPtr, bufSize)
#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_STRING(debugLevel, msgStrPtr, strPtr, str1Ptr)
#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_BOOL(debugLevel, msgStrPtr, strPtr, value)
#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_CH(debugLevel, msgStrPtr, strPtr, ch)
#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_U8(debugLevel, msgStrPtr, strPtr, value, format)
#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_U16(debugLevel, msgStrPtr, strPtr, value, format)
#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_U32(debugLevel, msgStrPtr, strPtr, value, format)
#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_I8(debugLevel, msgStrPtr, strPtr, value)
#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_I16(debugLevel, msgStrPtr, strPtr, value)
#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_I32(debugLevel, msgStrPtr, strPtr, value)
#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_FLOAT(debugLevel, msgStrPtr, strPtr, value)
#define TOMMROC_DEBUG_PRINTLN_PLUS_STRING_PLUS_BUFFER(debugLevel, msgStrPtr, strPtr, bufPtr, bufSize)
#define TOMMROC_DEBUG_PRINTLN_PLUS_I32_PLUS_SPACE_PLUS_BUFFER(debugLevel, msgStrPtr, value, bufPtr, bufSize)
#define TOMMROC_DEBUG_PRINTLN_PLUS_I32_PLUS_SPACE_PLUS_STRING_LEN(debugLevel, msgStrPtr, value, strPtr, strLen)
#define TOMMROC_DEBUG_VERSION(debugLevel, msgStrPtr, version)
#define TOMMROC_DEBUG_DATE_TIME(debugLevel, msgStrPtr, dateTime)
#define TOMMROC_DEBUG_GEOMETRY_VECTOR(debugLevel, msgStrPtr, vector)
#define TOMMROC_DEBUG_D(msgStrPtr)
#define TOMMROC_DEBUG_E(msgStrPtr)
#define TOMMROC_DEBUG_I(msgStrPtr)
#define TOMMROC_DEBUG_V(msgStrPtr)
#define TOMMROC_DEBUG_W(msgStrPtr)

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC debug level.
typedef enum {

    /**
     * Debug debug level.
     */
    TOMMRO_C_DEBUG_D_LEVEL = 0,

    /**
     * Debug error level.
     */
    TOMMRO_C_DEBUG_E_LEVEL,

    /**
     * Debug info level.
     */
    TOMMRO_C_DEBUG_I_LEVEL,

    /**
     * Debug verbose level.
     */
    TOMMRO_C_DEBUG_V_LEVEL,

    /**
     * Debug warning level.
     */
    TOMMRO_C_DEBUG_W_LEVEL,

} tommRoC_debug_level_enum_t;


// Enumeration of tommRoC debug properties.
typedef enum {

    /**
     * Debug raw type.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be bool*
     */
    TOMMRO_C_DEBUG_RAW_TYPE_PROP = 0,

    /**
     * Debug print guard.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_guard_t*
     */
    TOMMRO_C_DEBUG_PRINT_GUARD_PROP,

    /**
     * Debug save guard.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_guard_t*
     */
    TOMMRO_C_DEBUG_SAVE_GUARD_PROP,

    /**
     * Debug is print pending status function pointer.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_debug_is_pending_funct_t
     */
    TOMMRO_C_DEBUG_IS_PRINT_PENDING_FUNCT_PTR_PROP,

    /**
     * Debug is save pending status function pointer.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_debug_is_pending_funct_t
     */
    TOMMRO_C_DEBUG_IS_SAVE_PENDING_FUNCT_PTR_PROP,

    /**
     * Only printable enabled status for print.
     * NOTE: by default only printable is disabled.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_util_enabled_status_enum_t*
     */
    TOMMRO_C_DEBUG_PRINT_ONLY_PRINTABLE_ENABLED_STATUS_PROP,

    /**
     * Only printable enabled status for save.
     * NOTE: by default only printable is disabled.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be tommRoC_util_enabled_status_enum_t*
     */
    TOMMRO_C_DEBUG_SAVE_ONLY_PRINTABLE_ENABLED_STATUS_PROP,

} tommRoC_debug_prop_enum_t;


// tommRoC debug function enabled status.
typedef struct {

    /**
     * Enabled status for particular debug type.
     * All enabled status TOMMRO_C_UTIL_DISABLED -> debug disable
     */
    tommRoC_util_enabled_status_enum_t debugDStatus;
    tommRoC_util_enabled_status_enum_t debugEStatus;
    tommRoC_util_enabled_status_enum_t debugIStatus;
    tommRoC_util_enabled_status_enum_t debugVStatus;
    tommRoC_util_enabled_status_enum_t debugWStatus;

} tommRoC_debug_funct_enabled_status_t;

#define __EMPTY_tommRoC_debug_funct_enabled_status_t__  \
{                                                       \
    /* .debugDStatus */ TOMMRO_C_UTIL_DISABLED,         \
    /* .debugEStatus */ TOMMRO_C_UTIL_DISABLED,         \
    /* .debugIStatus */ TOMMRO_C_UTIL_DISABLED,         \
    /* .debugVStatus */ TOMMRO_C_UTIL_DISABLED,         \
    /* .debugWStatus */ TOMMRO_C_UTIL_DISABLED,         \
}


// Prototype of tommRoC debug print string ['\0' terminated] function.
typedef tommRoC_err_enum_t (*tommRoC_debug_print_str_funct_t)(const tommRoC_debug_level_enum_t debugLevel, const char* const stringPtr);
// Prototype of tommRoC debug print len string [not '\0' terminated] function.
typedef tommRoC_err_enum_t (*tommRoC_debug_print_str_len_funct_t)(const tommRoC_debug_level_enum_t debugLevel, const char* const stringPtr, const uint16_t stringLen);
// Prototype of tommRoC debug save string ['\0' terminated] function.
typedef tommRoC_err_enum_t (*tommRoC_debug_save_str_funct_t)(const char* const stringPtr);
// Prototype of tommRoC debug is pending function.
typedef tommRoC_err_enum_t (*tommRoC_debug_is_pending_funct_t)(bool* const isPendingPtr);


// tommRoC debug print environment init data.
typedef struct {

    /**
     * Print debug function.
     */
    tommRoC_debug_print_str_funct_t         debugPrintStr;
    tommRoC_debug_print_str_len_funct_t     debugPrintStrLen;

    /**
     * New line string pointer to (have to finish with '\0' char).
     */
    const char*                             newLineStrPtr;

    /**
     * Debug enabled status.
     */
    tommRoC_debug_funct_enabled_status_t*   debugStatusPtr;

    /**
     * Print debug guard (set to NULL for disable).
     */
    tommRoC_guard_t*                        guardPtr;

} tommRoC_debug_print_env_init_t;

#define __EMPTY_tommRoC_debug_print_env_init_t__    \
{                                                   \
    /* .debugPrintStr */        NULL,               \
    /* .debugPrintStrLen */     NULL,               \
    /* .newLineStrPtr */        NULL,               \
    /* .debugStatusPtr */       NULL,               \
    /* .guardPtr */             NULL,               \
}


// tommRoC debug save environment init data.
typedef struct {

    /**
     * Save debug function.
     */
    tommRoC_debug_save_str_funct_t          debugSaveStr;

    /**
     * New line string pointer to (have to finish with '\0' char).
     */
    const char*                             newLineStrPtr;

    /**
     * Save debug guard (set to NULL for disable).
     */
    tommRoC_guard_t*                        guardPtr;

} tommRoC_debug_save_env_init_t;

#define __EMPTY_tommRoC_debug_save_env_init_t__ \
{                                               \
    /* .debugSaveStr */         NULL,           \
    /* .newLineStrPtr */        NULL,           \
    /* .guardPtr */             NULL,           \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Prepare debug environment.
 *
 * param[in]        initEnvironmentPtr      pointer to environment resource init data.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugInitEnv(const tommRoC_debug_print_env_init_t* const initEnvironmentPtr);

/**
 * Prepare default print debug environment.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugInitDefautPrintEnv(void);

/**
 * Prepare specific debug for save environment.
 *
 * param[in]        initEnvironmentPtr      pointer to environment resource init data.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugExtendForSaveEnv(const tommRoC_debug_save_env_init_t* const initEnvironmentPtr);

/**
 * Close debug environment.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugCloseEnv(void);

/**
 * Check if debug environment is init.
 *
 * param[in]        isInitPtr               Is init boolean status.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugIsInitEnv(bool* const isInitPtr);

/**
 * Check if debug for save environment is init.
 *
 * param[in]        isInitPtr               Is init boolean status.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugExtendForSaveIsInitEnv(bool* const isInitPtr);

/**
 * Set debug property.
 *
 * param[in]    property                property.
 * param[in]    propValuePtr            value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugSetProp(
        const   tommRoC_debug_prop_enum_t           property,
        const   void*                       const   propValuePtr);

/**
 * Get debug is pending status.
 *
 * param[out]   isPendingPtr            is debug pending status pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugIsPending(bool* const isPendingPtr);

/**
 * Get debug enable status for specific level.
 *
 * param[in]        debugLevel              debug level.
 *
 * return tommRoC_util_enabled_status_enum_t
 */
tommRoC_util_enabled_status_enum_t tommRoCDebugGetStatusDebugLevel(const tommRoC_debug_level_enum_t debugLevel);

/**
 * Debug a message (message parameters passed as string - [char*]) + new line char.
 * Format: header message + object name + message + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintln(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr);

/**
 * Debug a message (string parameter passed as string pointer - [char*] - and string length) + new line char.
 * Format: header message + object name + message + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrLen               debug message string length.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnLen(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   uint16_t                            msgStrLen);

/**
 * Debug a message + string (string parameter passed as '\0' terminated string - [char*]) + new line char.
 * Format: header message + object name + message + string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  debug string pointer [NOTE: string have to be ended with '\0' char].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusString(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr);

/**
 * Debug a message + string (string parameter passed as string pointer - [char*] - and string length) + new line char.
 * Format: header message + object name + message + string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  debug string pointer.
 * param[in]        strLen                  debug string length.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusStringLen(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   uint16_t                            strLen);

/**
 * Debug a message (message parameters passed as string - [char*]) + bool + new line char.
 * Format: header message + object name + message + character + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug boolean value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusBool(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   bool                                value);

/**
 * Debug a message (message parameters passed as string - [char*]) + character + new line char.
 * Format: header message + object name + message + character + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        ch                      debug character value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusCh(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char                                ch);

/**
 * Debug a message (message parameters passed as string - [char*]) + uint8_t as string + new line char.
 * Format: header message + object name + message + uint8_t as string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug uint8_t value.
 * param[in]        format                  number format.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusU8(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   uint8_t                             value,
        const   tommRoC_util_number_format_enum_t   format);

/**
 * Debug a message (message parameters passed as string - [char*]) + uint16_t as string + new line char.
 * Format: header message + object name + message + uint16_t as string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug uint16_t value.
 * param[in]        format                  number format.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusU16(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   uint16_t                            value,
        const   tommRoC_util_number_format_enum_t   format);

/**
 * Debug a message (message parameters passed as string - [char*]) + uint32_t as string + new line char.
 * Format: header message + object name + message + uint32_t as string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug uint32_t value.
 * param[in]        format                  number format.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusU32(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   uint32_t                            value,
        const   tommRoC_util_number_format_enum_t   format);

/**
 * Debug a message (message parameters passed as string - [char*]) + int8_t as string + new line char.
 * Format: header message + object name + message + int8_t as string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug int8_t value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusI8(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   int8_t                              value);

/**
 * Debug a message (message parameters passed as string - [char*]) + int16_t as string + new line char.
 * Format: header message + object name + message + int16_t as string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug int16_t value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusI16(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   int16_t                             value);

/**
 * Debug a message (message parameters passed as string - [char*]) + int32_t as string + new line char.
 * Format: header message + object name + message + int32_t as string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug int32_t value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusI32(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   int32_t                             value);

/**
 * Debug a message (message parameters passed as string - [char*]) + float as string + new line char.
 * Format: header message + object name + message + float as string + new line.
 * NOTE: float number is converted as I32 + dot + 6 decimal digits.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug int32_t value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusFloat(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   float                               value);

/**
 * Debug a message (message parameters passed as string - [char*]) + buffer [void*] as string + new line char.
 * Format: header message + object name + message + buffer [U8] as string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        bufferPtr               debug buffer pointer.
 * param[in]        bufferSize              debug buffer size.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusBuffer(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   void*                       const   bufferPtr,
        const   uint16_t                            bufferSize);

/**
 * Debug a message + string + string (string parameter passed as '\0' terminated string - [char*]) + new line char.
 * Format: header message + object name + message + string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  debug string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        str1Ptr                 debug string 1 pointer [NOTE: string have to be ended with '\0' char].
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusStringPlusString(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   char*                       const   str1Ptr);

/**
 * Debug a message + string (message parameters passed as string - [char*]) + bool + new line char.
 * Format: header message + object name + message + character + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  debug string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug boolean value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusStringPlusBool(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   bool                                value);

/**
 * Debug a message + string (message parameters passed as string - [char*]) + character + new line char.
 * Format: header message + object name + message + character + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  debug string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        ch                      debug character value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusStringPlusCh(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   char                                ch);

/**
 * Debug a message + string (message parameters passed as string - [char*]) + uint8_t as string + new line char.
 * Format: header message + object name + message + uint8_t as string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  debug string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug uint8_t value.
 * param[in]        format                  number format.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusStringPlusU8(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   uint8_t                             value,
        const   tommRoC_util_number_format_enum_t   format);

/**
 * Debug a message + string (message parameters passed as string - [char*]) + uint16_t as string + new line char.
 * Format: header message + object name + message + uint16_t as string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  debug string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug uint16_t value.
 * param[in]        format                  number format.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusStringPlusU16(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   uint16_t                            value,
        const   tommRoC_util_number_format_enum_t   format);

/**
 * Debug a message + string (message parameters passed as string - [char*]) + uint32_t as string + new line char.
 * Format: header message + object name + message + uint32_t as string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  debug string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug uint32_t value.
 * param[in]        format                  number format.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusStringPlusU32(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   uint32_t                            value,
        const   tommRoC_util_number_format_enum_t   format);

/**
 * Debug a message + string (message parameters passed as string - [char*]) + int8_t as string + new line char.
 * Format: header message + object name + message + int8_t as string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  debug string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug int8_t value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusStringPlusI8(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   int8_t                              value);

/**
 * Debug a message + string (message parameters passed as string - [char*]) + int16_t as string + new line char.
 * Format: header message + object name + message + int16_t as string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  debug string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug int16_t value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusStringPlusI16(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   int16_t                             value);

/**
 * Debug a message + string (message parameters passed as string - [char*]) + int32_t as string + new line char.
 * Format: header message + object name + message + int32_t as string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  debug string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug int32_t value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusStringPlusI32(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   int32_t                             value);

/**
 * Debug a message + string (message parameters passed as string - [char*]) + float as string + new line char.
 * Format: header message + object name + message + float as string + new line.
 * NOTE: float number is converted as I32 + dot + 6 decimal digits.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  debug string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug int32_t value.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusStringPlusFloat(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   float                               value);

/**
 * Debug a message + string (message parameters passed as string - [char*]) + buffer [void*] as string + new line char.
 * Format: header message + object name + message + buffer [U8] as string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        strPtr                  debug string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        bufferPtr               debug buffer pointer.
 * param[in]        bufferSize              debug buffer size.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusStringPlusBuffer(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   char*                       const   strPtr,
        const   void*                       const   bufferPtr,
        const   uint16_t                            bufferSize);

/**
 * Debug a message (message parameters passed as string - [char*]) + int32_t as string + space + buffer [void*] as string + new line char.
 * Format: header message + object name + message + int32_t as string + space + buffer [U8] as string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug int32_t value.
 * param[in]        bufferPtr               debug buffer pointer.
 * param[in]        bufferSize              debug buffer size.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusI32PlusSpacePlusBuffer(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   int32_t                             value,
        const   void*                       const   bufferPtr,
        const   uint16_t                            bufferSize);

/**
 * Debug a message (message parameters passed as string - [char*]) + int32_t as string + space + string (string parameter passed as string pointer - [char*] - and string length)  + new line char.
 * Format: header message + object name + message + int32_t as string + space + string + new line.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        value                   debug int32_t value.
 * param[in]        strPtr                  debug string pointer.
 * param[in]        strLen                  debug string length.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugPrintlnPlusI32PlusSpacePlusStringLen(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   int32_t                             value,
        const   char*                       const   strPtr,
        const   uint16_t                            strLen);

/**
 * Debug a tommRoC version struct + new line char.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        versionPtr              version pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugVersion(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   tommRoC_version_t*          const   versionPtr);

/**
 * Debug a tommRoC date time struct + new line char.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        dateTimePtr             date time structure pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugDateTime(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   tommRoC_date_time_t*        const   dateTimePtr);

/**
 * Debug a tommRoC geometry 3 axes vector float structure + new line char.
 *
 * param[in]        debugLevel              debug level.
 * param[in]        objectIDStrPtr          debug object name string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        msgStrPtr               debug message string pointer [NOTE: string have to be ended with '\0' char].
 * param[in]        vectorPtr               geometry 3 axes vector pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCDebugGeometryVector(
        const   tommRoC_debug_level_enum_t          debugLevel,
        const   char*                       const   objectIDStrPtr,
        const   char*                       const   msgStrPtr,
        const   tommRoC_geometry_vector_t*  const   vectorPtr);

/**
 * @}
 */

#endif
