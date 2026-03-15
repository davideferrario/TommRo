
#ifndef TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_SW_H_
#define TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_SW_H_

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

/*******************************************************************************
 * defines
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_SW_TEMPLATE__) ||    \
    defined (__TOMMROC_HW_USE_I2C_MASTER_1_SW_TEMPLATE__) ||    \
    defined (__TOMMROC_HW_USE_I2C_MASTER_2_SW_TEMPLATE__)       \

#define __TOMMROC_HW_AT_LEAST_ONE_I2C_MASTER_SW_TEMPLATE_IS_USED__

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

#if defined (__TOMMROC_HW_AT_LEAST_ONE_I2C_MASTER_SW_TEMPLATE_IS_USED__)

// I2C master software structure for init.
typedef struct {

    tommRoC_hw_gpio_set_cb_t    clkHigh;
    tommRoC_hw_gpio_set_cb_t    clkLow;
    tommRoC_hw_gpio_set_cb_t    dataHigh;
    tommRoC_hw_gpio_set_cb_t    dataLow;
    tommRoC_hw_gpio_get_cb_t    dataStatus;
    uint16_t                    baudRateKbits;

} tommRoC_hw_template_bus_i2c_master_sw_init_t;

#define __EMPTY_tommRoC_hw_template_bus_i2c_master_sw_init_t__      \
{                                                                   \
    /* .clkHigh */          NULL,                                   \
    /* .clkLow */           NULL,                                   \
    /* .dataHigh */         NULL,                                   \
    /* .dataLow */          NULL,                                   \
    /* .dataStatus */       NULL,                                   \
    /* .baudRateKbits */    0,                                      \
}

#endif


/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_SW_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CMaster0SwStart(
        const   tommRoC_hw_template_bus_i2c_master_sw_init_t*   const   swInitPtr,
                tommRoC_hw_bus_t*                               const   busHandlePtr);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_SW_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CMaster1SwStart(
        const   tommRoC_hw_template_bus_i2c_master_sw_init_t*   const   swInitPtr,
                tommRoC_hw_bus_t*                               const   busHandlePtr);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_SW_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CMaster2SwStart(
        const   tommRoC_hw_template_bus_i2c_master_sw_init_t*   const   swInitPtr,
                tommRoC_hw_bus_t*                               const   busHandlePtr);
#endif

#endif
