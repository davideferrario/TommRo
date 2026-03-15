
#ifndef TOMMROC_SW_TEMPLATE_ENTROPY_H_
#define TOMMROC_SW_TEMPLATE_ENTROPY_H_

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
 *  - __TOMMROC_SW_USE_ENTROPY_TEMPLATE__   TommRoCSw software entropy
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "TOMMROCSw.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
typedef uint8_t (*tommRoC_sw_template_entropy_u8_result_base_funct_t)(void);
typedef uint16_t (*tommRoC_sw_template_entropy_u16_result_base_funct_t)(void);
typedef uint32_t (*tommRoC_sw_template_entropy_u32_result_base_funct_t)(void);

/*******************************************************************************
 * functions
 ******************************************************************************/
 
tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyStart(void);
tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyStop(void);

tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyU8BaseFunct(
                uint8_t*                                            const   bufferPtr,
        const   uint32_t                                                    maxSize,
                uint32_t*                                           const   outLenPtr,
        const   tommRoC_sw_template_entropy_u8_result_base_funct_t          resultFunct);
tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyU16BaseFunct(
                uint8_t*                                            const   bufferPtr,
        const   uint32_t                                                    maxSize,
                uint32_t*                                           const   outLenPtr,
        const   tommRoC_sw_template_entropy_u16_result_base_funct_t         resultFunct);
tommRoC_sw_err_enum_t tommRoCSwTemplateEntropyU32BaseFunct(
                uint8_t*                                            const   bufferPtr,
        const   uint32_t                                                    maxSize,
                uint32_t*                                           const   outLenPtr,
        const   tommRoC_sw_template_entropy_u32_result_base_funct_t         resultFunct);

#endif
