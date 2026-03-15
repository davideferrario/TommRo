
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusUARTNordicHal.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)

#include "bus/uart/tommRoCHwTemplateBusUARTDEF.h"

#include "nrf_gpio.h"

#if (defined (UART_PRESENT) && UART_COUNT)
#include "nrfx_uart.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if (defined (UART_PRESENT) && UART_COUNT)
static void _gpio_configure_for_bus(const uint32_t pselTXD, const uint32_t pselRXD) {

    // To avoid false start, configure output as high
    if (NRF_UART_PSEL_DISCONNECTED != pselTXD) {
        nrf_gpio_pin_set(pselTXD);
        nrf_gpio_cfg_output(pselTXD);
    }
    if (NRF_UART_PSEL_DISCONNECTED != pselRXD) {
        nrf_gpio_cfg_input(pselRXD, NRF_GPIO_PIN_NOPULL);
    }
}

static void _gpio_configure_for_low_power(const uint32_t pselTXD, const uint32_t pselRXD) {

    if (NRF_UART_PSEL_DISCONNECTED != pselTXD) {
        nrf_gpio_cfg_input(pselTXD, NRF_GPIO_PIN_NOPULL);
    }
    if (NRF_UART_PSEL_DISCONNECTED != pselRXD) {
        nrf_gpio_cfg_input(pselRXD, NRF_GPIO_PIN_NOPULL);
    }
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

#if (defined (UART_PRESENT) && UART_COUNT)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTNordicHalInit(const tommRoC_hw_template_bus_uart_nordic_hal_config_t* const initConfigPtr) {

    nrfx_uart_config_t nrfxUartConfig = NRFX_UART_DEFAULT_CONFIG;

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

    nrfxUartConfig.pseltxd  = initConfigPtr->pselTXD;
    nrfxUartConfig.pselrxd  = initConfigPtr->pselRXD;
    nrfxUartConfig.baudrate = initConfigPtr->baudRate;

    // Ensure a proper 'reset'
    nrfx_uart_uninit(&initConfigPtr->nrfxUart);

    if (NRFX_SUCCESS != nrfx_uart_init(&initConfigPtr->nrfxUart, &nrfxUartConfig, initConfigPtr->nrfxUartEventHandler)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTNordicHalSetForLowPowerEnter(const uint32_t pselTXD, const uint32_t pselRXD) {

    _gpio_configure_for_low_power(pselTXD, pselRXD);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTNordicHalSetForLowPowerExit(const uint32_t pselTXD, const uint32_t pselRXD) {

    _gpio_configure_for_bus(pselTXD, pselRXD);

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif
