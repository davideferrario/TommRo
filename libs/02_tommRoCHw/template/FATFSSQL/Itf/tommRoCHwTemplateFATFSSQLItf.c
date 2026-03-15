
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateFATFSSQLItf.h"

#include "tommRoCHwTemplateFATFS.h"

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

tommRoC_err_enum_t tommRoCHwTemplateFATFSSQLItfOpenFile(
                void*                           const   fileSystemHandlePtr,
        const   char*                           const   filePathStrPtr,
        const   uint32_t                                flags,
                void*                           const   fileHandlePtr) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);



    TOMMROC_UTIL_UNUSED_PARAM(filePathStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(flags);
    TOMMROC_UTIL_UNUSED_PARAM(fileHandlePtr);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;




}

tommRoC_err_enum_t tommRoCHwTemplateFATFSSQLItfCloseFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);



    TOMMROC_UTIL_UNUSED_PARAM(fileHandlePtr);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;




}

tommRoC_err_enum_t tommRoCHwTemplateFATFSSQLItfSyncFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);



    TOMMROC_UTIL_UNUSED_PARAM(fileHandlePtr);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;




}

tommRoC_err_enum_t tommRoCHwTemplateFATFSSQLItfTruncateFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr,
        const   uint32_t                                size) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);



    TOMMROC_UTIL_UNUSED_PARAM(fileHandlePtr);
    TOMMROC_UTIL_UNUSED_PARAM(size);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;




}

tommRoC_err_enum_t tommRoCHwTemplateFATFSSQLItfSeekFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr,
        const   int32_t                                 offset,
        const   tommRoC_fs_itf_def_seek_whence_enum_t   whence) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);



    TOMMROC_UTIL_UNUSED_PARAM(fileHandlePtr);
    TOMMROC_UTIL_UNUSED_PARAM(offset);
    TOMMROC_UTIL_UNUSED_PARAM(whence);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;




}

tommRoC_err_enum_t tommRoCHwTemplateFATFSSQLItfReadFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr,
                void*                           const   readBufferPtr,
        const   uint32_t                                toReadAmount,
                uint32_t*                       const   readedAmountPtr) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);



    TOMMROC_UTIL_UNUSED_PARAM(fileHandlePtr);
    TOMMROC_UTIL_UNUSED_PARAM(readBufferPtr);
    TOMMROC_UTIL_UNUSED_PARAM(toReadAmount);
    TOMMROC_UTIL_UNUSED_PARAM(readedAmountPtr);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;




}

tommRoC_err_enum_t tommRoCHwTemplateFATFSSQLItfWriteFile(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr,
        const   void*                           const   writeBufferPtr,
        const   uint32_t                                writeBufferLen,
                uint32_t*                       const   writtenAmountPtr) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);



    TOMMROC_UTIL_UNUSED_PARAM(fileHandlePtr);
    TOMMROC_UTIL_UNUSED_PARAM(writeBufferPtr);
    TOMMROC_UTIL_UNUSED_PARAM(writeBufferLen);
    TOMMROC_UTIL_UNUSED_PARAM(writtenAmountPtr);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;




}

tommRoC_err_enum_t tommRoCHwTemplateFATFSSQLItfDeleteFile(
                void*                           const   fileSystemHandlePtr,
        const   char*                           const   filePathStrPtr) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);



    TOMMROC_UTIL_UNUSED_PARAM(filePathStrPtr);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;




}

tommRoC_err_enum_t tommRoCHwTemplateFATFSSQLItfFileExists(
                void*                           const   fileSystemHandlePtr,
        const   char*                           const   filePathStrPtr,
                bool*                           const   fileExistsPtr) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);



    TOMMROC_UTIL_UNUSED_PARAM(filePathStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(fileExistsPtr);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;




}

uint32_t tommRoCHwTemplateFATFSSQLItfFileSize(
                void*                           const   fileSystemHandlePtr,
                void*                           const   fileHandlePtr) {

    TOMMROC_ASSERT_NULL(fileSystemHandlePtr);



    TOMMROC_UTIL_UNUSED_PARAM(fileHandlePtr);
    return TOMMRO_C_ENVIRONMENT_NOT_INIT_ERR;




}
