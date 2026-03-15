
#ifndef TOMMROC_HW_TEMPLATE_BUS_SPI_EFM32G222_LOCATION_H_
#define TOMMROC_HW_TEMPLATE_BUS_SPI_EFM32G222_LOCATION_H_

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

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_EFM32G_IS_USED__)

#if (defined (USART_PRESENT) && USART_COUNT)
#include "em_usart.h"
#endif

/*******************************************************************************
 * defines
 ******************************************************************************/

#if defined (EFM32G222F128)         ||  \
    defined (EFM32G222F32)          ||  \
    defined (EFM32G222F64)

/******************* SPI0 location */

#define SPI_0_LOCATION_0_SCK_PORT           (gpioPortE)
#define SPI_0_LOCATION_0_SCK_PIN            (12)
#define SPI_0_LOCATION_0_MISO_PORT          (gpioPortE)
#define SPI_0_LOCATION_0_MISO_PIN           (11)
#define SPI_0_LOCATION_0_MOSI_PORT          (gpioPortE)
#define SPI_0_LOCATION_0_MOSI_PIN           (10)

#define SPI_0_LOCATION_2_SCK_PORT           (gpioPortC)
#define SPI_0_LOCATION_2_SCK_PIN            (9)
#define SPI_0_LOCATION_2_MISO_PORT          (gpioPortC)
#define SPI_0_LOCATION_2_MISO_PIN           (10)
#define SPI_0_LOCATION_2_MOSI_PORT          (gpioPortC)
#define SPI_0_LOCATION_2_MOSI_PIN           (11)


/******************* SPI1 location */

#define SPI_1_LOCATION_0_SCK_PORT           (gpioPortB)
#define SPI_1_LOCATION_0_SCK_PIN            (7)
#define SPI_1_LOCATION_0_MISO_PORT          (gpioPortC)
#define SPI_1_LOCATION_0_MISO_PIN           (1)
#define SPI_1_LOCATION_0_MOSI_PORT          (gpioPortC)
#define SPI_1_LOCATION_0_MOSI_PIN           (0)

#endif

#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
