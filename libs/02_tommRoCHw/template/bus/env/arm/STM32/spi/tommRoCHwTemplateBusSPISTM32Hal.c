
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusSPISTM32Hal.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_HAL_DRIVER_IS_USED__)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__) || defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_SLAVE_DEF_AT_LEAST_ONE_IS_USED__)

#include "bus/env/arm/STM32/spi/tommRoCHwTemplateBusSPISTM32DEF.h"

#include "gpio.h"
#include "spi.h"

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
static void _gpio_configure_for_low_power(GPIO_TypeDef* SCK_GPIO_Port, uint32_t SCK_Pin, GPIO_TypeDef* MISO_GPIO_Port, uint32_t MISO_Pin,  GPIO_TypeDef* MOSI_GPIO_Port, uint32_t MOSI_Pin) {

    GPIO_InitTypeDef sckGPIO_InitStruct = {0};
    GPIO_InitTypeDef misoGPIO_InitStruct = {0};
    GPIO_InitTypeDef mosiGPIO_InitStruct = {0};

    sckGPIO_InitStruct.Pin      = SCK_Pin;
    sckGPIO_InitStruct.Mode     = GPIO_MODE_ANALOG;
    sckGPIO_InitStruct.Pull     = GPIO_NOPULL;
    sckGPIO_InitStruct.Speed    = GPIO_SPEED_FREQ_LOW;

    misoGPIO_InitStruct.Pin     = MISO_Pin;
    misoGPIO_InitStruct.Mode    = GPIO_MODE_ANALOG;
    misoGPIO_InitStruct.Pull    = GPIO_NOPULL;
    misoGPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_LOW;

    mosiGPIO_InitStruct.Pin     = MOSI_Pin;
    mosiGPIO_InitStruct.Mode    = GPIO_MODE_ANALOG;
    mosiGPIO_InitStruct.Pull    = GPIO_NOPULL;
    mosiGPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(SCK_GPIO_Port,    &sckGPIO_InitStruct);
    HAL_GPIO_Init(MISO_GPIO_Port,   &misoGPIO_InitStruct);
    HAL_GPIO_Init(MOSI_GPIO_Port,   &mosiGPIO_InitStruct);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISTM32HalSetForLowPowerEnter(SPI_HandleTypeDef* const spiHandlePtr) {

    if (HAL_OK != HAL_SPI_DeInit(spiHandlePtr)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    if (hspi1.Instance == spiHandlePtr->Instance) {
        _gpio_configure_for_low_power(
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI1_SCK_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI1_SCK_PIN,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI1_MISO_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI1_MISO_PIN,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI1_MOSI_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI1_MOSI_PIN);

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
    if (hspi2.Instance == spiHandlePtr->Instance) {
        _gpio_configure_for_low_power(
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI2_SCK_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI2_SCK_PIN,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI2_MISO_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI2_MISO_PIN,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI2_MOSI_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI2_MOSI_PIN);

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_3_TEMPLATE__)
    if (hspi3.Instance == spiHandlePtr->Instance) {
        _gpio_configure_for_low_power(
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI3_SCK_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI3_SCK_PIN,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI3_MISO_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI3_MISO_PIN,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI3_MOSI_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI3_MOSI_PIN);

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_4_TEMPLATE__)
    if (hspi4.Instance == spiHandlePtr->Instance) {
        _gpio_configure_for_low_power(
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI4_SCK_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI4_SCK_PIN,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI4_MISO_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI4_MISO_PIN,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI4_MOSI_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI4_MOSI_PIN);

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_5_TEMPLATE__)
    if (hspi5.Instance == spiHandlePtr->Instance) {
        _gpio_configure_for_low_power(
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI5_SCK_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI5_SCK_PIN,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI5_MISO_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI5_MISO_PIN,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI5_MOSI_GPIO_PORT,
                TOMMROC_HW_TEMPLATE_BUS_SPI_STM32_DEF_SPI5_MOSI_PIN);

        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

    // If here, ERROR!!!
    TOMMROC_ASSERT_TRUE(false);

    return TOMMRO_C_HW_PARAM_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISTM32HalSetForLowPowerExit(SPI_HandleTypeDef* const spiHandlePtr) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    if (hspi1.Instance == spiHandlePtr->Instance) {
        MX_SPI1_Init();
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
    if (hspi2.Instance == spiHandlePtr->Instance) {
        MX_SPI2_Init();
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_3_TEMPLATE__)
    if (hspi3.Instance == spiHandlePtr->Instance) {
        MX_SPI3_Init();
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_4_TEMPLATE__)
    if (hspi4.Instance == spiHandlePtr->Instance) {
        MX_SPI4_Init();
        return TOMMRO_C_HW_ERR_SUCCESS;
    }
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_5_TEMPLATE__)
    if (hspi5.Instance == spiHandlePtr->Instance) {
        MX_SPI5_Init();
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
