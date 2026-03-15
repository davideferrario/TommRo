
#ifndef TOMMROC_HW_COMM_IP_IPV4_H_
#define TOMMROC_HW_COMM_IP_IPV4_H_

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

#include "TOMMROC.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// IPv4 interface: Consists of dot-separated decimal (0 - 255) parameters of the form a1.a2.a3.a4
#define TOMMROC_HW_COMM_IP_IPv4_ITF_EAMOUNT             (4)
#define TOMMROC_HW_COMM_IP_IPv4_ITF_SIZE                (TOMMROC_HW_COMM_IP_IPv4_ITF_EAMOUNT * TOMMROC_UTIL_U8_SIZE)
#define TOMMROC_HW_COMM_IP_IPv4_ITF_STRING_MAX_SIZE     (sizeof("000.000.000.000"))
#define TOMMROC_HW_COMM_IP_IPv4_ITF_STRING_MAX_LENGTH   (TOMMROC_UTIL_STRING_ARR_LENGTH("000.000.000.000"))

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of IPv4 as string conversion format.
typedef enum {

    /**
     * Decimal no zero padded number format.
     * Example: "1.2.254.255"
     */
    TOMMROC_HW_COMM_IP_IPV4_AS_STRING_DECIMAL_FORMAT = 0,

    /**
     * Decimal zero padded number format [3 digits].
     * Example: "001.002.254.255"
     */
    TOMMROC_HW_COMM_IP_IPV4_AS_STRING_3_DIGIT_ZERO_PADDED_DECIMAL_FORMAT,

} tommRoC_hw_comm_ip_v4_as_string_conversion_format_enum_t;


// IPv4 interface structure.
typedef struct {
    uint8_t data[TOMMROC_HW_COMM_IP_IPv4_ITF_SIZE];
} tommRoC_hw_comm_ip_v4_itf_t;

#define __EMPTY_tommRoC_hw_comm_ip_v4_itf_t_data_field__            TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_HW_COMM_IP_IPv4_ITF_SIZE - 1, 0)
#define __EMPTY_tommRoC_hw_comm_ip_v4_itf_t__                       \
{                                                                   \
    /* .data */ __EMPTY_tommRoC_hw_comm_ip_v4_itf_t_data_field__,   \
}


// IPv4 interface as string structure.
// NOTE: in the form "1.2.254.255" or "001.002.254.255" + '\0'.
typedef struct {
    char data[TOMMROC_HW_COMM_IP_IPv4_ITF_STRING_MAX_SIZE];
} tommRoC_hw_comm_ip_v4_itf_as_string_t;

#define __EMPTY_tommRoC_hw_comm_ip_v4_itf_as_string_t_data_field__          TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_HW_COMM_IP_IPv4_ITF_STRING_MAX_SIZE - 1, TOMMROC_STRING_NULL_TERMINATOR_CHAR)
#define __EMPTY_tommRoC_hw_comm_ip_v4_itf_as_string_t__                     \
{                                                                           \
    /* .data */ __EMPTY_tommRoC_hw_comm_ip_v4_itf_as_string_t_data_field__, \
}


// IPv4 address.
typedef tommRoC_hw_comm_ip_v4_itf_t                         tommRoC_hw_comm_ip_v4_add_t;
typedef tommRoC_hw_comm_ip_v4_itf_as_string_t               tommRoC_hw_comm_ip_v4_add_as_string_t;
#define __EMPTY_tommRoC_hw_comm_ip_v4_add_t__               __EMPTY_tommRoC_hw_comm_ip_v4_itf_t__
#define __EMPTY_tommRoC_hw_comm_ip_v4_add_as_string_t__     __EMPTY_tommRoC_hw_comm_ip_v4_itf_as_string_t__

// IPv4 subnet mask.
typedef tommRoC_hw_comm_ip_v4_itf_t                         tommRoC_hw_comm_ip_v4_mask_t;
typedef tommRoC_hw_comm_ip_v4_itf_as_string_t               tommRoC_hw_comm_ip_v4_mask_as_string_t;
#define __EMPTY_tommRoC_hw_comm_ip_v4_mask_t__              __EMPTY_tommRoC_hw_comm_ip_v4_itf_t__
#define __EMPTY_tommRoC_hw_comm_ip_v4_mask_as_string_t__    __EMPTY_tommRoC_hw_comm_ip_v4_itf_as_string_t__

// IPv4 gateway.
typedef tommRoC_hw_comm_ip_v4_itf_t                         tommRoC_hw_comm_ip_v4_gateway_t;
typedef tommRoC_hw_comm_ip_v4_itf_as_string_t               tommRoC_hw_comm_ip_v4_gateway_as_string_t;
#define __EMPTY_tommRoC_hw_comm_ip_v4_gateway_t__           __EMPTY_tommRoC_hw_comm_ip_v4_itf_t__
#define __EMPTY_tommRoC_hw_comm_ip_v4_gateway_as_string_t__ __EMPTY_tommRoC_hw_comm_ip_v4_itf_as_string_t__

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init an IPv4 interface structure.
 * NOTE: IPv4 interface consists of dot-separated decimal parameters of the form a1.a2.a3.a4
 *
 * param[in]        a1,a2,a3,a4             interface octets.
 * param[out]       ipV4ItfPtr              output IPv4 interface structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommIPv4ItfInit(
        const   uint8_t                                                             a1,
        const   uint8_t                                                             a2,
        const   uint8_t                                                             a3,
        const   uint8_t                                                             a4,
                tommRoC_hw_comm_ip_v4_itf_t*                                const   ipV4ItfPtr);

/**
 * Init an IPv4 as string interface structure.
 *
 * param[in]        addStrPtr               IPv4 address expressed as string (a1.a2.a3.a4).
 * param[out]       ipV4ItfAsStrPtr         output IPv4 as string interface structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommIPv4AsStringItfInit(
        const   char*                                                       const   addStrPtr,
                tommRoC_hw_comm_ip_v4_itf_as_string_t*                      const   ipV4ItfAsStrPtr);


/**
 * Init an IPv4 as string interface structure.
 *
 * param[in]        addStrPtr               IPv4 address expressed as string (a1.a2.a3.a4).
 * param[in]        addStrLen               IPv4 address expressed as string length.
 * param[out]       ipV4ItfAsStrPtr         output IPv4 as string interface structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommIPv4AsStringLenItfInit(
        const   char*                                                       const   addStrPtr,
        const   uint16_t                                                            addStrLen,
                tommRoC_hw_comm_ip_v4_itf_as_string_t*                      const   ipV4ItfAsStrPtr);

/**
 * Convert an IPv4 interface structure to equivalent uint8_t array [TOMMROC_HW_COMM_IP_IPv4_ITF_EAMOUNT elements].
 * NOTE: ipV4AddU8ArrayPtr output param MUST be a pointer to an array of TOMMROC_HW_COMM_IP_IPv4_ITF_EAMOUNT uint8_t elements.
 *
 * param[in]        ipV4ItfPtr                  IPv4 interface structure pointer.
 * param[out]       ipV4ItfU8ArrayPtr           output IPv4 interface as uint8_t array pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommIPv4ItfToU8Array(
        const   tommRoC_hw_comm_ip_v4_itf_t*                                const   ipV4ItfPtr,
                uint8_t*                                                    const   ipV4ItfU8ArrayPtr);

/**
 * Convert an IPv4 interface structure to equivalent string.
 * NOTE: IPv4 interface as string is in the form "1.2.254.255" or "001.002.254.255" + '\0'.
 *
 * param[in]        ipV4ItfPtr              IPv4 interface structure pointer.
 * param[out]       ipV4ItfAsStrPtr         output IPv4 interface as string structure pointer.
 * param[in]        format                  string conversion format.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommIPv4ItfToAsString(
        const   tommRoC_hw_comm_ip_v4_itf_t*                                const   ipV4ItfPtr,
                tommRoC_hw_comm_ip_v4_itf_as_string_t*                      const   ipV4ItfAsStrPtr,
        const   tommRoC_hw_comm_ip_v4_as_string_conversion_format_enum_t            format);

/**
 * Convert an IPv4 interface as string to equivalent IPv4 interface structure.
 *
 * param[in]        ipV4ItfAsStrPtr         IPv4 interface as string structure pointer.
 * param[out]       ipV4AddPtr              output IPv4 interface structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommIPv4AsStringToItf(
        const   tommRoC_hw_comm_ip_v4_itf_as_string_t*                      const   ipV4ItfAsStrPtr,
                tommRoC_hw_comm_ip_v4_itf_t*                                const   ipV4ItfPtr);

#endif
