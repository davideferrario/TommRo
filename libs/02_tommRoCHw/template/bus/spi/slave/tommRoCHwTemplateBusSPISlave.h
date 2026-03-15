
#ifndef TOMMROC_HW_TEMPLATE_BUS_SPI_SLAVE_H_
#define TOMMROC_HW_TEMPLATE_BUS_SPI_SLAVE_H_

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

#include "tommRoCHwTemplateBusSpecific.h"
#include "tommRoCHwTemplateBusSPISlaveDEF.h"

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
 * Set a property for a bus SPI slave.
 * Notes:   MUST be called before start function.
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISlaveSetProp(
        const   tommRoC_hw_template_bus_spi_slave_prop_enum_t           property,
        const   tommRoC_hw_template_bus_spi_slave_enum_t                bus,
        const   void*                                           const   propValuePtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISlave0Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISlave1Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISlave2Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISlave3Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISlave4Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISlave5Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr);

#endif
