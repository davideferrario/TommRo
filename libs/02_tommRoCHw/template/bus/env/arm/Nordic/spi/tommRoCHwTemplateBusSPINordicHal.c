
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusSPINordicHal.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)

#include "bus/spi/master/tommRoCHwTemplateBusSPIMasterDEF.h"

#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "nrf_gpio.h"

#if (defined (SPI_PRESENT) && SPI_COUNT)
#include "nrfx_spi.h"
#endif

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
#if (defined (SPI_PRESENT) && SPI_COUNT)
static void _gpio_configure_for_bus(const nrf_spi_mode_t mode, const uint8_t sckPin, const uint8_t mosiPin, const uint8_t misoPin) {

    // Configure pins used by the peripheral:
    // - SCK - output with initial value corresponding with the SPI mode used:
    //   0 - for modes 0 and 1 (CPOL = 0), 1 - for modes 2 and 3 (CPOL = 1);
    //   according to the reference manual guidelines this pin and its input
    //   buffer must always be connected for the SPI to work.

    if (mode <= NRF_SPI_MODE_1) {
        nrf_gpio_pin_clear(sckPin);
    }
    else {
        nrf_gpio_pin_set(sckPin);
    }
    nrf_gpio_cfg(sckPin, NRF_GPIO_PIN_DIR_OUTPUT, NRF_GPIO_PIN_INPUT_CONNECT, NRF_GPIO_PIN_NOPULL, NRF_GPIO_PIN_S0S1, NRF_GPIO_PIN_NOSENSE);

    // - MOSI (optional) - output with initial value 0,
    if (NRFX_SPI_PIN_NOT_USED != mosiPin) {
        nrf_gpio_pin_clear(mosiPin);
        nrf_gpio_cfg_output(mosiPin);
    }

    // - MISO (optional) - input,
    if (NRFX_SPI_PIN_NOT_USED != misoPin) {
        nrf_gpio_cfg_input(misoPin, (nrf_gpio_pin_pull_t) NRFX_SPI_MISO_PULL_CFG);
    }
}

static void _gpio_configure_for_low_power(const uint8_t sckPin, const uint8_t mosiPin, const uint8_t misoPin) {

    if (NRFX_SPI_PIN_NOT_USED != sckPin) {
        nrf_gpio_cfg_input(sckPin, NRF_GPIO_PIN_NOPULL);
    }
    if (NRFX_SPI_PIN_NOT_USED != mosiPin) {
        nrf_gpio_cfg_input(mosiPin, NRF_GPIO_PIN_NOPULL);
    }
    if (NRFX_SPI_PIN_NOT_USED != misoPin) {
        nrf_gpio_cfg_input(misoPin, NRF_GPIO_PIN_NOPULL);
    }
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

#if (defined (SPI_PRESENT) && SPI_COUNT)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPINordicHalMasterInit(const tommRoC_hw_template_bus_spi_nordic_hal_config_t* const initConfigPtr) {

    nrfx_spi_config_t nrfxSpiConfig = NRFX_SPI_DEFAULT_CONFIG;

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

    nrfxSpiConfig.frequency = initConfigPtr->frequency;
    nrfxSpiConfig.mode      = initConfigPtr->mode;
    nrfxSpiConfig.sck_pin   = initConfigPtr->sckPin;
    nrfxSpiConfig.mosi_pin  = initConfigPtr->mosiPin;
    nrfxSpiConfig.miso_pin  = initConfigPtr->misoPin;

    // Ensure a proper 'reset'
    nrfx_spi_uninit(&initConfigPtr->nrfxSpi);

    if (NRFX_SUCCESS != nrfx_spi_init(&initConfigPtr->nrfxSpi, &nrfxSpiConfig, initConfigPtr->nrfxSpiEvtHandler, NULL)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPINordicHalSetForLowPowerEnter(const uint8_t sckPin, const uint8_t mosiPin, const uint8_t misoPin) {

    _gpio_configure_for_low_power(sckPin, mosiPin, misoPin);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPINordicHalSetForLowPowerExit(const nrf_spi_mode_t mode, const uint8_t sckPin, const uint8_t mosiPin, const uint8_t misoPin) {

    _gpio_configure_for_bus(mode, sckPin, mosiPin, misoPin);

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif

#endif
