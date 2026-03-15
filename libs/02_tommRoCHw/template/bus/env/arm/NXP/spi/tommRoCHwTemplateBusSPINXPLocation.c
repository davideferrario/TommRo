
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusSPINXPLocation.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_IS_USED__)

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MK22_IS_USED__)
#include "bus/env/arm/NXP/spi/MK22/tommRoCHwTemplateBusSPIMK22Location.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKWx1Z_IS_USED__)
#include "bus/env/arm/NXP/spi/MKWx1Z/tommRoCHwTemplateBusSPIMKWx1ZLocation.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_QN908XC_IS_USED__)
#include "bus/env/arm/NXP/spi/QN908XC/tommRoCHwTemplateBusSPIQN908XCLocation.h"
#endif

#if defined (__TOMMROC_TEMPLATE_ARM_NXP_MKE02Z4_IS_USED__)
#include "bus/env/arm/NXP/spi/MKE02Z4/tommRoCHwTemplateBusSPIMKE02Z4Location.h"
#endif

/*******************************************************************************
 * local defines
 ******************************************************************************/

#if defined (FSL_FEATURE_PORT_PCR_MUX_WIDTH) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
#define __CHECK_LOCATION__(SPI, SPI_TYPE, LOCATION)                                                                 \
        do {                                                                                                        \
            if ((TOMMROC_HW_TEMPLATE_BUS_ ## SPI_TYPE == spi) && (TOMMROC_HW_TEMPLATE_ ## LOCATION == location)) {  \
                                                                                                                    \
                locationConfigPtr->clockName                = SPI ## _ ## LOCATION ## _CLOCK_NAME;                  \
                locationConfigPtr->gpioSCKPort              = SPI ## _ ## LOCATION ## _SCK_PORT;                    \
                locationConfigPtr->gpioSCKPin               = SPI ## _ ## LOCATION ## _SCK_PIN;                     \
                locationConfigPtr->gpioSCKPortMux           = SPI ## _ ## LOCATION ## _SCK_PORT_MUX;                \
                locationConfigPtr->gpioMISOPort             = SPI ## _ ## LOCATION ## _MISO_PORT;                   \
                locationConfigPtr->gpioMISOPin              = SPI ## _ ## LOCATION ## _MISO_PIN;                    \
                locationConfigPtr->gpioMISOPortMux          = SPI ## _ ## LOCATION ## _MISO_PORT_MUX;               \
                locationConfigPtr->gpioMOSIPort             = SPI ## _ ## LOCATION ## _MOSI_PORT;                   \
                locationConfigPtr->gpioMOSIPin              = SPI ## _ ## LOCATION ## _MOSI_PIN;                    \
                locationConfigPtr->gpioMOSIPortMux          = SPI ## _ ## LOCATION ## _MOSI_PORT_MUX;               \
                                                                                                                    \
                locationConfigPtr->gpioSCKGpio              = SPI ## _ ## LOCATION ## _SCK_GPIO;                    \
                locationConfigPtr->gpioMISOGpio             = SPI ## _ ## LOCATION ## _MISO_GPIO;                   \
                locationConfigPtr->gpioMOSIGpio             = SPI ## _ ## LOCATION ## _MOSI_GPIO;                   \
                                                                                                                    \
                return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
            }                                                                                                       \
        } while (0)

#elif (defined (FSL_FEATURE_SOC_SYSCON_COUNT) && FSL_FEATURE_SOC_SYSCON_COUNT) || (defined (FSL_FEATURE_SOC_IOCON_COUNT) && FSL_FEATURE_SOC_IOCON_COUNT)
#define __CHECK_LOCATION__(SPI, SPI_TYPE, LOCATION)                                                                 \
        do {                                                                                                        \
            if ((TOMMROC_HW_TEMPLATE_BUS_ ## SPI_TYPE == spi) && (TOMMROC_HW_TEMPLATE_ ## LOCATION == location)) {  \
                                                                                                                    \
                locationConfigPtr->clockName                = SPI ## _ ## LOCATION ## _CLOCK_NAME;                  \
                locationConfigPtr->sckPortIdx               = SPI ## _ ## LOCATION ## _SCK_PORT_IDX;                \
                locationConfigPtr->sckPin                   = SPI ## _ ## LOCATION ## _SCK_PIN;                     \
                locationConfigPtr->sckIOCONFunc             = SPI ## _ ## LOCATION ## _SCK_IOCON_FUNC;              \
                locationConfigPtr->misoPortIdx              = SPI ## _ ## LOCATION ## _MISO_PORT_IDX;               \
                locationConfigPtr->misoPin                  = SPI ## _ ## LOCATION ## _MISO_PIN;                    \
                locationConfigPtr->misoIOCONFunc            = SPI ## _ ## LOCATION ## _MISO_IOCON_FUNC;             \
                locationConfigPtr->mosiPortIdx              = SPI ## _ ## LOCATION ## _MOSI_PORT_IDX;               \
                locationConfigPtr->mosiPin                  = SPI ## _ ## LOCATION ## _MOSI_PIN;                    \
                locationConfigPtr->mosiIOCONFunc            = SPI ## _ ## LOCATION ## _MOSI_IOCON_FUNC;             \
                                                                                                                    \
                locationConfigPtr->gpioSCKGpio              = SPI ## _ ## LOCATION ## _SCK_GPIO;                    \
                locationConfigPtr->gpioMISOGpio             = SPI ## _ ## LOCATION ## _MISO_GPIO;                   \
                locationConfigPtr->gpioMOSIGpio             = SPI ## _ ## LOCATION ## _MOSI_GPIO;                   \
                                                                                                                    \
                return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
            }                                                                                                       \
        } while (0)

#elif (MAKE_VERSION(2, 0, 1) == FSL_PORT_DRIVER_VERSION) || (MAKE_VERSION(2, 0, 2) == FSL_PORT_DRIVER_VERSION)
#define __CHECK_LOCATION__(SPI, SPI_TYPE, LOCATION)                                                                 \
        do {                                                                                                        \
            if ((TOMMROC_HW_TEMPLATE_BUS_ ## SPI_TYPE == spi) && (TOMMROC_HW_TEMPLATE_ ## LOCATION == location)) {  \
                                                                                                                    \
                locationConfigPtr->clockName                = SPI ## _ ## LOCATION ## _CLOCK_NAME;                  \
                locationConfigPtr->portSetPinSelectNeeded   = SPI ## _ ## LOCATION ## _PORT_SET_PIN_SELECT_NEEDED;  \
                locationConfigPtr->portModule               = SPI ## _ ## LOCATION ## _PORT_MODULE;                 \
                locationConfigPtr->portPinSelect            = SPI ## _ ## LOCATION ## _PORT_PIN_SELECT;             \
                                                                                                                    \
                locationConfigPtr->gpioSCKPort              = SPI ## _ ## LOCATION ## _SCK_PORT;                    \
                locationConfigPtr->gpioSCKPin               = SPI ## _ ## LOCATION ## _SCK_PIN;                     \
                locationConfigPtr->gpioMISOPort             = SPI ## _ ## LOCATION ## _MISO_PORT;                   \
                locationConfigPtr->gpioMISOPin              = SPI ## _ ## LOCATION ## _MISO_PIN;                    \
                locationConfigPtr->gpioMOSIPort             = SPI ## _ ## LOCATION ## _MOSI_PORT;                   \
                locationConfigPtr->gpioMOSIPin              = SPI ## _ ## LOCATION ## _MOSI_PIN;                    \
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

static tommRoC_hw_err_enum_t _set_gpio_pin_spi_master(
        const   tommRoC_hw_template_bus_spi_master_enum_t               spi,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_spi_nxp_location_t*     const   locationConfigPtr) {

    // To avoid warning if no one is used
    TOMMROC_UTIL_UNUSED_PARAM(spi);
    TOMMROC_UTIL_UNUSED_PARAM(location);
    TOMMROC_UTIL_UNUSED_PARAM(locationConfigPtr);


#if defined (__TOMMROC_HW_USE_SPI_MASTER_0_TEMPLATE__)
#if defined (SPI_0_LOCATION_0_CLOCK_NAME)
    __CHECK_LOCATION__(SPI_0, SPI_MASTER_0, LOCATION_0);
#endif
#if defined (SPI_0_LOCATION_1_CLOCK_NAME)
    __CHECK_LOCATION__(SPI_0, SPI_MASTER_0, LOCATION_1);
#endif
#if defined (SPI_0_LOCATION_2_CLOCK_NAME)
    __CHECK_LOCATION__(SPI_0, SPI_MASTER_0, LOCATION_2);
#endif
#if defined (SPI_0_LOCATION_3_CLOCK_NAME)
    __CHECK_LOCATION__(SPI_0, SPI_MASTER_0, LOCATION_3);
#endif
#endif


#if defined (__TOMMROC_HW_USE_SPI_MASTER_1_TEMPLATE__)
#if defined (SPI_1_LOCATION_0_CLOCK_NAME)
    __CHECK_LOCATION__(SPI_1, SPI_MASTER_1, LOCATION_0);
#endif
#if defined (SPI_1_LOCATION_1_CLOCK_NAME)
    __CHECK_LOCATION__(SPI_1, SPI_MASTER_1, LOCATION_1);
#endif
#if defined (SPI_1_LOCATION_2_CLOCK_NAME)
    __CHECK_LOCATION__(SPI_1, SPI_MASTER_1, LOCATION_2);
#endif
#if defined (SPI_1_LOCATION_3_CLOCK_NAME)
    __CHECK_LOCATION__(SPI_1, SPI_MASTER_1, LOCATION_3);
#endif
#endif


    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

static tommRoC_hw_err_enum_t _set_gpio_pin_spi_slave(
        const   tommRoC_hw_template_bus_spi_slave_enum_t                spi,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_spi_nxp_location_t*     const   locationConfigPtr) {

    // To avoid warning if no one is used
    TOMMROC_UTIL_UNUSED_PARAM(spi);
    TOMMROC_UTIL_UNUSED_PARAM(location);
    TOMMROC_UTIL_UNUSED_PARAM(locationConfigPtr);


#if defined (__TOMMROC_HW_USE_SPI_SLAVE_0_TEMPLATE__)
#if defined (SPI_0_LOCATION_0_CLOCK_NAME)
    __CHECK_LOCATION__(SPI_0, SPI_SLAVE_0, LOCATION_0);
#endif
#if defined (SPI_0_LOCATION_1_CLOCK_NAME)
    __CHECK_LOCATION__(SPI_0, SPI_SLAVE_0, LOCATION_1);
#endif
#if defined (SPI_0_LOCATION_2_CLOCK_NAME)
    __CHECK_LOCATION__(SPI_0, SPI_SLAVE_0, LOCATION_2);
#endif
#if defined (SPI_0_LOCATION_3_CLOCK_NAME)
    __CHECK_LOCATION__(SPI_0, SPI_SLAVE_0, LOCATION_3);
#endif
#endif


#if defined (__TOMMROC_HW_USE_SPI_SLAVE_1_TEMPLATE__)
#if defined (SPI_1_LOCATION_0_CLOCK_NAME)
    __CHECK_LOCATION__(SPI_1, SPI_SLAVE_1, LOCATION_0);
#endif
#if defined (SPI_1_LOCATION_1_CLOCK_NAME)
    __CHECK_LOCATION__(SPI_1, SPI_SLAVE_1, LOCATION_1);
#endif
#if defined (SPI_1_LOCATION_2_CLOCK_NAME)
    __CHECK_LOCATION__(SPI_1, SPI_SLAVE_1, LOCATION_2);
#endif
#if defined (SPI_1_LOCATION_3_CLOCK_NAME)
    __CHECK_LOCATION__(SPI_1, SPI_SLAVE_1, LOCATION_3);
#endif
#endif


    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPINXPLocationGetMaster(
        const   tommRoC_hw_template_bus_spi_master_enum_t               spi,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_spi_nxp_location_t*     const   locationConfigPtr) {

    TOMMROC_ASSERT_NOT_NULL(locationConfigPtr);

    return _set_gpio_pin_spi_master(spi, location, locationConfigPtr);
}

tommRoC_hw_err_enum_t tommRoCHwTemplateBusSPINXPLocationGetSlave(
        const   tommRoC_hw_template_bus_spi_slave_enum_t                spi,
        const   tommRoC_hw_template_bus_location_enum_t                 location,
                tommRoC_hw_template_bus_spi_nxp_location_t*     const   locationConfigPtr) {

    TOMMROC_ASSERT_NOT_NULL(locationConfigPtr);

    return _set_gpio_pin_spi_slave(spi, location, locationConfigPtr);
}

#endif

#endif
