
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusSPINXPHal.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#include "bus/spi/master/tommRoCHwTemplateBusSPIMasterDEF.h"

#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "env/tommRoCTemplateEnv.h"

#include "fsl_gpio.h"
#if (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT) || (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT)
#include "fsl_iocon.h"
#endif
#if defined (FSL_FEATURE_SOC_PORT_COUNT) && FSL_FEATURE_SOC_PORT_COUNT
#include "fsl_port.h"
#endif
#if defined (FSL_FEATURE_SOC_SPI_COUNT) && FSL_FEATURE_SOC_SPI_COUNT
#include "fsl_spi.h"
#endif
#if defined (FSL_FEATURE_SOC_DSPI_COUNT) && FSL_FEATURE_SOC_DSPI_COUNT
#include "fsl_dspi.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/
#if defined (FSL_FEATURE_SOC_SPI_COUNT) && FSL_FEATURE_SOC_SPI_COUNT
#define __master_config_t__             spi_master_config_t
#define __slave_config_t__              spi_slave_config_t
#define __MasterInit__                  SPI_MasterInit
#define __SlaveInit__                   SPI_SlaveInit
#endif

#if defined (FSL_FEATURE_SOC_DSPI_COUNT) && FSL_FEATURE_SOC_DSPI_COUNT
#define __master_config_t__             dspi_master_config_t
#define __slave_config_t__              dspi_slave_config_t
#define __MasterInit__                  DSPI_MasterInit
#define __SlaveInit__                   DSPI_SlaveInit
#endif

#define __SPI_ISR_PRIO__    (0x40)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
static void _gpio_configure_for_bus(const tommRoC_hw_template_bus_spi_nxp_location_t* const locationPtr) {

    TOMMROC_ASSERT_NOT_NULL(locationPtr);

#if (!((defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)))
    CLOCK_EnableClock(locationPtr->clockName);
#endif

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
    PORT_SetPinMux(locationPtr->gpioSCKPort, locationPtr->gpioSCKPin, locationPtr->gpioSCKPortMux);
    PORT_SetPinMux(locationPtr->gpioMISOPort, locationPtr->gpioMISOPin, locationPtr->gpioMISOPortMux);
    PORT_SetPinMux(locationPtr->gpioMOSIPort, locationPtr->gpioMOSIPin, locationPtr->gpioMOSIPortMux);

#elif (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)
    const uint32_t sckModeFunc = (
            locationPtr->sckIOCONFunc   |   // Select pin function
            IOCON_MODE_HIGHZ            |   // Selects High-Z function
            IOCON_DRIVE_LOW                 // Enable low drive strength
    );

    const uint32_t misoModeFunc = (
            locationPtr->misoIOCONFunc  |   // Select pin function
            IOCON_MODE_HIGHZ            |   // Select High-Z function
            IOCON_DRIVE_LOW                 // Enable low drive strength
    );

    const uint32_t mosiModeFunc = (
            locationPtr->mosiIOCONFunc  |   // Select pin function
            IOCON_MODE_HIGHZ            |   // Select High-Z function
            IOCON_DRIVE_LOW                 // Enable low drive strength
    );

    IOCON_PinMuxSet(IOCON, locationPtr->sckPortIdx, locationPtr->sckPin, sckModeFunc);
    IOCON_PinMuxSet(IOCON, locationPtr->misoPortIdx, locationPtr->misoPin, misoModeFunc);
    IOCON_PinMuxSet(IOCON, locationPtr->mosiPortIdx, locationPtr->mosiPin, mosiModeFunc);

#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
    if (locationPtr->portSetPinSelectNeeded) {
        PORT_SetPinSelect(locationPtr->portModule, locationPtr->portPinSelect);
    }
#endif

#if (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)
    CLOCK_EnableClock(locationPtr->clockName);
#endif
}

static void _gpio_configure_for_low_power(const tommRoC_hw_template_bus_spi_nxp_location_t* const locationPtr) {

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
    PORT_SetPinMux(locationPtr->gpioSCKPort, locationPtr->gpioSCKPin, kPORT_MuxAsGpio);
    PORT_SetPinMux(locationPtr->gpioMISOPort, locationPtr->gpioMISOPin, kPORT_MuxAsGpio);
    PORT_SetPinMux(locationPtr->gpioMOSIPort, locationPtr->gpioMOSIPin, kPORT_MuxAsGpio);

    GPIO_PinInit(locationPtr->gpioSCKGpio, locationPtr->gpioSCKPin, &gpioConfigAsInput);
    GPIO_PinInit(locationPtr->gpioMISOGpio, locationPtr->gpioMISOPin, &gpioConfigAsInput);
    GPIO_PinInit(locationPtr->gpioMOSIGpio, locationPtr->gpioMOSIPin, &gpioConfigAsInput);

#elif (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)
    const uint32_t modeFunc = (
            IOCON_FUNC0                 |   // Select pin function (FUNC0 -> GPIO)
            IOCON_MODE_HIGHZ            |   // Select High-Z function
            IOCON_DRIVE_LOW                 // Enable low drive strength
    );

    IOCON_PinMuxSet(IOCON, locationPtr->sckPortIdx, locationPtr->sckPin, modeFunc);
    IOCON_PinMuxSet(IOCON, locationPtr->misoPortIdx, locationPtr->misoPin, modeFunc);
    IOCON_PinMuxSet(IOCON, locationPtr->mosiPortIdx, locationPtr->mosiPin, modeFunc);

    GPIO_PinInit(locationPtr->gpioSCKGpio, locationPtr->sckPin, &gpioConfigAsInput);
    GPIO_PinInit(locationPtr->gpioMISOGpio, locationPtr->misoPin, &gpioConfigAsInput);
    GPIO_PinInit(locationPtr->gpioMOSIGpio, locationPtr->mosiPin, &gpioConfigAsInput);

#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
    GPIO_PinInit(locationPtr->gpioSCKPort, locationPtr->gpioSCKPin, &gpioConfigAsInput);
    GPIO_PinInit(locationPtr->gpioMISOPort, locationPtr->gpioMISOPin, &gpioConfigAsInput);
    GPIO_PinInit(locationPtr->gpioMOSIPort, locationPtr->gpioMOSIPin, &gpioConfigAsInput);
#endif
}

/*******************************************************************************
 * functions
 ******************************************************************************/

#if (defined (FSL_FEATURE_SOC_SPI_COUNT) && FSL_FEATURE_SOC_SPI_COUNT) || (defined (FSL_FEATURE_SOC_DSPI_COUNT) && FSL_FEATURE_SOC_DSPI_COUNT)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPINXPHalMasterInit(const tommRoC_hw_template_bus_spi_nxp_hal_config_t* const initConfigPtr) {

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__) && defined (CFG_BLE_PRJ)
    static const IRQn_Type spiIRQs[] = SPI_IRQS;
    IRQn_Type spiIRQn;
#endif

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

    SPI_Type* spi = (SPI_Type*) initConfigPtr->spiPtr;
    __master_config_t__* spiMasterConfigPtr = (__master_config_t__*) initConfigPtr->configPtr;

    _gpio_configure_for_bus(&initConfigPtr->location);

    __MasterInit__(spi, spiMasterConfigPtr, CLOCK_GetFreq(initConfigPtr->clockName));

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__) && defined (CFG_BLE_PRJ)
    spiIRQn = spiIRQs[SPI_GetInstance(spi)];
    NVIC_SetPriority(spiIRQn, __SPI_ISR_PRIO__ >> (8 - __NVIC_PRIO_BITS));
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPINXPHalSlaveInit(const tommRoC_hw_template_bus_spi_nxp_hal_config_t* const initConfigPtr) {

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__) && defined (CFG_BLE_PRJ)
    static const IRQn_Type spiIRQs[] = SPI_IRQS;
    IRQn_Type spiIRQn;
#endif

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

    SPI_Type* spi = (SPI_Type*) initConfigPtr->spiPtr;
    __slave_config_t__* spiSlaveConfigPtr = (__slave_config_t__*) initConfigPtr->configPtr;

    _gpio_configure_for_bus(&initConfigPtr->location);

    __SlaveInit__(spi, spiSlaveConfigPtr);

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__) && defined (CFG_BLE_PRJ)
    spiIRQn = spiIRQs[SPI_GetInstance(spi)];
    NVIC_SetPriority(spiIRQn, __SPI_ISR_PRIO__ >> (8 - __NVIC_PRIO_BITS));
#endif

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPINXPHalSetForLowPowerEnter(const tommRoC_hw_template_bus_spi_nxp_location_t* const locationPtr) {

    TOMMROC_ASSERT_NOT_NULL(locationPtr);

    _gpio_configure_for_low_power(locationPtr);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPINXPHalSetForLowPowerExit(const tommRoC_hw_template_bus_spi_nxp_location_t* const locationPtr) {

    TOMMROC_ASSERT_NOT_NULL(locationPtr);

    _gpio_configure_for_bus(locationPtr);

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif

#endif
