
#ifndef TOMMROC_HW_BUS_EXT_DOUBLE_H_
#define TOMMROC_HW_BUS_EXT_DOUBLE_H_

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
 *
 * TommRoCHwBus extended double bus.
 * A double bus is a bus linked to two physical buses.
 * All the data written into the double bus will be written on both physical buses
 * and all the data received from both physical buses can be received from double bus.
 *
 * NOTE: only one extended double bus can be used.
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwBus.h"
#include "tommRoCHwErr.h"

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
 * Init extended double buses.
 * NOTE: only one extended double bus can be used.
 *
 * param[in]        type                    bus type.
 * param[in]        bus1Ptr                 first bus handle pointer.
 * param[in]        bus2Ptr                 second bus handle pointer.
 * param[out]       bus2Ptr                 bus handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusExtDoubleInit(
        const   tommRoC_hw_bus_type_enum_t          type,
        const   tommRoC_hw_bus_t*           const   bus1Ptr,
        const   tommRoC_hw_bus_t*           const   bus2Ptr,
                tommRoC_hw_bus_t*           const   busPtr);

#endif
