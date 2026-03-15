
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusI2CNXPHal.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#include "bus/i2c/master/tommRoCHwTemplateBusI2CMasterDEF.h"

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "env/tommRoCTemplateEnv.h"

#include "fsl_gpio.h"
#if (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT) || (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT)
#include "fsl_iocon.h"
#endif
#if defined (FSL_FEATURE_SOC_PORT_COUNT) && FSL_FEATURE_SOC_PORT_COUNT
#include "fsl_port.h"
#endif
#if defined (FSL_FEATURE_SOC_I2C_COUNT) && FSL_FEATURE_SOC_I2C_COUNT
#include "fsl_i2c.h"
#endif

#if defined (FSL_FEATURE_SOC_I2C_COUNT) && FSL_FEATURE_SOC_I2C_COUNT
#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__) && defined (CFG_BLE_PRJ)
// NOTE: this is needed because of bug in "fsl_i2c.h" file of NXP system
extern uint32_t I2C_GetInstance(I2C_Type *base);
#endif
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __I2C_ISR_PRIO__    (0x40)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
static void _gpio_configure_for_bus(const tommRoC_hw_template_bus_i2c_nxp_location_t* const locationPtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus) {

    TOMMROC_ASSERT_NOT_NULL(locationPtr);

#if (!((defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)))
    CLOCK_EnableClock(locationPtr->clockName);
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
    port_pin_config_t portSDAPinConfig = {
#if defined (FSL_FEATURE_PORT_HAS_PULL_ENABLE) && FSL_FEATURE_PORT_HAS_PULL_ENABLE
#if (FSL_PORT_DRIVER_VERSION == (MAKE_VERSION(2, 0, 2)))
            .pullSelect             = (TOMMRO_C_UTIL_ENABLED == mcuPullUpStatus) ? (kPORT_PullUp) : (kPORT_PullDisable),    // Internal pull-up selection
#else
            .pullSelect             = (TOMMRO_C_UTIL_ENABLED == mcuPullUpStatus) ? (kPORT_PullEnable) : (kPORT_PullDisable),    // Internal pull-up selection
#endif
#endif
#if defined (FSL_FEATURE_PORT_HAS_SLEW_RATE) && FSL_FEATURE_PORT_HAS_SLEW_RATE
            .slewRate               = kPORT_FastSlewRate,           // Fast slew rate is configured
#endif
#if defined (FSL_FEATURE_PORT_HAS_PASSIVE_FILTER) && FSL_FEATURE_PORT_HAS_PASSIVE_FILTER
            .passiveFilterEnable    = kPORT_PassiveFilterDisable,   // Passive filter is disabled
#endif
#if defined (FSL_FEATURE_PORT_HAS_OPEN_DRAIN) && FSL_FEATURE_PORT_HAS_OPEN_DRAIN
            .openDrainEnable        = kPORT_OpenDrainEnable,        // Open drain is enabled
#endif
#if defined (FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH) && FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
            .driveStrength          = kPORT_LowDriveStrength,       // Low drive strength is configured
#endif
#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
            .mux                    = locationPtr->gpioSDAPortMux,  // Pin is configured as I2Cx_SDA
#endif
#if defined (FSL_FEATURE_PORT_HAS_PIN_CONTROL_LOCK) && FSL_FEATURE_PORT_HAS_PIN_CONTROL_LOCK
            .lockRegister           = kPORT_UnlockRegister,         // Pin Control Register fields [15:0] are not locked
#endif
    };

    port_pin_config_t portSCLPinConfig = {
#if defined (FSL_FEATURE_PORT_HAS_PULL_ENABLE) && FSL_FEATURE_PORT_HAS_PULL_ENABLE
#if (FSL_PORT_DRIVER_VERSION == (MAKE_VERSION(2, 0, 2)))
            .pullSelect             = (TOMMRO_C_UTIL_ENABLED == mcuPullUpStatus) ? (kPORT_PullUp) : (kPORT_PullDisable),    // Internal pull-up selection
#else
            .pullSelect             = (TOMMRO_C_UTIL_ENABLED == mcuPullUpStatus) ? (kPORT_PullEnable) : (kPORT_PullDisable),    // Internal pull-up selection
#endif
#endif
#if defined (FSL_FEATURE_PORT_HAS_SLEW_RATE) && FSL_FEATURE_PORT_HAS_SLEW_RATE
            .slewRate               = kPORT_FastSlewRate,           // Fast slew rate is configured
#endif
#if defined (FSL_FEATURE_PORT_HAS_PASSIVE_FILTER) && FSL_FEATURE_PORT_HAS_PASSIVE_FILTER
            .passiveFilterEnable    = kPORT_PassiveFilterDisable,   // Passive filter is disabled
#endif
#if defined (FSL_FEATURE_PORT_HAS_OPEN_DRAIN) && FSL_FEATURE_PORT_HAS_OPEN_DRAIN
            .openDrainEnable        = kPORT_OpenDrainEnable,        // Open drain is enabled
#endif
#if defined (FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH) && FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
            .driveStrength          = kPORT_LowDriveStrength,       // Low drive strength is configured
#endif
#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
            .mux                    = locationPtr->gpioSCLPortMux,  // Pin is configured as I2Cx_SCL
#endif
#if defined (FSL_FEATURE_PORT_HAS_PIN_CONTROL_LOCK) && FSL_FEATURE_PORT_HAS_PIN_CONTROL_LOCK
            .lockRegister           = kPORT_UnlockRegister,         // Pin Control Register fields [15:0] are not locked
#endif
    };

    // NOTE: SCL first, to ensure it is high before changing SDA
    PORT_SetPinConfig(locationPtr->gpioSCLPort, locationPtr->gpioSCLPin, &portSCLPinConfig);
    PORT_SetPinConfig(locationPtr->gpioSDAPort, locationPtr->gpioSDAPin, &portSDAPinConfig);

#elif (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)
    uint32_t sdaModeFunc = (
            locationPtr->sdaIOCONFunc                                                               |   // Select pin function
            ((TOMMRO_C_UTIL_ENABLED == mcuPullUpStatus) ? (IOCON_MODE_PULLUP) : (IOCON_MODE_HIGHZ)) |   // Select PullUp/High-Z function
            IOCON_DRIVE_LOW                                                                             // Enable low drive strength
    );

    uint32_t sclModeFunc = (
            locationPtr->sclIOCONFunc                                                               |   // Select pin function
            ((TOMMRO_C_UTIL_ENABLED == mcuPullUpStatus) ? (IOCON_MODE_PULLUP) : (IOCON_MODE_HIGHZ)) |   // Select PullUp/High-Z function
            IOCON_DRIVE_LOW                                                                             // Enable low drive strength
    );

    // NOTE: SCL first, to ensure it is high before changing SDA
    IOCON_PinMuxSet(IOCON, locationPtr->sclPortIdx, locationPtr->sclPin, sclModeFunc);
    IOCON_PinMuxSet(IOCON, locationPtr->sdaPortIdx, locationPtr->sdaPin, sdaModeFunc);

#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
    if (locationPtr->portSetPinSelectNeeded) {
        PORT_SetPinSelect(locationPtr->portModule, locationPtr->portPinSelect);
    }
#endif

#if (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)
    CLOCK_EnableClock(locationPtr->clockName);
#endif
}

static void _gpio_configure_for_low_power(const tommRoC_hw_template_bus_i2c_nxp_location_t* const locationPtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus) {

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

    TOMMROC_UTIL_UNUSED_PARAM(mcuPullUpStatus);

    // NOTE: SCL first, to ensure it is high before changing SDA
    PORT_SetPinMux(locationPtr->gpioSCLPort, locationPtr->gpioSCLPin, kPORT_MuxAsGpio);
    PORT_SetPinMux(locationPtr->gpioSDAPort, locationPtr->gpioSDAPin, kPORT_MuxAsGpio);

    GPIO_PinInit(locationPtr->gpioSCLGpio, locationPtr->gpioSCLPin, &gpioConfigAsInput);
    GPIO_PinInit(locationPtr->gpioSDAGpio, locationPtr->gpioSDAPin, &gpioConfigAsInput);

#elif (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)
    uint32_t modeFunc = (
            IOCON_FUNC0                                                                             |   // Select pin function (FUNC0 -> GPIO)
            ((TOMMRO_C_UTIL_ENABLED == mcuPullUpStatus) ? (IOCON_MODE_PULLUP) : (IOCON_MODE_HIGHZ)) |   // Select PullUp/High-Z function
            IOCON_DRIVE_LOW                                                                             // Enable low drive strength
    );

    // NOTE: SCL first, to ensure it is high before changing SDA
    IOCON_PinMuxSet(IOCON, locationPtr->sclPortIdx, locationPtr->sclPin, modeFunc);
    IOCON_PinMuxSet(IOCON, locationPtr->sdaPortIdx, locationPtr->sdaPin, modeFunc);

    GPIO_PinInit(locationPtr->gpioSCLGpio, locationPtr->sclPin, &gpioConfigAsInput);
    GPIO_PinInit(locationPtr->gpioSDAGpio, locationPtr->sdaPin, &gpioConfigAsInput);

#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
    // NOTE: SCL first, to ensure it is high before changing SDA
    GPIO_PinInit(locationPtr->gpioSCLPort, locationPtr->gpioSCLPin, &gpioConfigAsInput);
    GPIO_PinInit(locationPtr->gpioSDAPort, locationPtr->gpioSDAPin, &gpioConfigAsInput);
#endif
}

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (FSL_FEATURE_SOC_I2C_COUNT) && FSL_FEATURE_SOC_I2C_COUNT
tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNXPHalMasterInit(const tommRoC_hw_template_bus_i2c_nxp_hal_config_t* const initConfigPtr) {

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__) && defined (CFG_BLE_PRJ)
    static const IRQn_Type i2cIRQs[] = I2C_IRQS;
    IRQn_Type i2cIRQn;
#endif

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

    I2C_Type* i2c = (I2C_Type*) initConfigPtr->i2cPtr;
    i2c_master_config_t* i2cMasterConfigPtr = (i2c_master_config_t*) initConfigPtr->configPtr;

    _gpio_configure_for_bus(&initConfigPtr->location, initConfigPtr->mcuPullUpStatus);

    I2C_MasterInit(i2c, i2cMasterConfigPtr, CLOCK_GetFreq(initConfigPtr->clockName));

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__) && defined (CFG_BLE_PRJ)
    i2cIRQn = i2cIRQs[I2C_GetInstance(i2c)];
    NVIC_SetPriority(i2cIRQn, __I2C_ISR_PRIO__ >> (8 - __NVIC_PRIO_BITS));
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNXPHalSlaveInit(const tommRoC_hw_template_bus_i2c_nxp_hal_config_t* const initConfigPtr) {

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__) && defined (CFG_BLE_PRJ)
    static const IRQn_Type i2cIRQs[] = I2C_IRQS;
    IRQn_Type i2cIRQn;
#endif

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

    I2C_Type* i2c = (I2C_Type*) initConfigPtr->i2cPtr;
    i2c_slave_config_t* i2cSlaveConfigPtr = (i2c_slave_config_t*) initConfigPtr->configPtr;

    _gpio_configure_for_bus(&initConfigPtr->location, initConfigPtr->mcuPullUpStatus);

    I2C_SlaveInit(i2c, i2cSlaveConfigPtr, CLOCK_GetFreq(initConfigPtr->clockName));

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__) && defined (CFG_BLE_PRJ)
    i2cIRQn = i2cIRQs[I2C_GetInstance(i2c)];
    NVIC_SetPriority(i2cIRQn, __I2C_ISR_PRIO__ >> (8 - __NVIC_PRIO_BITS));
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNXPHalSetForLowPowerEnter(const tommRoC_hw_template_bus_i2c_nxp_location_t* const locationPtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus) {

    TOMMROC_ASSERT_NOT_NULL(locationPtr);

    _gpio_configure_for_low_power(locationPtr, mcuPullUpStatus);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNXPHalSetForLowPowerExit(const tommRoC_hw_template_bus_i2c_nxp_location_t* const locationPtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus) {

    TOMMROC_ASSERT_NOT_NULL(locationPtr);

    _gpio_configure_for_bus(locationPtr, mcuPullUpStatus);

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif

#endif
