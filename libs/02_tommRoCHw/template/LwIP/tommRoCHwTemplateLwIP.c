
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateLwIP.h"

#include "LwIP/mbox/tommRoCHwTemplateLwIPMBox.h"
#include "LwIP/mutex/tommRoCHwTemplateLwIPMutex.h"
#include "LwIP/sem/tommRoCHwTemplateLwIPSem.h"
#include "LwIP/thread/tommRoCHwTemplateLwIPThread.h"

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
TOMMROC_SCTA_LESS_OR_EQUALS_THAN(sizeof(tommRoC_mw_template_mutex_t),       TOMMROC_HW_NET_LWIP_SYS_MUTEX_SIZE_BYTE);
#endif
#if defined (__TOMMROC_MW_SEMAPHORE_TEMPLATE_IS_USED__)
TOMMROC_SCTA_LESS_OR_EQUALS_THAN(sizeof(tommRoC_mw_template_semaphore_t),   TOMMROC_HW_NET_LWIP_SYS_SEM_SIZE_BYTE);
#endif
#if defined (__TOMMROC_MW_QUEUE_TEMPLATE_IS_USED__)
TOMMROC_SCTA_LESS_OR_EQUALS_THAN(sizeof(tommRoC_mw_template_queue_t),       TOMMROC_HW_NET_LWIP_SYS_MBOX_SIZE_BYTE);
#endif
#if defined (__TOMMROC_MW_THREAD_TEMPLATE_IS_USED__)
TOMMROC_SCTA_LESS_OR_EQUALS_THAN(sizeof(tommRoC_mw_template_thread_t),      TOMMROC_HW_NET_LWIP_SYS_THREAD_SIZE_BYTE);
#endif

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_hw_err_enum_t _lwip_config(void) {

    tommRoC_hw_net_lwip_config_t config = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_hw_net_lwip_config_t);

    config.mutexCfg.mutexSizeByte           = tommRoCHwTemplateLwIPMutexEnvGetSize();
    config.mutexCfg.functs.createRecursive  = tommRoCHwTemplateLwIPMutexCreateRecursive;
    config.mutexCfg.functs.destroy          = tommRoCHwTemplateLwIPMutexDestroy;
    config.mutexCfg.functs.lock             = tommRoCHwTemplateLwIPMutexLock;
    config.mutexCfg.functs.unlock           = tommRoCHwTemplateLwIPMutexUnlock;

    config.semCfg.semSizeByte               = tommRoCHwTemplateLwIPSemEnvGetSize();
    config.semCfg.functs.create             = tommRoCHwTemplateLwIPSemCreate;
    config.semCfg.functs.destroy            = tommRoCHwTemplateLwIPSemDestroy;
    config.semCfg.functs.wait               = tommRoCHwTemplateLwIPSemWait;
    config.semCfg.functs.release            = tommRoCHwTemplateLwIPSemRelease;

    config.mboxCfg.mboxSizeByte             = tommRoCHwTemplateLwIPMBoxEnvGetSize();
    config.mboxCfg.functs.create            = tommRoCHwTemplateLwIPMBoxCreate;
    config.mboxCfg.functs.destroy           = tommRoCHwTemplateLwIPMBoxDestroy;
    config.mboxCfg.functs.put               = tommRoCHwTemplateLwIPMBoxPut;
    config.mboxCfg.functs.get               = tommRoCHwTemplateLwIPMBoxGet;
    config.mboxCfg.functs.putnow            = tommRoCHwTemplateLwIPMBoxPutnow;
    config.mboxCfg.functs.getnow            = tommRoCHwTemplateLwIPMBoxGetnow;

    config.threadCfg.threadSizeByte         = tommRoCHwTemplateLwIPThreadEnvGetSize();
    config.threadCfg.functs.create          = tommRoCHwTemplateLwIPThreadCreate;
    config.threadCfg.functs.terminate       = tommRoCHwTemplateLwIPThreadTerminate;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwNetLwIPConfig(
                    &config));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_hw_err_enum_t tommRoCHwTemplateLwIPInit(void) {

// NOTE: for LwIP, counting semaphores are mandatory.
#if !defined (__TOMMROC_MW_SEMAPHORE_COUNTING_SEMAPHORES_TEMPLATE_IS_USED__)
    return TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR;
#else

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            _lwip_config());

    return TOMMRO_C_HW_ERR_SUCCESS;
#endif
}
