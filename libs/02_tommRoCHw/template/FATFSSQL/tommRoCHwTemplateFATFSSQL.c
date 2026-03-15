
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateFATFSSQL.h"

#include "FATFSSQL/Itf/tommRoCHwTemplateFATFSSQLItf.h"

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

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSSQLInit(
        const   tommRoC_guard_t*    const   guardPtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    // NOTE: use always a config init as EMPTY_VARIABLE to avoid problems with new functionalities in the future.
    tommRoC_fs_itf_def_file_system_config_t SQLFSConfig = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_fs_itf_def_file_system_config_t);

    SQLFSConfig.fileSystemHandlePtr = NULL;
    SQLFSConfig.openFile            = tommRoCHwTemplateFATFSSQLItfOpenFile;
    SQLFSConfig.closeFile           = tommRoCHwTemplateFATFSSQLItfCloseFile;
    SQLFSConfig.syncFile            = tommRoCHwTemplateFATFSSQLItfSyncFile;
    SQLFSConfig.truncateFile        = tommRoCHwTemplateFATFSSQLItfTruncateFile;
    SQLFSConfig.seekFile            = tommRoCHwTemplateFATFSSQLItfSeekFile;
    SQLFSConfig.readFile            = tommRoCHwTemplateFATFSSQLItfReadFile;
    SQLFSConfig.writeFile           = tommRoCHwTemplateFATFSSQLItfWriteFile;
    SQLFSConfig.deleteFile          = tommRoCHwTemplateFATFSSQLItfDeleteFile;
    SQLFSConfig.fileExists          = tommRoCHwTemplateFATFSSQLItfFileExists;
    SQLFSConfig.fileSize            = tommRoCHwTemplateFATFSSQLItfFileSize;

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCSQLInit(
                    sizeof(tommRoC_hw_template_fat_fs_file_t),
                    &SQLFSConfig,
                    guardPtr),
            TOMMRO_C_HW_LOW_LEVEL_ERR);

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSSQLClose(void) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCSQLClose(),
            TOMMRO_C_HW_LOW_LEVEL_ERR);

    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}
