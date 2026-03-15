
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusSPIMasterSw.h"

#if defined (__TOMMROC_HW_AT_LEAST_ONE_SPI_MASTER_SW_TEMPLATE_IS_USED__)

#include "bus/spi/master/sw/base/gpio/tommRoCHwTemplateBusSPIMasterSwBaseGPIO.h"

#include "bus/spi/master/sw/base/tommRoCHwTemplateBusSPIMasterSwMode0.h"
#include "bus/spi/master/sw/base/tommRoCHwTemplateBusSPIMasterSwMode1.h"
#include "bus/spi/master/sw/base/tommRoCHwTemplateBusSPIMasterSwMode2.h"
#include "bus/spi/master/sw/base/tommRoCHwTemplateBusSPIMasterSwMode3.h"

#include "TOMMROC.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

typedef struct {

    void (*writeByte)(const uint8_t, const tommRoC_hw_template_bus_spi_master_sw_base_gpio_t* const);
    uint8_t (*readByte)(const tommRoC_hw_template_bus_spi_master_sw_base_gpio_t* const);

} _tommRoC_hw_template_bus_spi_master_sw_exchange_funct_t_;

#define __EMPTY__tommRoC_hw_template_bus_spi_master_sw_exchange_funct_t___  \
{                                                                           \
    /* .writeByte */    NULL,                                               \
    /* .readByte */     NULL,                                               \
}

typedef struct {

    tommRoC_hw_template_bus_spi_master_sw_base_gpio_t           baseGpio;
    _tommRoC_hw_template_bus_spi_master_sw_exchange_funct_t_    exchangeFunct;

} _tommRoC_hw_template_bus_spi_master_sw_t_;

#define __EMPTY__tommRoC_hw_template_bus_spi_master_sw_t___                                     \
{                                                                                               \
    /* .baseGpio */         __EMPTY_tommRoC_hw_template_bus_spi_master_sw_base_gpio_t__,        \
    /* .exchangeFunct */    __EMPTY__tommRoC_hw_template_bus_spi_master_sw_exchange_funct_t___, \
}

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_SW_TEMPLATE__)
static _tommRoC_hw_template_bus_spi_master_sw_t_ _spi_master_0_sw = TOMMROC_UTIL_EMPTY_VARIABLE(_tommRoC_hw_template_bus_spi_master_sw_t_);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_SW_TEMPLATE__)
static _tommRoC_hw_template_bus_spi_master_sw_t_ _spi_master_1_sw = TOMMROC_UTIL_EMPTY_VARIABLE(_tommRoC_hw_template_bus_spi_master_sw_t_);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_SW_TEMPLATE__)
static _tommRoC_hw_template_bus_spi_master_sw_t_ _spi_master_2_sw = TOMMROC_UTIL_EMPTY_VARIABLE(_tommRoC_hw_template_bus_spi_master_sw_t_);
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_hw_err_enum_t _spi_master_write_buffer_bit_bang(
        const   _tommRoC_hw_template_bus_spi_master_sw_t_*  const   spiMasterSwPtr,
        const   uint8_t*                                    const   writeBufferPtr,
        const   uint16_t                                            writeBufferLen) {
    
    uint8_t* ptr;

    for (ptr = (uint8_t*) writeBufferPtr; (uint16_t) (ptr - writeBufferPtr) < writeBufferLen; ++ptr) {

        spiMasterSwPtr->exchangeFunct.writeByte(*ptr, &spiMasterSwPtr->baseGpio);
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _spi_master_read_buffer_bit_bang(
        const   _tommRoC_hw_template_bus_spi_master_sw_t_*  const   spiMasterSwPtr,
                uint8_t*                                    const   readBufferPtr,
        const   uint16_t                                            toReadAmount,
                uint16_t*                                   const   readedAmountPtr) {

    uint8_t* ptr;

    for (ptr = (uint8_t*) readBufferPtr; (uint16_t) (ptr - readBufferPtr) < toReadAmount; ++ptr) {

        *ptr = spiMasterSwPtr->exchangeFunct.readByte(&spiMasterSwPtr->baseGpio);
    }

    *readedAmountPtr = toReadAmount;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _spi_master_sw_write_buffers(
        const   _tommRoC_hw_template_bus_spi_master_sw_t_*  const   spiMasterSwPtr,
        const   tommRoC_hw_bus_write_buf_t*                 const   writeBuffersPtr,
        const   uint8_t                                             writeBuffersAmount,
        const   uint8_t*                                    const   inputPtr,
                void*                                       const   resultPtr) {
    
    const tommRoC_hw_bus_write_buf_t* writeBufferPtr;
    uint8_t index;

    TOMMROC_UTIL_UNUSED_PARAM(inputPtr);
    TOMMROC_UTIL_UNUSED_PARAM(resultPtr);

    for (index = 0, writeBufferPtr = writeBuffersPtr; index < writeBuffersAmount; ++index, ++writeBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _spi_master_write_buffer_bit_bang(
                        spiMasterSwPtr,
                        writeBufferPtr->bufferPtr,
                        writeBufferPtr->toWriteAmount));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _spi_master_sw_read_buffers(
        const   _tommRoC_hw_template_bus_spi_master_sw_t_*  const   spiMasterSwPtr,
                tommRoC_hw_bus_read_buf_t*                  const   readBuffersPtr,
        const   uint8_t                                             readBuffersAmount,
        const   uint8_t*                                    const   inputPtr,
                void*                                       const   resultPtr) {

    tommRoC_hw_bus_read_buf_t* readBufferPtr;
    uint8_t index;

    TOMMROC_UTIL_UNUSED_PARAM(inputPtr);
    TOMMROC_UTIL_UNUSED_PARAM(resultPtr);

    for (index = 0, readBufferPtr = readBuffersPtr; index < readBuffersAmount; ++index, ++readBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _spi_master_read_buffer_bit_bang(
                        spiMasterSwPtr,
                        readBufferPtr->bufferPtr,
                        readBufferPtr->toReadAmount,
                        readBufferPtr->readedAmountPtr));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static void _init_pins(
        const   tommRoC_hw_template_bus_spi_master_sw_init_t*   const swInitPtr) {

    switch (swInitPtr->mode) {

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_0:
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_1:
        swInitPtr->clkLow();
        break;

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_2:
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_3:
        swInitPtr->clkHigh();
        break;

    default:
        // Error
        TOMMROC_ASSERT_TRUE(false);
        break;
    }
}

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_SW_TEMPLATE__)
static tommRoC_hw_err_enum_t _spi_master_0_sw_write_buffers(
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _spi_master_sw_write_buffers(
            &_spi_master_0_sw,
            writeBuffersPtr,
            writeBuffersAmount,
            inputPtr,
            resultPtr);
}

static tommRoC_hw_err_enum_t _spi_master_0_sw_read_buffers(
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _spi_master_sw_read_buffers(
            &_spi_master_0_sw,
            readBuffersPtr,
            readBuffersAmount,
            inputPtr,
            resultPtr);
}

static void _spi_master_0_sw_get_callback(
        tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwBusCbFunctReset(cbFunctPtr));

    cbFunctPtr->writeBuffers    = _spi_master_0_sw_write_buffers;
    cbFunctPtr->readBuffers     = _spi_master_0_sw_read_buffers;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_SW_TEMPLATE__)
static tommRoC_hw_err_enum_t _spi_master_1_sw_write_buffers(
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _spi_master_sw_write_buffers(
            &_spi_master_1_sw,
            writeBuffersPtr,
            writeBuffersAmount,
            inputPtr,
            resultPtr);
}

static tommRoC_hw_err_enum_t _spi_master_1_sw_read_buffers(
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _spi_master_sw_read_buffers(
            &_spi_master_1_sw,
            readBuffersPtr,
            readBuffersAmount,
            inputPtr,
            resultPtr);
}

static void _spi_master_1_sw_get_callback(
        tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwBusCbFunctReset(cbFunctPtr));

    cbFunctPtr->writeBuffers    = _spi_master_1_sw_write_buffers;
    cbFunctPtr->readBuffers     = _spi_master_1_sw_read_buffers;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_SW_TEMPLATE__)
static tommRoC_hw_err_enum_t _spi_master_2_sw_write_buffers(
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _spi_master_sw_write_buffers(
            &_spi_master_2_sw,
            writeBuffersPtr,
            writeBuffersAmount,
            inputPtr,
            resultPtr);
}

static tommRoC_hw_err_enum_t _spi_master_2_sw_read_buffers(
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _spi_master_sw_read_buffers(
            &_spi_master_2_sw,
            readBuffersPtr,
            readBuffersAmount,
            inputPtr,
            resultPtr);
}

static void _spi_master_2_sw_get_callback(
        tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwBusCbFunctReset(cbFunctPtr));

    cbFunctPtr->writeBuffers    = _spi_master_2_sw_write_buffers;
    cbFunctPtr->readBuffers     = _spi_master_2_sw_read_buffers;
}
#endif

static tommRoC_hw_err_enum_t _ckeck_init_param(
        const   tommRoC_hw_template_bus_spi_master_sw_init_t*   const   swInitPtr) {

    TOMMROC_ASSERT_NOT_NULL(swInitPtr);
    TOMMROC_ASSERT_NOT_NULL(swInitPtr->clkHigh);
    TOMMROC_ASSERT_NOT_NULL(swInitPtr->clkLow);
    TOMMROC_ASSERT_NOT_NULL(swInitPtr->mosiHigh);
    TOMMROC_ASSERT_NOT_NULL(swInitPtr->mosiLow);
    TOMMROC_ASSERT_NOT_NULL(swInitPtr->misoStatus);
    TOMMROC_ASSERT_NOT_ZERO(swInitPtr->baudRateKbits);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(swInitPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(swInitPtr->clkHigh);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(swInitPtr->clkLow);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(swInitPtr->mosiHigh);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(swInitPtr->mosiLow);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(swInitPtr->misoStatus);
    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(swInitPtr->baudRateKbits);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static void _init_spi_master_sw_struct(
        const   tommRoC_hw_template_bus_spi_master_sw_init_t*   const   swInitPtr,
                _tommRoC_hw_template_bus_spi_master_sw_t_*      const   spiMasterSwPtr) {

    spiMasterSwPtr->baseGpio.clkHigh    = swInitPtr->clkHigh;
    spiMasterSwPtr->baseGpio.clkLow     = swInitPtr->clkLow;
    spiMasterSwPtr->baseGpio.mosiHigh   = swInitPtr->mosiHigh;
    spiMasterSwPtr->baseGpio.mosiLow    = swInitPtr->mosiLow;
    spiMasterSwPtr->baseGpio.misoStatus = swInitPtr->misoStatus;

    spiMasterSwPtr->baseGpio.baseDelayUsec = (uint32_t) (1000) / ((uint32_t) swInitPtr->baudRateKbits * (uint32_t) 2);

    switch (swInitPtr->mode) {
    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_0:
        if (0 == spiMasterSwPtr->baseGpio.baseDelayUsec) {
            spiMasterSwPtr->exchangeFunct.writeByte = tommRoCHwTemplateBusSPIMasterSwMode0WriteByteNoDelay;
            spiMasterSwPtr->exchangeFunct.readByte  = tommRoCHwTemplateBusSPIMasterSwMode0ReadByteNoDelay;
        }
        else {
            spiMasterSwPtr->exchangeFunct.writeByte = tommRoCHwTemplateBusSPIMasterSwMode0WriteByte;
            spiMasterSwPtr->exchangeFunct.readByte  = tommRoCHwTemplateBusSPIMasterSwMode0ReadByte;
        }
        break;

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_1:
        if (0 == spiMasterSwPtr->baseGpio.baseDelayUsec) {
            spiMasterSwPtr->exchangeFunct.writeByte = tommRoCHwTemplateBusSPIMasterSwMode1WriteByteNoDelay;
            spiMasterSwPtr->exchangeFunct.readByte  = tommRoCHwTemplateBusSPIMasterSwMode1ReadByteNoDelay;
        }
        else {
            spiMasterSwPtr->exchangeFunct.writeByte = tommRoCHwTemplateBusSPIMasterSwMode1WriteByte;
            spiMasterSwPtr->exchangeFunct.readByte  = tommRoCHwTemplateBusSPIMasterSwMode1ReadByte;
        }
        break;

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_2:
        if (0 == spiMasterSwPtr->baseGpio.baseDelayUsec) {
            spiMasterSwPtr->exchangeFunct.writeByte = tommRoCHwTemplateBusSPIMasterSwMode2WriteByteNoDelay;
            spiMasterSwPtr->exchangeFunct.readByte  = tommRoCHwTemplateBusSPIMasterSwMode2ReadByteNoDelay;
        }
        else {
            spiMasterSwPtr->exchangeFunct.writeByte = tommRoCHwTemplateBusSPIMasterSwMode2WriteByte;
            spiMasterSwPtr->exchangeFunct.readByte  = tommRoCHwTemplateBusSPIMasterSwMode2ReadByte;
        }
        break;

    case TOMMRO_C_HW_TEMPLATE_BUS_SPI_MASTER_MODE_3:
        if (0 == spiMasterSwPtr->baseGpio.baseDelayUsec) {
            spiMasterSwPtr->exchangeFunct.writeByte = tommRoCHwTemplateBusSPIMasterSwMode3WriteByteNoDelay;
            spiMasterSwPtr->exchangeFunct.readByte  = tommRoCHwTemplateBusSPIMasterSwMode3ReadByteNoDelay;
        }
        else {
            spiMasterSwPtr->exchangeFunct.writeByte = tommRoCHwTemplateBusSPIMasterSwMode3WriteByte;
            spiMasterSwPtr->exchangeFunct.readByte  = tommRoCHwTemplateBusSPIMasterSwMode3ReadByte;
        }
        break;

    default:
        // Error
        TOMMROC_ASSERT_TRUE(false);
        break;
    }
}

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_SW_TEMPLATE__)

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMaster0SwStart(
        const   tommRoC_hw_template_bus_spi_master_sw_init_t*   const   swInitPtr,
                tommRoC_hw_bus_t*                               const   busHandlePtr) {

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_ckeck_init_param(swInitPtr));

    _init_pins(swInitPtr);

    _init_spi_master_sw_struct(swInitPtr, &_spi_master_0_sw);

    _spi_master_0_sw_get_callback(&cbFunct);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwBusInit(
                    TOMMRO_C_HW_BUS_SPI_MASTER_BUS_TYPE,
                    &cbFunct,
                    busHandlePtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_SW_TEMPLATE__)

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMaster1SwStart(
        const   tommRoC_hw_template_bus_spi_master_sw_init_t*   const   swInitPtr,
                tommRoC_hw_bus_t*                               const   busHandlePtr) {

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_ckeck_init_param(swInitPtr));

    _init_pins(swInitPtr);

    _init_spi_master_sw_struct(swInitPtr, &_spi_master_1_sw);

    _spi_master_1_sw_get_callback(&cbFunct);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwBusInit(
                    TOMMRO_C_HW_BUS_SPI_MASTER_BUS_TYPE,
                    &cbFunct,
                    busHandlePtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_SW_TEMPLATE__)

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMaster2SwStart(
        const   tommRoC_hw_template_bus_spi_master_sw_init_t*   const   swInitPtr,
                tommRoC_hw_bus_t*                               const   busHandlePtr) {

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_ckeck_init_param(swInitPtr));

    _init_pins(swInitPtr);

    _init_spi_master_sw_struct(swInitPtr, &_spi_master_2_sw);

    _spi_master_2_sw_get_callback(&cbFunct);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwBusInit(
                    TOMMRO_C_HW_BUS_SPI_MASTER_BUS_TYPE,
                    &cbFunct,
                    busHandlePtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif

#endif
