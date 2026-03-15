
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusUARTSTM32HalPropSet.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)

#include "bus/env/arm/STM32/uart/tommRoCHwTemplateBusUARTSTM32DEF.h"

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
static uint32_t _hw_flow_control_enum_to_STM32_U32(const tommRoC_hw_comm_hw_flow_control_enum_t hwFlowControl) {

    do { // Added to avoid "warning: unreachable code"
        switch (hwFlowControl) {

        case TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_DISABLED: return UART_HWCONTROL_NONE;
        case TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_ONLY_CTS: return UART_HWCONTROL_CTS;
        case TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_ONLY_RTS: return UART_HWCONTROL_RTS;
        case TOMMRO_C_HW_COMM_HW_FLOW_CONTROL_CTS_RTS:  return UART_HWCONTROL_RTS_CTS;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            break;
        }
    } while (0);

    return UART_HWCONTROL_NONE;
}

static tommRoC_hw_err_enum_t _set_baud_rate_prop(
                UART_HandleTypeDef*                                     const   uartHandlePtr,
        const   uint32_t*                                               const   propValuePtr) {

    if (HAL_OK != HAL_UART_DeInit(uartHandlePtr)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    uartHandlePtr->Init.BaudRate = *propValuePtr;

    if (HAL_OK != HAL_UART_Init(uartHandlePtr)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _set_flow_ctrl_prop(
                UART_HandleTypeDef*                                     const   uartHandlePtr,
        const   tommRoC_hw_comm_hw_flow_control_enum_t*                 const   propValuePtr) {

    if (HAL_OK != HAL_UART_DeInit(uartHandlePtr)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    uartHandlePtr->Init.HwFlowCtl = _hw_flow_control_enum_to_STM32_U32(*propValuePtr);

    if (HAL_OK != HAL_UART_Init(uartHandlePtr)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _set_baud_rate_flow_ctrl_prop(
                UART_HandleTypeDef*                                     const   uartHandlePtr,
        const   tommRoC_hw_bus_uart_prop_baud_rate_hw_flow_control_t*   const   propValuePtr) {

    if (HAL_OK != HAL_UART_DeInit(uartHandlePtr)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    uartHandlePtr->Init.BaudRate    = propValuePtr->baudRate;
    uartHandlePtr->Init.HwFlowCtl   = _hw_flow_control_enum_to_STM32_U32(propValuePtr->hwFlowControl);

    if (HAL_OK != HAL_UART_Init(uartHandlePtr)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTSTM32HalPropSet(
                UART_HandleTypeDef*         const   uartHandlePtr,
        const   tommRoC_hw_bus_prop_enum_t          property,
        const   void*                       const   propValuePtr) {

    do { // Added to avoid "warning: unreachable code"
        switch (property) {

        case TOMMRO_C_HW_BUS_UART_BAUD_RATE_PROP:
            return _set_baud_rate_prop(
                    uartHandlePtr,
                    (uint32_t*) propValuePtr);

        case TOMMRO_C_HW_BUS_UART_FLOW_CONTROL_PROP:
            return _set_flow_ctrl_prop(
                    uartHandlePtr,
                    (tommRoC_hw_comm_hw_flow_control_enum_t*) propValuePtr);

        case TOMMRO_C_HW_BUS_UART_BAUD_RATE_FLOW_CONTROL_PROP:
            return _set_baud_rate_flow_ctrl_prop(
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
