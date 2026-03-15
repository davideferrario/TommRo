
#ifndef TOMMROC_HW_DEVICES_GPS_CAM_M8_H_
#define TOMMROC_HW_DEVICES_GPS_CAM_M8_H_

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

#include "devices/GPS/tommRoCHwDevicesGPSNMEA.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Device data.
#define TOMMROC_HW_DEVICES_GPS_CAM_M8_DEVICE_DATA_SIZE  (   TOMMROC_UTIL_FUNCT_PTR_SIZE         +   \
                                                            TOMMROC_UTIL_FUNCT_PTR_SIZE         +   \
                                                            TOMMROC_UTIL_BOOL_SIZE              +   \
                                                            sizeof(tommRoC_hw_nmea_parser_t)    +   \
                                                            sizeof(tommRoC_hw_nmea_parser_t)    +   \
                                                            sizeof(tommRoC_hw_nmea_parser_t)        )
                                                                        
/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_GPS_CAM_M8_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_gps_cam_m8_device_data_t;

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
tommRoC_hw_err_enum_t tommRoCHwDevicesGPSCamM8InitUART(
        const   tommRoC_hw_bus_t*                               const   busHandlerPtr,
        const   tommRoC_guard_t*                                const   guardPtr,
                tommRoC_hw_bus_device_specific_uart_t*          const   specificPtr,
                tommRoC_hw_bus_device_t*                        const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPSCamM8AttachDeviceData(
        const   tommRoC_hw_devices_gps_cam_m8_device_data_t*    const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                        const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        RSTNPinLow              chip RESET_N pin low function pointer.
 * param[in]        RSTNPinHigh             chip RESET_N pin high function pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPSCamM8Start(
        const   tommRoC_hw_gpio_set_cb_t                                RSTN_NPinLow,
        const   tommRoC_hw_gpio_set_cb_t                                RSTN_NPinHigh,
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr);

/**
 * Update GPS status (read from UART and update internal status).
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 *          TOMMRO_C_HW_ERR_SUCCESS         -> new valid GPS result available.
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPSCamM8UpdateStatus(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr);

/**
 * Get GPS result.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       resultPtr               result value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPSCamM8GetResult(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr,
                tommRoC_hw_nmea_result_t*                       const   resultPtr);

/**
 * Update GPS status (read from UART and update internal status).
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPSCamM8Shutdown(
        const   tommRoC_hw_bus_device_t*                        const   busDevicePtr);

#endif
