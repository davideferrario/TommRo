
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusSPIMaster.h"

#include "bus/common/tommRoCHwTemplateBusCommon.h"

#include "bus/env/tommRoCHwTemplateBusEnvironmentSPIMaster.h"

#include "bus/common/spi/master/tommRoCHwTemplateBusCommonSPIMaster.h"

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

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMasterSetProp(
        const   tommRoC_hw_template_bus_spi_master_prop_enum_t          property,
        const   tommRoC_hw_template_bus_spi_master_enum_t               bus,
        const   void*                                           const   propValuePtr) {

    TOMMROC_ASSERT_NOT_NULL(propValuePtr);

#if defined (__TOMMROC_HW_TEMPLATE_BUS_SPI_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

    return tommRoCHwTemplateBusEnvironmentSPIMasterSetProp(property, bus, propValuePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(property);
    TOMMROC_UTIL_UNUSED_PARAM(bus);
    TOMMROC_UTIL_UNUSED_PARAM(propValuePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMaster0Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_SPI_MASTER_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentSPIMaster0Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMaster1Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_SPI_MASTER_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentSPIMaster1Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMaster2Start(tommRoC_hw_bus_t* const busHandlePtr){

#if defined (__TOMMROC_HW_USE_SPI_MASTER_2_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_SPI_MASTER_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentSPIMaster2Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMaster3Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_3_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_SPI_MASTER_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentSPIMaster3Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMaster4Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_4_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_SPI_MASTER_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentSPIMaster4Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPIMaster5Start(tommRoC_hw_bus_t* const busHandlePtr) {

#if defined (__TOMMROC_HW_USE_SPI_MASTER_5_TEMPLATE__)

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    return tommRoCHwTemplateBusCommonStart(
            TOMMRO_C_HW_BUS_SPI_MASTER_BUS_TYPE,
            tommRoCHwTemplateBusEnvironmentSPIMaster5Start,
            &cbFunct,
            busHandlePtr);
#else
    TOMMROC_UTIL_UNUSED_PARAM(busHandlePtr);
    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}
