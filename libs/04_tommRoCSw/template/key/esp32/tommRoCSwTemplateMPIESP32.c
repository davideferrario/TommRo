
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateMPIESP32.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

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

tommRoC_err_enum_t tommRoCSwTemplateMPIESP32ReadBinary(
                mbedtls_mpi*    const   mpiPtr,
        const   uint8_t*        const   bufferPtr,
        const   uint16_t                bufferLen) {

    int res;

    res = mbedtls_mpi_read_binary(mpiPtr, bufferPtr, bufferLen);

    if (MBEDTLS_ERR_MPI_ALLOC_FAILED == res) {
        return TOMMRO_C_NOT_ENOUGH_RESOURCE_ERR;
    }
    else if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

tommRoC_err_enum_t tommRoCSwTemplateMPIESP32WriteBinary(
        const   mbedtls_mpi*    const   mpiPtr,
                uint8_t*        const   bufferPtr,
        const   uint16_t                bufferLen) {

    int res;

    res = mbedtls_mpi_write_binary(mpiPtr, bufferPtr, bufferLen);

    if (MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL == res) {
        return TOMMRO_C_NOT_ENOUGH_RESOURCE_ERR;
    }
    else if (0 != res) {
        return TOMMRO_C_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_ERR_SUCCESS;
}

#endif
