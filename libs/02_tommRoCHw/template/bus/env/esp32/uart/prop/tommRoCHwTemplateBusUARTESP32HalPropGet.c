
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusUARTESP32HalPropGet.h"

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
static tommRoC_hw_comm_hw_flow_control_enum_t _ESP32_uart_hw_flowcontrol_to_hw_flow_control_enum(const uart_hw_flowcontrol_t flowCtrl) {

    do { // Added to avoid "warning: unreachable code"
        switch (flowCtrl) {

        case UART_HW_FLOWCTRL_DISABLE:  return TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_DISABLED;
        case UART_HW_FLOWCTRL_RTS:      return TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_ONLY_RTS;
        case UART_HW_FLOWCTRL_CTS:      return TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_ONLY_CTS;
        case UART_HW_FLOWCTRL_CTS_RTS:  return TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_CTS_RTS;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            break;
        }
    } while (0);

    return TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_DISABLED;
}

static tommRoC_hw_err_enum_t _get_baud_rate_prop(
        const   uart_port_t                                                     uartPort,
                uint32_t*                                               const   propValuePtr) {

    uint32_t baudRate;

    if (ESP_OK != uart_get_baudrate(uartPort, &baudRate)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    *propValuePtr = baudRate;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _get_flow_ctrl_prop(
        const   uart_port_t                                                     uartPort,
                tommRoC_hw_comm_hw_flow_control_enum_t*                 const   propValuePtr) {

    uart_hw_flowcontrol_t flowCtrl;

    if (ESP_OK != uart_get_hw_flow_ctrl(uartPort, &flowCtrl)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    *propValuePtr = _ESP32_uart_hw_flowcontrol_to_hw_flow_control_enum(flowCtrl);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _get_baud_rate_flow_ctrl_prop(
        const   uart_port_t                                                     uartPort,
                tommRoC_hw_bus_uart_prop_baud_rate_hw_flow_control_t*   const   propValuePtr) {

    uint32_t baudRate;
    uart_hw_flowcontrol_t flowCtrl;

    if (ESP_OK != uart_get_baudrate(uartPort, &baudRate)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != uart_get_hw_flow_ctrl(uartPort, &flowCtrl)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    propValuePtr->baudRate      = baudRate;
    propValuePtr->hwFlowControl = _ESP32_uart_hw_flowcontrol_to_hw_flow_control_enum(flowCtrl);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTESP32HalPropGet(
        const   uart_port_t                         uartPort,
        const   tommRoC_hw_bus_prop_enum_t          property,
                void*                       const   propValuePtr) {

    do { // Added to avoid "warning: unreachable code"
        switch (property) {

        case TOMMRO_C_HW_BUS_UART_BAUD_RATE_PROP:
            return _get_baud_rate_prop(
                    uartPort,
                    (uint32_t*) propValuePtr);

        case TOMMRO_C_HW_BUS_UART_FLOW_CONTROL_PROP:
            return _get_flow_ctrl_prop(
                    uartPort,
                    (tommRoC_hw_comm_hw_flow_control_enum_t*) propValuePtr);

        case TOMMRO_C_HW_BUS_UART_BAUD_RATE_FLOW_CONTROL_PROP:
            return _get_baud_rate_flow_ctrl_prop(
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
