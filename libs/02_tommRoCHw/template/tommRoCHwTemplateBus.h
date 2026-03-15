
#ifndef TOMMROC_HW_TEMPLATE_BUS_H_
#define TOMMROC_HW_TEMPLATE_BUS_H_

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
 *  - Hardware buses
 *      - __TOMMROC_HW_USE_I2C_MASTER_x_TEMPLATE__      hardware I2C master bus
 *      - __TOMMROC_HW_USE_I2C_SLAVE_x_TEMPLATE__       hardware I2C slave bus
 *      - __TOMMROC_HW_USE_SPI_MASTER_x_TEMPLATE__      hardware SPI master bus
 *      - __TOMMROC_HW_USE_SPI_SLAVE_x_TEMPLATE__       hardware SPI slave bus
 *      - __TOMMROC_HW_USE_UART_x_TEMPLATE__            hardware UART bus
 *      - __TOMMROC_HW_USE_LEUART_x_TEMPLATE__          hardware low power UART bus
 *
 *      - __TOMMROC_HW_USE_SPECIFIC_INTERRUPT_UART_x_TEMPLATE_TX_BUFFER_SIZE_BYTE__/__TOMMROC_HW_USE_SPECIFIC_INTERRUPT_LEUART_x_TEMPLATE_TX_BUFFER_SIZE_BYTE__
 *        if you want to use low level UART buffer to speed-up UART Tx ISR.
 *        NOTE: a good value is 256 Byte to have an effective baud-rate of about 98.4% of theoretical baud-rate (tested with an 3Mbit/s UART).
 *
 *      - __TOMMROC_HW_USE_UART_TEMPLATE_NOT_STANDARD_WORD_LENGTH_ENABLED__ if you want to support not standard (8-bit) long UART frame (typically 9-bit long UART frame).
 *
 *  - Software buses
 *      - __TOMMROC_HW_USE_I2C_MASTER_x_SW_TEMPLATE__   TommRoCHw software I2C master bus
 *      - __TOMMROC_HW_USE_SPI_MASTER_x_SW_TEMPLATE__   TommRoCHw software SPI master bus
 *      - __TOMMROC_HW_USE_UART_x_SW_TEMPLATE__         TommRoCHw software UART master bus
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/i2c/master/tommRoCHwTemplateBusI2CMaster.h"
#include "bus/i2c/slave/tommRoCHwTemplateBusI2CSlave.h"
#include "bus/spi/master/tommRoCHwTemplateBusSPIMaster.h"
#include "bus/spi/slave/tommRoCHwTemplateBusSPISlave.h"
#include "bus/uart/tommRoCHwTemplateBusUART.h"

#include "bus/i2c/master/sw/tommRoCHwTemplateBusI2CMasterSw.h"
#include "bus/spi/master/sw/tommRoCHwTemplateBusSPIMasterSw.h"
#include "bus/uart/sw/tommRoCHwTemplateBusUARTSw.h"

#include "TOMMROCHw.h"

/*******************************************************************************
 * defines
 ******************************************************************************/
#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)    ||  \
    defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__)   ||  \
    defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#define __TOMMROC_HW_TEMPLATE_BUS_AT_LEAST_ONE_IS_USED__
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Generic bus start function prototype.
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_template_bus_start_funct_t)(tommRoC_hw_bus_t* const busHandlePtr);

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
