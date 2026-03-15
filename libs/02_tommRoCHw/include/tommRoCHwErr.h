
#ifndef TOMMROC_HW_ERR_H_
#define TOMMROC_HW_ERR_H_

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
#define TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(funct, errCodeRet)                        \
        TOMMROC_ERR_IF_FUNCT_RESULT_NOT_VALID_RETURN_SPECIFIC_RESULT(tommRoC_hw_err_enum_t, funct, TOMMRO_C_HW_ERR_SUCCESS, errCodeRet)

#define TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_CALL_AND_RETURN_SPECIFIC_RESULT(funct, callFunct, errCodeRet)    \
        TOMMROC_ERR_IF_FUNCT_RESULT_NOT_VALID_CALL_AND_RETURN_SPECIFIC_RESULT(tommRoC_hw_err_enum_t, funct, callFunct, TOMMRO_C_HW_ERR_SUCCESS, errCodeRet)

#define TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(funct)                                             \
        TOMMROC_ERR_IF_FUNCT_RESULT_NOT_VALID_RETURN_RESULT(tommRoC_hw_err_enum_t, funct, TOMMRO_C_HW_ERR_SUCCESS)

#define TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_CALL_AND_RETURN_RESULT(funct, callFunct)                         \
        TOMMROC_ERR_IF_FUNCT_RESULT_NOT_VALID_CALL_AND_RETURN_RESULT(tommRoC_hw_err_enum_t, funct, callFunct, TOMMRO_C_HW_ERR_SUCCESS)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC hardware layer functions common error codes.
typedef enum {

    /**
     * **************************** Commons error codes.
     */

    /**
     * Success.
     */
    TOMMRO_C_HW_ERR_SUCCESS = 0,

    /**
     * Null input param error.
     */
    TOMMRO_C_HW_NULL_PARAM_ERR,

    /**
     * Generic input param error.
     */
    TOMMRO_C_HW_PARAM_ERR,

    /**
     * Low level error.
     */
    TOMMRO_C_HW_LOW_LEVEL_ERR,

    /**
     * Low level environment not correctly init.
     */
    TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR,

    /**
     * Low level functionality not available.
     */
    TOMMRO_C_HW_NOT_AVAILABLE_ERR,

    /**
     * Disconnected.
     */
    TOMMRO_C_HW_DISCONNECTED_ERR,

    /**
     * Timeout expired.
     */
    TOMMRO_C_HW_TIMEOUT_ERR,

    /**
     * Generic error.
     */
    TOMMRO_C_HW_GENERIC_ERR,


    /**
     * **************************** Bus specific error codes.
     */

    /**
     * Bus data not available.
     */
    TOMMRO_C_HW_BUS_DATA_NOT_AVAILABLE_ERR,

    /**
     * Hardware bus operation fails.
     */
    TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR,

    /**
     * **************************** MMC specific error codes.
     */

    /**
     * Hardware MMC operation fails.
     */
    TOMMRO_C_HW_MMC_OPERATION_FAIL_ERR,

    /**
     * **************************** BLE specific error codes.
     */

    /**
     * BLE operation fault cause BLE not connected.
     */
    TOMMRO_C_HW_BLE_NOT_CONNECTED_ERR,

    /**
     * BLE operation fault cause BLE connected.
     */
    TOMMRO_C_HW_BLE_CONNECTED_ERR,
            
    /**
     * BLE information not available.
     */
    TOMMRO_C_HW_BLE_INFO_NOT_AVAILABLE_ERR,

    /**
     * **************************** GPS specific error codes.
     */

    /**
     * GPS decode in progress.
     */
    TOMMRO_C_HW_GPS_DECODE_IN_PROGRESS_ERR,

    /**
     * GPS decode failed.
     */
    TOMMRO_C_HW_GPS_DECODE_FAILED_ERR,

    /**
     * **************************** Net Socket specific error codes.
     */

    TOMMRO_C_HW_NET_SOCKET_PIPE_ERR,
    TOMMRO_C_HW_NET_SOCKET_CONN_RESET_ERR,
    TOMMRO_C_HW_NET_SOCKET_INTR_ERR,

} tommRoC_hw_err_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
