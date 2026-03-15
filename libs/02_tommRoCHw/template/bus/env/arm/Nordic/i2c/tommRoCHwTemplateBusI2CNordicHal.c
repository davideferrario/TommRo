
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusI2CNordicHal.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)

#include "bus/i2c/master/tommRoCHwTemplateBusI2CMasterDEF.h"

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "nrf_gpio.h"

#if (defined (TWI_PRESENT) && TWI_COUNT)
#include "nrfx_twi.h"
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
#if (defined (TWI_PRESENT) && TWI_COUNT)
static void _gpio_configure_for_bus(const uint32_t sclPin, const uint32_t sdaPin) {

    /* To secure correct signal levels on the pins used by the TWI
       master when the system is in OFF mode, and when the TWI master is
       disabled, these pins must be configured in the GPIO peripheral.
    */

    nrf_gpio_cfg(
            sclPin,
            NRF_GPIO_PIN_DIR_INPUT,
            NRF_GPIO_PIN_INPUT_CONNECT,
            NRF_GPIO_PIN_PULLUP,
            NRF_GPIO_PIN_S0D1,
            NRF_GPIO_PIN_NOSENSE);

    nrf_gpio_cfg(
            sdaPin,
            NRF_GPIO_PIN_DIR_INPUT,
            NRF_GPIO_PIN_INPUT_CONNECT,
            NRF_GPIO_PIN_PULLUP,
            NRF_GPIO_PIN_S0D1,
            NRF_GPIO_PIN_NOSENSE);
}

static void _gpio_configure_for_low_power(const uint32_t sclPin, const uint32_t sdaPin) {

    if (31 != sclPin) {
        nrf_gpio_cfg_input(sclPin, NRF_GPIO_PIN_NOPULL);
    }
    if (31 != sdaPin) {
        nrf_gpio_cfg_input(sdaPin, NRF_GPIO_PIN_NOPULL);
    }
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

#if (defined (TWI_PRESENT) && TWI_COUNT)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNordicHalMasterInit(const tommRoC_hw_template_bus_i2c_nordic_hal_config_t* const initConfigPtr) {

    nrfx_twi_config_t nrfxTwiConfig = NRFX_TWI_DEFAULT_CONFIG;

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

    nrfxTwiConfig.scl       = initConfigPtr->sclPin;
    nrfxTwiConfig.sda       = initConfigPtr->sdaPin;
    nrfxTwiConfig.frequency = initConfigPtr->frequency;

    // Ensure a proper 'reset'
    nrfx_twi_uninit(&initConfigPtr->nrfxTwi);

    if (NRFX_SUCCESS != nrfx_twi_init(&initConfigPtr->nrfxTwi, &nrfxTwiConfig, initConfigPtr->nrfxTwiEvtHandler, NULL)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    nrfx_twi_enable(&initConfigPtr->nrfxTwi);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNordicHalSetForLowPowerEnter(const uint32_t sclPin, const uint32_t sdaPin) {

    _gpio_configure_for_low_power(sclPin, sdaPin);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNordicHalSetForLowPowerExit(const uint32_t sclPin, const uint32_t sdaPin) {

    _gpio_configure_for_bus(sclPin, sdaPin);

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif

#endif
