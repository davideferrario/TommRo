
#ifndef TOMMROC_HW_DEVICES_GPS_L80_H_
#define TOMMROC_HW_DEVICES_GPS_L80_H_

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

#include "devices/GPS/tommRoCHwDevicesGPSNMEA.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// tommRoC hardware GPS L80.
typedef struct {

    /**
     * Bus.
     * NOTE: only UART 9600 baud rate bus supported.
     */
    tommRoC_hw_bus_t*           busHandlerPtr;

    /**
     * Guard (NULL if disabled).
     */
    tommRoC_guard_t*            guardPtr;

    /**
     * Put in reset pin callback.
     */
    tommRoC_hw_gpio_set_cb_t    putInReset;

    /**
     * Remove from reset pin callback.
     */
    tommRoC_hw_gpio_set_cb_t    removeFromReset;

    /**
     * NMEA parser.
     */
    tommRoC_hw_nmea_parser_t    nmeaParser;

} tommRoC_hw_devices_gps_l80_t;

#define __EMPTY_tommRoC_hw_devices_gps_l80_t__                                      \
{                                                                                   \
    /* .busHandlerPtr */    NULL,                                                   \
    /* .guardPtr */         NULL,                                                   \
    /* .putInReset */       NULL,                                                   \
    /* .removeFromReset */  NULL,                                                   \
    /* .nmeaParser */       __EMPTY_tommRoC_hw_nmea_parser_t__,                     \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Start a GPS L80.
 *
 * param[in]        busHandlerPtr           bus pointer.
 * param[in]        guardPtr                guard (NULL if none).
 * param[in]        putInReset              GPS put in reset function.
 * param[in]        removeFromReset         GPS remove from reset function.
 * param[out]       gpsPtr                  GPS handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPSL80Start(
        const   tommRoC_hw_bus_t*               const   busHandlerPtr,
        const   tommRoC_guard_t*                const   guardPtr,
        const   tommRoC_hw_gpio_set_cb_t                putInReset,
        const   tommRoC_hw_gpio_set_cb_t                removeFromReset,
                tommRoC_hw_devices_gps_l80_t*   const   gpsPtr);

/**
 * Update GPS status (read from UART and update internal status).
 *
 * param[in]        gpsPtr                  GPS handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPSL80UpdateStatus(
        const   tommRoC_hw_devices_gps_l80_t*   const   gpsPtr);

/**
 * Get GPS result.
 *
 * param[in]        gpsPtr                  GPS handle pointer.
 * param[out]       resultPtr               result value pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesGPSL80GetResult(
        const   tommRoC_hw_devices_gps_l80_t*   const   gpsPtr,
                tommRoC_hw_nmea_result_t*       const   resultPtr);

#endif
