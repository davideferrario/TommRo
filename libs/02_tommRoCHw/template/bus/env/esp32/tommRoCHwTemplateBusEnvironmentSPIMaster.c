
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentSPIMaster.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "TOMMROCMw.h"

#include "bus/common/spi/master/tommRoCHwTemplateBusCommonSPIMasterCb.h"

#include "bus/env/esp32/spi/tommRoCHwTemplateBusSPIESP32Hal.h"

#if (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
#include "soc/gpio_num.h"
#endif

#include "driver/gpio.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "freertos/FreeRTOS.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __DEFAULT_MODE__                    (TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_0)
#define __DEFAULT_BAUDRATE__                (500000)
#define __DEFAULT_SCK_IO_NUM__              (GPIO_NUM_NC)
#define __DEFAULT_MISO_IO_NUM__             (GPIO_NUM_NC)
#define __DEFAULT_MOSI_IO_NUM__             (GPIO_NUM_NC)

#define __SPI_DUMMYDATA__                   (0xFF)
#define __SPI_MAX_NO_DMA_DATA_SIZE_BYTE__   (4092)  // Selecting DMA channel limits the amount of bytes transfered to a maximum of 4092.

#if (4 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
#define __SPI_0_HOST_DEVICE__               (HSPI_HOST)
#define __SPI_1_HOST_DEVICE__               (VSPI_HOST)
#elif (5 == TOMMROC_TEMPLATE_ENV_ESP32_ESP_IDF_VERSION_MAJOR)
#define __SPI_0_HOST_DEVICE__               (SPI1_HOST)
#define __SPI_1_HOST_DEVICE__               (SPI2_HOST)
#if SOC_SPI_PERIPH_NUM > 2
#define __SPI_2_HOST_DEVICE__               (SPI3_HOST)
#endif
#endif

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    tommRoC_hw_template_bus_spi_master_mode_t   mode;
    uint32_t                                    baudRate;
    gpio_num_t                                  sckGPIONum;
    gpio_num_t                                  misoGPIONum;
    gpio_num_t                                  mosiGPIONum;

} __tommRoC_hw_spi_master_config_t__;

#define __EMPTY___tommRoC_hw_spi_master_config_t____    \
{                                                       \
    /* .mode */         __DEFAULT_MODE__,               \
    /* .baudRate */     __DEFAULT_BAUDRATE__,           \
    /* .sckGPIONum */   __DEFAULT_SCK_IO_NUM__,         \
    /* .misoGPIONum */  __DEFAULT_MISO_IO_NUM__,        \
    /* .mosiGPIONum */  __DEFAULT_MOSI_IO_NUM__,        \
}

typedef struct {

    spi_host_device_t               spiHostDevice;
    spi_device_interface_config_t   spiDeviceInterfaceConfig;
    spi_device_handle_t             spiDeviceHandle;

} __tommRoC_hw_spi_master_handle_t__;

#define __EMPTY___tommRoC_hw_spi_master_handle_t____        \
{                                                           \
    /* .spiHostDevice */            __SPI_0_HOST_DEVICE__,  \
    /* .spiDeviceInterfaceConfig */ {0},                    \
    /* .spiDeviceHandle */          NULL,                   \
}

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
static __tommRoC_hw_spi_master_config_t__ _spi_master_config_0 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_spi_master_config_t__);
static __tommRoC_hw_spi_master_handle_t__ _spi_master_handle_0 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_spi_master_handle_t__);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
static __tommRoC_hw_spi_master_config_t__ _spi_master_config_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_spi_master_config_t__);
static __tommRoC_hw_spi_master_handle_t__ _spi_master_handle_1 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_spi_master_handle_t__);
#endif

static uint8_t _write_dummy_buffer[__SPI_MAX_NO_DMA_DATA_SIZE_BYTE__] = { __SPI_DUMMYDATA__ };

/*******************************************************************************
 * local functions
 ******************************************************************************/
static uint8_t _spi_master_mode_enum_to_U8(const tommRoC_hw_template_bus_spi_master_mode_t mode) {

    switch (mode) {

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_0:    return 0;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_1:    return 1;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_2:    return 2;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_3:    return 3;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;
    }

    return 0;
}

static tommRoC_hw_err_enum_t _write_buffer(
                spi_device_handle_t         handle,
        const   uint8_t*            const   writeBufferPtr,
        const   uint16_t                    writeBufferLen,
        const   uint32_t                    timeoutMsec) {

    spi_transaction_t transaction;
    uint16_t remaining;
    uint8_t* ptr;
    uint16_t toSend;

    TOMMROC_UTIL_UNUSED_PARAM(timeoutMsec);

    ptr         = (uint8_t*) writeBufferPtr;
    remaining   = writeBufferLen;

    while (remaining > 0) {

        toSend = tommRoCMathMin(remaining, __SPI_MAX_NO_DMA_DATA_SIZE_BYTE__);

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&transaction, 0, sizeof(spi_transaction_t)));

        transaction.length      = (size_t) (toSend * 8);
        transaction.tx_buffer   = (void*) ptr;

        if (ESP_OK != spi_device_transmit(handle, &transaction)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        remaining -= toSend;

        if (remaining > 0) {

            ptr += toSend;

            // NOTE: don't replace with tommRoCOsDelayMsec(0) because tommRoCMwThreadYield is faster.
            TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwThreadYield());
        }
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _read_buffer(
                spi_device_handle_t         handle,
                uint8_t*            const   readBufferPtr,
        const   uint16_t                    toReadAmount,
        const   uint32_t                    timeoutMsec) {

    spi_transaction_t transaction;
    uint16_t remaining;
    uint8_t* ptr;
    uint8_t toRead;

    TOMMROC_UTIL_UNUSED_PARAM(timeoutMsec);

    ptr         = readBufferPtr;
    remaining   = toReadAmount;

    while (remaining > 0) {

        toRead = tommRoCMathMin(remaining, __SPI_MAX_NO_DMA_DATA_SIZE_BYTE__);

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&transaction, 0, sizeof(spi_transaction_t)));

        transaction.length      = (size_t) (toRead * 8);
        transaction.tx_buffer   = (void*) _write_dummy_buffer;
        transaction.rxlength    = (size_t) (toRead * 8);
        transaction.rx_buffer   = (void*) ptr;

        if (ESP_OK != spi_device_transmit(handle, &transaction)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        remaining -= toRead;

        if (remaining > 0) {

            ptr += toRead;

            // NOTE: don't replace with tommRoCOsDelayMsec(0) because tommRoCMwThreadYield is faster.
            TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwThreadYield());
        }
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _write_buffers(
                spi_device_handle_t                 handle,
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   uint32_t                            timeoutPerByteMsec) {

    const tommRoC_hw_bus_write_buf_t* writeBufferPtr;
    uint8_t index;

    for (index = 0, writeBufferPtr = writeBuffersPtr; index < writeBuffersAmount; ++index, ++writeBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _write_buffer(
                        handle,
                        writeBufferPtr->bufferPtr,
                        writeBufferPtr->toWriteAmount,
                        timeoutPerByteMsec * writeBufferPtr->toWriteAmount));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _read_buffers(
                spi_device_handle_t                 handle,
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   uint32_t                            timeoutPerByteMsec) {

    tommRoC_hw_bus_read_buf_t* readBufferPtr;
    uint8_t index;

    for (index = 0, readBufferPtr = readBuffersPtr; index < readBuffersAmount; ++index, ++readBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _read_buffer(
                        handle,
                        readBufferPtr->bufferPtr,
                        readBufferPtr->toReadAmount,
                        timeoutPerByteMsec * readBufferPtr->toReadAmount));

        *(readBufferPtr->readedAmountPtr) = readBufferPtr->toReadAmount;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _write_read_buffer(
                spi_device_handle_t                 handle,
        const   uint8_t*                    const   writeBufferPtr,
        const   uint16_t                            writeBufferLen,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            toReadAmount,
        const   uint32_t                            delayWriteToReadMsec,
        const   uint32_t                            timeoutPerByteMsec) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _write_buffer(
                    handle,
                    writeBufferPtr,
                    writeBufferLen,
                    timeoutPerByteMsec * writeBufferLen));

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(delayWriteToReadMsec));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _read_buffer(
                    handle,
                    readBufferPtr,
                    toReadAmount,
                    timeoutPerByteMsec * toReadAmount));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _transceive_buffer(
                spi_device_handle_t                 handle,
        const   uint8_t*                    const   writeBufferPtr,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            bufferLength,
        const   uint32_t                            timeoutPerByteMsec) {

    spi_transaction_t transaction;
    uint16_t remaining;
    uint8_t* wrPtr;
    uint8_t* rdPtr;
    uint8_t amount;

    TOMMROC_UTIL_UNUSED_PARAM(timeoutPerByteMsec);

    wrPtr       = (uint8_t*) writeBufferPtr;
    rdPtr       = (uint8_t*) readBufferPtr;
    remaining   = bufferLength;

    while (remaining > 0) {

        amount = tommRoCMathMin(remaining, __SPI_MAX_NO_DMA_DATA_SIZE_BYTE__);

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&transaction, 0, sizeof(spi_transaction_t)));

        transaction.length      = (size_t) (amount * 8);
        transaction.tx_buffer   = (void*) wrPtr;
        transaction.rxlength    = (size_t) (amount * 8);
        transaction.rx_buffer   = (void*) rdPtr;

        if (ESP_OK != spi_device_transmit(handle, &transaction)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        remaining -= amount;

        if (remaining > 0) {

            wrPtr += amount;
            rdPtr += amount;

            // NOTE: don't replace with tommRoCOsDelayMsec(0) because tommRoCMwThreadYield is faster.
            TOMMROC_MW_ASSERT_TOMMROC_MW_LIB_FUNCT_SUCCESS(tommRoCMwThreadYield());
        }
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_write_buffers(
                void*                       const   spiConfigPtr,
                void*                       const   spiHandlePtr,
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   uint32_t                            timeoutPerByteMsec) {

    __tommRoC_hw_spi_master_handle_t__* handlePtr = (__tommRoC_hw_spi_master_handle_t__*) spiHandlePtr;

    TOMMROC_UTIL_UNUSED_PARAM(spiConfigPtr);

    return _write_buffers(
            handlePtr->spiDeviceHandle,
            writeBuffersPtr,
            writeBuffersAmount,
            timeoutPerByteMsec);
}

static tommRoC_hw_err_enum_t _phy_read_buffers(
                void*                       const   spiConfigPtr,
                void*                       const   spiHandlePtr,
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   uint32_t                            timeoutPerByteMsec) {

    __tommRoC_hw_spi_master_handle_t__* handlePtr = (__tommRoC_hw_spi_master_handle_t__*) spiHandlePtr;

    TOMMROC_UTIL_UNUSED_PARAM(spiConfigPtr);

    return _read_buffers(
            handlePtr->spiDeviceHandle,
            readBuffersPtr,
            readBuffersAmount,
            timeoutPerByteMsec);
}

static tommRoC_hw_err_enum_t _phy_write_read_buffer(
                void*                       const   spiConfigPtr,
                void*                       const   spiHandlePtr,
        const   uint8_t*                    const   writeBufferPtr,
        const   uint16_t                            writeBufferLen,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            toReadAmount,
        const   uint32_t                            delayWriteToReadMsec,
        const   uint32_t                            timeoutPerByteMsec) {

    __tommRoC_hw_spi_master_handle_t__* handlePtr = (__tommRoC_hw_spi_master_handle_t__*) spiHandlePtr;

    TOMMROC_UTIL_UNUSED_PARAM(spiConfigPtr);

    return _write_read_buffer(
            handlePtr->spiDeviceHandle,
            writeBufferPtr,
            writeBufferLen,
            readBufferPtr,
            toReadAmount,
            delayWriteToReadMsec,
            timeoutPerByteMsec);
}

static tommRoC_hw_err_enum_t _phy_transceive_buffer(
                void*                       const   spiConfigPtr,
                void*                       const   spiHandlePtr,
        const   uint8_t*                    const   writeBufferPtr,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            bufferLength,
        const   uint32_t                            timeoutPerByteMsec) {

    __tommRoC_hw_spi_master_handle_t__* handlePtr = (__tommRoC_hw_spi_master_handle_t__*) spiHandlePtr;

    TOMMROC_UTIL_UNUSED_PARAM(spiConfigPtr);

    return _transceive_buffer(
            handlePtr->spiDeviceHandle,
            writeBufferPtr,
            readBufferPtr,
            bufferLength,
            timeoutPerByteMsec);
}

/******************* BUS implementation functs */

#define __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(                                \
                spiMasterPrefix,                                                                        \
                spiMaster,                                                                              \
                spiConfig,                                                                              \
                spiHandle)                                                                              \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _write_buffers_ESP32(               \
            const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,                                \
            const   uint8_t                             writeBuffersAmount,                             \
            const   void*                       const   inputPtr,                                       \
                    void*                       const   resultPtr) {                                    \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return tommRoCHwTemplateBusCommonSPIMasterCbWriteBuffers(                                       \
                writeBuffersPtr,                                                                        \
                writeBuffersAmount,                                                                     \
                &spiConfig,                                                                             \
                &spiHandle,                                                                             \
                _phy_write_buffers);                                                                    \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _read_buffers_ESP32(                \
                    tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,                                 \
            const   uint8_t                             readBuffersAmount,                              \
            const   void*                       const   inputPtr,                                       \
                    void*                       const   resultPtr) {                                    \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return tommRoCHwTemplateBusCommonSPIMasterCbReadBuffers(                                        \
                readBuffersPtr,                                                                         \
                readBuffersAmount,                                                                      \
                &spiConfig,                                                                             \
                &spiHandle,                                                                             \
                _phy_read_buffers);                                                                     \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _write_read_buffer_ESP32(           \
            const   uint8_t*                    const   writeBufferPtr,                                 \
            const   uint16_t                            writeBufferLen,                                 \
                    uint8_t*                    const   readBufferPtr,                                  \
            const   uint16_t                            toReadAmount,                                   \
                    uint16_t*                   const   readedAmountPtr,                                \
            const   uint32_t                            delayWriteToReadMsec,                           \
            const   void*                       const   inputPtr,                                       \
                    void*                       const   resultPtr) {                                    \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return tommRoCHwTemplateBusCommonSPIMasterCbWriteReadBuffer(                                    \
                writeBufferPtr,                                                                         \
                writeBufferLen,                                                                         \
                readBufferPtr,                                                                          \
                toReadAmount,                                                                           \
                readedAmountPtr,                                                                        \
                delayWriteToReadMsec,                                                                   \
                &spiConfig,                                                                             \
                &spiHandle,                                                                             \
                _phy_write_read_buffer);                                                                \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _transceive_buffer_ESP32(           \
            const   uint8_t*                    const   writeBufferPtr,                                 \
                    uint8_t*                    const   readBufferPtr,                                  \
            const   uint16_t                            bufferLength,                                   \
            const   void*                       const   inputPtr,                                       \
                    void*                       const   resultPtr) {                                    \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return tommRoCHwTemplateBusCommonSPIMasterCbTransceiveBuffer(                                   \
                writeBufferPtr,                                                                         \
                readBufferPtr,                                                                          \
                bufferLength,                                                                           \
                &spiConfig,                                                                             \
                &spiHandle,                                                                             \
                _phy_transceive_buffer);                                                                \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _clear_data_ESP32(                  \
            const   void*                       const   inputPtr,                                       \
                    void*                       const   resultPtr) {                                    \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                 \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _low_power_enter_ESP32(             \
            const   void*                       const   inputPtr,                                       \
            void*                       const   resultPtr) {                                            \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return tommRoCHwTemplateBusSPIESP32HalSetForLowPowerEnter(                                      \
                spiHandle.spiHostDevice,                                                                \
                spiConfig.sckGPIONum,                                                                   \
                spiConfig.mosiGPIONum,                                                                  \
                spiConfig.misoGPIONum);                                                                 \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _low_power_exit_ESP32(              \
            const   void*                       const   inputPtr,                                       \
                    void*                       const   resultPtr) {                                    \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return tommRoCHwTemplateBusSPIESP32HalSetForLowPowerExit(                                       \
                spiHandle.spiHostDevice,                                                                \
                spiConfig.sckGPIONum,                                                                   \
                spiConfig.mosiGPIONum,                                                                  \
                spiConfig.misoGPIONum);                                                                 \
    }                                                                                                   \
                                                                                                        \
    static void _spi_master_ ## spiMasterPrefix ## _get_callback_ESP32(                                 \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                                   \
                                                                                                        \
        cbFunctPtr->writeBuffers        = _spi_master_ ## spiMasterPrefix ## _write_buffers_ESP32;      \
        cbFunctPtr->readBuffers         = _spi_master_ ## spiMasterPrefix ## _read_buffers_ESP32;       \
        cbFunctPtr->writeReadBuffer     = _spi_master_ ## spiMasterPrefix ## _write_read_buffer_ESP32;  \
        cbFunctPtr->transceiveBuffer    = _spi_master_ ## spiMasterPrefix ## _transceive_buffer_ESP32;  \
        cbFunctPtr->clearData           = _spi_master_ ## spiMasterPrefix ## _clear_data_ESP32;         \
        cbFunctPtr->lowPowerEnter       = _spi_master_ ## spiMasterPrefix ## _low_power_enter_ESP32;    \
        cbFunctPtr->lowPowerExit        = _spi_master_ ## spiMasterPrefix ## _low_power_exit_ESP32;     \
    }

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI0, TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0, _spi_master_config_0, _spi_master_handle_0);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI1, TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1, _spi_master_config_1, _spi_master_handle_1);
#endif


/******************* BUS set prop functs */

static tommRoC_hw_err_enum_t _set_mode(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   tommRoC_hw_template_bus_spi_master_mode_t*  const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.mode = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.mode = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_baudrate(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   uint32_t*                                   const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.baudRate = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_sck_pin(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   gpio_num_t*                                 const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.sckGPIONum = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.sckGPIONum = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_miso_pin(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   gpio_num_t*                                 const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.misoGPIONum = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.misoGPIONum = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_mosi_pin(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   gpio_num_t*                                 const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.mosiGPIONum = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.mosiGPIONum = *propValuePtr;
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
        return _set_mode(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_BAUD_RATE:
        return _set_baudrate(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_SCK_PIN:
        return _set_sck_pin(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_MISO_PIN:
        return _set_miso_pin(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_MOSI_PIN:
        return _set_mosi_pin(bus, propValuePtr);

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

    tommRoC_hw_template_bus_spi_esp32_hal_config_t halConfig;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(_write_dummy_buffer, __SPI_DUMMYDATA__, sizeof(_write_dummy_buffer)));

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&halConfig.spiHostDevice,    0, sizeof(spi_host_device_t)));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&halConfig.spiBusConfig,     0, sizeof(spi_bus_config_t)));

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&_spi_master_handle_0.spiDeviceInterfaceConfig,  0, sizeof(spi_device_interface_config_t)));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&_spi_master_handle_0.spiDeviceHandle,           0, sizeof(spi_device_handle_t)));

    halConfig.spiHostDevice                 = __SPI_0_HOST_DEVICE__;
    halConfig.spiBusConfig.mosi_io_num      = (int) _spi_master_config_0.mosiGPIONum;
    halConfig.spiBusConfig.miso_io_num      = (int) _spi_master_config_0.misoGPIONum;
    halConfig.spiBusConfig.sclk_io_num      = (int) _spi_master_config_0.sckGPIONum;
    halConfig.spiBusConfig.quadwp_io_num    = (int) GPIO_NUM_NC;    // GPIO_NUM_NC -> not used
    halConfig.spiBusConfig.quadhd_io_num    = (int) GPIO_NUM_NC;    // GPIO_NUM_NC -> not used
    halConfig.spiBusConfig.max_transfer_sz  = 0;                    // 0 means that max transfer size is 4k bytes
    halConfig.spiBusConfig.intr_flags       = 0;
    halConfig.spiBusConfig.flags            = SPICOMMON_BUSFLAG_MASTER;
    if ((int) GPIO_NUM_NC != (int) _spi_master_config_0.sckGPIONum)     { halConfig.spiBusConfig.flags |= SPICOMMON_BUSFLAG_SCLK; }
    if ((int) GPIO_NUM_NC != (int) _spi_master_config_0.misoGPIONum)    { halConfig.spiBusConfig.flags |= SPICOMMON_BUSFLAG_MISO; }
    if ((int) GPIO_NUM_NC != (int) _spi_master_config_0.mosiGPIONum)    { halConfig.spiBusConfig.flags |= SPICOMMON_BUSFLAG_MOSI; }

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusSPIESP32HalMasterInit(&halConfig));

    _spi_master_handle_0.spiDeviceInterfaceConfig.mode              = _spi_master_mode_enum_to_U8(_spi_master_config_0.mode);
    _spi_master_handle_0.spiDeviceInterfaceConfig.clock_speed_hz    = (int) _spi_master_config_0.baudRate;
    _spi_master_handle_0.spiDeviceInterfaceConfig.spics_io_num      = (int) GPIO_NUM_NC;    // CS pin not used here
    _spi_master_handle_0.spiDeviceInterfaceConfig.queue_size        = 1;

    if (ESP_OK != spi_bus_add_device(__SPI_0_HOST_DEVICE__, &_spi_master_handle_0.spiDeviceInterfaceConfig, &_spi_master_handle_0.spiDeviceHandle)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    _spi_master_SPI0_get_callback_ESP32(cbFunctPtr);

    _spi_master_handle_0.spiHostDevice = halConfig.spiHostDevice;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    tommRoC_hw_template_bus_spi_esp32_hal_config_t halConfig;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(_write_dummy_buffer, __SPI_DUMMYDATA__, sizeof(_write_dummy_buffer)));

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&halConfig.spiHostDevice,    0, sizeof(spi_host_device_t)));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&halConfig.spiBusConfig,     0, sizeof(spi_bus_config_t)));

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&_spi_master_handle_1.spiDeviceInterfaceConfig,  0, sizeof(spi_device_interface_config_t)));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(&_spi_master_handle_1.spiDeviceHandle,           0, sizeof(spi_device_handle_t)));

    halConfig.spiHostDevice                 = __SPI_1_HOST_DEVICE__;
    halConfig.spiBusConfig.mosi_io_num      = (int) _spi_master_config_1.mosiGPIONum;
    halConfig.spiBusConfig.miso_io_num      = (int) _spi_master_config_1.misoGPIONum;
    halConfig.spiBusConfig.sclk_io_num      = (int) _spi_master_config_1.sckGPIONum;
    halConfig.spiBusConfig.quadwp_io_num    = (int) GPIO_NUM_NC;    // GPIO_NUM_NC -> not used
    halConfig.spiBusConfig.quadhd_io_num    = (int) GPIO_NUM_NC;    // GPIO_NUM_NC -> not used
    halConfig.spiBusConfig.max_transfer_sz  = 0;                    // 0 means that max transfer size is 4k bytes
    halConfig.spiBusConfig.intr_flags       = 0;
    halConfig.spiBusConfig.flags            = SPICOMMON_BUSFLAG_MASTER;
    if ((int) GPIO_NUM_NC != (int) _spi_master_config_1.sckGPIONum)     { halConfig.spiBusConfig.flags |= SPICOMMON_BUSFLAG_SCLK; }
    if ((int) GPIO_NUM_NC != (int) _spi_master_config_1.misoGPIONum)    { halConfig.spiBusConfig.flags |= SPICOMMON_BUSFLAG_MISO; }
    if ((int) GPIO_NUM_NC != (int) _spi_master_config_1.mosiGPIONum)    { halConfig.spiBusConfig.flags |= SPICOMMON_BUSFLAG_MOSI; }

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusSPIESP32HalMasterInit(&halConfig));

    _spi_master_handle_1.spiDeviceInterfaceConfig.mode              = _spi_master_mode_enum_to_U8(_spi_master_config_1.mode);
    _spi_master_handle_1.spiDeviceInterfaceConfig.clock_speed_hz    = (int) _spi_master_config_1.baudRate;
    _spi_master_handle_1.spiDeviceInterfaceConfig.spics_io_num      = (int) GPIO_NUM_NC;    // CS pin not used here
    _spi_master_handle_1.spiDeviceInterfaceConfig.queue_size        = 1;

    if (ESP_OK != spi_bus_add_device(__SPI_1_HOST_DEVICE__, &_spi_master_handle_1.spiDeviceInterfaceConfig, &_spi_master_handle_1.spiDeviceHandle)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    _spi_master_SPI1_get_callback_ESP32(cbFunctPtr);

    _spi_master_handle_1.spiHostDevice = halConfig.spiHostDevice;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif
