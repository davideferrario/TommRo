
#ifndef TOMMROC_MW_ERR_H_
#define TOMMROC_MW_ERR_H_

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
#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * Function result check call and return.
 */
#define TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(funct, errCodeRet)                        \
        TOMMROC_ERR_IF_FUNCT_RESULT_NOT_VALID_RETURN_SPECIFIC_RESULT(tommRoC_mw_err_enum_t, funct, TOMMRO_C_MW_ERR_SUCCESS, errCodeRet)

#define TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_CALL_AND_RETURN_SPECIFIC_RESULT(funct, callFunct, errCodeRet)    \
        TOMMROC_ERR_IF_FUNCT_RESULT_NOT_VALID_CALL_AND_RETURN_SPECIFIC_RESULT(tommRoC_mw_err_enum_t, funct, callFunct, TOMMRO_C_MW_ERR_SUCCESS, errCodeRet)

#define TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(funct)                                             \
        TOMMROC_ERR_IF_FUNCT_RESULT_NOT_VALID_RETURN_RESULT(tommRoC_mw_err_enum_t, funct, TOMMRO_C_MW_ERR_SUCCESS)

#define TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_CALL_AND_RETURN_RESULT(funct, callFunct)                         \
        TOMMROC_ERR_IF_FUNCT_RESULT_NOT_VALID_CALL_AND_RETURN_RESULT(tommRoC_mw_err_enum_t, funct, callFunct, TOMMRO_C_MW_ERR_SUCCESS)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC middleware functions common error codes.
typedef enum {

    /**
     * **************************** Commons error codes.
     */

    /**
     * Success.
     */
    TOMMRO_C_MW_ERR_SUCCESS = 0,

    /**
     * Null input param error.
     */
    TOMMRO_C_MW_NULL_PARAM_ERR,

    /**
     * Generic input param error.
     */
    TOMMRO_C_MW_PARAM_ERR,

    /**
     * Low level error.
     */
    TOMMRO_C_MW_LOW_LEVEL_ERR,

    /**
     * Low level environment not correctly init.
     */
    TOMMRO_C_MW_ENVIRONMENT_NOT_INIT_ERR,

    /**
     * Low level functionality not available.
     */
    TOMMRO_C_MW_NOT_AVAILABLE_ERR,

    /**
     * Timeout error.
     */
    TOMMRO_C_MW_TIMEOUT_ERR,

    /**
     * Not enough resource error.
     */
    TOMMRO_C_MW_NOT_ENOUGH_RESOURCE_ERR,

    /**
     * Generic error.
     */
    TOMMRO_C_MW_GENERIC_ERR,

    /**
     * Data not available.
     */
    TOMMRO_C_MW_DATA_NOT_AVAILABLE_ERR,


    /**
     * **************************** Disk specific error codes.
     */

    /**
     * Specific disk generic error.
     */
    TOMMRO_C_MW_DISK_GENERIC_ERR,

    /**
     * Specific disk file/folder exists error.
     */
    TOMMRO_C_MW_DISK_FILE_EXISTS_ERR,

    /**
     * Specific disk permission denied error.
     */
    TOMMRO_C_MW_DISK_PERMISSION_DENIED_ERR,


    /**
     * **************************** File specific error codes.
     */

    /**
     * Specific file generic error.
     */
    TOMMRO_C_MW_FILE_GENERIC_ERR,

    /**
     * Specific file open NULL stream error.
     */
    TOMMRO_C_MW_FILE_OPEN_NULL_STREAM_ERR,

    /**
     * Specific file write error.
     */
    TOMMRO_C_MW_FILE_WRITE_ERR,

    /**
     * Specific file read end-of-file error.
     */
    TOMMRO_C_MW_FILE_READ_EOF_ERR,

    /**
     * Specific file read not enough data error.
     */
    TOMMRO_C_MW_FILE_READ_NOT_ENOUGH_DATA_ERR,

} tommRoC_mw_err_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
