
#if defined (__TOMMROC_HW_USE_MONGOOSE_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_MONGOOSE_TOMMROC_FS_MBED_FILE_TEMPLATE__)
#include "mongoose/lib/source/port/FS/mongooseHALFSFile.h"

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

    tommRoC_fs_file_t file;
    uint32_t size;

    char* data = NULL;

    if (!tommRoCFSMbedIsEnabled()) {
        TOMMROC_DEBUG_E("FSMbed MUST be enabled");
        return NULL;
    }

    if (TOMMRO_C_ERR_SUCCESS != tommRoCFSMbedFileOpen(path, TOMMROC_FS_OPEN_FILE_FOR_READ, &file)) {
        return NULL;
    }

    size = tommRoCFSMbedFileSize(&file);

    data = (char*) calloc(1, size + 1);

    if (NULL == data) {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFSMbedFileClose(&file));
        return NULL;
    }

    if (TOMMRO_C_ERR_SUCCESS != tommRoCFSMbedFileRead(&file, data, size)) {
        free(data);
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFSMbedFileClose(&file));
        return NULL;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFSMbedFileClose(&file));

    data[size] = TOMMROC_STRING_NULL_TERMINATOR_CHAR;

    if (sizep != NULL) {
        *sizep = (size_t) size;
    }

    return data;
}

bool mongooseHALFSFileWrite(const char *path, const void *buf, size_t len) {

    /**
     * NOTE:
     * don't use random name/rename because rename function is slow in FSMbed.
     */

    bool fileExists;

    tommRoC_fs_file_t file;

    if (!tommRoCFSMbedIsEnabled()) {
        TOMMROC_DEBUG_E("FSMbed MUST be enabled");
        return NULL;
    }

    if (TOMMRO_C_ERR_SUCCESS != tommRoCFSMbedFileExists(path, &fileExists)) {
        TOMMROC_DEBUG_E("FSMbedFileExists error");
        return NULL;
    }

    if (fileExists) {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFSMbedRemove(path));
    }

    if (TOMMRO_C_ERR_SUCCESS != tommRoCFSMbedFileOpen(path, TOMMROC_FS_OPEN_FILE_FOR_WRITE, &file)) {
        return NULL;
    }

    if (TOMMRO_C_ERR_SUCCESS != tommRoCFSMbedFileWrite(&file, buf, len)) {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFSMbedFileClose(&file));
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFSMbedRemove(path));
        return false;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCFSMbedFileClose(&file));

    return true;
}

#endif

#endif
