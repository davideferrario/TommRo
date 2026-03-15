
#ifndef TOMMROC_HW_DEVICES_COMM_CELLULAR_DEF_H_
#define TOMMROC_HW_DEVICES_COMM_CELLULAR_DEF_H_

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

/*******************************************************************************
 * defines
 ******************************************************************************/

// NOTE: these are used to check externally the correctness of the size of tommRoCMw structures
#define TOMMROC_HW_DEVICES_COMM_CELLULAR_DEF_MUTEX_SIZE_BYTE    (52)
#define TOMMROC_HW_DEVICES_COMM_CELLULAR_DEF_THREAD_SIZE_BYTE   (188)

// Invalid signal value.
#define TOMMROC_HW_DEVICES_COMM_CELLULAR_DEF_INVALID_SIGNAL_VALUE       (-32768)
// Invalid signal bar value.
#define TOMMROC_HW_DEVICES_COMM_CELLULAR_DEF_INVALID_SIGNAL_BAR_VALUE   (0xFFU)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Cellular signal information structure.
typedef struct {
    int16_t rssi;   // Received Signal Strength Indicator (RSSI) in dBm.
    int16_t rsrp;   // LTE Reference Signal Received Power (RSRP) in dBm.
    int16_t rsrq;   // LTE Reference Signal Received Quality (RSRQ) in dB.
    int16_t sinr;   // LTE Signal to Interference-Noise Ratio in dB.
    int16_t ber;    // Bit Error Rate (BER) in 0.01%.
    uint8_t bars;   // A number between 0 to 5 (both inclusive) indicating signal strength.
} tommRoC_hw_devices_comm_cellular_def_signal_info_t;

#define __EMPTY_tommRoC_hw_devices_comm_cellular_def_signal_info_t__            \
{                                                                               \
    /* .rssi */ TOMMROC_HW_DEVICES_COMM_CELLULAR_DEF_INVALID_SIGNAL_VALUE,      \
    /* .rsrp */ TOMMROC_HW_DEVICES_COMM_CELLULAR_DEF_INVALID_SIGNAL_VALUE,      \
    /* .rsrq */ TOMMROC_HW_DEVICES_COMM_CELLULAR_DEF_INVALID_SIGNAL_VALUE,      \
    /* .sinr */ TOMMROC_HW_DEVICES_COMM_CELLULAR_DEF_INVALID_SIGNAL_VALUE,      \
    /* .ber */  TOMMROC_HW_DEVICES_COMM_CELLULAR_DEF_INVALID_SIGNAL_VALUE,      \
    /* .bars */ TOMMROC_HW_DEVICES_COMM_CELLULAR_DEF_INVALID_SIGNAL_BAR_VALUE,  \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
