
#ifndef TOMMROC_ENV_H_
#define TOMMROC_ENV_H_

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
 * @defgroup tommRoCEnv tommRoCEnv
 *
 * @brief  TommRoC library environment module
 * @author TommRo Software Department
 *
 * This module is providing environment detect and functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * Environment used.
 */
#if (   (defined (__GNUC__) && defined (__arm__) && !defined (__linux__) && !defined (__aarch64__)) ||  \
        (defined (__IAR_SYSTEMS_ICC__))                                                             ||  \
        (defined (__CC_ARM)) || (defined (__ARMCC_VERSION))                                         ||  \
        (defined (__SES_ARM)) || (defined (__SES_RISCV)) || (defined (__CROSSWORKS_ARM)))
#define TOMMRO_C_ENV_ENVIRONMENT_IS_ARM

#if ((defined (__GNUC__)) && !(defined (__SES_ARM)) && !(defined (__CROSSWORKS_ARM)) && !(defined (__ARMCC_VERSION)) && !(defined (__CC_ARM)))
#define TOMMRO_C_ENV_ENVIRONMENT_IS_ARM_GCC
#elif (defined (__IAR_SYSTEMS_ICC__))
#define TOMMRO_C_ENV_ENVIRONMENT_IS_ARM_IAR
#elif ((defined (__CC_ARM)) || (defined (__ARMCC_VERSION)))
#define TOMMRO_C_ENV_ENVIRONMENT_IS_ARM_KEIL
#elif ((defined (__SES_ARM)) || (defined (__SES_RISCV)) || (defined (__CROSSWORKS_ARM)))
#define TOMMRO_C_ENV_ENVIRONMENT_IS_ARM_SES
#else
#error "Not supported ARM compiler"
#endif

#if (__ARM_ARCH == 6) && defined(__ARM_ARCH_6M__) && (__ARM_ARCH_6M__ == 1)
#define TOMMRO_C_ENV_ENVIRONMENT_IS_ARM_CORTEX_M0_M0PLUS
#elif (__ARM_ARCH == 7) && defined(__ARM_ARCH_7M__) && (__ARM_ARCH_7M__ == 1)
#define TOMMRO_C_ENV_ENVIRONMENT_IS_ARM_CORTEX_M3
#elif (__ARM_ARCH == 8)
#define TOMMRO_C_ENV_ENVIRONMENT_IS_ARM_CORTEX_M33
#elif (__ARM_ARCH == 7) && defined(__ARM_ARCH_7EM__) && (__ARM_ARCH_7EM__ == 1)
#define TOMMRO_C_ENV_ENVIRONMENT_IS_ARM_CORTEX_M4
#endif

#elif defined (__GNUC__) && (defined (__XTENSA__) || defined (__riscv) || defined (ESP_PLATFORM))
#define TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32

#if defined (__XTENSA__)
#define TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32_XTENSA_GCC
#elif defined (__riscv)
#define TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32_RISCV_GCC
#endif

#elif (defined (__GNUC__) && defined (__arm__) && defined (__linux__)) || (defined (__GNUC__) && defined (__aarch64__) && defined (__linux__))
#define TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX
#if defined (__GNUC__) && defined (__arm__) && defined (__linux__)
#define TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX_AARCH32
#elif defined (__GNUC__) && defined (__aarch64__) && defined (__linux__)
#define TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX_AARCH64
#endif

#elif defined (__GNUC__) && !defined (__arm__) && !defined (__aarch64__) && defined (__linux__)
#define TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX

#elif defined (__GNUC__) && !defined (__arm__) && !defined (__linux__)
#define TOMMRO_C_ENV_ENVIRONMENT_IS_WIN

#elif defined (__XC8)
#define TOMMRO_C_ENV_ENVIRONMENT_IS_XC8

#elif defined (__XC16)
#define TOMMRO_C_ENV_ENVIRONMENT_IS_XC16

#elif defined (__XC32)
#define TOMMRO_C_ENV_ENVIRONMENT_IS_XC32

#else
#error "Not supported compiler"
#endif


/**
 * Architecture size type.
 */
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)
#define TOMMRO_C_ENV_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)
#define TOMMRO_C_ENV_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX_AARCH32)
#define TOMMRO_C_ENV_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE
#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX_AARCH64)
#define TOMMRO_C_ENV_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE
#endif

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)
#define TOMMRO_C_ENV_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)
#define TOMMRO_C_ENV_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)
#define TOMMRO_C_ENV_ARCHITECTURE_IS_8_BIT_SIZE
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_IS_16_BIT_SIZE
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC16)
#define TOMMRO_C_ENV_ARCHITECTURE_IS_16_BIT_SIZE
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_IS_16_BIT_SIZE
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE

#elif defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC32)
#define TOMMRO_C_ENV_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE

#endif


/**
 * Architecture size.
 */
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_BYTE_SIZE                    (sizeof(int))
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_BIT_SIZE                     (TOMMRO_C_ENV_DATA_ARCHITECTURE_BYTE_SIZE * 8))
#if defined (TOMMRO_C_ENV_ARCHITECTURE_IS_8_BIT_SIZE)
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_BYTE_SIZE_AS_NUM             (1)
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_BIT_SIZE_AS_NUM              (8)
#elif defined (TOMMRO_C_ENV_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_BYTE_SIZE_AS_NUM             (2)
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_BIT_SIZE_AS_NUM              (16)
#elif defined (TOMMRO_C_ENV_ARCHITECTURE_IS_32_BIT_SIZE)
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_BYTE_SIZE_AS_NUM             (4)
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_BIT_SIZE_AS_NUM              (32)
#elif defined (TOMMRO_C_ENV_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_BYTE_SIZE_AS_NUM             (8)
#define TOMMRO_C_ENV_DATA_ARCHITECTURE_BIT_SIZE_AS_NUM              (64)
#else
#error "Not supported architecture"
#endif


/**
 * Memory architecture size.
 */
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE                  (sizeof(void*))
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BIT_SIZE                   (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE * 8))
#if defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_8_BIT_SIZE)
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE_AS_NUM           (1)
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BIT_SIZE_AS_NUM            (8)
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE_AS_NUM           (2)
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BIT_SIZE_AS_NUM            (16)
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE)
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE_AS_NUM           (4)
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BIT_SIZE_AS_NUM            (32)
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BYTE_SIZE_AS_NUM           (8)
#define TOMMRO_C_ENV_MEMORY_ARCHITECTURE_BIT_SIZE_AS_NUM            (64)
#else
#error "Not supported memory architecture"
#endif


/**
 * Flash memory architecture size.
 */
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_BYTE_SIZE            (sizeof(void (*)(void)))
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_BIT_SIZE             (TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_BYTE_SIZE * 8))
#if defined (TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_IS_8_BIT_SIZE)
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_BYTE_SIZE_AS_NUM     (1)
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_BIT_SIZE_AS_NUM      (8)
#elif defined (TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_BYTE_SIZE_AS_NUM     (2)
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_BIT_SIZE_AS_NUM      (16)
#elif defined (TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE)
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_BYTE_SIZE_AS_NUM     (4)
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_BIT_SIZE_AS_NUM      (32)
#elif defined (TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_BYTE_SIZE_AS_NUM     (8)
#define TOMMRO_C_ENV_FLASH_MEMORY_ARCHITECTURE_BIT_SIZE_AS_NUM      (64)
#else
#error "Not supported flash memory architecture"
#endif

/**
 * VA args supported by compiler
 */
#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARM)       ||  \
    defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ESP32)     ||  \
    defined (TOMMRO_C_ENV_ENVIRONMENT_IS_ARMLINUX)  ||  \
    defined (TOMMRO_C_ENV_ENVIRONMENT_IS_LINUX)     ||  \
    defined (TOMMRO_C_ENV_ENVIRONMENT_IS_WIN)

#define TOMMRO_C_ENV_VA_ARGS_SUPPORTED_BY_COMPILER
#endif


/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC environment property.
typedef enum {

    /**
     * Is environment multitasking.
     *
     * Available:   get/set.
     * Notes:       propValuePtr has to be bool*
     */
     TOMMROC_ENV_IS_MULTITASKING_PROP = 0,

     /**
      * Is environment little endian.
      * NOTE: if environment is not little endian, then it is big endian.
      *
      * uint32_t x = 1;
      *
      * Little endian                   Big endian
      *
      * higher memory                   higher memory
      * ----->                          ----->
      * +----+----+----+----+           +----+----+----+----+
      * |0x01|0x00|0x00|0x00|           |0x00|0x00|0x00|0x01|
      * +----+----+----+----+           +----+----+----+----+
      * ^                               ^
      * |                               |
      * &x                              &x
      *
      * Available:   get.
      * Notes:       propValuePtr has to be bool*
      */
     TOMMROC_ENV_IS_LITTLE_ENDIAN_PROP,

} tommRoC_env_prop_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Get a prop.
 *
 * param[in]        property                property.
 * param[out]       propValuePtr            output property value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCEnvGetProp(
        const   tommRoC_env_prop_enum_t         property,
                void*                   const   propValuePtr);

/**
 * Set a prop.
 *
 * param[in]        property                property.
 * param[in]        propValuePtr            property value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCEnvSetProp(
        const   tommRoC_env_prop_enum_t         property,
        const   void*                   const   propValuePtr);

/**
 * @}
 */

#endif
