
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusSPIESP32Hal.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#include "driver/spi_master.h"
#include "driver/spi_slave.h"

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

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIESP32HalMasterInit(const tommRoC_hw_template_bus_spi_esp32_hal_config_t* const initConfigPtr) {

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

    if (ESP_OK != spi_bus_initialize(initConfigPtr->spiHostDevice, &initConfigPtr->spiBusConfig, SPI_DMA_CH_AUTO)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIESP32HalSlaveInit(const tommRoC_hw_template_bus_spi_esp32_hal_config_t* const initConfigPtr) {
    return TOMMRO_C_HW_LOW_LEVEL_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIESP32HalSetForLowPowerEnter(const spi_host_device_t spiHostDevice, const gpio_num_t sckGPIONum, const gpio_num_t misoGPIONum, const gpio_num_t mosiGPIONum) {


    TOMMROC_UTIL_UNUSED_PARAM(spiHostDevice);
    TOMMROC_UTIL_UNUSED_PARAM(sckGPIONum);
    TOMMROC_UTIL_UNUSED_PARAM(misoGPIONum);
    TOMMROC_UTIL_UNUSED_PARAM(mosiGPIONum);


/*
    TOMMROC_UTIL_UNUSED_PARAM(spiHostDevice);

    gpio_pad_select_gpio(sckGPIONum);
    gpio_pad_select_gpio(misoGPIONum);
    gpio_pad_select_gpio(mosiGPIONum);

    if (ESP_OK != gpio_reset_pin(sckGPIONum)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != gpio_reset_pin(misoGPIONum)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != gpio_reset_pin(mosiGPIONum)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (ESP_OK != gpio_set_direction(sckGPIONum, GPIO_MODE_INPUT)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != gpio_set_direction(misoGPIONum, GPIO_MODE_INPUT)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != gpio_set_direction(mosiGPIONum, GPIO_MODE_INPUT)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
*/
    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIESP32HalSetForLowPowerExit(const spi_host_device_t spiHostDevice, const gpio_num_t sckGPIONum, const gpio_num_t misoGPIONum, const gpio_num_t mosiGPIONum) {

    TOMMROC_UTIL_UNUSED_PARAM(spiHostDevice);
    TOMMROC_UTIL_UNUSED_PARAM(sckGPIONum);
    TOMMROC_UTIL_UNUSED_PARAM(misoGPIONum);
    TOMMROC_UTIL_UNUSED_PARAM(mosiGPIONum);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif
