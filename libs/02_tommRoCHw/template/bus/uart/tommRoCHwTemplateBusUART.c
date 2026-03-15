
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusUART.h"

#include "bus/common/tommRoCHwTemplateBusCommon.h"

#include "bus/env/tommRoCHwTemplateBusEnvironmentUART.h"

#include "bus/common/uart/tommRoCHwTemplateBusCommonUART.h"

#include "TOMMROC.h"

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

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTSetProp(
        const   tommRoC_hw_template_bus_uart_prop_enum_t            property,
        const   tommRoC_hw_template_bus_uart_enum_t                 bus,
        const   void*                                       const   propValuePtr) {

    TOMMROC_ASSERT_NOT_NULL(propValuePtr);

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)

    return tommRoCHwTemplateBusEnvironmentUARTSetProp(property, bus, propValuePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(property);
    TOMMROC_UTIL_UNUSED_PARAM(bus);
    TOMMROC_UTIL_UNUSED_PARAM(propValuePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUART0Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_UART_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentUART0Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUART1Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_UART_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentUART1Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUART2Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_UART_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentUART2Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUART3Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_UART_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentUART3Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUART4Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_UART_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentUART4Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUART5Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_UART_5_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_UART_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentUART5Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUART6Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_UART_6_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_UART_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentUART6Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUART7Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_UART_7_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_UART_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentUART7Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUART8Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_UART_8_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_UART_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentUART8Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusLEUART0Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_LEUART_0_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_UART_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentLEUART0Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusLEUART1Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_LEUART_1_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_UART_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentLEUART1Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}
