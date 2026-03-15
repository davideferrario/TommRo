
#ifndef TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_H_
#define TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_H_

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

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// The default Modbus comm slave TCP port (502)
#define TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_TCP_PORT_DEFAULT  (502)

// Use the default Modbus comm slave TCP port (502)
#define TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_TCP_INIT_PORT_USE_DEFAULT (0)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * If register should be written or read.
 *
 * NOTE:
 * This value is passed to the callback functions which support either reading or writing register values.
 * Writing means that the application registers should be updated.
 * Reading means that the modbus protocol stack needs to know the current register values.
 */
typedef enum {

    TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_REG_READ = 0, // Read register values and pass to protocol stack
    TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_REG_WRITE,    // Update register values

} tommRoC_hw_protocol_modbus_comm_slave_register_mode_enum_t;

/**
 * Error codes used by modbus callback functions.
 */
typedef enum {

    TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_ENOERR = 0,   // No error
    TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_ENOREG,       // Illegal register address
    TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_EINVAL,       // Illegal argument
    TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_EPORTERR,     // Porting layer error
    TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_ENORES,       // Insufficient resources
    TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_EIO,          // I/O error
    TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_EILLSTATE,    // Protocol stack in illegal state
    TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_ETIMEDOUT,    // Timeout error occurred

} tommRoC_hw_protocol_modbus_comm_slave_error_code_enum_t;


// tommRoC hardware layer protocol modbus comm slave callback functions type definition.

/**
 * Callback function used by the protocol stack to get the value of "Input Registers".
 * The starting register address is given by regStartAdd parameter.
 * The last register is given by regAmount + regAmount - 1.
 *
 * param[out]       regBufferPtr            buffer where the callback should write current values of the modbus registers.
 * param[in]        regStartAdd             starting address of the register. Input registers are in the range 1 - 65535.
 * param[in]        regAmount               number of registers the callback function must handle.
 *
 * return tommRoC_hw_protocol_modbus_comm_slave_error_code_enum_t
 */
typedef tommRoC_hw_protocol_modbus_comm_slave_error_code_enum_t (*tommRoC_hw_protocol_modbus_comm_slave_reg_input_funct_t)(
                uint8_t*                                            const   regBufferPtr,
        const   uint16_t                                                    regStartAdd,
        const   uint16_t                                                    regAmount);

/**
 * Callback function used by the protocol stack to read/write the value of "Holding Register".
 * The starting register address is given by regStartAdd parameter.
 * The last register is given by regAmount + regAmount - 1.
 *
 * param[in/out]    regBufferPtr            buffer where the callback should read/write current values of the modbus registers.
 * param[in]        regStartAdd             starting address of the register. Input registers are in the range 1 - 65535.
 * param[in]        regAmount               number of registers the callback function must handle.
 * param[in]        regMode                 read or write mode.
 *                                          TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_REG_READ   the application should copy the current values into the buffer.
 *                                          TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_REG_WRITE  the application register register values should be updated from the values in the buffer.
 *
 * return tommRoC_hw_protocol_modbus_comm_slave_error_code_enum_t
 */
typedef tommRoC_hw_protocol_modbus_comm_slave_error_code_enum_t (*tommRoC_hw_protocol_modbus_comm_slave_reg_holding_funct_t)(
                uint8_t*                                            const   regBufferPtr,
        const   uint16_t                                                    regStartAdd,
        const   uint16_t                                                    regAmount,
        const   tommRoC_hw_protocol_modbus_comm_slave_register_mode_enum_t  regMode);

/**
 * Callback function used by the protocol stack to read/write the value of "Coil Register".
 *
 * param[in/out]    coilBufferPtr           bits are packed in bytes where the first coil starting at address coilStartNum is stored in the LSB of the first byte in the buffer.
 *                                          If the buffer should be written by the callback function, unused coil values (I.e. if not a multiple of eight coils is used) should be set to zero.
 * param[in]        coilStartNum            the first coil number.
 * param[in]        coilAmount              number of coil values requested.
 * param[in]        regMode                 read or write mode.
 *                                          TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_REG_READ   the application should store the current values in the buffer.
 *                                          TOMMROC_HW_PROTOCOL_MODBUS_COMM_SLAVE_REG_WRITE  the application values should be updated from the values supplied in the buffer.
 *
 * return tommRoC_hw_protocol_modbus_comm_slave_error_code_enum_t
 */
typedef tommRoC_hw_protocol_modbus_comm_slave_error_code_enum_t (*tommRoC_hw_protocol_modbus_comm_slave_reg_coils_funct_t)(
                uint8_t*                                            const   coilBufferPtr,
        const   uint16_t                                                    coilStartNum,
        const   uint16_t                                                    coilAmount,
        const   tommRoC_hw_protocol_modbus_comm_slave_register_mode_enum_t  regMode);

/**
 * Callback function used by the protocol stack to get the value of "Input Discrete Register".
 *
 * param[out]       discreteBufferPtr       buffer where the callback should write current values of the modbus registers.
 * param[in]        discreteStartAdd        starting address of the first discrete input.
 * param[in]        discreteAmount          number of discrete input values.
 *
 * return tommRoC_hw_protocol_modbus_comm_slave_error_code_enum_t
 */
typedef tommRoC_hw_protocol_modbus_comm_slave_error_code_enum_t (*tommRoC_hw_protocol_modbus_comm_slave_reg_discrete_funct_t)(
                uint8_t*                                        const   discreteBufferPtr,
        const   uint16_t                                                discreteStartAdd,
        const   uint16_t                                                discreteAmount);

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Set the guard for Modbus comm slave protocol stack.
 * NOTE: call this before the RTU and/or TCP init function.
 *
 * param[in]        guardPtr                guard pointer (NULL if not used).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwProtocolModbusCommSlaveSetGuard(const tommRoC_guard_t* const guardPtr);

/**
 * Set the callbacks for Modbus comm slave protocol stack.
 * NOTE: call this before the RTU and/or TCP init function.
 *
 * param[in]        regInputCb              register input callback function pointer (NULL if none).
 * param[in]        regHoldingCb            register holding callback function pointer (NULL if none).
 * param[in]        regCoilsCb              register coils callback function pointer (NULL if none).
 * param[in]        regDiscreteCb           register discrete callback function pointer (NULL if none).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwProtocolModbusCommSlaveSetCb(
        const   tommRoC_hw_protocol_modbus_comm_slave_reg_input_funct_t     regInputCb,
        const   tommRoC_hw_protocol_modbus_comm_slave_reg_holding_funct_t   regHoldingCb,
        const   tommRoC_hw_protocol_modbus_comm_slave_reg_coils_funct_t     regCoilsCb,
        const   tommRoC_hw_protocol_modbus_comm_slave_reg_discrete_funct_t  regDiscreteCb);

/**
 * Initialize the RTU Modbus comm slave protocol stack.
 * NOTE: this function initializes the RTU module. The receiver is still disabled; no frames are processed until the enable function has been called.
 *
 * param[in]        ucSlaveAddress          Modbus RTU slave address. Only frames sent to this address or to the broadcast address are processed.
 * param[in]        busHandlerPtr           RTU (uart) bus pointer.
 * param[in]        baudRate                RTU (uart) bus baudrate. NOTE: it is used to calculate character timer reload timeout.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwProtocolModbusCommSlaveRTUInit(
        const   uint8_t                                                 ucSlaveAddress,
        const   tommRoC_hw_bus_t*                               const   busHandlerPtr,
        const   uint32_t                                                baudRate);

/**
 * Initialize the Modbus comm slave protocol stack for Modbus TCP.
 * NOTE: this function initializes the Modbus TCP Module. Frame processing is still disabled; no frames are processed until the enable function has been called.
 *
 * param[in]        tcpPort                 TCP port to listen on (0 -> use default: 502).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwProtocolModbusCommSlaveTCPInit(
        const   uint16_t                                                tcpPort);

/**
 * Close the Modbus comm slave protocol stack.
 * NOTE: release resources used by the protocol stack. It must only be called when the protocol stack is disabled.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwProtocolModbusCommSlaveClose(void);

/**
 * Enable the Modbus comm slave protocol stack.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwProtocolModbusCommSlaveEnable(void);

/**
 * Disable the Modbus comm slave protocol stack.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwProtocolModbusCommSlaveDisable(void);

/**
 * Main pooling loop of the Modbus comm slave protocol stack.
 * NOTE: this function must be called periodically.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwProtocolModbusCommSlavePoll(void);

#endif
