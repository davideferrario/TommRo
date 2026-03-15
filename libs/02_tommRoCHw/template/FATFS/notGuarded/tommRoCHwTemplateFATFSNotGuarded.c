
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateFATFSNotGuarded.h"

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)
#include "FATFS/openFileDirCounter/tommRoCHwTemplateFATFSOpenFileDirCounter.h"

#include "fatfs.h"

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
static tommRoC_hw_err_enum_t _FILINFO_to_fat_fs_into(const FILINFO* const filInfoPtr, tommRoC_hw_template_fat_fs_info* const infoPtr) {

    infoPtr->type = (0 == (filInfoPtr->fattrib & AM_DIR)) ? (TOMMROC_HW_TEMPLATE_FAT_FS_TYPE_FILE) : (TOMMROC_HW_TEMPLATE_FAT_FS_TYPE_DIR);
    infoPtr->size = (uint32_t) filInfoPtr->fsize;
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCUtilMemCopy(infoPtr->name, filInfoPtr->fname, _MAX_LFN + 1));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFOpen(FIL* fp, const char* const path, const uint8_t mode) {

    TOMMROC_ASSERT_LESS_THAN(tommRoCHwTemplateFATFSOpenFileDirCounterGet(), UINT8_MAX);

    if (tommRoCHwTemplateFATFSOpenFileDirCounterGet() >= UINT8_MAX) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }

    if (FR_OK != f_open(fp, (const TCHAR*) path, (BYTE) mode)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    tommRoCHwTemplateFATFSOpenFileDirCounterInc();
    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFClose(FIL* fp) {

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    if (FR_OK != f_close(fp)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    tommRoCHwTemplateFATFSOpenFileDirCounterDec();
    TOMMROC_ASSERT_NOT_EQUALS(tommRoCHwTemplateFATFSOpenFileDirCounterGet(), UINT8_MAX);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFRead(FIL* fp, void* const buff, const uint32_t btr, uint32_t* const br) {

    UINT brL;

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    if (FR_OK != f_read(fp, (void*) buff, (UINT) btr, &brL)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    *br = (uint32_t) brL;

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFWrite(FIL* fp, const void* const buff, const uint32_t btw, uint32_t* const bw) {

    UINT bwL;

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    if (FR_OK != f_write(fp, (const void*) buff, (UINT) btw, &bwL)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    *bw = (uint32_t) bwL;

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFLSeek(FIL* fp, const uint32_t ofs) {

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    if (FR_OK != f_lseek(fp, (FSIZE_t) ofs)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFDelete(const char* const path) {

    if (FR_OK != f_unlink((const TCHAR*) path)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFRename(const char* const pathOld, const char* const pathNew) {

    if (FR_OK != f_rename((const TCHAR*) pathOld, (const TCHAR*) pathNew)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFStat(const char* const path, tommRoC_hw_template_fat_fs_info* const fileInfoPtr) {

    FILINFO fno;

    if (FR_OK != f_stat((const TCHAR*) path, &fno)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(_FILINFO_to_fat_fs_into(&fno, fileInfoPtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFMount(FATFS* fs, const char* const path, const uint8_t opt) {

    if (FR_OK != f_mount(fs, (const TCHAR*) path, (BYTE) opt)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFMkfs(char* const path) {

    // A work buffer for the f_mkfs()
    static uint8_t buffer[_MAX_SS];

    if (0 != tommRoCHwTemplateFATFSOpenFileDirCounterGet()) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }

    if (FR_OK != f_mkfs((const TCHAR*) path, FM_ANY, 0, buffer, sizeof(buffer))) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

uint32_t tommRoCHwTemplateFATFSNotGuardedFSize(FIL* fp) {

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    if (NULL == fp) {
        return UINT32_MAX;
    }

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    return (uint32_t) f_size(fp);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFRewind(FIL* fp) {

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    if (FR_OK != f_rewind(fp)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFExists(const char* const path, bool* const fileExistsPtr) {

    FILINFO fno;

    *fileExistsPtr = (bool) (FR_OK == f_stat((const TCHAR*) path, &fno));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFMkDir(const char* const path) {

    if (FR_OK != f_mkdir((const TCHAR*) path)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFOpenDir(DIR* dp, const char* const path) {

    TOMMROC_ASSERT_LESS_THAN(tommRoCHwTemplateFATFSOpenFileDirCounterGet(), UINT8_MAX);

    if (tommRoCHwTemplateFATFSOpenFileDirCounterGet() >= UINT8_MAX) {
        return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
    }

    if (FR_OK != f_opendir(dp, (const TCHAR*) path)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    tommRoCHwTemplateFATFSOpenFileDirCounterInc();
    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFCloseDir(DIR* dp) {

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    if (FR_OK != f_closedir(dp)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    tommRoCHwTemplateFATFSOpenFileDirCounterDec();
    TOMMROC_ASSERT_NOT_EQUALS(tommRoCHwTemplateFATFSOpenFileDirCounterGet(), UINT8_MAX);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFReadDir(DIR* dp, tommRoC_hw_template_fat_fs_info* const dirInfoPtr, tommRoC_hw_template_fat_fs_availability_enum_t* const availabilityPtr) {

    FILINFO fno;

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    if (FR_OK != f_readdir(dp, &fno)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(_FILINFO_to_fat_fs_into(&fno, dirInfoPtr));

    *availabilityPtr = (TOMMROC_STRING_NULL_TERMINATOR_CHAR == fno.fname[0]) ? (TOMMROC_HW_TEMPLATE_FAT_FS_AVAILABILITY_NO_ELEMENT) : (TOMMROC_HW_TEMPLATE_FAT_FS_AVAILABILITY_ELEMENT);

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFRewindDir(DIR* dp) {

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    if (FR_OK != f_rewinddir(dp)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    TOMMROC_ASSERT_NOT_ZERO(tommRoCHwTemplateFATFSOpenFileDirCounterGet());

    return TOMMRO_C_HW_ERR_SUCCESS;
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSNotGuardedFGetFree(uint32_t* const freeSizeBytePtr) {

    FATFS *fs;
    DWORD fre_clust;
    DWORD fre_sect;

#if (_MIN_SS < _MAX_SS)
    WORD sectorSizeByte;
#endif

    uint32_t freeSizeByte;

    if (FR_OK != f_getfree("/", &fre_clust, &fs)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }

    // Get total sectors and free sectors
    fre_sect = fre_clust * fs->csize;

    /**
     * NOTE:
     * FatFs supports the sector size in range of 512 to 4096 bytes.
     * _MIN_SS == _MAX_SS -> FatFs is configured for fixed sector size.
     * _MIN_SS < _MAX_SS -> FatFs is configured for variable sector size and GET_SECTOR_SIZE command must be implemented to the disk_ioctl() function.
     */
#if (_MIN_SS == _MAX_SS)
    freeSizeByte = (uint32_t) fre_sect * (uint32_t) _MIN_SS;
#elif (_MIN_SS < _MAX_SS)
    if (RES_OK != disk_ioctl(fs->drv, GET_SECTOR_SIZE, &sectorSizeByte)) {
        return TOMMRO_C_HW_LOW_LEVEL_ERR;
    }
    freeSizeByte = (uint32_t) fre_sect * (uint32_t) sectorSizeByte;
#else
#error "Error in FatFS configuration."
#endif

    *freeSizeBytePtr = freeSizeByte;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif
