
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusI2CSlave.h"

#include "bus/common/tommRoCHwTemplateBusCommon.h"

#include "bus/env/tommRoCHwTemplateBusEnvironmentI2CSlave.h"

#include "bus/common/i2c/slave/tommRoCHwTemplateBusCommonI2CSlave.h"

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

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSlaveSetProp(
        const   tommRoC_hw_template_bus_i2c_slave_prop_enum_t           property,
        const   tommRoC_hw_template_bus_i2c_slave_enum_t                bus,
        const   void*                                           const   propValuePtr) {

    TOMMROC_ASSERT_NOT_NULL(propValuePtr);

#if defined (__TOMMROC_HW_AT_LEAST_ONE_I2C_SLAVE_TEMPLATE_IS_USED__)

    return tommRoCHwTemplateBusEnvironmentI2CSlaveSetProp(property, bus, propValuePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(property);
    TOMMROC_UTIL_UNUSED_PARAM(bus);
    TOMMROC_UTIL_UNUSED_PARAM(propValuePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSlave0Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr) {

#if defined (__TOMMROC_HW_USE_I2C_SLAVE_0_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_I2C_SLAVE_BUS_TYPE,
            guardPtr,
            tommRoCHwTemplateBusEnvironmentI2CSlave0Start,
            &cbFunct,
            busHandlePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif

}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSlave1Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr) {

#if defined (__TOMMROC_HW_USE_I2C_SLAVE_1_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_I2C_SLAVE_BUS_TYPE,
            guardPtr,
            tommRoCHwTemplateBusEnvironmentI2CSlave1Start,
            &cbFunct,
            busHandlePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif

}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSlave2Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr) {

#if defined (__TOMMROC_HW_USE_I2C_SLAVE_2_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_I2C_SLAVE_BUS_TYPE,
            guardPtr,
            tommRoCHwTemplateBusEnvironmentI2CSlave2Start,
            &cbFunct,
            busHandlePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif

}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSlave3Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr) {

#if defined (__TOMMROC_HW_USE_I2C_SLAVE_3_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_I2C_SLAVE_BUS_TYPE,
            guardPtr,
            tommRoCHwTemplateBusEnvironmentI2CSlave3Start,
            &cbFunct,
            busHandlePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif

}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSlave4Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr) {

#if defined (__TOMMROC_HW_USE_I2C_SLAVE_4_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_I2C_SLAVE_BUS_TYPE,
            guardPtr,
            tommRoCHwTemplateBusEnvironmentI2CSlave4Start,
            &cbFunct,
            busHandlePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif

}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSlave5Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr) {

#if defined (__TOMMROC_HW_USE_I2C_SLAVE_5_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_I2C_SLAVE_BUS_TYPE,
            guardPtr,
            tommRoCHwTemplateBusEnvironmentI2CSlave5Start,
            &cbFunct,
            busHandlePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif

}
