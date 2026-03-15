
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusI2CMaster.h"

#include "bus/common/tommRoCHwTemplateBusCommon.h"

#include "bus/env/tommRoCHwTemplateBusEnvironmentI2CMaster.h"

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

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CMasterSetProp(
        const   tommRoC_hw_template_bus_i2c_master_prop_enum_t          property,
        const   tommRoC_hw_template_bus_i2c_master_enum_t               bus,
        const   void*                                           const   propValuePtr) {

    TOMMROC_ASSERT_NOT_NULL(propValuePtr);

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

    return tommRoCHwTemplateBusEnvironmentI2CMasterSetProp(property, bus, propValuePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(property);
    TOMMROC_UTIL_UNUSED_PARAM(bus);
    TOMMROC_UTIL_UNUSED_PARAM(propValuePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CMaster0Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_I2C_MASTER_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentI2CMaster0Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CMaster1Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_I2C_MASTER_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentI2CMaster1Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CMaster2Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_I2C_MASTER_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentI2CMaster2Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CMaster3Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_3_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_I2C_MASTER_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentI2CMaster3Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CMaster4Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_4_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_I2C_MASTER_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentI2CMaster4Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CMaster5Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_I2C_MASTER_5_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_I2C_MASTER_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentI2CMaster5Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}
