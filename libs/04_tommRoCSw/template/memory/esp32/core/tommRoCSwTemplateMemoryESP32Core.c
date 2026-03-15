
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateMemoryESP32Core.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

#include "mbedtls/memory_buffer_alloc.h"

#include <stdbool.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
static bool _is_init = false;

/*******************************************************************************
 * local functions
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_sw_err_enum_t tommRoCSwTemplateMemoryESP32CoreInit(
                uint8_t*    const   memoryBufferPtr,
        const   uint32_t            memoryBufferSize) {

    TOMMROC_ASSERT_NOT_NULL(memoryBufferPtr);
    TOMMROC_ASSERT_NOT_ZERO(memoryBufferSize);

    TOMMROC_SW_PARAM_CHECK_ON_NULL_RETURN_ERR(memoryBufferPtr);
    TOMMROC_SW_PARAM_CHECK_ON_ZERO_RETURN_ERR(memoryBufferSize);

    if (_is_init) {
        return TOMMRO_C_SW_GENERIC_ERR;
    }

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)

    mbedtls_memory_buffer_alloc_init(
            memoryBufferPtr,
            memoryBufferSize);
#endif

    _is_init = true;

    return TOMMRO_C_SW_ERR_SUCCESS;
}

tommRoC_sw_err_enum_t tommRoCSwTemplateMemoryESP32CoreIsInit(void) {

    if (!_is_init) {
        return TOMMRO_C_SW_ENVIRONMENT_NOT_INIT_ERR;
    }

    return TOMMRO_C_SW_ERR_SUCCESS;
}

#endif
