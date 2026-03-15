
#ifndef TOMMROC_CRC_H_
#define TOMMROC_CRC_H_

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
 * @defgroup tommRoCCRC tommRoCCRC
 *
 * @brief  TommRoC library CRC module
 * @author TommRo Software Department
 *
 * This module is providing CRC8/CRC16/CRC32 functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

// XOR based CRC reset value
#define TOMMRO_C_CRC_XOR_BASED_RESET_VALUE              (0)

/******************* Standard polynomial CRC8 configuration */

#define TOMMRO_C_CRC_CRC8_CONFIG                        \
{                                                       \
    /* .polynomial */       0x07,                       \
    /* .initialValue */     0x00,                       \
    /* .finalXorValue */    0x00,                       \
    /* .inputReflected */   TOMMRO_C_CRC_NO_REFLECTED,  \
    /* .resultReflected */  TOMMRO_C_CRC_NO_REFLECTED,  \
}

#define TOMMRO_C_CRC_CRC8_CDMA2000_CONFIG               \
{                                                       \
    /* .polynomial */       0x9B,                       \
    /* .initialValue */     0xFF,                       \
    /* .finalXorValue */    0x00,                       \
    /* .inputReflected */   TOMMRO_C_CRC_NO_REFLECTED,  \
    /* .resultReflected */  TOMMRO_C_CRC_NO_REFLECTED,  \
}

#define TOMMRO_C_CRC_CRC8_ITU_CONFIG                    \
{                                                       \
    /* .polynomial */       0x07,                       \
    /* .initialValue */     0x00,                       \
    /* .finalXorValue */    0x55,                       \
    /* .inputReflected */   TOMMRO_C_CRC_NO_REFLECTED,  \
    /* .resultReflected */  TOMMRO_C_CRC_NO_REFLECTED,  \
}


/******************* Standard polynomial CRC16 configuration */

#define TOMMRO_C_CRC_CRC16_CCITT                        \
{                                                       \
    /* .polynomial */       0x1021,                     \
    /* .initialValue */     0xFFFF,                     \
    /* .finalXorValue */    0x0000,                     \
    /* .inputReflected */   TOMMRO_C_CRC_NO_REFLECTED,  \
    /* .resultReflected */  TOMMRO_C_CRC_NO_REFLECTED,  \
}

#define TOMMRO_C_CRC_CRC16_CCITT_ZERO                   \
{                                                       \
    /* .polynomial */       0x1021,                     \
    /* .initialValue */     0x0000,                     \
    /* .finalXorValue */    0x0000,                     \
    /* .inputReflected */   TOMMRO_C_CRC_NO_REFLECTED,  \
    /* .resultReflected */  TOMMRO_C_CRC_NO_REFLECTED,  \
}

#define TOMMRO_C_CRC_CRC16_MODBUS                       \
{                                                       \
    /* .polynomial */       0x8005,                     \
    /* .initialValue */     0xFFFF,                     \
    /* .finalXorValue */    0x0000,                     \
    /* .inputReflected */   TOMMRO_C_CRC_REFLECTED,     \
    /* .resultReflected */  TOMMRO_C_CRC_REFLECTED,     \
}


/******************* Standard polynomial CRC32 configuration */

#define TOMMRO_C_CRC_CRC32_CONFIG                       \
{                                                       \
    /* .polynomial */       0x04C11DB7,                 \
    /* .initialValue */     0xFFFFFFFF,                 \
    /* .finalXorValue */    0xFFFFFFFF,                 \
    /* .inputReflected */   TOMMRO_C_CRC_REFLECTED,     \
    /* .resultReflected */  TOMMRO_C_CRC_REFLECTED,     \
}

#define TOMMRO_C_CRC_CRC32_POSIX_CONFIG                 \
{                                                       \
    /* .polynomial */       0x04C11DB7,                 \
    /* .initialValue */     0x00000000,                 \
    /* .finalXorValue */    0xFFFFFFFF,                 \
    /* .inputReflected */   TOMMRO_C_CRC_NO_REFLECTED,  \
    /* .resultReflected */  TOMMRO_C_CRC_NO_REFLECTED,  \
}

#define TOMMRO_C_CRC_CRC32_Q_CONFIG                     \
{                                                       \
    /* .polynomial */       0x814141AB,                 \
    /* .initialValue */     0x00000000,                 \
    /* .finalXorValue */    0x00000000,                 \
    /* .inputReflected */   TOMMRO_C_CRC_NO_REFLECTED,  \
    /* .resultReflected */  TOMMRO_C_CRC_NO_REFLECTED,  \
}

#define TOMMRO_C_CRC_CRC32_XFER_CONFIG                  \
{                                                       \
    /* .polynomial */       0x000000AF,                 \
    /* .initialValue */     0x00000000,                 \
    /* .finalXorValue */    0x00000000,                 \
    /* .inputReflected */   TOMMRO_C_CRC_NO_REFLECTED,  \
    /* .resultReflected */  TOMMRO_C_CRC_NO_REFLECTED,  \
}


/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC CRC reflection.
typedef enum {

    /**
     * Input/Output no reflected.
     */
    TOMMRO_C_CRC_NO_REFLECTED = 0,

    /**
     * Input/Output reflected.
     */
    TOMMRO_C_CRC_REFLECTED,

} tommRoC_crc_reflected_enum_t;


// tommRoC CRC polynomial crc8/crc16/crc32 configuration struct.
typedef struct {

    uint8_t                         polynomial;
    uint8_t                         initialValue;
    uint8_t                         finalXorValue;
    tommRoC_crc_reflected_enum_t    inputReflected;
    tommRoC_crc_reflected_enum_t    resultReflected;

} tommRoC_crc_polynomial_crc8_config_t;

#define __EMPTY_tommRoC_crc_polynomial_crc8_config_t__  \
{                                                       \
    /* .polynomial */       0,                          \
    /* .initialValue */     0,                          \
    /* .finalXorValue */    0,                          \
    /* .inputReflected */   TOMMRO_C_CRC_NO_REFLECTED,  \
    /* .resultReflected */  TOMMRO_C_CRC_NO_REFLECTED,  \
}

typedef struct {

    uint16_t                        polynomial;
    uint16_t                        initialValue;
    uint16_t                        finalXorValue;
    tommRoC_crc_reflected_enum_t    inputReflected;
    tommRoC_crc_reflected_enum_t    resultReflected;

} tommRoC_crc_polynomial_crc16_config_t;

#define __EMPTY_tommRoC_crc_polynomial_crc16_config_t__ \
{                                                       \
    /* .polynomial */       0,                          \
    /* .initialValue */     0,                          \
    /* .finalXorValue */    0,                          \
    /* .inputReflected */   TOMMRO_C_CRC_NO_REFLECTED,  \
    /* .resultReflected */  TOMMRO_C_CRC_NO_REFLECTED,  \
}

typedef struct {

    uint32_t                        polynomial;
    uint32_t                        initialValue;
    uint32_t                        finalXorValue;
    tommRoC_crc_reflected_enum_t    inputReflected;
    tommRoC_crc_reflected_enum_t    resultReflected;

} tommRoC_crc_polynomial_crc32_config_t;

#define __EMPTY_tommRoC_crc_polynomial_crc32_config_t__ \
{                                                       \
    /* .polynomial */       0,                          \
    /* .initialValue */     0,                          \
    /* .finalXorValue */    0,                          \
    /* .inputReflected */   TOMMRO_C_CRC_NO_REFLECTED,  \
    /* .resultReflected */  TOMMRO_C_CRC_NO_REFLECTED,  \
}

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Get XOR based CRC8 of a byte array.
 *
 * param[in]        bufferPtr               input buffer data pointer.
 * param[in]        bufferLen               input buffer data length.
 *
 * return uint8_t
 */
uint8_t tommRoCCRCXORCRC8(
        const   uint8_t*    const   bufferPtr,
        const   uint32_t            bufferLen);

/**
 * Update (starting from previous CRC value) XOR based CRC8 of a byte array.
 *
 * param[in]        previousCRC             previous CRC value.
 * param[in]        bufferPtr               input buffer data pointer.
 * param[in]        bufferLen               input buffer data length.
 *
 * return uint8_t
 */
uint8_t tommRoCCRCXORCRC8Update(
        const   uint8_t             previousCRC,
        const   uint8_t*    const   bufferPtr,
        const   uint32_t            bufferLen);

/**
 * Get polynomial CRC8/CRC16/CRC32 of a byte array.
 *
 * param[in]        crcConfigPtr            CRC configuration structure pointer.
 * param[in]        bufferPtr               input buffer data pointer.
 * param[in]        bufferLen               input buffer data length.
 *
 * return uintx_t
 */
uint8_t tommRoCCRCPolynomialCRC8(
        const   tommRoC_crc_polynomial_crc8_config_t*   const   crcConfigPtr,
        const   uint8_t*                                const   bufferPtr,
        const   uint32_t                                        bufferLen);

uint16_t tommRoCCRCPolynomialCRC16(
        const   tommRoC_crc_polynomial_crc16_config_t*  const   crcConfigPtr,
        const   uint8_t*                                const   bufferPtr,
        const   uint32_t                                        bufferLen);

uint32_t tommRoCCRCPolynomialCRC32(
        const   tommRoC_crc_polynomial_crc32_config_t*  const   crcConfigPtr,
        const   uint8_t*                                const   bufferPtr,
        const   uint32_t                                        bufferLen);

/**
 * Update (starting from previous CRC value) polynomial CRC8/CRC16/CRC32 of a byte array.
 *
 * param[in]        crcConfigPtr            CRC configuration structure pointer.
 * param[in]        previousCRC             previous CRC value.
 * param[in]        bufferPtr               input buffer data pointer.
 * param[in]        bufferLen               input buffer data length.
 *
 * return uintx_t
 */
uint8_t tommRoCCRCPolynomialCRC8Update(
        const   tommRoC_crc_polynomial_crc8_config_t*   const   crcConfigPtr,
        const   uint8_t                                         previousCRC,
        const   uint8_t*                                const   bufferPtr,
        const   uint32_t                                        bufferLen);

uint16_t tommRoCCRCPolynomialCRC16Update(
        const   tommRoC_crc_polynomial_crc16_config_t*  const   crcConfigPtr,
        const   uint16_t                                        previousCRC,
        const   uint8_t*                                const   bufferPtr,
        const   uint32_t                                        bufferLen);

uint32_t tommRoCCRCPolynomialCRC32Update(
        const   tommRoC_crc_polynomial_crc32_config_t*  const   crcConfigPtr,
        const   uint32_t                                        previousCRC,
        const   uint8_t*                                const   bufferPtr,
        const   uint32_t                                        bufferLen);

/**
 * @}
 */

#endif
