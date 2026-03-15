
#ifndef TOMMROC_HW_COMM_NFC_H_
#define TOMMROC_HW_COMM_NFC_H_

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
#include "comm/NFC/NDEF/tommRoCHwCommNFCNDEF.h"
#include "comm/NFC/SNEP/tommRoCHwCommNFCSNEP.h"
 
#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/******************* NFC enumerations. */

// NFC interfaces.
typedef enum {

    TOMMROC_HW_COMM_NFC_INTERFACE_UNDETERMINED = 0,
    TOMMROC_HW_COMM_NFC_INTERFACE_FRAME,
    TOMMROC_HW_COMM_NFC_INTERFACE_ISODEP,
    TOMMROC_HW_COMM_NFC_INTERFACE_NFCDEP,
    TOMMROC_HW_COMM_NFC_INTERFACE_TAGCMD,

} tommRoC_hw_comm_nfc_interface_enum_t;

// NFC protocols.
typedef enum {

    TOMMROC_HW_COMM_NFC_PROTOCOL_UNDETERMINED = 0,
    TOMMROC_HW_COMM_NFC_PROTOCOL_T1T,
    TOMMROC_HW_COMM_NFC_PROTOCOL_T2T,
    TOMMROC_HW_COMM_NFC_PROTOCOL_T3T,
    TOMMROC_HW_COMM_NFC_PROTOCOL_T4T,
    TOMMROC_HW_COMM_NFC_PROTOCOL_ISODEP,
    TOMMROC_HW_COMM_NFC_PROTOCOL_NFCDEP,
    TOMMROC_HW_COMM_NFC_PROTOCOL_ISO14443A,
    TOMMROC_HW_COMM_NFC_PROTOCOL_ISO15693,
    TOMMROC_HW_COMM_NFC_PROTOCOL_MIFARE,

} tommRoC_hw_comm_nfc_protocol_enum_t;

// NFC modes.
typedef enum {

    TOMMROC_HW_COMM_NFC_MODE_POLL = 0,
    TOMMROC_HW_COMM_NFC_MODE_LISTEN,

} tommRoC_hw_comm_nfc_mode_enum_t;

// NFC technologies.
typedef enum {

    // For PN71x0 device
    TOMMROC_HW_COMM_NFC_TECH_PASSIVE_NFCA = 0,
    TOMMROC_HW_COMM_NFC_TECH_PASSIVE_NFCB,
    TOMMROC_HW_COMM_NFC_TECH_PASSIVE_NFCF,
    TOMMROC_HW_COMM_NFC_TECH_ACTIVE_NFCA,
    TOMMROC_HW_COMM_NFC_TECH_ACTIVE_NFCF,
    TOMMROC_HW_COMM_NFC_TECH_PASSIVE_15693,

    // For CR95HF device
    TOMMROC_HW_COMM_NFC_TECH_A,
    TOMMROC_HW_COMM_NFC_TECH_B,
    TOMMROC_HW_COMM_NFC_TECH_F,
    TOMMROC_HW_COMM_NFC_TECH_V,
    TOMMROC_HW_COMM_NFC_TECH_AP2P,
    TOMMROC_HW_COMM_NFC_TECH_ST25TB,

} tommRoC_hw_comm_nfc_tech_enum_t;


/******************* NFC structures. */

// NFC mode/technologies.
typedef struct {

    tommRoC_hw_comm_nfc_mode_enum_t mode;
    tommRoC_hw_comm_nfc_tech_enum_t tech;

} tommRoC_hw_comm_nfc_mode_tech_t;


/******************* NFC discovered remote device structures. */

// NFC POLL passive type A
typedef struct {

    uint8_t sensRes[2];
    uint8_t nfcIdLen;
    uint8_t nfcId[10];
    uint8_t selResLen;
    uint8_t selRes[1];
    uint8_t ratsLen;
    uint8_t rats[20];

} tommRoC_hw_comm_nfc_app_t;

#define __EMPTY_tommRoC_hw_comm_nfc_app_t_sensRes_field__       { 0, 0, }
#define __EMPTY_tommRoC_hw_comm_nfc_app_t_nfcIdLen_field__      (0)
#define __EMPTY_tommRoC_hw_comm_nfc_app_t_nfcId_field__         { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }
#define __EMPTY_tommRoC_hw_comm_nfc_app_t_selResLen_field__     (0)
#define __EMPTY_tommRoC_hw_comm_nfc_app_t_selRes_field__        { 0, }
#define __EMPTY_tommRoC_hw_comm_nfc_app_t_ratsLen_field__       (0)
#define __EMPTY_tommRoC_hw_comm_nfc_app_t_rats_field__          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }
#define __EMPTY_tommRoC_hw_comm_nfc_app_t__                                     \
{                                                                               \
    /* .sensRes */      __EMPTY_tommRoC_hw_comm_nfc_app_t_sensRes_field__,      \
    /* .nfcIdLen */     __EMPTY_tommRoC_hw_comm_nfc_app_t_nfcIdLen_field__,     \
    /* .nfcId */        __EMPTY_tommRoC_hw_comm_nfc_app_t_nfcId_field__,        \
    /* .selResLen */    __EMPTY_tommRoC_hw_comm_nfc_app_t_selResLen_field__,    \
    /* .selRes */       __EMPTY_tommRoC_hw_comm_nfc_app_t_selRes_field__,       \
    /* .ratsLen */      __EMPTY_tommRoC_hw_comm_nfc_app_t_ratsLen_field__,      \
    /* .rats */         __EMPTY_tommRoC_hw_comm_nfc_app_t_rats_field__,         \
}


// NFC POLL passive type B
typedef struct {

    uint8_t sensResLen;
    uint8_t sensRes[12];
    uint8_t attribResLen;
    uint8_t attribRes[17];

} tommRoC_hw_comm_nfc_bpp_t;

#define __EMPTY_tommRoC_hw_comm_nfc_bpp_t_sensResLen_field__    (0)
#define __EMPTY_tommRoC_hw_comm_nfc_bpp_t_sensRes_field__       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }
#define __EMPTY_tommRoC_hw_comm_nfc_bpp_t_attribResLen_field__  (0)
#define __EMPTY_tommRoC_hw_comm_nfc_bpp_t_attribRes_field__     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }
#define __EMPTY_tommRoC_hw_comm_nfc_bpp_t__                                     \
{                                                                               \
    /* .sensResLen */   __EMPTY_tommRoC_hw_comm_nfc_bpp_t_sensResLen_field__,   \
    /* .sensRes */      __EMPTY_tommRoC_hw_comm_nfc_bpp_t_sensRes_field__,      \
    /* .attribResLen */ __EMPTY_tommRoC_hw_comm_nfc_bpp_t_attribResLen_field__, \
    /* .attribRes */    __EMPTY_tommRoC_hw_comm_nfc_bpp_t_attribRes_field__,    \
}


// NFC POLL passive type F
typedef struct {

    uint8_t bitRate;
    uint8_t sensResLen;
    uint8_t sensRes[18];

} tommRoC_hw_comm_nfc_fpp_t;

#define __EMPTY_tommRoC_hw_comm_nfc_fpp_t_bitRate_field__       (0)
#define __EMPTY_tommRoC_hw_comm_nfc_fpp_t_sensResLen_field__    (0)
#define __EMPTY_tommRoC_hw_comm_nfc_fpp_t_sensRes_field__       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }
#define __EMPTY_tommRoC_hw_comm_nfc_fpp_t__                                     \
{                                                                               \
    /* .bitRate */      __EMPTY_tommRoC_hw_comm_nfc_fpp_t_bitRate_field__,      \
    /* .sensResLen */   __EMPTY_tommRoC_hw_comm_nfc_fpp_t_sensResLen_field__,   \
    /* .sensRes */      __EMPTY_tommRoC_hw_comm_nfc_fpp_t_sensRes_field__,      \
}


// NFC POLL passive type ISO15693
typedef struct {

    uint8_t AFI;
    uint8_t DSFID;
    uint8_t ID[8];

} tommRoC_hw_comm_nfc_vpp_t;

#define __EMPTY_tommRoC_hw_comm_nfc_vpp_t_AFI_field__           (0)
#define __EMPTY_tommRoC_hw_comm_nfc_vpp_t_DSFID_field__         (0)
#define __EMPTY_tommRoC_hw_comm_nfc_vpp_t_ID_field__            { 0, 0, 0, 0, 0, 0, 0, 0, }
#define __EMPTY_tommRoC_hw_comm_nfc_vpp_t__                                     \
{                                                                               \
    /* .AFI */      __EMPTY_tommRoC_hw_comm_nfc_vpp_t_AFI_field__,              \
    /* .DSFID */    __EMPTY_tommRoC_hw_comm_nfc_vpp_t_DSFID_field__,            \
    /* .ID */       __EMPTY_tommRoC_hw_comm_nfc_vpp_t_ID_field__,               \
}

// Generic union POLL passive type.
typedef union {

    tommRoC_hw_comm_nfc_app_t   nfcAPP;
    tommRoC_hw_comm_nfc_bpp_t   nfcBPP;
    tommRoC_hw_comm_nfc_fpp_t   nfcFPP;
    tommRoC_hw_comm_nfc_vpp_t   nfcVPP;

} tommRoC_hw_comm_nfc_generic_pp_t;


// Discovered remote device.
typedef struct {

    tommRoC_hw_comm_nfc_interface_enum_t    nfcItf;
    tommRoC_hw_comm_nfc_protocol_enum_t     nfcProtocol;
    tommRoC_hw_comm_nfc_mode_enum_t         nfcMode;
    tommRoC_hw_comm_nfc_tech_enum_t         nfcTech;
    bool                                    moreTags;
    tommRoC_hw_comm_nfc_generic_pp_t        nfcInfo;

} tommRoC_hw_comm_nfc_device_t;

#define __EMPTY_tommRoC_hw_comm_nfc_device_t_nfcItf_field__         (TOMMROC_HW_COMM_NFC_INTERFACE_UNDETERMINED)
#define __EMPTY_tommRoC_hw_comm_nfc_device_t_nfcProtocol_field__    (TOMMROC_HW_COMM_NFC_PROTOCOL_UNDETERMINED)
#define __EMPTY_tommRoC_hw_comm_nfc_device_t_nfcMode_field__        (TOMMROC_HW_COMM_NFC_MODE_POLL)
#define __EMPTY_tommRoC_hw_comm_nfc_device_t_nfcTech_field__        (TOMMROC_HW_COMM_NFC_TECH_PASSIVE_NFCA)
#define __EMPTY_tommRoC_hw_comm_nfc_device_t_moreTags_field__       (false)

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
