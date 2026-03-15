
#ifndef TOMMROC_HW_BUS_DEVICE_H_
#define TOMMROC_HW_BUS_DEVICE_H_

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
#include "tommRoCHwGPIO.h"

#include "TOMMROC.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs - I2C bus device
 ******************************************************************************/

typedef struct {

    /**
     * I2C Slave address.
     * NOTE: Write address (left shift) and read address (left shift + set bit 0) is managed into library.
     */
    uint16_t slaveAddress;

} tommRoC_hw_bus_device_specific_i2c_slave_t;

/*******************************************************************************
 * typedefs - SPI bus device
 ******************************************************************************/

typedef struct {

    /**
     * SPI slave chip select function.
     */
    tommRoC_hw_gpio_set_cb_t chipSelect;

    /**
     * SPI slave after chip select delay [usec].
     */
    uint32_t chipSelectDelayUSec;

    /**
     * SPI slave chip deselect function.
     */
    tommRoC_hw_gpio_set_cb_t chipDeSelect;

    /**
     * SPI slave after chip deselect delay [usec].
     */
    uint32_t chipDeSelectDelayUSec;

} tommRoC_hw_bus_device_specific_spi_slave_t;

/*******************************************************************************
 * typedefs - RS485 bus device
 ******************************************************************************/

typedef struct {

    /**
     * RS485 enable TX function.
     */
    tommRoC_hw_gpio_set_cb_t    enableTX;

    /**
     * RS485 enable RX function.
     */
    tommRoC_hw_gpio_set_cb_t    enableRX;

} tommRoC_hw_bus_device_specific_rs485_t;

/*******************************************************************************
 * typedefs - UART bus device
 ******************************************************************************/

typedef struct {

} tommRoC_hw_bus_device_specific_uart_t;

/*******************************************************************************
 * typedefs - Common bus device
 ******************************************************************************/

// tommRoC hardware layer bus device.
typedef struct {

    /**
     * Bus handler.
     */
    tommRoC_hw_bus_t*   busPtr;

    /**
     * Specific bus device pointer.
     * NOTE: have to be:    tommRoC_hw_bus_device_specific_i2c_slave_t*
     *                      tommRoC_hw_bus_device_specific_spi_slave_t*
     *                      tommRoC_hw_bus_device_specific_rs485_t*
     *                      tommRoC_hw_bus_device_specific_uart_t*
     */
    void*               deviceSpecificPtr;

    /**
     * Bus device operation pointer (used internally).
     */
    void*               deviceOpPtr;

    /**
     * Device data pointer.
     * NOTE: can be used for some devices to store specific informations.
     */
    void*               deviceDataPtr;

    /**
     * Guard (NULL if disabled).
     */
    tommRoC_guard_t*    guardPtr;

} tommRoC_hw_bus_device_t;

/*******************************************************************************
 * functions - I2C Slave bus device
 ******************************************************************************/

/**
 * Init I2C slave specific bus device structure.
 *
 * param[in]        slaveAddress            device I2C slave address.
 * param[out]       deviceSpecificPtr       bus device specific structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceSpecificI2CSlaveInit(
        const   uint16_t                                                slaveAddress,
                tommRoC_hw_bus_device_specific_i2c_slave_t*     const   deviceSpecificPtr);

/**
 * Check I2C slave specific bus device structure.
 *
 * param[in]        devicePtr               bus device specific structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceSpecificI2CSlaveCheck(
        const   tommRoC_hw_bus_device_specific_i2c_slave_t*     const   deviceSpecificPtr);

/*******************************************************************************
 * functions - SPI Slave bus device
 ******************************************************************************/

/**
 * Init SPI slave specific bus device structure.
 *
 * param[in]        chipSelect              chip select function pointer (NULL if none - handled by higher level application).
 * param[in]        chipSelectDelayUSec     after chip select delay [usec] (0 if none - handled by higher level application).
 * param[in]        chipDeSelect            chip de-select function pointer (NULL if none - handled by higher level application).
 * param[in]        chipDeSelectDelayUSec   after chip de-select delay [usec] (0 if none - handled by higher level application).
 * param[out]       deviceSpecificPtr       bus device specific structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceSpecificSPISlaveInit(
        const   tommRoC_hw_gpio_set_cb_t                            chipSelect,
        const   uint32_t                                            chipSelectDelayUSec,
        const   tommRoC_hw_gpio_set_cb_t                            chipDeSelect,
        const   uint32_t                                            chipDeSelectDelayUSec,
                tommRoC_hw_bus_device_specific_spi_slave_t* const   deviceSpecificPtr);

/**
 * Check SPI slave specific bus device structure.
 *
 * param[in]        deviceSpecificPtr       bus device specific structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceSpecificSPISlaveCheck(
        const   tommRoC_hw_bus_device_specific_spi_slave_t* const   deviceSpecificPtr);

/*******************************************************************************
 * functions - RS485 bus device
 ******************************************************************************/

/**
 * Init RS485 specific bus device structure.
 *
 * param[in]        enableTX                enable TX function pointer.
 * param[in]        enableTX                enable RX function pointer.
 * param[out]       deviceSpecificPtr       bus device specific structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceSpecificRS485Init(
        const   tommRoC_hw_gpio_set_cb_t                        enableTX,
        const   tommRoC_hw_gpio_set_cb_t                        enableRX,
                tommRoC_hw_bus_device_specific_rs485_t* const   deviceSpecificPtr);

/**
 * Check RS485 specific bus device structure.
 *
 * param[in]        deviceSpecificPtr       bus device specific structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceSpecificRS485Check(
        const   tommRoC_hw_bus_device_specific_rs485_t* const   deviceSpecificPtr);

/*******************************************************************************
 * functions - UART bus device
 ******************************************************************************/

/**
 * Init UART specific bus device structure.
 *
 * param[out]       deviceSpecificPtr       bus device specific structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceSpecificUARTInit(
                tommRoC_hw_bus_device_specific_uart_t*  const   deviceSpecificPtr);

/**
 * Check UART specific bus device structure.
 *
 * param[in]        deviceSpecificPtr       bus device specific structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceSpecificUARTCheck(
        const   tommRoC_hw_bus_device_specific_uart_t*  const   deviceSpecificPtr);

/*******************************************************************************
 * functions - Common bus device
 ******************************************************************************/

/**
 * Init "no-bus" device.
 *
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       busDevicePtr            bus device structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceNoBusInit(
        const   tommRoC_guard_t*                            const   guardPtr,
                tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Init I2C slave bus device.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        deviceSpecificPtr       bus device specific I2C slave structure pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       busDevicePtr            bus device structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceI2CSlaveInit(
        const   tommRoC_hw_bus_t*                           const   busPtr,
        const   tommRoC_hw_bus_device_specific_i2c_slave_t* const   deviceSpecificPtr,
        const   tommRoC_guard_t*                            const   guardPtr,
                tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Init SPI slave bus device.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        deviceSpecificPtr       bus device specific SPI slave structure pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       busDevicePtr            bus device structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceSPISlaveInit(
        const   tommRoC_hw_bus_t*                           const   busPtr,
        const   tommRoC_hw_bus_device_specific_spi_slave_t* const   deviceSpecificPtr,
        const   tommRoC_guard_t*                            const   guardPtr,
                tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Init RS485 bus device.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        deviceSpecificPtr       bus device specific RS485 structure pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       busDevicePtr            bus device structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceRS485Init(
        const   tommRoC_hw_bus_t*                           const   busPtr,
        const   tommRoC_hw_bus_device_specific_rs485_t*     const   deviceSpecificPtr,
        const   tommRoC_guard_t*                            const   guardPtr,
                tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Init UART bus device.
 *
 * param[in]        busPtr                  bus handle pointer.
 * param[in]        deviceSpecificPtr       bus device specific UART structure pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       busDevicePtr            bus device structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceUARTInit(
        const   tommRoC_hw_bus_t*                           const   busPtr,
        const   tommRoC_hw_bus_device_specific_uart_t*      const   deviceSpecificPtr,
        const   tommRoC_guard_t*                            const   guardPtr,
                tommRoC_hw_bus_device_t*                    const   busDevicePtr);

/**
 * Attach device data to bus device.
 *
 * param[in]        deviceDataPtr           device data pointer.
 * param[in/out]    busDevicePtr            bus device structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceAttachDeviceData(
        const   void*                       const   deviceDataPtr,
                tommRoC_hw_bus_device_t*    const   busDevicePtr);

/**
 * Check if a bus device is valid.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceCheck(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr);

/**
 * Check if is available received data.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> received data available
 *          TOMMRO_C_HW_BUS_DATA_NOT_AVAILABLE_ERR  -> received data not available
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceIsDataAvailable(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr);

/**
 * Get amount of available received data.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[out]       availableAmountPtr      amount of available received data pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceDataReady(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
                uint16_t*                   const   availableAmountPtr);

/**
 * Write byte.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[in]        writeData               data byte.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceWriteByte(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   uint8_t                             writeData);

/**
 * Write buffer.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[in]        writeBufferPtr          data buffer.
 * param[in]        writeBufferLen          data buffer length.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceWriteBuffer(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   uint8_t*                    const   writeBufferPtr,
        const   uint16_t                            writeBufferLen);

/**
 * Write buffers.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[in]        writeBuffersPtr         write buffer structure pointer.
 * param[in]        writeBuffersAmount      write buffer structure amount.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceWriteBuffers(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount);

/**
 * Read byte.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[out]       readDataPtr             output data byte pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceReadByte(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
                uint8_t*                    const   readDataPtr);

/**
 * Read buffer.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceReadBuffer(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            toReadAmount,
                uint16_t*                   const   readedAmountPtr);

/**
 * Read buffers.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[in/out]    readBuffersPtr          read buffer structure pointer.
 * param[in]        readBuffersAmount       read buffer structure amount.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceReadBuffers(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount);

/**
 * Get byte.
 * NOTE: data are not removed from busDevice - they are just readed but they are not loosed.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[out]       dataPtr                 output data byte pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceGetByte(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
                uint8_t*                    const   dataPtr);

/**
 * Get buffer.
 * NOTE: data are not removed from busDevice - they are just readed but they are not loosed.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[out]       bufferPtr               output data buffer pointer.
 * param[in]        toGetAmount             to get byte amount.
 * param[out]       getAmountPtr            get byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceGetBuffer(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
                uint8_t*                    const   bufferPtr,
        const   uint16_t                            toGetAmount,
                uint16_t*                   const   getAmountPtr);

/**
 * Get buffers.
 * NOTE: data are not removed from busDevice - they are just readed but they are not loosed.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[in/out]    getBuffersPtr           get buffer structure pointer.
 * param[in]        getBuffersAmount        get buffer structure amount.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceGetBuffers(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
                tommRoC_hw_bus_read_buf_t*  const   getBuffersPtr,
        const   uint8_t                             getBuffersAmount);

/**
 * Write and read byte.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[in]        writeData               data byte.
 * param[out]       readDataPtr             output data byte pointer.
 * param[in]        delayWriteToReadMsec    delay between write and read [msec].
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceWriteAndReadByte(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   uint8_t                             writeData,
                uint8_t*                    const   readDataPtr,
        const   uint32_t                            delayWriteToReadMsec);

/**
 * Write and read buffer.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[in]        writeBufferPtr          data buffer.
 * param[in]        writeBufferLen          data buffer length.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 * param[in]        delayWriteToReadMsec    delay between write and read [msec].
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceWriteAndReadBuffer(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   uint8_t*                    const   writeBufferPtr,
        const   uint16_t                            writeBufferLen,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            toReadAmount,
                uint16_t*                   const   readedAmountPtr,
        const   uint32_t                            delayWriteToReadMsec);

/**
 * Write and read buffers.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[in]        writeBuffersPtr         write buffer structure pointer.
 * param[in]        writeBuffersAmount      write buffer structure amount.
 * param[in/out]    readBuffersPtr          read buffer structure pointer.
 * param[in]        readBuffersAmount       read buffer structure amount.
 * param[in]        delayWriteToReadMsec    delay between write and read [msec].
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceWriteAndReadBuffers(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   uint32_t                            delayWriteToReadMsec);

/**
 * Transceive byte.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[in]        writeData               data byte.
 * param[out]       readDataPtr             output data byte pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceTransceiveByte(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   uint8_t                             writeData,
                uint8_t*                    const   readDataPtr);

/**
 * Transceive buffer.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 * param[in]        writeBufferPtr          write data buffer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        bufferLength            transceive data buffer length.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceTransceiveBuffer(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   uint8_t*                    const   writeBufferPtr,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            bufferLength);

/**
 * Clear to send/received data of bus device.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceClearData(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr);

/**
 * Clear to send data of bus device.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceClearToSendData(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr);

/**
 * Clear received data of bus device.
 *
 * param[in]        busDevicePtr            bus device struct pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_NOT_AVAILABLE_ERR           -> operation not available
 *          TOMMRO_C_HW_ERR_SUCCESS                 -> operation success
 */
tommRoC_hw_err_enum_t tommRoCHwBusDeviceClearReceivedData(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr);

#endif
