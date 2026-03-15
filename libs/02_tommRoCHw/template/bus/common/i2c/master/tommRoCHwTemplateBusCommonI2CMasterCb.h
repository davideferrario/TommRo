
#ifndef TOMMROC_HW_TEMPLATE_BUS_COMMON_I2C_MASTER_CB_H_
#define TOMMROC_HW_TEMPLATE_BUS_COMMON_I2C_MASTER_CB_H_

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
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_bus_common_i2c_master_cb_phy_write_buffers_t) (
                void*                       const   i2cConfigPtr,
                void*                       const   i2cHandlePtr,
        const   uint8_t                             slaveAddress7Bit,
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   uint32_t                            timeoutPerByteMsec);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_bus_common_i2c_master_cb_phy_read_buffers_t) (
                void*                       const   i2cConfigPtr,
                void*                       const   i2cHandlePtr,
        const   uint8_t                             slaveAddress7Bit,
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   uint32_t                            timeoutPerByteMsec);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_bus_common_i2c_master_cb_phy_write_read_buffer_t) (
                void*                       const   i2cConfigPtr,
                void*                       const   i2cHandlePtr,
        const   uint8_t                             slaveAddress7Bit,
        const   uint8_t*                    const   writeBufferPtr,
        const   uint16_t                            writeBufferLen,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            toReadAmount,
        const   uint32_t                            delayWriteToReadMsec,
        const   uint32_t                            timeoutPerByteMsec);

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonI2CMasterCbWriteBuffers(
        const   tommRoC_hw_bus_write_buf_t*                 const   writeBuffersPtr,
        const   uint8_t                                             writeBuffersAmount,
        const   tommRoC_hw_bus_device_specific_i2c_slave_t* const   specificI2CSlavePtr,
                void*                                       const   i2cConfigPtr,
                void*                                       const   i2cHandlePtr,
                tommRoC_hw_template_bus_common_i2c_master_cb_phy_write_buffers_t phyWriteBuffers);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonI2CMasterCbReadBuffers(
                tommRoC_hw_bus_read_buf_t*                  const   readBuffersPtr,
        const   uint8_t                                             readBuffersAmount,
        const   tommRoC_hw_bus_device_specific_i2c_slave_t* const   specificI2CSlavePtr,
                void*                                       const   i2cConfigPtr,
                void*                                       const   i2cHandlePtr,
                tommRoC_hw_template_bus_common_i2c_master_cb_phy_read_buffers_t phyReadBuffers);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonI2CMasterCbWriteReadBuffer(
        const   uint8_t*                                    const   writeBufferPtr,
        const   uint16_t                                            writeBufferLen,
                uint8_t*                                    const   readBufferPtr,
        const   uint16_t                                            toReadAmount,
                uint16_t*                                   const   readedAmountPtr,
        const   uint32_t                                            delayWriteToReadMsec,
        const   tommRoC_hw_bus_device_specific_i2c_slave_t* const   specificI2CSlavePtr,
                void*                                       const   i2cConfigPtr,
                void*                                       const   i2cHandlePtr,
                tommRoC_hw_template_bus_common_i2c_master_cb_phy_write_read_buffer_t phyWriteReadBuffer);

#endif
