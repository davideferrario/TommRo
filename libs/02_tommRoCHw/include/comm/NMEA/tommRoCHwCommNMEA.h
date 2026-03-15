
#ifndef TOMMROC_HW_COMM_NMEA_H_
#define TOMMROC_HW_COMM_NMEA_H_

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
#include "comm/NMEA/GNGGA/tommRoCHwCommNMEAGNGGA.h"
#include "comm/NMEA/GPGGA/tommRoCHwCommNMEAGPGGA.h"
#include "comm/NMEA/GPRMC/tommRoCHwCommNMEAGPRMC.h"

#include "tommRoCHwErr.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// NMEA sentences.
typedef enum {

    TOMMROC_HW_COMM_NMEA_SENTENCE_GPAPB = 0,
    TOMMROC_HW_COMM_NMEA_SENTENCE_GPBOD,
    TOMMROC_HW_COMM_NMEA_SENTENCE_GPGGA,
    TOMMROC_HW_COMM_NMEA_SENTENCE_GPGLL,
    TOMMROC_HW_COMM_NMEA_SENTENCE_GPGSA,
    TOMMROC_HW_COMM_NMEA_SENTENCE_GPGSV,
    TOMMROC_HW_COMM_NMEA_SENTENCE_GPRMB,
    TOMMROC_HW_COMM_NMEA_SENTENCE_GPRMC,
    TOMMROC_HW_COMM_NMEA_SENTENCE_GPRTE,
    TOMMROC_HW_COMM_NMEA_SENTENCE_GPWPL,

    TOMMROC_HW_COMM_NMEA_SENTENCE_GNGGA,

} tommRoC_hw_comm_nmea_sentence_type_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Check if a sentence is a valid NMEA sentence.
 * NOTE: what is tested is:
 *          - sentence string starts with "$GP" or "$GN".
 *          - sentence string contains "*" and two more characters for HEX checksum.
 *          - the checksum is corrected.
 *
 * param[in]        sentenceStrPtr          NMEA sentence string pointer.
 * param[in]        sentenceStrLen          NMEA sentence string length.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNMEAIsValidSentence(
        const   char*       const   sentenceStrPtr,
        const   uint16_t            sentenceStrLen);

/**
 * Check if a sentence is a valid specific NMEA sentence.
 * NOTE: what is tested is:
 *          - sentence is a valid NMEA sentence.
 *
 * param[in]        sentenceStrPtr          NMEA sentence string pointer.
 * param[in]        sentenceStrLen          NMEA sentence string length.
 * param[in]        sentenceType            NMEA sentence type.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommNMEAIsValidSpecificSentence(
        const   char*                                       const   sentenceStrPtr,
        const   uint16_t                                            sentenceStrLen,
        const   tommRoC_hw_comm_nmea_sentence_type_enum_t           sentenceType);

#endif
