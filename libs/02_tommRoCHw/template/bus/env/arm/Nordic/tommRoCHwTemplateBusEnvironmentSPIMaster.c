
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentSPIMaster.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#include "env/tommRoCTemplateEnv.h"

#if defined (__TOMMROC_TEMPLATE_ARM_NORDIC_IS_USED__)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "bus/common/spi/master/tommRoCHwTemplateBusCommonSPIMasterCb.h"

#include "bus/env/arm/Nordic/spi/tommRoCHwTemplateBusSPINordicHal.h"

#include "TOMMROCMwTemplate.h"

#if (defined (SPI_PRESENT) && SPI_COUNT)
#include "nrfx_spi.h"
#endif

#include <stdbool.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __DEFAULT_MODE__                (NRF_SPI_MODE_0)
#define __DEFAULT_FREQUENCY__           (NRF_SPI_FREQ_500K)
#define __DEFAULT_SCK_PIN_NUM__         (NRFX_SPI_PIN_NOT_USED)
#define __DEFAULT_MOSI_PIN_NUM__        (NRFX_SPI_PIN_NOT_USED)
#define __DEFAULT_MISO_PIN_NUM__        (NRFX_SPI_PIN_NOT_USED)

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef struct {

    nrf_spi_mode_t          mode;
    nrf_spi_frequency_t     frequency;
    uint8_t                 sckPin;
    uint8_t                 mosiPin;
    uint8_t                 misoPin;

} __tommRoC_hw_spi_master_config_t__;

#define __EMPTY___tommRoC_hw_spi_master_config_t____    \
{                                                       \
    /* .mode */         __DEFAULT_MODE__,               \
    /* .frequency */    __DEFAULT_FREQUENCY__,          \
    /* .sckPin */       __DEFAULT_SCK_PIN_NUM__,        \
    /* .mosiPin */      __DEFAULT_MOSI_PIN_NUM__,       \
    /* .misoPin */      __DEFAULT_MISO_PIN_NUM__,       \
}

typedef struct {

    bool        cbCalled;
    nrfx_err_t  transferResult;

} __nordic_callback_data_t__;

#define __EMPTY___nordic_callback_data_t____            \
{                                                       \
    /* .cbCalled */         false,                      \
    /* .transferResult */   NRFX_ERROR_INTERNAL,        \
}

typedef struct {

    nrfx_spi_t                  nrfxSpi;
    _nordic_callback_data_t__   nordicCallbackData;

} __tommRoC_hw_spi_master_handle_t__;

#define __EMPTY___tommRoC_hw_spi_master_handle_t____                    \
{                                                                       \
    /* .nrfxSpi */              NRFX_SPI_INSTANCE(0),                   \
    /* .nordicCallbackData */   __EMPTY___nordic_callback_data_t____,   \
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

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
static __tommRoC_hw_spi_master_config_t__ _spi_master_config_2 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_spi_master_config_t__);
static __tommRoC_hw_spi_master_handle_t__ _spi_master_handle_2 = TOMMROC_UTIL_EMPTY_VARIABLE(__tommRoC_hw_spi_master_handle_t__);
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if (defined (SPI_PRESENT) && SPI_COUNT)
static void _nrfx_spi_evt_handler(
                __nordic_callback_data_t__* const   nordicCallbackDataPtr,
                nrfx_spi_evt_t              const*  p_event,
                void*                               p_context) {

    TOMMROC_UTIL_UNUSED_PARAM(p_context);

    switch (p_event->type) {

    case NRFX_SPI_EVENT_DONE:
        nordicCallbackDataPtr->transferResult = NRFX_SUCCESS;
        break;

    default:
        nordicCallbackDataPtr->transferResult = NRFX_ERROR_INTERNAL;
        break;

    }

    nordicCallbackDataPtr->cbCalled = true;
}

static tommRoC_hw_err_enum_t _spi_master_transfer(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
                nrfx_spi_xfer_desc_t*               const   nrfxSpiXferDescPtr,
        const   uint32_t                                    flags,
        const   uint32_t                                    timeoutMsec) {

    nrfx_spi_t* nrfxSpiPtr = &spiHandlePtr->nrfxSpi;

    tommRoC_timer_t timer;
    uint32_t elapsedMsec;

    spiHandlePtr->nordicCallbackData.cbCalled = false;

    if (NRFX_SUCCESS != nrfx_spi_xfer(nrfxSpiPtr, nrfxSpiXferDescPtr, flags)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, timeoutMsec));

    do {

        if (spiHandlePtr->nordicCallbackData.cbCalled) {
            if (NRFX_SUCCESS == spiHandlePtr->nordicCallbackData.transferResult) {
                return TOMMRO_C_HW_ERR_SUCCESS;
            }
            else {
                return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
            }
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerElapsed(&timer, &elapsedMsec));

        if (elapsedMsec > 1) {
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));
        }
        else {
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
            // NOTE: don't replace with tommRoCOsDelayMsec(0) because as fast as possible is needed in case of single task project.
            tommRoCMwThreadYield();
#endif
        }

    } while (TOMMRO_C_TIMER_NOT_EXPIRED_ERR == tommRoCTimerIsExpired(&timer));
    
    // NOTE: in case of timeout expired, check again if SUCCESS because it could be the case in multitask environment
    if ((spiHandlePtr->nordicCallbackData.cbCalled) && (NRFX_SUCCESS == spiHandlePtr->nordicCallbackData.transferResult)) {
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    nrfx_spi_abort(nrfxSpiPtr);

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
}

static tommRoC_hw_err_enum_t _spi_master_write_transfer(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
        const   uint8_t*                            const   writeBufferPtr,
        const   uint16_t                                    writeBufferLen,
        const   uint32_t                                    flags,
        const   uint32_t                                    timeoutMsec) {

    nrfx_spi_xfer_desc_t nrfxSpiXferDesc = NRFX_SPI_XFER_TX(writeBufferPtr, writeBufferLen);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_spi_master_transfer(spiHandlePtr, &nrfxSpiXferDesc, flags, timeoutMsec));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _spi_master_read_transfer(
                __tommRoC_hw_spi_master_handle_t__* const   spiHandlePtr,
                uint8_t*                            const   readBufferPtr,
        const   uint16_t                                    toReadAmount,
        const   uint32_t                                    flags,
        const   uint32_t                                    timeoutMsec) {

    nrfx_spi_xfer_desc_t nrfxSpiXferDesc = NRFX_SPI_XFER_RX(readBufferPtr, toReadAmount);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_spi_master_transfer(spiHandlePtr, &nrfxSpiXferDesc, flags, timeoutMsec));

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
                        0,
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
                        0,
                        timeoutPerByteMsec * readBufferPtr->toReadAmount));

        *(readBufferPtr->readedAmountPtr) = readBufferPtr->toReadAmount;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif


/******************* Driver IRQ event Handler */

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
static void _nrfx_spi0_evt_handler(
                nrfx_spi_evt_t  const*  p_event,
                void*                   p_context) {

    _nrfx_spi_evt_handler(&_spi_master_handle_0.nordicCallbackData, p_event, p_context);
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
static void _nrfx_spi1_evt_handler(
                nrfx_spi_evt_t  const*  p_event,
                void*                   p_context) {

    _nrfx_spi_evt_handler(&_spi_master_handle_1.nordicCallbackData, p_event, p_context);
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
static void _nrfx_spi2_evt_handler(
                nrfx_spi_evt_t  const*  p_event,
                void*                   p_context) {

    _nrfx_spi_evt_handler(&_spi_master_handle_2.nordicCallbackData, p_event, p_context);
}
#endif


/******************* BUS implementation functs */

#define __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(                            \
                spiMasterPrefix,                                                                    \
                spiMaster,                                                                          \
                spiConfig,                                                                          \
                spiHandle)                                                                          \
                                                                                                    \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _write_buffers_ARM(             \
            const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,                            \
            const   uint8_t                             writeBuffersAmount,                         \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonSPIMasterCbWriteBuffers(                                   \
                writeBuffersPtr,                                                                    \
                writeBuffersAmount,                                                                 \
                &spiConfig,                                                                         \
                &spiHandle,                                                                         \
                _phy_write_buffers);                                                                \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _read_buffers_ARM(              \
                    tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,                             \
            const   uint8_t                             readBuffersAmount,                          \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusCommonSPIMasterCbReadBuffers(                                    \
                readBuffersPtr,                                                                     \
                readBuffersAmount,                                                                  \
                &spiConfig,                                                                         \
                &spiHandle,                                                                         \
                _phy_read_buffers);                                                                 \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _clear_data_ARM(                \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                             \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _low_power_enter_ARM(           \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusSPINordicHalSetForLowPowerEnter(                                 \
                spiConfig.sckPin,                                                                   \
                spiConfig.mosiPin,                                                                  \
                spiConfig.misoPin);                                                                 \
    }                                                                                               \
                                                                                                    \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _low_power_exit_ARM(            \
            const   void*                       const   inputPtr,                                   \
                    void*                       const   resultPtr) {                                \
                                                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                        \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                       \
                                                                                                    \
        return tommRoCHwTemplateBusSPINordicHalSetForLowPowerExit(                                  \
                spiConfig.mode,                                                                     \
                spiConfig.sckPin,                                                                   \
                spiConfig.mosiPin,                                                                  \
                spiConfig.misoPin);                                                                 \
    }                                                                                               \
                                                                                                    \
    static void _spi_master_ ## spiMasterPrefix ## _get_callback_ARM(                               \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                               \
                                                                                                    \
        cbFunctPtr->writeBuffers    = _spi_master_ ## spiMasterPrefix ## _write_buffers_ARM;        \
        cbFunctPtr->readBuffers     = _spi_master_ ## spiMasterPrefix ## _read_buffers_ARM;         \
        cbFunctPtr->clearData       = _spi_master_ ## spiMasterPrefix ## _clear_data_ARM;           \
        cbFunctPtr->lowPowerEnter   = _spi_master_ ## spiMasterPrefix ## _low_power_enter_ARM;      \
        cbFunctPtr->lowPowerExit    = _spi_master_ ## spiMasterPrefix ## _low_power_exit_ARM;       \
    }

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI0, TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0, _spi_master_config_0, _spi_master_handle_0);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI1, TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1, _spi_master_config_1, _spi_master_handle_1);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI2, TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_2, _spi_master_config_2, _spi_master_handle_2);
#endif


/******************* BUS set prop functs */

static nrf_spi_mode_t _mode_convert(const tommRoC_hw_template_bus_spi_master_mode_t spiMasterMode) {

    switch (spiMasterMode) {

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_0:    return NRF_SPI_MODE_0;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_1:    return NRF_SPI_MODE_1;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_2:    return NRF_SPI_MODE_2;
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_3:    return NRF_SPI_MODE_3;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;

    }

    return __DEFAULT_MODE__;
}

static nrf_spi_frequency_t _frequency_convert(const uint32_t frequencyU32) {

    switch (frequencyU32) {

    case 125000UL:  return NRF_SPI_FREQ_125K;
    case 250000UL:  return NRF_SPI_FREQ_250K;
    case 500000UL:  return NRF_SPI_FREQ_500K;
    case 1000000UL: return NRF_SPI_FREQ_1M;
    case 2000000UL: return NRF_SPI_FREQ_2M;
    case 4000000UL: return NRF_SPI_FREQ_4M;
    case 8000000UL: return NRF_SPI_FREQ_8M;

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;

    }

    return __DEFAULT_FREQUENCY__;
}

static tommRoC_hw_err_enum_t _set_mode(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   tommRoC_hw_template_bus_spi_master_mode_t*  const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.mode = _mode_convert(*propValuePtr);
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.mode = _mode_convert(*propValuePtr);
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_2:
        _spi_master_config_2.mode = _mode_convert(*propValuePtr);
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
        _spi_master_config_0.frequency = _frequency_convert(*propValuePtr);
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.frequency = _frequency_convert(*propValuePtr);
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_2:
        _spi_master_config_0.frequency = _frequency_convert(*propValuePtr);
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_sck_pin(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   uint8_t*                                    const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.sckPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.sckPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_2:
        _spi_master_config_2.sckPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_mosi_pin(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   uint8_t*                                    const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.mosiPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.mosiPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_2:
        _spi_master_config_2.mosiPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

    default:
        break;

    }

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_miso_pin(
        const   tommRoC_hw_template_bus_spi_master_enum_t           bus,
        const   uint8_t*                                    const   propValuePtr) {

    switch (bus) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_0:
        _spi_master_config_0.misoPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_1:
        _spi_master_config_1.misoPin = *propValuePtr;
        return TOMMRO_C_HW_ERR_SUCCESS;
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
    case TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_2:
        _spi_master_config_2.misoPin = *propValuePtr;
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

    tommRoC_hw_template_bus_spi_nordic_hal_config_t halConfig;

    halConfig.nrfxSpi.p_reg         = NRF_SPI0;
    halConfig.nrfxSpi.drv_inst_idx  = NRFX_SPI0_INST_IDX;
    halConfig.frequency             = _spi_master_config_0.frequency;
    halConfig.mode                  = _spi_master_config_0.mode;
    halConfig.sckPin                = _spi_master_config_0.sckPin;
    halConfig.mosiPin               = _spi_master_config_0.mosiPin;
    halConfig.misoPin               = _spi_master_config_0.misoPin;
    halConfig.nrfxSpiEvtHandler     = _nrfx_spi0_evt_handler;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusSPINordicHalMasterInit(&halConfig));

    _spi_master_SPI0_get_callback_ARM(cbFunctPtr);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&_spi_master_handle_0.nrfxSpi, &halConfig.nrfxSpi, sizeof(nrfx_spi_t)));

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    tommRoC_hw_template_bus_spi_nordic_hal_config_t halConfig;

    halConfig.nrfxSpi.p_reg         = NRF_SPI1;
    halConfig.nrfxSpi.drv_inst_idx  = NRFX_SPI1_INST_IDX;
    halConfig.frequency             = _spi_master_config_1.frequency;
    halConfig.mode                  = _spi_master_config_1.mode;
    halConfig.sckPin                = _spi_master_config_1.sckPin;
    halConfig.mosiPin               = _spi_master_config_1.mosiPin;
    halConfig.misoPin               = _spi_master_config_1.misoPin;
    halConfig.nrfxSpiEvtHandler     = _nrfx_spi1_evt_handler;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusSPINordicHalMasterInit(&halConfig));

    _spi_master_SPI1_get_callback_ARM(cbFunctPtr);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&_spi_master_handle_1.nrfxSpi, &halConfig.nrfxSpi, sizeof(nrfx_spi_t)));

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster2Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    tommRoC_hw_template_bus_spi_nordic_hal_config_t halConfig;

    halConfig.nrfxSpi.p_reg         = NRF_SPI2;
    halConfig.nrfxSpi.drv_inst_idx  = NRFX_SPI2_INST_IDX;
    halConfig.frequency             = _spi_master_config_2.frequency;
    halConfig.mode                  = _spi_master_config_2.mode;
    halConfig.sckPin                = _spi_master_config_2.sckPin;
    halConfig.mosiPin               = _spi_master_config_2.mosiPin;
    halConfig.misoPin               = _spi_master_config_2.misoPin;
    halConfig.nrfxSpiEvtHandler     = _nrfx_spi2_evt_handler;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateBusSPINordicHalMasterInit(&halConfig));

    _spi_master_SPI2_get_callback_ARM(cbFunctPtr);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(&_spi_master_handle_2.nrfxSpi, &halConfig.nrfxSpi, sizeof(nrfx_spi_t)));

    return TOMMRO_C_HW_ERR_SUCCESS;
}
#endif

#endif

#endif

#endif

