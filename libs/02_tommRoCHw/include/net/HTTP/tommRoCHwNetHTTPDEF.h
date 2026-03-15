
#ifndef TOMMROC_HW_NET_HTTP_DEF_H_
#define TOMMROC_HW_NET_HTTP_DEF_H_

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

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * Enumeration of tommRoC Hw HTTP Version type.
 */
typedef enum {

    TOMMROC_HW_NET_HTTP_DEF_VERSION_0_9 = 0,    // HTTP Version 0.9
    TOMMROC_HW_NET_HTTP_DEF_VERSION_1_0,        // HTTP Version 1.0
    TOMMROC_HW_NET_HTTP_DEF_VERSION_1_1,        // HTTP Version 1.1
    TOMMROC_HW_NET_HTTP_DEF_VERSION_2_0,        // HTTP Version 2.0

} tommRoC_hw_net_http_def_version_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
