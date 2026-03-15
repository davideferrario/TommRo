
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusCommonSPIMasterCb.h"

#include "bus/common/spi/master/tommRoCHwTemplateBusCommonSPIMaster.h"

#include "TOMMROC.h"

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

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonSPIMasterCbWriteBuffers(
        const   tommRoC_hw_bus_write_buf_t*                 const   writeBuffersPtr,
        const   uint8_t                                             writeBuffersAmount,
                void*                                       const   spiConfigPtr,
                void*                                       const   spiHandlePtr,
                tommRoC_hw_template_bus_common_spi_master_cb_phy_write_buffers_t phyWriteBuffers) {

    uint8_t retryCount;
    tommRoC_hw_err_enum_t res;

    TOMMROC_ASSERT_NOT_NULL(writeBuffersPtr);
    TOMMROC_ASSERT_NOT_ZERO(writeBuffersAmount);
    TOMMROC_ASSERT_NOT_NULL(spiHandlePtr);
    TOMMROC_ASSERT_NOT_NULL(phyWriteBuffers);

    for (retryCount = 0; retryCount < SPI_MASTER_RETRY_COUNT; ++retryCount) {

        res = phyWriteBuffers(
                spiConfigPtr,
                spiHandlePtr,
                writeBuffersPtr,
                writeBuffersAmount,
                SPI_MASTER_WRITE_x_BYTE_TIMEOUT_MSEC);

        if (TOMMRO_C_HW_ERR_SUCCESS == res) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(SPI_MASTER_ON_ERROR_WAIT_MSEC));
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonSPIMasterCbReadBuffers(
                tommRoC_hw_bus_read_buf_t*                  const   readBuffersPtr,
        const   uint8_t                                             readBuffersAmount,
                void*                                       const   spiConfigPtr,
                void*                                       const   spiHandlePtr,
                tommRoC_hw_template_bus_common_spi_master_cb_phy_read_buffers_t phyReadBuffers) {

    uint8_t retryCount;
    tommRoC_hw_err_enum_t res;

    TOMMROC_ASSERT_NOT_NULL(readBuffersPtr);
    TOMMROC_ASSERT_NOT_ZERO(readBuffersAmount);
    TOMMROC_ASSERT_NOT_NULL(spiHandlePtr);
    TOMMROC_ASSERT_NOT_NULL(phyReadBuffers);

    for (retryCount = 0; retryCount < SPI_MASTER_RETRY_COUNT; ++retryCount) {

        res = phyReadBuffers(
                spiConfigPtr,
                spiHandlePtr,
                readBuffersPtr,
                readBuffersAmount,
                SPI_MASTER_READ_x_BYTE_TIMEOUT_MSEC);

        if (TOMMRO_C_HW_ERR_SUCCESS == res) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(SPI_MASTER_ON_ERROR_WAIT_MSEC));
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonSPIMasterCbWriteReadBuffer(
        const   uint8_t*                                    const   writeBufferPtr,
        const   uint16_t                                            writeBufferLen,
                uint8_t*                                    const   readBufferPtr,
        const   uint16_t                                            toReadAmount,
                uint16_t*                                   const   readedAmountPtr,
        const   uint32_t                                            delayWriteToReadMsec,
                void*                                       const   spiConfigPtr,
                void*                                       const   spiHandlePtr,
                tommRoC_hw_template_bus_common_spi_master_cb_phy_write_read_buffer_t phyWriteReadBuffer) {

    uint8_t retryCount;
    tommRoC_hw_err_enum_t res;

    TOMMROC_ASSERT_NOT_NULL(writeBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(writeBufferLen);
    TOMMROC_ASSERT_NOT_NULL(readBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(toReadAmount);
    TOMMROC_ASSERT_NOT_NULL(readedAmountPtr);
    TOMMROC_ASSERT_NOT_NULL(spiHandlePtr);
    TOMMROC_ASSERT_NOT_NULL(phyWriteReadBuffer);

    for (retryCount = 0; retryCount < SPI_MASTER_RETRY_COUNT; ++retryCount) {

        res = phyWriteReadBuffer(
                spiConfigPtr,
                spiHandlePtr,
                writeBufferPtr,
                writeBufferLen,
                readBufferPtr,
                toReadAmount,
                delayWriteToReadMsec,
                SPI_MASTER_WRITE_READ_x_BYTE_TIMEOUT_MSEC);

        if (TOMMRO_C_HW_ERR_SUCCESS == res) {
            *readedAmountPtr = toReadAmount;
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(SPI_MASTER_ON_ERROR_WAIT_MSEC));
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonSPIMasterCbTransceiveBuffer(
        const   uint8_t*                                    const   writeBufferPtr,
                uint8_t*                                    const   readBufferPtr,
        const   uint16_t                                            bufferLength,
                void*                                       const   spiConfigPtr,
                void*                                       const   spiHandlePtr,
                tommRoC_hw_template_bus_common_spi_master_cb_phy_transceive_buffer_t phyTransceiveBuffer) {

    uint8_t retryCount;
    tommRoC_hw_err_enum_t res;

    TOMMROC_ASSERT_NOT_NULL(writeBufferPtr);
    TOMMROC_ASSERT_NOT_NULL(readBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(bufferLength);
    TOMMROC_ASSERT_NOT_NULL(spiHandlePtr);
    TOMMROC_ASSERT_NOT_NULL(phyTransceiveBuffer);

    for (retryCount = 0; retryCount < SPI_MASTER_RETRY_COUNT; ++retryCount) {

        res = phyTransceiveBuffer(
                spiConfigPtr,
                spiHandlePtr,
                writeBufferPtr,
                readBufferPtr,
                bufferLength,
                SPI_MASTER_TRANSCEIVE_x_BYTE_TIMEOUT_MSEC);

        if (TOMMRO_C_HW_ERR_SUCCESS == res) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(SPI_MASTER_ON_ERROR_WAIT_MSEC));
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
}
