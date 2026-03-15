
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSEventU32NotGuarded.h"

#if defined (__TOMMROC_MW_EVENT_TEMPLATE_IS_USED__)
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
static uint32_t _used_event_bitmask = 0;
static uint8_t _max_event_amount = 0;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_mw_err_enum_t _reset_status(void) {

    TOMMROC_ASSERT_EQUALS(_used_event_bitmask, 0);

    _used_event_bitmask = 0;
    _max_event_amount   = 0;

    return TOMMRO_C_MW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSEventU32NotGuardedStart(const uint8_t maxEventAmount) {

    TOMMROC_ASSERT_LESS_OR_EQUALS_THAN(maxEventAmount, TOMMROC_UNIT_MEASURE_BYTE_TO_BIT(sizeof(uint32_t)));

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_reset_status());

    _max_event_amount = maxEventAmount;

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSEventU32NotGuardedStop(void) {

    TOMMROC_MW_ERR_IF_TOMMROC_MW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_reset_status());

    return TOMMRO_C_MW_ERR_SUCCESS;
}

uint32_t tommRoCMwTemplateRTOSEventU32NotGuardedGetFirstAvailable(void) {

    uint8_t idx;

    if (_max_event_amount == tommRoCMathCountBitsSet(_used_event_bitmask)) {
        return TOMMROC_MW_TEMPLATE_RTOS_EVENT_U32_NOT_GUARDED_NOT_AVAILABLE_EVENT;
    }

    for (idx = 0; idx < TOMMROC_UNIT_MEASURE_BYTE_TO_BIT(sizeof(_used_event_bitmask)); ++idx) {

        if (TOMMRO_C_MATH_LOW_LEVEL == tommRoCMathBitTest(_used_event_bitmask, idx)) {

            _used_event_bitmask = tommRoCMathBitSet(_used_event_bitmask, idx);

            return (uint32_t) tommRoCMathBitSet(0, idx);
        }
    }

    return TOMMROC_MW_TEMPLATE_RTOS_EVENT_U32_NOT_GUARDED_NOT_AVAILABLE_EVENT;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSEventU32NotGuardedDestroy(const uint32_t event) {

    if (1 != tommRoCMathCountBitsSet(_used_event_bitmask & event)) {
        return TOMMRO_C_MW_PARAM_ERR;
    }

    _used_event_bitmask &= ~event;

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
