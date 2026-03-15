
#ifndef TOMMROC_HW_DEVICES_GPS_NMEA_H_
#define TOMMROC_HW_DEVICES_GPS_NMEA_H_

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
#include <stdint.h>

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/
#define NMEA_PARSER_SAVED_NMEA_STRING_MAX_SIZE          (89)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration tommRoC NMEA latitude direction.
typedef enum {

    /**
     * North latitude direction.
     */
    TOMMRO_C_HW_NMEA_LATITUDE_DIR_NORTH = 0,

    /**
     * South latitude direction.
     */
    TOMMRO_C_HW_NMEA_LATITUDE_DIR_SOUTH,

} tommRoC_hw_nmea_latitude_direction_enum_t;

// Enumeration tommRoC NMEA longitude direction.
typedef enum {

    /**
     *  East longitude direction.
     */
    TOMMRO_C_HW_NMEA_LONGITUDE_DIR_EAST = 0,

    /**
     *  West longitude direction.
     */
    TOMMRO_C_HW_NMEA_LONGITUDE_DIR_WEST,

} tommRoC_hw_nmea_longitude_direction_enum_t;


// Enumeration tommRoC NMEA GPS fix.
typedef enum {

    /**
     *  GPS fix not valid.
     */
    TOMMRO_C_HW_NMEA_GPS_FIX_INVALID = 0,

    /**
     *  GPS fix.
     */
    TOMMRO_C_HW_NMEA_GPS_FIX_VALID,

    /**
     *  GPS differential fix.
     */
    TOMMRO_C_HW_NMEA_GPS_FIX_DIFF_VALID,

    /**
     *  GPS Real-Time Kinematic, fixed integers fix.
     */
    TOMMRO_C_HW_NMEA_GPS_FIX_RTK_FIXED_INTEGERS,

    /**
     *  GPS Real-Time Kinematic, float integers fix.
     */
    TOMMRO_C_HW_NMEA_GPS_FIX_RTK_FLOAT_INTEGERS,

} tommRoC_hw_nmea_gps_fix_enum_t;


// tommRoC NMEA result struct.
typedef struct {

    /**
     * Latitude value and direction.
     */
    float                                       latitudeValue;
    tommRoC_hw_nmea_latitude_direction_enum_t   latitudeDir;

    /**
     * Longitude value and direction.
     */
    float                                       longitudeValue;
    tommRoC_hw_nmea_longitude_direction_enum_t  longitudeDir;

    /**
     * GPS fix.
     */
    tommRoC_hw_nmea_gps_fix_enum_t              gpsFix;

    /**
     * Altitude above mean-sea-level [meters].
     */
    float                                       altitudeValue;
    
    /**
     * Satellites number.
     */
    uint8_t                                     satNumber;

    /**
     * Date time.
     */
    tommRoC_date_time_t                         dateTime;

} tommRoC_hw_nmea_result_t;

#define __EMPTY_tommRoC_hw_nmea_result_t__                                      \
{                                                                               \
    /* .latitudeValue */    0.0f,                                               \
    /* .latitudeDir */      TOMMRO_C_HW_NMEA_LATITUDE_DIR_NORTH,                \
                                                                                \
    /* .longitudeValue */   0.0f,                                               \
    /* .longitudeDir */     TOMMRO_C_HW_NMEA_LONGITUDE_DIR_EAST,                \
                                                                                \
    /* .gpsFix */           TOMMRO_C_HW_NMEA_GPS_FIX_INVALID,                   \
                                                                                \
    /* .altitudeValue */    0.0f,                                               \
                                                                                \
    /* .satNumber */        0,                                                  \
                                                                                \
    /* .dateTime */         __EMPTY_tommRoC_date_time_t__,                      \
}


// tommRoC NMEA decode struct.
typedef struct {

    /**
     * Saved nmea string.
     */
    char                        string[NMEA_PARSER_SAVED_NMEA_STRING_MAX_SIZE];

    /**
     * Saved nmea string index.
     */
    uint16_t                    stringIndex;

    /**
     * Latest decoded result.
     */
    tommRoC_hw_nmea_result_t    result;

} tommRoC_hw_nmea_parser_t;

#define __EMPTY_tommRoC_hw_nmea_parser_t__                                      \
{                                                                               \
    /* .string */       "",                                                     \
    /* .stringIndex */  0,                                                      \
    /* .result */       __EMPTY_tommRoC_hw_nmea_result_t__,                     \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
