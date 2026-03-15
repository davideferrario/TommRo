
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusUARTSTM32Hal.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)

#include "bus/env/arm/STM32/uart/tommRoCHwTemplateBusUARTSTM32DEF.h"

#include "gpio.h"
#include "usart.h"

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
static void _gpio_configure_for_low_power_pin(GPIO_TypeDef* GPIO_Port, uint32_t Pin) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin     = Pin;
    GPIO_InitStruct.Mode    = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull    = GPIO_NOPULL;
    GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIO_Port, &GPIO_InitStruct);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTSTM32HalSetForLowPowerEnter(UART_HandleTypeDef* const uartHandlePtr) {

    if (HAL_OK != HAL_UART_DeInit(uartHandlePtr)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    if (huart1.Instance == uartHandlePtr->Instance) {
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_TX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_TX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_TX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_RX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_RX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_RX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_DE_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_DE_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_DE_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_RTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_RTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_RTS_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_CTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_CTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART1_CTS_PIN);
#endif

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    if (huart2.Instance == uartHandlePtr->Instance) {
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_TX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_TX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_TX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_RX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_RX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_RX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_DE_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_DE_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_DE_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_RTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_RTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_RTS_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_CTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_CTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART2_CTS_PIN);
#endif

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
    if (huart3.Instance == uartHandlePtr->Instance) {
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_TX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_TX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_TX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_RX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_RX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_RX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_DE_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_DE_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_DE_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_RTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_RTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_RTS_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_CTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_CTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART3_CTS_PIN);
#endif

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
    if (huart4.Instance == uartHandlePtr->Instance) {
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_TX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_TX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_TX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_RX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_RX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_RX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_DE_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_DE_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_DE_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_RTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_RTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_RTS_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_CTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_CTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART4_CTS_PIN);
#endif

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_UART_5_TEMPLATE__)
    if (huart5.Instance == uartHandlePtr->Instance) {
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_TX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_TX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_TX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_RX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_RX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_RX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_DE_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_DE_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_DE_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_RTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_RTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_RTS_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_CTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_CTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART5_CTS_PIN);
#endif

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_UART_6_TEMPLATE__)
    if (huart6.Instance == uartHandlePtr->Instance) {
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_TX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_TX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_TX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_RX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_RX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_RX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_DE_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_DE_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_DE_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_RTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_RTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_RTS_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_CTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_CTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART6_CTS_PIN);
#endif

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_UART_7_TEMPLATE__)
    if (huart7.Instance == uartHandlePtr->Instance) {
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_TX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_TX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_TX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_RX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_RX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_RX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_DE_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_DE_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_DE_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_RTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_RTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_RTS_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_CTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_CTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART7_CTS_PIN);
#endif

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_UART_8_TEMPLATE__)
    if (huart8.Instance == uartHandlePtr->Instance) {
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_TX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_TX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_TX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_RX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_RX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_RX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_DE_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_DE_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_DE_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_RTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_RTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_RTS_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_CTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_CTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_UART8_CTS_PIN);
#endif

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
    if (hlpuart1.Instance == uartHandlePtr->Instance) {
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_TX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_TX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_TX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_RX_GPIO_PORT)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_RX_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_RX_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_DE_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_DE_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_DE_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_RTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_RTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_RTS_PIN);
#endif
#if defined (TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_CTS_IS_USED)
        _gpio_configure_for_low_power_pin(
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_CTS_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_UART_STM32_DEF_LPUART1_CTS_PIN);
#endif

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    return TOMMRO_C_HW_PARAM_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTSTM32HalSetForLowPowerExit(UART_HandleTypeDef* const uartHandlePtr) {

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    if (huart1.Instance == uartHandlePtr->Instance) {
#if defined (USART1)
        MX_USART1_UART_Init();
#elif defined (UART1)
        MX_UART1_Init();
#endif
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    if (huart2.Instance == uartHandlePtr->Instance) {
#if defined (USART2)
        MX_USART2_UART_Init();
#elif defined (UART2)
        MX_UART2_Init();
#endif
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
    if (huart3.Instance == uartHandlePtr->Instance) {
#if defined (USART3)
        MX_USART3_UART_Init();
#elif defined (UART3)
        MX_UART3_Init();
#endif
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
    if (huart4.Instance == uartHandlePtr->Instance) {
#if defined (USART4)
        MX_USART4_UART_Init();
#elif defined (UART4)
        MX_UART4_Init();
#endif
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_UART_5_TEMPLATE__)
    if (huart5.Instance == uartHandlePtr->Instance) {
#if defined (USART5)
        MX_USART5_UART_Init();
#elif defined (UART5)
        MX_UART5_Init();
#endif
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_UART_6_TEMPLATE__)
    if (huart6.Instance == uartHandlePtr->Instance) {
#if defined (USART6)
        MX_USART6_UART_Init();
#elif defined (UART6)
        MX_UART6_Init();
#endif
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_UART_7_TEMPLATE__)
    if (huart7.Instance == uartHandlePtr->Instance) {
#if defined (USART7)
        MX_USART7_UART_Init();
#elif defined (UART7)
        MX_UART7_Init();
#endif
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_UART_8_TEMPLATE__)
    if (huart8.Instance == uartHandlePtr->Instance) {
#if defined (USART8)
        MX_USART8_UART_Init();
#elif defined (UART8)
        MX_UART8_Init();
#endif
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)
    if (hlpuart1.Instance == uartHandlePtr->Instance) {
        MX_LPUART1_UART_Init();
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    return TOMMRO_C_HW_PARAM_ERR;
}

#endif

#endif

#endif
