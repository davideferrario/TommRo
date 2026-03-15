
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusSPISiLabsHal.h"

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
#if (defined (USART_PRESENT) && USART_COUNT)
static void _gpio_configure_for_bus(
        const   CMU_Clock_TypeDef                                       clock,
        const   tommRoC_hw_template_bus_spi_silabs_location_t*  const   locationPtr,
        const   GPIO_Mode_TypeDef                                       sckPinMode,
        const   GPIO_Mode_TypeDef                                       misoPinMode,
        const   GPIO_Mode_TypeDef                                       mosiPinMode) {

    CMU_ClockEnable(cmuClock_GPIO, true);

    GPIO_PinModeSet(locationPtr->gpioSCKPort, locationPtr->gpioSCKPin, sckPinMode, 0);
    GPIO_PinModeSet(locationPtr->gpioMISOPort, locationPtr->gpioMISOPin, misoPinMode, 0);
    GPIO_PinModeSet(locationPtr->gpioMOSIPort, locationPtr->gpioMOSIPin, mosiPinMode, 0);

    CMU_ClockEnable(clock, true);
}

static void _gpio_configure_for_bus_master(const CMU_Clock_TypeDef clock, const tommRoC_hw_template_bus_spi_silabs_location_t* const locationPtr) {

    _gpio_configure_for_bus(clock, locationPtr, gpioModePushPull, gpioModeInput, gpioModePushPull);
}

static void _gpio_configure_for_bus_slave(const CMU_Clock_TypeDef clock, const tommRoC_hw_template_bus_spi_silabs_location_t* const locationPtr) {

    _gpio_configure_for_bus(clock, locationPtr, gpioModeInput, gpioModePushPull, gpioModeInput);
}

static void _gpio_configure_for_low_power(const CMU_Clock_TypeDef clock, const tommRoC_hw_template_bus_spi_silabs_location_t* const locationPtr) {

    CMU_ClockEnable(clock, false);

    CMU_ClockEnable(cmuClock_GPIO, true);

    // To avoid false start, configure output as high
    GPIO_PinModeSet(locationPtr->gpioSCKPort, locationPtr->gpioSCKPin, gpioModeDisabled, 0);
    GPIO_PinModeSet(locationPtr->gpioMISOPort, locationPtr->gpioMISOPin, gpioModeDisabled, 0);
    GPIO_PinModeSet(locationPtr->gpioMOSIPort, locationPtr->gpioMOSIPin, gpioModeDisabled, 0);
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (USART_PRESENT) && USART_COUNT
tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISiLabsHalMasterInit(const tommRoC_hw_template_bus_spi_silabs_hal_config_t* const initConfigPtr) {

    USART_TypeDef* spi = (USART_TypeDef*) initConfigPtr->spiPtr;
    USART_InitSync_TypeDef spiInit = USART_INITSYNC_DEFAULT;

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

#if defined (_GPIO_USART_ROUTEEN_RESETVALUE)
    uint8_t idx = 0;

#if defined (USART0)
    if (USART0 == spi) { idx = 0; }
#endif
#if defined (USART1)
    if (USART1 == spi) { idx = 1; }
#endif
#if defined (USART2)
    if (USART2 == spi) { idx = 2; }
#endif
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_IS_USED__)
    // Enable clock for HF peripherals
    CMU_ClockEnable(cmuClock_HFPER, true);
#endif
    // Enable clock for module
    CMU_ClockEnable(initConfigPtr->clock, true);

    // Ensure a proper 'reset'
    USART_Reset(spi);

    _gpio_configure_for_bus_master(initConfigPtr->clock, &initConfigPtr->location);

    // Prepare struct for initializing USART in synchronous mode
    spiInit.enable          = usartDisable;             // Don't enable USART upon intialization
    spiInit.baudrate        = initConfigPtr->baudRate;  // Baud rate
    spiInit.databits        = usartDatabits8;           // Number of data bits. Range is 4 to 10
    spiInit.master          = true;                     // Master mode
    spiInit.msbf            = true;                     // Send most significant bit first
    spiInit.clockMode       = initConfigPtr->clockMode; // Clock polarity/phase mode
#if defined (USART_TRIGCTRL_AUTOTXTEN)
    spiInit.autoTx          = false;                    // Disable Auto TX
#endif
    spiInit.autoCsEnable    = false;                    // Disable Auto CS
#if defined (_USART_TIMING_CSHOLD_MASK)
    spiInit.autoCsHold      = 0;                        // Auto CS hold time [baud cycles]
    spiInit.autoCsSetup     = 0;                        // Auto CS setup time[baud cycles]
#endif

    // Initialize SPI with spiInit struct
    USART_InitSync(spi, &spiInit);

#if defined (_USART_ROUTE_LOCATION_MASK)
    // SPI location
    spi->ROUTE = (spi->ROUTE & ~_USART_ROUTE_LOCATION_MASK) | initConfigPtr->location.locationU32;
    spi->ROUTE |= USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_CLKPEN;
#endif

#if defined (_GPIO_USART_ROUTEEN_RESETVALUE)
    // Route GPIO pins to SPI module
    GPIO->USARTROUTE[idx].RXROUTE   = (GPIO->USARTROUTE[idx].RXROUTE    & ~_GPIO_USART_RXROUTE_MASK)    | ((initConfigPtr->location.gpioMISOPort    << _GPIO_USART_RXROUTE_PORT_SHIFT)  | (initConfigPtr->location.gpioMISOPin  << _GPIO_USART_RXROUTE_PIN_SHIFT));
    GPIO->USARTROUTE[idx].CLKROUTE  = (GPIO->USARTROUTE[idx].CLKROUTE   & ~_GPIO_USART_CLKROUTE_MASK)   | ((initConfigPtr->location.gpioSCKPort     << _GPIO_USART_CLKROUTE_PORT_SHIFT) | (initConfigPtr->location.gpioSCKPin   << _GPIO_USART_CLKROUTE_PIN_SHIFT));
    GPIO->USARTROUTE[idx].TXROUTE   = (GPIO->USARTROUTE[idx].TXROUTE    & ~_GPIO_USART_TXROUTE_MASK)    | ((initConfigPtr->location.gpioMOSIPort    << _GPIO_USART_TXROUTE_PORT_SHIFT)  | (initConfigPtr->location.gpioMOSIPin  << _GPIO_USART_TXROUTE_PIN_SHIFT));

    // Enable CLK/RX/TX signals now that they have been routed
    GPIO->USARTROUTE[idx].ROUTEEN   = GPIO_USART_ROUTEEN_RXPEN | GPIO_USART_ROUTEEN_CLKPEN | GPIO_USART_ROUTEEN_TXPEN;
#endif

    // Enable SPI
    USART_Enable(spi, usartEnable);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISiLabsHalSlaveInit(const tommRoC_hw_template_bus_spi_silabs_hal_config_t* const initConfigPtr) {

    USART_TypeDef* spi = (USART_TypeDef*) initConfigPtr->spiPtr;
    USART_InitSync_TypeDef spiInit = USART_INITSYNC_DEFAULT;

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

#if defined (_GPIO_USART_ROUTEEN_RESETVALUE)
    uint8_t idx = 0;

#if defined (USART0)
    if (USART0 == spi) { idx = 0; }
#endif
#if defined (USART1)
    if (USART1 == spi) { idx = 1; }
#endif
#if defined (USART2)
    if (USART2 == spi) { idx = 2; }
#endif
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_IS_USED__)
    // Enable clock for HF peripherals
    CMU_ClockEnable(cmuClock_HFPER, true);
#endif
    // Enable clock for module
    CMU_ClockEnable(initConfigPtr->clock, true);

    // Ensure a proper 'reset'
    USART_Reset(spi);

    _gpio_configure_for_bus_slave(initConfigPtr->clock, &initConfigPtr->location);

    // Prepare struct for initializing USART in synchronous mode
    spiInit.enable          = usartDisable;             // Don't enable USART upon intialization
    spiInit.baudrate        = initConfigPtr->baudRate;  // Baud rate
    spiInit.databits        = usartDatabits8;           // Number of data bits. Range is 4 to 10
    spiInit.master          = false;                    // Slave mode
    spiInit.msbf            = true;                     // Send most significant bit first
    spiInit.clockMode       = initConfigPtr->clockMode; // Clock polarity/phase mode
#if defined (USART_TRIGCTRL_AUTOTXTEN)
    spiInit.autoTx          = false;                    // Disable Auto TX
#endif
    spiInit.autoCsEnable    = false;                    // Disable Auto CS
#if defined (_USART_TIMING_CSHOLD_MASK)
    spiInit.autoCsHold      = 0;                        // Auto CS hold time [baud cycles]
    spiInit.autoCsSetup     = 0;                        // Auto CS setup time[baud cycles]
#endif

    // Initialize SPI with spiInit struct
    USART_InitSync(spi, &spiInit);

#if defined (_USART_ROUTE_LOCATION_MASK)
    // SPI location
    spi->ROUTE = (spi->ROUTE & ~_USART_ROUTE_LOCATION_MASK) | initConfigPtr->location.locationU32;
    spi->ROUTE |= USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_CLKPEN;
#endif

#if defined (_GPIO_USART_ROUTEEN_RESETVALUE)
    // Route GPIO pins to SPI module
    GPIO->USARTROUTE[idx].RXROUTE   = (GPIO->USARTROUTE[idx].RXROUTE    & ~_GPIO_USART_RXROUTE_MASK)    | ((initConfigPtr->location.gpioMOSIPort    << _GPIO_USART_RXROUTE_PORT_SHIFT)  | (initConfigPtr->location.gpioMOSIPin  << _GPIO_USART_RXROUTE_PIN_SHIFT));
    GPIO->USARTROUTE[idx].CLKROUTE  = (GPIO->USARTROUTE[idx].CLKROUTE   & ~_GPIO_USART_CLKROUTE_MASK)   | ((initConfigPtr->location.gpioSCKPort     << _GPIO_USART_CLKROUTE_PORT_SHIFT) | (initConfigPtr->location.gpioSCKPin   << _GPIO_USART_CLKROUTE_PIN_SHIFT));
    GPIO->USARTROUTE[idx].TXROUTE   = (GPIO->USARTROUTE[idx].TXROUTE    & ~_GPIO_USART_TXROUTE_MASK)    | ((initConfigPtr->location.gpioMISOPort    << _GPIO_USART_TXROUTE_PORT_SHIFT)  | (initConfigPtr->location.gpioMISOPin  << _GPIO_USART_TXROUTE_PIN_SHIFT));

    // Enable CLK/RX/TX signals now that they have been routed
    GPIO->USARTROUTE[idx].ROUTEEN   = GPIO_USART_ROUTEEN_RXPEN | GPIO_USART_ROUTEEN_CLKPEN | GPIO_USART_ROUTEEN_TXPEN;
#endif

    // Enable SPI
    USART_Enable(spi, usartEnable);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISiLabsHalSetForLowPowerEnter(const CMU_Clock_TypeDef clock, const tommRoC_hw_template_bus_spi_silabs_location_t* const locationPtr) {

    TOMMROC_ASSERT_NOT_NULL(locationPtr);

    _gpio_configure_for_low_power(clock, locationPtr);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISiLabsHalSetForLowPowerExit(const CMU_Clock_TypeDef clock, const tommRoC_hw_template_bus_spi_silabs_location_t* const locationPtr) {

    TOMMROC_ASSERT_NOT_NULL(locationPtr);

    _gpio_configure_for_bus_master(clock, locationPtr);

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif
