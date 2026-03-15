
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentI2CMaster.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include <pigpio.h>

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __RPIZEROW_I2C0_SDA_GPIO_PIN__              (0)
#define __RPIZEROW_I2C0_SCL_GPIO_PIN__              (1)

#define __RPIZEROW_I2C1_SDA_GPIO_PIN__              (2)
#define __RPIZEROW_I2C1_SCL_GPIO_PIN__              (3)

#define __NOT_VALID_HANDLE__                        (-1)

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

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMasterSetProp(
        const   tommRoC_hw_template_bus_spi_master_prop_enum_t          property,
        const   tommRoC_hw_template_bus_spi_master_enum_t               bus,
        const   void*                                           const   propValuePtr) {

    TOMMROC_UTIL_UNUSED_PARAM(property);
    TOMMROC_UTIL_UNUSED_PARAM(bus);
    TOMMROC_UTIL_UNUSED_PARAM(propValuePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster0Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster2Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_3_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster3Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_4_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster4Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_5_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster5Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_UTIL_UNUSED_PARAM(cbFunctPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#endif

#endif
