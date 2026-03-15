
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusI2CSTM32Hal.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__) || defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_SLAVE_DEF_AT_LEAST_ONE_IS_USED__)

#include "bus/env/arm/STM32/i2c/tommRoCHwTemplateBusI2CSTM32DEF.h"

#include "gpio.h"
#include "i2c.h"

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
static void _gpio_configure_for_low_power(GPIO_TypeDef* SCL_GPIO_Port, const uint32_t SCL_Pin, GPIO_TypeDef* SDA_GPIO_Port, const uint32_t SDA_Pin, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus) {

    GPIO_InitTypeDef sclGPIO_InitStruct = {0};
    GPIO_InitTypeDef sdaGPIO_InitStruct = {0};

    uint32_t Mode;
    uint32_t Pull;

    Mode = (TOMMRO_C_UTIL_ENABLED == mcuPullUpStatus) ? (GPIO_MODE_INPUT) : (GPIO_MODE_ANALOG);
    Pull = (TOMMRO_C_UTIL_ENABLED == mcuPullUpStatus) ? (GPIO_PULLUP) : (GPIO_NOPULL);

    sclGPIO_InitStruct.Pin      = SCL_Pin;
    sclGPIO_InitStruct.Mode     = Mode;
    sclGPIO_InitStruct.Pull     = Pull;
    sclGPIO_InitStruct.Speed    = GPIO_SPEED_FREQ_LOW;

    sdaGPIO_InitStruct.Pin      = SDA_Pin;
    sdaGPIO_InitStruct.Mode     = Mode;
    sdaGPIO_InitStruct.Pull     = Pull;
    sdaGPIO_InitStruct.Speed    = GPIO_SPEED_FREQ_LOW;

    // NOTE: SCL first, to ensure it is high before changing SDA
    HAL_GPIO_Init(SCL_GPIO_Port, &sclGPIO_InitStruct);
    HAL_GPIO_Init(SDA_GPIO_Port, &sdaGPIO_InitStruct);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSTM32HalSetForLowPowerEnter(I2C_HandleTypeDef* const i2cHandlePtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus) {

    if (HAL_OK != HAL_I2C_DeInit(i2cHandlePtr)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    if (hi2c1.Instance == i2cHandlePtr->Instance) {
        _gpio_configure_for_low_power(
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C1_SCL_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C1_SCL_PIN,
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C1_SDA_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C1_SDA_PIN,
                mcuPullUpStatus);

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_TEMPLATE__)
    if (hi2c2.Instance == i2cHandlePtr->Instance) {
        _gpio_configure_for_low_power(
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C2_SCL_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C2_SCL_PIN,
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C2_SDA_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C2_SDA_PIN,
                mcuPullUpStatus);

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_3_TEMPLATE__)
    if (hi2c3.Instance == i2cHandlePtr->Instance) {
        _gpio_configure_for_low_power(
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C3_SCL_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C3_SCL_PIN,
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C3_SDA_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C3_SDA_PIN,
                mcuPullUpStatus);

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_4_TEMPLATE__)
    if (hi2c4.Instance == i2cHandlePtr->Instance) {
        _gpio_configure_for_low_power(
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C4_SCL_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C4_SCL_PIN,
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C4_SDA_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C4_SDA_PIN,
                mcuPullUpStatus);

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_5_TEMPLATE__)
    if (hi2c5.Instance == i2cHandlePtr->Instance) {
        _gpio_configure_for_low_power(
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C5_SCL_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C5_SCL_PIN,
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C5_SDA_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_I2C_STM32_DEF_I2C5_SDA_PIN,
                mcuPullUpStatus);

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    return TOMMRO_C_HW_PARAM_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSTM32HalSetForLowPowerExit(I2C_HandleTypeDef* const i2cHandlePtr, const tommRoC_util_enabled_status_enum_t mcuPullUpStatus) {

    TOMMROC_UTIL_UNUSED_PARAM(mcuPullUpStatus);

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    if (hi2c1.Instance == i2cHandlePtr->Instance) {
        MX_I2C1_Init();
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_TEMPLATE__)
    if (hi2c2.Instance == i2cHandlePtr->Instance) {
        MX_I2C2_Init();
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_3_TEMPLATE__)
    if (hi2c3.Instance == i2cHandlePtr->Instance) {
        MX_I2C3_Init();
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_4_TEMPLATE__)
    if (hi2c4.Instance == i2cHandlePtr->Instance) {
        MX_I2C4_Init();
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_5_TEMPLATE__)
    if (hi2c5.Instance == i2cHandlePtr->Instance) {
        MX_I2C5_Init();
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
