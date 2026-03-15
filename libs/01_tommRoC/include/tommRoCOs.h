
#ifndef TOMMROC_OS_H_
#define TOMMROC_OS_H_

/*
 *******************************************************************************
 * License
 * (C) Copyright 2017
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications according to the supply agreement.
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: this software is provided
 * "AS IS", with no express or implied warranties of any kind, including,
 * but not limited to, any implied warranties of merchantability or
 * fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Supplier will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 */

/**
 * @defgroup tommRoCOs tommRoCOs
 *
 * @brief  TommRoC library Os module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted delay, uptime, timestamp, calendar, critical, sleep functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCDateTime.h"
#include "tommRoCErr.h"
#include "tommRoCUtil.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC Os reset cause.
typedef enum {

    TOMMRO_C_OS_RESET_CAUSE_POWER_ON = 0,       // Power On reset.
    TOMMRO_C_OS_RESET_CAUSE_BROWN_DOWN,         // Brown down reset.
    TOMMRO_C_OS_RESET_CAUSE_EXTERNAL_PIN,       // External pin reset.
    TOMMRO_C_OS_RESET_CAUSE_WATCHDOG,           // Watch dog reset.
    TOMMRO_C_OS_RESET_CAUSE_LOCK_UP,            // Lock up reset.
    TOMMRO_C_OS_RESET_CAUSE_REBOOT,             // Reboot reset.
    TOMMRO_C_OS_RESET_CAUSE_CPU_SYSTEM,         // CPU system reset.
    TOMMRO_C_OS_RESET_CAUSE_WAKE_UP,            // Wake up reset.
    TOMMRO_C_OS_RESET_CAUSE_CPU_SOFTWARE,       // CPU software reset.
    TOMMRO_C_OS_RESET_CAUSE_LOW_POWER,          // Low power reset.
    TOMMRO_C_OS_RESET_CAUSE_OPTION_BYTE_LOADER, // Option byte loader reset.

    // NOTE: this is a low level error - not handled condition.
    TOMMRO_C_OS_RESET_CAUSE_UNKNOWN,            // Unknown cause reset.

} tommRoC_os_reset_cause_enum_t;

// tommRoC Os delay [msec] function type.
typedef tommRoC_err_enum_t (*tommRoC_os_delay_msec_funct_t)(const uint32_t);
// tommRoC Os delay [usec] function type.
typedef tommRoC_err_enum_t (*tommRoC_os_delay_usec_funct_t)(const uint32_t);
// tommRoC Os get upTime [msec] function type.
typedef uint32_t (*tommRoC_os_get_uptime_msec_funct_t)(void);
// tommRoC Os get upTime [usec] function type.
typedef uint32_t (*tommRoC_os_get_uptime_usec_funct_t)(void);
// tommRoC Os get hard clock function type.
typedef uint32_t (*tommRoC_os_get_hard_clock_funct_t)(void);

// tommRoC Os set timestamp function type.
typedef tommRoC_err_enum_t (*tommRoC_os_set_timestamp_funct_t)(const uint32_t);
// tommRoC Os get timestamp function type.
typedef uint32_t (*tommRoC_os_get_timestamp_funct_t)(void);

// tommRoC Os set date time function type.
typedef tommRoC_err_enum_t (*tommRoC_os_set_date_time_funct_t)(const tommRoC_date_time_t* const);
// tommRoC Os get date time function type.
typedef tommRoC_err_enum_t (*tommRoC_os_get_date_time_funct_t)(tommRoC_date_time_t* const);

// tommRoC Os enter critical function type.
typedef tommRoC_err_enum_t (*tommRoC_os_enter_critical_funct_t)(uint32_t* const specificDataPtr);
// tommRoC Os exit critical function type.
typedef tommRoC_err_enum_t (*tommRoC_os_exit_critical_funct_t)(uint32_t* const specificDataPtr);

// tommRoC Os is from ISR function type.
typedef tommRoC_err_enum_t (*tommRoC_os_is_from_isr_funct_t)(bool* const isFromISRPtr);

// tommRoC Os disable WDT function type.
typedef void (*tommRoC_os_disable_wdt_funct_t)(void);
// tommRoC Os enable WDT function type.
typedef void (*tommRoC_os_enable_wdt_funct_t)(void);

// tommRoC Os sleep for [msec] function type.
typedef tommRoC_err_enum_t (*tommRoC_os_sleep_for_msec_funct_t)(const uint32_t);

// tommRoC Os reboot function type.
typedef tommRoC_err_enum_t (*tommRoC_os_reboot_funct_t)(void);

// tommRoC Os get UUID function type.
typedef tommRoC_err_enum_t (*tommRoC_os_get_uuid_funct_t)(
                void*       const   uuidBufferPtr,
        const   uint8_t             uuidBufferSize,
                uint8_t*    const   uuidBufferLenPtr);

// tommRoC Os get/clear reset cause function type.
typedef tommRoC_os_reset_cause_enum_t (*tommRoC_os_reset_cause_funct_t)(void);
typedef tommRoC_err_enum_t (*tommRoC_os_clear_reset_cause_funct_t)(void);

// tommRoC Os extend delay [msec] function type.
typedef uint32_t (*tommRoC_os_extend_delay_msec_funct_t)(void);


// tommRoC Os timestamp function type.
typedef struct {

    tommRoC_os_set_timestamp_funct_t    setTimestamp;
    tommRoC_os_get_timestamp_funct_t    getTimestamp;
    uint16_t                            minValidYear;
    uint16_t                            maxValidYear;

} tommRoC_os_timestamp_funct_init_t;

// tommRoC Os date time function type.
typedef struct {

    tommRoC_os_set_date_time_funct_t    setDateTime;
    tommRoC_os_get_date_time_funct_t    getDateTime;
    uint16_t                            minValidYear;
    uint16_t                            maxValidYear;

} tommRoC_os_date_time_funct_init_t;

// tommRoC Os critical function type.
typedef struct {

    tommRoC_os_enter_critical_funct_t   enterCritical;
    tommRoC_os_exit_critical_funct_t    exitCritical;

} tommRoC_os_critical_funct_t;

// tommRoC Os WDT function type.
typedef struct {

    tommRoC_os_disable_wdt_funct_t      disableWDT;
    tommRoC_os_enable_wdt_funct_t       enableWDT;

} tommRoC_os_wdt_funct_t;


// Enumeration of tommRoC Os init resources.
typedef enum {

    /**
     * Os delay [msec] funct resource.
     *
     * initResourcePtr have to be tommRoC_os_delay_msec_funct_t.
     */
    TOMMRO_C_OS_DELAY_MSEC_FUNCT = 0,

    /**
     * Os delay [usec] funct resource.
     *
     * initResourcePtr have to be tommRoC_os_delay_usec_funct_t.
     */
    TOMMRO_C_OS_DELAY_USEC_FUNCT,

    /**
     * Os uptime [msec] funct resource.
     *
     * initResourcePtr have to be tommRoC_os_get_uptime_msec_funct_t.
     */
    TOMMRO_C_OS_UPTIME_MSEC_FUNCT,

    /**
     * Os uptime [usec] funct resource.
     *
     * initResourcePtr have to be tommRoC_os_get_uptime_usec_funct_t.
     */
    TOMMRO_C_OS_UPTIME_USEC_FUNCT,

    /**
     * Os hard clock funct resource.
     *
     * initResourcePtr have to be tommRoC_os_get_hard_clock_funct_t.
     */
    TOMMRO_C_OS_HARD_CLOCK_FUNCT,

    /**
     * Os timestamp funct resource.
     *
     * initResourcePtr have to be tommRoC_os_timestamp_funct_init_t*.
     */
    TOMMRO_C_OS_TIMESTAMP_FUNCT,

    /**
     * Os date time funct resource.
     *
     * initResourcePtr have to be tommRoC_os_date_time_funct_init_t*.
     */
    TOMMRO_C_OS_DATE_TIME_FUNCT,

    /**
     * Os critical funct resource.
     *
     * initResourcePtr have to be tommRoC_os_critical_funct_t*.
     */
    TOMMRO_C_OS_CRITICAL_FUNCT,

    /**
     * Os is from ISR funct resource.
     *
     * initResourcePtr have to be tommRoC_os_is_from_isr_funct_t*.
     */
    TOMMRO_C_OS_IS_FROM_ISR_FUNCT,

    /**
     * Os WDT funct resource.
     *
     * initResourcePtr have to be tommRoC_os_wdt_funct_t*.
     */
    TOMMRO_C_OS_WDT_FUNCT,

    /**
     * Os sleep for [msec] funct resource.
     *
     * initResourcePtr have to be tommRoC_os_sleep_for_msec_funct_t.
     */
    TOMMRO_C_OS_SLEEP_FOR_MSEC_FUNCT,

    /**
     * Os reboot funct resource.
     *
     * initResourcePtr have to be tommRoC_os_reboot_funct_t.
     */
    TOMMRO_C_OS_REBOOT_FUNCT,

    /**
     * Os get UUID funct resource.
     *
     * initResourcePtr have to be tommRoC_os_get_uuid_funct_t.
     */
    TOMMRO_C_OS_GET_UUID_FUNCT,

    /**
     * Os get reset cause funct resource.
     *
     * initResourcePtr have to be tommRoC_os_reset_cause_funct_t.
     */
    TOMMRO_C_OS_RESET_CAUSE_FUNCT,

    /**
     * Os clear reset cause funct resource.
     *
     * initResourcePtr have to be tommRoC_os_clear_reset_cause_funct_t.
     */
    TOMMRO_C_OS_CLEAR_RESET_CAUSE_FUNCT,

    /**
     * Os extend delay [msec] funct resource.
     *
     * initResourcePtr have to be tommRoC_os_extend_delay_msec_funct_t.
     */
    TOMMRO_C_OS_EXTEND_DELAY_MSEC_FUNCT,

} tommRoC_os_environment_resource_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Prepare single library Os environment.
 * NOTE: to be used for compiler (e.g.: XC8) that are not able to distinguish internal switch and generate recursive function error message.
 *
 * param[in]        initResourcePtr         pointer to environment resource init data.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsInitDelayMsec(const tommRoC_os_delay_msec_funct_t initResourcePtr);
tommRoC_err_enum_t tommRoCOsInitDelayUsec(const tommRoC_os_delay_usec_funct_t initResourcePtr);
tommRoC_err_enum_t tommRoCOsInitUptimeMsec(const tommRoC_os_get_uptime_msec_funct_t initResourcePtr);
tommRoC_err_enum_t tommRoCOsInitUptimeUsec(const tommRoC_os_get_uptime_usec_funct_t initResourcePtr);
tommRoC_err_enum_t tommRoCOsInitHardClock(const tommRoC_os_get_hard_clock_funct_t initResourcePtr);
tommRoC_err_enum_t tommRoCOsInitTimestamp(const tommRoC_os_timestamp_funct_init_t* const initResourcePtr);
tommRoC_err_enum_t tommRoCOsInitDateTime(const tommRoC_os_date_time_funct_init_t* const initResourcePtr);
tommRoC_err_enum_t tommRoCOsInitCritical(const tommRoC_os_critical_funct_t* const initResourcePtr);
tommRoC_err_enum_t tommRoCOsInitIsFromISR(const tommRoC_os_is_from_isr_funct_t initResourcePtr);
tommRoC_err_enum_t tommRoCOsInitWDT(const tommRoC_os_wdt_funct_t* const initResourcePtr);
tommRoC_err_enum_t tommRoCOsInitSleepForMsec(const tommRoC_os_sleep_for_msec_funct_t initResourcePtr);
tommRoC_err_enum_t tommRoCOsInitReboot(const tommRoC_os_reboot_funct_t initResourcePtr);
tommRoC_err_enum_t tommRoCOsInitGetUUID(const tommRoC_os_get_uuid_funct_t initResourcePtr);
tommRoC_err_enum_t tommRoCOsInitResetCause(const tommRoC_os_reset_cause_funct_t initResourcePtr);
tommRoC_err_enum_t tommRoCOsInitClearResetCause(const tommRoC_os_clear_reset_cause_funct_t initResourcePtr);
tommRoC_err_enum_t tommRoCOsInitExtendDelayMsec(const tommRoC_os_extend_delay_msec_funct_t initResourcePtr);

/**
 * Prepare library Os environment.
 *
 * param[in]        resource                Os init environment resource to set.
 * param[in]        initResourcePtr         pointer to environment resource init data.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsInitEnv(
        const   tommRoC_os_environment_resource_enum_t          resource,
        const   void*                                   const   initResourcePtr);

/**
 * Close library Os environment.
 *
 * param[in]        resource                Os init environment resource to set.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsCloseEnv(
        const   tommRoC_os_environment_resource_enum_t          resource);

/**
 * Check if library Os environment is init.
 *
 * param[in]        resource                Os init environment resource to check.
 * param[in]        isInitPtr               Is init boolean status.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsIsInitEnv(
        const   tommRoC_os_environment_resource_enum_t          resource,
                bool*                                   const   isInitPtr);


/**
 * Delay [msec].
 *
 * NOTE:
 * function does not test special case delay param zero. This MUST be made by higher level application function.
 * In case of NOT multitasking environment, function should return SUCCESS result immediately.
 * In case of multitasking environment, a task yield MUST be performed.
 *
 * param[in]        msec                    msec to delay.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsDelayMsec(const uint32_t msec);

/**
 * Delay [usec].
 *
 * NOTE: if delay param is zero, SUCCESS result is returned immediately.
 *
 * param[in]        usec                    nsec to delay.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsDelayUsec(const uint32_t usec);

/**
 * Get current execution (elapsed time since board power up) timestamp [msec].
 *
 * return uint32_t
 */
uint32_t tommRoCOsUptime(void);

/**
 * Get current execution (elapsed time since board power up) timestamp [usec].
 *
 * return uint32_t
 */
uint32_t tommRoCOsUptimeUsec(void);

/**
 * Get current CPU cycle counter value.
 *
 * return uint32_t
 */
uint32_t tommRoCOsHardClock(void);

/**
 * Set current timestamp [Unix timestamp format - seconds elapsed since UTC 01/01/1970 00:00:00].
 *
 * param[in]        timestamp               input timestamp.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsSetTimestamp(const uint32_t timestamp);

/**
 * Get current timestamp [Unix timestamp format - seconds elapsed since UTC 01/01/1970 00:00:00].
 *
 * return uint32_t
 */
uint32_t tommRoCOsGetTimestamp(void);

/**
 * Set current date time.
 *
 * param[in]        dateTimePtr             input date time pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsSetDateTime(const tommRoC_date_time_t* const dateTimePtr);

/**
 * Get current date time.
 *
 * param[out]       dateTimePtr             output date time pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsGetDateTime(tommRoC_date_time_t* const dateTimePtr);

/**
 * Enter critical region.
 * NOTE: usually the critical region is where all interrupts are disabled.
 *
 * param[in/out]    specificDataPtr         specific input/output data pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsEnterCritical(uint32_t* const specificDataPtr);

/**
 * Exit critical region.
 * NOTE: usually the critical region is where all interrupts are disabled.
 *
 * param[in/out]    specificDataPtr         specific input/output data pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsExitCritical(uint32_t* const specificDataPtr);

/**
 * Check if current execution is from ISR - Interrupt Service Routine.
 *
 * param[in/out]    isFromISRPtr            is from ISR boolean status pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsIsFromISR(bool* const isFromISRPtr);

/**
 * Disable WDT.
 * NOTE: some tommRoC libraries operation can need some time to compute. WDT will be disabled for the needed time.
 */
void tommRoCOsDisableWDT(void);

/**
 * Enable WDT.
 */
void tommRoCOsEnableWDT(void);

/**
 * Sleep (low power) CPU for [msec].
 * NOTE: only CPU is put in low power; no other output/devices will be init for low power.
 * NOTE: only wakeup for timeout is enabled; no other wakeup cause is active.
 * NOTE: if msec resolution is not available, an approximation in seconds is made.
 *
 * param[in]        msec                    msec to sleep for.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsSleepForMsec(const uint32_t msec);

/**
 * Reboot system.
 *
 * param[in]waitNoDebugmsec                 wait for no debug is pending.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsReboot(const tommRoC_util_enabled_status_enum_t waitNoDebug);

/**
 * Get minimum/maximum valid calendar year.
 *
 * return uint16_t
 */
uint16_t tommRoCOsGetCalendarMinValidYear(void);
uint16_t tommRoCOsGetCalendarMaxValidYear(void);

/**
 * Get UUID (universally unique identifier) of the device.
 *
 * param[in/out]        uuidBufferPtr       UUID buffer pointer.
 * param[in]            uuidBufferSize      UUID buffer size [byte].
 * param[out]           uuidBufferLenPtr    output UUID buffer length pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsGetUUID(
                void*       const   uuidBufferPtr,
        const   uint8_t             uuidBufferSize,
                uint8_t*    const   uuidBufferLenPtr);

/**
 * Get UUID (universally unique identifier) of the device as HEX string.
 * NOTE: default is upper case HEX string.
 *
 * param[in/out]        uuidStrPtr          UUID string buffer pointer.
 * param[in]            uuidStrSize         UUID string buffer size [byte].
 *                                          NOTE: in variable declaration, application must reserve 1 byte for '\0' character.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsGetUUIDAsStr(
                char*       const   uuidStrPtr,
        const   uint8_t             uuidStrSize);

/**
 * Get UUID (universally unique identifier) of the device as lower case HEX string.
 * NOTE: lower case HEX string.
 *
 * param[in/out]        uuidStrPtr          UUID string buffer pointer.
 * param[in]            uuidStrSize         UUID string buffer size [byte].
 *                                          NOTE: in variable declaration, application must reserve 1 byte for '\0' character.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsGetUUIDAsLowerCaseStr(
                char*       const   uuidStrPtr,
        const   uint8_t             uuidStrSize);

/**
 * Get the reset cause.
 *
 * return tommRoC_os_reset_cause_enum_t
 */
tommRoC_os_reset_cause_enum_t tommRoCOsResetCause(void);

/**
 * Get the reset cause as NULL terminated ('\0') string.
 *
 * return char*
 */
const char* tommRoCOsResetCauseAsStr(void);

/**
 * Clear the reset cause.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCOsClearResetCause(void);

/**
 * @}
 */

#endif
