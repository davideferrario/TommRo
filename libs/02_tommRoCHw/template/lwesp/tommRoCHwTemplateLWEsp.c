
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateLWEsp.h"

#include "lwesp/mbox/tommRoCHwTemplateLWEspMBox.h"
#include "lwesp/mutex/tommRoCHwTemplateLWEspMutex.h"
#include "lwesp/sem/tommRoCHwTemplateLWEspSem.h"
#include "lwesp/thread/tommRoCHwTemplateLWEspThread.h"

#include "TOMMROC.h"
#include "TOMMROCHw.h"

#include "TOMMROCMwTemplate.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/
#if defined (__TOMMROC_MW_MUTEX_TEMPLATE_IS_USED__)
TOMMROC_SCTA_LESS_OR_EQUALS_THAN(sizeof(tommRoC_mw_template_mutex_t),       TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_SYS_MUTEX_SIZE_BYTE);
#endif
#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
TOMMROC_SCTA_LESS_OR_EQUALS_THAN(sizeof(tommRoC_mw_template_semaphore_t),   TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_SYS_SEM_SIZE_BYTE);
#endif
#if defined (__TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__)
TOMMROC_SCTA_LESS_OR_EQUALS_THAN(sizeof(tommRoC_mw_template_queue_t),       TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_SYS_MBOX_SIZE_BYTE);
#endif
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
TOMMROC_SCTA_LESS_OR_EQUALS_THAN(sizeof(tommRoC_mw_template_thread_t),      TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_SYS_THREAD_SIZE_BYTE);
#endif

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_hw_err_enum_t _lwesp_start(
        const   tommRoC_hw_gpio_set_cb_t                        resetLow,
        const   tommRoC_hw_gpio_set_cb_t                        resetHigh,
        const   uint32_t                                        baudRate,
        const   tommRoC_hw_comm_hw_flow_control_enum_t          hwFlowControl,
                tommRoC_hw_bus_device_t*                const   busDevicePtr) {

    tommRoC_hw_devices_comm_esp32_lwesp_config_t config = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_hw_devices_comm_esp32_lwesp_config_t);

    config.mutexCfg.mutexSizeByte           = tommRoCHwTemplateLWEspMutexEnvGetSize();
    config.mutexCfg.functs.createRecursive  = tommRoCHwTemplateLWEspMutexCreateRecursive;
    config.mutexCfg.functs.destroy          = tommRoCHwTemplateLWEspMutexDestroy;
    config.mutexCfg.functs.lock             = tommRoCHwTemplateLWEspMutexLock;
    config.mutexCfg.functs.unlock           = tommRoCHwTemplateLWEspMutexUnlock;

    config.semCfg.semSizeByte               = tommRoCHwTemplateLWEspSemEnvGetSize();
    config.semCfg.functs.create             = tommRoCHwTemplateLWEspSemCreate;
    config.semCfg.functs.destroy            = tommRoCHwTemplateLWEspSemDestroy;
    config.semCfg.functs.wait               = tommRoCHwTemplateLWEspSemWait;
    config.semCfg.functs.release            = tommRoCHwTemplateLWEspSemRelease;

    config.mboxCfg.mboxSizeByte             = tommRoCHwTemplateLWEspMBoxEnvGetSize();
    config.mboxCfg.functs.create            = tommRoCHwTemplateLWEspMBoxCreate;
    config.mboxCfg.functs.destroy           = tommRoCHwTemplateLWEspMBoxDestroy;
    config.mboxCfg.functs.put               = tommRoCHwTemplateLWEspMBoxPut;
    config.mboxCfg.functs.get               = tommRoCHwTemplateLWEspMBoxGet;
    config.mboxCfg.functs.putnow            = tommRoCHwTemplateLWEspMBoxPutnow;
    config.mboxCfg.functs.getnow            = tommRoCHwTemplateLWEspMBoxGetnow;

    config.threadCfg.threadSizeByte         = tommRoCHwTemplateLWEspThreadEnvGetSize();
    config.threadCfg.functs.create          = tommRoCHwTemplateLWEspThreadCreate;
    config.threadCfg.functs.terminate       = tommRoCHwTemplateLWEspThreadTerminate;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwDevicesCommESP32LWEspStart(
                    resetLow,
                    resetHigh,
                    baudRate,
                    hwFlowControl,
                    &config,
                    busDevicePtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateLWEspInit(
        const   tommRoC_hw_gpio_set_cb_t                        resetLow,
        const   tommRoC_hw_gpio_set_cb_t                        resetHigh,
        const   uint32_t                                        baudRate,
        const   tommRoC_hw_comm_hw_flow_control_enum_t          hwFlowControl,
        const   tommRoC_hw_bus_t*                       const   busHandlerPtr,
        const   tommRoC_guard_t*                        const   guardPtr,
                tommRoC_hw_bus_device_t*                const   busDevicePtr) {

    static tommRoC_hw_bus_device_specific_uart_t specificSlave;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwDevicesCommESP32LWEspInitUART(
                    busHandlerPtr,
                    guardPtr,
                    &specificSlave,
                    busDevicePtr));

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _lwesp_start(
                    resetLow,
                    resetHigh,
                    baudRate,
                    hwFlowControl,
                    busDevicePtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}
