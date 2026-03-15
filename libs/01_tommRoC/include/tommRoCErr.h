
#ifndef TOMMROC_ERR_H_
#define TOMMROC_ERR_H_

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
 * @defgroup tommRoCErr tommRoCErr
 *
 * @brief  TommRoC library error module
 * @author TommRo Software Department
 *
 * This module is providing error define and functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * Function result check call and return.
 */
#define TOMMROC_ERR_IF_FUNCT_RESULT_NOT_VALID_RETURN_SPECIFIC_RESULT(resType, funct, validRes, errCodeRet)                      \
        do {                                                                                                                    \
            resType __res__;                                                                                                    \
            __res__ = funct;                                                                                                    \
                                                                                                                                \
            if ((validRes) != (__res__)) {                                                                                      \
                return (errCodeRet);                                                                                            \
            }                                                                                                                   \
        } while (0)

#define TOMMROC_ERR_IF_FUNCT_RESULT_NOT_VALID_CALL_AND_RETURN_SPECIFIC_RESULT(resType, funct, callFunct, validRes, errCodeRet)  \
        do {                                                                                                                    \
            resType __res__;                                                                                                    \
            __res__ = funct;                                                                                                    \
                                                                                                                                \
            if ((validRes) != (__res__)) {                                                                                      \
                do { callFunct; } while (0);                                                                                    \
                return (errCodeRet);                                                                                            \
            }                                                                                                                   \
        } while (0)

#define TOMMROC_ERR_IF_FUNCT_RESULT_NOT_VALID_RETURN_RESULT(resType, funct, validRes)                                           \
        do {                                                                                                                    \
            resType __res__;                                                                                                    \
            __res__ = funct;                                                                                                    \
                                                                                                                                \
            if ((validRes) != (__res__)) {                                                                                      \
                return (__res__);                                                                                               \
            }                                                                                                                   \
        } while (0)

#define TOMMROC_ERR_IF_FUNCT_RESULT_NOT_VALID_CALL_AND_RETURN_RESULT(resType, funct, callFunct, validRes)                       \
        do {                                                                                                                    \
            resType __res__;                                                                                                    \
            __res__ = funct;                                                                                                    \
                                                                                                                                \
            if ((validRes) != (__res__)) {                                                                                      \
                do { callFunct; } while (0);                                                                                    \
                return (__res__);                                                                                               \
            }                                                                                                                   \
        } while (0)

#define TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(funct, errCodeRet)                      \
        TOMMROC_ERR_IF_FUNCT_RESULT_NOT_VALID_RETURN_SPECIFIC_RESULT(tommRoC_err_enum_t, funct, TOMMRO_C_ERR_SUCCESS, errCodeRet)

#define TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_CALL_AND_RETURN_SPECIFIC_RESULT(funct, callFunct, errCodeRet)  \
        TOMMROC_ERR_IF_FUNCT_RESULT_NOT_VALID_CALL_AND_RETURN_SPECIFIC_RESULT(tommRoC_err_enum_t, funct, callFunct, TOMMRO_C_ERR_SUCCESS, errCodeRet)

#define TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(funct)                                           \
        TOMMROC_ERR_IF_FUNCT_RESULT_NOT_VALID_RETURN_RESULT(tommRoC_err_enum_t, funct, TOMMRO_C_ERR_SUCCESS)

#define TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_CALL_AND_RETURN_RESULT(funct, callFunct)                       \
        TOMMROC_ERR_IF_FUNCT_RESULT_NOT_VALID_CALL_AND_RETURN_RESULT(tommRoC_err_enum_t, funct, callFunct, TOMMRO_C_ERR_SUCCESS)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC functions common error codes.
typedef enum {

    /**
     * **************************** Commons error codes.
     */

    /**
     * Success.
     */
    TOMMRO_C_ERR_SUCCESS = 0,

    /**
     * Null input param error.
     */
    TOMMRO_C_NULL_PARAM_ERR,

    /**
     * Generic input param error.
     */
    TOMMRO_C_PARAM_ERR,

    /**
     * Low level error.
     */
    TOMMRO_C_LOW_LEVEL_ERR,

    /**
     * Low level environment not correctly init.
     */
    TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR,

    /**
     * Empty resource error.
     */
    TOMMRO_C_IS_EMPTY_ERR,

    /**
     * Not enough resource error.
     */
    TOMMRO_C_NOT_ENOUGH_RESOURCE_ERR,

    /**
     * Not found error.
     */
    TOMMRO_C_NOT_FOUND_ERR,

    /**
     * Timeout expired.
     */
    TOMMRO_C_TIMEOUT_ERR,

    /**
     * Generic error.
     */
    TOMMRO_C_GENERIC_ERR,

    /**
     * **************************** Guard specific error codes.
     */

    /**
     * Guard already locked (it's not possible to execute UnLock).
     */
    TOMMRO_C_GUARD_ALREADY_LOCKED_ERR,

    /**
     * Guard not locked (it's not possible to execute UnLock).
     */
    TOMMRO_C_GUARD_NOT_LOCKED_ERR,


    /**
     * **************************** Timer specific error codes.
     */

    /**
     * Timer not start.
     */
    TOMMRO_C_TIMER_NOT_START_ERR,

    /**
     * Timer not expired.
     */
    TOMMRO_C_TIMER_NOT_EXPIRED_ERR,

    /**
     * Timer expired.
     */
    TOMMRO_C_TIMER_EXPIRED_ERR,


    /**
     * **************************** Compare specific error codes.
     */

    /**
     * Parameter 1 has a lower value than in parameter 2.
     */
    TOMMRO_C_COMPARE_PARAM_1_LOWER_THAN_PARAM_2_ERR,

    /**
     * Parameter 1 has a greater value than in parameter 2.
     */
    TOMMRO_C_COMPARE_PARAM_1_GREATER_THAN_PARAM_2_ERR,

    /**
     * Not compatible parameters.
     */
    TOMMRO_C_COMPARE_NOT_COMPATIBLE_PARAMS,


    /**
     * **************************** Protocol encode specific error codes.
     */

    /**
     * Encode in progress.
     */
    TOMMRO_C_ENCODE_IN_PROGRESS_ERR,

    /**
     * Encode generic error.
     */
    TOMMRO_C_ENCODE_GENERIC_ERR,

    /**
     * Encode panic error.
     * NOTE: to be used only for critical error.
     */
    TOMMRO_C_ENCODE_PANIC_ERR,


    /**
     * **************************** Protocol decode specific error codes.
     */

    /**
     * Decode in progress.
     */
    TOMMRO_C_DECODE_IN_PROGRESS_ERR,

    /**
     * Decode first byte error.
     */
    TOMMRO_C_DECODE_1ST_BYTE_ERR,

    /**
     * Decode n-th byte error.
     */
    TOMMRO_C_DECODE_nTH_BYTE_ERR,

    /**
     * Decode length byte error.
     */
    TOMMRO_C_DECODE_LENGTH_ERR,

    /**
     * Decode CRC byte error.
     */
    TOMMRO_C_DECODE_CRC_ERR,

    /**
     * Decode generic error.
     */
    TOMMRO_C_DECODE_GENERIC_ERR,

    /**
     * Decode panic error.
     * NOTE: to be used only for critical error.
     */
    TOMMRO_C_DECODE_PANIC_ERR,

} tommRoC_err_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * @}
 */

#endif
