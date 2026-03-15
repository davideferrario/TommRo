
#ifndef TOMMROC_HW_COMM_IP_IPV6_H_
#define TOMMROC_HW_COMM_IP_IPV6_H_

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

// IPv6 address: Consists of colon-separated hexadecimal (0 – FFFF) parameters of the form a1:a2:a3:a4:a5:a6:a7:a8 with abbreviations
#define TOMMROC_HW_COMM_IP_IPv6_ADD_EAMOUNT     (8)
#define TOMMROC_HW_COMM_IP_IPv6_ADD_SIZE        (TOMMROC_HW_COMM_IP_IPv6_ADD_EAMOUNT * TOMMROC_UTIL_U16_SIZE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// IPv6 address structure.
typedef struct {
    uint8_t add[TOMMROC_HW_COMM_IP_IPv6_ADD_SIZE];
} tommRoC_hw_comm_ip_v6_add_t;

#define __EMPTY_tommRoC_hw_comm_ip_v6_add_t_data_field__            TOMMROC_UTIL_DESIGNATED_SECTION_ARRAY(0, TOMMROC_HW_COMM_IP_IPv6_ADD_SIZE - 1, 0)
#define __EMPTY_tommRoC_hw_comm_ip_v6_add_t__                       \
{                                                                   \
    /* .data */ __EMPTY_tommRoC_hw_comm_ip_v6_add_t_data_field__,   \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init an IPv6 address structure.
 * NOTE: IPv6 address consists of colon-separated hexadecimal (0 – FFFF) parameters of the form a1:a2:a3:a4:a5:a6:a7:a8 with abbreviations
 *
 * param[in]        a1,a2,a3,a4,a5,a6,a7,a8 address octets.
 * param[out]       ipV6AddPtr              output IPv6 address structure pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwCommIPv6AddInit(
        const   uint16_t                                a1,
        const   uint16_t                                a2,
        const   uint16_t                                a3,
        const   uint16_t                                a4,
        const   uint16_t                                a5,
        const   uint16_t                                a6,
        const   uint16_t                                a7,
        const   uint16_t                                a8,
                tommRoC_hw_comm_ip_v6_add_t*    const   ipV6AddPtr);

#endif
