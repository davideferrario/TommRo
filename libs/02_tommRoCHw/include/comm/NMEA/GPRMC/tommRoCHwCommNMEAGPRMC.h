
#ifndef TOMMROC_HW_COMM_NMEA_GPRMC_H_
#define TOMMROC_HW_COMM_NMEA_GPRMC_H_

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

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Starting from valid GPRMC string, extract specific field string.
 *
 * param[in]        sentenceStrPtr          NMEA GPRMC sentence string pointer.
 * param[in]        sentenceStrLen          NMEA GPRMC sentence string length.
 * param[out]       fieldStrPtr             output field string pointer.
 * param[in]        fieldStrSize            field string size.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNMEAGPRMCGetTimeString(
        const   char*       const   sentenceStrPtr,
        const   uint16_t            sentenceStrLen,
                char*       const   fieldStrPtr,
        const   uint16_t            fieldStrSize);

tommRoC_hw_err_enum_t tommRoCHwCommNMEAGPRMCGetStatusString(
        const   char*       const   sentenceStrPtr,
        const   uint16_t            sentenceStrLen,
                char*       const   fieldStrPtr,
        const   uint16_t            fieldStrSize);

tommRoC_hw_err_enum_t tommRoCHwCommNMEAGPRMCGetLatitudeString(
        const   char*       const   sentenceStrPtr,
        const   uint16_t            sentenceStrLen,
                char*       const   fieldStrPtr,
        const   uint16_t            fieldStrSize);

tommRoC_hw_err_enum_t tommRoCHwCommNMEAGPRMCGetLongitudeString(
        const   char*       const   sentenceStrPtr,
        const   uint16_t            sentenceStrLen,
                char*       const   fieldStrPtr,
        const   uint16_t            fieldStrSize);

tommRoC_hw_err_enum_t tommRoCHwCommNMEAGPRMCGetDateString(
        const   char*       const   sentenceStrPtr,
        const   uint16_t            sentenceStrLen,
                char*       const   fieldStrPtr,
        const   uint16_t            fieldStrSize);

#endif
