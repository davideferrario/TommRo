
#ifndef TOMMROC_HW_TEMPLATE_BUS_SPI_MKE02Z4_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_SPI_MKE02Z4_LOCATION_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)

/*******************************************************************************
 * defines
 ******************************************************************************/

/******************* SPI0 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define SPI_0_LOCATION_0_CLOCK_NAME                         (kCLOCK_PortB)
#define SPI_0_LOCATION_0_SCK_PORT                           (PORTB)
#define SPI_0_LOCATION_0_SCK_PIN                            (2U)
#define SPI_0_LOCATION_0_SCK_PORT_MUX                       (kPORT_MuxAlt2)
#define SPI_0_LOCATION_0_MISO_PORT                          (PORTB)
#define SPI_0_LOCATION_0_MISO_PIN                           (4U)
#define SPI_0_LOCATION_0_MISO_PORT_MUX                      (kPORT_MuxAlt2)
#define SPI_0_LOCATION_0_MOSI_PORT                          (PORTB)
#define SPI_0_LOCATION_0_MOSI_PIN                           (3U)
#define SPI_0_LOCATION_0_MOSI_PORT_MUX                      (kPORT_MuxAlt2)

#define SPI_0_LOCATION_0_SCK_GPIO                           (GPIOB)
#define SPI_0_LOCATION_0_MISO_GPIO                          (GPIOB)
#define SPI_0_LOCATION_0_MOSI_GPIO                          (GPIOB)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
#define SPI_0_LOCATION_0_CLOCK_NAME                         (kCLOCK_Spi0)
#define SPI_0_LOCATION_0_PORT_SET_PIN_SELECT_NEEDED         (true)
#define SPI_0_LOCATION_0_PORT_MODULE                        (kPORT_SPI0)
#define SPI_0_LOCATION_0_PORT_PIN_SELECT                    (kPORT_SPI0_SCKPTB2_MOSIPTB3_MISOPTB4_PCSPTB5)

#define SPI_0_LOCATION_0_SCK_PORT                           (kGPIO_PORTB)
#define SPI_0_LOCATION_0_SCK_PIN                            (2U)
#define SPI_0_LOCATION_0_MISO_PORT                          (kGPIO_PORTB)
#define SPI_0_LOCATION_0_MISO_PIN                           (4U)
#define SPI_0_LOCATION_0_MOSI_PORT                          (kGPIO_PORTB)
#define SPI_0_LOCATION_0_MOSI_PIN                           (3U)
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define SPI_0_LOCATION_1_CLOCK_NAME                         (kCLOCK_PortE)
#define SPI_0_LOCATION_1_SCK_PORT                           (PORTE)
#define SPI_0_LOCATION_1_SCK_PIN                            (0U)
#define SPI_0_LOCATION_1_SCK_PORT_MUX                       (kPORT_MuxAlt2)
#define SPI_0_LOCATION_1_MISO_PORT                          (PORTE)
#define SPI_0_LOCATION_1_MISO_PIN                           (2U)
#define SPI_0_LOCATION_1_MISO_PORT_MUX                      (kPORT_MuxAlt2)
#define SPI_0_LOCATION_1_MOSI_PORT                          (PORTE)
#define SPI_0_LOCATION_1_MOSI_PIN                           (1U)
#define SPI_0_LOCATION_1_MOSI_PORT_MUX                      (kPORT_MuxAlt2)

#define SPI_0_LOCATION_1_SCK_GPIO                           (GPIOE)
#define SPI_0_LOCATION_1_MISO_GPIO                          (GPIOE)
#define SPI_0_LOCATION_1_MOSI_GPIO                          (GPIOE)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
#define SPI_0_LOCATION_1_CLOCK_NAME                         (kCLOCK_Spi0)
#define SPI_0_LOCATION_1_PORT_SET_PIN_SELECT_NEEDED         (true)
#define SPI_0_LOCATION_1_PORT_MODULE                        (kPORT_SPI0)
#define SPI_0_LOCATION_1_PORT_PIN_SELECT                    (kPORT_SPI0_SCKPTE0_MOSIPTE1_MISOPTE2_PCSPTE3)

#define SPI_0_LOCATION_1_SCK_PORT                           (kGPIO_PORTE)
#define SPI_0_LOCATION_1_SCK_PIN                            (0U)
#define SPI_0_LOCATION_1_MISO_PORT                          (kGPIO_PORTE)
#define SPI_0_LOCATION_1_MISO_PIN                           (2U)
#define SPI_0_LOCATION_1_MOSI_PORT                          (kGPIO_PORTE)
#define SPI_0_LOCATION_1_MOSI_PIN                           (1U)
#endif

/******************* SPI1 location */

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define SPI_1_LOCATION_0_CLOCK_NAME                         (kCLOCK_PortD)
#define SPI_1_LOCATION_0_SCK_PORT                           (PORTD)
#define SPI_1_LOCATION_0_SCK_PIN                            (0U)
#define SPI_1_LOCATION_0_SCK_PORT_MUX                       (kPORT_MuxAlt3)
#define SPI_1_LOCATION_0_MISO_PORT                          (PORTD)
#define SPI_1_LOCATION_0_MISO_PIN                           (2U)
#define SPI_1_LOCATION_0_MISO_PORT_MUX                      (kPORT_MuxAlt2)
#define SPI_1_LOCATION_0_MOSI_PORT                          (PORTD)
#define SPI_1_LOCATION_0_MOSI_PIN                           (1U)
#define SPI_1_LOCATION_0_MOSI_PORT_MUX                      (kPORT_MuxAlt3)

#define SPI_1_LOCATION_0_SCK_GPIO                           (GPIOD)
#define SPI_1_LOCATION_0_MISO_GPIO                          (GPIOD)
#define SPI_1_LOCATION_0_MOSI_GPIO                          (GPIOD)
#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
#define SPI_1_LOCATION_0_CLOCK_NAME                         (kCLOCK_Spi1)
#define SPI_1_LOCATION_0_PORT_SET_PIN_SELECT_NEEDED         (false)
#define SPI_1_LOCATION_0_PORT_MODULE                        (0)
#define SPI_1_LOCATION_0_PORT_PIN_SELECT                    (0)

#define SPI_1_LOCATION_0_SCK_PORT                           (kGPIO_PORTD)
#define SPI_1_LOCATION_0_SCK_PIN                            (0U)
#define SPI_1_LOCATION_0_MISO_PORT                          (kGPIO_PORTD)
#define SPI_1_LOCATION_0_MISO_PIN                           (2U)
#define SPI_1_LOCATION_0_MOSI_PORT                          (kGPIO_PORTD)
#define SPI_1_LOCATION_0_MOSI_PIN                           (1U)
#endif

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
