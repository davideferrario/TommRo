
#ifndef TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_H_
#define TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_H_

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
#include "tommRoCHwTemplateBusSPIMasterDEF.h"

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
 * Set a property for a bus SPI master.
 * Notes:   MUST be called before start function.
 */
tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMasterSetProp(
        const   tommRoC_hw_template_bus_spi_master_prop_enum_t          property,
        const   tommRoC_hw_template_bus_spi_master_enum_t               bus,
        const   void*                                           const   propValuePtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMaster0Start(tommRoC_hw_bus_t* const busHandlePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMaster1Start(tommRoC_hw_bus_t* const busHandlePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMaster2Start(tommRoC_hw_bus_t* const busHandlePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMaster3Start(tommRoC_hw_bus_t* const busHandlePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMaster4Start(tommRoC_hw_bus_t* const busHandlePtr);
tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMaster5Start(tommRoC_hw_bus_t* const busHandlePtr);

#endif
