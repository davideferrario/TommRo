
#if defined (__TOMMROC_MW_USE_TIMER_CMSIS_V1_RTOS_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOS_CMSIS_RTOS_TimerCb.h"

#include "rtos/cmsisRTOS/V1/common/compatibility/tommRoCMwTemplateRTOS_CMSIS_RTOS_Compatibility.h"

#if defined (__TOMMROC_MW_ARM_CMSIS_RTOS_EXTERNAL_IS_USED__)
#include "rtos/cmsisRTOS/V1/common/critical/tommRoCMwTemplateRTOS_CMSIS_RTOS_Critical.h"
#endif

#include "TOMMROC.h"

#include "TOMMROCMwTemplate.h"

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

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_TimerCb_Create(
        const   uint32_t                                periodMsec,
        const   tommRoC_mw_timer_type_enum_t            type,
        const   tommRoC_mw_timer_cb_funct_t             cbFunctPtr,
                void*                           const   inputTimerPtr) {
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_TimerCb_Destroy(
                void*                           const   inputTimerPtr) {

    tommRoC_mw_template_timer_t* timerPtr;
    osStatus res;

    timerPtr = (tommRoC_mw_template_timer_t*) inputTimerPtr;

    res = osTimerDelete(timerPtr->osTimerId);

    if (__CMSIS_RTOS_TIMER_DELETE_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_TimerCb_Start(
                void*                           const   inputTimerPtr) {

    tommRoC_mw_template_timer_t* timerPtr;
    osStatus res;

    timerPtr = (tommRoC_mw_template_timer_t*) inputTimerPtr;

    res = osTimerStart(timerPtr->osTimerId);

    if (__CMSIS_RTOS_TIMER_START_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOS_CMSIS_RTOS_TimerCb_Stop(
                void*                           const   inputTimerPtr) {

    tommRoC_mw_template_timer_t* timerPtr;
    osStatus res;

    timerPtr = (tommRoC_mw_template_timer_t*) inputTimerPtr;

    res = osTimerStop(timerPtr->osTimerId);

    if (__CMSIS_RTOS_TIMER_STOP_SUCCESS_RESULT__ != res) {
        return TOMMRO_C_MW_LOW_LEVEL_ERR;
    }

    return TOMMRO_C_MW_ERR_SUCCESS;
}

#endif
