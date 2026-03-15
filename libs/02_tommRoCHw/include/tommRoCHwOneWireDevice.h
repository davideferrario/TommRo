
#ifndef TOMMROC_HW_ONE_WIRE_DEVICE_H_
#define TOMMROC_HW_ONE_WIRE_DEVICE_H_

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
#include "tommRoCHwOneWire.h"

#include "TOMMROC.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// tommRoC hardware one wire device.
#define TOMMROC_HW_ONE_WIRE_DEVICE_HANDLE_SIZE  (TOMMROC_UTIL_PTR_SIZE + TOMMROC_UTIL_PTR_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC hardware layer one wire device.
typedef struct {
    uint8_t data[TOMMROC_HW_ONE_WIRE_DEVICE_HANDLE_SIZE];
} tommRoC_hw_one_wire_device_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init one wire device.
 *
 * param[in]        oneWirePtr              one wire handle pointer.
 * param[in]        guardPtr                one wire device guard (NULL if none).
 * param[out]       oneWireDevicePtr        one wire device handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireDeviceInit(
        const   tommRoC_hw_one_wire_t*          const   oneWirePtr,
        const   tommRoC_guard_t*                const   guardPtr,
                tommRoC_hw_one_wire_device_t*   const   oneWireDevicePtr);

/**
 * Reset and check presence of one wire device.
 *
 * param[in]        oneWireDevicePtr        one wire device handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireDeviceResetCheckPresence(
        const   tommRoC_hw_one_wire_device_t*   const   oneWireDevicePtr);

/**
 * Write byte.
 *
 * param[in]        oneWireDevicePtr        one wire device handle pointer.
 * param[in]        writeData               data byte.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireDeviceWriteByte(
        const   tommRoC_hw_one_wire_device_t*   const   oneWireDevicePtr,
        const   uint8_t                                 writeData);

/**
 * Write buffer.
 *
 * param[in]        oneWireDevicePtr        one wire device handle pointer.
 * param[in]        writeBufferPtr          data buffer pointer.
 * param[in]        writeBufferLen          data buffer length.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireDeviceWriteBuffer(
        const   tommRoC_hw_one_wire_device_t*   const   oneWireDevicePtr,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen);

/**
 * Write buffers.
 *
 * param[in]        oneWireDevicePtr        one wire device handle pointer.
 * param[in]        writeBuffersPtr         write buffer structure pointer.
 * param[in]        writeBuffersAmount      write buffer structure amount.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireDeviceWriteBuffers(
        const   tommRoC_hw_one_wire_device_t*   const   oneWireDevicePtr,
        const   tommRoC_hw_bus_write_buf_t*     const   writeBuffersPtr,
        const   uint8_t                                 writeBuffersAmount);

/**
 * Read byte.
 *
 * param[in]        oneWireDevicePtr        one wire device handle pointer.
 * param[out]       readDataPtr             output data byte pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireDeviceReadByte(
        const   tommRoC_hw_one_wire_device_t*   const   oneWireDevicePtr,
                uint8_t*                        const   readDataPtr);

/**
 * Read buffer.
 *
 * param[in]        oneWireDevicePtr        one wire device handle pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireDeviceReadBuffer(
        const   tommRoC_hw_one_wire_device_t*   const   oneWireDevicePtr,
                uint8_t*                        const   readBufferPtr,
        const   uint16_t                                toReadAmount,
                uint16_t*                       const   readedAmountPtr);

/**
 * Read buffers.
 *
 * param[in]        oneWireDevicePtr        one wire device handle pointer.
 * param[in/out]    readBuffersPtr          read buffer structure pointer.
 * param[in]        readBuffersAmount       read buffer structure amount.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireDeviceReadBuffers(
        const   tommRoC_hw_one_wire_device_t*   const   oneWireDevicePtr,
                tommRoC_hw_bus_read_buf_t*      const   readBuffersPtr,
        const   uint8_t                                 readBuffersAmount);

/**
 * Write/Read byte.
 *
 * param[in]        oneWireDevicePtr        one wire device handle pointer.
 * param[in]        writeData               data byte.
 * param[out]       readDataPtr             output data byte pointer.
 * param[in]        delayWriteToReadMsec    delay between write and read [msec].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireDeviceWriteReadByte(
        const   tommRoC_hw_one_wire_device_t*   const   oneWireDevicePtr,
        const   uint8_t                                 writeData,
                uint8_t*                        const   readDataPtr,
        const   uint32_t                                delayWriteToReadMsec);

/**
 * Write/Read buffer.
 *
 * param[in]        oneWireDevicePtr        one wire device handle pointer.
 * param[in]        writeBufferPtr          write data buffer.
 * param[in]        writeBufferLen          write data buffer length.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 * param[in]        delayWriteToReadMsec    delay between write and read [msec].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireDeviceWriteReadBuffer(
        const   tommRoC_hw_one_wire_device_t*   const   oneWireDevicePtr,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen,
                uint8_t*                        const   readBufferPtr,
        const   uint16_t                                toReadAmount,
                uint16_t*                       const   readedAmountPtr,
        const   uint32_t                                delayWriteToReadMsec);

#endif
