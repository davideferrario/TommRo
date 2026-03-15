
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusUARTNXPLocation.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__)
#include "bus/env/arm/NXP/uart/MK22/tommRoCHwTemplateBusUARTMK22Location.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)
#include "bus/env/arm/NXP/uart/MKWx1Z/tommRoCHwTemplateBusUARTMKWx1ZLocation.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__)
#include "bus/env/arm/NXP/uart/QN908XC/tommRoCHwTemplateBusUARTQN908XCLocation.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
#include "bus/env/arm/NXP/uart/MKE02Z4/tommRoCHwTemplateBusUARTMKE02Z4Location.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define __CHECK_LOCATION__(UART, LOCATION)                                                                          \
        do {                                                                                                        \
            if ((TOMMROC_HW_TEMPLATE_BUS_ ## UART == uart) && (TOMMROC_HW_TEMPLATE_ ## LOCATION == location)) {     \
                                                                                                                    \
                locationConfigPtr->clockName                = UART ## _ ## LOCATION ## _CLOCK_NAME;                 \
                locationConfigPtr->gpioTxPort               = UART ## _ ## LOCATION ## _TX_PORT;                    \
                locationConfigPtr->gpioTxPin                = UART ## _ ## LOCATION ## _TX_PIN;                     \
                locationConfigPtr->gpioTxPortMux            = UART ## _ ## LOCATION ## _TX_PORT_MUX;                \
                locationConfigPtr->gpioRxPort               = UART ## _ ## LOCATION ## _RX_PORT;                    \
                locationConfigPtr->gpioRxPin                = UART ## _ ## LOCATION ## _RX_PIN;                     \
                locationConfigPtr->gpioRxPortMux            = UART ## _ ## LOCATION ## _RX_PORT_MUX;                \
                                                                                                                    \
                locationConfigPtr->gpioTxGpio               = UART ## _ ## LOCATION ## _TX_GPIO;                    \
                locationConfigPtr->gpioRxGpio               = UART ## _ ## LOCATION ## _RX_GPIO;                    \
                                                                                                                    \
                return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
            }                                                                                                       \
        } while (0)

#elif (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)
#define __CHECK_LOCATION__(UART, LOCATION)                                                                          \
        do {                                                                                                        \
            if ((TOMMROC_HW_TEMPLATE_BUS_ ## UART == uart) && (TOMMROC_HW_TEMPLATE_ ## LOCATION == location)) {     \
                                                                                                                    \
                locationConfigPtr->clockName                = UART ## _ ## LOCATION ## _CLOCK_NAME;                 \
                locationConfigPtr->txPortIdx                = UART ## _ ## LOCATION ## _TX_PORT_IDX;                \
                locationConfigPtr->txPin                    = UART ## _ ## LOCATION ## _TX_PIN;                     \
                locationConfigPtr->txIOCONFunc              = UART ## _ ## LOCATION ## _TX_IOCON_FUNC;              \
                locationConfigPtr->rxPortIdx                = UART ## _ ## LOCATION ## _RX_PORT_IDX;                \
                locationConfigPtr->rxPin                    = UART ## _ ## LOCATION ## _RX_PIN;                     \
                locationConfigPtr->rxIOCONFunc              = UART ## _ ## LOCATION ## _RX_IOCON_FUNC;              \
                                                                                                                    \
                locationConfigPtr->gpioTxGpio               = UART ## _ ## LOCATION ## _TX_GPIO;                    \
                locationConfigPtr->gpioRxGpio               = UART ## _ ## LOCATION ## _RX_GPIO;                    \
                                                                                                                    \
                return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
            }                                                                                                       \
        } while (0)

#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
#define __CHECK_LOCATION__(UART, LOCATION)                                                                          \
        do {                                                                                                        \
            if ((TOMMROC_HW_TEMPLATE_BUS_ ## UART == uart) && (TOMMROC_HW_TEMPLATE_ ## LOCATION == location)) {     \
                                                                                                                    \
                locationConfigPtr->clockName                = UART ## _ ## LOCATION ## _CLOCK_NAME;                 \
                locationConfigPtr->portSetPinSelectNeeded   = UART ## _ ## LOCATION ## _PORT_SET_PIN_SELECT_NEEDED; \
                locationConfigPtr->portModule               = UART ## _ ## LOCATION ## _PORT_MODULE;                \
                locationConfigPtr->portPinSelect            = UART ## _ ## LOCATION ## _PORT_PIN_SELECT;            \
                                                                                                                    \
                locationConfigPtr->gpioTxPort               = UART ## _ ## LOCATION ## _TX_PORT;                    \
                locationConfigPtr->gpioTxPin                = UART ## _ ## LOCATION ## _TX_PIN;                     \
                locationConfigPtr->gpioRxPort               = UART ## _ ## LOCATION ## _RX_PORT;                    \
                locationConfigPtr->gpioRxPin                = UART ## _ ## LOCATION ## _RX_PIN;                     \
                                                                                                                    \
                return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
            }                                                                                                       \
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

static tommRoC_hw_err_enum_t _set_gpio_pin(
        const   tommRoC_hw_template_bus_uart_enum_t                     uart,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_uart_nxp_location_t*    const   locationConfigPtr) {

    // To avoid warning if no one is used
    TOMMROC_UTIL_UNUSED_PARAM(uart);
    TOMMROC_UTIL_UNUSED_PARAM(location);
    TOMMROC_UTIL_UNUSED_PARAM(locationConfigPtr);


#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
#if defined (UART_0_LOCATION_0_CLOCK_NAME)
    __CHECK_LOCATION__(UART_0, LOCATION_0);
#endif
#if defined (UART_0_LOCATION_1_CLOCK_NAME)
    __CHECK_LOCATION__(UART_0, LOCATION_1);
#endif
#if defined (UART_0_LOCATION_2_CLOCK_NAME)
    __CHECK_LOCATION__(UART_0, LOCATION_2);
#endif
#if defined (UART_0_LOCATION_3_CLOCK_NAME)
    __CHECK_LOCATION__(UART_0, LOCATION_3);
#endif
#endif


#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
#if defined (UART_1_LOCATION_0_CLOCK_NAME)
    __CHECK_LOCATION__(UART_1, LOCATION_0);
#endif
#if defined (UART_1_LOCATION_1_CLOCK_NAME)
    __CHECK_LOCATION__(UART_1, LOCATION_1);
#endif
#if defined (UART_1_LOCATION_2_CLOCK_NAME)
    __CHECK_LOCATION__(UART_1, LOCATION_2);
#endif
#if defined (UART_1_LOCATION_3_CLOCK_NAME)
    __CHECK_LOCATION__(UART_1, LOCATION_3);
#endif
#endif


#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
#if defined (UART_2_LOCATION_0_CLOCK_NAME)
    __CHECK_LOCATION__(UART_2, LOCATION_0);
#endif
#if defined (UART_2_LOCATION_1_CLOCK_NAME)
    __CHECK_LOCATION__(UART_2, LOCATION_1);
#endif
#if defined (UART_2_LOCATION_2_CLOCK_NAME)
    __CHECK_LOCATION__(UART_2, LOCATION_2);
#endif
#if defined (UART_2_LOCATION_3_CLOCK_NAME)
    __CHECK_LOCATION__(UART_2, LOCATION_3);
#endif
#endif


#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)
#if defined (LEUART_0_LOCATION_0_CLOCK_NAME)
    __CHECK_LOCATION__(LEUART_0, LOCATION_0);
#endif
#if defined (LEUART_0_LOCATION_1_CLOCK_NAME)
    __CHECK_LOCATION__(LEUART_0, LOCATION_1);
#endif
#if defined (LEUART_0_LOCATION_2_CLOCK_NAME)
    __CHECK_LOCATION__(LEUART_0, LOCATION_2);
#endif
#if defined (LEUART_0_LOCATION_3_CLOCK_NAME)
    __CHECK_LOCATION__(LEUART_0, LOCATION_3);
#endif
#endif


    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTNXPLocationGet(
        const   tommRoC_hw_template_bus_uart_enum_t                     uart,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_uart_nxp_location_t*    const   locationConfigPtr) {

    TOMMROC_ASSERT_NOT_NULL(locationConfigPtr);

    return _set_gpio_pin(uart, location, locationConfigPtr);
}

#endif

#endif
