
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateFileXFSSQLItf.h"

#include "tommRoCHwTemplateFileXFS.h"

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
static uint32_t _sql_open_flags_To_filex_open_type(const uint32_t flagsU32) {
    return ((TOMMROC_FS_ITF_DEF_OPEN_FLAG_READONLY == (flagsU32 & TOMMROC_FS_ITF_DEF_OPEN_FLAG_READONLY)) ? (TOMMROC_HW_TEMPLATE_FILEX_FS_OPEN_FOR_READ) : (TOMMROC_HW_TEMPLATE_FILEX_FS_OPEN_FOR_WRITE));
}

static bool _sql_open_flags_To_filex_create_if_not_exist(const uint32_t flagsU32) {
    return (TOMMROC_FS_ITF_DEF_OPEN_FLAG_CREATE == (flagsU32 & TOMMROC_FS_ITF_DEF_OPEN_FLAG_CREATE));
}

static uint32_t _fs_itf_def_seek_whence_To_filex_seek_whence(const tommRoC_fs_itf_def_seek_whence_enum_t SQLWhence) {

    do { // Added to avoid "warning: unreachable code"
        switch (SQLWhence) {

        case TOMMROC_FS_ITF_DEF_SEEK_FILE_SET:  return TOMMROC_HW_TEMPLATE_FILEX_FS_SEEK_BEGIN;
        case TOMMROC_FS_ITF_DEF_SEEK_FILE_CUR:  return TOMMROC_HW_TEMPLATE_FILEX_FS_SEEK_FORWARD;
        case TOMMROC_FS_ITF_DEF_SEEK_FILE_END:  return TOMMROC_HW_TEMPLATE_FILEX_FS_SEEK_END;

        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            break;
        }
    } while (0);

    return TOMMROC_HW_TEMPLATE_FILEX_FS_SEEK_BEGIN;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfOpenFile(
                void*                           const   fileSystemHandlePtr,
        const   char*                           const   filePathStrPtr,
        const   uint32_t                                flags,
                void*                           const   fileHandlePtr) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCHwTemplateFileXFSFOpen(
                    filePathStrPtr,
                    _sql_open_flags_To_filex_open_type(flags),
                    _sql_open_flags_To_filex_create_if_not_exist(flags),
                    (tommRoC_hw_template_filex_fs_file_t*) fileHandlePtr),
            TOMMRO_C_LOW_LEVEL_ERR);

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfCloseFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCHwTemplateFileXFSFClose(
                    (tommRoC_hw_template_filex_fs_file_t*) fileHandlePtr),
            TOMMRO_C_LOW_LEVEL_ERR);

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfSyncFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);

    TOMMROC_UTIL_UNUSED_PARAM(fileHandlePtr);

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfTruncateFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr,
        const   uint32_t                                size) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCHwTemplateFileXFSFTruncate(
                    (tommRoC_hw_template_filex_fs_file_t*) fileHandlePtr,
                    size),
            TOMMRO_C_LOW_LEVEL_ERR);

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfSeekFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr,
        const   int32_t                                 offset,
        const   tommRoC_fs_itf_def_seek_whence_enum_t   whence) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCHwTemplateFileXFSFSeek(
                    (tommRoC_hw_template_filex_fs_file_t*) fileHandlePtr,
                    (uint32_t) offset,
                    _fs_itf_def_seek_whence_To_filex_seek_whence(whence)),
            TOMMRO_C_LOW_LEVEL_ERR);

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfReadFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr,
                void*                           const   readBufferPtr,
        const   uint32_t                                toReadAmount,
                uint32_t*                       const   readedAmountPtr) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCHwTemplateFileXFSFRead(
                    (tommRoC_hw_template_filex_fs_file_t*) fileHandlePtr,
                    readBufferPtr,
                    toReadAmount,
                    readedAmountPtr),
            TOMMRO_C_LOW_LEVEL_ERR);

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfWriteFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr,
        const   void*                           const   writeBufferPtr,
        const   uint32_t                                writeBufferLen,
                uint32_t*                       const   writtenAmountPtr) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCHwTemplateFileXFSFWrite(
                    (tommRoC_hw_template_filex_fs_file_t*) fileHandlePtr,
                    writeBufferPtr,
                    writeBufferLen,
                    writtenAmountPtr),
            TOMMRO_C_LOW_LEVEL_ERR);

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfDeleteFile(
                void*                           const   fileSystemHandlePtr,
        const   char*                           const   filePathStrPtr) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCHwTemplateFileXFSFDelete(
                    filePathStrPtr),
            TOMMRO_C_LOW_LEVEL_ERR);

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCHwTemplateFileXFSSQLItfFileExists(
                void*                           const   fileSystemHandlePtr,
        const   char*                           const   filePathStrPtr,
                bool*                           const   fileExistsPtr) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCHwTemplateFileXFSFExists(
                    filePathStrPtr,
                    fileExistsPtr),
            TOMMRO_C_LOW_LEVEL_ERR);

    return TOMMRO_C_ERR_SUCCESS;
}

uint32_t tommRoCHwTemplateFileXFSSQLItfFileSize(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);

    return tommRoCHwTemplateFileXFSFSize(
            (tommRoC_hw_template_filex_fs_file_t*) fileHandlePtr);
}
