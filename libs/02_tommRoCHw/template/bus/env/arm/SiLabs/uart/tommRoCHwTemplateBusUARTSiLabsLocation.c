
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusUARTSiLabsLocation.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_EFM32G_IS_USED__)
#include "bus/env/arm/SiLabs/uart/EFM32G/tommRoCHwTemplateBusUARTEFM32GLocation.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_EFM32GG_IS_USED__)
#include "bus/env/arm/SiLabs/uart/EFM32GG/tommRoCHwTemplateBusUARTEFM32GGLocation.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_EFR32_IS_USED__)
#include "bus/env/arm/SiLabs/uart/EFR32/tommRoCHwTemplateBusUARTEFR32Location.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/

#if defined (_USART_ROUTE_LOCATION_MASK)
#define __LOCATION_ENUM_ERROR__                 ((uint32_t) -1)

#define __CHECK_LOCATION__(UART, LOCATION)                                                                              \
        do {                                                                                                            \
            if ((TOMMROC_HW_TEMPLATE_BUS_ ## UART == uart) && (TOMMROC_HW_TEMPLATE_ ## LOCATION == location)) {         \
                                                                                                                        \
                locationConfigPtr->gpioTxPort   = UART ## _ ## LOCATION ## _TX_PORT;                                    \
                locationConfigPtr->gpioTxPin    = UART ## _ ## LOCATION ## _TX_PIN;                                     \
                locationConfigPtr->gpioRxPort   = UART ## _ ## LOCATION ## _RX_PORT;                                    \
                locationConfigPtr->gpioRxPin    = UART ## _ ## LOCATION ## _RX_PIN;                                     \
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
static uint32_t _convert_usart_location(
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

static uint32_t _convert_leuart_location(
        const   tommRoC_hw_template_bus_location_enum_t location) {

    switch (location) {

#if defined (LEUART_ROUTE_LOCATION_LOC0)
    case TOMMROC_HW_TEMPLATE_LOCATION_0:    return LEUART_ROUTE_LOCATION_LOC0;
#endif
#if defined (LEUART_ROUTE_LOCATION_LOC1)
    case TOMMROC_HW_TEMPLATE_LOCATION_1:    return LEUART_ROUTE_LOCATION_LOC1;
#endif
#if defined (LEUART_ROUTE_LOCATION_LOC2)
    case TOMMROC_HW_TEMPLATE_LOCATION_2:    return LEUART_ROUTE_LOCATION_LOC2;
#endif
#if defined (LEUART_ROUTE_LOCATION_LOC3)
    case TOMMROC_HW_TEMPLATE_LOCATION_3:    return LEUART_ROUTE_LOCATION_LOC3;
#endif
#if defined (LEUART_ROUTE_LOCATION_LOC4)
    case TOMMROC_HW_TEMPLATE_LOCATION_4:    return LEUART_ROUTE_LOCATION_LOC4;
#endif
#if defined (LEUART_ROUTE_LOCATION_LOC5)
    case TOMMROC_HW_TEMPLATE_LOCATION_5:    return LEUART_ROUTE_LOCATION_LOC5;
#endif
#if defined (LEUART_ROUTE_LOCATION_LOC6)
    case TOMMROC_HW_TEMPLATE_LOCATION_6:    return LEUART_ROUTE_LOCATION_LOC6;
#endif

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;
    }

    return __LOCATION_ENUM_ERROR__;
}

static tommRoC_hw_err_enum_t _set_gpio_pin(
        const   tommRoC_hw_template_bus_uart_enum_t                     uart,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_uart_silabs_location_t* const   locationConfigPtr) {

    // To avoid warning if no one is used
    TOMMROC_UTIL_UNUSED_PARAM(uart);
    TOMMROC_UTIL_UNUSED_PARAM(location);
    TOMMROC_UTIL_UNUSED_PARAM(locationConfigPtr);


#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
#if defined (UART_0_LOCATION_0_TX_PORT)
    __CHECK_LOCATION__(UART_0, LOCATION_0);
#endif
#if defined (UART_0_LOCATION_1_TX_PORT)
    __CHECK_LOCATION__(UART_0, LOCATION_1);
#endif
#if defined (UART_0_LOCATION_2_TX_PORT)
    __CHECK_LOCATION__(UART_0, LOCATION_2);
#endif
#if defined (UART_0_LOCATION_3_TX_PORT)
    __CHECK_LOCATION__(UART_0, LOCATION_3);
#endif
#if defined (UART_0_LOCATION_4_TX_PORT)
    __CHECK_LOCATION__(UART_0, LOCATION_4);
#endif
#if defined (UART_0_LOCATION_5_TX_PORT)
    __CHECK_LOCATION__(UART_0, LOCATION_5);
#endif
#if defined (UART_0_LOCATION_6_TX_PORT)
    __CHECK_LOCATION__(UART_0, LOCATION_6);
#endif
#endif


#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
#if defined (UART_1_LOCATION_0_TX_PORT)
    __CHECK_LOCATION__(UART_1, LOCATION_0);
#endif
#if defined (UART_1_LOCATION_1_TX_PORT)
    __CHECK_LOCATION__(UART_1, LOCATION_1);
#endif
#if defined (UART_1_LOCATION_2_TX_PORT)
    __CHECK_LOCATION__(UART_1, LOCATION_2);
#endif
#if defined (UART_1_LOCATION_3_TX_PORT)
    __CHECK_LOCATION__(UART_1, LOCATION_3);
#endif
#if defined (UART_1_LOCATION_4_TX_PORT)
    __CHECK_LOCATION__(UART_1, LOCATION_4);
#endif
#if defined (UART_1_LOCATION_5_TX_PORT)
    __CHECK_LOCATION__(UART_1, LOCATION_5);
#endif
#if defined (UART_1_LOCATION_6_TX_PORT)
    __CHECK_LOCATION__(UART_1, LOCATION_6);
#endif
#endif


#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
#if defined (UART_2_LOCATION_0_TX_PORT)
    __CHECK_LOCATION__(UART_2, LOCATION_0);
#endif
#if defined (UART_2_LOCATION_1_TX_PORT)
    __CHECK_LOCATION__(UART_2, LOCATION_1);
#endif
#if defined (UART_2_LOCATION_2_TX_PORT)
    __CHECK_LOCATION__(UART_2, LOCATION_2);
#endif
#if defined (UART_2_LOCATION_3_TX_PORT)
    __CHECK_LOCATION__(UART_2, LOCATION_3);
#endif
#if defined (UART_2_LOCATION_4_TX_PORT)
    __CHECK_LOCATION__(UART_2, LOCATION_4);
#endif
#if defined (UART_2_LOCATION_5_TX_PORT)
    __CHECK_LOCATION__(UART_2, LOCATION_5);
#endif
#if defined (UART_2_LOCATION_6_TX_PORT)
    __CHECK_LOCATION__(UART_2, LOCATION_6);
#endif
#endif


#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
#if defined (LEUART_0_LOCATION_0_TX_PORT)
    __CHECK_LOCATION__(LEUART_0, LOCATION_0);
#endif
#if defined (LEUART_0_LOCATION_1_TX_PORT)
    __CHECK_LOCATION__(LEUART_0, LOCATION_1);
#endif
#if defined (LEUART_0_LOCATION_2_TX_PORT)
    __CHECK_LOCATION__(LEUART_0, LOCATION_2);
#endif
#if defined (LEUART_0_LOCATION_3_TX_PORT)
    __CHECK_LOCATION__(LEUART_0, LOCATION_3);
#endif
#if defined (LEUART_0_LOCATION_4_TX_PORT)
    __CHECK_LOCATION__(LEUART_0, LOCATION_4);
#endif
#if defined (LEUART_0_LOCATION_5_TX_PORT)
    __CHECK_LOCATION__(LEUART_0, LOCATION_5);
#endif
#if defined (LEUART_0_LOCATION_6_TX_PORT)
    __CHECK_LOCATION__(LEUART_0, LOCATION_6);
#endif
#endif


#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
#if defined (LEUART_1_LOCATION_0_TX_PORT)
    __CHECK_LOCATION__(LEUART_1, LOCATION_0);
#endif
#if defined (LEUART_1_LOCATION_1_TX_PORT)
    __CHECK_LOCATION__(LEUART_1, LOCATION_1);
#endif
#if defined (LEUART_1_LOCATION_2_TX_PORT)
    __CHECK_LOCATION__(LEUART_1, LOCATION_2);
#endif
#if defined (LEUART_1_LOCATION_3_TX_PORT)
    __CHECK_LOCATION__(LEUART_1, LOCATION_3);
#endif
#if defined (LEUART_1_LOCATION_4_TX_PORT)
    __CHECK_LOCATION__(LEUART_1, LOCATION_4);
#endif
#if defined (LEUART_1_LOCATION_5_TX_PORT)
    __CHECK_LOCATION__(LEUART_1, LOCATION_5);
#endif
#if defined (LEUART_1_LOCATION_6_TX_PORT)
    __CHECK_LOCATION__(LEUART_1, LOCATION_6);
#endif
#endif


    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTSiLabsLocationGet(
        const   tommRoC_hw_template_bus_uart_enum_t                     uart,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_uart_silabs_location_t* const   locationConfigPtr) {

#if defined (_USART_ROUTE_LOCATION_MASK)

    TOMMROC_ASSERT_NOT_NULL(locationConfigPtr);

    switch (uart) {

    case TOMMROC_HW_TEMPLATE_BUS_UART_0:
    case TOMMROC_HW_TEMPLATE_BUS_UART_1:
    case TOMMROC_HW_TEMPLATE_BUS_UART_2:
    case TOMMROC_HW_TEMPLATE_BUS_UART_3:
    case TOMMROC_HW_TEMPLATE_BUS_UART_4:
    case TOMMROC_HW_TEMPLATE_BUS_UART_5:
        locationConfigPtr->locationU32 = _convert_usart_location(location);
        break;

    case TOMMROC_HW_TEMPLATE_BUS_LEUART_0:
    case TOMMROC_HW_TEMPLATE_BUS_LEUART_1:
        locationConfigPtr->locationU32 = _convert_leuart_location(location);
        break;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);

        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }

    TOMMROC_ASSERT_NOT_EQUALS(locationConfigPtr->locationU32, __LOCATION_ENUM_ERROR__);

    return _set_gpio_pin(uart, location, locationConfigPtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(uart);
    TOMMROC_UTIL_UNUSED_PARAM(location);
    TOMMROC_UTIL_UNUSED_PARAM(locationConfigPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

#endif

#endif
