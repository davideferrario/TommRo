
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentSPIMaster.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "bus/common/spi/master/tommRoCHwTemplateBusCommonSPIMasterCb.h"

#include "bus/env/arm/SiLabs/spi/tommRoCHwTemplateBusSPISiLabsHal.h"
#include "bus/env/arm/SiLabs/spi/tommRoCHwTemplateBusSPISiLabsLocation.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __DEFAULT_MODE__                (TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_0)
#define __DEFAULT_BAUDRATE__            (500000)

#define __SPI_DUMMYDATA__               (0xFF)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    tommRoC_hw_template_bus_spi_master_mode_t       mode;
    uint32_t                                        baudRate;
    tommRoC_hw_template_bus_spi_silabs_location_t   siLabsLocation;

} __tommRoC_hw_spi_master_config_t__;

#define __EMPTY___tommRoC_hw_spi_master_config_t____                                \
{                                                                                   \
    /* .mode */         __DEFAULT_MODE__,                                           \
    /* .baudRate */     __DEFAULT_BAUDRATE__,                                       \
/* .siLabsLocation */   __EMPTY_tommRoC_hw_template_bus_spi_silabs_location_t__,    \
}

typedef struct {

    void*       spiPtr;

} __tommRoC_hw_spi_master_handle_t__;

#define __EMPTY___tommRoC_hw_spi_master_handle_t____    \
{                                                       \
    /* .spiPtr */           NULL,                       \
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

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if defined (USART_PRESENT) && USART_COUNT
static tommRoC_hw_err_enum_t _spi_master_write_transfer(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
        const   uint8_t*                            const   writeBufferPtr,
        const   uint16_t                                    writeBufferLen,
        const   uint32_t                                    timeoutMsec) {

    uint16_t i;
    uint8_t* ptr;

    TOMMROC_UTIL_UNUSED_PARAM(timeoutMsec);

    for (i = 0, ptr = (uint8_t*) writeBufferPtr; i < writeBufferLen; ++i, ++ptr) {
        USART_SpiTransfer((USART_TypeDef*) spiHandlePtr->spiPtr, *ptr);
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _spi_master_read_transfer(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    toReadAmount,
        const   uint32_t                                    timeoutMsec) {

    uint16_t i;
    uint8_t* ptr;

    TOMMROC_UTIL_UNUSED_PARAM(timeoutMsec);

    for (i = 0, ptr = readBufferPtr; i < toReadAmount; ++i, ++ptr) {
        *ptr = USART_SpiTransfer((USART_TypeDef*) spiHandlePtr->spiPtr, __SPI_DUMMYDATA__);
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _spi_master_transceive_transfer(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
        const   uint8_t*                            const   writeBufferPtr,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    bufferLength,
        const   uint32_t                                    timeoutMsec) {

    uint16_t i;
    uint8_t* ptrWr;
    uint8_t* ptrRd;

    TOMMROC_UTIL_UNUSED_PARAM(timeoutMsec);

    ptrWr   = (uint8_t*) writeBufferPtr;
    ptrRd   = readBufferPtr;

    for (i = 0; i < bufferLength; ++i, ++ptrWr, ++ptrRd) {
        *ptrRd = USART_SpiTransfer((USART_TypeDef*) spiHandlePtr->spiPtr, *ptrWr);
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_write_buffers(
                void*                       const   spiConfigPtr,
                void*                       const   spiHandlePtr,
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   uint32_t                            timeoutPerByteMsec) {

    const tommRoC_hw_bus_write_buf_t* writeBufferPtr;
    uint8_t index;

    TOMMROC_UTIL_UNUSED_PARAM(spiConfigPtr);

    for (index = 0, writeBufferPtr = writeBuffersPtr; index < writeBuffersAmount; ++index, ++writeBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _spi_master_write_transfer(
                        spiHandlePtr,
                        writeBufferPtr->bufferPtr,
                        writeBufferPtr->toWriteAmount,
                        timeoutPerByteMsec * writeBufferPtr->toWriteAmount));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_read_buffers(
                void*                       const   spiConfigPtr,
                void*                       const   spiHandlePtr,
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   uint32_t                            timeoutPerByteMsec) {

    tommRoC_hw_bus_read_buf_t* readBufferPtr;
    uint8_t index;

    TOMMROC_UTIL_UNUSED_PARAM(spiConfigPtr);

    for (index = 0, readBufferPtr = readBuffersPtr; index < readBuffersAmount; ++index, ++readBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _spi_master_read_transfer(
                        spiHandlePtr,
                        readBufferPtr->bufferPtr,
                        readBufferPtr->toReadAmount,
                        timeoutPerByteMsec * readBufferPtr->toReadAmount));

        *(readBufferPtr->readedAmountPtr) = readBufferPtr->toReadAmount;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _phy_transceive_buffer(
                void*                       const   spiConfigPtr,
                void*                       const   spiHandlePtr,
        const   uint8_t*                    const   writeBufferPtr,
                uint8_t*                    const   readBufferPtr,
        const   uint16_t                            bufferLength,
        const   uint32_t                            timeoutPerByteMsec) {

    TOMMROC_UTIL_UNUSED_PARAM(spiConfigPtr);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _spi_master_transceive_transfer(
                    spiHandlePtr,
                    writeBufferPtr,
                    readBufferPtr,
                    bufferLength,
                    timeoutPerByteMsec * bufferLength));

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif


/******************* BUS implementation functs */

#define __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(                                \
                spiMasterPrefix,                                                                        \
                spiMaster,                                                                              \
                spiConfig,                                                                              \
                spiHandle,                                                                              \
                spiClock)                                                                               \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _write_buffers_ARM(                 \
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
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _read_buffers_ARM(                  \
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
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _transceive_buffer_ARM(             \
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
                NULL,                                                                                   \
                &spiHandle,                                                                             \
                _phy_transceive_buffer);                                                                \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _clear_data_ARM(                    \
            const   void*                       const   inputPtr,                                       \
                    void*                       const   resultPtr) {                                    \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                 \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _low_power_enter_ARM(               \
            const   void*                       const   inputPtr,                                       \
                    void*                       const   resultPtr) {                                    \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return tommRoCHwTemplateBusSPISiLabsHalSetForLowPowerEnter(                                     \
                spiClock,                                                                               \
                &spiConfig.siLabsLocation);                                                             \
    }                                                                                                   \
                                                                                                        \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _low_power_exit_ARM(                \
            const   void*                       const   inputPtr,                                       \
                    void*                       const   resultPtr) {                                    \
                                                                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                           \
                                                                                                        \
        return tommRoCHwTemplateBusSPISiLabsHalSetForLowPowerExit(                                      \
                spiClock,                                                                               \
                &spiConfig.siLabsLocation);                                                             \
    }                                                                                                   \
                                                                                                        \
    static void _spi_master_ ## spiMasterPrefix ## _get_callback_ARM(                                   \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                                   \
                                                                                                        \
        cbFunctPtr->writeBuffers        = _spi_master_ ## spiMasterPrefix ## _write_buffers_ARM;        \
        cbFunctPtr->readBuffers         = _spi_master_ ## spiMasterPrefix ## _read_buffers_ARM;         \
        cbFunctPtr->transceiveBuffer    = _spi_master_ ## spiMasterPrefix ## _transceive_buffer_ARM;    \
        cbFunctPtr->clearData           = _spi_master_ ## spiMasterPrefix ## _clear_data_ARM;           \
        cbFunctPtr->lowPowerEnter       = _spi_master_ ## spiMasterPrefix ## _low_power_enter_ARM;      \
        cbFunctPtr->lowPowerExit        = _spi_master_ ## spiMasterPrefix ## _low_power_exit_ARM;       \
    }

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI0, TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0, _spi_master_config_0, _spi_master_handle_0, cmuClock_USART0);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI1, TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1, _spi_master_config_1, _spi_master_handle_1, cmuClock_USART1);
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

#if defined (_USART_ROUTE_LOCATION_MASK)
static tommRoC_hw_err_enum_t _set_location(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   tommRoC_hw_template_bus_location_enum_t*    const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        return tommRoCHwTemplateBusSPISiLabsLocationGetMaster(bus, *propValuePtr, &_spi_master_config_0.siLabsLocation);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        return tommRoCHwTemplateBusSPISiLabsLocationGetMaster(bus, *propValuePtr, &_spi_master_config_1.siLabsLocation);
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (_GPIO_USART_ROUTEEN_RESETVALUE)
static tommRoC_hw_err_enum_t _set_sck_port(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   GPIO_Port_TypeDef*                          const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.siLabsLocation.gpioSCKPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.siLabsLocation.gpioSCKPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_miso_port(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   GPIO_Port_TypeDef*                          const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.siLabsLocation.gpioMISOPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.siLabsLocation.gpioMISOPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_mosi_port(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   GPIO_Port_TypeDef*                          const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.siLabsLocation.gpioMOSIPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.siLabsLocation.gpioMOSIPort = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_sck_pin(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   uint32_t*                                   const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.siLabsLocation.gpioSCKPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.siLabsLocation.gpioSCKPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_miso_pin(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   uint32_t*                                   const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.siLabsLocation.gpioMISOPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.siLabsLocation.gpioMISOPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_mosi_pin(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   uint32_t*                                   const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.siLabsLocation.gpioMOSIPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.siLabsLocation.gpioMOSIPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

static USART_ClockMode_TypeDef _spi_master_mode_enum_to_USART_ClockMode(const tommRoC_hw_template_bus_spi_master_mode_t mode) {

    switch (mode) {

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_0:    return usartClockMode0;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_1:    return usartClockMode1;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_2:    return usartClockMode2;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_3:    return usartClockMode3;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;
    }

    return usartClockMode0;
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

#if defined (_USART_ROUTE_LOCATION_MASK)
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_LOCATION:
        return _set_location(bus, propValuePtr);
#endif

#if defined (_GPIO_USART_ROUTEEN_RESETVALUE)
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_SCK_PORT:
        return _set_sck_port(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_MISO_PORT:
        return _set_miso_port(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_MOSI_PORT:
        return _set_mosi_port(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_SCK_PIN:
        return _set_sck_pin(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_MISO_PIN:
        return _set_miso_pin(bus, propValuePtr);

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_PROP_MOSI_PIN:
        return _set_mosi_pin(bus, propValuePtr);
#endif

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

    tommRoC_hw_template_bus_spi_silabs_hal_config_t halConfig;

    halConfig.clock     = cmuClock_USART0;
    halConfig.spiPtr    = (void*) USART0;
    halConfig.baudRate  = _spi_master_config_0.baudRate;
    halConfig.clockMode = _spi_master_mode_enum_to_USART_ClockMode(_spi_master_config_0.mode);
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&halConfig.location, &_spi_master_config_0.siLabsLocation, sizeof(tommRoC_hw_template_bus_spi_silabs_location_t)));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusSPISiLabsHalMasterInit(&halConfig));

    _spi_master_SPI0_get_callback_ARM(cbFunctPtr);

    _spi_master_handle_0.spiPtr = halConfig.spiPtr;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    tommRoC_hw_template_bus_spi_silabs_hal_config_t halConfig;

    halConfig.clock     = cmuClock_USART1;
    halConfig.spiPtr    = (void*) USART1;
    halConfig.baudRate  = _spi_master_config_1.baudRate;
    halConfig.clockMode = _spi_master_mode_enum_to_USART_ClockMode(_spi_master_config_1.mode);
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&halConfig.location, &_spi_master_config_1.siLabsLocation, sizeof(tommRoC_hw_template_bus_spi_silabs_location_t)));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusSPISiLabsHalMasterInit(&halConfig));

    _spi_master_SPI1_get_callback_ARM(cbFunctPtr);

    _spi_master_handle_1.spiPtr = halConfig.spiPtr;

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif

#endif
