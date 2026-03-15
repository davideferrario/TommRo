
#ifndef TOMMROC_HW_TEMPLATE_BUS_I2C_NXP_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_I2C_NXP_LOCATION_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#include "TOMMROCHw.h"
#include "TOMMROCHwTemplate.h"

#include "fsl_clock.h"
#if defined (FSL_FEATURE_SOC_GPIO_COUNT) && FSL_FEATURE_SOC_GPIO_COUNT
#include "fsl_gpio.h"
#endif
#if defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT
#include "fsl_syscon.h"
#endif
#if defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT
#include "fsl_iocon.h"
#endif
#if defined (FSL_FEATURE_SOC_PORT_COUNT) && FSL_FEATURE_SOC_PORT_COUNT
#include "fsl_port.h"
#endif

#include <stdbool.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
TOMMRO_C_UTIL_PACKED_PRE typedef struct TOMMRO_C_UTIL_PACKED_POST {

    clock_ip_name_t     clockName;

    // Configuration for setup bus
#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
    PORT_Type*          gpioSDAPort;
    uint32_t            gpioSDAPin;
    port_mux_t          gpioSDAPortMux;

    PORT_Type*          gpioSCLPort;
    uint32_t            gpioSCLPin;
    port_mux_t          gpioSCLPortMux;

#elif (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)
    uint8_t             sdaPortIdx;
    uint8_t             sdaPin;
    uint32_t            sdaIOCONFunc;

    uint8_t             sclPortIdx;
    uint8_t             sclPin;
    uint32_t            sclIOCONFunc;

#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
    bool                portSetPinSelectNeeded;
    port_module_t       portModule;
    port_pin_select_t   portPinSelect;
#endif

    // Configuration for setup as input GPIO (low power)
#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
    GPIO_Type*          gpioSDAGpio;
    GPIO_Type*          gpioSCLGpio;

#elif (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)
    GPIO_Type*          gpioSDAGpio;
    GPIO_Type*          gpioSCLGpio;

#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
    gpio_port_num_t     gpioSDAPort;
    uint8_t             gpioSDAPin;
    gpio_port_num_t     gpioSCLPort;
    uint8_t             gpioSCLPin;
#endif

} tommRoC_hw_template_bus_i2c_nxp_location_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNXPLocationGetMaster(
        const   tommRoC_hw_template_bus_i2c_master_enum_t               i2c,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_i2c_nxp_location_t*     const   locationConfigPtr);

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNXPLocationGetSlave(
        const   tommRoC_hw_template_bus_i2c_slave_enum_t                i2c,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_i2c_nxp_location_t*     const   locationConfigPtr);

#endif

#endif

#endif
