
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusCommonI2CMasterCb.h"

#include "bus/common/i2c/master/tommRoCHwTemplateBusCommonI2CMaster.h"

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

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonI2CMasterCbWriteBuffers(
        const   tommRoC_hw_bus_write_buf_t*                 const   writeBuffersPtr,
        const   uint8_t                                             writeBuffersAmount,
        const   tommRoC_hw_bus_device_specific_i2c_slave_t* const   specificI2CSlavePtr,
                void*                                       const   i2cConfigPtr,
                void*                                       const   i2cHandlePtr,
                tommRoC_hw_template_bus_common_i2c_master_cb_phy_write_buffers_t phyWriteBuffers) {

    uint8_t slaveAddress7Bit;
    uint8_t retryCount;
    uint8_t retryCountMax;
    tommRoC_hw_err_enum_t res;

    TOMMROC_ASSERT_NOT_NULL(writeBuffersPtr);
    TOMMROC_ASSERT_NOT_ZERO(writeBuffersAmount);
    TOMMROC_ASSERT_NOT_NULL(specificI2CSlavePtr);
    TOMMROC_ASSERT_NOT_NULL(i2cHandlePtr);
    TOMMROC_ASSERT_NOT_NULL(phyWriteBuffers);

    slaveAddress7Bit = (uint8_t) specificI2CSlavePtr->slaveAddress;

    retryCountMax = ((1 == writeBuffersAmount) && (NULL == writeBuffersPtr->bufferPtr) && (0 == writeBuffersPtr->toWriteAmount)) ? 1 : I2C_MASTER_RETRY_COUNT;

    for (retryCount = 0; retryCount < retryCountMax; ++retryCount) {

        res = phyWriteBuffers(
                i2cConfigPtr,
                i2cHandlePtr,
                slaveAddress7Bit,
                writeBuffersPtr,
                writeBuffersAmount,
                I2C_MASTER_WRITE_x_BYTE_TIMEOUT_MSEC);

        if (TOMMRO_C_HW_ERR_SUCCESS == res) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(I2C_MASTER_ON_ERROR_WAIT_MSEC));
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonI2CMasterCbReadBuffers(
                tommRoC_hw_bus_read_buf_t*                  const   readBuffersPtr,
        const   uint8_t                                             readBuffersAmount,
        const   tommRoC_hw_bus_device_specific_i2c_slave_t* const   specificI2CSlavePtr,
                void*                                       const   i2cConfigPtr,
                void*                                       const   i2cHandlePtr,
                tommRoC_hw_template_bus_common_i2c_master_cb_phy_read_buffers_t phyReadBuffers) {

    uint8_t slaveAddress7Bit;
    uint8_t retryCount;
    uint8_t retryCountMax;
    tommRoC_hw_err_enum_t res;

    TOMMROC_ASSERT_NOT_NULL(readBuffersPtr);
    TOMMROC_ASSERT_NOT_ZERO(readBuffersAmount);
    TOMMROC_ASSERT_NOT_NULL(specificI2CSlavePtr);
    TOMMROC_ASSERT_NOT_NULL(i2cHandlePtr);
    TOMMROC_ASSERT_NOT_NULL(phyReadBuffers);

    slaveAddress7Bit = (uint8_t) specificI2CSlavePtr->slaveAddress;

    retryCountMax = ((1 == readBuffersAmount) && (NULL == readBuffersPtr->bufferPtr) && (0 == readBuffersPtr->toReadAmount)) ? 1 : I2C_MASTER_RETRY_COUNT;

    for (retryCount = 0; retryCount < retryCountMax; ++retryCount) {

        res = phyReadBuffers(
                i2cConfigPtr,
                i2cHandlePtr,
                slaveAddress7Bit,
                readBuffersPtr,
                readBuffersAmount,
                I2C_MASTER_READ_x_BYTE_TIMEOUT_MSEC);

        if (TOMMRO_C_HW_ERR_SUCCESS == res) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(I2C_MASTER_ON_ERROR_WAIT_MSEC));
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusCommonI2CMasterCbWriteReadBuffer(
        const   uint8_t*                                    const   writeBufferPtr,
        const   uint16_t                                            writeBufferLen,
                uint8_t*                                    const   readBufferPtr,
        const   uint16_t                                            toReadAmount,
                uint16_t*                                   const   readedAmountPtr,
        const   uint32_t                                            delayWriteToReadMsec,
        const   tommRoC_hw_bus_device_specific_i2c_slave_t* const   specificI2CSlavePtr,
                void*                                       const   i2cConfigPtr,
                void*                                       const   i2cHandlePtr,
                tommRoC_hw_template_bus_common_i2c_master_cb_phy_write_read_buffer_t phyWriteReadBuffer) {

    uint8_t slaveAddress7Bit;
    uint8_t retryCount;
    tommRoC_hw_err_enum_t res;

    /**
     * NOTE:
     * for I2C master it is possible to write a NULL/zero length buffer.
     * Used to just send slave I2C address.
     */

    TOMMROC_ASSERT_NOT_NULL(readBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(toReadAmount);
    TOMMROC_ASSERT_NOT_NULL(readedAmountPtr);
    TOMMROC_ASSERT_NOT_NULL(specificI2CSlavePtr);
    TOMMROC_ASSERT_NOT_NULL(i2cHandlePtr);
    TOMMROC_ASSERT_NOT_NULL(phyWriteReadBuffer);

    slaveAddress7Bit = (uint8_t) specificI2CSlavePtr->slaveAddress;

    for (retryCount = 0; retryCount < I2C_MASTER_RETRY_COUNT; ++retryCount) {

        res = phyWriteReadBuffer(
                i2cConfigPtr,
                i2cHandlePtr,
                slaveAddress7Bit,
                writeBufferPtr,
                writeBufferLen,
                readBufferPtr,
                toReadAmount,
                delayWriteToReadMsec,
                I2C_MASTER_WRITE_READ_x_BYTE_TIMEOUT_MSEC);

        if (TOMMRO_C_HW_ERR_SUCCESS == res) {
            *readedAmountPtr = toReadAmount;
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(I2C_MASTER_ON_ERROR_WAIT_MSEC));
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
}
