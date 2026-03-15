
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateNetSNTPHandler.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/
#define __POWER_ON_TIMEOUT_MSEC__   (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(10))
#define __HANDLE_TIMEOUT_MSEC__     (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(1))

#define __CHECK_SNTP_PERIOD_MSEC__  (TOMMROC_TIMER_HRS_TO_mSEC_TIMEOUT(12))

#define __SNTP_SERVER_IP_ADD_1__    (129)
#define __SNTP_SERVER_IP_ADD_2__    (6)
#define __SNTP_SERVER_IP_ADD_3__    (15)
#define __SNTP_SERVER_IP_ADD_4__    (30)
#define __SNTP_SERVER_HOST_NAME__   "time-c-g.nist.gov"

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
typedef enum {

    START_POWER_ON_TIMEOUT_FSM_STATUS = 0,
    WAIT_FOR_POWER_ON_TIMEOUT_EXPIRED_FSM_STATUS,
    HANDLE_FSM_STATUS,
    START_HANDLE_TIMEOUT_FSM_STATUS,
    WAIT_FOR_HANDLE_TIMEOUT_EXPIRED_FSM_STATUS,

} __sntp_FSM_status_enum_t__;

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_DEBUG_ENABLE__)
static const char __DEBUG_OBJ_ID__[] = "hwTempSNTPH";
#endif

static __sntp_FSM_status_enum_t__ _status = START_POWER_ON_TIMEOUT_FSM_STATUS;

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_hw_err_enum_t _SNTP_ip_add(uint32_t* const timestampPtr) {

    tommRoC_hw_comm_ip_v4_add_t iPv4Add;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwCommIPv4ItfInit(__SNTP_SERVER_IP_ADD_1__, __SNTP_SERVER_IP_ADD_2__, __SNTP_SERVER_IP_ADD_3__, __SNTP_SERVER_IP_ADD_4__, &iPv4Add));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetSNTPSync(&iPv4Add, timestampPtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _SNTP_host(uint32_t* const timestampPtr) {

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(tommRoCHwNetSNTPSyncHost(__SNTP_SERVER_HOST_NAME__, timestampPtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _SNTP(uint32_t* const timestampPtr) {

    bool isGetHostByNameInit;

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwNetDNSIsInitGetHostByNameEnv(&isGetHostByNameInit));

    return (isGetHostByNameInit) ? (_SNTP_host(timestampPtr)) : (_SNTP_ip_add(timestampPtr));
}

static void _SNTP_update_mng(void) {

    static tommRoC_timer_t timer = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_timer_t);

    uint32_t timestamp;
    tommRoC_date_time_t dateTimeOnEnter;
    tommRoC_date_time_t dateTimeOnExit;

    if (tommRoCTimerIsStarted(&timer) && (TOMMRO_C_TIMER_NOT_EXPIRED_ERR == tommRoCTimerIsExpired(&timer))) {
        return;
    }

    if (TOMMRO_C_HW_ERR_SUCCESS != _SNTP(&timestamp)) {
        return;
    }

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, __CHECK_SNTP_PERIOD_MSEC__));

    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsGetDateTime(&dateTimeOnEnter));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsSetTimestamp(timestamp));
    TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCOsGetDateTime(&dateTimeOnExit));

    TOMMROC_DEBUG_DATE_TIME(TOMMRO_C_DEBUG_D_LEVEL, "dateOnEnter: ", dateTimeOnEnter);
    TOMMROC_DEBUG_DATE_TIME(TOMMRO_C_DEBUG_D_LEVEL, "dateOnExit:  ", dateTimeOnExit);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateNetSNTPHandlerRun(void) {

    static tommRoC_timer_t timer = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_timer_t);

    bool isItfUp;
    bool isLinkUp;

    do { // Added to avoid "warning: unreachable code"
        switch (_status) {

        case START_POWER_ON_TIMEOUT_FSM_STATUS:
            // NOTE: delay a little bit before start thread to leave the time to setup all interface
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, __POWER_ON_TIMEOUT_MSEC__));
            _status = WAIT_FOR_POWER_ON_TIMEOUT_EXPIRED_FSM_STATUS;
            break;

        case WAIT_FOR_POWER_ON_TIMEOUT_EXPIRED_FSM_STATUS:
            if (TOMMRO_C_TIMER_EXPIRED_ERR == tommRoCTimerIsExpired(&timer)) {
                _status = HANDLE_FSM_STATUS;
            }
            break;

        case HANDLE_FSM_STATUS:
            TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwNetIsItfUp(&isItfUp));
            TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(tommRoCHwNetIsLinkUp(&isLinkUp));

            if (isItfUp && isLinkUp) {
                _SNTP_update_mng();
                _status = START_HANDLE_TIMEOUT_FSM_STATUS;
            }
            break;

        case START_HANDLE_TIMEOUT_FSM_STATUS:
            TOMMROC_ASSERT_TOMMROC_LIB_FUNCT_SUCCESS(tommRoCTimerStart(&timer, __HANDLE_TIMEOUT_MSEC__));
            _status = WAIT_FOR_HANDLE_TIMEOUT_EXPIRED_FSM_STATUS;
            break;

        case WAIT_FOR_HANDLE_TIMEOUT_EXPIRED_FSM_STATUS:
            if (TOMMRO_C_TIMER_EXPIRED_ERR == tommRoCTimerIsExpired(&timer)) {
                _status = HANDLE_FSM_STATUS;
            }
            break;


        default:
            // If here, ERROR!!!
            TOMMROC_ASSERT_TRUE(false);
            break;

        }
    } while (0);

    return TOMMRO_C_HW_ERR_SUCCESS;
}
