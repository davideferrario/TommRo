
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusI2CESP32Hal.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __ESP32_I2C_SLAVE_FIFO_BUFFER_SIZE_BYTE__   (128)

#define __I2C_MASTER_TX_BUF_DISABLE__               (0) // I2C master doesn't need buffer
#define __I2C_MASTER_RX_BUF_DISABLE__               (0) // I2C master doesn't need buffer

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

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CESP32HalMasterInit(const tommRoC_hw_template_bus_i2c_esp32_hal_config_t* const initConfigPtr) {

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

    if (ESP_OK != i2c_param_config(initConfigPtr->i2cPort, &initConfigPtr->i2cConfig)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    // NOTE: slv_rx_buf_len/slv_tx_buf_len parameters are used only for slave mode; driver will ignore this value in master mode.
    if (ESP_OK != i2c_driver_install(initConfigPtr->i2cPort, I2C_MODE_MASTER, __I2C_MASTER_RX_BUF_DISABLE__, __I2C_MASTER_TX_BUF_DISABLE__, 0)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CESP32HalSlaveInit(const tommRoC_hw_template_bus_i2c_esp32_hal_config_t* const initConfigPtr) {

    uint8_t usedI2CBufferAmount = 0;

    TOMMROC_ASSERT_NOT_NULL(initConfigPtr);

#if defined (__TOMMROC_HW_USE_I2C_SLAVE_0_TEMPLATE__)
    usedI2CBufferAmount += 2;
#endif
#if defined (__TOMMROC_HW_USE_I2C_SLAVE_1_TEMPLATE__)
    usedI2CBufferAmount += 2;
#endif

    TOMMROC_ASSERT_NOT_ZERO(usedI2CBufferAmount);

    if (ESP_OK != i2c_param_config(initConfigPtr->i2cPort, &initConfigPtr->i2cConfig)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != i2c_driver_install(initConfigPtr->i2cPort, I2C_MODE_SLAVE, __ESP32_I2C_SLAVE_FIFO_BUFFER_SIZE_BYTE__ / usedI2CBufferAmount, __ESP32_I2C_SLAVE_FIFO_BUFFER_SIZE_BYTE__ / usedI2CBufferAmount, 0)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CESP32HalSetForLowPowerEnter(const i2c_port_t i2cPort, const gpio_num_t sdaGPIONum, const gpio_num_t sclGPIONum) {

    TOMMROC_UTIL_UNUSED_PARAM(i2cPort);
    TOMMROC_UTIL_UNUSED_PARAM(sdaGPIONum);
    TOMMROC_UTIL_UNUSED_PARAM(sclGPIONum);



/*
    TOMMROC_UTIL_UNUSED_PARAM(i2cPort);

    gpio_pad_select_gpio(sdaGPIONum);
    gpio_pad_select_gpio(sclGPIONum);

    if (ESP_OK != gpio_reset_pin(sdaGPIONum)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != gpio_reset_pin(sclGPIONum)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (ESP_OK != gpio_set_direction(sdaGPIONum, GPIO_MODE_INPUT)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    if (ESP_OK != gpio_set_direction(sclGPIONum, GPIO_MODE_INPUT)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
*/
    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CESP32HalSetForLowPowerExit(const i2c_port_t i2cPort, const gpio_num_t sdaGPIONum, const gpio_num_t sclGPIONum) {


    TOMMROC_UTIL_UNUSED_PARAM(i2cPort);
    TOMMROC_UTIL_UNUSED_PARAM(sdaGPIONum);
    TOMMROC_UTIL_UNUSED_PARAM(sclGPIONum);




/*
    if (ESP_OK != i2c_set_pin(i2cPort, (int) sdaGPIONum, (int) sclGPIONum, GPIO_PULLUP_DISABLE, GPIO_PULLUP_DISABLE, I2C_MODE_MASTER)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
*/
    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif
