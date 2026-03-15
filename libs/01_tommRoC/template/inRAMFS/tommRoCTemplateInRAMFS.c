
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateInRAMFS.h"

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
#if defined (__TOMMROC_USE_IN_RAM_FS_TEMPLATE__)
static int _read_block(
                tommRoC_fs_param_cb_t*  const   paramPtr,
        const   uint32_t                        blockIdx,
        const   uint32_t                        blockOffset,
                void*                   const   readBufferPtr,
        const   uint32_t                        toReadAmount) {

    void* RAMBufferPtr          = paramPtr->contextPtr;
    uint32_t erasableBlockSize  = paramPtr->erasableBlockSize;
    uint32_t erasableBlockCount = paramPtr->erasableBlockCount;

    TOMMROC_ASSERT_NOT_NULL(RAMBufferPtr);
    TOMMROC_ASSERT_LESS_OR_EQUALS_THAN(blockOffset + toReadAmount, erasableBlockSize);
    TOMMROC_ASSERT_LESS_THAN(blockIdx, erasableBlockCount);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(readBufferPtr, RAMBufferPtr + (blockIdx * erasableBlockSize) + blockOffset, toReadAmount));

    return ((int) TOMMROC_FS_ERR_OK);
}

static int _write_block(
                tommRoC_fs_param_cb_t*  const   paramPtr,
        const   uint32_t                        blockIdx,
        const   uint32_t                        blockOffset,
        const   void*                   const   writeBufferPtr,
        const   uint32_t                        writeBufferLen) {
            
    void* RAMBufferPtr          = paramPtr->contextPtr;
    uint32_t erasableBlockSize  = paramPtr->erasableBlockSize;
    uint32_t erasableBlockCount = paramPtr->erasableBlockCount;
    
    TOMMROC_ASSERT_NOT_NULL(RAMBufferPtr);
    TOMMROC_ASSERT_LESS_OR_EQUALS_THAN(blockOffset + writeBufferLen, erasableBlockSize);
    TOMMROC_ASSERT_LESS_THAN(blockIdx, erasableBlockCount);

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(RAMBufferPtr + (blockIdx * erasableBlockSize) + blockOffset, writeBufferPtr, writeBufferLen));

    return ((int) TOMMROC_FS_ERR_OK);
}

static int _erase_block(
                tommRoC_fs_param_cb_t*  const   paramPtr,
        const   uint32_t                        blockIdx) {
            
    void* RAMBufferPtr          = paramPtr->contextPtr;
    uint32_t erasableBlockSize  = paramPtr->erasableBlockSize;
    uint32_t erasableBlockCount = paramPtr->erasableBlockCount;
    
    TOMMROC_ASSERT_NOT_NULL(RAMBufferPtr);
    TOMMROC_ASSERT_LESS_THAN(blockIdx, erasableBlockCount);
    
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemSet(RAMBufferPtr + (blockIdx * erasableBlockSize), 0xFF, erasableBlockSize));

    return ((int) TOMMROC_FS_ERR_OK);
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateInRAMFSStart(
                void*                               const   RAMBufferPtr,
        const   uint32_t                                    RAMBufferSize,
        const   uint32_t                                    RAMBufferErasableBlockSize,
        const   tommRoC_guard_t*                    const   guardPtr,
                tommRoC_fs_file_system_t*           const   fsHandlePtr) {

#if defined (__TOMMROC_USE_IN_RAM_FS_TEMPLATE__)

    tommRoC_fs_file_system_config_t fsConfig;

    TOMMROC_ASSERT_NOT_NULL(RAMBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(RAMBufferSize);
    TOMMROC_ASSERT_NOT_ZERO(RAMBufferErasableBlockSize);

    TOMMROC_PARAM_CHECK_ON_NULL_RETURN_ERR(RAMBufferPtr);
    TOMMROC_PARAM_CHECK_ON_ZERO_RETURN_ERR(RAMBufferSize);
    TOMMROC_PARAM_CHECK_ON_ZERO_RETURN_ERR(RAMBufferErasableBlockSize);

    fsConfig.contextPtr         = RAMBufferPtr;
    fsConfig.readCb             = (tommRoC_fs_read_funct_t) _read_block;
    fsConfig.writeCb            = (tommRoC_fs_write_funct_t) _write_block;
    fsConfig.eraseCb            = (tommRoC_fs_erase_funct_t) _erase_block;
    fsConfig.erasableBlockSize  = RAMBufferErasableBlockSize;
    fsConfig.erasableBlockCount = RAMBufferSize / RAMBufferErasableBlockSize;

    return tommRoCFSInit(
            TOMMROC_FS_INIT_FORCE_FORMAT,
            &fsConfig,
            guardPtr,
            fsHandlePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(RAMBufferPtr);
    TOMMROC_UTIL_UNUSED_PARAM(RAMBufferSize);
    TOMMROC_UTIL_UNUSED_PARAM(RAMBufferErasableBlockSize);
    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    TOMMROC_UTIL_UNUSED_PARAM(fsHandlePtr);    

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateInRAMFSClose(
                tommRoC_fs_file_system_t*           const   fsHandlePtr) {

#if defined (__TOMMROC_USE_IN_RAM_FS_TEMPLATE__)

    return tommRoCFSClose(fsHandlePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(fsHandlePtr);

    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;
#endif
}
