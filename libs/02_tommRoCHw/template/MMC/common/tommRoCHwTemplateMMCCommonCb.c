
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateMMCCommonCb.h"

#include "tommRoCHwTemplateMMCCommon.h"

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

tommRoC_hw_err_enum_t tommRoCHwTemplateMMCCommonCbWriteBuffer(
        const   uint32_t            logicalAddStart,
        const   void*       const   writeBufferPtr,
        const   uint32_t            writeBufferLen,
                uint32_t*   const   writtenLenPtr,
                void*       const   MMCConfigPtr,
                void*       const   MMCHandlePtr,
                tommRoC_hw_template_mmc_common_cb_phy_write_buffer_t phyWriteBuffer) {

    uint8_t retryCount;
    tommRoC_hw_err_enum_t res;

    TOMMROC_ASSERT_NOT_NULL(writeBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(writeBufferLen);
    TOMMROC_ASSERT_NOT_NULL(writtenLenPtr);
    TOMMROC_ASSERT_NOT_NULL(MMCHandlePtr);
    TOMMROC_ASSERT_NOT_NULL(phyWriteBuffer);

    for (retryCount = 0; retryCount < MMC_RETRY_COUNT; ++retryCount) {

        res = phyWriteBuffer(
                MMCConfigPtr,
                MMCHandlePtr,
                logicalAddStart,
                writeBufferPtr,
                writeBufferLen,
                writtenLenPtr,
                MMC_WRITE_x_BYTE_TIMEOUT_MSEC);

        if (TOMMRO_C_HW_ERR_SUCCESS == res) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(MMC_ON_ERROR_WAIT_MSEC));
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateMMCCommonCbReadBuffer(
        const   uint32_t            logicalAddStart,
                void*       const   readBufferPtr,
        const   uint32_t            readBufferLen,
                uint32_t*   const   readedLenPtr,
                void*       const   MMCConfigPtr,
                void*       const   MMCHandlePtr,
                tommRoC_hw_template_mmc_common_cb_phy_read_buffer_t phyReadBuffer) {

    uint8_t retryCount;
    tommRoC_hw_err_enum_t res;

    TOMMROC_ASSERT_NOT_NULL(readBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(readBufferLen);
    TOMMROC_ASSERT_NOT_NULL(readedLenPtr);
    TOMMROC_ASSERT_NOT_NULL(MMCHandlePtr);
    TOMMROC_ASSERT_NOT_NULL(phyReadBuffer);

    for (retryCount = 0; retryCount < MMC_RETRY_COUNT; ++retryCount) {

        res = phyReadBuffer(
                MMCConfigPtr,
                MMCHandlePtr,
                logicalAddStart,
                readBufferPtr,
                readBufferLen,
                readedLenPtr,
                MMC_READ_x_BYTE_TIMEOUT_MSEC);

        if (TOMMRO_C_HW_ERR_SUCCESS == res) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(MMC_ON_ERROR_WAIT_MSEC));
    }

    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;
}
