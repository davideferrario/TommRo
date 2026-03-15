
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusUARTSTM32HalPropGet.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)

#include "bus/env/arm/STM32/uart/tommRoCHwTemplateBusUARTSTM32DEF.h"

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
static tommRoC_hw_comm_hw_flow_control_enum_t _STM32_U32_to_hw_flow_control_enum(const uint32_t HwFlowCtlU32) {

    do { // Added to avoid "warning: unreachable code"
        switch (HwFlowCtlU32) {

        case UART_HWCONTROL_NONE:       return TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_DISABLED;
        case UART_HWCONTROL_CTS:        return TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_ONLY_CTS;
        case UART_HWCONTROL_RTS:        return TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_ONLY_RTS;
        case UART_HWCONTROL_RTS_CTS:    return TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_CTS_RTS;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            break;
        }
    } while (0);

    return TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_DISABLED;
}

static tommRoC_hw_err_enum_t _get_baud_rate_prop(
                UART_HandleTypeDef*                                     const   uartHandlePtr,
                uint32_t*                                               const   propValuePtr) {

    // NOTE: it is supposed that the UART has been configured correctly with last HAL_UART_Init.
    *propValuePtr = (uint32_t) uartHandlePtr->Init.BaudRate;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _get_flow_ctrl_prop(
                UART_HandleTypeDef*                                     const   uartHandlePtr,
                tommRoC_hw_comm_hw_flow_control_enum_t*                 const   propValuePtr) {

    // NOTE: it is supposed that the UART has been configured correctly with last HAL_UART_Init.
    *propValuePtr = _STM32_U32_to_hw_flow_control_enum(uartHandlePtr->Init.HwFlowCtl);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _get_baud_rate_flow_ctrl_prop(
                UART_HandleTypeDef*                                     const   uartHandlePtr,
                tommRoC_hw_bus_uart_prop_baud_rate_hw_flow_control_t*   const   propValuePtr) {

    // NOTE: it is supposed that the UART has been configured correctly with last HAL_UART_Init.
    propValuePtr->baudRate      = uartHandlePtr->Init.BaudRate;
    propValuePtr->hwFlowControl = _STM32_U32_to_hw_flow_control_enum(uartHandlePtr->Init.HwFlowCtl);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTSTM32HalPropGet(
                UART_HandleTypeDef*         const   uartHandlePtr,
        const   tommRoC_hw_bus_prop_enum_t          property,
                void*                       const   propValuePtr) {

    do { // Added to avoid "warning: unreachable code"
        switch (property) {

        case TOMMRO_C_HW_BUS_UART_BAUD_RATE_PROP:
            return _get_baud_rate_prop(
                    uartHandlePtr,
                    (uint32_t*) propValuePtr);

        case TOMMRO_C_HW_BUS_UART_FLOW_CONTROL_PROP:
            return _get_flow_ctrl_prop(
                    uartHandlePtr,
                    (tommRoC_hw_comm_hw_flow_control_enum_t*) propValuePtr);

        case TOMMRO_C_HW_BUS_UART_BAUD_RATE_FLOW_CONTROL_PROP:
            return _get_baud_rate_flow_ctrl_prop(
                    uartHandlePtr,
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

#endif

#endif
