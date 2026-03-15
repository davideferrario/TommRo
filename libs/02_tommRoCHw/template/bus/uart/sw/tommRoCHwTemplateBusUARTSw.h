
#ifndef TOMMROC_HW_TEMPLATE_BUS_UART_SW_H_
#define TOMMROC_HW_TEMPLATE_BUS_UART_SW_H_

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
#include "tommRoCHwTemplateBusUARTSwDEF.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// UART software structure for init.
typedef struct {

    tommRoC_hw_gpio_set_cb_t    txHigh;
    tommRoC_hw_gpio_set_cb_t    txLow;
    tommRoC_hw_gpio_get_cb_t    rxStatus;

    uint8_t                     dataBitAmount;
    uint32_t                    baudRateBPS;

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
    bool                        useHwTimer;
#endif

} tommRoC_hw_template_bus_uart_sw_init_t;

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#define __EMPTY_tommRoC_hw_template_bus_uart_sw_init_t__                            \
{                                                                                   \
    /* .txHigh */           NULL,                                                   \
    /* .txLow */            NULL,                                                   \
    /* .rxStatus */         NULL,                                                   \
    /* .dataBitAmount */    TOMMROC_UNIT_MEASURE_BYTE_TO_BIT(TOMMROC_UTIL_U8_SIZE), \
    /* .baudRateBPS */      9600,                                                   \
    /* .useHwTimer */       true,                                                   \
}
#else
#define __EMPTY_tommRoC_hw_template_bus_uart_sw_init_t__                            \
{                                                                                   \
    /* .txHigh */           NULL,                                                   \
    /* .txLow */            NULL,                                                   \
    /* .rxStatus */         NULL,                                                   \
    /* .dataBitAmount */    TOMMROC_UNIT_MEASURE_BYTE_TO_BIT(TOMMROC_UTIL_U8_SIZE), \
    /* .baudRateBPS */      9600,                                                   \
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUART0SwStart(
        const   tommRoC_hw_template_bus_uart_sw_init_t* const   swInitPtr,
                tommRoC_hw_bus_t*                       const   busHandlePtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUART1SwStart(
        const   tommRoC_hw_template_bus_uart_sw_init_t* const   swInitPtr,
                tommRoC_hw_bus_t*                       const   busHandlePtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUART2SwStart(
        const   tommRoC_hw_template_bus_uart_sw_init_t* const   swInitPtr,
                tommRoC_hw_bus_t*                       const   busHandlePtr);

#endif
