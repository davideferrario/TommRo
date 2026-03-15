
#ifndef TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_DEF_H_
#define TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_DEF_H_

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
 * Author
 * TommRo Software Department
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwErr.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// NOTE: these are used to check externally the correctness of the size of tommRoCMw structures
#define TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_SYS_MUTEX_SIZE_BYTE     (52)
#define TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_SYS_SEM_SIZE_BYTE       (32)
#define TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_SYS_MBOX_SIZE_BYTE      (112)
#define TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_SYS_THREAD_SIZE_BYTE    (188)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_esp32_lwesp_mutex_create_funct_t)(void* mutexPtr);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_esp32_lwesp_mutex_destroy_funct_t)(void* mutexPtr);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_esp32_lwesp_mutex_lock_funct_t)(void* mutexPtr);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_esp32_lwesp_mutex_unlock_funct_t)(void* mutexPtr);

typedef struct {

    tommRoC_hw_devices_comm_esp32_lwesp_mutex_create_funct_t    createRecursive;
    tommRoC_hw_devices_comm_esp32_lwesp_mutex_destroy_funct_t   destroy;
    tommRoC_hw_devices_comm_esp32_lwesp_mutex_lock_funct_t      lock;
    tommRoC_hw_devices_comm_esp32_lwesp_mutex_unlock_funct_t    unlock;

} tommRoC_hw_devices_comm_esp32_lwesp_mutex_functs_t;

#define __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_mutex_functs_t__    \
{                                                                       \
    /* .createRecursive */  NULL,                                       \
    /* .destroy */          NULL,                                       \
    /* .lock */             NULL,                                       \
    /* .unlock */           NULL,                                       \
}

typedef struct {

    uint32_t mutexSizeByte;
    tommRoC_hw_devices_comm_esp32_lwesp_mutex_functs_t functs;

} tommRoC_hw_devices_comm_esp32_lwesp_mutex_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_mutex_config_t__                        \
{                                                                                           \
    /* .mutexSizeByte */    0,                                                              \
    /* .functs */           __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_mutex_functs_t__,   \
}


typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_esp32_lwesp_sem_create_funct_t)(void* semPtr, uint8_t cnt);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_esp32_lwesp_sem_destroy_funct_t)(void* semPtr);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_esp32_lwesp_sem_wait_funct_t)(void* semPtr, uint32_t timeout);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_esp32_lwesp_sem_release_funct_t)(void* semPtr);

typedef struct {

    tommRoC_hw_devices_comm_esp32_lwesp_sem_create_funct_t  create;
    tommRoC_hw_devices_comm_esp32_lwesp_sem_destroy_funct_t destroy;
    tommRoC_hw_devices_comm_esp32_lwesp_sem_wait_funct_t    wait;
    tommRoC_hw_devices_comm_esp32_lwesp_sem_release_funct_t release;

} tommRoC_hw_devices_comm_esp32_lwesp_sem_functs_t;

#define __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_sem_functs_t__  \
{                                                                   \
    /* .create */   NULL,                                           \
    /* .destroy */  NULL,                                           \
    /* .wait */     NULL,                                           \
    /* .release */  NULL,                                           \
}

typedef struct {

    uint32_t semSizeByte;
    tommRoC_hw_devices_comm_esp32_lwesp_sem_functs_t functs;

} tommRoC_hw_devices_comm_esp32_lwesp_sem_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_sem_config_t__                  \
{                                                                                   \
    /* .semSizeByte */  0,                                                          \
    /* .functs */       __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_sem_functs_t__, \
}


typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_esp32_lwesp_mbox_create_funct_t)(void* mboxPtr, uint32_t size);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_esp32_lwesp_mbox_destroy_funct_t)(void* mboxPtr);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_esp32_lwesp_mbox_put_funct_t)(void* mboxPtr, void* dataPtr);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_esp32_lwesp_mbox_get_funct_t)(void* mboxPtr, void** dataPtr, uint32_t timeout);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_esp32_lwesp_mbox_putnow_funct_t)(void* mboxPtr, void* dataPtr);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_esp32_lwesp_mbox_getnow_funct_t)(void* mboxPtr, void** dataPtr);

typedef struct {

    tommRoC_hw_devices_comm_esp32_lwesp_mbox_create_funct_t     create;
    tommRoC_hw_devices_comm_esp32_lwesp_mbox_destroy_funct_t    destroy;
    tommRoC_hw_devices_comm_esp32_lwesp_mbox_put_funct_t        put;
    tommRoC_hw_devices_comm_esp32_lwesp_mbox_get_funct_t        get;
    tommRoC_hw_devices_comm_esp32_lwesp_mbox_putnow_funct_t     putnow;
    tommRoC_hw_devices_comm_esp32_lwesp_mbox_getnow_funct_t     getnow;

} tommRoC_hw_devices_comm_esp32_lwesp_mbox_functs_t;

#define __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_mbox_functs_t__ \
{                                                                   \
    /* .create */   NULL,                                           \
    /* .destroy */  NULL,                                           \
    /* .put */      NULL,                                           \
    /* .get */      NULL,                                           \
    /* .putnow */   NULL,                                           \
    /* .getnow */   NULL,                                           \
}

typedef struct {

    uint32_t mboxSizeByte;
    tommRoC_hw_devices_comm_esp32_lwesp_mbox_functs_t functs;

} tommRoC_hw_devices_comm_esp32_lwesp_mbox_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_mbox_config_t__                     \
{                                                                                       \
    /* .mboxSizeByte */ 0,                                                              \
    /* .functs */       __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_mbox_functs_t__,    \
}

typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_esp32_lwesp_thread_create_funct_t)(void* threadPtr, const char* threadNamePtr, void(*threadMain)(void*), void* const threadArgPtr, uint32_t threadStackSize, uint32_t threadPriority);
typedef tommRoC_hw_err_enum_t (*tommRoC_hw_devices_comm_esp32_lwesp_thread_terminate_funct_t)(void* threadPtr);

typedef struct {

    tommRoC_hw_devices_comm_esp32_lwesp_thread_create_funct_t       create;
    tommRoC_hw_devices_comm_esp32_lwesp_thread_terminate_funct_t    terminate;

} tommRoC_hw_devices_comm_esp32_lwesp_thread_functs_t;

#define __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_thread_functs_t__   \
{                                                                       \
    /* .create */       NULL,                                           \
    /* .terminate */    NULL,                                           \
}

typedef struct {

    uint32_t threadSizeByte;
    tommRoC_hw_devices_comm_esp32_lwesp_thread_functs_t functs;

} tommRoC_hw_devices_comm_esp32_lwesp_thread_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_thread_config_t__                       \
{                                                                                           \
    /* .threadSizeByte */   0,                                                              \
    /* .functs */           __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_thread_functs_t__,  \
}


typedef struct {

    tommRoC_hw_devices_comm_esp32_lwesp_mutex_config_t  mutexCfg;
    tommRoC_hw_devices_comm_esp32_lwesp_sem_config_t    semCfg;
    tommRoC_hw_devices_comm_esp32_lwesp_mbox_config_t   mboxCfg;
    tommRoC_hw_devices_comm_esp32_lwesp_thread_config_t threadCfg;

} tommRoC_hw_devices_comm_esp32_lwesp_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_config_t__                          \
{                                                                                       \
    /* .mutexCfg */     __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_mutex_config_t__,   \
    /* .semCfg */       __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_sem_config_t__,     \
    /* .mboxCfg */      __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_mbox_config_t__,    \
    /* .threadCfg */    __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_thread_config_t__,  \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
