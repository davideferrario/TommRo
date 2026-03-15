
#ifndef TOMMROC_HW_TEMPLATE_BUS_SPECIFIC_H_
#define TOMMROC_HW_TEMPLATE_BUS_SPECIFIC_H_

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
#include <stddef.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef enum {

    TOMMROC_HW_TEMPLATE_LOCATION_0 = 0,
    TOMMROC_HW_TEMPLATE_LOCATION_1,
    TOMMROC_HW_TEMPLATE_LOCATION_2,
    TOMMROC_HW_TEMPLATE_LOCATION_3,
    TOMMROC_HW_TEMPLATE_LOCATION_4,
    TOMMROC_HW_TEMPLATE_LOCATION_5,
    TOMMROC_HW_TEMPLATE_LOCATION_6,

} tommRoC_hw_template_bus_location_enum_t;

/*******************************************************************************
 * typedefs - I2C Master template bus specific
 ******************************************************************************/

/**
 * I2C master bus.
 */
typedef enum {

    TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_0 = 0,
    TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_1,
    TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_2,
    TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_3,
    TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_4,
    TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_5,

} tommRoC_hw_template_bus_i2c_master_enum_t;


/**
 * I2C master property.
 */
typedef enum {

    /**
     * I2C baud rate property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be uint32_t*
     */
    TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_BAUD_RATE = 0,

    /**
     * I2C location property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_template_bus_location_enum_t*
     */
    TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_LOCATION,

    /**
     * I2C MCU pull up status (enabled/disabled) property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_util_enabled_status_enum_t*
     */
    TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_MCU_PULL_UP_STATUS,

    /**
     * I2C SDA/SCL port property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be void* (cast is needed in low level routine).
     *                  - GPIO_Port_TypeDef* for ARM SiLabs EFR32 environment.
     */
    TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_SDA_PORT,
    TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_SCL_PORT,

    /**
     * I2C SDA/SCL pin property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be void* (cast is needed in low level routine).
     *                  - gpio_num_t* for ESP32 environment.
     *                  - uint32_t* for ARM Nordic environment.
     *                  - uint32_t* for ARM SiLabs EFR32 environment.
     */
    TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_SDA_PIN,
    TOMMRO_C_HW_TEMPLATE_BUS_I2C_MASTER_PROP_SCL_PIN,

} tommRoC_hw_template_bus_i2c_master_prop_enum_t;

/*******************************************************************************
 * typedefs - I2C Slave template bus specific
 ******************************************************************************/

/**
 * I2C slave bus.
 */
typedef enum {

    TOMMROC_HW_TEMPLATE_BUS_I2C_SLAVE_0 = 0,
    TOMMROC_HW_TEMPLATE_BUS_I2C_SLAVE_1,
    TOMMROC_HW_TEMPLATE_BUS_I2C_SLAVE_2,
    TOMMROC_HW_TEMPLATE_BUS_I2C_SLAVE_3,
    TOMMROC_HW_TEMPLATE_BUS_I2C_SLAVE_4,
    TOMMROC_HW_TEMPLATE_BUS_I2C_SLAVE_5,

} tommRoC_hw_template_bus_i2c_slave_enum_t;


/**
 * I2C slave property.
 */
typedef enum {

    EMPTY_I2C_SLAVE = 0,

} tommRoC_hw_template_bus_i2c_slave_prop_enum_t;

/*******************************************************************************
 * typedefs - SPI Master template bus specific
 ******************************************************************************/

/**
 * SPI master bus.
 */
typedef enum {

    TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0 = 0,
    TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1,
    TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_2,
    TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_3,
    TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_4,
    TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_5,

} tommRoC_hw_template_bus_spi_master_enum_t;


/**
 * SPI mode.
 * SPI clock polarity (CPOL) and clock phase (CPHA) can be specified as '0' or '1' to
 * form 4 unique modes.
 *
 * Mode 0:
 * -------
 * CPOL = '0'; CPHA = '0'.
 * Data is sampled at the leading (first) rising edge of the clock.
 *
 * Mode 1:
 * -------
 * CPOL = '0'; CPHA = '1'.
 * Data is sampled at the trailing (second) falling edge of the clock.
 *
 * Mode 2:
 * -------
 * CPOL is '1'; CPHA is '0'.
 * Data is sampled at the leading (first) falling edge of the clock.
 *
 * Mode 3:
 * -------
 * CPOL = '1'; CPHA = '1'.
 * Data is sampled on the trailing (second) rising edge of the clock.
 */
typedef enum {

    TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_0 = 0,
    TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_1,
    TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_2,
    TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_3,

} tommRoC_hw_template_bus_spi_master_mode_t;


/**
 * SPI master property.
 */
typedef enum {

    /**
     * SPI master mode property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_template_bus_spi_master_mode_t*
     */
    TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_MODE = 0,

    /**
     * SPI baud rate property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be uint32_t*
     */
    TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_BAUD_RATE,

    /**
     * SPI location property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_template_bus_location_enum_t*
     */
    TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_LOCATION,

    /**
     * SPI SCK/MISO/MOSI port property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be void* (cast is needed in low level routine).
     *                  - GPIO_Port_TypeDef* for ARM SiLabs EFR32 environment.
     */
    TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_SCK_PORT,
    TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_MISO_PORT,
    TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_MOSI_PORT,

    /**
     * SPI SCK/MISO/MOSI pin property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be void* (cast is needed in low level routine).
     *                  - gpio_num_t* for ESP32 environment.
     *                  - uint8_t* for ARM Nordic environment.
     */
    TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_SCK_PIN,
    TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_MISO_PIN,
    TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_MOSI_PIN,

} tommRoC_hw_template_bus_spi_master_prop_enum_t;

/*******************************************************************************
 * typedefs - SPI Slave template bus specific
 ******************************************************************************/

/**
 * SPI slave bus.
 */
typedef enum {

    TOMMROC_HW_TEMPLATE_BUS_SPI_SLAVE_0 = 0,
    TOMMROC_HW_TEMPLATE_BUS_SPI_SLAVE_1,
    TOMMROC_HW_TEMPLATE_BUS_SPI_SLAVE_2,
    TOMMROC_HW_TEMPLATE_BUS_SPI_SLAVE_3,
    TOMMROC_HW_TEMPLATE_BUS_SPI_SLAVE_4,
    TOMMROC_HW_TEMPLATE_BUS_SPI_SLAVE_5,

} tommRoC_hw_template_bus_spi_slave_enum_t;


/**
 * SPI slave property.
 */
typedef enum {

    EMPTY_SPI_SLAVE = 0,

} tommRoC_hw_template_bus_spi_slave_prop_enum_t;

/*******************************************************************************
 * typedefs - UART template bus specific
 ******************************************************************************/

/**
 * UART bus.
 */
typedef enum {

    TOMMROC_HW_TEMPLATE_BUS_UART_0 = 0,
    TOMMROC_HW_TEMPLATE_BUS_UART_1,
    TOMMROC_HW_TEMPLATE_BUS_UART_2,
    TOMMROC_HW_TEMPLATE_BUS_UART_3,
    TOMMROC_HW_TEMPLATE_BUS_UART_4,
    TOMMROC_HW_TEMPLATE_BUS_UART_5,
    TOMMROC_HW_TEMPLATE_BUS_UART_6,
    TOMMROC_HW_TEMPLATE_BUS_UART_7,
    TOMMROC_HW_TEMPLATE_BUS_UART_8,

    TOMMROC_HW_TEMPLATE_BUS_LEUART_0,
    TOMMROC_HW_TEMPLATE_BUS_LEUART_1,

} tommRoC_hw_template_bus_uart_enum_t;

/**
 * UART buffer struct.
 */
typedef struct {

    uint8_t*    txBufferPtr;
    uint16_t    txBufferSize;

    uint8_t*    rxBufferPtr;
    uint16_t    rxBufferSize;

} tommRoC_hw_template_bus_uart_buffer_t;

#define __EMPTY_tommRoC_hw_template_bus_uart_buffer_t__ \
{                                                       \
    /* .txBufferPtr */  NULL,                           \
    /* .txBufferSize */ 0,                              \
    /* .rxBufferPtr */  NULL,                           \
    /* .rxBufferSize */ 0,                              \
}


/**
 * UART property.
 */
typedef enum {

    /**
     * UART transmit/receive buffer property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_template_bus_uart_buffer_t*
     */
    TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_BUFFER = 0,

    /**
     * UART transmit/receive buffer size [byte] property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be uint16_t*
     */
    TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_TX_BUFFER_SIZE,
    TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_RX_BUFFER_SIZE,

    /**
     * UART baud rate property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be uint32_t*
     */
    TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_BAUD_RATE,

    /**
     * UART location property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be tommRoC_hw_template_bus_location_enum_t*
     */
    TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_LOCATION,

    /**
     * UART device name string property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be char* NULL ('\0') terminated.
     */
    TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_DEVICE_NAME_STRING,

    /**
     * UART TX/RX port property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be void* (cast is needed in low level routine).
     *                  - GPIO_Port_TypeDef* for ARM SiLabs EFR32 environment.
     */
    TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_TX_PORT,
    TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_RX_PORT,

    /**
     * UART TX/RX pin property.
     *
     * Available:   set
     * Notes:       propValuePtr has to be void* (cast is needed in low level routine).
     *                  - gpio_num_t* for ESP32 environment.
     *                  - uint32_t* for ARM Nordic environment.
     *                  - uint32_t* for ARM SiLabs EFR32 environment.
     */
    TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_TX_PIN,
    TOMMRO_C_HW_TEMPLATE_BUS_UART_PROP_RX_PIN,

} tommRoC_hw_template_bus_uart_prop_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
