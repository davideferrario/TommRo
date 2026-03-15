
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusI2CSiLabsLocation.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_SILABS_IS_USED__)

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_EFM32G_IS_USED__)
#include "bus/env/arm/SiLabs/i2c/EFM32G/tommRoCHwTemplateBusI2CEFM32GLocation.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_EFM32_EFM32GG_IS_USED__)
#include "bus/env/arm/SiLabs/i2c/EFM32GG/tommRoCHwTemplateBusI2CEFM32GGLocation.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_EFR32_IS_USED__)
#include "bus/env/arm/SiLabs/i2c/EFR32/tommRoCHwTemplateBusI2CEFR32Location.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/

#if defined (_I2C_ROUTE_LOCATION_MASK)
#define __LOCATION_ENUM_ERROR__                 ((uint32_t) -1)

#define __CHECK_LOCATION__(I2C, I2C_TYPE, LOCATION)                                                                     \
        do {                                                                                                            \
            if ((TOMMROC_HW_TEMPLATE_BUS_ ## I2C_TYPE == i2c) && (TOMMROC_HW_TEMPLATE_ ## LOCATION == location)) {      \
                                                                                                                        \
                locationConfigPtr->gpioSDAPort      = I2C ## _ ## LOCATION ## _SDA_PORT;                                \
                locationConfigPtr->gpioSDAPin       = I2C ## _ ## LOCATION ## _SDA_PIN;                                 \
                locationConfigPtr->gpioSCLPort      = I2C ## _ ## LOCATION ## _SCL_PORT;                                \
                locationConfigPtr->gpioSCLPin       = I2C ## _ ## LOCATION ## _SCL_PIN;                                 \
                                                                                                                        \
                return TOMMRO_C_HW_ERR_SUCCESS;                                                                         \
            }                                                                                                           \
        } while (0)
#endif

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/

#if defined (_I2C_ROUTE_LOCATION_MASK)
static uint32_t _convert_i2c_location(
        const   tommRoC_hw_template_bus_location_enum_t location) {

    switch (location) {

#if defined (I2C_ROUTE_LOCATION_LOC0)
    case TOMMROC_HW_TEMPLATE_LOCATION_0:    return I2C_ROUTE_LOCATION_LOC0;
#endif
#if defined (I2C_ROUTE_LOCATION_LOC1)
    case TOMMROC_HW_TEMPLATE_LOCATION_1:    return I2C_ROUTE_LOCATION_LOC1;
#endif
#if defined (I2C_ROUTE_LOCATION_LOC2)
    case TOMMROC_HW_TEMPLATE_LOCATION_2:    return I2C_ROUTE_LOCATION_LOC2;
#endif
#if defined (I2C_ROUTE_LOCATION_LOC3)
    case TOMMROC_HW_TEMPLATE_LOCATION_3:    return I2C_ROUTE_LOCATION_LOC3;
#endif
#if defined (I2C_ROUTE_LOCATION_LOC4)
    case TOMMROC_HW_TEMPLATE_LOCATION_4:    return I2C_ROUTE_LOCATION_LOC4;
#endif
#if defined (I2C_ROUTE_LOCATION_LOC5)
    case TOMMROC_HW_TEMPLATE_LOCATION_5:    return I2C_ROUTE_LOCATION_LOC5;
#endif
#if defined (I2C_ROUTE_LOCATION_LOC6)
    case TOMMROC_HW_TEMPLATE_LOCATION_6:    return I2C_ROUTE_LOCATION_LOC6;
#endif

    default:
        // If here, ERROR!!!
        TOMMROC_ASSERT_TRUE(false);
        break;
    }

    return __LOCATION_ENUM_ERROR__;
}

static tommRoC_hw_err_enum_t _set_gpio_pin_i2c_master(
        const   tommRoC_hw_template_bus_i2c_master_enum_t               i2c,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_i2c_silabs_location_t*  const   locationConfigPtr) {

    // To avoid warning if no one is used
    TOMMROC_UTIL_UNUSED_PARAM(i2c);
    TOMMROC_UTIL_UNUSED_PARAM(location);
    TOMMROC_UTIL_UNUSED_PARAM(locationConfigPtr);


#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
#if defined (I2C_0_LOCATION_0_SDA_PORT)
    __CHECK_LOCATION__(I2C_0, I2C_MASTER_0, LOCATION_0);
#endif
#if defined (I2C_0_LOCATION_1_SDA_PORT)
    __CHECK_LOCATION__(I2C_0, I2C_MASTER_0, LOCATION_1);
#endif
#if defined (I2C_0_LOCATION_2_SDA_PORT)
    __CHECK_LOCATION__(I2C_0, I2C_MASTER_0, LOCATION_2);
#endif
#if defined (I2C_0_LOCATION_3_SDA_PORT)
    __CHECK_LOCATION__(I2C_0, I2C_MASTER_0, LOCATION_3);
#endif
#if defined (I2C_0_LOCATION_4_SDA_PORT)
    __CHECK_LOCATION__(I2C_0, I2C_MASTER_0, LOCATION_4);
#endif
#if defined (I2C_0_LOCATION_5_SDA_PORT)
    __CHECK_LOCATION__(I2C_0, I2C_MASTER_0, LOCATION_5);
#endif
#if defined (I2C_0_LOCATION_6_SDA_PORT)
    __CHECK_LOCATION__(I2C_0, I2C_MASTER_0, LOCATION_6);
#endif
#endif


#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
#if defined (I2C_1_LOCATION_0_SDA_PORT)
    __CHECK_LOCATION__(I2C_1, I2C_MASTER_1, LOCATION_0);
#endif
#if defined (I2C_1_LOCATION_1_SDA_PORT)
    __CHECK_LOCATION__(I2C_1, I2C_MASTER_1, LOCATION_1);
#endif
#if defined (I2C_1_LOCATION_2_SDA_PORT)
    __CHECK_LOCATION__(I2C_1, I2C_MASTER_1, LOCATION_2);
#endif
#if defined (I2C_1_LOCATION_3_SDA_PORT)
    __CHECK_LOCATION__(I2C_1, I2C_MASTER_1, LOCATION_3);
#endif
#if defined (I2C_1_LOCATION_4_SDA_PORT)
    __CHECK_LOCATION__(I2C_1, I2C_MASTER_1, LOCATION_4);
#endif
#if defined (I2C_1_LOCATION_5_SDA_PORT)
    __CHECK_LOCATION__(I2C_1, I2C_MASTER_1, LOCATION_5);
#endif
#if defined (I2C_1_LOCATION_6_SDA_PORT)
    __CHECK_LOCATION__(I2C_1, I2C_MASTER_1, LOCATION_6);
#endif
#endif


    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_gpio_pin_i2c_slave(
        const   tommRoC_hw_template_bus_i2c_slave_enum_t                i2c,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_i2c_silabs_location_t*  const   locationConfigPtr) {

    // To avoid warning if no one is used
    TOMMROC_UTIL_UNUSED_PARAM(i2c);
    TOMMROC_UTIL_UNUSED_PARAM(location);
    TOMMROC_UTIL_UNUSED_PARAM(locationConfigPtr);


#if defined (__TOMMROC_HW_USE_I2C_SLAVE_0_TEMPLATE__)
#if defined (I2C_0_LOCATION_0_SDA_PORT)
    __CHECK_LOCATION__(I2C_0, I2C_SLAVE_0, LOCATION_0);
#endif
#if defined (I2C_0_LOCATION_1_SDA_PORT)
    __CHECK_LOCATION__(I2C_0, I2C_SLAVE_0, LOCATION_1);
#endif
#if defined (I2C_0_LOCATION_2_SDA_PORT)
    __CHECK_LOCATION__(I2C_0, I2C_SLAVE_0, LOCATION_2);
#endif
#if defined (I2C_0_LOCATION_3_SDA_PORT)
    __CHECK_LOCATION__(I2C_0, I2C_SLAVE_0, LOCATION_3);
#endif
#if defined (I2C_0_LOCATION_4_SDA_PORT)
    __CHECK_LOCATION__(I2C_0, I2C_SLAVE_0, LOCATION_4);
#endif
#if defined (I2C_0_LOCATION_5_SDA_PORT)
    __CHECK_LOCATION__(I2C_0, I2C_SLAVE_0, LOCATION_5);
#endif
#if defined (I2C_0_LOCATION_6_SDA_PORT)
    __CHECK_LOCATION__(I2C_0, I2C_SLAVE_0, LOCATION_6);
#endif
#endif


#if defined (__TOMMROC_HW_USE_I2C_SLAVE_1_TEMPLATE__)
#if defined (I2C_1_LOCATION_0_SDA_PORT)
    __CHECK_LOCATION__(I2C_1, I2C_SLAVE_1, LOCATION_0);
#endif
#if defined (I2C_1_LOCATION_1_SDA_PORT)
    __CHECK_LOCATION__(I2C_1, I2C_SLAVE_1, LOCATION_1);
#endif
#if defined (I2C_1_LOCATION_2_SDA_PORT)
    __CHECK_LOCATION__(I2C_1, I2C_SLAVE_1, LOCATION_2);
#endif
#if defined (I2C_1_LOCATION_3_SDA_PORT)
    __CHECK_LOCATION__(I2C_1, I2C_SLAVE_1, LOCATION_3);
#endif
#if defined (I2C_1_LOCATION_4_SDA_PORT)
    __CHECK_LOCATION__(I2C_1, I2C_SLAVE_1, LOCATION_4);
#endif
#if defined (I2C_1_LOCATION_5_SDA_PORT)
    __CHECK_LOCATION__(I2C_1, I2C_SLAVE_1, LOCATION_5);
#endif
#if defined (I2C_1_LOCATION_6_SDA_PORT)
    __CHECK_LOCATION__(I2C_1, I2C_SLAVE_1, LOCATION_6);
#endif
#endif


    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSiLabsLocationGetMaster(
        const   tommRoC_hw_template_bus_i2c_master_enum_t               i2c,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_i2c_silabs_location_t*  const   locationConfigPtr) {

#if defined (_I2C_ROUTE_LOCATION_MASK)

    TOMMROC_ASSERT_NOT_NULL(locationConfigPtr);

    locationConfigPtr->locationU32 = _convert_i2c_location(location);

    TOMMROC_ASSERT_NOT_EQUALS(locationConfigPtr->locationU32, __LOCATION_ENUM_ERROR__);

    return _set_gpio_pin_i2c_master(i2c, location, locationConfigPtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(i2c);
    TOMMROC_UTIL_UNUSED_PARAM(location);
    TOMMROC_UTIL_UNUSED_PARAM(locationConfigPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CSiLabsLocationGetSlave(
        const   tommRoC_hw_template_bus_i2c_slave_enum_t                i2c,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_i2c_silabs_location_t*  const   locationConfigPtr) {

#if defined (_I2C_ROUTE_LOCATION_MASK)
    TOMMROC_ASSERT_NOT_NULL(locationConfigPtr);

    locationConfigPtr->locationU32 = _convert_i2c_location(location);

    TOMMROC_ASSERT_NOT_EQUALS(locationConfigPtr->locationU32, __LOCATION_ENUM_ERROR__);

    return _set_gpio_pin_i2c_slave(i2c, location, locationConfigPtr);
#else

    TOMMROC_UTIL_UNUSED_PARAM(i2c);
    TOMMROC_UTIL_UNUSED_PARAM(location);
    TOMMROC_UTIL_UNUSED_PARAM(locationConfigPtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
#endif
}

#endif

#endif
