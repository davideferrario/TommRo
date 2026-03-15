
#if defined (__TOMMROC_MW_USE_QUEUE_PTHREAD_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCMwTemplateRTOSQueue.h"

#include "rtos/pthread/queue/callback/tommRoCMwTemplateRTOS_Pthread_QueueCb.h"

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

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSQueueStart(void) {

    tommRoC_mw_queue_environment_init_t mwQueueInit = TOMMROC_UTIL_EMPTY_VARIABLE(tommRoC_mw_queue_environment_init_t);

    mwQueueInit.create          = tommRoCMwTemplateRTOS_Pthread_QueueCb_Create;
    mwQueueInit.put             = tommRoCMwTemplateRTOS_Pthread_QueueCb_Put;
    mwQueueInit.get             = tommRoCMwTemplateRTOS_Pthread_QueueCb_Get;
    mwQueueInit.insideAmount    = tommRoCMwTemplateRTOS_Pthread_QueueCb_InsideAmount;
    mwQueueInit.freeAmount      = tommRoCMwTemplateRTOS_Pthread_QueueCb_FreeAmount;
    mwQueueInit.destroy         = tommRoCMwTemplateRTOS_Pthread_QueueCb_Destroy;

    return tommRoCMwQueueEnvironmentInit(&mwQueueInit);
}

tommRoC_mw_err_enum_t tommRoCMwTemplateRTOSQueueStop(void) {

    return tommRoCMwQueueCloseEnvironment();
}

#endif
