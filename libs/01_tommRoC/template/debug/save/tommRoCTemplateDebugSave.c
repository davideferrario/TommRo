
#if defined (__TOMMROC_USE_SAVE_DEBUG_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCTemplateDebugSave.h"

#include "TOMMROCMw.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __MAIN_FOLDER_PATH_STR__                "LOG"
#define __MAIN_FOLDER_PATH_STR_LEN__            (3)

#define __NO_DATE_FILE_NAME_FORMAT_STR__        "%s/saved.log"
#define __DATE_FILE_NAME_FORMAT_STR__           "%s/%04d%02d%02d.log"

#define __DATE_FILE_NAME_EXTENSION_STR_LEN      (1 + 3)
#define __DATE_FILE_NAME_STR_MAX_LEN__          (__MAIN_FOLDER_PATH_STR_LEN__ + 1 + 4 + 2 + 2 + __DATE_FILE_NAME_EXTENSION_STR_LEN + 1)

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
 
tommRoC_err_enum_t tommRoCTemplateDebugSaveStart(void) {

    return TOMMRO_C_ERR_SUCCESS;
}

const char* tommRoCTemplateDebugSaveNewLineStr(void) {

    static const char newLineStr[] = TOMMROC_STRING_NEW_LINE_STR;

    return newLineStr;
}

tommRoC_err_enum_t tommRoCTemplateDebugSaveStr(const char* const str) {

    static const char noDateFileNameFormat[]    = __NO_DATE_FILE_NAME_FORMAT_STR__;
    static const char dateFileNameFormat[]      = __DATE_FILE_NAME_FORMAT_STR__;
    static const char mainFolderPath[]          = __MAIN_FOLDER_PATH_STR__;

    static char fileName[__DATE_FILE_NAME_STR_MAX_LEN__];
    tommRoC_mw_file_t file;

    tommRoC_date_time_t dateTime;

    if (TOMMRO_C_MW_ERR_SUCCESS != tommRoCMwDiskIsAvailable()) {
        return TOMMRO_C_ERR_SUCCESS;
    }

    if (TOMMRO_C_MW_ERR_SUCCESS != tommRoCMwFileIsAvailable()) {
        return TOMMRO_C_ERR_SUCCESS;
    }

    tommRoCMwDiskMakeFolder(mainFolderPath);

    if (TOMMRO_C_ERR_SUCCESS == tommRoCOsGetDateTime(&dateTime)) {

        tommRoCSTDIOSNPrintf(
                fileName,
                sizeof(fileName),
                dateFileNameFormat,
                mainFolderPath,
                tommRoCDateTimeGetYear(&dateTime),
                tommRoCDateTimeGetMonth(&dateTime),
                tommRoCDateTimeGetDay(&dateTime));
    }
    else {

        tommRoCSTDIOSNPrintf(
                fileName,
                sizeof(fileName),
                noDateFileNameFormat,
                mainFolderPath);
    }

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCMwFileOpen(fileName, TOMMRO_C_MW_FILE_OPEN_FOR_APPEND, &file),
            TOMMRO_C_GENERIC_ERR);

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCMwFileWriteString(str, &file),
            TOMMRO_C_GENERIC_ERR);

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(
            tommRoCMwFileClose(&file),
            TOMMRO_C_GENERIC_ERR);

    return TOMMRO_C_ERR_SUCCESS;
}

#endif
