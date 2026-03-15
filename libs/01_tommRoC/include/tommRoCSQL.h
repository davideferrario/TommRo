
#ifndef TOMMROC_SQL_H_
#define TOMMROC_SQL_H_

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
 * @defgroup tommRoCSQL tommRoCSQL
 *
 * @brief  TommRoC library SQL module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted SQL functionality.
 * Please note that it is based on SQLite (https://www.sqlite.org/index.html) library.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "FSItf/tommRoCFSItfDEF.h"

#include "tommRoCFS.h"
#include "tommRoCErr.h"
#include "tommRoCGuard.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/
#define TOMMROC_SQL_SQLITE_OK   (0)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * tommRoC SQL Database Connection Handle
 */
typedef void* tommRoC_sql_database_t;
#define __EMPTY_tommRoC_sql_database_t__    (NULL)

/**
 * tommRoC SQL result row coming out from evaluated SQL statements callback function.
 *
 * return TOMMROC_SQL_SQLITE_OK in case of success.
 */
typedef int (*tommRoC_sql_result_row_cb_t)(void* opaquePtr, int elemAmount, char** elemValueStrPtr, char** elemDescStrPtr);

/*******************************************************************************
 * functions
 ******************************************************************************/

/******************* SQL framework management functions */

/**
 * Init SQL framework.
 *
 * param[in]        lowLevelFileSize        low level file structure size [byte].
 * param[in]        SQLFSConfigPtr          SQL file system configuration pointer.
 * param[in]        guardPtr                SQL framework guard pointer (set to NULL to disable).
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCSQLInit(
        const   uint32_t                                            lowLevelFileSize,
        const   tommRoC_fs_itf_def_file_system_config_t*    const   SQLFSConfigPtr,
        const   tommRoC_guard_t*                            const   guardPtr);

/**
 * Init SQL framework for a tommRoCFS file system.
 *
 * param[in]        fsHandlePtr             tommRoCFS file system handle pointer.
 * param[in]        guardPtr                SQL framework guard pointer (set to NULL to disable).
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCSQLInitAsFS(
        const   tommRoC_fs_file_system_t*                   const   fsHandlePtr,
        const   tommRoC_guard_t*                            const   guardPtr);

/**
 * Init SQL framework for a tommRoCFSMbed file system.
 *
 * param[in]        guardPtr                SQL framework guard pointer (set to NULL to disable).
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCSQLInitAsFSMbed(
        const   tommRoC_guard_t*                            const   guardPtr);

/**
 * Close SQL framework.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCSQLClose(void);


/******************* SQL framework database functions */

/**
 * Open an SQL database as specified by the database name argument.
 *
 * param[in]        databaseNameStrPtr      database name string pointer.
 * param[in]        flags                   opening flags (OR of TOMMROC_SQL_OPEN_FLAG_x bits).
 * param[out]       databaseHandlePtr       opaque database handle pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCSQLDatabaseOpen(
        const   char*                                       const   databaseNameStrPtr,
        const   uint32_t                                            flags,
                tommRoC_sql_database_t*                     const   databaseHandlePtr);

/**
 * Close an SQL database.
 *
 * param[in/out]    databaseHandle          opaque database handle.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCSQLDatabaseClose(
                tommRoC_sql_database_t                              databaseHandle);

/**
 * Delete an SQL database as specified by the database name argument.
 *
 * param[in]        databaseNameStrPtr      database name string pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCSQLDatabaseDelete(
        const   char*                                       const   databaseNameStrPtr);

/**
 * Run zero or more UTF-8 encoded, semicolon-separate SQL statements.
 *
 * param[in/out]    databaseHandle          opaque database handle.
 * param[in]        SQLCommandStrPtr        SQL command to be evaluated string pointer.
 * param[in]        resultRowCb             result row coming out of the evaluated SQL statements callback function (NULL if none).
 * param[in]        cbOpaquePtr             opaque pointer passed as first parameter to result row callback.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCSQLDatabaseExec(
                tommRoC_sql_database_t                              databaseHandle,
        const   char*                                       const   SQLCommandStrPtr,
        const   tommRoC_sql_result_row_cb_t                         resultRowCb,
                void*                                       const   cbOpaquePtr);

/**
 * @}
 */

#endif
