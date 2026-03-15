
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentSPISlave.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)

#if defined (__TOMMROC_HW_AT_LEAST_ONE_SPI_SLAVE_TEMPLATE_IS_USED__)

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

#if defined (__TOMMROC_HW_AT_LEAST_ONE_SPI_SLAVE_TEMPLATE_IS_USED__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPISlaveSetProp(
        const   tommRoC_hw_template_bus_spi_slave_prop_enum_t           property,
        const   tommRoC_hw_template_bus_spi_slave_enum_t                bus,
        const   void*                                           const   propValuePtr) {

    TOMMROC_UTIL_UNUSED_PARAM(property);
    TOMMROC_UTIL_UNUSED_PARAM(bus);
    TOMMROC_UTIL_UNUSED_PARAM(propValuePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_0_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPISlave0Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPISlave1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPISlave2Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_3_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPISlave3Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_4_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPISlave4Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_5_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentSPISlave5Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#endif

#endif
