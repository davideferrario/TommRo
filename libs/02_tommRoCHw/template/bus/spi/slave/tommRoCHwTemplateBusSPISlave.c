
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusSPISlave.h"

#include "bus/common/tommRoCHwTemplateBusCommon.h"

#include "bus/env/tommRoCHwTemplateBusEnvironmentSPISlave.h"

#include "bus/common/spi/slave/tommRoCHwTemplateBusCommonSPISlave.h"

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

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISlaveSetProp(
        const   tommRoC_hw_template_bus_spi_slave_prop_enum_t           property,
        const   tommRoC_hw_template_bus_spi_slave_enum_t                bus,
        const   void*                                           const   propValuePtr) {

    TOMMROC_ASSERT_NOT_NULL(propValuePtr);

#if defined (__TOMMROC_HW_AT_LEAST_ONE_SPI_SLAVE_TEMPLATE_IS_USED__)

    return tommRoCHwTemplateBusEnvironmentSPISlaveSetProp(property, bus, propValuePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(property);
    TOMMROC_UTIL_UNUSED_PARAM(bus);
    TOMMROC_UTIL_UNUSED_PARAM(propValuePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISlave0Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr) {

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_0_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_SPI_SLAVE_BUS_TYPE,
            guardPtr,
            tommRoCHwTemplateBusEnvironmentSPISlave0Start,
            &cbFunct,
            busHandlePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif

}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISlave1Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr) {

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_1_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_SPI_SLAVE_BUS_TYPE,
            guardPtr,
            tommRoCHwTemplateBusEnvironmentSPISlave1Start,
            &cbFunct,
            busHandlePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif

}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISlave2Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr) {

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_2_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_SPI_SLAVE_BUS_TYPE,
            guardPtr,
            tommRoCHwTemplateBusEnvironmentSPISlave2Start,
            &cbFunct,
            busHandlePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif

}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISlave3Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr) {

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_3_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_SPI_SLAVE_BUS_TYPE,
            guardPtr,
            tommRoCHwTemplateBusEnvironmentSPISlave3Start,
            &cbFunct,
            busHandlePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif

}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISlave4Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr) {

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_4_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_SPI_SLAVE_BUS_TYPE,
            guardPtr,
            tommRoCHwTemplateBusEnvironmentSPISlave4Start,
            &cbFunct,
            busHandlePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif

}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPISlave5Start(
        const   tommRoC_guard_t*    const   guardPtr,
                tommRoC_hw_bus_t*   const   busHandlePtr) {

#if defined (__TOMMROC_HW_USE_SPI_SLAVE_5_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_SPI_SLAVE_BUS_TYPE,
            guardPtr,
            tommRoCHwTemplateBusEnvironmentSPISlave5Start,
            &cbFunct,
            busHandlePtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(guardPtr);
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif

}
