
#ifndef TOMMROC_HW_NET_LWIP_PPP_DEF_H_
#define TOMMROC_HW_NET_LWIP_PPP_DEF_H_

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

// Enumeration of tommRoC hardware net LwIP PPP authentication type.
typedef enum {

    TOMMROC_HW_NET_LWIP_PPP_DEF_AUTH_TYPE_NONE = 0,
    TOMMROC_HW_NET_LWIP_PPP_DEF_AUTH_TYPE_PAP,
    TOMMROC_HW_NET_LWIP_PPP_DEF_AUTH_TYPE_CHAP,
    TOMMROC_HW_NET_LWIP_PPP_DEF_AUTH_TYPE_MSCHAP,
    TOMMROC_HW_NET_LWIP_PPP_DEF_AUTH_TYPE_MSCHAP_V2,
    TOMMROC_HW_NET_LWIP_PPP_DEF_AUTH_TYPE_EAP,
    TOMMROC_HW_NET_LWIP_PPP_DEF_AUTH_TYPE_ANY,

} tommRoC_hw_net_lwip_ppp_def_auth_type_enum_t;


// Enumeration of tommRoC hardware net LwIP PPP phase type.
typedef enum {

    TOMMROC_HW_NET_LWIP_PPP_DEF_PHASE_TYPE_PHASE_DEAD = 0,
    TOMMROC_HW_NET_LWIP_PPP_DEF_PHASE_TYPE_PHASE_MASTER,
    TOMMROC_HW_NET_LWIP_PPP_DEF_PHASE_TYPE_PHASE_HOLDOFF,
    TOMMROC_HW_NET_LWIP_PPP_DEF_PHASE_TYPE_PHASE_INITIALIZE,
    TOMMROC_HW_NET_LWIP_PPP_DEF_PHASE_TYPE_PHASE_SERIALCONN,
    TOMMROC_HW_NET_LWIP_PPP_DEF_PHASE_TYPE_PHASE_DORMANT,
    TOMMROC_HW_NET_LWIP_PPP_DEF_PHASE_TYPE_PHASE_ESTABLISH,
    TOMMROC_HW_NET_LWIP_PPP_DEF_PHASE_TYPE_PHASE_AUTHENTICATE,
    TOMMROC_HW_NET_LWIP_PPP_DEF_PHASE_TYPE_PHASE_CALLBACK,
    TOMMROC_HW_NET_LWIP_PPP_DEF_PHASE_TYPE_PHASE_NETWORK,
    TOMMROC_HW_NET_LWIP_PPP_DEF_PHASE_TYPE_PHASE_RUNNING,
    TOMMROC_HW_NET_LWIP_PPP_DEF_PHASE_TYPE_PHASE_TERMINATE,
    TOMMROC_HW_NET_LWIP_PPP_DEF_PHASE_TYPE_PHASE_DISCONNECT,

} tommRoC_hw_net_lwip_ppp_def_phase_type_enum_t;


// tommRoC hardware net LwIP PPP layer phase notify phase callback function type definition.
typedef void (*tommRoC_hw_net_lwip_ppp_def_notify_phase_funct_t)(const tommRoC_hw_net_lwip_ppp_def_phase_type_enum_t phase);

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
