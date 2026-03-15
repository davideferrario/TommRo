
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusSPIMasterSwMode1.h"

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

void tommRoCHwTemplateBusSPIMasterSwMode1WriteByte(
        const   uint8_t                                                     data,
        const   tommRoC_hw_template_bus_spi_master_sw_base_gpio_t*  const   spiMasterSwBaseGpioPtr) {

    uint8_t mask;

    for (mask = SPI_MASTER_SW_BASE_START_MASK_BIT; mask != 0; mask >>= 1) {

        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(spiMasterSwBaseGpioPtr->clkHigh());

        tommRoCHwTemplateBusSPIMasterSwBaseGPIOOutputBit(
                data,
                mask,
                spiMasterSwBaseGpioPtr->mosiHigh,
                spiMasterSwBaseGpioPtr->mosiLow);

        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayUsec(spiMasterSwBaseGpioPtr->baseDelayUsec));

        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(spiMasterSwBaseGpioPtr->clkLow());
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayUsec(spiMasterSwBaseGpioPtr->baseDelayUsec));
    }
}

void tommRoCHwTemplateBusSPIMasterSwMode1WriteByteNoDelay(
        const   uint8_t                                                     data,
        const   tommRoC_hw_template_bus_spi_master_sw_base_gpio_t*  const   spiMasterSwBaseGpioPtr) {

    uint8_t mask;

    for (mask = SPI_MASTER_SW_BASE_START_MASK_BIT; mask != 0; mask >>= 1) {

        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(spiMasterSwBaseGpioPtr->clkHigh());

        tommRoCHwTemplateBusSPIMasterSwBaseGPIOOutputBit(
                data,
                mask,
                spiMasterSwBaseGpioPtr->mosiHigh,
                spiMasterSwBaseGpioPtr->mosiLow);

        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(spiMasterSwBaseGpioPtr->clkLow());
    }
}

uint8_t tommRoCHwTemplateBusSPIMasterSwMode1ReadByte(
        const   tommRoC_hw_template_bus_spi_master_sw_base_gpio_t*  const   spiMasterSwBaseGpioPtr) {

    uint8_t mask;
    uint8_t result = 0;

    for (mask = SPI_MASTER_SW_BASE_START_MASK_BIT; mask != 0; mask >>= 1) {

        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(spiMasterSwBaseGpioPtr->clkHigh());

        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(spiMasterSwBaseGpioPtr->mosiLow());
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayUsec(spiMasterSwBaseGpioPtr->baseDelayUsec));

        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(spiMasterSwBaseGpioPtr->clkLow());
        TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsDelayUsec(spiMasterSwBaseGpioPtr->baseDelayUsec));

        if (TOMMRO_C_UTIL_HIGH_LEVEL == spiMasterSwBaseGpioPtr->misoStatus()) {
            result |= mask;
        }
    }

    return result;
}

uint8_t tommRoCHwTemplateBusSPIMasterSwMode1ReadByteNoDelay(
        const   tommRoC_hw_template_bus_spi_master_sw_base_gpio_t*  const   spiMasterSwBaseGpioPtr) {

    uint8_t mask;
    uint8_t result = 0;

    for (mask = SPI_MASTER_SW_BASE_START_MASK_BIT; mask != 0; mask >>= 1) {

        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(spiMasterSwBaseGpioPtr->clkHigh());

        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(spiMasterSwBaseGpioPtr->mosiLow());

        TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(spiMasterSwBaseGpioPtr->clkLow());

        if (TOMMRO_C_UTIL_HIGH_LEVEL == spiMasterSwBaseGpioPtr->misoStatus()) {
            result |= mask;
        }
    }

    return result;
}
