
#ifndef TOMMROC_HW_TEMPLATE_BUS_SPI_MKWx1Z_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_SPI_MKWx1Z_LOCATION_H_

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
#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************* SPI0 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define SPI_0_LOCATION_0_CLOCK_NAME                         (kCLOCK_PortC)
#define SPI_0_LOCATION_0_SCK_PORT                           (PORTC)
#define SPI_0_LOCATION_0_SCK_PIN                            (16U)
#define SPI_0_LOCATION_0_SCK_PORT_MUX                       (kPORT_MuxAlt2)
#define SPI_0_LOCATION_0_MISO_PORT                          (PORTC)
#define SPI_0_LOCATION_0_MISO_PIN                           (18U)
#define SPI_0_LOCATION_0_MISO_PORT_MUX                      (kPORT_MuxAlt2)
#define SPI_0_LOCATION_0_MOSI_PORT                          (PORTC)
#define SPI_0_LOCATION_0_MOSI_PIN                           (17U)
#define SPI_0_LOCATION_0_MOSI_PORT_MUX                      (kPORT_MuxAlt2)

#define SPI_0_LOCATION_0_SCK_GPIO                           (GPIOC)
#define SPI_0_LOCATION_0_MISO_GPIO                          (GPIOC)
#define SPI_0_LOCATION_0_MOSI_GPIO                          (GPIOC)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#endif

/******************* SPI1 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define SPI_1_LOCATION_0_CLOCK_NAME                         (kCLOCK_PortA)
#define SPI_1_LOCATION_0_SCK_PORT                           (PORTA)
#define SPI_1_LOCATION_0_SCK_PIN                            (18U)
#define SPI_1_LOCATION_0_SCK_PORT_MUX                       (kPORT_MuxAlt2)
#define SPI_1_LOCATION_0_MISO_PORT                          (PORTA)
#define SPI_1_LOCATION_0_MISO_PIN                           (17U)
#define SPI_1_LOCATION_0_MISO_PORT_MUX                      (kPORT_MuxAlt2)
#define SPI_1_LOCATION_0_MOSI_PORT                          (PORTA)
#define SPI_1_LOCATION_0_MOSI_PIN                           (16U)
#define SPI_1_LOCATION_0_MOSI_PORT_MUX                      (kPORT_MuxAlt2)

#define SPI_1_LOCATION_0_SCK_GPIO                           (GPIOA)
#define SPI_1_LOCATION_0_MISO_GPIO                          (GPIOA)
#define SPI_1_LOCATION_0_MOSI_GPIO                          (GPIOA)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION)
#endif

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
