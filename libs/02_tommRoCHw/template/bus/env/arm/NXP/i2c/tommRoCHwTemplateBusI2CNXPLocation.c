
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusI2CNXPLocation.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__)
#include "bus/env/arm/NXP/i2c/MK22/tommRoCHwTemplateBusI2CMK22Location.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)
#include "bus/env/arm/NXP/i2c/MKWx1Z/tommRoCHwTemplateBusI2CMKWx1ZLocation.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__)
#include "bus/env/arm/NXP/i2c/QN908XC/tommRoCHwTemplateBusI2CQN908XCLocation.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
#include "bus/env/arm/NXP/i2c/MKE02Z4/tommRoCHwTemplateBusI2CMKE02Z4Location.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define __CHECK_LOCATION__(I2C, I2C_TYPE, LOCATION)                                                                 \
        do {                                                                                                        \
            if ((TOMMROC_HW_TEMPLATE_BUS_ ## I2C_TYPE == i2c) && (TOMMROC_HW_TEMPLATE_ ## LOCATION == location)) {  \
                                                                                                                    \
                locationConfigPtr->clockName                = I2C ## _ ## LOCATION ## _CLOCK_NAME;                  \
                locationConfigPtr->gpioSDAPort              = I2C ## _ ## LOCATION ## _SDA_PORT;                    \
                locationConfigPtr->gpioSDAPin               = I2C ## _ ## LOCATION ## _SDA_PIN;                     \
                locationConfigPtr->gpioSDAPortMux           = I2C ## _ ## LOCATION ## _SDA_PORT_MUX;                \
                locationConfigPtr->gpioSCLPort              = I2C ## _ ## LOCATION ## _SCL_PORT;                    \
                locationConfigPtr->gpioSCLPin               = I2C ## _ ## LOCATION ## _SCL_PIN;                     \
                locationConfigPtr->gpioSCLPortMux           = I2C ## _ ## LOCATION ## _SCL_PORT_MUX;                \
                                                                                                                    \
                locationConfigPtr->gpioSDAGpio              = I2C ## _ ## LOCATION ## _SDA_GPIO;                    \
                locationConfigPtr->gpioSCLGpio              = I2C ## _ ## LOCATION ## _SCL_GPIO;                    \
                                                                                                                    \
                return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
            }                                                                                                       \
        } while (0)

#elif (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)
#define __CHECK_LOCATION__(I2C, I2C_TYPE, LOCATION)                                                                 \
        do {                                                                                                        \
            if ((TOMMROC_HW_TEMPLATE_BUS_ ## I2C_TYPE == i2c) && (TOMMROC_HW_TEMPLATE_ ## LOCATION == location)) {  \
                                                                                                                    \
                locationConfigPtr->clockName                = I2C ## _ ## LOCATION ## _CLOCK_NAME;                  \
                locationConfigPtr->sdaPortIdx               = I2C ## _ ## LOCATION ## _SDA_PORT_IDX;                \
                locationConfigPtr->sdaPin                   = I2C ## _ ## LOCATION ## _SDA_PIN;                     \
                locationConfigPtr->sdaIOCONFunc             = I2C ## _ ## LOCATION ## _SDA_IOCON_FUNC;              \
                locationConfigPtr->sclPortIdx               = I2C ## _ ## LOCATION ## _SCL_PORT_IDX;                \
                locationConfigPtr->sclPin                   = I2C ## _ ## LOCATION ## _SCL_PIN;                     \
                locationConfigPtr->sclIOCONFunc             = I2C ## _ ## LOCATION ## _SCL_IOCON_FUNC;              \
                                                                                                                    \
                locationConfigPtr->gpioSDAGpio              = I2C ## _ ## LOCATION ## _SDA_GPIO;                    \
                locationConfigPtr->gpioSCLGpio              = I2C ## _ ## LOCATION ## _SCL_GPIO;                    \
                                                                                                                    \
                return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
            }                                                                                                       \
        } while (0)

#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
#define __CHECK_LOCATION__(I2C, I2C_TYPE, LOCATION)                                                                 \
        do {                                                                                                        \
            if ((TOMMROC_HW_TEMPLATE_BUS_ ## I2C_TYPE == i2c) && (TOMMROC_HW_TEMPLATE_ ## LOCATION == location)) {  \
                                                                                                                    \
                locationConfigPtr->clockName                = I2C ## _ ## LOCATION ## _CLOCK_NAME;                  \
                locationConfigPtr->portSetPinSelectNeeded   = I2C ## _ ## LOCATION ## _PORT_SET_PIN_SELECT_NEEDED;  \
                locationConfigPtr->portModule               = I2C ## _ ## LOCATION ## _PORT_MODULE;                 \
                locationConfigPtr->portPinSelect            = I2C ## _ ## LOCATION ## _PORT_PIN_SELECT;             \
                                                                                                                    \
                locationConfigPtr->gpioSDAPort              = I2C ## _ ## LOCATION ## _SDA_PORT;                    \
                locationConfigPtr->gpioSDAPin               = I2C ## _ ## LOCATION ## _SDA_PIN;                     \
                locationConfigPtr->gpioSCLPort              = I2C ## _ ## LOCATION ## _SCL_PORT;                    \
                locationConfigPtr->gpioSCLPin               = I2C ## _ ## LOCATION ## _SCL_PIN;                     \
                                                                                                                    \
                return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
            }                                                                                                       \
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

static tommRoC_hw_err_enum_t _set_gpio_pin_i2c_master(
        const   tommRoC_hw_template_bus_i2c_master_enum_t               i2c,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_i2c_nxp_location_t*     const   locationConfigPtr) {

    // To avoid warning if no one is used
    TOMMROC_UTIL_UNUSED_PARAM(i2c);
    TOMMROC_UTIL_UNUSED_PARAM(location);
    TOMMROC_UTIL_UNUSED_PARAM(locationConfigPtr);


#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
#if defined (I2C_0_LOCATION_0_CLOCK_NAME)
    __CHECK_LOCATION__(I2C_0, I2C_MASTER_0, LOCATION_0);
#endif
#if defined (I2C_0_LOCATION_1_CLOCK_NAME)
    __CHECK_LOCATION__(I2C_0, I2C_MASTER_0, LOCATION_1);
#endif
#if defined (I2C_0_LOCATION_2_CLOCK_NAME)
    __CHECK_LOCATION__(I2C_0, I2C_MASTER_0, LOCATION_2);
#endif
#if defined (I2C_0_LOCATION_3_CLOCK_NAME)
    __CHECK_LOCATION__(I2C_0, I2C_MASTER_0, LOCATION_3);
#endif
#endif


#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
#if defined (I2C_1_LOCATION_0_CLOCK_NAME)
    __CHECK_LOCATION__(I2C_1, I2C_MASTER_1, LOCATION_0);
#endif
#if defined (I2C_1_LOCATION_1_CLOCK_NAME)
    __CHECK_LOCATION__(I2C_1, I2C_MASTER_1, LOCATION_1);
#endif
#if defined (I2C_1_LOCATION_2_CLOCK_NAME)
    __CHECK_LOCATION__(I2C_1, I2C_MASTER_1, LOCATION_2);
#endif
#if defined (I2C_1_LOCATION_3_CLOCK_NAME)
    __CHECK_LOCATION__(I2C_1, I2C_MASTER_1, LOCATION_3);
#endif
#endif


    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_gpio_pin_i2c_slave(
        const   tommRoC_hw_template_bus_i2c_slave_enum_t                i2c,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_i2c_nxp_location_t*     const   locationConfigPtr) {

    // To avoid warning if no one is used
    TOMMROC_UTIL_UNUSED_PARAM(i2c);
    TOMMROC_UTIL_UNUSED_PARAM(location);
    TOMMROC_UTIL_UNUSED_PARAM(locationConfigPtr);


#if defined (__TOMMROC_HW_USE_I2C_SLAVE_0_TEMPLATE__)
#if defined (I2C_0_LOCATION_0_CLOCK_NAME)
    __CHECK_LOCATION__(I2C_0, I2C_SLAVE_0, LOCATION_0);
#endif
#if defined (I2C_0_LOCATION_1_CLOCK_NAME)
    __CHECK_LOCATION__(I2C_0, I2C_SLAVE_0, LOCATION_1);
#endif
#if defined (I2C_0_LOCATION_2_CLOCK_NAME)
    __CHECK_LOCATION__(I2C_0, I2C_SLAVE_0, LOCATION_2);
#endif
#if defined (I2C_0_LOCATION_3_CLOCK_NAME)
    __CHECK_LOCATION__(I2C_0, I2C_SLAVE_0, LOCATION_3);
#endif
#endif


#if defined (__TOMMROC_HW_USE_I2C_SLAVE_1_TEMPLATE__)
#if defined (I2C_1_LOCATION_0_CLOCK_NAME)
    __CHECK_LOCATION__(I2C_1, I2C_SLAVE_1, LOCATION_0);
#endif
#if defined (I2C_1_LOCATION_1_CLOCK_NAME)
    __CHECK_LOCATION__(I2C_1, I2C_SLAVE_1, LOCATION_1);
#endif
#if defined (I2C_1_LOCATION_2_CLOCK_NAME)
    __CHECK_LOCATION__(I2C_1, I2C_SLAVE_1, LOCATION_2);
#endif
#if defined (I2C_1_LOCATION_3_CLOCK_NAME)
    __CHECK_LOCATION__(I2C_1, I2C_SLAVE_1, LOCATION_3);
#endif
#endif


    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNXPLocationGetMaster(
        const   tommRoC_hw_template_bus_i2c_master_enum_t               i2c,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_i2c_nxp_location_t*     const   locationConfigPtr) {

    TOMMROC_ASSERT_NOT_NULL(locationConfigPtr);

    return _set_gpio_pin_i2c_master(i2c, location, locationConfigPtr);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CNXPLocationGetSlave(
        const   tommRoC_hw_template_bus_i2c_slave_enum_t                i2c,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_i2c_nxp_location_t*     const   locationConfigPtr) {

    TOMMROC_ASSERT_NOT_NULL(locationConfigPtr);

    return _set_gpio_pin_i2c_slave(i2c, location, locationConfigPtr);
}

#endif

#endif
