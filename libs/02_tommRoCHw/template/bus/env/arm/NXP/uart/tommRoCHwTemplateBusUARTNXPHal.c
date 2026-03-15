
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusUARTNXPHal.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#include "bus/uart/tommRoCHwTemplateBusUARTDEF.h"

#if defined (__TOMMROC_HW_TEMPLATE_BUS_UART_DEF_AT_LEAST_ONE_UART_IS_USED__)

#include "env/tommRoCTemplateEnv.h"

#include "fsl_gpio.h"
#if (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT) || (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT)
#include "fsl_iocon.h"
#endif
#if defined (FSL_FEATURE_SOC_PORT_COUNT) && FSL_FEATURE_SOC_PORT_COUNT
#include "fsl_port.h"
#endif
#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
#include "fsl_uart.h"
#endif
#if defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
#include "fsl_usart.h"
#endif
#if defined (FSL_FEATURE_SOC_LPUART_COUNT) && FSL_FEATURE_SOC_LPUART_COUNT
#include "fsl_lpuart.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __UART_ISR_PRIO__   (0x40)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
static void _gpio_configure_for_bus(const tommRoC_hw_template_bus_uart_nxp_location_t* const locationPtr) {

    TOMMROC_ASSERT_NOT_NULL(locationPtr);

#if (!((defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)))
    CLOCK_EnableClock(locationPtr->clockName);
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
    PORT_SetPinMux(locationPtr->gpioTxPort, locationPtr->gpioTxPin, locationPtr->gpioTxPortMux);
    PORT_SetPinMux(locationPtr->gpioRxPort, locationPtr->gpioRxPin, locationPtr->gpioRxPortMux);

#elif (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)
    const uint32_t txModeFunc = (
            locationPtr->txIOCONFunc    |   // Select pin function
            IOCON_MODE_HIGHZ            |   // Select High-Z function
            IOCON_DRIVE_LOW                 // Enable low drive strength
    );

    const uint32_t rxModeFunc = (
            locationPtr->rxIOCONFunc    |   // Select pin function
            IOCON_MODE_HIGHZ            |   // Select High-Z function
            IOCON_DRIVE_LOW                 // Enable low drive strength
    );

    IOCON_PinMuxSet(IOCON, locationPtr->txPortIdx, locationPtr->txPin, txModeFunc);
    IOCON_PinMuxSet(IOCON, locationPtr->rxPortIdx, locationPtr->rxPin, rxModeFunc);

#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
    if (locationPtr->portSetPinSelectNeeded) {
        PORT_SetPinSelect(locationPtr->portModule, locationPtr->portPinSelect);
    }
#endif

#if (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)
    CLOCK_EnableClock(locationPtr->clockName);
#endif
}

static void _gpio_configure_for_low_power(const tommRoC_hw_template_bus_uart_nxp_location_t* const locationPtr) {

    const gpio_pin_config_t gpioConfigAsInput = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };

    TOMMROC_ASSERT_NOT_NULL(locationPtr);

#if (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)
    CLOCK_DisableClock(locationPtr->clockName);
#else
    CLOCK_EnableClock(locationPtr->clockName);
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
    PORT_SetPinMux(locationPtr->gpioTxPort, locationPtr->gpioTxPin, kPORT_MuxAsGpio);
    PORT_SetPinMux(locationPtr->gpioRxPort, locationPtr->gpioRxPin, kPORT_MuxAsGpio);

    GPIO_PinInit(locationPtr->gpioTxGpio, locationPtr->gpioTxPin, &gpioConfigAsInput);
    GPIO_PinInit(locationPtr->gpioRxGpio, locationPtr->gpioRxPin, &gpioConfigAsInput);

#elif (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)
    const uint32_t modeFunc = (
            IOCON_FUNC0                 |   // Select pin function (FUNC0 -> GPIO)
            IOCON_MODE_HIGHZ            |   // Select High-Z function
            IOCON_DRIVE_LOW                 // Enable low drive strength
    );

    IOCON_PinMuxSet(IOCON, locationPtr->txPortIdx, locationPtr->txPin, modeFunc);
    IOCON_PinMuxSet(IOCON, locationPtr->rxPortIdx, locationPtr->rxPin, modeFunc);

    GPIO_PinInit(locationPtr->gpioTxGpio, locationPtr->txPin, &gpioConfigAsInput);
    GPIO_PinInit(locationPtr->gpioRxGpio, locationPtr->rxPin, &gpioConfigAsInput);

#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
    GPIO_PinInit(locationPtr->gpioTxPort, locationPtr->gpioTxPin, &gpioConfigAsInput);
    GPIO_PinInit(locationPtr->gpioRxPort, locationPtr->gpioRxPin, &gpioConfigAsInput);
#endif
}

#if defined (FSL_FEATURE_SOC_LPUART_COUNT) && FSL_FEATURE_SOC_LPUART_COUNT
static tommRoC_hw_err_enum_t _lpuart_clock_configure(void) {

    /* SIM_SOPT2[27:26]:
     *  00: Clock Disabled
     *  01: MCGFLLCLK
     *  10: OSCERCLK
     *  11: MCGIRCCLK
     */
    uint32_t src;
    tommRoC_hw_err_enum_t result;

    src     = 0b00U;                        // Default: clock disabled
    result  = TOMMRO_C_HW_LOW_LEVEL_ERR;
    
    if (0 != CLOCK_GetFreq(kCLOCK_Osc0ErClk)) {
        src     = 0b10U;                    // OSCERCLK
        result  = TOMMRO_C_HW_ERR_SUCCESS;
    }    
    else if (0 != CLOCK_GetFreq(kCLOCK_McgFllClk)) {
        src     = 0b01U;                    // MCGFLLCLK
        result  = TOMMRO_C_HW_ERR_SUCCESS;
    }
    else if (0 != CLOCK_GetFreq(kCLOCK_McgInternalRefClk)) {
        src     = 0b11U;                    // MCGIRCCLK
        result  = TOMMRO_C_HW_ERR_SUCCESS;
    }

    CLOCK_SetLpuartClock(src);

    return result;
}
#endif

static void _enable_irq(IRQn_Type interrupt) {

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__) && defined (CFG_BLE_PRJ)
    NVIC_SetPriority(interrupt, __UART_ISR_PRIO__ >> (8 - __NVIC_PRIO_BITS));
#endif

    NVIC_ClearPendingIRQ(interrupt);

    EnableIRQ(interrupt);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

#if (defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT) || \
    (defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTNXPHalInit(const tommRoC_hw_template_bus_uart_nxp_hal_config_t* const initConfigPtr) {

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    UART_Type* usart = (UART_Type*) initConfigPtr->usartPtr;
    uart_config_t* usartConfigPtr = (uart_config_t*) initConfigPtr->configPtr;
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    USART_Type* usart = (USART_Type*) initConfigPtr->usartPtr;
    usart_config_t* usartConfigPtr = (usart_config_t*) initConfigPtr->configPtr;
#endif

    _gpio_configure_for_bus(&initConfigPtr->location);

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    if (kStatus_Success != UART_Init(usart, usartConfigPtr, CLOCK_GetFreq(initConfigPtr->clockName))) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    if (kStatus_Success != USART_Init(usart, usartConfigPtr, CLOCK_GetFreq(initConfigPtr->clockName))) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
#endif

    _enable_irq(initConfigPtr->rxTxIRQn);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

void tommRoCHwTemplateBusUARTNXPHalRxIRQEnable(void* const usartPtr) {

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    UART_EnableInterrupts((UART_Type*) usartPtr, kUART_RxDataRegFullInterruptEnable);
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    USART_EnableInterrupts((USART_Type*) usartPtr, kUSART_RxLevelInterruptEnable | kUSART_RxErrorInterruptEnable);
#endif
}

void tommRoCHwTemplateBusUARTNXPHalRxIRQDisable(void* const usartPtr) {

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    UART_DisableInterrupts((UART_Type*) usartPtr, kUART_RxDataRegFullInterruptEnable);
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    USART_DisableInterrupts((USART_Type*) usartPtr, kUSART_RxLevelInterruptEnable | kUSART_RxErrorInterruptEnable);
#endif
}

bool tommRoCHwTemplateBusUARTNXPHalRxIRQIsEnabled(void* const usartPtr) {

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    return (!(0 == (kUART_RxDataRegFullInterruptEnable & UART_GetEnabledInterrupts((UART_Type*) usartPtr))));
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    return (!(0 == ((kUSART_RxLevelInterruptEnable | kUSART_RxErrorInterruptEnable) & USART_GetEnabledInterrupts((USART_Type*) usartPtr))));
#endif
}

void tommRoCHwTemplateBusUARTNXPHalTxIRQEnable(void* const usartPtr) {

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    UART_EnableInterrupts((UART_Type*) usartPtr, kUART_TxDataRegEmptyInterruptEnable);
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    USART_EnableInterrupts((USART_Type*) usartPtr, kUSART_TxLevelInterruptEnable);
#endif
}

void tommRoCHwTemplateBusUARTNXPHalTxIRQDisable(void* const usartPtr) {

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    UART_DisableInterrupts((UART_Type*) usartPtr, kUART_TxDataRegEmptyInterruptEnable);
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    USART_DisableInterrupts((USART_Type*) usartPtr, kUSART_TxLevelInterruptEnable);
#endif
}

bool tommRoCHwTemplateBusUARTNXPHalTxIRQIsEnabled(void* const usartPtr) {

#if defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT
    return (!(0 == (kUART_TxDataRegEmptyInterruptEnable & UART_GetEnabledInterrupts((UART_Type*) usartPtr))));
#elif defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT
    return (!(0 == (kUSART_TxLevelInterruptEnable & USART_GetEnabledInterrupts((USART_Type*) usartPtr))));
#endif
}
#endif

#if defined (FSL_FEATURE_SOC_LPUART_COUNT) && FSL_FEATURE_SOC_LPUART_COUNT
tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTNXPHalLEInit(const tommRoC_hw_template_bus_uart_nxp_hal_config_t* const initConfigPtr) {

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

    LPUART_Type* usart = (LPUART_Type*) initConfigPtr->usartPtr;
    lpuart_config_t* lpUartConfigPtr = (lpuart_config_t*) initConfigPtr->configPtr;

    _gpio_configure_for_bus(&initConfigPtr->location);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _lpuart_clock_configure());

    if (kStatus_Success != LPUART_Init(usart, lpUartConfigPtr, CLOCK_GetFreq(initConfigPtr->clockName))) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    _enable_irq(initConfigPtr->rxTxIRQn);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

void tommRoCHwTemplateBusUARTNXPHalLERxIRQEnable(LPUART_Type* const usartPtr) {
    LPUART_EnableInterrupts(usartPtr, kLPUART_RxDataRegFullInterruptEnable);
}

void tommRoCHwTemplateBusUARTNXPHalLERxIRQDisable(LPUART_Type* const usartPtr) {
    LPUART_DisableInterrupts(usartPtr, kLPUART_RxDataRegFullInterruptEnable);
}

bool tommRoCHwTemplateBusUARTNXPHalLERxIRQIsEnabled(LPUART_Type* const usartPtr) {
    return (!(0 == (kLPUART_RxDataRegFullInterruptEnable & LPUART_GetEnabledInterrupts(usartPtr))));
}

void tommRoCHwTemplateBusUARTNXPHalLETxIRQEnable(LPUART_Type* const usartPtr) {
    LPUART_EnableInterrupts(usartPtr, kLPUART_TxDataRegEmptyInterruptEnable);
}

void tommRoCHwTemplateBusUARTNXPHalLETxIRQDisable(LPUART_Type* const usartPtr) {
    LPUART_DisableInterrupts(usartPtr, kLPUART_TxDataRegEmptyInterruptEnable);
}

bool tommRoCHwTemplateBusUARTNXPHalLETxIRQIsEnabled(LPUART_Type* const usartPtr) {
    return (!(0 == (kLPUART_TxDataRegEmptyInterruptEnable & LPUART_GetEnabledInterrupts(usartPtr))));
}
#endif

#if (defined (FSL_FEATURE_SOC_UART_COUNT) && FSL_FEATURE_SOC_UART_COUNT) || \
    (defined (FSL_FEATURE_SOC_USART_COUNT) && FSL_FEATURE_SOC_USART_COUNT) || \
    (defined (FSL_FEATURE_SOC_LPUART_COUNT) && FSL_FEATURE_SOC_LPUART_COUNT)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTNXPHalSetForLowPowerEnter(const tommRoC_hw_template_bus_uart_nxp_location_t* const locationPtr) {

    TOMMROC_ASSERT_NOT_NULL(locationPtr);

    _gpio_configure_for_low_power(locationPtr);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTNXPHalSetForLowPowerExit(const tommRoC_hw_template_bus_uart_nxp_location_t* const locationPtr) {

    TOMMROC_ASSERT_NOT_NULL(locationPtr);

    _gpio_configure_for_bus(locationPtr);

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif

#endif
