
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateFATFS.h"

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)
#include "FATFS/busy/tommRoCHwTemplateFATFSBusy.h"
#include "FATFS/notGuarded/tommRoCHwTemplateFATFSNotGuarded.h"
#include "FATFS/openFileDirCounter/tommRoCHwTemplateFATFSOpenFileDirCounter.h"

#include "TOMMROC.h"
#include "TOMMROCHw.h"
#include "TOMMROCTemplate.h"

#if defined (__TOMMROC_TEMPLATE_ARM_STM32_IS_USED__)
#include "main.h"
#if !defined (HAL_SD_MODULE_ENABLED)
#error "HAL_SD_MODULE_ENABLED must be defined"
#endif
#if !defined(SDCARD_CD_Pin) || !defined(SDCARD_CD_GPIO_Port)
#error "Define SDCARD_CD Pin"
#endif
#endif

#include "fatfs.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
TOMMROC_SCTA_EQUALS(TOMMROC_HW_TEMPLATE_FAT_FS_FA_READ,             FA_READ);
TOMMROC_SCTA_EQUALS(TOMMROC_HW_TEMPLATE_FAT_FS_FA_WRITE,            FA_WRITE);
TOMMROC_SCTA_EQUALS(TOMMROC_HW_TEMPLATE_FAT_FS_FA_OPEN_EXISTING,    FA_OPEN_EXISTING);
TOMMROC_SCTA_EQUALS(TOMMROC_HW_TEMPLATE_FAT_FS_FA_CREATE_NEW,       FA_CREATE_NEW);
TOMMROC_SCTA_EQUALS(TOMMROC_HW_TEMPLATE_FAT_FS_FA_CREATE_ALWAYS,    FA_CREATE_ALWAYS);
TOMMROC_SCTA_EQUALS(TOMMROC_HW_TEMPLATE_FAT_FS_FA_OPEN_ALWAYS,      FA_OPEN_ALWAYS);
TOMMROC_SCTA_EQUALS(TOMMROC_HW_TEMPLATE_FAT_FS_FA_OPEN_APPEND,      FA_OPEN_APPEND);

TOMMROC_SCTA_SIZE_OF_EQUALS(tommRoC_hw_template_fat_fs_file_t,      FIL);
TOMMROC_SCTA_SIZE_OF_EQUALS(tommRoC_hw_template_fat_fs_dir_t,       DIR);

/*******************************************************************************
 * local vars
 ******************************************************************************/
static tommRoC_guard_t* _guard_ptr = NULL;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_hw_err_enum_t _sd_card_available(bool* const sdCardAvailablePtr) {

#if defined (__TOMMROC_TEMPLATE_ARM_STM32_IS_USED__)
    *sdCardAvailablePtr = (GPIO_PIN_RESET == HAL_GPIO_ReadPin(SDCARD_CD_GPIO_Port, SDCARD_CD_Pin));
    return TOMMRO_C_HW_ERR_SUCCESS;
#else
    TOMMROC_UTIL_UNUSED_PARAM(sdCardAvailablePtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

static tommRoC_hw_err_enum_t _fatfs_start(void) {

    tommRoCHwTemplateFATFSOpenFileDirCounterInit();

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateFATFSNotGuardedFMount(
                    &SDFatFS,
                    SDPath,
                    0));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _fatfs_stop(void) {

    _guard_ptr = NULL;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateFATFSNotGuardedFMount(
                    NULL,
                    "",
                    0));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _f_open(
        const   char*                                           const   pathStrPtr,
        const   uint8_t                                                 mode,
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFOpen(
                    (FIL*) filePtr,
                    pathStrPtr,
                    mode));
}

static tommRoC_hw_err_enum_t _f_close(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFClose(
                    (FIL*) filePtr));
}

static tommRoC_hw_err_enum_t _f_read(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr,
                void*                                           const   readBufferPtr,
        const   uint32_t                                                toReadAmount,
                uint32_t*                                       const   readedAmountPtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFRead(
                    (FIL*) filePtr,
                    readBufferPtr,
                    toReadAmount,
                    readedAmountPtr));
}

static tommRoC_hw_err_enum_t _f_write(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr,
        const   void*                                           const   writeBufferPtr,
        const   uint32_t                                                writeBufferLen,
                uint32_t*                                       const   writtenAmountPtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFWrite(
                    (FIL*) filePtr,
                    writeBufferPtr,
                    writeBufferLen,
                    writtenAmountPtr));
}

static tommRoC_hw_err_enum_t _f_l_seek(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr,
        const   uint32_t                                                offsetByte) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFLSeek(
                    (FIL*) filePtr,
                    offsetByte));
}

static tommRoC_hw_err_enum_t _f_delete(
        const   char*                                           const   pathStrPtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFDelete(
                    pathStrPtr));
}

static tommRoC_hw_err_enum_t _f_rename(
        const   char*                                           const   pathOldStrPtr,
        const   char*                                           const   pathNewStrPtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFRename(
                    pathOldStrPtr,
                    pathNewStrPtr));
}

static tommRoC_hw_err_enum_t _f_stat(
        const   char*                                           const   pathStrPtr,
                tommRoC_hw_template_fat_fs_info*                const   fileInfoPtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFStat(
                    pathStrPtr,
                    fileInfoPtr));
}

static tommRoC_hw_err_enum_t _f_mkfs_low_level(void) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFMkfs(
                    SDPath));
}

static tommRoC_hw_err_enum_t _f_mkfs(const uint32_t timeoutMsec) {

    tommRoC_timer_t timer = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_timer_t);

    // Wait for all file/dir closed and after try to format.
    // NOTE: "try" to format because it can be possible that between "check for files closed" and format, some other tasks open files.
    if (TOMMROC_HW_TEMPLATE_FAT_FS_DISK_FORMAT_WAIT_FOREVER_TIMEOUT != timeoutMsec) {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, timeoutMsec));
    }

    while ((!tommRoCTimerIsStarted(&timer)) || (TOMMRO_C_TIMER_NOT_EXPIRED_ERR == tommRoCTimerIsExpired(&timer))) {

        if (0 == tommRoCHwTemplateFATFSOpenFileDirCounterGet()) {

            // Added to avoid "warning: unreachable code"
            do {
                // Try to format and check result
                switch (_f_mkfs_low_level()) {

                case TOMMRO_C_HW_ERR_SUCCESS:       return TOMMRO_C_HW_ERR_SUCCESS;     // Format success.
                case TOMMRO_C_HW_NOT_AVAILABLE_ERR: break;                              // Skip format because there are opened files.
                default:                            return TOMMRO_C_HW_LOW_LEVEL_ERR;   // Low lever error.

                }
            } while (0);
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));
    }

    return TOMMRO_C_HW_TIMEOUT_ERR;
}

static uint32_t _f_size(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr) {

    TOMMROC_GUARD_SYNCHRO_WITH_RESULT_FUNCT(
            uint32_t,
            _guard_ptr,
            UINT32_MAX,
            tommRoCHwTemplateFATFSNotGuardedFSize(
                    (FIL*) filePtr));
}

static tommRoC_hw_err_enum_t _f_rewind(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFRewind(
                    (FIL*) filePtr));
}

static tommRoC_hw_err_enum_t _f_exists(
        const   char*                                           const   pathStrPtr,
                bool*                                           const   fileExistsPtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFExists(
                    pathStrPtr,
                    fileExistsPtr));
}

static tommRoC_hw_err_enum_t _f_mk_dir(
        const   char*                                           const   pathStrPtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFMkDir(
                    pathStrPtr));
}

static tommRoC_hw_err_enum_t _f_open_dir(
        const   char*                                           const   pathStrPtr,
                tommRoC_hw_template_fat_fs_dir_t*               const   dirPtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFOpenDir(
                    (DIR*) dirPtr,
                    pathStrPtr));
}

static tommRoC_hw_err_enum_t _f_close_dir(
                tommRoC_hw_template_fat_fs_dir_t*               const   dirPtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFCloseDir(
                    (DIR*) dirPtr));
}

static tommRoC_hw_err_enum_t _f_read_dir(
                tommRoC_hw_template_fat_fs_dir_t*               const   dirPtr,
                tommRoC_hw_template_fat_fs_info*                const   dirInfoPtr,
                tommRoC_hw_template_fat_fs_availability_enum_t* const   availabilityPtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFReadDir(
                    (DIR*) dirPtr,
                    dirInfoPtr,
                    availabilityPtr));
}

static tommRoC_hw_err_enum_t _f_rewind_dir(
                tommRoC_hw_template_fat_fs_dir_t*               const   dirPtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFRewindDir(
                    (DIR*) dirPtr));
}

static tommRoC_hw_err_enum_t _f_get_free(
                uint32_t*                                       const   freeSizeBytePtr) {

    TOMMROC_HW_UTIL_SYNCHRO_TOMMROC_HW_LIB_FUNCT(
            _guard_ptr,
            tommRoCHwTemplateFATFSNotGuardedFGetFree(
                    freeSizeBytePtr));
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSStart(void) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _fatfs_start());
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSStop(void) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _fatfs_stop());
#else
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSSetGuard(const tommRoC_guard_t* const guardPtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

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

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSSDCardAvailable(
                bool*                                           const   sdCardAvailablePtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(sdCardAvailablePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(sdCardAvailablePtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _sd_card_available(
                    sdCardAvailablePtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(sdCardAvailablePtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

bool tommRoCHwTemplateFATFSGetIsBusy(void) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)
    return tommRoCHwTemplateFATFSBusyIs();
#else
    return false;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFOpen(
        const   char*                                           const   pathStrPtr,
        const   uint8_t                                                 mode,
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(pathStrPtr);
    TOMMROC_ASSERT_NOT_NULL(filePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(pathStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(filePtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_open(
                    pathStrPtr,
                    mode,
                    filePtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(pathStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(mode);
    TOMMROC_UTIL_UNUSED_PARAM(filePtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFClose(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(filePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(filePtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_close(
                    filePtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(filePtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFRead(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr,
                void*                                           const   readBufferPtr,
        const   uint32_t                                                toReadAmount,
                uint32_t*                                       const   readedAmountPtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(filePtr);
    TOMMROC_ASSERT_NOT_NULL(readBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(toReadAmount);
    TOMMROC_ASSERT_NOT_NULL(readedAmountPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(filePtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(readBufferPtr);
    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(toReadAmount);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(readedAmountPtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_read(
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

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFWrite(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr,
        const   void*                                           const   writeBufferPtr,
        const   uint32_t                                                writeBufferLen,
                uint32_t*                                       const   writtenAmountPtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(filePtr);
    TOMMROC_ASSERT_NOT_NULL(writeBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(writeBufferLen);
    TOMMROC_ASSERT_NOT_NULL(writtenAmountPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(filePtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(writeBufferPtr);
    TOMMROC_HW_PARAM_CHECK_ON_ZERO_RETURN_ERR(writeBufferLen);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(writtenAmountPtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_write(
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

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFReadRP(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr,
                void*                                           const   readBufferPtr,
        const   uint32_t                                                toReadAmount) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    uint32_t readedAmount;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateFATFSFRead(
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

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFWriteRP(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr,
        const   void*                                           const   writeBufferPtr,
        const   uint32_t                                                writeBufferLen) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    uint32_t writtenAmount;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwTemplateFATFSFWrite(
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

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFLSeek(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr,
        const   uint32_t                                                offsetByte) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(filePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(filePtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_l_seek(
                    filePtr,
                    offsetByte));
#else
    TOMMROC_UTIL_UNUSED_PARAM(filePtr);
    TOMMROC_UTIL_UNUSED_PARAM(offsetByte);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFDelete(
        const   char*                                           const   pathStrPtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(pathStrPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(pathStrPtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_delete(
                    pathStrPtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(pathStrPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFRename(
        const   char*                                           const   pathOldStrPtr,
        const   char*                                           const   pathNewStrPtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(pathOldStrPtr);
    TOMMROC_ASSERT_NOT_NULL(pathNewStrPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(pathOldStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(pathNewStrPtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_rename(
                    pathOldStrPtr,
                    pathNewStrPtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(pathOldStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(pathNewStrPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFStat(
        const   char*                                           const   pathStrPtr,
                tommRoC_hw_template_fat_fs_info*                const   fileInfoPtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(pathStrPtr);
    TOMMROC_ASSERT_NOT_NULL(fileInfoPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(pathStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(fileInfoPtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_stat(
                    pathStrPtr,
                    fileInfoPtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(pathStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(fileInfoPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFMkfs(
        const   uint32_t                                                timeoutMsec) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    tommRoC_timer_t timer = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_timer_t);

    if (TOMMROC_HW_TEMPLATE_FAT_FS_DISK_FORMAT_WAIT_FOREVER_TIMEOUT != timeoutMsec) {
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, timeoutMsec));
    }

    // Wait for all file/dir closed before set file system is busy flag
    while ((!tommRoCTimerIsStarted(&timer)) || (TOMMRO_C_TIMER_NOT_EXPIRED_ERR == tommRoCTimerIsExpired(&timer))) {

        if (0 == tommRoCHwTemplateFATFSOpenFileDirCounterGet()) {

            TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
                    tommRoCHwTemplateFATFSBusySet(),
                    tommRoCHwTemplateFATFSBusyReset(),
                    _f_mkfs(
                            timeoutMsec));
        }

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayMsec(1));
    }

    return TOMMRO_C_HW_TIMEOUT_ERR;
#else
    TOMMROC_UTIL_UNUSED_PARAM(timeoutMsec);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

uint32_t tommRoCHwTemplateFATFSFSize(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(filePtr);

    if (NULL == filePtr) {
        return 0;
    }

    TOMMROC_UTIL_BLOCK_CODE_WITH_RESULT_FUNCT(
            uint32_t,
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_size(
                    filePtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(filePtr);
    return 0;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFRewind(
                tommRoC_hw_template_fat_fs_file_t*              const   filePtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(filePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(filePtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_rewind(
                    filePtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(filePtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFExists(
        const   char*                                           const   pathStrPtr,
                bool*                                           const   fileExistsPtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(pathStrPtr);
    TOMMROC_ASSERT_NOT_NULL(fileExistsPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(pathStrPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(fileExistsPtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_exists(
                    pathStrPtr,
                    fileExistsPtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(pathStrPtr);
    TOMMROC_UTIL_UNUSED_PARAM(fileExistsPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFMkDir(
        const   char*                                           const   pathStrPtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(pathStrPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(pathStrPtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_mk_dir(
                    pathStrPtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(pathStrPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFOpenDir(
        const   char*                                           const   pathStrPtr,
                tommRoC_hw_template_fat_fs_dir_t*               const   dirPtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(dirPtr);
    TOMMROC_ASSERT_NOT_NULL(pathStrPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(dirPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(pathStrPtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_open_dir(
                    pathStrPtr,
                    dirPtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(dirPtr);
    TOMMROC_UTIL_UNUSED_PARAM(pathStrPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFCloseDir(
                tommRoC_hw_template_fat_fs_dir_t*               const   dirPtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(dirPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(dirPtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_close_dir(
                    dirPtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(dirPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFReadDir(
                tommRoC_hw_template_fat_fs_dir_t*               const   dirPtr,
                tommRoC_hw_template_fat_fs_info*                const   dirInfoPtr,
                tommRoC_hw_template_fat_fs_availability_enum_t* const   availabilityPtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(dirPtr);
    TOMMROC_ASSERT_NOT_NULL(dirInfoPtr);
    TOMMROC_ASSERT_NOT_NULL(availabilityPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(dirPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(dirInfoPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(availabilityPtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_read_dir(
                    dirPtr,
                    dirInfoPtr,
                    availabilityPtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(dirPtr);
    TOMMROC_UTIL_UNUSED_PARAM(dirInfoPtr);
    TOMMROC_UTIL_UNUSED_PARAM(availabilityPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFRewindDir(
                tommRoC_hw_template_fat_fs_dir_t*               const   dirPtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(dirPtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(dirPtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_rewind_dir(
                    dirPtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(dirPtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateFATFSFGetFree(
                uint32_t*                                       const   freeSizeBytePtr) {

#if defined (__TOMMROC_HW_USE_FAT_FS_TEMPLATE__)

    TOMMROC_ASSERT_NOT_NULL(freeSizeBytePtr);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(freeSizeBytePtr);

    TOMMROC_HW_UTIL_BLOCK_CODE_TOMMROC_HW_LIB_FUNCT(
            tommRoCHwTemplateFATFSBusySet(),
            tommRoCHwTemplateFATFSBusyReset(),
            _f_get_free(
                    freeSizeBytePtr));
#else
    TOMMROC_UTIL_UNUSED_PARAM(freeSizeBytePtr);
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#endif
}

#endif
