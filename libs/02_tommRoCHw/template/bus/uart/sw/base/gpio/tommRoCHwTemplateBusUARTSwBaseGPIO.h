
#ifndef TOMMROC_HW_TEMPLATE_BUS_UART_SW_BASE_GPIO_H_
#define TOMMROC_HW_TEMPLATE_BUS_UART_SW_BASE_GPIO_H_

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
#include <stdint.h>

#include "TOMMROC.h"
#include "TOMMROCHw.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef struct {

    tommRoC_hw_gpio_set_cb_t    txHigh;
    tommRoC_hw_gpio_set_cb_t    txLow;
    tommRoC_hw_gpio_get_cb_t    rxStatus;
    uint8_t                     dataBitAmount;
    uint32_t                    baseDelayUsec;

} tommRoC_hw_template_bus_uart_sw_base_gpio_t;

#define __EMPTY_tommRoC_hw_template_bus_uart_sw_base_gpio_t__                       \
{                                                                                   \
    /* .txHigh */           NULL,                                                   \
    /* .txLow */            NULL,                                                   \
    /* .rxStatus */         NULL,                                                   \
    /* .dataBitAmount */    TOMMROC_UNIT_MEASURE_BYTE_TO_BIT(TOMMROC_UTIL_U8_SIZE), \
    /* .baseDelayUsec */    0,                                                      \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
