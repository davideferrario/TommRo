
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentSPIMaster.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include <pigpio.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __RPI_AVAILABLE_RES_HARDWARE_AMOUNT__       (2)

#define __RPI_SPI_0_INDEX__                         (0)
#define __RPI_SPI_1_INDEX__                         (1)

#define __RPI_SPI0_MISO_GPIO_PIN__                  (9)
#define __RPI_SPI0_MOSI_GPIO_PIN__                  (10)
#define __RPI_SPI0_CLK_GPIO_PIN__                   (11)

#define __RPI_SPI1_MISO_GPIO_PIN__                  (19)
#define __RPI_SPI1_MOSI_GPIO_PIN__                  (20)
#define __RPI_SPI1_CLK_GPIO_PIN__                   (21)

#define __NOT_VALID_HANDLE__                        (-1)

#define __HARDWARE_RPI_SPI_DEFAULT_BAUDRAUTE__      (4000000)

#define __PIGPIO_GPIO_SUCCESS_RESULT__              (0)
#define __PIGPIO_HW_SUCCESS_RESULT__                (0)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    uint8_t     modeU8;
    uint32_t    baudRateKbits;

} _spi_master_arm_linux_config_t_;

#define __EMPTY__spi_master_arm_linux_config_t___                   \
{                                                                   \
    /* .modeU8 */           0,                                      \
    /* .baudRateKbits */    __HARDWARE_RPI_SPI_DEFAULT_BAUDRAUTE__, \
}

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
static _spi_master_arm_linux_config_t_ _hw_0_config = TOMMROC_UTIL_EMPTY_VARIABLE(_spi_master_arm_linux_config_t_);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
static _spi_master_arm_linux_config_t_ _hw_1_config = TOMMROC_UTIL_EMPTY_VARIABLE(_spi_master_arm_linux_config_t_);
#endif

static int _hw_handle[__RPI_AVAILABLE_RES_HARDWARE_AMOUNT__] = {
        __NOT_VALID_HANDLE__,
        __NOT_VALID_HANDLE__,
};

/*******************************************************************************
 * local functions
 ******************************************************************************/

/******************* Low level functions */

static tommRoC_hw_err_enum_t _init_gpio(const uint8_t hwResIndex) {

    TOMMROC_ASSERT_LESS_THAN(hwResIndex, __RPI_AVAILABLE_RES_HARDWARE_AMOUNT__);

    switch (hwResIndex) {

    case __RPI_SPI_0_INDEX__:
        break;

    case __RPI_SPI_1_INDEX__:
        if (__PIGPIO_GPIO_SUCCESS_RESULT__ != gpioSetMode(__RPI_SPI1_MISO_GPIO_PIN__, PI_ALT4)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        if (__PIGPIO_GPIO_SUCCESS_RESULT__ != gpioSetMode(__RPI_SPI1_MOSI_GPIO_PIN__, PI_ALT4)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        if (__PIGPIO_GPIO_SUCCESS_RESULT__ != gpioSetMode(__RPI_SPI1_CLK_GPIO_PIN__, PI_ALT4)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }
        break;

    default:
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;

    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _open_hw(
        const   uint8_t                                     hwResIndex,
        const   _spi_master_arm_linux_config_t_*    const   configPtr) {

    int handle;

    TOMMROC_ASSERT_LESS_THAN(hwResIndex, __RPI_AVAILABLE_RES_HARDWARE_AMOUNT__);

    handle = spiOpen(
            (unsigned) hwResIndex,
            configPtr->baudRateKbits,
            PI_SPI_FLAGS_AUX_SPI(hwResIndex) | PI_SPI_FLAGS_MODE(configPtr->modeU8));

    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(handle, __PIGPIO_HW_SUCCESS_RESULT__);

    if (handle < __PIGPIO_HW_SUCCESS_RESULT__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    _hw_handle[hwResIndex] = handle;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

/******************* Common BUS functions */

static tommRoC_hw_err_enum_t _hw_write_buffer(
        const   uint8_t             hwResIndex,
        const   uint8_t*    const   writeBufferPtr,
        const   uint16_t            writeBufferLen) {

    int handle;
    int result;

    TOMMROC_ASSERT_LESS_THAN(hwResIndex, __RPI_AVAILABLE_RES_HARDWARE_AMOUNT__);

    handle = _hw_handle[hwResIndex];

    TOMMROC_ASSERT_NOT_EQUALS(handle, __NOT_VALID_HANDLE__);

    if (__NOT_VALID_HANDLE__ == handle) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    result = spiWrite(handle, (char*) writeBufferPtr, (unsigned) writeBufferLen);

    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(result, __PIGPIO_HW_SUCCESS_RESULT__);
    TOMMROC_ASSERT_EQUALS(result, writeBufferLen);

    if (result < __PIGPIO_HW_SUCCESS_RESULT__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (result != writeBufferLen) {
        return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _hw_read_buffer(
        const   uint8_t             hwResIndex,
                uint8_t*    const   readBufferPtr,
        const   uint16_t            toReadAmount,
                uint16_t*   const   readedAmountPtr) {

    int handle;
    int result;

    TOMMROC_ASSERT_LESS_THAN(hwResIndex, __RPI_AVAILABLE_RES_HARDWARE_AMOUNT__);

    handle = _hw_handle[hwResIndex];

    TOMMROC_ASSERT_NOT_EQUALS(handle, __NOT_VALID_HANDLE__);

    if (__NOT_VALID_HANDLE__ == handle) {
        return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
    }

    result = spiRead(handle, (char*) readBufferPtr, (unsigned) toReadAmount);

    TOMMROC_ASSERT_MORE_OR_EQUALS_THAN(result, __PIGPIO_HW_SUCCESS_RESULT__);
    TOMMROC_ASSERT_EQUALS(result, toReadAmount);

    if (result < __PIGPIO_HW_SUCCESS_RESULT__) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (result != toReadAmount) {
        return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
    }

    *readedAmountPtr = toReadAmount;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _common_write_buffers(
        const   uint8_t                             hwResIndex,
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount) {

    const tommRoC_hw_bus_write_buf_t* writeBufferPtr;
    uint8_t index;

    for (index = 0, writeBufferPtr = writeBuffersPtr; index < writeBuffersAmount; ++index, ++writeBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _hw_write_buffer(
                        hwResIndex,
                        writeBufferPtr->bufferPtr,
                        writeBufferPtr->toWriteAmount));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _common_read_buffers(
        const   uint8_t                             hwResIndex,
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount) {

    tommRoC_hw_bus_read_buf_t* readBufferPtr;
    uint8_t index;

    for (index = 0, readBufferPtr = readBuffersPtr; index < readBuffersAmount; ++index, ++readBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _hw_read_buffer(
                        hwResIndex,
                        readBufferPtr->bufferPtr,
                        readBufferPtr->toReadAmount,
                        readBufferPtr->readedAmountPtr));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}


/******************* BUS implementation functs */

#define __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(hwResIndex)                         \
                                                                                                            \
    static tommRoC_hw_err_enum_t _spi_master_ ## hwResIndex ## _write_buffers_ARMLinux(                     \
            const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,                                    \
            const   uint8_t                             writeBuffersAmount,                                 \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        return _common_write_buffers(hwResIndex, writeBuffersPtr, writeBuffersAmount);                      \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _spi_master_ ## hwResIndex ## _read_buffers_ARMLinux(                      \
                    tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,                                     \
            const   uint8_t                             readBuffersAmount,                                  \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        return _common_read_buffers(hwResIndex, readBuffersPtr, readBuffersAmount);                         \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _spi_master_ ## hwResIndex ## _clear_data_ARMLinux(                        \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
    }                                                                                                       \
                                                                                                            \
    static void _spi_master_ ## hwResIndex ## _get_callback_ARMLinux(                                       \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                                       \
                                                                                                            \
        cbFunctPtr->writeBuffers    = _spi_master_ ## hwResIndex ## _write_buffers_ARMLinux;                \
        cbFunctPtr->readBuffers     = _spi_master_ ## hwResIndex ## _read_buffers_ARMLinux;                 \
        cbFunctPtr->clearData       = _spi_master_ ## hwResIndex ## _clear_data_ARMLinux;                   \
    }

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(__RPI_SPI_0_INDEX__);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(__RPI_SPI_1_INDEX__);
#endif


#define __TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_START_ARMLINUX__(hwResIndex, config, cbFunctPtr)               \
                                                                                                            \
        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_init_gpio(hwResIndex));           \
                                                                                                            \
        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_open_hw(hwResIndex, &config));    \
                                                                                                            \
        _spi_master_ ## hwResIndex ## _get_callback_ARMLinux(cbFunctPtr);                                   \
                                                                                                            \
        return TOMMRO_C_HW_ERR_SUCCESS;

static uint8_t _master_mode_to_u8(
        const   tommRoC_hw_template_bus_spi_master_mode_t   masterMode) {

    switch (masterMode) {

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_0:
        return 0;

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_1:
        return 1;

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_2:
        return 2;

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_3:
        return 3;

    default:
        break;

    }

    // Error
    TOMMROC_ASSERT_TRUE(false);

    return 0xFF;
}


static tommRoC_hw_err_enum_t _set_bus_spi_master_mode(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   tommRoC_hw_template_bus_spi_master_mode_t*  const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _hw_0_config.modeU8 = _master_mode_to_u8(*propValuePtr);
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _hw_1_config.modeU8 = _master_mode_to_u8(*propValuePtr);
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_bus_spi_master_baud_rate(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   uint32_t*                                   const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _hw_0_config.baudRateKbits = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _hw_1_config.baudRateKbits = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMasterSetProp(
        const   tommRoC_hw_template_bus_spi_master_prop_enum_t          property,
        const   tommRoC_hw_template_bus_spi_master_enum_t               bus,
        const   void*                                           const   propValuePtr) {

    switch (property) {

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_MODE:
        return _set_bus_spi_master_mode(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_BAUD_RATE:
        return _set_bus_spi_master_baud_rate(bus, propValuePtr);

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;
    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster0Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_START_ARMLINUX__(__RPI_SPI_0_INDEX__, _hw_0_config, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_START_ARMLINUX__(__RPI_SPI_1_INDEX__, _hw_1_config, cbFunctPtr);
}
#endif

#endif

#endif
