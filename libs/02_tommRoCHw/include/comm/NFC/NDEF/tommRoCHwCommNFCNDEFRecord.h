
#ifndef TOMMROC_HW_COMM_NFC_NDEF_RECORD_H_
#define TOMMROC_HW_COMM_NFC_NDEF_RECORD_H_

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
#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// NFC NDEF message record fields size.
#define TOMMROC_HW_COMM_NFC_NDEF_RECORD_HEADER_SIZE_BYTE                (TOMMROC_UTIL_U8_SIZE)  // NOTE: field is always present.
                                                                                                // NOTE: field size is fixed 1 byte.

#define TOMMROC_HW_COMM_NFC_NDEF_RECORD_TYPE_LENGTH_SIZE_BYTE           (TOMMROC_UTIL_U8_SIZE)  // NOTE: field is always present.
                                                                                                // NOTE: field size is fixed 1 byte.

#define TOMMROC_HW_COMM_NFC_NDEF_RECORD_SHORT_PAYLOAD_LENGTH_SIZE_BYTE  (TOMMROC_UTIL_U8_SIZE)  // NOTE: field is always present.
#define TOMMROC_HW_COMM_NFC_NDEF_RECORD_LONG_PAYLOAD_LENGTH_SIZE_BYTE   (TOMMROC_UTIL_U32_SIZE) // NOTE: field size could be 1 or 4 bytes.

#define TOMMROC_HW_COMM_NFC_NDEF_RECORD_NO_ID_LENGTH_SIZE_BYTE          (0)                     // NOTE: field can be omitted.
#define TOMMROC_HW_COMM_NFC_NDEF_RECORD_WITH_ID_LENGTH_SIZE_BYTE        (TOMMROC_UTIL_U8_SIZE)  // NOTE: if present, field size is fixed 1 byte.


// NFC NDEF message record size.
#define TOMMROC_HW_COMM_NFC_NDEF_RECORD_SHORT_PAYLOAD_NO_ID_SIZE_BYTE(sizeOfType, sizeOfPayload)    \
        (   TOMMROC_HW_COMM_NFC_NDEF_RECORD_HEADER_SIZE_BYTE                +                       \
            TOMMROC_HW_COMM_NFC_NDEF_RECORD_TYPE_LENGTH_SIZE_BYTE           +                       \
            TOMMROC_HW_COMM_NFC_NDEF_RECORD_SHORT_PAYLOAD_LENGTH_SIZE_BYTE  +                       \
            TOMMROC_HW_COMM_NFC_NDEF_RECORD_NO_ID_LENGTH_SIZE_BYTE          +                       \
            sizeOfType                                                      +                       \
            sizeOfPayload                                                                           )

#define TOMMROC_HW_COMM_NFC_NDEF_RECORD_LONG_PAYLOAD_NO_ID_SIZE_BYTE(sizeOfType, sizeOfPayload)     \
        (   TOMMROC_HW_COMM_NFC_NDEF_RECORD_HEADER_SIZE_BYTE                +                       \
            TOMMROC_HW_COMM_NFC_NDEF_RECORD_TYPE_LENGTH_SIZE_BYTE           +                       \
            TOMMROC_HW_COMM_NFC_NDEF_RECORD_LONG_PAYLOAD_LENGTH_SIZE_BYTE   +                       \
            TOMMROC_HW_COMM_NFC_NDEF_RECORD_NO_ID_LENGTH_SIZE_BYTE          +                       \
            sizeOfType                                                      +                       \
            sizeOfPayload                                                                           )

#define TOMMROC_HW_COMM_NFC_NDEF_RECORD_SHORT_PAYLOAD_WITH_ID_SIZE_BYTE(sizeOfType, sizeOfID, sizeOfPayload)    \
        (   TOMMROC_HW_COMM_NFC_NDEF_RECORD_HEADER_SIZE_BYTE                +                                   \
            TOMMROC_HW_COMM_NFC_NDEF_RECORD_TYPE_LENGTH_SIZE_BYTE           +                                   \
            TOMMROC_HW_COMM_NFC_NDEF_RECORD_SHORT_PAYLOAD_LENGTH_SIZE_BYTE  +                                   \
            TOMMROC_HW_COMM_NFC_NDEF_RECORD_WITH_ID_LENGTH_SIZE_BYTE        +                                   \
            sizeOfType                                                      +                                   \
            sizeOfID                                                        +                                   \
            sizeOfPayload                                                                                       )

#define TOMMROC_HW_COMM_NFC_NDEF_RECORD_LONG_PAYLOAD_WITH_ID_SIZE_BYTE(sizeOfType, sizeOfID, sizeOfPayload)     \
        (   TOMMROC_HW_COMM_NFC_NDEF_RECORD_HEADER_SIZE_BYTE                +                                   \
            TOMMROC_HW_COMM_NFC_NDEF_RECORD_TYPE_LENGTH_SIZE_BYTE           +                                   \
            TOMMROC_HW_COMM_NFC_NDEF_RECORD_LONG_PAYLOAD_LENGTH_SIZE_BYTE   +                                   \
            TOMMROC_HW_COMM_NFC_NDEF_RECORD_WITH_ID_LENGTH_SIZE_BYTE        +                                   \
            sizeOfType                                                      +                                   \
            sizeOfID                                                        +                                   \
            sizeOfPayload                                                                                       )

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * NFC NDEF record header Type Name Format Field.
 * It describes the record type.
 * It sets the expectation for the structure and content of the rest of the record.
 */
typedef enum {

    /**
     * Empty Record.
     * Indicates no type, id, or payload is associated with this NDEF Record.
     * This record type is useful on newly formatted cards since every NDEF tag
     * must have at least one NDEF Record.
     */
    TOMMROC_HW_COMM_NFC_NDEF_TNF_EMPTY_RECORD = 0,

    /**
     * Well-Known Record [NFC RTD].
     * Indicates the type field uses the RTD type name format.
     * This type name is used to stored any record defined by a Record Type Definition (RTD),
     * such as storing RTD Text, RTD URIs, etc., and is one of the mostly frequently used
     * and useful record types.
     */
    TOMMROC_HW_COMM_NFC_NDEF_TNF_WELL_KNOWN_RECORD,

    /**
     * MIME Media Record [RFC 2046].
     * Indicates the payload is an intermediate or final chunk of a chunked NDEF Record.
     */
    TOMMROC_HW_COMM_NFC_NDEF_TNF_MIME_MEDIA_RECORD,

    /**
     * Absolute URI Record [RFC 3986].
     * Indicates the type field contains a value that follows the absolute-URI BNF construct
     * defined by RFC 3986.
     */
    TOMMROC_HW_COMM_NFC_NDEF_TNF_ABSOLUTE_URI_RECORD,

    /**
     * External Record [NFC RTD].
     * Indicates the type field contains a value that follows the RTD external name specification.
     */
    TOMMROC_HW_COMM_NFC_NDEF_TNF_EXTERNAL_RECORD,

    /**
     * Unknown Record.
     * Indicates the payload type is unknown.
     */
    TOMMROC_HW_COMM_NFC_NDEF_TNF_UNKNOWN_RECORD,

    /**
     * Unchanged Record.
     * Indicates the payload is an intermediate or final chunk of a chunked NDEF Record.
     */
    TOMMROC_HW_COMM_NFC_NDEF_TNF_UNCHANGED_RECORD,

} tommRoC_hw_comm_nfc_ndef_record_header_TNF_enum_t;


/**
 * NFC NDEF record header Chunk Flag.
 * It indicates when a record is chunked.
 * If this flag set, reading a single record won’t provide you with all the data for that data item.
 * You must read all the records associated with that data item to get the complete information about it.
 */
typedef enum {

    // Record not chunked.
    TOMMROC_HW_COMM_NFC_NDEF_CF_NOT_CHUNKED = 0,

    // Record chunked.
    TOMMROC_HW_COMM_NFC_NDEF_CF_CHUNKED,

} tommRoC_hw_comm_nfc_ndef_record_header_CF_enum_t;


/**
 * NFC NDEF record header Message End.
 * It indicates if this is the end of an NDEF message.
 */
typedef enum {

    // This is not the end of an NDEF message.
    TOMMROC_HW_COMM_NFC_NDEF_ME_NOT_LAST_RECORD = 0,

    // This is the end of an NDEF message.
    TOMMROC_HW_COMM_NFC_NDEF_ME_LAST_RECORD,

} tommRoC_hw_comm_nfc_ndef_record_header_ME_enum_t;


/**
 * NFC NDEF record header Message Begin.
 * It indicates if this is the start of an NDEF message.
 */
typedef enum {

    // This is not the start of an NDEF message.
    TOMMROC_HW_COMM_NFC_NDEF_MB_NOT_FIRST_RECORD = 0,

    // This is the start of an NDEF message.
    TOMMROC_HW_COMM_NFC_NDEF_MB_FIRST_RECORD,

} tommRoC_hw_comm_nfc_ndef_record_header_MB_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
