
#ifndef TOMMROC_SW_ENTROPY_H_
#define TOMMROC_SW_ENTROPY_H_

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
#include "tommRoCSwErr.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC secure layer entropy source type.
// NOTE: at least one strong source needs to be added.
//       Weaker sources (such as the cycle counter) can be used as a complement.
typedef enum {

    // Entropy source is strong.
    TOMMRO_C_SW_ENTROPY_SOURCE_STRONG = 0,

    // Entropy source is weak.
    TOMMRO_C_SW_ENTROPY_SOURCE_WEAK,

} tommRoC_sw_entropy_source_type_enum_t;


/**
 * Entropy callback type.
 *
 * param[in]        bufferPtr               buffer to fill.
 * param[in]        maxSize                 buffer max size.
 * param[out]       outLenPtr               actual amount of bytes put into the buffer.
 *
 * return tommRoC_sw_err_enum_t
 */
typedef tommRoC_sw_err_enum_t (*tommRoC_sw_entropy_funct_t)(uint8_t* const bufferPtr, const uint32_t maxSize, uint32_t* const outLenPtr);

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Start entropy software framework.
 *
 * return tommRoC_sw_err_enum_t
 */
tommRoC_sw_err_enum_t tommRoCSwEntropyStart(void);

/**
 * Stop entropy software framework.
 *
 * return tommRoC_sw_err_enum_t
 */
tommRoC_sw_err_enum_t tommRoCSwEntropyStop(void);

/**
 * Adds an entropy software source to framework.
 *
 * param[in]        sourceFunct             entropy callback function.
 * param[in]        threshold               minimum required from source before entropy is released.
 * param[in]        sourceType              entropy source type.
 *
 * return tommRoC_sw_err_enum_t
 */
tommRoC_sw_err_enum_t tommRoCSwEntropyAddSource(
        const   tommRoC_sw_entropy_funct_t              sourceFunct,
        const   uint32_t                                threshold,
        const   tommRoC_sw_entropy_source_type_enum_t   sourceType);

/**
 * Trigger an extra gather poll for the framework.
 *
 * return tommRoC_sw_err_enum_t
 */
tommRoC_sw_err_enum_t tommRoCSwEntropyGather(void);

#endif
