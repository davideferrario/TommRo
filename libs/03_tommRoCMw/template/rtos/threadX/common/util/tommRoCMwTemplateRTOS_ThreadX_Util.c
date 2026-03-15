
#if defined (__TOMMROC_MW_USE_THREAD_THREADX_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_ThreadX_Util.h"

#include "application/appMain.h"

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
static TX_BYTE_POOL* _app_stack_byte_pool_ptr = NULL;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static void _start_system(TX_BYTE_POOL* const appStackBytePoolPtr) {

    _app_stack_byte_pool_ptr = appStackBytePoolPtr;

    appMainStartMainApp();
}

/*******************************************************************************
 * functions
 ******************************************************************************/

void tommRoCMwTemplateRTOS_ThreadX_Util_StartSystem(TX_BYTE_POOL* const appStackBytePoolPtr) {
    _start_system(appStackBytePoolPtr);
}

TX_BYTE_POOL* tommRoCMwTemplateRTOS_ThreadX_Util_GetAppStackBytePoolPtr(void) {
    return _app_stack_byte_pool_ptr;
}

#endif
