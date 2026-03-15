
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentUART.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)

#include "mcc.h"

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

#define __TOMMROC_HW_UART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(UARTPREFIX)                               \
                                                                                                            \
    static tommRoC_hw_err_enum_t _uart_ ## UARTPREFIX ## _data_ready_XC(                                    \
                    uint16_t*   const   availableAmountPtr,                                                 \
            const   void*       const   inputPtr,                                                           \
                    void*       const   resultPtr) {                                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        *availableAmountPtr = (uint16_t) UARTPREFIX ## _is_rx_ready();                                      \
                                                                                                            \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _uart_ ## UARTPREFIX ## _write_buffers_XC(                                 \
            const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,                                    \
            const   uint8_t                             writeBuffersAmount,                                 \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        const tommRoC_hw_bus_write_buf_t* writeBufferPtr;                                                   \
        uint8_t idx;                                                                                        \
        uint8_t* ptr;                                                                                       \
        uint16_t counter;                                                                                   \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        for (idx = 0, writeBufferPtr = writeBuffersPtr; idx < writeBuffersAmount; ++idx, ++writeBufferPtr) {\
                                                                                                            \
            ptr = (uint8_t*) writeBufferPtr->bufferPtr;                                                     \
                                                                                                            \
            for (counter = 0; counter < writeBufferPtr->toWriteAmount; ++counter, ++ptr) {                  \
                UARTPREFIX ## _Write(*ptr);                                                                 \
            }                                                                                               \
        }                                                                                                   \
                                                                                                            \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _uart_ ## UARTPREFIX ## _read_buffers_XC(                                  \
                    tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,                                     \
            const   uint8_t                             readBuffersAmount,                                  \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        tommRoC_hw_bus_read_buf_t* readBufferPtr;                                                           \
        uint8_t idx;                                                                                        \
        uint8_t* ptr;                                                                                       \
        uint16_t counter;                                                                                   \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        for (idx = 0, readBufferPtr = readBuffersPtr; idx < readBuffersAmount; ++idx, ++readBufferPtr) {    \
                                                                                                            \
            ptr = (uint8_t*) readBufferPtr->bufferPtr;                                                      \
                                                                                                            \
            for (counter = 0; counter < readBufferPtr->toReadAmount; ++counter, ++ptr) {                    \
                *ptr = UARTPREFIX ## _Read();                                                               \
            }                                                                                               \
                                                                                                            \
            *(readBufferPtr->readedAmountPtr) = readBufferPtr->toReadAmount;                                \
        }                                                                                                   \
                                                                                                            \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
    }                                                                                                       \
                                                                                                            \
    static void _uart_ ## UARTPREFIX ## _get_callback_XC(                                                   \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                                       \
                                                                                                            \
        cbFunctPtr->dataReady       = _uart_ ## UARTPREFIX ## _data_ready_XC;                               \
        cbFunctPtr->writeBuffers    = _uart_ ## UARTPREFIX ## _write_buffers_XC;                            \
        cbFunctPtr->readBuffers     = _uart_ ## UARTPREFIX ## _read_buffers_XC;                             \
    }

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
    __TOMMROC_HW_UART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART);
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
    __TOMMROC_HW_UART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART1);
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
    __TOMMROC_HW_UART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART2);
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
    __TOMMROC_HW_UART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART3);
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
    __TOMMROC_HW_UART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART4);
#endif

#if defined (__TOMMROC_HW_USE_UART_5_TEMPLATE__)
    __TOMMROC_HW_UART_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(EUSART5);
#endif


#define __TOMMROC_HW_TEMPLATE_BUS_UART_START_XC__(UARTPREFIX, cbFunctPtr)       \
        _uart_ ## UARTPREFIX ## _get_callback_XC(cbFunctPtr);                   \
        return TOMMRO_C_HW_ERR_SUCCESS;

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUARTSetProp(
        const   tommRoC_hw_template_bus_uart_prop_enum_t            property,
        const   tommRoC_hw_template_bus_uart_enum_t                 bus,
        const   void*                                       const   propValuePtr) {

    TOMMROC_UTIL_UNUSED_PARAM(property);
    TOMMROC_UTIL_UNUSED_PARAM(bus);
    TOMMROC_UTIL_UNUSED_PARAM(propValuePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_UART_0_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART0Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_XC__(EUSART, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_UART_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_XC__(EUSART1, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_UART_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART2Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_XC__(EUSART2, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_UART_3_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART3Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_XC__(EUSART3, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_UART_4_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART4Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_XC__(EUSART4, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_UART_5_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentUART5Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_UART_START_XC__(EUSART5, cbFunctPtr);
}
#endif

#endif

#endif
