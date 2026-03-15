
#ifndef TOMMROC_STDIO_H_
#define TOMMROC_STDIO_H_

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
 * @defgroup tommRoCSTDIO tommRoCSTDIO
 *
 * @brief  TommRoC library stdio module
 * @author TommRo Software Department
 *
 * This module is providing stdio functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCEnv.h"

/*******************************************************************************
 * defines
 ******************************************************************************/
#if defined (TOMMRO_C_ENV_VA_ARGS_SUPPORTED_BY_COMPILER)

#include <stdarg.h>
#include <stddef.h>
#else

#include <stdio.h>

#define tommRoCSTDIOPrintfD     printf
#define tommRoCSTDIOPrintfE     printf
#define tommRoCSTDIOPrintfI     printf
#define tommRoCSTDIOPrintfV     printf
#define tommRoCSTDIOPrintfW     printf
#define tommRoCSTDIOSPrintf     sprintf
#define tommRoCSTDIOSNPrintf    snprintf
#define tommRoCSTDIOVSNPrintf   vsnprintf
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (TOMMRO_C_ENV_VA_ARGS_SUPPORTED_BY_COMPILER)
int tommRoCSTDIOPrintfD(const char* format, ...);
int tommRoCSTDIOPrintfE(const char* format, ...);
int tommRoCSTDIOPrintfI(const char* format, ...);
int tommRoCSTDIOPrintfV(const char* format, ...);
int tommRoCSTDIOPrintfW(const char* format, ...);
int tommRoCSTDIOSPrintf(char* buffer, const char* format, ...);
int tommRoCSTDIOSNPrintf(char* buffer, size_t count, const char* format, ...);
int tommRoCSTDIOVSNPrintf(char* buffer, size_t count, const char* format, va_list va);
#endif

/**
 * @}
 */

#endif
