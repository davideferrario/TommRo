
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentSPIMaster.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "mcc.h"

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

#define __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(spiMasterPrefix)                        \
                                                                                                                \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _hw_write_buffer_XC(                        \
            const   uint8_t*    const   writeBufferPtr,                                                         \
            const   uint16_t            writeBufferLen) {                                                       \
                                                                                                                \
        spiMasterPrefix ## _Exchange8bitBuffer((uint8_t*) writeBufferPtr, writeBufferLen, NULL);                \
                                                                                                                \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                         \
    }                                                                                                           \
                                                                                                                \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _hw_read_buffer_XC(                         \
                    uint8_t*    const   readBufferPtr,                                                          \
            const   uint16_t            toReadAmount,                                                           \
                    uint16_t*   const   readedAmountPtr) {                                                      \
                                                                                                                \
        uint8_t* ptr;                                                                                           \
                                                                                                                \
        for (ptr = (uint8_t*) readBufferPtr; (uint16_t) (ptr - readBufferPtr) < toReadAmount; ++ptr) {          \
            *ptr = spiMasterPrefix ## _Exchange8bit(DUMMY_DATA);                                                \
        }                                                                                                       \
                                                                                                                \
        *readedAmountPtr = toReadAmount;                                                                        \
                                                                                                                \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                         \
    }                                                                                                           \
                                                                                                                \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _write_buffers_XC(                          \
            const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,                                        \
            const   uint8_t                             writeBuffersAmount,                                     \
            const   void*                       const   inputPtr,                                               \
                    void*                       const   resultPtr) {                                            \
                                                                                                                \
        const tommRoC_hw_bus_write_buf_t* writeBufferPtr;                                                       \
        uint8_t idx;                                                                                            \
                                                                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                                   \
                                                                                                                \
        for (idx = 0, writeBufferPtr = writeBuffersPtr; idx < writeBuffersAmount; ++idx, ++writeBufferPtr) {    \
                                                                                                                \
            TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(                                   \
                    _spi_master_ ## spiMasterPrefix ## _hw_write_buffer_XC(                                     \
                            writeBufferPtr->bufferPtr,                                                          \
                            writeBufferPtr->toWriteAmount));                                                    \
        }                                                                                                       \
                                                                                                                \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                         \
    }                                                                                                           \
                                                                                                                \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _read_buffers_XC(                           \
                    tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,                                         \
            const   uint8_t                             readBuffersAmount,                                      \
            const   void*                       const   inputPtr,                                               \
                    void*                       const   resultPtr) {                                            \
                                                                                                                \
        tommRoC_hw_bus_read_buf_t* readBufferPtr;                                                               \
        uint8_t idx;                                                                                            \
                                                                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                                   \
                                                                                                                \
        for (idx = 0, readBufferPtr = readBuffersPtr; idx < readBuffersAmount; ++idx, ++readBufferPtr) {        \
                                                                                                                \
            TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(                                   \
                    _spi_master_ ## spiMasterPrefix ## _hw_read_buffer_XC(                                      \
                            readBufferPtr->bufferPtr,                                                           \
                            readBufferPtr->toReadAmount,                                                        \
                            readBufferPtr->readedAmountPtr));                                                   \
        }                                                                                                       \
                                                                                                                \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                         \
    }                                                                                                           \
                                                                                                                \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _get_prop_XC(                               \
            const   tommRoC_hw_bus_prop_enum_t          property,                                               \
                    void*                       const   propValuePtr,                                           \
            const   void*                       const   inputPtr,                                               \
                    void*                       const   resultPtr) {                                            \
                                                                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                                   \
                                                                                                                \
        switch (property) {                                                                                     \
                                                                                                                \
        case TOMMRO_C_HW_BUS_PROP_WRITE_COLLISION_OCCURED:                                                      \
            *(bool*)propValuePtr = spiMasterPrefix ## _HasWriteCollisionOccured();                              \
            return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
                                                                                                                \
        default:                                                                                                \
            break;                                                                                              \
                                                                                                                \
        }                                                                                                       \
                                                                                                                \
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;                                                                   \
    }                                                                                                           \
                                                                                                                \
    static tommRoC_hw_err_enum_t _spi_master_ ## spiMasterPrefix ## _set_prop_XC(                               \
            const   tommRoC_hw_bus_prop_enum_t          property,                                               \
            const   void*                       const   propValuePtr,                                           \
            const   void*                       const   inputPtr,                                               \
                    void*                       const   resultPtr) {                                            \
                                                                                                                \
        TOMMROC_UTIL_UNUSED_PARAM(inputPtr);                                                                    \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                                   \
                                                                                                                \
        switch (property) {                                                                                     \
                                                                                                                \
        case TOMMRO_C_HW_BUS_PROP_WRITE_COLLISION_OCCURED:                                                      \
            if (*(bool*) propValuePtr) {                                                                        \
                return TOMMRO_C_HW_PARAM_ERR;                                                                   \
            }                                                                                                   \
                                                                                                                \
            spiMasterPrefix ## _ClearWriteCollisionStatus();                                                    \
            return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
                                                                                                                \
        default:                                                                                                \
        break;                                                                                                  \
        }                                                                                                       \
                                                                                                                \
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;                                                                   \
    }                                                                                                           \
                                                                                                                \
    static void _spi_master_ ## spiMasterPrefix ## _get_callback_XC(                                            \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                                           \
                                                                                                                \
        cbFunctPtr->writeBuffers    = _spi_master_ ## spiMasterPrefix ## _write_buffers_XC;                     \
        cbFunctPtr->readBuffers     = _spi_master_ ## spiMasterPrefix ## _read_buffers_XC;                      \
        cbFunctPtr->getProp         = _spi_master_ ## spiMasterPrefix ## _get_prop_XC;                          \
        cbFunctPtr->setProp         = _spi_master_ ## spiMasterPrefix ## _set_prop_XC;                          \
    }

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI1);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI2);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_3_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI3);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_4_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI4);
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_5_TEMPLATE__)
    __TOMMROC_HW_SPI_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(SPI5);
#endif


#define __TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_START_XC__(spiMasterPrefix, cbFunctPtr)    \
        _spi_master_ ## spiMasterPrefix ## _get_callback_XC(cbFunctPtr);                \
        return TOMMRO_C_HW_ERR_SUCCESS;

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMasterSetProp(
        const   tommRoC_hw_template_bus_spi_master_prop_enum_t          property,
        const   tommRoC_hw_template_bus_spi_master_enum_t               bus,
        const   void*                                           const   propValuePtr) {

    TOMMROC_UTIL_UNUSED_PARAM(property);
    TOMMROC_UTIL_UNUSED_PARAM(bus);
    TOMMROC_UTIL_UNUSED_PARAM(propValuePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster0Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_START_XC__(SPI, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_START_XC__(SPI1, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster2Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_START_XC__(SPI2, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_3_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster3Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_START_XC__(SPI3, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_4_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster4Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_START_XC__(SPI4, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_MASTER_5_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPIMaster5Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_START_XC__(SPI5, cbFunctPtr);
}
#endif

#endif

#endif
