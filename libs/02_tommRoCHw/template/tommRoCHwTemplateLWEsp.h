
#ifndef TOMMROC_HW_TEMPLATE_LWESP_H_
#define TOMMROC_HW_TEMPLATE_LWESP_H_

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
#include "TOMMROC.h"
#include "TOMMROCHw.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Start template LWEsp chip.
 *
 * param[in]        resetLow                set RESET pin low function pointer (NULL if none).
 * param[in]        resetHigh               set RESET pin high function pointer (NULL if none).
 * param[in]        baudRate                baud rate to be used [bit/sec]. If used 115200, nothing is changed.
 *                                          NOTE: on start, ESP32 has baud rate=115200. Then the used UART MUST start with baud rate=115200 and it will be configured using the bus set prop function.
 * param[in]        busHandlerPtr           bus pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       busDevicePtr            output bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspInit(
        const   tommRoC_hw_gpio_set_cb_t                        resetLow,
        const   tommRoC_hw_gpio_set_cb_t                        resetHigh,
        const   uint32_t                                        baudRate,
        const   tommRoC_hw_comm_hw_flow_control_enum_t          hwFlowControl,
        const   tommRoC_hw_bus_t*                       const   busHandlerPtr,
        const   tommRoC_guard_t*                        const   guardPtr,
                tommRoC_hw_bus_device_t*                const   busDevicePtr);

#endif
