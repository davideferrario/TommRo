
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusSPISiLabsLocation.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_EFM32G_IS_USED__)
#include "bus/env/arm/SiLabs/spi/EFM32G/tommRoCHwTemplateBusSPIEFM32GLocation.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_EFM32GG_IS_USED__)
#include "bus/env/arm/SiLabs/spi/EFM32GG/tommRoCHwTemplateBusSPIEFM32GGLocation.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_EFR32_IS_USED__)
#include "bus/env/arm/SiLabs/spi/EFR32/tommRoCHwTemplateBusSPIEFR32Location.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/

#if defined (_USART_ROUTE_LOCATION_MASK)
#define __LOCATION_ENUM_ERROR__                 ((uint32_t) -1)

#define __CHECK_LOCATION__(SPI, SPI_TYPE, LOCATION)                                                                     \
        do {                                                                                                            \
            if ((TOMMROC_HW_TEMPLATE_BUS_ ## SPI_TYPE == spi) && (TOMMROC_HW_TEMPLATE_ ## LOCATION == location)) {      \
                                                                                                                        \
                locationConfigPtr->gpioSCKPort      = SPI ## _ ## LOCATION ## _SCK_PORT;                                \
                locationConfigPtr->gpioSCKPin       = SPI ## _ ## LOCATION ## _SCK_PIN;                                 \
                locationConfigPtr->gpioMISOPort     = SPI ## _ ## LOCATION ## _MISO_PORT;                               \
                locationConfigPtr->gpioMISOPin      = SPI ## _ ## LOCATION ## _MISO_PIN;                                \
                locationConfigPtr->gpioMOSIPort     = SPI ## _ ## LOCATION ## _MOSI_PORT;                               \
                locationConfigPtr->gpioMOSIPin      = SPI ## _ ## LOCATION ## _MOSI_PIN;                                \
                                                                                                                        \
                return TOMMRO_C_HW_ERR_SUCCESS;                                                                         \
            }                                                                                                           \
        } while (0)
#endif

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/

#if defined (_USART_ROUTE_LOCATION_MASK)
static uint32_t _convert_spi_location(
        const   tommRoC_hw_template_bus_location_enum_t location) {

    switch (location) {

#if defined (USART_ROUTE_LOCATION_LOC0)
    case TOMMROC_HW_TEMPLATE_LOCATION_0:    return USART_ROUTE_LOCATION_LOC0;
#endif
#if defined (USART_ROUTE_LOCATION_LOC1)
    case TOMMROC_HW_TEMPLATE_LOCATION_1:    return USART_ROUTE_LOCATION_LOC1;
#endif
#if defined (USART_ROUTE_LOCATION_LOC2)
    case TOMMROC_HW_TEMPLATE_LOCATION_2:    return USART_ROUTE_LOCATION_LOC2;
#endif
#if defined (USART_ROUTE_LOCATION_LOC3)
    case TOMMROC_HW_TEMPLATE_LOCATION_3:    return USART_ROUTE_LOCATION_LOC3;
#endif
#if defined (USART_ROUTE_LOCATION_LOC4)
    case TOMMROC_HW_TEMPLATE_LOCATION_4:    return USART_ROUTE_LOCATION_LOC4;
#endif
#if defined (USART_ROUTE_LOCATION_LOC5)
    case TOMMROC_HW_TEMPLATE_LOCATION_5:    return USART_ROUTE_LOCATION_LOC5;
#endif
#if defined (USART_ROUTE_LOCATION_LOC6)
    case TOMMROC_HW_TEMPLATE_LOCATION_6:    return USART_ROUTE_LOCATION_LOC6;
#endif

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;
    }

    return __LOCATION_ENUM_ERROR__;
}

static tommRoC_hw_err_enum_t _set_gpio_pin_spi_master(
        const   tommRoC_hw_template_bus_spi_master_enum_t               spi,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_spi_silabs_location_t*  const   locationConfigPtr) {

    // To avoid warning if no one is used
    TOMMROC_UTIL_UNUSED_PARAM(spi);
    TOMMROC_UTIL_UNUSED_PARAM(location);
    TOMMROC_UTIL_UNUSED_PARAM(locationConfigPtr);


#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
#if defined (SPI_0_LOCATION_0_SCK_PORT)
    __CHECK_LOCATION__(SPI_0, SPI_MASTER_0, LOCATION_0);
#endif
#if defined (SPI_0_LOCATION_1_SCK_PORT)
    __CHECK_LOCATION__(SPI_0, SPI_MASTER_0, LOCATION_1);
#endif
#if defined (SPI_0_LOCATION_2_SCK_PORT)
    __CHECK_LOCATION__(SPI_0, SPI_MASTER_0, LOCATION_2);
#endif
#if defined (SPI_0_LOCATION_3_SCK_PORT)
    __CHECK_LOCATION__(SPI_0, SPI_MASTER_0, LOCATION_3);
#endif
#if defined (SPI_0_LOCATION_4_SCK_PORT)
    __CHECK_LOCATION__(SPI_0, SPI_MASTER_0, LOCATION_4);
#endif
#if defined (SPI_0_LOCATION_5_SCK_PORT)
    __CHECK_LOCATION__(SPI_0, SPI_MASTER_0, LOCATION_5);
#endif
#if defined (SPI_0_LOCATION_6_SCK_PORT)
    __CHECK_LOCATION__(SPI_0, SPI_MASTER_0, LOCATION_6);
#endif
#endif


#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
#if defined (SPI_1_LOCATION_0_SCK_PORT)
    __CHECK_LOCATION__(SPI_1, SPI_MASTER_1, LOCATION_0);
#endif
#if defined (SPI_1_LOCATION_1_SCK_PORT)
    __CHECK_LOCATION__(SPI_1, SPI_MASTER_1, LOCATION_1);
#endif
#if defined (SPI_1_LOCATION_2_SCK_PORT)
    __CHECK_LOCATION__(SPI_1, SPI_MASTER_1, LOCATION_2);
#endif
#if defined (SPI_1_LOCATION_3_SCK_PORT)
    __CHECK_LOCATION__(SPI_1, SPI_MASTER_1, LOCATION_3);
#endif
#if defined (SPI_1_LOCATION_4_SCK_PORT)
    __CHECK_LOCATION__(SPI_1, SPI_MASTER_1, LOCATION_4);
#endif
#if defined (SPI_1_LOCATION_5_SCK_PORT)
    __CHECK_LOCATION__(SPI_1, SPI_MASTER_1, LOCATION_5);
#endif
#if defined (SPI_1_LOCATION_6_SCK_PORT)
    __CHECK_LOCATION__(SPI_1, SPI_MASTER_1, LOCATION_6);
#endif
#endif


    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_gpio_pin_spi_slave(
        const   tommRoC_hw_template_bus_spi_slave_enum_t                spi,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_spi_silabs_location_t*  const   locationConfigPtr) {

    // To avoid warning if no one is used
    TOMMROC_UTIL_UNUSED_PARAM(spi);
    TOMMROC_UTIL_UNUSED_PARAM(location);
    TOMMROC_UTIL_UNUSED_PARAM(locationConfigPtr);


#if defined (__TOMMROC_HW_USE_SPI_SLAVE_0_TEMPLATE__)
#if defined (SPI_0_LOCATION_0_SCK_PORT)
    __CHECK_LOCATION__(SPI_0, SPI_SLAVE_0, LOCATION_0);
#endif
#if defined (SPI_0_LOCATION_1_SCK_PORT)
    __CHECK_LOCATION__(SPI_0, SPI_SLAVE_0, LOCATION_1);
#endif
#if defined (SPI_0_LOCATION_2_SCK_PORT)
    __CHECK_LOCATION__(SPI_0, SPI_SLAVE_0, LOCATION_2);
#endif
#if defined (SPI_0_LOCATION_3_SCK_PORT)
    __CHECK_LOCATION__(SPI_0, SPI_SLAVE_0, LOCATION_3);
#endif
#if defined (SPI_0_LOCATION_4_SCK_PORT)
    __CHECK_LOCATION__(SPI_0, SPI_SLAVE_0, LOCATION_4);
#endif
#if defined (SPI_0_LOCATION_5_SCK_PORT)
    __CHECK_LOCATION__(SPI_0, SPI_SLAVE_0, LOCATION_5);
#endif
#if defined (SPI_0_LOCATION_6_SCK_PORT)
    __CHECK_LOCATION__(SPI_0, SPI_SLAVE_0, LOCATION_6);
#endif
#endif


#if defined (__TOMMROC_HW_USE_SPI_SLAVE_1_TEMPLATE__)
#if defined (SPI_1_LOCATION_0_SCK_PORT)
    __CHECK_LOCATION__(SPI_1, SPI_SLAVE_1, LOCATION_0);
#endif
#if defined (SPI_1_LOCATION_1_SCK_PORT)
    __CHECK_LOCATION__(SPI_1, SPI_SLAVE_1, LOCATION_1);
#endif
#if defined (SPI_1_LOCATION_2_SCK_PORT)
    __CHECK_LOCATION__(SPI_1, SPI_SLAVE_1, LOCATION_2);
#endif
#if defined (SPI_1_LOCATION_3_SCK_PORT)
    __CHECK_LOCATION__(SPI_1, SPI_SLAVE_1, LOCATION_3);
#endif
#if defined (SPI_1_LOCATION_4_SCK_PORT)
    __CHECK_LOCATION__(SPI_1, SPI_SLAVE_1, LOCATION_4);
#endif
#if defined (SPI_1_LOCATION_5_SCK_PORT)
    __CHECK_LOCATION__(SPI_1, SPI_SLAVE_1, LOCATION_5);
#endif
#if defined (SPI_1_LOCATION_6_SCK_PORT)
    __CHECK_LOCATION__(SPI_1, SPI_SLAVE_1, LOCATION_6);
#endif
#endif


    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISiLabsLocationGetMaster(
        const   tommRoC_hw_template_bus_spi_master_enum_t               spi,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_spi_silabs_location_t*  const   locationConfigPtr) {

#if defined (_USART_ROUTE_LOCATION_MASK)
    TOMMROC_ASSERT_NOT_NULL(locationConfigPtr);

    locationConfigPtr->locationU32 = _convert_spi_location(location);

    TOMMROC_ASSERT_NOT_EQUALS(locationConfigPtr->locationU32, __LOCATION_ENUM_ERROR__);

    return _set_gpio_pin_spi_master(spi, location, locationConfigPtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(spi);
    TOMMROC_UTIL_UNUSED_PARAM(location);
    TOMMROC_UTIL_UNUSED_PARAM(locationConfigPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISiLabsLocationGetSlave(
        const   tommRoC_hw_template_bus_spi_slave_enum_t                spi,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_spi_silabs_location_t*  const   locationConfigPtr) {

#if defined (_USART_ROUTE_LOCATION_MASK)
    TOMMROC_ASSERT_NOT_NULL(locationConfigPtr);

    locationConfigPtr->locationU32 = _convert_spi_location(location);

    TOMMROC_ASSERT_NOT_EQUALS(locationConfigPtr->locationU32, __LOCATION_ENUM_ERROR__);

    return _set_gpio_pin_spi_slave(spi, location, locationConfigPtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(spi);
    TOMMROC_UTIL_UNUSED_PARAM(location);
    TOMMROC_UTIL_UNUSED_PARAM(locationConfigPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

#endif

#endif
