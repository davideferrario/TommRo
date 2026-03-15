
#if defined (__TOMMROC_HW_USE_MONGOOSE_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "mongoose/lib/source/lib/mongoose.h"

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

char *mg_file_read(const char *path, size_t *sizep) {

#if defined (TOMMROC_HW_TEMPLATE_MONGOOSE_HAL_DEF_FS_IS_USED)
    return mongooseHALFSFileRead(path, sizep);
#else
    TOMMROC_UTIL_UNUSED_PARAM(path);
    TOMMROC_UTIL_UNUSED_PARAM(sizep);
    return NULL;
#endif
}

bool mg_file_write(const char *path, const void *buf, size_t len) {

#if defined (TOMMROC_HW_TEMPLATE_MONGOOSE_HAL_DEF_FS_IS_USED)
    return mongooseHALFSFileWrite(path, buf, len);
#else
    TOMMROC_UTIL_UNUSED_PARAM(path);
    TOMMROC_UTIL_UNUSED_PARAM(buf);
    TOMMROC_UTIL_UNUSED_PARAM(len);
    return false;
#endif
}

#endif
