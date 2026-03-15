
#ifndef TOMMROC_HW_DEF_MEMS_H_
#define TOMMROC_HW_DEF_MEMS_H_

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
#include "DEF/MEMS/compass/tommRoCHwDEFMEMSCompass.h"
#include "DEF/MEMS/gravity/tommRoCHwDEFMEMSGravity.h"
#include "DEF/MEMS/gyro/tommRoCHwDEFMEMSGyro.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC hardware MEMS interrupt modes type.
typedef enum {

    // Interrupt are disabled.
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_DISABLED = 0,

    // Interrupt on data ready.
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_DATA_READY,

    // Interrupt on free fall (with different sensitivity).
    // Sensitivity maximum means that "a small force/movement" is needed to generate free fall condition.
    // Sensitivity minimum means that "a big force/movement" is needed to generate free fall condition.
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_MAXIMUM,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_HIGH_MAX_MAX,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_HIGH_MAX,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_HIGH_HIGH,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_HIGH,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_MEDIUM_HIGH_HIGH_HIGH,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_MEDIUM_HIGH_HIGH,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_MEDIUM_HIGH,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_MEDIUM,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_MEDIUM_LOW,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_MEDIUM_LOW_LOW,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_MEDIUM_LOW_LOW_LOW,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_LOW,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_LOW_LOW,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_LOW_MIN,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_LOW_MIN_MIN,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_FREE_FALL_SNSTVTY_MINIMUM,

    // Interrupt on motion (with different sensitivity).
    // Sensitivity maximum means that "a small force/movement" is needed to generate motion condition.
    // Sensitivity minimum means that "a big force/movement" is needed to generate motion condition.
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_MAXIMUM,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_HIGH_MAX_MAX,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_HIGH_MAX,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_HIGH_HIGH,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_HIGH,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_MEDIUM_HIGH_HIGH_HIGH,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_MEDIUM_HIGH_HIGH,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_MEDIUM_HIGH,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_MEDIUM,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_MEDIUM_LOW,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_MEDIUM_LOW_LOW,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_MEDIUM_LOW_LOW_LOW,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_LOW,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_LOW_LOW,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_LOW_MIN,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_LOW_MIN_MIN,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_MOTION_SNSTVTY_MINIMUM,

    // Interrupt on wake up (with different sensitivity).
    // Sensitivity maximum means that "a small force/movement" is needed to generate wake up condition.
    // Sensitivity minimum means that "a big force/movement" is needed to generate wake up condition.
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_MAXIMUM,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_HIGH_MAX_MAX,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_HIGH_MAX,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_HIGH_HIGH,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_HIGH,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_MEDIUM_HIGH_HIGH_HIGH,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_MEDIUM_HIGH_HIGH,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_MEDIUM_HIGH,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_MEDIUM,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_MEDIUM_LOW,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_MEDIUM_LOW_LOW,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_MEDIUM_LOW_LOW_LOW,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_LOW,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_LOW_LOW,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_LOW_MIN,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_LOW_MIN_MIN,
    TOMMRO_C_HW_DEF_MEMS_INTERRUPT_MODE_WAKEUP_SNSTVTY_MINIMUM,

} tommRoC_hw_mems_def_interrupt_mode_enum_t;


// tommRoC devices MEMS 3 axes float result structure.
typedef tommRoC_geometry_vector_t tommRoC_hw_mems_def_result_t;
#define __EMPTY_tommRoC_hw_mems_def_result_t__ __EMPTY_tommRoC_geometry_vector_t__

// tommRoC devices MEMS 3 axes signed 16-bit result structure.
typedef tommRoC_geometry_vector_16bit_t tommRoC_hw_mems_def_result_16bit_t;
#define __EMPTY_tommRoC_hw_mems_def_result_16bit_t__ __EMPTY_tommRoC_geometry_vector_16bit_t__

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
