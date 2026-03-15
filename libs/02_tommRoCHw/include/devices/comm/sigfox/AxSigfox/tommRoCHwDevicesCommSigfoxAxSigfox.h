
#ifndef TOMMROC_HW_DEVICES_COMM_SIGFOX_AX_SIGFOX_H_
#define TOMMROC_HW_DEVICES_COMM_SIGFOX_AX_SIGFOX_H_

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
#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"
#include "tommRoCHwGPIO.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Ax Sigfox Device ID size [byte]
#define TOMMRO_C_HW_DEVICES_COMM_SIGFOX_AX_SIGFOX_DEVICE_ID_SIZE_BYTE       (8)

// Ax Sigfox PAC size [byte]
#define TOMMRO_C_HW_DEVICES_COMM_SIGFOX_AX_SIGFOX_PAC_SIZE_BYTE             (16)


// Enumeration of tommRoC hardware Ax Sigfox device properties.
typedef enum {

    /**
     * Ax Sigfox Device ID.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be char[TOMMRO_C_HW_DEVICES_COMM_SIGFOX_AX_SIGFOX_DEVICE_ID_SIZE_BYTE].
     */
    TOMMRO_C_HW_DEVICES_COMM_SIGFOX_AX_SIGFOX_DEVICE_ID_PROP = 0,

    /**
     * Ax Sigfox PAC.
     *
     * Available:   get.
     * Notes:       propValuePtr has to be char[TOMMRO_C_HW_DEVICES_COMM_SIGFOX_AX_SIGFOX_PAC_SIZE_BYTE].
     */
    TOMMRO_C_HW_DEVICES_COMM_SIGFOX_AX_SIGFOX_PAC_PROP,

    /**
     * Ax Sigfox Enter Sleep.
     *
     * Available:   set.
     * Notes:       propValuePtr has to be NULL.
     */
    TOMMRO_C_HW_DEVICES_COMM_SIGFOX_AX_SIGFOX_ENTER_SLEEP_PROP,

} tommRoC_hw_devices_comm_sigfox_ax_sigfox_prop_enum_t;


// Maximum Sigfox Send Payload size [byte]
#define TOMMROC_HW_DEVICES_COMM_SIGFOX_AX_SIGFOX_MAX_SEND_FRAME_SIZE_BYTE       (12)

// Maximum Sigfox Receive Payload size [byte]
#define TOMMROC_HW_DEVICES_COMM_SIGFOX_AX_SIGFOX_MAX_RECEIVE_FRAME_SIZE_BYTE    (8)

// Device data.
#define TOMMROC_HW_DEVICES_COMM_SIGFOX_AX_SIGFOX_DEVICE_DATA_SIZE   (   TOMMROC_UTIL_FUNCT_PTR_SIZE +   \
                                                                        TOMMROC_UTIL_FUNCT_PTR_SIZE     )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_COMM_SIGFOX_AX_SIGFOX_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_comm_sigfox_ax_sigfox_device_data_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init bus device as for UART bus.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        busHandlerPtr           bus pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       specificPtr             output specific UART pointer [needed as static because linked by bus device].
 * param[out]       busDevicePtr            output bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommSigfoxAxSigfoxInitUART(
        const   tommRoC_hw_bus_t*                       const   busHandlerPtr,
        const   tommRoC_guard_t*                        const   guardPtr,
                tommRoC_hw_bus_device_specific_uart_t*  const   specificPtr,
                tommRoC_hw_bus_device_t*                const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommSigfoxAxSigfoxAttachDeviceData(
        const   tommRoC_hw_devices_comm_sigfox_ax_sigfox_device_data_t* const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        enterReset              enter in reset function pointer.
 * param[in]        exitReset               exit from reset function pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommSigfoxAxSigfoxStart(
        const   tommRoC_hw_gpio_set_cb_t            enterReset,
        const   tommRoC_hw_gpio_set_cb_t            exitReset,
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr);

/**
 * Write buffer.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        writeBufferPtr          data buffer.
 * param[in]        writeBufferLen          data buffer length.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommSigfoxAxSigfoxWriteBuffer(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   uint8_t*                    const   writeBufferPtr,
        const   uint16_t                            writeBufferLen);

/**
 * Write and read buffer.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        writeBufferPtr          data buffer.
 * param[in]        writeBufferLen          data buffer length.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        toReadAmount            to read byte amount.
 * param[out]       readedAmountPtr         readed byte count pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommSigfoxAxSigfoxWriteAndReadBuffer(
        const   tommRoC_hw_bus_device_t*    const   busDevicePtr,
        const   uint8_t*                    const   writeBufferPtr,
        const   uint16_t                            writeBufferLen,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            toReadAmount,
                uint16_t*                   const   readedAmountPtr);

/**
 * Get a prop.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[out]       propValuePtr            output property value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommSigfoxAxSigfoxGetProp(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_devices_comm_sigfox_ax_sigfox_prop_enum_t            property,
                void*                                                   const   propValuePtr);

/**
 * Set a prop.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        property                property.
 * param[in]        propValuePtr            property value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommSigfoxAxSigfoxSetProp(
        const   tommRoC_hw_bus_device_t*                                const   busDevicePtr,
        const   tommRoC_hw_devices_comm_sigfox_ax_sigfox_prop_enum_t            property,
        const   void*                                                   const   propValuePtr);

#endif
