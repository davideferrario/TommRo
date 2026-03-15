
#ifndef TOMMROC_HW_TEMPLATE_BUS_ENVIRONMENT_SPI_SLAVE_H_
#define TOMMROC_HW_TEMPLATE_BUS_ENVIRONMENT_SPI_SLAVE_H_

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
#include "TOMMROCHw.h"

#include "tommRoCHwTemplateBusSpecific.h"

#include "bus/spi/slave/tommRoCHwTemplateBusSPISlaveDEF.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_SLAVE_DEF_AT_LEAST_ONE_IS_USED__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPISlaveSetProp(
        const   tommRoC_hw_template_bus_spi_slave_prop_enum_t           property,
        const   tommRoC_hw_template_bus_spi_slave_enum_t                bus,
        const   void*                                           const   propValuePtr);
#endif

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_0_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPISlave0Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr);
#endif

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPISlave1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr);
#endif

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPISlave2Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr);
#endif

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_3_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPISlave3Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr);
#endif

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_4_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPISlave4Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr);
#endif

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_5_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPISlave5Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr);
#endif

#endif
