
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusUARTSiLabsHal.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)

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
#if defined (LEUART_PRESENT) && LEUART_COUNT
static void _start_LE_clock(
        const   uint32_t            baudRate,
        const   CMU_Clock_TypeDef   leUARTClock) {

    CMU_ClockEnable(cmuClock_HFLE, true);

    // Start LFXO, and use LFXO for low-energy modules
    if (baudRate <= 9600) {
        CMU_OscillatorEnable(cmuOsc_LFXO, true, true);
        CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);
    }
    else {
        CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_HFCLKLE);
        CMU_ClockDivSet(leUARTClock, cmuClkDiv_4);    // 1/2/4/8
    }

    CMU_ClockEnable(cmuClock_LFB, true);
}
#endif

#if (defined (USART_PRESENT) && USART_COUNT) || \
    (defined (LEUART_PRESENT) && LEUART_COUNT)
static void _gpio_configure_for_bus(const CMU_Clock_TypeDef clock, const tommRoC_hw_template_bus_uart_silabs_location_t* const locationPtr) {

    CMU_ClockEnable(cmuClock_GPIO, true);

    // To avoid false start, configure TX pin as output/high
    GPIO_PinModeSet(locationPtr->gpioTxPort, locationPtr->gpioTxPin, gpioModePushPull, 1);
    GPIO_PinModeSet(locationPtr->gpioRxPort, locationPtr->gpioRxPin, gpioModeInput, 0);

    CMU_ClockEnable(clock, true);
}

#if !defined (__TOMMROC_TEMPLATE_ARM_EFR32_IS_USED__)
static void _gpio_configure_for_low_power(const CMU_Clock_TypeDef clock, const tommRoC_hw_template_bus_uart_silabs_location_t* const locationPtr) {

    CMU_ClockEnable(clock, false);

    CMU_ClockEnable(cmuClock_GPIO, true);

    GPIO_PinModeSet(locationPtr->gpioTxPort, locationPtr->gpioTxPin, gpioModeDisabled, 0);
    GPIO_PinModeSet(locationPtr->gpioRxPort, locationPtr->gpioRxPin, gpioModeDisabled, 0);
}
#endif
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (USART_PRESENT) && USART_COUNT
tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTSiLabsHalInit(const tommRoC_hw_template_bus_uart_silabs_hal_config_t* const initConfigPtr) {

    USART_TypeDef* usart = (USART_TypeDef*) initConfigPtr->usartPtr;
    USART_InitAsync_TypeDef uartInit = USART_INITASYNC_DEFAULT;

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

#if defined (_GPIO_USART_ROUTEEN_RESETVALUE)
    uint8_t idx = 0;

#if defined (USART0)
    if (USART0 == usart) { idx = 0; }
#endif
#if defined (USART1)
    if (USART1 == usart) { idx = 1; }
#endif
#if defined (USART2)
    if (USART2 == usart) { idx = 2; }
#endif
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_IS_USED__)
    // Enable clock for HF peripherals
    CMU_ClockEnable(cmuClock_HFPER, true);
#endif
    // Enable clock for module
    CMU_ClockEnable(initConfigPtr->clock, true);

    // Ensure a proper 'reset'
    USART_Reset(usart);

    _gpio_configure_for_bus(initConfigPtr->clock, &initConfigPtr->location);

    // Prepare struct for initializing USART in asynchronous mode
    uartInit.enable         = usartDisable;             // Don't enable USART upon intialization
    uartInit.baudrate       = initConfigPtr->baudRate;  // Baud rate
    uartInit.databits       = usartDatabits8;           // Number of data bits. Range is 4 to 10
    uartInit.parity         = usartNoParity;            // Parity mode
    uartInit.stopbits       = usartStopbits1;           // Number of stop bits. Range is 0 to 2

    // Initialize USART with uartInit struct
    USART_InitAsync(usart, &uartInit);

#if defined (_USART_ROUTE_LOCATION_MASK)
    // UART location
    usart->ROUTE = (usart->ROUTE & ~_USART_ROUTE_LOCATION_MASK) | initConfigPtr->location.locationU32;
    usart->ROUTE |= USART_ROUTE_TXPEN | USART_ROUTE_RXPEN;
#endif

#if defined (_GPIO_USART_ROUTEEN_RESETVALUE)
    // Route GPIO pins to USART module
    GPIO->USARTROUTE[idx].RXROUTE   = (GPIO->USARTROUTE[idx].RXROUTE & ~_GPIO_USART_RXROUTE_MASK) | ((initConfigPtr->location.gpioRxPort << _GPIO_USART_RXROUTE_PORT_SHIFT) | (initConfigPtr->location.gpioRxPin << _GPIO_USART_RXROUTE_PIN_SHIFT));
    GPIO->USARTROUTE[idx].TXROUTE   = (GPIO->USARTROUTE[idx].TXROUTE & ~_GPIO_USART_TXROUTE_MASK) | ((initConfigPtr->location.gpioTxPort << _GPIO_USART_TXROUTE_PORT_SHIFT) | (initConfigPtr->location.gpioTxPin << _GPIO_USART_TXROUTE_PIN_SHIFT));

    // Enable RX/TX signals now that they have been routed
    GPIO->USARTROUTE[idx].ROUTEEN   = GPIO_USART_ROUTEEN_RXPEN | GPIO_USART_ROUTEEN_TXPEN;
#endif

    // Prepare UART Rx and Tx interrupts
#if defined (_USART_IFC_MASK)
    USART_IntClear(usart, _USART_IFC_MASK);
#endif
#if defined (USART_IEN_RXDATAV)
    USART_IntEnable(usart, USART_IEN_RXDATAV);
#endif
    NVIC_ClearPendingIRQ(initConfigPtr->rxIRQn);
    NVIC_ClearPendingIRQ(initConfigPtr->txIRQn);
    NVIC_EnableIRQ(initConfigPtr->rxIRQn);
    NVIC_EnableIRQ(initConfigPtr->txIRQn);    

    // Enable UART
    USART_Enable(usart, usartEnable);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

void tommRoCHwTemplateBusUARTSiLabsHalRxIRQEnable(USART_TypeDef* const usartPtr) {
    USART_IntEnable(usartPtr, USART_IEN_RXDATAV);
}

void tommRoCHwTemplateBusUARTSiLabsHalRxIRQDisable(USART_TypeDef* const usartPtr) {
    USART_IntDisable(usartPtr, USART_IEN_RXDATAV);
}

bool tommRoCHwTemplateBusUARTSiLabsHalRxIRQIsEnabled(USART_TypeDef* const usartPtr) {
    return (!(0 == (USART_IEN_RXDATAV & usartPtr->IEN)));
}

void tommRoCHwTemplateBusUARTSiLabsHalTxIRQEnable(USART_TypeDef* const usartPtr) {
    USART_IntEnable(usartPtr, USART_IEN_TXBL);
}

void tommRoCHwTemplateBusUARTSiLabsHalTxIRQDisable(USART_TypeDef* const usartPtr) {
    USART_IntDisable(usartPtr, USART_IEN_TXBL);
}

bool tommRoCHwTemplateBusUARTSiLabsHalTxIRQIsEnabled(USART_TypeDef* const usartPtr) {
    return (!(0 == (USART_IEN_TXBL & usartPtr->IEN)));
}
#endif

#if defined (LEUART_PRESENT) && LEUART_COUNT
tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTSiLabsHalLEInit(const tommRoC_hw_template_bus_uart_silabs_hal_config_t* const initConfigPtr) {

    LEUART_TypeDef* leuart = (LEUART_TypeDef*) initConfigPtr->usartPtr;
    LEUART_Init_TypeDef leuartInit = LEUART_INIT_DEFAULT;

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

    TOMMROC_ASSERT_EQUALS(initConfigPtr->rxIRQn, initConfigPtr->txIRQn);

    if (initConfigPtr->rxIRQn != initConfigPtr->txIRQn) {
        return TOMMRO_C_HW_PARAM_ERR;
    }

    // Start LFXO clock
    _start_LE_clock(initConfigPtr->baudRate, initConfigPtr->clock);

    // Enable clock for module
    CMU_ClockEnable(initConfigPtr->clock, true);

    // Ensure a proper 'reset'
    LEUART_Reset(leuart);

    _gpio_configure_for_bus(initConfigPtr->clock, &initConfigPtr->location);

    // Prepare struct for initializing USART in asynchronous mode
    leuartInit.enable   = leuartDisable;              // Don't enable USART upon intialization
    leuartInit.baudrate = initConfigPtr->baudRate;    // Baud rate
    leuartInit.databits = leuartDatabits8;            // Number of data bits. Range is 4 to 10
    leuartInit.parity   = leuartNoParity;             // Parity mode
    leuartInit.stopbits = leuartStopbits1;            // Number of stop bits. Range is 0 to 2

    // Initialize USART with uartInit struct
    LEUART_Init(leuart, &leuartInit);

#if defined (_LEUART_ROUTE_LOCATION_MASK)
    // LEUART location
    leuart->ROUTE = (leuart->ROUTE & ~_LEUART_ROUTE_LOCATION_MASK) | initConfigPtr->location.locationU32;
    leuart->ROUTE |= LEUART_ROUTE_TXPEN | LEUART_ROUTE_RXPEN;
#endif

    // Prepare UART Rx and Tx interrupts
#if defined (_LEUART_IFC_MASK)
    LEUART_IntClear(leuart, _LEUART_IFC_MASK);
#endif
#if defined (LEUART_IEN_RXDATAV)
    LEUART_IntEnable(leuart, LEUART_IEN_RXDATAV);
#endif
    NVIC_ClearPendingIRQ(initConfigPtr->rxIRQn);
    NVIC_EnableIRQ(initConfigPtr->rxIRQn);

    // Enable UART
    LEUART_Enable(leuart, leuartEnable);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

void tommRoCHwTemplateBusUARTSiLabsHalLERxIRQEnable(LEUART_TypeDef* const usartPtr) {
    LEUART_IntEnable(usartPtr, LEUART_IEN_RXDATAV);
}

void tommRoCHwTemplateBusUARTSiLabsHalLERxIRQDisable(LEUART_TypeDef* const usartPtr) {
    LEUART_IntDisable(usartPtr, LEUART_IEN_RXDATAV);
}

bool tommRoCHwTemplateBusUARTSiLabsHalLERxIRQIsEnabled(LEUART_TypeDef* const usartPtr) {
    return (!(0 == (LEUART_IEN_RXDATAV & usartPtr->IEN)));
}

void tommRoCHwTemplateBusUARTSiLabsHalLETxIRQEnable(LEUART_TypeDef* const usartPtr) {
    LEUART_IntEnable(usartPtr, LEUART_IEN_TXBL);
}

void tommRoCHwTemplateBusUARTSiLabsHalLETxIRQDisable(LEUART_TypeDef* const usartPtr) {
    LEUART_IntDisable(usartPtr, LEUART_IEN_TXBL);
}

bool tommRoCHwTemplateBusUARTSiLabsHalLETxIRQIsEnabled(LEUART_TypeDef* const usartPtr) {
    return (!(0 == (LEUART_IEN_TXBL & usartPtr->IEN)));
}
#endif

#if (defined (USART_PRESENT) && USART_COUNT) || \
    (defined (LEUART_PRESENT) && LEUART_COUNT)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTSiLabsHalSetForLowPowerEnter(const CMU_Clock_TypeDef clock, const tommRoC_hw_template_bus_uart_silabs_location_t* const locationPtr) {

#if defined (__TOMMROC_TEMPLATE_ARM_EFR32_IS_USED__)
    TOMMROC_UTIL_UNUSED_PARAM(clock);
#endif

    TOMMROC_ASSERT_NOT_NULL(locationPtr);

#if !defined (__TOMMROC_TEMPLATE_ARM_EFR32_IS_USED__)
    _gpio_configure_for_low_power(clock, locationPtr);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusUARTSiLabsHalSetForLowPowerExit(const CMU_Clock_TypeDef clock, const tommRoC_hw_template_bus_uart_silabs_location_t* const locationPtr) {

#if defined (__TOMMROC_TEMPLATE_ARM_EFR32_IS_USED__)
    TOMMROC_UTIL_UNUSED_PARAM(clock);
#endif

    TOMMROC_ASSERT_NOT_NULL(locationPtr);

#if !defined (__TOMMROC_TEMPLATE_ARM_EFR32_IS_USED__)
    _gpio_configure_for_bus(clock, locationPtr);
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif
