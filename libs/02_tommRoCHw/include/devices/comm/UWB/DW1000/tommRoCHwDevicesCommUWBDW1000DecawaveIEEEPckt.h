
#ifndef TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DECAWAVE_IEEE_PCKT_H_
#define TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DECAWAVE_IEEE_PCKT_H_

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

/**
 * DecaWave definition of TAG messages
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

//IEEE EUI-64 tag ID (ISO/IEC 24730-62)
#define TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DECAWAVE_IEEE_PCKT_FRAME_CONTROL_BYTES       (1)
#define TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DECAWAVE_IEEE_PCKT_FRAME_SEQ_NUM_BYTES       (1)
#define TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DECAWAVE_IEEE_PCKT_FRAME_CRC                 (2)
#define TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DECAWAVE_IEEE_PCKT_FRAME_SOURCE_ADDRESS      (8)
#define TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DECAWAVE_IEEE_PCKT_FRAME_CTRLP               (TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DECAWAVE_IEEE_PCKT_FRAME_CONTROL_BYTES + TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DECAWAVE_IEEE_PCKT_FRAME_SEQ_NUM_BYTES) //2
#define TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DECAWAVE_IEEE_PCKT_FRAME_CRTL_AND_ADDRESS    (TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DECAWAVE_IEEE_PCKT_FRAME_SOURCE_ADDRESS + TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DECAWAVE_IEEE_PCKT_FRAME_CTRLP) //10 bytes

// Frame Control
#define TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DECAWAVE_IEEE_PCKT_FCS_EUI_64                (0xC5)
#define TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DECAWAVE_IEEE_PCKT_EUI64_ADDR_SIZE           (8)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// 12 octets for Minimum IEEE ID blink
TOMMRO_C_UTIL_PACKED_PRE typedef struct TOMMRO_C_UTIL_PACKED_POST {

    uint8_t frameCtrl;                                                                      // 00       frame control bytes
    uint8_t seqNum;                                                                         // 01       sequence_number
    uint8_t tagID[TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DECAWAVE_IEEE_PCKT_EUI64_ADDR_SIZE];   // 02-09    64 bit addresses
    uint8_t fcs[2];                                                                         // 10-11    we allow space for the CRC as it is logically part of the message. However DW1000 TX calculates and adds these bytes */

} tommRoC_hw_devices_comm_uwb_dw1000_decawave_ieee_pckt_iso_IEEE_EUI64_blink_msg;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
