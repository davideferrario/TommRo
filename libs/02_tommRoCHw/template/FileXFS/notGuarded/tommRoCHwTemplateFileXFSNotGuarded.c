
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateFileXFSNotGuarded.h"

#if defined (__TOMMROC_HW_USE_FILEX_FS_TEMPLATE__)
#include "FileXFS/openFileDirCounter/tommRoCHwTemplateFileXFSOpenFileDirCounter.h"

#include "app_filex.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#if defined (FX_STM32_MMC_DEFAULT_SECTOR_SIZE)
#define __FX_DEFAULT_SECTOR_SIZE__      (FX_STM32_MMC_DEFAULT_SECTOR_SIZE)
#define __FX_MEDIA_DRIVER__             fx_stm32_mmc_driver
#elif defined (LX_STM32_DEFAULT_SECTOR_SIZE)
#define __FX_DEFAULT_SECTOR_SIZE__      (LX_STM32_DEFAULT_SECTOR_SIZE)
#define __FX_MEDIA_DRIVER__             fx_stm32_levelx_nor_driver
#else
#error "FX configuration error"
#endif

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static const CHAR _media_name_str[] = "FXFS";

// Buffer for FileX FX_MEDIA sector cache.
ALIGN_32BYTES (uint32_t _fx_media_memory[__FX_DEFAULT_SECTOR_SIZE__ / sizeof(uint32_t)]);
//FileX global data structures.
static FX_MEDIA _fx_disk;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static bool _file_exists(const char* const path) {

    UINT attributes;

    return (FX_SUCCESS == fx_file_attributes_read(&_fx_disk, (CHAR*) path, &attributes));
}

static ULONG64 _file_size(FX_FILE* filePtr) {
    return filePtr->fx_file_current_file_size;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedMediaOpen(void) {

    if (FX_SUCCESS != fx_media_open(&_fx_disk, (CHAR*) _media_name_str, __FX_MEDIA_DRIVER__, (VOID*) FX_NULL, (VOID*) _fx_media_memory, sizeof(_fx_media_memory))) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedMediaClose(void) {

    if (FX_SUCCESS != fx_media_flush(&_fx_disk)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (FX_SUCCESS != fx_media_close(&_fx_disk)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedMediaFormat(const uint64_t rawDiskSize) {

    UINT res;

    res = fx_media_format(
            &_fx_disk,                                                                  // nor_ospi_flash_disk pointer
            __FX_MEDIA_DRIVER__,                                                        // Driver entry
            (VOID*) NULL,                                                               // Device info pointer
            (UCHAR*) _fx_media_memory,                                                  // Media buffer pointer
            sizeof(_fx_media_memory),                                                   // Media buffer size
            (CHAR*) _media_name_str,                                                    // Volume Name
            1,                                                                          // Number of FATs
            32,                                                                         // Directory Entries
            0,                                                                          // Hidden sectors
            (rawDiskSize - __FX_DEFAULT_SECTOR_SIZE__) / (__FX_DEFAULT_SECTOR_SIZE__),  // Total sectors
            __FX_DEFAULT_SECTOR_SIZE__,                                                 // Sector size
            8,                                                                          // Sectors per cluster
            1,                                                                          // Heads
            1);                                                                         // Sectors per track

    if (FX_SUCCESS != res) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFOpen(FX_FILE* filePtr, const char* const path, const uint32_t openType, const bool createIfNotExist) {

    bool fileCreated;

    TOMMROC_ASSERT_LESS_THAN(tommRoCHwTemplateFileXFSOpenFileDirCounterGet(), UINT8_MAX);

    if (tommRoCHwTemplateFileXFSOpenFileDirCounterGet() >= UINT8_MAX) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }

    fileCreated = false;

    if (!_file_exists(path)) {

        if (!createIfNotExist) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        if (FX_SUCCESS != fx_file_create(&_fx_disk, (CHAR*) path)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        if (FX_SUCCESS != fx_media_flush(&_fx_disk)) {
            return TOMMRO_C_HW_LOW_LEVEL_ERR;
        }

        fileCreated = true;
    }

    if (FX_SUCCESS != fx_file_open(&_fx_disk, filePtr, (CHAR*) path, openType)) {
        if (fileCreated) {
            TOMMROC_ASSERT_FUNCT_RESULT_EQUALS(fx_file_delete(&_fx_disk, (CHAR*) path), FX_SUCCESS);
        }
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    tommRoCHwTemplateFileXFSOpenFileDirCounterInc();
    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFileXFSOpenFileDirCounterGet());

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFClose(FX_FILE* filePtr) {

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFileXFSOpenFileDirCounterGet());

    if (FX_SUCCESS != fx_file_close(filePtr)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    tommRoCHwTemplateFileXFSOpenFileDirCounterDec();
    TOMMROC_ASSERT_NOT_EQUALS(tommRoCHwTemplateFileXFSOpenFileDirCounterGet(), UINT8_MAX);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFRead(FX_FILE* filePtr, void* const bufferPtr, const uint32_t readSize, uint32_t* const readedAmountPtr) {

    ULONG actualSize;

    UINT res;

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFileXFSOpenFileDirCounterGet());

    res = fx_file_read(filePtr, bufferPtr, readSize, &actualSize);

    // NOTE: FX_END_OF_FILE is the return in case of the file is at the end. Then no more data available to read
    if (FX_END_OF_FILE == res) {
        TOMMROC_ASSERT_ZERO(actualSize);
        *readedAmountPtr = (uint32_t) 0;
        return TOMMRO_C_HW_ERR_SUCCESS;
    }

    if (FX_SUCCESS != res) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    *readedAmountPtr = (uint32_t) actualSize;

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFileXFSOpenFileDirCounterGet());

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFWrite(FX_FILE* filePtr, const void* const bufferPtr, const uint32_t writeSize) {

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFileXFSOpenFileDirCounterGet());

    if (FX_SUCCESS != fx_file_write(filePtr, (VOID*) bufferPtr, writeSize)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (FX_SUCCESS != fx_media_flush(&_fx_disk)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFileXFSOpenFileDirCounterGet());

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFRelativeSeek(FX_FILE* filePtr, const uint32_t offset, const uint32_t seekFrom) {

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFileXFSOpenFileDirCounterGet());

    if (FX_SUCCESS != fx_file_relative_seek(filePtr, offset, seekFrom)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFileXFSOpenFileDirCounterGet());

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFDelete(const char* const path) {

    if (FX_SUCCESS != fx_file_delete(&_fx_disk, (CHAR*) path)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (FX_SUCCESS != fx_media_flush(&_fx_disk)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFRename(const char* const pathOld, const char* const pathNew) {

    if (FX_SUCCESS != fx_file_rename(&_fx_disk, (CHAR*) pathOld, (CHAR*) pathNew)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (FX_SUCCESS != fx_media_flush(&_fx_disk)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFTruncate(FX_FILE* filePtr, const uint32_t size) {

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFileXFSOpenFileDirCounterGet());

    if (FX_SUCCESS != fx_file_truncate_release(filePtr, size)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    if (FX_SUCCESS != fx_media_flush(&_fx_disk)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFileXFSOpenFileDirCounterGet());

    return TOMMRO_C_HW_ERR_SUCCESS;
}

uint32_t tommRoCHwTemplateFileXFSNotGuardedFSize(FX_FILE* filePtr) {

    uint32_t size;

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFileXFSOpenFileDirCounterGet());

    size = (uint32_t) _file_size(filePtr);

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFileXFSOpenFileDirCounterGet());

    return size;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFileXFSNotGuardedFExists(const char* const path, bool* const fileExistsPtr) {

    *fileExistsPtr = _file_exists(path);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif
