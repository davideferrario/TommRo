
#ifndef TOMMROC_HW_ONE_WIRE_H_
#define TOMMROC_HW_ONE_WIRE_H_

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

/*******************************************************************************
 * defines
 ******************************************************************************/

// tommRoC hardware one wire.
#define TOMMROC_HW_ONE_WIRE_HANDLE_SIZE (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                            TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                            TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                            TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                            TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                            TOMMROC_UTIL_FUNCT_PTR_SIZE     )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC hardware layer one wire.
typedef struct {
    uint8_t data[TOMMROC_HW_ONE_WIRE_HANDLE_SIZE];
} tommRoC_hw_one_wire_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init one wire.
 *
 * param[in]        setPinAsInput           set pin as input function pointer.
 * param[in]        setPinAsOutputLow       set pin as output low function pointer.
 * param[in]        setPinAsOutputHigh      set pin as output high function pointer.
 * param[in]        getPinStatus            get input pin status function pointer.
 * param[in]        setPinLow               set output pin low function pointer.
 * param[in]        setPinHigh              set output pin high function pointer.
 * param[out]       oneWirePtr              one wire handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireInit(
        const   tommRoC_hw_gpio_set_dir_cb_t            setPinAsInput,
        const   tommRoC_hw_gpio_set_dir_cb_t            setPinAsOutputLow,
        const   tommRoC_hw_gpio_set_dir_cb_t            setPinAsOutputHigh,
        const   tommRoC_hw_gpio_get_cb_t                getPinStatus,
        const   tommRoC_hw_gpio_set_cb_t                setPinLow,
        const   tommRoC_hw_gpio_set_cb_t                setPinHigh,
                tommRoC_hw_one_wire_t*          const   oneWirePtr);

/**
 * Reset and check presence on one wire.
 *
 * param[in]        oneWirePtr              one wire handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireResetCheckPresence(
        const   tommRoC_hw_one_wire_t*          const   oneWirePtr);

/**
 * Write byte.
 *
 * param[in]        oneWirePtr              one wire handle pointer.
 * param[in]        writeData               data byte.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireWriteByte(
        const   tommRoC_hw_one_wire_t*          const   oneWirePtr,
        const   uint8_t                                 writeData);

/**
 * Write buffer.
 *
 * param[in]        oneWirePtr              one wire handle pointer.
 * param[in]        writeBufferPtr          data buffer pointer.
 * param[in]        writeBufferLen          data buffer length.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireWriteBuffer(
        const   tommRoC_hw_one_wire_t*          const   oneWirePtr,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen);

/**
 * Write buffers.
 *
 * param[in]        oneWirePtr              one wire handle pointer.
 * param[in]        writeBuffersPtr         write buffer structure pointer.
 * param[in]        writeBuffersAmount      write buffer structure amount.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireWriteBuffers(
        const   tommRoC_hw_one_wire_t*          const   oneWirePtr,
        const   tommRoC_hw_bus_write_buf_t*     const   writeBuffersPtr,
        const   uint8_t                                 writeBuffersAmount);

/**
 * Read byte.
 *
 * param[in]        oneWirePtr              one wire handle pointer.
 * param[out]       readDataPtr             output data byte pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireReadByte(
        const   tommRoC_hw_one_wire_t*          const   oneWirePtr,
                uint8_t*                        const   readDataPtr);

/**
 * Read buffer.
 *
 * param[in]        oneWirePtr              one wire handle pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireReadBuffer(
        const   tommRoC_hw_one_wire_t*          const   oneWirePtr,
                uint8_t*                        const   readBufferPtr,
        const   uint16_t                                toReadAmount,
                uint16_t*                       const   readedAmountPtr);

/**
 * Read buffers.
 *
 * param[in]        oneWirePtr              one wire handle pointer.
 * param[in/out]    readBuffersPtr          read buffer structure pointer.
 * param[in]        readBuffersAmount       read buffer structure amount.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireReadBuffers(
        const   tommRoC_hw_one_wire_t*          const   oneWirePtr,
                tommRoC_hw_bus_read_buf_t*      const   readBuffersPtr,
        const   uint8_t                                 readBuffersAmount);

/**
 * Write/Read byte.
 *
 * param[in]        oneWirePtr              one wire handle pointer.
 * param[in]        writeData               data byte.
 * param[out]       readDataPtr             output data byte pointer.
 * param[in]        delayWriteToReadMsec    delay between write and read [msec].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireWriteReadByte(
        const   tommRoC_hw_one_wire_t*          const   oneWirePtr,
        const   uint8_t                                 writeData,
                uint8_t*                        const   readDataPtr,
        const   uint32_t                                delayWriteToReadMsec);

/**
 * Write/Read buffer.
 *
 * param[in]        oneWirePtr              one wire handle pointer.
 * param[in]        writeBufferPtr          write data buffer.
 * param[in]        writeBufferLen          write data buffer length.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 * param[in]        delayWriteToReadMsec    delay between write and read [msec].
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwOneWireWriteReadBuffer(
        const   tommRoC_hw_one_wire_t*          const   oneWirePtr,
        const   uint8_t*                        const   writeBufferPtr,
        const   uint16_t                                writeBufferLen,
                uint8_t*                        const   readBufferPtr,
        const   uint16_t                                toReadAmount,
                uint16_t*                       const   readedAmountPtr,
        const   uint32_t                                delayWriteToReadMsec);

#endif
