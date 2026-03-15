
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateFileXFSOpenFileDirCounter.h"

#include "TOMMROC.h"

#include <stdint.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static uint8_t _open_file_dir_counter;  // NOTE: limit to 255 the max number of "opened in same time" file/dir

/*******************************************************************************
 * local functions
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

void tommRoCHwTemplateFileXFSOpenFileDirCounterInit(void)   { _open_file_dir_counter = 0; }
uint8_t tommRoCHwTemplateFileXFSOpenFileDirCounterGet(void) { return _open_file_dir_counter; }

void tommRoCHwTemplateFileXFSOpenFileDirCounterDec(void)    { TOMMROC_ASSERT_NOT_ZERO(_open_file_dir_counter);              --_open_file_dir_counter; }
void tommRoCHwTemplateFileXFSOpenFileDirCounterInc(void)    { TOMMROC_ASSERT_NOT_EQUALS(_open_file_dir_counter, UINT8_MAX); ++_open_file_dir_counter; }
