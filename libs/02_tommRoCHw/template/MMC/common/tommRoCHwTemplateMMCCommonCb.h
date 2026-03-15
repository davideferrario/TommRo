
#ifndef TOMMROC_HW_TEMPLATE_MMC_COMMON_CB_H_
#define TOMMROC_HW_TEMPLATE_MMC_COMMON_CB_H_

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
#include "TOMMROCHw.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_mmc_common_cb_phy_write_buffer_t) (
                void*       const   MMCConfigPtr,
                void*       const   MMCHandlePtr,
        const   uint32_t            logicalAddStart,
        const   void*       const   writeBufferPtr,
        const   uint32_t            writeBufferLen,
                uint32_t*   const   writtenLenPtr,
        const   uint32_t            timeoutPerByteMsec);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_mmc_common_cb_phy_read_buffer_t) (
                void*       const   MMCConfigPtr,
                void*       const   MMCHandlePtr,
        const   uint32_t            logicalAddStart,
                void*       const   readBufferPtr,
        const   uint32_t            readBufferLen,
                uint32_t*   const   readedLenPtr,
        const   uint32_t            timeoutPerByteMsec);

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateMMCCommonCbWriteBuffer(
        const   uint32_t            logicalAddStart,
        const   void*       const   writeBufferPtr,
        const   uint32_t            writeBufferLen,
                uint32_t*   const   writtenLenPtr,
                void*       const   MMCConfigPtr,
                void*       const   MMCHandlePtr,
                tommRoC_hw_template_mmc_common_cb_phy_write_buffer_t phyWriteBuffer);

tommRoC_hw_err_enum_t tommRoCHwTemplateMMCCommonCbReadBuffer(
        const   uint32_t            logicalAddStart,
                void*       const   readBufferPtr,
        const   uint32_t            readBufferLen,
                uint32_t*   const   readedLenPtr,
                void*       const   MMCConfigPtr,
                void*       const   MMCHandlePtr,
                tommRoC_hw_template_mmc_common_cb_phy_read_buffer_t phyReadBuffer);

#endif
