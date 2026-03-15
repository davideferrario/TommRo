
#ifndef TOMMROC_HW_PROTOCOL_MODBUS_COMM_MASTER_H_
#define TOMMROC_HW_PROTOCOL_MODBUS_COMM_MASTER_H_

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
#include "tommRoCHwBus.h"
#include "tommRoCHwErr.h"

#include "TOMMROC.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// tommRoC hardware protocol modbus comm master.
#define TOMMROC_HW_PROTOCOL_MODBUS_COMM_MASTER_TX_BUFFER_SIZE_BYTE  (254)
#define TOMMROC_HW_PROTOCOL_MODBUS_COMM_MASTER_RX_BUFFER_SIZE_BYTE  (254)

#define TOMMROC_HW_PROTOCOL_MODBUS_COMM_MASTER_HANDLE_SIZE          (   TOMMROC_UTIL_PTR_SIZE                                       +   \
                                                                        TOMMROC_UTIL_U32_SIZE                                       +   \
                                                                        TOMMROC_UTIL_U32_SIZE                                       +   \
                                                                        TOMMROC_UTIL_BOOL_SIZE                                      +   \
                                                                        TOMMROC_HW_PROTOCOL_MODBUS_COMM_MASTER_TX_BUFFER_SIZE_BYTE  +   \
                                                                        TOMMROC_HW_PROTOCOL_MODBUS_COMM_MASTER_RX_BUFFER_SIZE_BYTE  +   \
                                                                        TOMMROC_UTIL_PTR_SIZE                                           )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC hardware protocol modbus comm master.
typedef struct {
    uint8_t data[TOMMROC_HW_PROTOCOL_MODBUS_COMM_MASTER_HANDLE_SIZE];
} tommRoC_hw_protocol_modbus_comm_master_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Initialize the RTU Modbus comm master protocol stack.
 *
 * param[in]        busHandlerPtr           RTU (uart) bus pointer.
 * param[in]        baudRate                RTU (uart) bus baudrate. NOTE: it is used to calculate character timer reload timeout.
 * param[in]        recvTimeoutMsec         wait for reply timeout [msec].
 * param[in]        isWithEcho              is with echo flag.
 * param[in]        guardPtr                RTU Modbus comm master guard pointer (set to NULL to disable).
 * param[out]       modbusCommMasterPtr     RTU Modbus comm master handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwProtocolModbusCommMasterRTUInit(
        const   tommRoC_hw_bus_t*                           const   busHandlerPtr,
        const   uint32_t                                            baudRate,
        const   uint32_t                                            recvTimeoutMsec,
        const   bool                                                isWithEcho,
        const   tommRoC_guard_t*                            const   guardPtr,
                tommRoC_hw_protocol_modbus_comm_master_t*   const   modbusCommMasterPtr);

/**
 * Close the Modbus comm master protocol stack.
 *
 * param[in/out]    modbusCommMasterPtr     RTU Modbus comm master handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwProtocolModbusCommMasterClose(
                tommRoC_hw_protocol_modbus_comm_master_t*   const   modbusCommMasterPtr);

/**
 * Modbus comm master write register operation.
 *
 * param[in/out]    modbusCommMasterPtr     RTU Modbus comm master handle pointer.
 * param[in]        devAddr                 Slave device address.
 * param[in]        regAddr                 Slave register address (in the slave memory).
 * param[in]        data                    Data to be written into slave register.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwProtocolModbusCommMasterWriteRegister(
                tommRoC_hw_protocol_modbus_comm_master_t*   const   modbusCommMasterPtr,
        const   uint8_t                                             devAddr,
        const   uint16_t                                            regAddr,
        const   uint16_t                                            data);

/**
 * Modbus comm master write multiple register operation.
 *
 * param[in/out]    modbusCommMasterPtr     RTU Modbus comm master handle pointer.
 * param[in]        devAddr                 Slave device address.
 * param[in]        regAddr                 Slave register address (in the slave memory).
 * param[in]        dataBufferPtr           Data buffer pointer to be written into slave register.
 * param[in]        regsAmount              Amount of slave registers to be written.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwProtocolModbusCommMasterWriteMultipleRegisters(
                tommRoC_hw_protocol_modbus_comm_master_t*   const   modbusCommMasterPtr,
        const   uint8_t                                             devAddr,
        const   uint16_t                                            regAddr,
        const   uint16_t*                                   const   dataBufferPtr,
        const   uint16_t                                            regsAmount);

/**
 * Modbus comm master read holding register operation.
 *
 * param[in/out]    modbusCommMasterPtr     RTU Modbus comm master handle pointer.
 * param[in]        devAddr                 Slave device address.
 * param[in]        regAddr                 Slave register address (in the slave memory).
 * param[out]       dataBufferPtr           Read data buffer pointer.
 * param[in]        dataBufferSize          Read data buffer size [byte].
 * param[in]        regsAmount              Amount of slave registers to be read.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwProtocolModbusCommMasterReadHoldingRegister(
                tommRoC_hw_protocol_modbus_comm_master_t*   const   modbusCommMasterPtr,
        const   uint8_t                                             devAddr,
        const   uint16_t                                            regAddr,
                uint16_t*                                   const   dataBufferPtr,
        const   uint16_t                                            dataBufferSize,
        const   uint16_t                                            regsAmount);

/**
 * Modbus comm master read input register operation.
 *
 * param[in/out]    modbusCommMasterPtr     RTU Modbus comm master handle pointer.
 * param[in]        devAddr                 Slave device address.
 * param[in]        regAddr                 Slave register address (in the slave memory).
 * param[out]       dataBufferPtr           Read data buffer pointer.
 * param[in]        dataBufferSize          Read data buffer size [byte].
 * param[in]        regsAmount              Amount of slave registers to be read.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwProtocolModbusCommMasterReadInputRegister(
                tommRoC_hw_protocol_modbus_comm_master_t*   const   modbusCommMasterPtr,
        const   uint8_t                                             devAddr,
        const   uint16_t                                            regAddr,
                uint16_t*                                   const   dataBufferPtr,
        const   uint16_t                                            dataBufferSize,
        const   uint16_t                                            regsAmount);

/**
 * Modbus comm master report slave ID operation.
 *
 * param[in]        devAddr                 Slave device address.
 * param[out]       dataBufferPtr           Read data buffer pointer.
 * param[in]        dataBufferSize          Read data buffer size [byte].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwProtocolModbusCommMasterReportSlaveID(
                tommRoC_hw_protocol_modbus_comm_master_t*   const   modbusCommMasterPtr,
        const   uint8_t                                             devAddr,
                uint16_t*                                   const   dataBufferPtr,
        const   uint16_t                                            dataBufferSize);

#endif
