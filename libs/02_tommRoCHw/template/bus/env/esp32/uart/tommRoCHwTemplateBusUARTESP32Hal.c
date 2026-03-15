
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusUARTESP32Hal.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

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

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTESP32HalInit(const tommRoC_hw_template_bus_uart_esp32_hal_config_t* const initConfigPtr) {

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

    /**
     * NOTE:
     * Rx_buffer_size should be greater than SOC_UART_FIFO_LEN.
     * Tx_buffer_size should be greater than SOC_UART_FIFO_LEN.
     */
    TOMMROC_ASSERT_ZERO(initConfigPtr->rxBufferSize % TOMMROC_UTIL_U32_SIZE);
    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(initConfigPtr->rxBufferSize, TOMMROC_HW_TEMPLATE_BUS_UART_ESP32_HAL_MINIMUM_BUFFER_SIZE);
    TOMMROC_ASSERT_ZERO(initConfigPtr->txBufferSize % TOMMROC_UTIL_U32_SIZE);
    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(initConfigPtr->txBufferSize, TOMMROC_HW_TEMPLATE_BUS_UART_ESP32_HAL_MINIMUM_BUFFER_SIZE);

    if (ESP_OK != uart_param_config(initConfigPtr->uartPort, &initConfigPtr->uartConfig)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != uart_set_pin(initConfigPtr->uartPort, (int) initConfigPtr->txGPIONum, (int) initConfigPtr->rxGPIONum, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != uart_driver_install(initConfigPtr->uartPort, (int) initConfigPtr->rxBufferSize, (int) initConfigPtr->txBufferSize, 0, NULL, 0)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTESP32HalSetForLowPowerEnter(const uart_port_t uartPort, const gpio_num_t txGPIONum, const gpio_num_t rxGPIONum) {

    TOMMROC_UTIL_UNUSED_PARAM(uartPort);
    TOMMROC_UTIL_UNUSED_PARAM(txGPIONum);
    TOMMROC_UTIL_UNUSED_PARAM(rxGPIONum);

/*
    TOMMROC_UTIL_UNUSED_PARAM(uartPort);

    gpio_pad_select_gpio(txGPIONum);
    gpio_pad_select_gpio(rxGPIONum);

    if (ESP_OK != gpio_reset_pin(txGPIONum)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != gpio_reset_pin(rxGPIONum)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (ESP_OK != gpio_set_direction(txGPIONum, GPIO_MODE_INPUT)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != gpio_set_direction(rxGPIONum, GPIO_MODE_INPUT)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
*/
    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTESP32HalSetForLowPowerExit(const uart_port_t uartPort, const gpio_num_t txGPIONum, const gpio_num_t rxGPIONum) {

    TOMMROC_UTIL_UNUSED_PARAM(uartPort);
    TOMMROC_UTIL_UNUSED_PARAM(txGPIONum);
    TOMMROC_UTIL_UNUSED_PARAM(rxGPIONum);
/*
    if (ESP_OK != uart_set_pin(uartPort, (int) txGPIONum, (int) rxGPIONum, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
*/
    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif
