
#ifndef TOMMROC_HW_TEMPLATE_BUS_COMMON_SPI_MASTER_CB_H_
#define TOMMROC_HW_TEMPLATE_BUS_COMMON_SPI_MASTER_CB_H_

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
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_bus_common_spi_master_cb_phy_write_buffers_t) (
                void*                       const   spiConfigPtr,
                void*                       const   spiHandlePtr,
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   uint32_t                            timeoutPerByteMsec);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_bus_common_spi_master_cb_phy_read_buffers_t) (
                void*                       const   spiConfigPtr,
                void*                       const   spiHandlePtr,
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   uint32_t                            timeoutPerByteMsec);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_bus_common_spi_master_cb_phy_write_read_buffer_t) (
                void*                       const   spiConfigPtr,
                void*                       const   spiHandlePtr,
        const   uint8_t*                    const   writeBufferPtr,
        const   uint16_t                            writeBufferLen,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            toReadAmount,
        const   uint32_t                            delayWriteToReadMsec,
        const   uint32_t                            timeoutPerByteMsec);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_bus_common_spi_master_cb_phy_transceive_buffer_t) (
                void*                       const   spiConfigPtr,
                void*                       const   spiHandlePtr,
        const   uint8_t*                    const   writeBufferPtr,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            bufferLength,
        const   uint32_t                            timeoutPerByteMsec);

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonSPIMasterCbWriteBuffers(
        const   tommRoC_hw_bus_write_buf_t*                 const   writeBuffersPtr,
        const   uint8_t                                             writeBuffersAmount,
                void*                                       const   spiConfigPtr,
                void*                                       const   spiHandlePtr,
                tommRoC_hw_template_bus_common_spi_master_cb_phy_write_buffers_t phyWriteBuffers);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonSPIMasterCbReadBuffers(
                tommRoC_hw_bus_read_buf_t*                  const   readBuffersPtr,
        const   uint8_t                                             readBuffersAmount,
                void*                                       const   spiConfigPtr,
                void*                                       const   spiHandlePtr,
                tommRoC_hw_template_bus_common_spi_master_cb_phy_read_buffers_t phyReadBuffers);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonSPIMasterCbWriteReadBuffer(
        const   uint8_t*                                    const   writeBufferPtr,
        const   uint16_t                                            writeBufferLen,
                uint8_t*                                    const   readBufferPtr,
        const   uint16_t                                            toReadAmount,
                uint16_t*                                   const   readedAmountPtr,
        const   uint32_t                                            delayWriteToReadMsec,
                void*                                       const   spiConfigPtr,
                void*                                       const   spiHandlePtr,
                tommRoC_hw_template_bus_common_spi_master_cb_phy_write_read_buffer_t phyWriteReadBuffer);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonSPIMasterCbTransceiveBuffer(
        const   uint8_t*                                    const   writeBufferPtr,
                uint8_t*                                    const   readBufferPtr,
        const   uint16_t                                            bufferLength,
                void*                                       const   spiConfigPtr,
                void*                                       const   spiHandlePtr,
                tommRoC_hw_template_bus_common_spi_master_cb_phy_transceive_buffer_t phyTransceiveBuffer);

#endif
