
#ifndef TOMMROC_HW_BUS_EXT_LINKED_H_
#define TOMMROC_HW_BUS_EXT_LINKED_H_

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
 * TommRoCHwBus extended linked bus.
 * Linking two buses means emulating a physical connection between two buses.
 * All the data written into one bus will be received by the other one and viceversa.
 *
 * NOTE: only one extended linked bus can be used.
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
 * Init extended linked buses.
 * NOTE: only one extended linked bus can be used.
 *
 * param[in]        type                    bus type.
 * param[in]        bus1RxBufferPtr         first bus receive buffer pointer.
 * param[in]        bus1RxBufferSize        first bus receive buffer size [byte].
 * param[out]       bus1Ptr                 first bus handle pointer.
 * param[in]        bus2RxBufferPtr         second bus receive buffer pointer.
 * param[in]        bus2RxBufferSize        second bus receive buffer size [byte].
 * param[out]       bus2Ptr                 second bus handle pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwBusExtLinkedInit(
        const   tommRoC_hw_bus_type_enum_t          type,
                uint8_t*                    const   bus1RxBufferPtr,
        const   uint16_t                            bus1RxBufferSize,
                tommRoC_hw_bus_t*           const   bus1Ptr,
                uint8_t*                    const   bus2RxBufferPtr,
        const   uint16_t                            bus2RxBufferSize,
                tommRoC_hw_bus_t*           const   bus2Ptr);

#endif
