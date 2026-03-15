
#ifndef TOMMROC_HW_NET_LWIP_DEF_H_
#define TOMMROC_HW_NET_LWIP_DEF_H_

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

// NOTE: include Hw Devices Comm ESP32LWEsp because they share some objects for LwIP.
#include "devices/comm/ESP32LWEsp/tommRoCHwDevicesCommESP32LWEspDEF.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// NOTE: re-typedef all Hw Devices Comm ESP32LWEsp objects because they share some objects for LwIP.

// NOTE: these are used to check externally the correctness of the size of tommRoCMw structures
#define TOMMROC_HW_NET_LWIP_SYS_MUTEX_SIZE_BYTE     (TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_SYS_MUTEX_SIZE_BYTE)
#define TOMMROC_HW_NET_LWIP_SYS_SEM_SIZE_BYTE       (TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_SYS_SEM_SIZE_BYTE)
#define TOMMROC_HW_NET_LWIP_SYS_MBOX_SIZE_BYTE      (TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_SYS_MBOX_SIZE_BYTE)
#define TOMMROC_HW_NET_LWIP_SYS_THREAD_SIZE_BYTE    (TOMMROC_HW_DEVICES_COMM_ESP32_LWESP_SYS_THREAD_SIZE_BYTE)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Mutex
typedef tommRoC_hw_devices_comm_esp32_lwesp_mutex_create_funct_t    tommRoC_hw_net_lwip_mutex_create_funct_t;
typedef tommRoC_hw_devices_comm_esp32_lwesp_mutex_destroy_funct_t   tommRoC_hw_net_lwip_mutex_destroy_funct_t;
typedef tommRoC_hw_devices_comm_esp32_lwesp_mutex_lock_funct_t      tommRoC_hw_net_lwip_mutex_lock_funct_t;
typedef tommRoC_hw_devices_comm_esp32_lwesp_mutex_unlock_funct_t    tommRoC_hw_net_lwip_mutex_unlock_funct_t;

typedef tommRoC_hw_devices_comm_esp32_lwesp_mutex_functs_t tommRoC_hw_net_lwip_mutex_functs_t;
#define __EMPTY_tommRoC_hw_net_lwip_mutex_functs_t__ __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_mutex_functs_t__
typedef tommRoC_hw_devices_comm_esp32_lwesp_mutex_config_t tommRoC_hw_net_lwip_mutex_config_t;
#define __EMPTY_tommRoC_hw_net_lwip_mutex_config_t__ __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_mutex_config_t__


// Semaphore
typedef tommRoC_hw_devices_comm_esp32_lwesp_sem_create_funct_t  tommRoC_hw_net_lwip_sem_create_funct_t;
typedef tommRoC_hw_devices_comm_esp32_lwesp_sem_destroy_funct_t tommRoC_hw_net_lwip_sem_destroy_funct_t;
typedef tommRoC_hw_devices_comm_esp32_lwesp_sem_wait_funct_t    tommRoC_hw_net_lwip_sem_wait_funct_t;
typedef tommRoC_hw_devices_comm_esp32_lwesp_sem_release_funct_t tommRoC_hw_net_lwip_sem_release_funct_t;

typedef tommRoC_hw_devices_comm_esp32_lwesp_sem_functs_t    tommRoC_hw_net_lwip_sem_functs_t;
#define __EMPTY_tommRoC_hw_net_lwip_sem_functs_t__ __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_sem_functs_t__
typedef tommRoC_hw_devices_comm_esp32_lwesp_sem_config_t tommRoC_hw_net_lwip_sem_config_t;
#define __EMPTY_tommRoC_hw_net_lwip_sem_config_t__ __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_sem_config_t__


// MBox
typedef tommRoC_hw_devices_comm_esp32_lwesp_mbox_create_funct_t     tommRoC_hw_net_lwip_mbox_create_funct_t;
typedef tommRoC_hw_devices_comm_esp32_lwesp_mbox_destroy_funct_t    tommRoC_hw_net_lwip_mbox_destroy_funct_t;
typedef tommRoC_hw_devices_comm_esp32_lwesp_mbox_put_funct_t        tommRoC_hw_net_lwip_mbox_put_funct_t;
typedef tommRoC_hw_devices_comm_esp32_lwesp_mbox_get_funct_t        tommRoC_hw_net_lwip_mbox_get_funct_t;
typedef tommRoC_hw_devices_comm_esp32_lwesp_mbox_putnow_funct_t     tommRoC_hw_net_lwip_mbox_putnow_funct_t;
typedef tommRoC_hw_devices_comm_esp32_lwesp_mbox_getnow_funct_t     tommRoC_hw_net_lwip_mbox_getnow_funct_t;

typedef tommRoC_hw_devices_comm_esp32_lwesp_mbox_functs_t tommRoC_hw_net_lwip_mbox_functs_t;
#define __EMPTY_tommRoC_hw_net_lwip_mbox_functs_t__ __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_mbox_functs_t__
typedef tommRoC_hw_devices_comm_esp32_lwesp_mbox_config_t tommRoC_hw_net_lwip_mbox_config_t;
#define __EMPTY_tommRoC_hw_net_lwip_mbox_config_t__ __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_mbox_config_t__

typedef tommRoC_hw_devices_comm_esp32_lwesp_thread_create_funct_t       tommRoC_hw_net_lwip_thread_create_funct_t;
typedef tommRoC_hw_devices_comm_esp32_lwesp_thread_terminate_funct_t    tommRoC_hw_net_lwip_thread_terminate_funct_t;

typedef tommRoC_hw_devices_comm_esp32_lwesp_thread_functs_t tommRoC_hw_net_lwip_thread_functs_t;
#define __EMPTY_tommRoC_hw_net_lwip_thread_functs_t__ __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_thread_functs_t__
typedef tommRoC_hw_devices_comm_esp32_lwesp_thread_config_t tommRoC_hw_net_lwip_thread_config_t;
#define __EMPTY_tommRoC_hw_net_lwip_thread_config_t__ __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_thread_config_t__


// Global configuration
typedef tommRoC_hw_devices_comm_esp32_lwesp_config_t tommRoC_hw_net_lwip_config_t;
#define __EMPTY_tommRoC_hw_net_lwip_config_t__ __EMPTY_tommRoC_hw_devices_comm_esp32_lwesp_config_t__

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
