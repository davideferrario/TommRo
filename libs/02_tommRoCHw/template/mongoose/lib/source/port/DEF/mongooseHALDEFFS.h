
#ifndef TOMMROC_HW_TEMPLATE_MONGOOSE_HAL_DEF_FS_H_
#define TOMMROC_HW_TEMPLATE_MONGOOSE_HAL_DEF_FS_H_

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
#include <stdbool.h>
#include <stddef.h>

/*******************************************************************************
 * defines
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_MONGOOSE_FAT_FS_FILE_TEMPLATE__)
#if !defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)
#error "mongoose FAT FS file template need FAT FS template"
#endif
#if defined (TOMMROC_HW_TEMPLATE_MONGOOSE_HAL_DEF_FS_IS_USED)
#error "only one mongoose FS template MUST be defined"
#endif
#define TOMMROC_HW_TEMPLATE_MONGOOSE_HAL_DEF_FS_IS_USED
#endif

#if defined (__TOMMROC_HW_USE_MONGOOSE_TOMMROC_FS_MBED_FILE_TEMPLATE__)
#if defined (TOMMROC_HW_TEMPLATE_MONGOOSE_HAL_DEF_FS_IS_USED)
#error "only one mongoose FS template MUST be defined"
#endif
#define TOMMROC_HW_TEMPLATE_MONGOOSE_HAL_DEF_FS_IS_USED
#endif

#if defined (__TOMMROC_HW_USE_MONGOOSE_CUSTOM_FILE_TEMPLATE__)
#if defined (TOMMROC_HW_TEMPLATE_MONGOOSE_HAL_DEF_FS_IS_USED)
#error "only one mongoose FS template MUST be defined"
#endif
#define TOMMROC_HW_TEMPLATE_MONGOOSE_HAL_DEF_FS_IS_USED
#endif

#if defined (TOMMROC_HW_TEMPLATE_MONGOOSE_HAL_DEF_FS_IS_USED) && !defined (__TOMMROC_HW_USE_MONGOOSE_TEMPLATE__)
#error "mongoose FS template NEED mongoose template"
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
