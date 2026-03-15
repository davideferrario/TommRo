
#ifndef TOMMROC_HW_BUS_H_
#define TOMMROC_HW_BUS_H_

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
#include "tommRoCHwErr.h"

#include "comm/tommRoCHwComm.h"

#include "TOMMROC.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC hardware layer bus type.
typedef enum {

    /**
     * UART (RS232/RS485) bus.
     */
    TOMMRO_C_HW_BUS_UART_BUS_TYPE = 0,

    /**
     * I2C master bus.
     */
    TOMMRO_C_HW_BUS_I2C_MASTER_BUS_TYPE,

    /**
     * I2C slave bus.
     */
    TOMMRO_C_HW_BUS_I2C_SLAVE_BUS_TYPE,

    /**
     * SPI master bus.
     */
    TOMMRO_C_HW_BUS_SPI_MASTER_BUS_TYPE,

    /**
     * SPI slave bus.
     */
    TOMMRO_C_HW_BUS_SPI_SLAVE_BUS_TYPE,

    /**
     * Empty bus (used only for variable init).
     */
    TOMMRO_C_HW_BUS_EMPTY_BUS_TYPE,

} tommRoC_hw_bus_type_enum_t;


// Enumeration of tommRoC hardware layer bus functions.
typedef enum {

    /**
     * Check if is available received data.
     */
    TOMMRO_C_HW_BUS_IS_DATA_AVAILABLE = 0,

    /**
     * Get amount of available received data.
     */
    TOMMRO_C_HW_BUS_DATA_READY,

    /**
     * Check if data to transmit are pending.
     */
    TOMMRO_C_HW_BUS_IS_DATA_TO_TX_PENDING,

    /**
     * Get amount of available data to transmit pending.
     */
    TOMMRO_C_HW_BUS_DATA_TO_TX_PENDING_AMOUNT,

    /**
     * Write buffers.
     */
    TOMMRO_C_HW_BUS_WRITE_BUFFERS,

    /**
     * Read buffers.
     */
    TOMMRO_C_HW_BUS_READ_BUFFERS,

    /**
     * Get buffers.
     */
    TOMMRO_C_HW_BUS_GET_BUFFERS,

    /**
     * Write/Read buffer.
     */
    TOMMRO_C_HW_BUS_WRITE_READ_BUFFER,

    /**
     * Transceive (read while writing) buffer.
     * NOTE: valid only for SPI bus.
     */
    TOMMRO_C_HW_BUS_TRANSCEIVE_BUFFER,

    /**
     * Clear to send/received data.
     */
    TOMMRO_C_HW_BUS_CLEAR_DATA,

    /**
     * Clear to send data.
     */
    TOMMRO_C_HW_BUS_CLEAR_TO_SEND_DATA,

    /**
     * Clear received data.
     */
    TOMMRO_C_HW_BUS_CLEAR_RECEIVED_DATA,

    /**
     * Low power enter.
     */
    TOMMRO_C_HW_BUS_LOW_POWER_ENTER,

    /**
     * Low power exit.
     */
    TOMMRO_C_HW_BUS_LOW_POWER_EXIT,

    /**
     * Get property.
     */
    TOMMRO_C_HW_BUS_GET_PROP,

    /**
     * Set property.
     */
    TOMMRO_C_HW_BUS_SET_PROP,

} tommRoC_hw_bus_operations_enum_t;


// Enumeration of tommRoC hardware layer bus properties.
typedef enum {

    /**
     * tommRoC hardware library bus layer properties.
     * NOTE: properties are get/set into tommRoC hardware layer bus.
     */

    /**
     * External implemented bus layer properties.
     * NOTE: properties are get/set into external implementation of layer bus.
     */

    /**
     * Write collision status.
     *
     * Available:   get/set.
     * Notes:       propValuePtr has to be bool*
     */
    TOMMRO_C_HW_BUS_WRITE_COLLISION_OCCURED_PROP = 0,

    /**
     * Baud rate configuration.
     *
     * Available:   get/set.
     * Notes:       propValuePtr has to be uint32_t*
     */
    TOMMRO_C_HW_BUS_UART_BAUD_RATE_PROP,

    /**
     * Hw flow control configuration.
     *
     * Available:   get/set.
     * Notes:       propValuePtr has to be tommRoC_hw_comm_hw_flow_control_enum_t*
     */
    TOMMRO_C_HW_BUS_UART_FLOW_CONTROL_PROP,

    /**
     * Baud rate/hw flow control configuration.
     *
     * Available:   get/set.
     * Notes:       propValuePtr has to be tommRoC_hw_bus_uart_prop_baud_rate_hw_flow_control_t*
     */
    TOMMRO_C_HW_BUS_UART_BAUD_RATE_FLOW_CONTROL_PROP,

} tommRoC_hw_bus_prop_enum_t;

// tommRoC hardware layer bus baud rate/hw flow control structure.
typedef struct {

    uint32_t                                baudRate;
    tommRoC_hw_comm_hw_flow_control_enum_t  hwFlowControl;

} tommRoC_hw_bus_uart_prop_baud_rate_hw_flow_control_t;


// tommRoC hardware layer write buffer structure.
typedef struct {

    uint8_t*    bufferPtr;          // Input data buffer pointer.
    uint16_t    toWriteAmount;      // To write data amount [byte].

} tommRoC_hw_bus_write_buf_t;

// tommRoC hardware layer read buffer structure.
typedef struct {

    uint8_t*    bufferPtr;          // Output data buffer pointer.
    uint16_t    toReadAmount;       // To read data amount [byte].
    uint16_t*   readedAmountPtr;    // Output readed data amount [byte] pointer.

} tommRoC_hw_bus_read_buf_t;


// tommRoC hardware layer bus callback functions type definition.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_bus_is_data_available_funct_t)(
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_bus_data_ready_funct_t)(
                uint16_t*                   const   availableAmountPtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_bus_is_data_to_tx_pending_funct_t)(
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_bus_data_to_tx_pending_amount_funct_t)(
                uint16_t*                   const   availableAmountPtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_bus_write_buffers_funct_t)(
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_bus_read_buffers_funct_t)(
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_bus_get_buffers_funct_t)(
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_bus_write_read_buffer_funct_t)(
        const   uint8_t*                    const   writeBufferPtr,
        const   uint16_t                            writeBufferLen,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            toReadAmount,
                uint16_t*                   const   readedAmountPtr,
        const   uint32_t                            delayWriteToReadMsec,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_bus_transceive_buffer_funct_t)(
        const   uint8_t*                    const   writeBufferPtr,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            bufferLength,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_bus_clear_data_funct_t)(
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_bus_clear_to_send_data_funct_t)(
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_bus_clear_received_data_funct_t)(
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_bus_low_power_enter_funct_t)(
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_bus_low_power_exit_funct_t)(
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_bus_get_prop_funct_t)(
        const   tommRoC_hw_bus_prop_enum_t          property,
                void*                       const   propValuePtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_bus_set_prop_funct_t)(
        const   tommRoC_hw_bus_prop_enum_t          property,
        const   void*                       const   propValuePtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);


// tommRoC hardware layer bus callback functions.
typedef struct {

    /**
     * Each function pointer is specific to particular bus operation.
     * Some functions could be NULL if none/not available in specific bus.
     * Some functions could not be NULL (some specific bus base functions are needed).
     *
     * Every function got specific parameters input/result output pointers plus
     * void* more input/result parameters to be compatible with different bus environment (NULL value IS not checked).
     * Specific cast and check have to be made by software high level.
     */

    tommRoC_hw_bus_is_data_available_funct_t            isDataAvailable;        // Check if are available received data.
    tommRoC_hw_bus_data_ready_funct_t                   dataReady;              // Get amount of available received data.
    tommRoC_hw_bus_is_data_to_tx_pending_funct_t        isDataToTxPending;      // Check if data to transmit are pending.
    tommRoC_hw_bus_data_to_tx_pending_amount_funct_t    dataToTxPendingAmount;  // Get amount of available data to transmit pending.
    tommRoC_hw_bus_write_buffers_funct_t                writeBuffers;           // Write buffers.
    tommRoC_hw_bus_read_buffers_funct_t                 readBuffers;            // Read buffers.
    tommRoC_hw_bus_get_buffers_funct_t                  getBuffers;             // Get buffers.
    tommRoC_hw_bus_write_read_buffer_funct_t            writeReadBuffer;        // Write/Read buffer.
    tommRoC_hw_bus_transceive_buffer_funct_t            transceiveBuffer;       // Transceive buffer.
    tommRoC_hw_bus_clear_data_funct_t                   clearData;              // Clear to send/received data.
    tommRoC_hw_bus_clear_to_send_data_funct_t           clearToSendData;        // Clear to send data.
    tommRoC_hw_bus_clear_received_data_funct_t          clearReceivedData;      // Clear received data.
    tommRoC_hw_bus_low_power_enter_funct_t              lowPowerEnter;          // Low power enter.
    tommRoC_hw_bus_low_power_exit_funct_t               lowPowerExit;           // Low power exit.
    tommRoC_hw_bus_get_prop_funct_t                     getProp;                // Get property.
    tommRoC_hw_bus_set_prop_funct_t                     setProp;                // Set property.

} tommRoC_hw_bus_cb_funct_t;

// tommRoC hardware layer bus.
typedef struct {

    /**
     * Type.
     */
    tommRoC_hw_bus_type_enum_t      busType;

    /**
     * Callback functions structure.
     */
    tommRoC_hw_bus_cb_funct_t*      cbFunctPtr;

} tommRoC_hw_bus_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Reset bus callback functions structure.
 *
 * param[out]       cbFunctPtr              bus callback funct structure.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusCbFunctReset(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr);

/**
 * Init bus.
 *
 * param[in]        type                    bus type.
 * param[in]        cbFunctPtr              bus callback funct structure.
 * param[out]       busPtr                  bus handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusInit(
        const   tommRoC_hw_bus_type_enum_t          type,
        const   tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr,
                tommRoC_hw_bus_t*           const   busPtr);

/**
 * Check if a bus is valid.
 *
 * param[in]        busPtr                  bus handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusCheck(
        const   tommRoC_hw_bus_t*           const   busPtr);

/**
 * Check if a specific operation is available (has been initiated).
 *
 * param[in]        operation               operation.
 * param[in]        busPtr                  bus handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation available
 */
tommRoC_hw_err_enum_t tommRoCHwBusIsOpAvailable(
        const   tommRoC_hw_bus_operations_enum_t            operation,
        const   tommRoC_hw_bus_t*                   const   busPtr);

/**
 * Check if is available received data.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> received data available
 *          TOMMRO_C_HW_BUS_DATA_NOT_AVAILABLE_ERR  -> received data not available
 */
tommRoC_hw_err_enum_t tommRoCHwBusIsDataAvailable(
        const   tommRoC_hw_bus_t*           const   busPtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Get amount of available received data.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[out]       availableAmountPtr      amount of available received data pointer.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDataReady(
        const   tommRoC_hw_bus_t*           const   busPtr,
                uint16_t*                   const   availableAmountPtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Check if data to transmit are pending.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> there are some data to transmit pending
 *          TOMMRO_C_HW_BUS_DATA_NOT_AVAILABLE_ERR  -> no data to transmit pending
 */
tommRoC_hw_err_enum_t tommRoCHwBusIsDataToTxPending(
        const   tommRoC_hw_bus_t*           const   busPtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Get amount of available data to transmit pending.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[out]       availableAmountPtr      amount of available data to transmit pending pointer.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDataToTxPendingAmount(
        const   tommRoC_hw_bus_t*           const   busPtr,
                uint16_t*                   const   availableAmountPtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Write byte.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        writeData               data byte.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusWriteByte(
        const   tommRoC_hw_bus_t*           const   busPtr,
        const   uint8_t                             writeData,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Write buffer.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        writeBufferPtr          data buffer pointer.
 * param[in]        writeBufferLen          data buffer length.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusWriteBuffer(
        const   tommRoC_hw_bus_t*           const   busPtr,
        const   uint8_t*                    const   writeBufferPtr,
        const   uint16_t                            writeBufferLen,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Write buffers.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        writeBuffersPtr         write buffer structure pointer.
 * param[in]        writeBuffersAmount      write buffer structure amount.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusWriteBuffers(
        const   tommRoC_hw_bus_t*           const   busPtr,
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Read byte.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[out]       readDataPtr             output data byte pointer.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 *          TOMMRO_C_HW_BUS_DATA_NOT_AVAILABLE_ERR  -> received data not available
 */
tommRoC_hw_err_enum_t tommRoCHwBusReadByte(
        const   tommRoC_hw_bus_t*           const   busPtr,
                uint8_t*                    const   readDataPtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Read buffer.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 *          TOMMRO_C_HW_BUS_DATA_NOT_AVAILABLE_ERR  -> received data not available
 */
tommRoC_hw_err_enum_t tommRoCHwBusReadBuffer(
        const   tommRoC_hw_bus_t*           const   busPtr,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            toReadAmount,
                uint16_t*                   const   readedAmountPtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Read buffers.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in/out]    readBuffersPtr          read buffer structure pointer.
 * param[in]        readBuffersAmount       read buffer structure amount.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 *          TOMMRO_C_HW_BUS_DATA_NOT_AVAILABLE_ERR  -> received data not available
 */
tommRoC_hw_err_enum_t tommRoCHwBusReadBuffers(
        const   tommRoC_hw_bus_t*           const   busPtr,
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Get byte.
 * NOTE: data are not removed from bus - they are just readed but they are not loosed.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[out]       dataPtr                 output data byte pointer.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 *          TOMMRO_C_HW_BUS_DATA_NOT_AVAILABLE_ERR  -> received data not available
 */
tommRoC_hw_err_enum_t tommRoCHwBusGetByte(
        const   tommRoC_hw_bus_t*           const   busPtr,
                uint8_t*                    const   dataPtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Get buffer.
 * NOTE: data are not removed from bus - they are just readed but they are not loosed.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[out]       bufferPtr               output data buffer pointer.
 * param[in]        toGetAmount             to get byte amount.
 * param[out]       getAmountPtr            get byte count pointer.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 *          TOMMRO_C_HW_BUS_DATA_NOT_AVAILABLE_ERR  -> received data not available
 */
tommRoC_hw_err_enum_t tommRoCHwBusGetBuffer(
        const   tommRoC_hw_bus_t*           const   busPtr,
                uint8_t*                    const   bufferPtr,
        const   uint16_t                            toGetAmount,
                uint16_t*                   const   getAmountPtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Get buffers.
 * NOTE: data are not removed from bus - they are just readed but they are not loosed.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in/out]    getBuffersPtr           get buffer structure pointer.
 * param[in]        getBuffersAmount        get buffer structure amount.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 *          TOMMRO_C_HW_BUS_DATA_NOT_AVAILABLE_ERR  -> received data not available
 */
tommRoC_hw_err_enum_t tommRoCHwBusGetBuffers(
        const   tommRoC_hw_bus_t*           const   busPtr,
                tommRoC_hw_bus_read_buf_t*  const   getBuffersPtr,
        const   uint8_t                             getBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Write/Read byte.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        writeData               data byte.
 * param[out]       readDataPtr             output data byte pointer.
 * param[in]        delayWriteToReadMsec    delay between write and read [msec].
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusWriteReadByte(
        const   tommRoC_hw_bus_t*           const   busPtr,
        const   uint8_t                             writeData,
                uint8_t*                    const   readDataPtr,
        const   uint32_t                            delayWriteToReadMsec,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Write/Read buffer.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        writeBufferPtr          write data buffer.
 * param[in]        writeBufferLen          write data buffer length.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 * param[in]        delayWriteToReadMsec    delay between write and read [msec].
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusWriteReadBuffer(
        const   tommRoC_hw_bus_t*           const   busPtr,
        const   uint8_t*                    const   writeBufferPtr,
        const   uint16_t                            writeBufferLen,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            toReadAmount,
                uint16_t*                   const   readedAmountPtr,
        const   uint32_t                            delayWriteToReadMsec,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Transceive byte.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        writeData               data byte.
 * param[out]       readDataPtr             output data byte pointer.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusTransceiveByte(
        const   tommRoC_hw_bus_t*           const   busPtr,
        const   uint8_t                             writeData,
                uint8_t*                    const   readDataPtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Transceive buffer.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        writeBufferPtr          write data buffer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        bufferLength            transceive data buffer length.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusTransceiveBuffer(
        const   tommRoC_hw_bus_t*           const   busPtr,
        const   uint8_t*                    const   writeBufferPtr,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            bufferLength,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Clear to send/received data of bus.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusClearData(
        const   tommRoC_hw_bus_t*           const   busPtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Clear to send data of bus.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusClearToSendData(
        const   tommRoC_hw_bus_t*           const   busPtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Clear received data of bus.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusClearReceivedData(
        const   tommRoC_hw_bus_t*           const   busPtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Prepare bus for entering low power.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusLowPowerEnter(
        const   tommRoC_hw_bus_t*           const   busPtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Prepare bus for exiting low power.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusLowPowerExit(
        const   tommRoC_hw_bus_t*           const   busPtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Get a prop.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        property                property.
 * param[out]       propValuePtr            output property value pointer.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusGetProp(
        const   tommRoC_hw_bus_t*           const   busPtr,
        const   tommRoC_hw_bus_prop_enum_t          property,
                void*                       const   propValuePtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Set a prop.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        property                property.
 * param[in]        propValuePtr            property value pointer.
 * param[in]        inputPtr                pointer to funct generic input param (cast is made to high level routine).
 * param[out]       resultPtr               pointer to funct generic output param (cast is made to high level routine).
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusSetProp(
                tommRoC_hw_bus_t*           const   busPtr,
        const   tommRoC_hw_bus_prop_enum_t          property,
        const   void*                       const   propValuePtr,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr);

/**
 * Get total to write data amount of a set of write buffer.
 *
 * param[in]        writeBuffersPtr         write buffer structure pointer.
 * param[in]        writeBuffersAmount      write buffer structure amount.
 *
 * return uint32_t
 */
uint32_t tommRoCHwBusWriteBuffersTotalToWriteData(
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount);

/**
 * Get total to read data amount of a set of read buffer.
 *
 * param[in]        readBuffersPtr          read buffer structure pointer.
 * param[in]        readBuffersAmount       read buffer structure amount.
 *
 * return uint32_t
 */
uint32_t tommRoCHwBusReadBuffersTotalToReadData(
        const   tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount);

#endif
