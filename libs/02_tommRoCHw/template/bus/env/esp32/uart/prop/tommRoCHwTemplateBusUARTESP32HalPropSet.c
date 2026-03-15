
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusUARTESP32HalPropSet.h"

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
static uart_hw_flowcontrol_t _hw_flow_control_enum_to_ESP32_uart_hw_flowcontrol(const tommRoC_hw_comm_hw_flow_control_enum_t hwFlowControl) {

    do { // Added to avoid "warning: unreachable code"
        switch (hwFlowControl) {

        case TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_DISABLED: return UART_HW_FLOWCTRL_DISABLE;
        case TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_ONLY_CTS: return UART_HW_FLOWCTRL_CTS;
        case TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_ONLY_RTS: return UART_HW_FLOWCTRL_RTS;
        case TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_CTS_RTS:  return UART_HW_FLOWCTRL_CTS_RTS;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            break;
        }
    } while (0);

    return UART_HW_FLOWCTRL_DISABLE;
}

static tommRoC_hw_err_enum_t _set_baud_rate_prop(
        const   uart_port_t                                                     uartPort,
        const   uint32_t*                                               const   propValuePtr) {

    if (ESP_OK != uart_set_baudrate(uartPort, *propValuePtr)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _set_flow_ctrl_prop(
        const   uart_port_t                                                     uartPort,
        const   tommRoC_hw_comm_hw_flow_control_enum_t*                 const   propValuePtr) {

    if (ESP_OK != uart_set_hw_flow_ctrl(uartPort, _hw_flow_control_enum_to_ESP32_uart_hw_flowcontrol(*propValuePtr), 0)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _set_baud_rate_flow_ctrl_prop(
        const   uart_port_t                                                     uartPort,
        const   tommRoC_hw_bus_uart_prop_baud_rate_hw_flow_control_t*   const   propValuePtr) {

    if (ESP_OK != uart_set_baudrate(uartPort, propValuePtr->baudRate)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != uart_set_hw_flow_ctrl(uartPort, _hw_flow_control_enum_to_ESP32_uart_hw_flowcontrol(propValuePtr->hwFlowControl), 0)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTESP32HalPropSet(
        const   uart_port_t                         uartPort,
        const   tommRoC_hw_bus_prop_enum_t          property,
        const   void*                       const   propValuePtr) {

    do { // Added to avoid "warning: unreachable code"
        switch (property) {

        case TOMMRO_C_HW_BUS_UART_BAUD_RATE_PROP:
            return _set_baud_rate_prop(
                    uartPort,
                    (uint32_t*) propValuePtr);

        case TOMMRO_C_HW_BUS_UART_FLOW_CONTROL_PROP:
            return _set_flow_ctrl_prop(
                    uartPort,
                    (tommRoC_hw_comm_hw_flow_control_enum_t*) propValuePtr);

        case TOMMRO_C_HW_BUS_UART_BAUD_RATE_FLOW_CONTROL_PROP:
            return _set_baud_rate_flow_ctrl_prop(
                    uartPort,
                    (tommRoC_hw_bus_uart_prop_baud_rate_hw_flow_control_t*) propValuePtr);

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            break;
        }
    } while (0);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

#endif
