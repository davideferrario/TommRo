
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateInRAMFileX.h"

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
#if defined (__TOMMROC_USE_IN_RAM_FILE_X_TEMPLATE__)
static tommRoC_err_enum_t _read(
                void*       const   fxMediaDriverInfoPtr,
        const   uint32_t            logicalAddStart,
                void*       const   dataBufferPtr,
        const   uint32_t            dataBufferSize,
                uint32_t*   const   readedLengthPtr) {

    void* RAMBufferPtr = fxMediaDriverInfoPtr;

    TOMMROC_ASSERT_NOT_NULL(RAMBufferPtr);
    TOMMROC_ASSERT_NOT_NULL(dataBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(dataBufferSize);
    TOMMROC_ASSERT_NOT_NULL(readedLengthPtr);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(dataBufferPtr, (uint8_t*) RAMBufferPtr + logicalAddStart, dataBufferSize));
    *readedLengthPtr = dataBufferSize;
    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _write(
                void*       const   fxMediaDriverInfoPtr,
        const   uint32_t            logicalAddStart,
        const   void*       const   dataBufferPtr,
        const   uint32_t            dataBufferSize,
                uint32_t*   const   writtenLengthPtr) {

    void* RAMBufferPtr = fxMediaDriverInfoPtr;

    TOMMROC_ASSERT_NOT_NULL(RAMBufferPtr);
    TOMMROC_ASSERT_NOT_NULL(dataBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(dataBufferSize);
    TOMMROC_ASSERT_NOT_NULL(writtenLengthPtr);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy((uint8_t*) RAMBufferPtr + logicalAddStart, dataBufferPtr, dataBufferSize));
    *writtenLengthPtr = dataBufferSize;
    return TOMMRO_C_ERR_SUCCESS;
}

static tommRoC_err_enum_t _release(
                void*       const   fxMediaDriverInfoPtr,
        const   uint32_t            logicalAddStart,
        const   uint32_t            dataSize,
                uint32_t*   const   releasedLengthPtr) {

    void* RAMBufferPtr = fxMediaDriverInfoPtr;

    TOMMROC_ASSERT_NOT_NULL(RAMBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(dataSize);
    TOMMROC_ASSERT_NOT_NULL(releasedLengthPtr);

    TEST_ASSERT_EQUAL(TOMMRO_C_ERR_SUCCESS, tommRoCUtilMemSet((uint8_t*) RAMBufferPtr + logicalAddStart, 0xFF, dataSize));
    *releasedLengthPtr = dataSize;
    return TOMMRO_C_ERR_SUCCESS;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateInRAMFileXStart(
                void*                               const   RAMBufferPtr,
        const   uint32_t                                    RAMBufferSize,
        const   tommRoC_guard_t*                    const   guardPtr,
                tommRoC_file_x_file_system_t*       const   fileXHandlePtr) {

#if defined (__TOMMROC_USE_IN_RAM_FILE_X_TEMPLATE__)

    tommRoC_file_x_file_system_config_t fileXConfig;

    TOMMROC_ASSERT_NOT_NULL(RAMBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(RAMBufferSize);

    TOMMROC_PARAM_CHECK_ON_NULL_RETURN_ERR(RAMBufferPtr);
    TOMMROC_PARAM_CHECK_ON_ZERO_RETURN_ERR(RAMBufferSize);

    fileXConfig.fxMediaDriverInfoPtr    = RAMBufferPtr;
    fileXConfig.readCb                  = _read;
    fileXConfig.writeCb                 = _write;
    fileXConfig.releaseCb               = _release;
    fileXConfig.diskRawSizeByte         = RAMBufferSize;

    return tommRoCFileXInit(
            TOMMROC_FILE_X_INIT_FORCE_FORMAT,
            TOMMRO_C_UTIL_DISABLED,
            &fileXConfig,
            guardPtr,
            fileXHandlePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(RAMBufferPtr);
    TOMMROC_UTIL_UNUSED_PARAM(RAMBufferSize);
    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    TOMMROC_UTIL_UNUSED_PARAM(fileXHandlePtr);    

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateInRAMFileXClose(
                tommRoC_file_x_file_system_t*       const   fileXHandlePtr) {

#if defined (__TOMMROC_USE_IN_RAM_FILE_X_TEMPLATE__)

    return tommRoCFileXClose(fileXHandlePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(fileXHandlePtr);

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}
