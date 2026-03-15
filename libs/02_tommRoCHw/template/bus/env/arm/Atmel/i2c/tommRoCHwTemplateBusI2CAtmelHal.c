
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusI2CAtmelHal.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_ATMEL_IS_USED__)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__) || defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_SLAVE_DEF_AT_LEAST_ONE_IS_USED__)

#include "bus/env/arm/Atmel/i2c/tommRoCHwTemplateBusI2CAtmelDEF.h"

#include "driver_init.h"

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
static void _gpio_configure_for_low_power(const uint8_t SCLPin, const uint8_t SDAPin, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus) {

    enum gpio_pull_mode pullMode;

    pullMode = (TOMMRO_C_UTIL_ENABLED == mcuPullUpStatus) ? (GPIO_PULL_UP): (GPIO_PULL_OFF);

    // NOTE: SCL first, to ensure it is high before changing SDA
    gpio_set_pin_direction(SCLPin, GPIO_DIRECTION_IN);
    gpio_set_pin_pull_mode(SCLPin, pullMode);
    gpio_set_pin_function(SCLPin, GPIO_PIN_FUNCTION_OFF);

    gpio_set_pin_direction(SDAPin, GPIO_DIRECTION_IN);
    gpio_set_pin_pull_mode(SDAPin, pullMode);
    gpio_set_pin_function(SDAPin, GPIO_PIN_FUNCTION_OFF);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CAtmelHalSetForLowPowerEnter(struct i2c_m_async_desc* const i2cHandlePtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
    if (&I2C_0 == i2cHandlePtr) {
        _gpio_configure_for_low_power(
                TOMMROC_HW_TEMPLATE_BUS_I2C_ATMEL_DEF_I2C0_SCL,
                TOMMROC_HW_TEMPLATE_BUS_I2C_ATMEL_DEF_I2C0_SDA,
                mcuPullUpStatus);

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    if (&I2C_1 == i2cHandlePtr) {
        _gpio_configure_for_low_power(
                TOMMROC_HW_TEMPLATE_BUS_I2C_ATMEL_DEF_I2C1_SCL,
                TOMMROC_HW_TEMPLATE_BUS_I2C_ATMEL_DEF_I2C1_SDA,
                mcuPullUpStatus);

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    return TOMMRO_C_HW_PARAM_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CAtmelHalSetForLowPowerExit(struct i2c_m_async_desc* const i2cHandlePtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus) {

    TOMMROC_UTIL_UNUSED_PARAM(mcuPullUpStatus);

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
    if (&I2C_0 == i2cHandlePtr) {
        I2C_0_PORT_init();
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    if (&I2C_1 == i2cHandlePtr) {
        I2C_1_PORT_init();
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    return TOMMRO_C_HW_PARAM_ERR;
}

#endif

#endif

#endif
