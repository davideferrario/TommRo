
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateFileXFS.h"

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)
#include "FileXFS/busy/tommRoCHwTemplateFileXFSBusy.h"
#include "FileXFS/notGuarded/tommRoCHwTemplateFileXFSNotGuarded.h"
#include "FileXFS/openFileDirCounter/tommRoCHwTemplateFileXFSOpenFileDirCounter.h"

#include "TOMMROC.h"
#include "TOMMROCHw.h"
#include "TOMMROCTemplate.h"

#if defined (__TOMMROC_TEMPLATE_ARM_STM32_IS_USED__)
#if !defined (FX_INCLUDE_USER_DEFINE_FILE)
#error "FX_INCLUDE_USER_DEFINE_FILE must be defined"
#endif
#endif

#include "fx_api.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
TOMMROC_SCTA_EQUALS(TOMMROC_HW_TEMPLATE_FILEX_FS_OPEN_FOR_READ,         FX_OPEN_FOR_READ);
TOMMROC_SCTA_EQUALS(TOMMROC_HW_TEMPLATE_FILEX_FS_OPEN_FOR_WRITE,        FX_OPEN_FOR_WRITE);
TOMMROC_SCTA_EQUALS(TOMMROC_HW_TEMPLATE_FILEX_FS_OPEN_FOR_READ_FAST,    FX_OPEN_FOR_READ_FAST);

TOMMROC_SCTA_EQUALS(TOMMROC_HW_TEMPLATE_FILEX_FS_SEEK_BEGIN,            FX_SEEK_BEGIN);
TOMMROC_SCTA_EQUALS(TOMMROC_HW_TEMPLATE_FILEX_FS_SEEK_END,              FX_SEEK_END);
TOMMROC_SCTA_EQUALS(TOMMROC_HW_TEMPLATE_FILEX_FS_SEEK_FORWARD,          FX_SEEK_FORWARD);
TOMMROC_SCTA_EQUALS(TOMMROC_HW_TEMPLATE_FILEX_FS_SEEK_BACK,             FX_SEEK_BACK);

// NOTE: limit file name length to reduce RAM use
TOMMROC_SCTA_EQUALS(FX_MAX_LAST_NAME_LEN, 48);
TOMMROC_SCTA_EQUALS(FX_MAX_LONG_NAME_LEN, 48);
TOMMROC_SCTA_SIZE_OF_EQUALS(tommRoC_hw_template_filex_fs_file_t, FX_FILE);

/*******************************************************************************
 * local vars
 ******************************************************************************/
static tommRoC_guard_t* _guard_ptr = NULL;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_hw_err_enum_t _filex_start(void) {

    tommRoCHwTemplateFileXFSOpenFileDirCounterInit();

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _filex_stop(void) {

    _guard_ptr = NULL;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateFileXFSNotGuardedMediaClose());

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _f_mount(const bool forceFormat) {

    if (!forceFormat) {
        // Try to open (mount) the file system
        if (TOMMRO_C_HW_ERR_SUCCESS == tommRoCHwTemplateFileXFSNotGuardedMediaOpen()) {
            return TOMMRO_C_HW_ERR_SUCCESS;
        }
    }

    // Reformat if we can't mount the filesystem. This should only happen on the first boot
    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateFileXFSNotGuardedMediaFormat(
                    __TOMMROC_HW_USE_FILEX_FS_TEMPLATE_RAW_DISK_SIZE_BYTE__));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateFileXFSNotGuardedMediaOpen());

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _f_format(void) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateFileXFSNotGuardedMediaClose());

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _f_mount(
                    true));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _not_guarded_mount(const tommRoC_hw_template_filex_fs_mount_type_enum_t mountType) {

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFileXFSBusySet(),
            tommRoCHwTemplateFileXFSBusyReset(),
            _f_mount(
                    (TOMMROC_HW_TEMPLATE_FILEX_FS_MOUNT_FORCE_FORMAT == mountType)));
}

static tommRoC_hw_err_enum_t _not_guarded_open(
        const   char*                                   const   pathStrPtr,
        const   uint32_t                                        openType,
        const   bool                                            createIfNotExist,
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr) {

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFileXFSBusySet(),
            tommRoCHwTemplateFileXFSBusyReset(),
            tommRoCHwTemplateFileXFSNotGuardedFOpen(
                    (FX_FILE*) filePtr,
                    pathStrPtr,
                    openType,
                    createIfNotExist));
}

static tommRoC_hw_err_enum_t _not_guarded_close(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr) {

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFileXFSBusySet(),
            tommRoCHwTemplateFileXFSBusyReset(),
            tommRoCHwTemplateFileXFSNotGuardedFClose(
                    (FX_FILE*) filePtr));
}

static tommRoC_hw_err_enum_t _not_guarded_read(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr,
                void*                                   const   readBufferPtr,
        const   uint32_t                                        toReadAmount,
                uint32_t*                               const   readedAmountPtr) {

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFileXFSBusySet(),
            tommRoCHwTemplateFileXFSBusyReset(),
            tommRoCHwTemplateFileXFSNotGuardedFRead(
                    (FX_FILE*) filePtr,
                    readBufferPtr,
                    toReadAmount,
                    readedAmountPtr));
}

static tommRoC_hw_err_enum_t _not_guarded_write(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr,
        const   void*                                   const   writeBufferPtr,
        const   uint32_t                                        writeBufferLen,
                uint32_t*                               const   writtenAmountPtr) {

    *writtenAmountPtr = writeBufferLen;

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFileXFSBusySet(),
            tommRoCHwTemplateFileXFSBusyReset(),
            tommRoCHwTemplateFileXFSNotGuardedFWrite(
                    (FX_FILE*) filePtr,
                    writeBufferPtr,
                    writeBufferLen));
}

static tommRoC_hw_err_enum_t _not_guarded_seek(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr,
        const   uint32_t                                        offsetByte,
        const   uint32_t                                        whence) {

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFileXFSBusySet(),
            tommRoCHwTemplateFileXFSBusyReset(),
            tommRoCHwTemplateFileXFSNotGuardedFRelativeSeek(
                    (FX_FILE*) filePtr,
                    offsetByte,
                    whence));
}

static tommRoC_hw_err_enum_t _not_guarded_delete(
        const   char*                                   const   pathStrPtr) {

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFileXFSBusySet(),
            tommRoCHwTemplateFileXFSBusyReset(),
            tommRoCHwTemplateFileXFSNotGuardedFDelete(
                    pathStrPtr));
}

static tommRoC_hw_err_enum_t _not_guarded_rename(
        const   char*                                   const   pathOldStrPtr,
        const   char*                                   const   pathNewStrPtr) {

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFileXFSBusySet(),
            tommRoCHwTemplateFileXFSBusyReset(),
            tommRoCHwTemplateFileXFSNotGuardedFRename(
                    pathOldStrPtr,
                    pathNewStrPtr));
}

static tommRoC_hw_err_enum_t _not_guarded_truncate(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr,
        const   uint32_t                                        sizeByte) {

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFileXFSBusySet(),
            tommRoCHwTemplateFileXFSBusyReset(),
            tommRoCHwTemplateFileXFSNotGuardedFTruncate(
                    (FX_FILE*) filePtr,
                    sizeByte));
}

static uint32_t _not_guarded_size(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr) {

    TOMMROC_UTIL_BLOCK_CODE_WITH_RESULT_FUNCT(
            uint32_t,
            tommRoCHwTemplateFileXFSBusySet(),
            tommRoCHwTemplateFileXFSBusyReset(),
            tommRoCHwTemplateFileXFSNotGuardedFSize(
                    (FX_FILE*) filePtr));
}

static tommRoC_hw_err_enum_t _not_guarded_exists(
        const   char*                                   const   pathStrPtr,
                bool*                                   const   fileExistsPtr) {

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFileXFSBusySet(),
            tommRoCHwTemplateFileXFSBusyReset(),
            tommRoCHwTemplateFileXFSNotGuardedFExists(
                    pathStrPtr,
                    fileExistsPtr));
}

static tommRoC_hw_err_enum_t _not_guarded_format(void) {

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFileXFSBusySet(),
            tommRoCHwTemplateFileXFSBusyReset(),
            _f_format());
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSStart(void) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFileXFSBusySet(),
            tommRoCHwTemplateFileXFSBusyReset(),
            _filex_start());
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSStop(void) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFileXFSBusySet(),
            tommRoCHwTemplateFileXFSBusyReset(),
            _filex_stop());
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSSetGuard(const tommRoC_guard_t* const guardPtr) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    if (NULL != guardPtr) {
        TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCGuardCheck(guardPtr), TOMMRO_C_HW_PARAM_ERR);
    }

    _guard_ptr = (tommRoC_guard_t*) guardPtr;

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSMount(const tommRoC_hw_template_filex_fs_mount_type_enum_t mountType) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            _not_guarded_mount(
                    mountType));
#else
    TOMMROC_UTIL_UNUSED_PARAM(mountType);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

bool tommRoCHwTemplateFileXFSGetIsBusy(void) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)
    return tommRoCHwTemplateFileXFSBusyIs();
#else
    return false;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFOpen(
        const   char*                                   const   pathStrPtr,
        const   uint32_t                                        openType,
        const   bool                                            createIfNotExist,
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(pathStrPtr);
    TOMMROC_ASSERT_NOT_NULL(filePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(pathStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(filePtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            _not_guarded_open(
                    pathStrPtr,
                    openType,
                    createIfNotExist,
                    filePtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(pathStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(openType);
    TOMMROC_UTIL_UNUSED_PARAM(createIfNotExist);
    TOMMROC_UTIL_UNUSED_PARAM(filePtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFClose(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(filePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(filePtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            _not_guarded_close(
                    filePtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(filePtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFRead(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr,
                void*                                   const   readBufferPtr,
        const   uint32_t                                        toReadAmount,
                uint32_t*                               const   readedAmountPtr) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(filePtr);
    TOMMROC_ASSERT_NOT_NULL(readBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(toReadAmount);
    TOMMROC_ASSERT_NOT_NULL(readedAmountPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(filePtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(readBufferPtr);
    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(toReadAmount);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(readedAmountPtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            _not_guarded_read(
                    filePtr,
                    readBufferPtr,
                    toReadAmount,
                    readedAmountPtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(filePtr);
    TOMMROC_UTIL_UNUSED_PARAM(readBufferPtr);
    TOMMROC_UTIL_UNUSED_PARAM(toReadAmount);
    TOMMROC_UTIL_UNUSED_PARAM(readedAmountPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFWrite(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr,
        const   void*                                   const   writeBufferPtr,
        const   uint32_t                                        writeBufferLen,
                uint32_t*                               const   writtenAmountPtr) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(filePtr);
    TOMMROC_ASSERT_NOT_NULL(writeBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(writeBufferLen);
    TOMMROC_ASSERT_NOT_NULL(writtenAmountPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(filePtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(writeBufferPtr);
    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(writeBufferLen);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(writtenAmountPtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            _not_guarded_write(
                    filePtr,
                    writeBufferPtr,
                    writeBufferLen,
                    writtenAmountPtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(filePtr);
    TOMMROC_UTIL_UNUSED_PARAM(writeBufferPtr);
    TOMMROC_UTIL_UNUSED_PARAM(writeBufferLen);
    TOMMROC_UTIL_UNUSED_PARAM(writtenAmountPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFReadRP(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr,
                void*                                   const   readBufferPtr,
        const   uint32_t                                        toReadAmount) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    uint32_t readedAmount;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateFileXFSFRead(
                    filePtr,
                    readBufferPtr,
                    toReadAmount,
                    &readedAmount));

    TOMMROC_ASSERT_EQUALS(readedAmount, toReadAmount);

    if (toReadAmount != readedAmount) {
        return TOMMRO_C_HW_GENERIC_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(filePtr);
    TOMMROC_UTIL_UNUSED_PARAM(readBufferPtr);
    TOMMROC_UTIL_UNUSED_PARAM(toReadAmount);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFWriteRP(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr,
        const   void*                                   const   writeBufferPtr,
        const   uint32_t                                        writeBufferLen) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    uint32_t writtenAmount;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateFileXFSFWrite(
                    filePtr,
                    writeBufferPtr,
                    writeBufferLen,
                    &writtenAmount));

    TOMMROC_ASSERT_EQUALS(writtenAmount, writeBufferLen);

    if (writeBufferLen != writtenAmount) {
        return TOMMRO_C_HW_GENERIC_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(filePtr);
    TOMMROC_UTIL_UNUSED_PARAM(writeBufferPtr);
    TOMMROC_UTIL_UNUSED_PARAM(writeBufferLen);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFSeek(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr,
        const   uint32_t                                        offsetByte,
        const   uint32_t                                        whence) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(filePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(filePtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            _not_guarded_seek(
                    filePtr,
                    offsetByte,
                    whence));
#else
    TOMMROC_UTIL_UNUSED_PARAM(filePtr);
    TOMMROC_UTIL_UNUSED_PARAM(offsetByte);
    TOMMROC_UTIL_UNUSED_PARAM(whence);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFDelete(
        const   char*                                   const   pathStrPtr) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(pathStrPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(pathStrPtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            _not_guarded_delete(
                    pathStrPtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(pathStrPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFRename(
        const   char*                                   const   pathOldStrPtr,
        const   char*                                   const   pathNewStrPtr) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(pathOldStrPtr);
    TOMMROC_ASSERT_NOT_NULL(pathNewStrPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(pathOldStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(pathNewStrPtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            _not_guarded_rename(
                    pathOldStrPtr,
                    pathNewStrPtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(pathOldStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(pathNewStrPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFTruncate(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr,
        const   uint32_t                                        sizeByte) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(filePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(filePtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            _not_guarded_truncate(
                    filePtr,
                    sizeByte));
#else
    TOMMROC_UTIL_UNUSED_PARAM(filePtr);
    TOMMROC_UTIL_UNUSED_PARAM(sizeByte);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

uint32_t tommRoCHwTemplateFileXFSFSize(
                tommRoC_hw_template_filex_fs_file_t*    const   filePtr) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(filePtr);

    if (NULL == filePtr) {
        return 0;
    }

    TOMMROC_GUARD_SYNCHRO_WITH_RESULT_FUNCT(
            uint32_t,
            _guard_ptr,
            UINT32_MAX,
            _not_guarded_size(
                    filePtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(filePtr);
    return 0;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFExists(
        const   char*                                   const   pathStrPtr,
                bool*                                   const   fileExistsPtr) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(pathStrPtr);
    TOMMROC_ASSERT_NOT_NULL(fileExistsPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(pathStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(fileExistsPtr);

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            _not_guarded_exists(
                    pathStrPtr,
                    fileExistsPtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(pathStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(fileExistsPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSFormat(void) {

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            _not_guarded_format());
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

#endif
