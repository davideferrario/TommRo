
#ifndef TOMMROC_HW_COMM_GSM_GPRS_H_
#define TOMMROC_HW_COMM_GSM_GPRS_H_

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
#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * IMEI (International Mobile Equipment Identity) is a string of 15 bytes in length.
 * Each module corresponds to the only IMEI number.
 */
#define TOMMROC_HW_COMM_GSM_GPRS_IMEI_STRING_DEVICE_LENGTH  (15)
#define TOMMROC_HW_COMM_GSM_GPRS_IMEI_STRING_DEVICE_SIZE    (TOMMROC_HW_COMM_GSM_GPRS_IMEI_STRING_DEVICE_LENGTH + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)

/**
 * ISMI (International Mobile Subscriber Identity) is a string of 15 bytes in length.
 * Each module corresponds to the only IMEI number.
 */
#define TOMMROC_HW_COMM_GSM_GPRS_IMSI_STRING_DEVICE_LENGTH  (15)
#define TOMMROC_HW_COMM_GSM_GPRS_IMSI_STRING_DEVICE_SIZE    (TOMMROC_HW_COMM_GSM_GPRS_IMSI_STRING_DEVICE_LENGTH + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// NMEA sentences.
typedef enum {

    TOMMROC_HW_COMM_GSM_GPRS_NETWORK_REGISTRATION_STATUS_NOT_REGISTERED_NOT_SEARCH_ACTIVE = 0,
    TOMMROC_HW_COMM_GSM_GPRS_NETWORK_REGISTRATION_STATUS_REGISTERED_HOME,
    TOMMROC_HW_COMM_GSM_GPRS_NETWORK_REGISTRATION_STATUS_NOT_REGISTERED_SEARCH_ACTIVE,
    TOMMROC_HW_COMM_GSM_GPRS_NETWORK_REGISTRATION_STATUS_REGISTRATION_DENIED,
    TOMMROC_HW_COMM_GSM_GPRS_NETWORK_REGISTRATION_STATUS_UNKNOWN,
    TOMMROC_HW_COMM_GSM_GPRS_NETWORK_REGISTRATION_STATUS_REGISTERED_ROAMING,
    TOMMROC_HW_COMM_GSM_GPRS_NETWORK_REGISTRATION_STATUS_REGISTERED_HOME_SMS_ONLY,
    TOMMROC_HW_COMM_GSM_GPRS_NETWORK_REGISTRATION_STATUS_REGISTERED_ROAMING_SMS_ONLY,
    TOMMROC_HW_COMM_GSM_GPRS_NETWORK_REGISTRATION_STATUS_ATTACHED_EMERGENCY,
    TOMMROC_HW_COMM_GSM_GPRS_NETWORK_REGISTRATION_STATUS_REGISTERED_HOME_CSFB,
    TOMMROC_HW_COMM_GSM_GPRS_NETWORK_REGISTRATION_STATUS_REGISTERED_ROAMING_CSFB,

} tommRoC_hw_comm_gsm_gprs_network_registration_status_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
