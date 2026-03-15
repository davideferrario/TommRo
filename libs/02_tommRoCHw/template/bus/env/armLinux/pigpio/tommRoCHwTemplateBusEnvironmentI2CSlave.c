
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentI2CSlave.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)

#if defined (__TOMMROC_HW_AT_LEAST_ONE_I2C_SLAVE_TEMPLATE_IS_USED__)

#include <pigpio.h>

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

#if defined (__TOMMROC_HW_AT_LEAST_ONE_I2C_SLAVE_TEMPLATE_IS_USED__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CSlaveSetProp(
        const   tommRoC_hw_template_bus_spi_slave_prop_enum_t           property,
        const   tommRoC_hw_template_bus_spi_slave_enum_t                bus,
        const   void*                                           const   propValuePtr) {

    TOMMROC_UTIL_UNUSED_PARAM(property);
    TOMMROC_UTIL_UNUSED_PARAM(bus);
    TOMMROC_UTIL_UNUSED_PARAM(propValuePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_SLAVE_0_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CSlave0Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_SLAVE_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CSlave1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_SLAVE_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CSlave2Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_SLAVE_3_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CSlave3Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_SLAVE_4_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CSlave4Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_SLAVE_5_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CSlave5Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#endif

#endif
