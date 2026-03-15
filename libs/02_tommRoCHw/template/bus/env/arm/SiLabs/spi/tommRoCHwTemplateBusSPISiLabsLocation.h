
#ifndef TOMMROC_HW_TEMPLATE_BUS_SPI_SILABS_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_SPI_SILABS_LOCATION_H_

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

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)

#include "TOMMROCHw.h"
#include "TOMMROCHwTemplate.h"

#include "em_gpio.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
TOMMRO_C_UTIL_PACKED_PRE typedef struct TOMMRO_C_UTIL_PACKED_POST {

#if defined (_USART_ROUTE_LOCATION_MASK)
    uint32_t            locationU32;
#endif

    GPIO_Port_TypeDef   gpioSCKPort;
    uint32_t            gpioSCKPin;

    GPIO_Port_TypeDef   gpioMISOPort;
    uint32_t            gpioMISOPin;
    
    GPIO_Port_TypeDef   gpioMOSIPort;
    uint32_t            gpioMOSIPin;    

} tommRoC_hw_template_bus_spi_silabs_location_t;

#if defined (_USART_ROUTE_LOCATION_MASK)
#define __EMPTY_tommRoC_hw_template_bus_spi_silabs_location_t__ \
{                                                               \
    /* .locationU32 */  USART_ROUTE_LOCATION_LOC0,              \
    /* .gpioSCKPort */  gpioPortA,                              \
    /* .gpioSCKPin */   0,                                      \
    /* .gpioMISOPort */ gpioPortA,                              \
    /* .gpioMISOPin */  0,                                      \
    /* .gpioMOSIPort */ gpioPortA,                              \
    /* .gpioMOSIPin */  0,                                      \
}
#else

#define __EMPTY_tommRoC_hw_template_bus_spi_silabs_location_t__ \
{                                                               \
    /* .gpioSCKPort */  gpioPortA,                              \
    /* .gpioSCKPin */   0,                                      \
    /* .gpioMISOPort */ gpioPortA,                              \
    /* .gpioMISOPin */  0,                                      \
    /* .gpioMOSIPort */ gpioPortA,                              \
    /* .gpioMOSIPin */  0,                                      \
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISiLabsLocationGetMaster(
        const   tommRoC_hw_template_bus_spi_master_enum_t               spi,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_spi_silabs_location_t*  const   locationConfigPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISiLabsLocationGetSlave(
        const   tommRoC_hw_template_bus_spi_slave_enum_t                spi,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_spi_silabs_location_t*  const   locationConfigPtr);

#endif

#endif

#endif
