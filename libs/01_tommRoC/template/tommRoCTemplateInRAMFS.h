
#ifndef TOMMROC_TEMPLATE_IN_RAM_FS_H_
#define TOMMROC_TEMPLATE_IN_RAM_FS_H_

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

/**
 *  - __TOMMROC_USE_IN_RAM_FS_TEMPLATE__                                    in RAM file system
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateInRAMFSStart(
                void*                               const   RAMBufferPtr,
        const   uint32_t                                    RAMBufferSize,
        const   uint32_t                                    RAMBufferErasableBlockSize,
        const   tommRoC_guard_t*                    const   guardPtr,
                tommRoC_fs_file_system_t*           const   fsHandlePtr);

tommRoC_err_enum_t tommRoCTemplateInRAMFSClose(
                tommRoC_fs_file_system_t*           const   fsHandlePtr);

#endif
