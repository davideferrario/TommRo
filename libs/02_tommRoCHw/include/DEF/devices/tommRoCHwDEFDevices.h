
#ifndef TOMMROC_HW_DEF_DEVICES_H_
#define TOMMROC_HW_DEF_DEVICES_H_

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

// Enumeration of tommRoC hardware devices operating modes type.
typedef enum {

    // Top performance mode.
    // Configuration for maximum possible performance/no care for power consumption (without/with low noise version).
    TOMMRO_C_HW_DEVICES_DEF_OPERATING_MODE_TOP_PERFORMANCE = 0,
    TOMMRO_C_HW_DEVICES_DEF_OPERATING_MODE_TOP_PERFORMANCE_LOW_NOISE,

    // High performance mode.
    // Configuration for good performance/little care for power consumption (without/with low noise version).
    TOMMRO_C_HW_DEVICES_DEF_OPERATING_MODE_HIGH_PERFORMANCE,
    TOMMRO_C_HW_DEVICES_DEF_OPERATING_MODE_HIGH_PERFORMANCE_LOW_NOISE,

    // Medium performance mode.
    // Average configuration for performance/power consumption (without/with low noise version).
    TOMMRO_C_HW_DEVICES_DEF_OPERATING_MODE_MEDIUM_PERFORMANCE,
    TOMMRO_C_HW_DEVICES_DEF_OPERATING_MODE_MEDIUM_PERFORMANCE_LOW_NOISE,

    // Low performance mode.
    // Configuration for good power consumption/little care for performance (without/with low noise version).
    TOMMRO_C_HW_DEVICES_DEF_OPERATING_MODE_LOW_PERFORMANCE,
    TOMMRO_C_HW_DEVICES_DEF_OPERATING_MODE_LOW_PERFORMANCE_LOW_NOISE,

    // Low power mode.
    // Configuration for as minimum as possible power consumption/no care for performance (without/with low noise version).
    TOMMRO_C_HW_DEVICES_DEF_OPERATING_MODE_LOW_POWER,
    TOMMRO_C_HW_DEVICES_DEF_OPERATING_MODE_LOW_POWER_LOW_NOISE,

    // Power down/sleep mode.
    // If available, chip is set to power down/sleep
    TOMMRO_C_HW_DEVICES_DEF_OPERATING_MODE_POWER_DOWN,

} tommRoC_hw_devices_def_operating_mode_enum_t;

// Enumeration of tommRoC hardware devices conversion modes type.
typedef enum {

    // Conversion on demand mode.
    TOMMRO_C_HW_DEVICES_DEF_CONVERSION_MODE_ON_DEMAND = 0,

    // Conversion continuous.
    TOMMRO_C_HW_DEVICES_DEF_CONVERSION_CONTINUOUS,

} tommRoC_hw_mems_def_conversion_mode_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
