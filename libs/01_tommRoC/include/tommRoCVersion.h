
#ifndef TOMMROC_VERSION_H_
#define TOMMROC_VERSION_H_

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
 * @defgroup tommRoCVersion tommRoCVersion
 *
 * @brief  TommRoC library version module
 * @author TommRo Software Department
 *
 * This module is providing version define and functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCString.h"
#include "tommRoCUtil.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// Library version
#define TOMMROC_VERSION_MAJOR       1   // NOTE: don't use () because it is not compatible with define string conversion
#define TOMMROC_VERSION_MINOR       3
#define TOMMROC_VERSION_PATCH       16

#if defined (__GNUC__)
#define TOMMROC_VERSION_AS_STR_STRING_MAX_ARRAY_SIZE_BYTE(projectNameStr)       \
        TOMMROC_UTIL_STRING_ARR_LENGTH(projectNameStr)                      +   \
        TOMMROC_STRING_SPACE_CHAR_SIZE                                      +   \
        TOMMROC_STRING_U8_DEC_AS_STRING_MAX_LENGTH_BYTE                     +   \
        TOMMROC_STRING_DOT_CHAR_SIZE                                        +   \
        TOMMROC_STRING_U8_DEC_AS_STRING_MAX_LENGTH_BYTE                     +   \
        TOMMROC_STRING_DOT_CHAR_SIZE                                        +   \
        TOMMROC_STRING_U8_DEC_AS_STRING_MAX_LENGTH_BYTE                     +   \
        TOMMROC_STRING_SPACE_CHAR_SIZE                                      +   \
        TOMMROC_STRING_U8_DEC_AS_STRING_MAX_LENGTH_BYTE                     +   \
        TOMMROC_STRING_DOT_CHAR_SIZE                                        +   \
        TOMMROC_STRING_U8_DEC_AS_STRING_MAX_LENGTH_BYTE                     +   \
        TOMMROC_STRING_DOT_CHAR_SIZE                                        +   \
        TOMMROC_STRING_U8_DEC_AS_STRING_MAX_LENGTH_BYTE                     +   \
        TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE
#else
#define TOMMROC_VERSION_AS_STR_STRING_MAX_ARRAY_SIZE_BYTE(projectNameStr)       \
        TOMMROC_UTIL_STRING_ARR_LENGTH(projectNameStr)                      +   \
        TOMMROC_STRING_SPACE_CHAR_SIZE                                      +   \
        TOMMROC_STRING_U8_DEC_AS_STRING_MAX_LENGTH_BYTE                     +   \
        TOMMROC_STRING_DOT_CHAR_SIZE                                        +   \
        TOMMROC_STRING_U8_DEC_AS_STRING_MAX_LENGTH_BYTE                     +   \
        TOMMROC_STRING_DOT_CHAR_SIZE                                        +   \
        TOMMROC_STRING_U8_DEC_AS_STRING_MAX_LENGTH_BYTE                     +   \
        TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE
#endif

#define TOMMROC_VERSION_AS_STR_STRING_ARR_LENGTH(projectNameStr)    (TOMMROC_VERSION_AS_STR_STRING_MAX_ARRAY_SIZE_BYTE(projectNameStr) - TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC version struct
// NOTE: refer to http://semver.org/ for details
typedef struct {

    /**
     * Project name (pointer to '\0' terminated string).
     */
    char*   projectName;

    /**
     * Project major version.
     * NOTE: not compatible API changes.
     */
    uint8_t major;

    /**
     * Project minor version.
     * NOTE: functionality added in a backwards-compatible manner.
     */
    uint8_t minor;

    /**
     * Project patch version.
     * NOTE: backwards-compatible bug fixes.
     */
    uint8_t patch;

#if defined (__GNUC__)
    /**
     * GNU C compiler major/minor/patch version.
     */
    uint8_t GNUCMajor;
    uint8_t GNUCMinor;
    uint8_t GNUCPatch;
#endif

} tommRoC_version_t;

#if defined (__GNUC__)
#define __EMPTY_tommRoC_version_t__             \
{                                               \
    /* .projectName */  NULL,                   \
    /* .major */        0,                      \
    /* .minor */        0,                      \
    /* .patch */        0,                      \
    /* .GNUCMajor */    __GNUC__,               \
    /* .GNUCMinor */    __GNUC_MINOR__,         \
    /* .GNUCPatch */    __GNUC_PATCHLEVEL__,    \
}
#else
#define __EMPTY_tommRoC_version_t__             \
{                                               \
    /* .projectName */  NULL,                   \
    /* .major */        0,                      \
    /* .minor */        0,                      \
    /* .patch */        0,                      \
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Get tommRoC library version.
 *
 * param[out]       libVersionPtr           pointer to library version result.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCVersionGet(
                tommRoC_version_t*  const   libVersionPtr);

/**
 * Get tommRoC library version as string.
 *
 * return const char*
 */
const char* tommRoCVersionGetAsStr(void);

/**
 * Get tommRoC library compiled as debug status.
 *
 * return bool
 */
bool tommRoCVersionIsDbg(void);

/**
 * Convert a version struct into a null terminated string.
 *
 * param[in]        versionPtr              version pointer.
 * param[in]        versionStrMaxSize       output version string buffer max size [byte].
 * param[out]       versionStrPtr           output version string pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCVersionToStr(
        const   tommRoC_version_t*  const   versionPtr,
        const   uint16_t                    versionStrMaxSize,
                char*               const   versionStrPtr);

/**
 * Compares two versions.
 *
 * param[in]        version1Ptr             first version pointer.
 * param[in]        version2Ptr             second version pointer.
 *
 * return tommRoC_err_enum_t
 *          TOMMRO_C_ERR_SUCCESS                                    -> compare success (versions are matching).
 *          TOMMRO_C_COMPARE_NOT_COMPATIBLE_PARAMS                  -> versions has different project name string
 *          TOMMRO_C_COMPARE_PARAM_1_LOWER_THAN_PARAM_2_ERR         -> version version1Ptr is lower than version2Ptr.
 *          TOMMRO_C_COMPARE_PARAM_1_GREATER_THAN_PARAM_2_ERR       -> version2Ptr is greater than version2Ptr.
 *          TOMMRO_C_NULL_PARAM_ERR                                 -> NULL param error.
 *          TOMMRO_C_PARAM_ERR                                      -> param error.
 */
tommRoC_err_enum_t tommRoCVersionCompare(
        const   tommRoC_version_t*  const   version1Ptr,
        const   tommRoC_version_t*  const   version2Ptr);

/**
 * Compares two versions (excluding project name string).
 *
 * param[in]        version1Ptr             first version pointer.
 * param[in]        version2Ptr             second version pointer.
 *
 * return tommRoC_err_enum_t
 *          TOMMRO_C_ERR_SUCCESS                                    -> compare success (versions are matching).
 *          TOMMRO_C_COMPARE_PARAM_1_LOWER_THAN_PARAM_2_ERR         -> version version1Ptr is lower than version2Ptr.
 *          TOMMRO_C_COMPARE_PARAM_1_GREATER_THAN_PARAM_2_ERR       -> version2Ptr is greater than version2Ptr.
 *          TOMMRO_C_NULL_PARAM_ERR                                 -> NULL param error.
 *          TOMMRO_C_PARAM_ERR                                      -> param error.
 */
tommRoC_err_enum_t tommRoCVersionCompareNameExclude(
        const   tommRoC_version_t*  const   version1Ptr,
        const   tommRoC_version_t*  const   version2Ptr);

/**
 * @}
 */

#endif
