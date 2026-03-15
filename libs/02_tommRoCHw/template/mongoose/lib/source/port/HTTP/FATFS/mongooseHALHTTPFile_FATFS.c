
#if defined (__TOMMROC_HW_USE_MONGOOSE_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_MONGOOSE_FAT_FS_FILE_TEMPLATE__)
#include "mongoose/lib/source/port/HTTP/mongooseHALHTTPFile.h"

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

int mongooseHALHTTPFileUpload(
        const   char*       const   pathStrPtr,
        const   uint32_t            offset,
        const   void*       const   dataBufferPtr,
        const   uint32_t            dataBufferLen,
        const   bool                isFirstChunk,
        const   bool                isEmptyLastChunk) {

    tommRoC_hw_template_fat_fs_file_t file;

    uint8_t fileOpenMode;

    uint32_t writtenAmount;

    fileOpenMode = ((0 == offset) ? (TOMMROC_HW_TEMPLATE_FAT_FS_FA_CREATE_NEW | TOMMROC_HW_TEMPLATE_FAT_FS_FA_WRITE) : (TOMMROC_HW_TEMPLATE_FAT_FS_FA_OPEN_APPEND));

    if (TOMMRO_C_HW_ERR_SUCCESS != tommRoCHwTemplateFATFSFOpen(pathStrPtr, fileOpenMode, &file)) {
        return -1;
    }

    if (0 != offset) {
        if (TOMMRO_C_HW_ERR_SUCCESS != tommRoCHwTemplateFATFSFLSeek(&file, offset)) {
            tommRoCHwTemplateFATFSFClose(&file);
            return -1;
        }
    }

    if (TOMMRO_C_HW_ERR_SUCCESS != tommRoCHwTemplateFATFSFWrite(&file, dataBufferPtr, dataBufferLen, &writtenAmount)) {
        tommRoCHwTemplateFATFSFClose(&file);
        return -1;
    }

    if (TOMMRO_C_HW_ERR_SUCCESS != tommRoCHwTemplateFATFSFClose(&file)) {
        return -1;
    }

    return writtenAmount;
}

#endif

#endif
