
#if defined (__TOMMROC_HW_USE_MONGOOSE_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "mongoose/lib/source/lib/mongoose.h"

#include "mongoose/lib/source/port/HTTP/mongooseHALHTTPFile.h"

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
#if defined (TOMMROC_HW_TEMPLATE_MONGOOSE_HAL_DEF_FS_IS_USED)
static const char __DEBUG_OBJ_ID__[] = "mgHALHTTP";
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * HTTP upload is chunked.
 * For every packet offset and data length are sent.
 * First chunk can be detected checking (offset == 0).
 * Next N-1 packets can be detected checking (offset != 0 && dataLength != 0).
 * Last chunk can be detected checking (dataLength == 0). Offset of last chunk is file size.
 */
int mg_http_upload(struct mg_connection *c, struct mg_http_message *hm,
                   const char *dir) {

#if defined (TOMMROC_HW_TEMPLATE_MONGOOSE_HAL_DEF_FS_IS_USED)
    static char offsetStr[TOMMROC_STRING_U64_DEC_AS_STRING_MAX_ARRAY_SIZE_BYTE];
    static char nameStr[64];
    static char pathStr[64];

    uint16_t offsetStrLen;
    uint16_t nameStrLen;

    uint32_t offset;

    int res;

    void* ptr;
    uint16_t bSize;

    // Extract offset and name string from query.
    if (mg_http_get_var(&hm->query, "offset", offsetStr, sizeof(offsetStr)) < 0) {
        TOMMROC_DEBUG_E("extract offset error");
        mg_http_reply(c, 400, "", "%s", "extract offset error");
        return -1;
    }
    if (mg_http_get_var(&hm->query, "name", nameStr, sizeof(nameStr)) < 0) {
        TOMMROC_DEBUG_E("extract name error");
        mg_http_reply(c, 400, "", "%s", "extract name error");
        return -1;
    }

    offsetStrLen    = tommRoCStringStrLen(offsetStr);
    nameStrLen      = tommRoCStringStrLen(nameStr);

    if (0 == offsetStrLen) {
        TOMMROC_DEBUG_E("offset required");
        mg_http_reply(c, 400, "", "%s", "offset required");
        return -1;
    }

    if (0 == nameStrLen) {
        TOMMROC_DEBUG_E("name required");
        mg_http_reply(c, 400, "", "%s", "name required");
        return -1;
    }

    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCStringStringToU32(offsetStr, offsetStrLen, 10, &offset), -1);

    ptr     = pathStr;
    bSize   = sizeof(pathStr);
    if (tommRoCStringStrLen(dir) > 0) {
        TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCUtilBufferAppendString(ptr, bSize, dir, &ptr, &bSize), -1);
    }
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCUtilBufferAppendU8(ptr, bSize, MG_DIRSEP, &ptr, &bSize), -1);
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCUtilBufferAppendString(ptr, bSize, nameStr, &ptr, &bSize), -1);
    TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(tommRoCUtilBufferAppendU8(ptr, bSize, TOMMROC_STRING_NULL_TERMINATOR_CHAR, &ptr, &bSize), -1);

    TOMMROC_DEBUG_PRINTLN_PLUS_STRING(TOMMRO_C_DEBUG_D_LEVEL, "pathStr: ", pathStr);
    TOMMROC_DEBUG_PRINTLN_PLUS_U32(TOMMRO_C_DEBUG_D_LEVEL, "offset: ", offset, TOMMRO_C_UTIL_DECIMAL_FORMAT);
    TOMMROC_DEBUG_PRINTLN_PLUS_U32(TOMMRO_C_DEBUG_D_LEVEL, "data len: ", hm->body.len, TOMMRO_C_UTIL_DECIMAL_FORMAT);

    res = mongooseHALHTTPFileUpload(
            pathStr,
            offset,
            hm->body.ptr,
            hm->body.len,
            (0 == offset),
            (0 == hm->body.len));

    if (res < 0) {
        TOMMROC_DEBUG_E("file operation error");
        mg_http_reply(c, 400, "", "file operation error: %s", nameStr);
        return res;
    }

    TOMMROC_DEBUG_D("file operation success");
    mg_http_reply(c, 200, "", "");
    return res;

#else
    TOMMROC_UTIL_UNUSED_PARAM(c);
    TOMMROC_UTIL_UNUSED_PARAM(hm);
    TOMMROC_UTIL_UNUSED_PARAM(dir);
    return -1;
#endif
}

#endif
