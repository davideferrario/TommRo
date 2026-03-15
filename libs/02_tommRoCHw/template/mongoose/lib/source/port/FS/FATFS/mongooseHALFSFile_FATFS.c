
#if defined (__TOMMROC_HW_USE_MONGOOSE_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_MONGOOSE_FAT_FS_FILE_TEMPLATE__)
#include "mongoose/lib/source/port/FS/mongooseHALFSFile.h"

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

char* mongooseHALFSFileRead(const char *path, size_t *sizep) {

    tommRoC_hw_template_fat_fs_file_t file;
    uint32_t size;

    char* data = NULL;

    uint32_t readed;

    if (TOMMRO_C_HW_ERR_SUCCESS != tommRoCHwTemplateFATFSFOpen(path, TOMMROC_HW_TEMPLATE_FAT_FS_FA_READ, &file)) {
        return NULL;
    }

    size = tommRoCHwTemplateFATFSFSize(&file);

    data = (char*) calloc(1, size + 1);

    if (NULL == data) {
        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateFATFSFClose(&file));
        return NULL;
    }

    if (TOMMRO_C_HW_ERR_SUCCESS != tommRoCHwTemplateFATFSFRead(&file, data, size, &readed)) {
        free(data);
        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateFATFSFClose(&file));
        return NULL;
    }

    if (size != readed) {
        free(data);
        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateFATFSFClose(&file));
        return NULL;
    }

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateFATFSFClose(&file));

    data[size] = TOMMROC_STRING_NULL_TERMINATOR_CHAR;

    if (sizep != NULL) {
        *sizep = (size_t) size;
    }

    return data;
}

bool mongooseHALFSFileWrite(const char *path, const void *buf, size_t len) {

    char rndStr[TOMMROC_STRING_U32_DEC_AS_STRING_MAX_ARRAY_SIZE_BYTE];
    char tmpFileNameStr[TOMMROC_UTIL_STRING_ARR_LENGTH("__tmp__") + TOMMROC_STRING_U32_DEC_AS_STRING_MAX_LENGTH_BYTE + TOMMROC_UTIL_STRING_ARR_LENGTH("__tmp__") + TOMMROC_UTIL_STRING_ARR_LENGTH(".tmp") + TOMMROC_STRING_NULL_TERMINATOR_CHAR_SIZE];

    uint32_t rnd;

    bool fileExists;

    tommRoC_hw_template_fat_fs_file_t file;

    uint32_t written;

    void* ptr;
    uint16_t bSize;

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilPrngInit());

    rnd = tommRoCUtilU32Prng();

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(TOMMROC_STRING_U32_ARRAY_TO_STRING(&rnd, 1, sizeof(rndStr), rndStr));

    ptr     = tmpFileNameStr;
    bSize   = sizeof(tmpFileNameStr);
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilBufferAppendString(ptr, bSize, "__tmp__", &ptr, &bSize));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilBufferAppendString(ptr, bSize, rndStr, &ptr, &bSize));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilBufferAppendString(ptr, bSize, "__tmp__", &ptr, &bSize));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilBufferAppendString(ptr, bSize, ".tmp", &ptr, &bSize));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilBufferAppendU8(ptr, bSize, TOMMROC_STRING_NULL_TERMINATOR_CHAR, &ptr, &bSize));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateFATFSFExists(tmpFileNameStr, &fileExists));
    if (fileExists) {
        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateFATFSFDelete(tmpFileNameStr));
    }

    if (TOMMRO_C_HW_ERR_SUCCESS != tommRoCHwTemplateFATFSFOpen(tmpFileNameStr, TOMMROC_HW_TEMPLATE_FAT_FS_FA_CREATE_NEW | TOMMROC_HW_TEMPLATE_FAT_FS_FA_WRITE, &file)) {
        return false;
    }

    if (TOMMRO_C_HW_ERR_SUCCESS != tommRoCHwTemplateFATFSFWrite(&file, buf, len, &written)) {
        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateFATFSFClose(&file));
        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateFATFSFDelete(tmpFileNameStr));
        return false;
    }

    if (len != written) {
        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateFATFSFClose(&file));
        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateFATFSFDelete(tmpFileNameStr));
        return false;
    }

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateFATFSFClose(&file));

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateFATFSFExists(path, &fileExists));
    if (fileExists) {
        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateFATFSFDelete(path));
    }

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwTemplateFATFSFRename(tmpFileNameStr, path));

    return true;
}

#endif

#endif
