
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusI2CSiLabsHal.h"

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
#if defined (I2C_PRESENT) && I2C_COUNT
static void _gpio_configure_for_bus(const CMU_Clock_TypeDef clock, const tommRoC_hw_template_bus_i2c_silabs_location_t* const locationPtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus) {

    GPIO_Mode_TypeDef mode;

    mode = (TOMMRO_C_UTIL_ENABLED == mcuPullUpStatus) ? (gpioModeWiredAndPullUp) : (gpioModeWiredAnd);

    CMU_ClockEnable(cmuClock_GPIO, true);

    // NOTE: SCL first, to ensure it is high before changing SDA
    GPIO_PinModeSet(locationPtr->gpioSCLPort, locationPtr->gpioSCLPin, mode, 1);
    GPIO_PinModeSet(locationPtr->gpioSDAPort, locationPtr->gpioSDAPin, mode, 1);

    CMU_ClockEnable(clock, true);
}

static void _gpio_configure_for_low_power(const CMU_Clock_TypeDef clock, const tommRoC_hw_template_bus_i2c_silabs_location_t* const locationPtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus) {

    GPIO_Mode_TypeDef mode;
    unsigned int out;

    mode    = (TOMMRO_C_UTIL_ENABLED == mcuPullUpStatus) ? (gpioModeWiredAndPullUp) : (gpioModeDisabled);
    out     = (TOMMRO_C_UTIL_ENABLED == mcuPullUpStatus) ? (1) : (0);

    CMU_ClockEnable(clock, false);

    CMU_ClockEnable(cmuClock_GPIO, true);

    // NOTE: SCL first, to ensure it is high before changing SDA
    GPIO_PinModeSet(locationPtr->gpioSCLPort, locationPtr->gpioSCLPin, mode, out);
    GPIO_PinModeSet(locationPtr->gpioSDAPort, locationPtr->gpioSDAPin, mode, out);
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (I2C_PRESENT) && I2C_COUNT
tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSiLabsHalMasterInit(const tommRoC_hw_template_bus_i2c_silabs_hal_config_t* const initConfigPtr) {

    I2C_TypeDef* i2c = (I2C_TypeDef*) initConfigPtr->i2cPtr;
    I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

#if defined (_GPIO_I2C_ROUTEEN_RESETVALUE)
    uint8_t idx = 0;

#if defined (I2C0)
    if (I2C0 == i2c) { idx = 0; }
#endif
#if defined (I2C1)
    if (I2C1 == i2c) { idx = 1; }
#endif
#if defined (I2C2)
    if (I2C2 == i2c) { idx = 2; }
#endif
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_IS_USED__)
    // Enable clock for HF peripherals
    CMU_ClockEnable(cmuClock_HFPER, true);
#endif
    // Enable clock for module
    CMU_ClockEnable(initConfigPtr->clock, true);

    // Ensure a proper 'reset'
    I2C_Reset(i2c);

    _gpio_configure_for_bus(initConfigPtr->clock, &initConfigPtr->location, initConfigPtr->mcuPullUpStatus);

    // Prepare struct for initializing I2C
    i2cInit.enable  = false;                    // Don't enable I2C upon intialization
    i2cInit.master  = true;                     // Set to master (true)
    i2cInit.freq    = (initConfigPtr->baudRate <= I2C_FREQ_STANDARD_MAX) ? (initConfigPtr->baudRate) : (I2C_FREQ_STANDARD_MAX); // I2C bus frequency to use

    // Initialize I2C with i2cInit struct
    I2C_Init(i2c, &i2cInit);

#if defined (_I2C_ROUTE_LOCATION_MASK)
    // I2C location
    i2c->ROUTE = (i2c->ROUTE & ~_I2C_ROUTE_LOCATION_MASK) | initConfigPtr->location.locationU32;
    i2c->ROUTE |= I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN;
#endif

#if defined (_GPIO_I2C_ROUTEEN_RESETVALUE)
    // Route GPIO pins to I2C module
    GPIO->I2CROUTE[idx].SDAROUTE = (GPIO->I2CROUTE[idx].SDAROUTE & ~_GPIO_I2C_SDAROUTE_MASK) | ((initConfigPtr->location.gpioSDAPort << _GPIO_I2C_SDAROUTE_PORT_SHIFT) | (initConfigPtr->location.gpioSDAPin << _GPIO_I2C_SDAROUTE_PIN_SHIFT));
    GPIO->I2CROUTE[idx].SCLROUTE = (GPIO->I2CROUTE[idx].SCLROUTE & ~_GPIO_I2C_SCLROUTE_MASK) | ((initConfigPtr->location.gpioSCLPort << _GPIO_I2C_SCLROUTE_PORT_SHIFT) | (initConfigPtr->location.gpioSCLPin << _GPIO_I2C_SCLROUTE_PIN_SHIFT));

    // Enable SDA/SCL signals now that they have been routed
    GPIO->I2CROUTE[idx].ROUTEEN = GPIO_I2C_ROUTEEN_SDAPEN | GPIO_I2C_ROUTEEN_SCLPEN;
#endif

    // Prepare I2C interrupt
    NVIC_ClearPendingIRQ(initConfigPtr->IRQn);
    NVIC_EnableIRQ(initConfigPtr->IRQn);

    // Enable I2C
    I2C_Enable(i2c, true);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSiLabsHalSlaveInit(const tommRoC_hw_template_bus_i2c_silabs_hal_config_t* const initConfigPtr) {

    I2C_TypeDef* i2c = (I2C_TypeDef*) initConfigPtr->i2cPtr;
    I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

#if defined (_GPIO_I2C_ROUTEEN_RESETVALUE)
    uint8_t idx = 0;

#if defined (I2C0)
    if (I2C0 == i2c) { idx = 0; }
#endif
#if defined (I2C1)
    if (I2C1 == i2c) { idx = 1; }
#endif
#if defined (I2C2)
    if (I2C2 == i2c) { idx = 2; }
#endif
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_IS_USED__)
    // Enable clock for HF peripherals
    CMU_ClockEnable(cmuClock_HFPER, true);
#endif
    // Enable clock for module
    CMU_ClockEnable(initConfigPtr->clock, true);

    // Ensure a proper 'reset'
    I2C_Reset(i2c);

    _gpio_configure_for_bus(initConfigPtr->clock, &initConfigPtr->location, initConfigPtr->mcuPullUpStatus);

    // Prepare struct for initializing I2C
    i2cInit.enable  = false;                    // Don't enable I2C upon intialization
    i2cInit.master  = false;                    // Set to slave (false)

    // Initialize I2C with i2cInit struct
    I2C_Init(i2c, &i2cInit);

#if defined (_I2C_ROUTE_LOCATION_MASK)
    // I2C location
    i2c->ROUTE = (i2c->ROUTE & ~_I2C_ROUTE_LOCATION_MASK) | initConfigPtr->location.locationU32;
    i2c->ROUTE |= I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN;
#endif

#if defined (_GPIO_I2C_ROUTEEN_RESETVALUE)
    // Route GPIO pins to I2C module
    GPIO->I2CROUTE[idx].SDAROUTE = (GPIO->I2CROUTE[idx].SDAROUTE & ~_GPIO_I2C_SDAROUTE_MASK) | ((initConfigPtr->location.gpioSDAPort << _GPIO_I2C_SDAROUTE_PORT_SHIFT) | (initConfigPtr->location.gpioSDAPin << _GPIO_I2C_SDAROUTE_PIN_SHIFT));
    GPIO->I2CROUTE[idx].SCLROUTE = (GPIO->I2CROUTE[idx].SCLROUTE & ~_GPIO_I2C_SCLROUTE_MASK) | ((initConfigPtr->location.gpioSCLPort << _GPIO_I2C_SCLROUTE_PORT_SHIFT) | (initConfigPtr->location.gpioSCLPin << _GPIO_I2C_SCLROUTE_PIN_SHIFT));

    // Enable SDA/SCL signals now that they have been routed
    GPIO->I2CROUTE[idx].ROUTEEN = GPIO_I2C_ROUTEEN_SDAPEN | GPIO_I2C_ROUTEEN_SCLPEN;
#endif







/*
    // Setting up to enable slave mode
    I2C_SlaveAddressSet(i2c, I2C_ADDRESS);
    I2C_SlaveAddressMaskSet(i2c, 0x7F); // must match exact address
    I2C0->CTRL = I2C_CTRL_SLAVE;
*/




    // Enable I2C
    I2C_Enable(i2c, true);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSiLabsHalSetForLowPowerEnter(const CMU_Clock_TypeDef clock, const tommRoC_hw_template_bus_i2c_silabs_location_t* const locationPtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus) {

    TOMMROC_ASSERT_NOT_NULL(locationPtr);

    _gpio_configure_for_low_power(clock, locationPtr, mcuPullUpStatus);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSiLabsHalSetForLowPowerExit(const CMU_Clock_TypeDef clock,const tommRoC_hw_template_bus_i2c_silabs_location_t* const locationPtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus) {

    TOMMROC_ASSERT_NOT_NULL(locationPtr);

    _gpio_configure_for_bus(clock, locationPtr, mcuPullUpStatus);

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif
