
#if defined (__TOMMROC_USE_TIME_ARM_OS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "os/tommRoCTemplateOsIsFromISR.h"

#include "env/tommRoCTemplateEnv.h"

// ARM Compiler 4/5
#if   defined ( __CC_ARM )
#include "cmsis_armcc.h"
// GNU Compiler
#elif defined ( __GNUC__ )
#include "cmsis_gcc.h"
// IAR Compiler
#elif defined ( __ICCARM__ )
#include <cmsis_iar.h>
#endif

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

tommRoC_err_enum_t tommRoCTemplateOsIsFromISRInit(void) {
    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsIsFromISRClose(void) {
    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCTemplateOsIsFromISR(bool* const isFromISRPtr) {
    *isFromISRPtr = (0 !=  __get_IPSR());
    return TOMMRO_C_ERR_SUCCESS;
}

#endif
