
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCSwTemplateECDHESP32Context.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#include "TOMMROCSw.h"

#include "mbedtls/bignum.h"
#include "mbedtls/ecp.h"

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

void tommRoCSwTemplateECDHESP32ContextInit(tommRoC_sw_template_ecdh_esp32_context_t* const ecdhCtxPtr) {

    mbedtls_ecp_group_init(&ecdhCtxPtr->grp);
    mbedtls_mpi_init(&ecdhCtxPtr->d);
    mbedtls_ecp_point_init(&ecdhCtxPtr->Q);
    mbedtls_ecp_point_init(&ecdhCtxPtr->Qp);
    mbedtls_mpi_init(&ecdhCtxPtr->z);
}

void tommRoCSwTemplateECDHESP32ContextFree(tommRoC_sw_template_ecdh_esp32_context_t* const ecdhCtxPtr) {

    mbedtls_ecp_group_free(&ecdhCtxPtr->grp);
    mbedtls_mpi_free(&ecdhCtxPtr->d);
    mbedtls_ecp_point_free(&ecdhCtxPtr->Q);
    mbedtls_ecp_point_free(&ecdhCtxPtr->Qp);
    mbedtls_mpi_free(&ecdhCtxPtr->z);
}

#endif
