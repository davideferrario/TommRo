
#ifndef TOMMROC_BIT_FIELD_H_
#define TOMMROC_BIT_FIELD_H_

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
 * @defgroup tommRoCBitField tommRoCBitField
 *
 * @brief  TommRoC library bit field module
 * @author TommRo Software Department
 *
 * This module is providing bit field define functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCCTA.h"
#include "tommRoCUtil.h"

#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * NOTE: start description of bit field structure from LSB.
 */

/******************* Generic bit field structure define */

#define TOMMROC_BIT_FIELD_1_FIELD(                                          \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,                                     \
        STRUCT_NAME,                                                        \
        UNSIGNED_TYPE)                                                      \
                                                                            \
        TOMMROC_SCTA_EQUALS(                                                \
            SIZE_BIT_1,                                                     \
            sizeof(UNSIGNED_TYPE) * 8);                                     \
        typedef union {                                                     \
            struct {                                                        \
                VAR_TYPE_1 NAME_1 : SIZE_BIT_1;                             \
            } bits;                                                         \
            UNSIGNED_TYPE value;                                            \
        } STRUCT_NAME

#define TOMMROC_BIT_FIELD_2_FIELD(                                          \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,                                     \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,                                     \
        STRUCT_NAME,                                                        \
        UNSIGNED_TYPE)                                                      \
                                                                            \
        TOMMROC_SCTA_EQUALS(                                                \
            SIZE_BIT_1 +                                                    \
            SIZE_BIT_2,                                                     \
            sizeof(UNSIGNED_TYPE) * 8);                                     \
        typedef union {                                                     \
            struct {                                                        \
                VAR_TYPE_1 NAME_1 : SIZE_BIT_1;                             \
                VAR_TYPE_2 NAME_2 : SIZE_BIT_2;                             \
            } bits;                                                         \
            UNSIGNED_TYPE value;                                            \
        } STRUCT_NAME

#define TOMMROC_BIT_FIELD_3_FIELD(                                          \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,                                     \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,                                     \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,                                     \
        STRUCT_NAME,                                                        \
        UNSIGNED_TYPE)                                                      \
                                                                            \
        TOMMROC_SCTA_EQUALS(                                                \
            SIZE_BIT_1 +                                                    \
            SIZE_BIT_2 +                                                    \
            SIZE_BIT_3,                                                     \
            sizeof(UNSIGNED_TYPE) * 8);                                     \
        typedef union {                                                     \
            struct {                                                        \
                VAR_TYPE_1 NAME_1 : SIZE_BIT_1;                             \
                VAR_TYPE_2 NAME_2 : SIZE_BIT_2;                             \
                VAR_TYPE_3 NAME_3 : SIZE_BIT_3;                             \
            } bits;                                                         \
            UNSIGNED_TYPE value;                                            \
        } STRUCT_NAME

#define TOMMROC_BIT_FIELD_4_FIELD(                                          \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,                                     \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,                                     \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,                                     \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,                                     \
        STRUCT_NAME,                                                        \
        UNSIGNED_TYPE)                                                      \
                                                                            \
        TOMMROC_SCTA_EQUALS(                                                \
            SIZE_BIT_1 +                                                    \
            SIZE_BIT_2 +                                                    \
            SIZE_BIT_3 +                                                    \
            SIZE_BIT_4,                                                     \
            sizeof(UNSIGNED_TYPE) * 8);                                     \
        typedef union {                                                     \
            struct {                                                        \
                VAR_TYPE_1 NAME_1 : SIZE_BIT_1;                             \
                VAR_TYPE_2 NAME_2 : SIZE_BIT_2;                             \
                VAR_TYPE_3 NAME_3 : SIZE_BIT_3;                             \
                VAR_TYPE_4 NAME_4 : SIZE_BIT_4;                             \
            } bits;                                                         \
            UNSIGNED_TYPE value;                                            \
        } STRUCT_NAME

#define TOMMROC_BIT_FIELD_5_FIELD(                                          \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,                                     \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,                                     \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,                                     \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,                                     \
        VAR_TYPE_5, NAME_5, SIZE_BIT_5,                                     \
        STRUCT_NAME,                                                        \
        UNSIGNED_TYPE)                                                      \
                                                                            \
        TOMMROC_SCTA_EQUALS(                                                \
            SIZE_BIT_1 +                                                    \
            SIZE_BIT_2 +                                                    \
            SIZE_BIT_3 +                                                    \
            SIZE_BIT_4 +                                                    \
            SIZE_BIT_5,                                                     \
            sizeof(UNSIGNED_TYPE) * 8);                                     \
        typedef union {                                                     \
            struct {                                                        \
                VAR_TYPE_1 NAME_1 : SIZE_BIT_1;                             \
                VAR_TYPE_2 NAME_2 : SIZE_BIT_2;                             \
                VAR_TYPE_3 NAME_3 : SIZE_BIT_3;                             \
                VAR_TYPE_4 NAME_4 : SIZE_BIT_4;                             \
                VAR_TYPE_5 NAME_5 : SIZE_BIT_5;                             \
            } bits;                                                         \
            UNSIGNED_TYPE value;                                            \
        } STRUCT_NAME

#define TOMMROC_BIT_FIELD_6_FIELD(                                          \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,                                     \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,                                     \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,                                     \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,                                     \
        VAR_TYPE_5, NAME_5, SIZE_BIT_5,                                     \
        VAR_TYPE_6, NAME_6, SIZE_BIT_6,                                     \
        STRUCT_NAME,                                                        \
        UNSIGNED_TYPE)                                                      \
                                                                            \
        TOMMROC_SCTA_EQUALS(                                                \
            SIZE_BIT_1 +                                                    \
            SIZE_BIT_2 +                                                    \
            SIZE_BIT_3 +                                                    \
            SIZE_BIT_4 +                                                    \
            SIZE_BIT_5 +                                                    \
            SIZE_BIT_6,                                                     \
            sizeof(UNSIGNED_TYPE) * 8);                                     \
        typedef union {                                                     \
            struct {                                                        \
                VAR_TYPE_1 NAME_1 : SIZE_BIT_1;                             \
                VAR_TYPE_2 NAME_2 : SIZE_BIT_2;                             \
                VAR_TYPE_3 NAME_3 : SIZE_BIT_3;                             \
                VAR_TYPE_4 NAME_4 : SIZE_BIT_4;                             \
                VAR_TYPE_5 NAME_5 : SIZE_BIT_5;                             \
                VAR_TYPE_6 NAME_6 : SIZE_BIT_6;                             \
            } bits;                                                         \
            UNSIGNED_TYPE value;                                            \
        } STRUCT_NAME

#define TOMMROC_BIT_FIELD_7_FIELD(                                          \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,                                     \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,                                     \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,                                     \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,                                     \
        VAR_TYPE_5, NAME_5, SIZE_BIT_5,                                     \
        VAR_TYPE_6, NAME_6, SIZE_BIT_6,                                     \
        VAR_TYPE_7, NAME_7, SIZE_BIT_7,                                     \
        STRUCT_NAME,                                                        \
        UNSIGNED_TYPE)                                                      \
                                                                            \
        TOMMROC_SCTA_EQUALS(                                                \
            SIZE_BIT_1 +                                                    \
            SIZE_BIT_2 +                                                    \
            SIZE_BIT_3 +                                                    \
            SIZE_BIT_4 +                                                    \
            SIZE_BIT_5 +                                                    \
            SIZE_BIT_6 +                                                    \
            SIZE_BIT_7,                                                     \
            sizeof(UNSIGNED_TYPE) * 8);                                     \
        typedef union {                                                     \
            struct {                                                        \
                VAR_TYPE_1 NAME_1 : SIZE_BIT_1;                             \
                VAR_TYPE_2 NAME_2 : SIZE_BIT_2;                             \
                VAR_TYPE_3 NAME_3 : SIZE_BIT_3;                             \
                VAR_TYPE_4 NAME_4 : SIZE_BIT_4;                             \
                VAR_TYPE_5 NAME_5 : SIZE_BIT_5;                             \
                VAR_TYPE_6 NAME_6 : SIZE_BIT_6;                             \
                VAR_TYPE_7 NAME_7 : SIZE_BIT_7;                             \
            } bits;                                                         \
            UNSIGNED_TYPE value;                                            \
        } STRUCT_NAME

#define TOMMROC_BIT_FIELD_8_FIELD(                                          \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,                                     \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,                                     \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,                                     \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,                                     \
        VAR_TYPE_5, NAME_5, SIZE_BIT_5,                                     \
        VAR_TYPE_6, NAME_6, SIZE_BIT_6,                                     \
        VAR_TYPE_7, NAME_7, SIZE_BIT_7,                                     \
        VAR_TYPE_8, NAME_8, SIZE_BIT_8,                                     \
        STRUCT_NAME,                                                        \
        UNSIGNED_TYPE)                                                      \
                                                                            \
        TOMMROC_SCTA_EQUALS(                                                \
            SIZE_BIT_1 +                                                    \
            SIZE_BIT_2 +                                                    \
            SIZE_BIT_3 +                                                    \
            SIZE_BIT_4 +                                                    \
            SIZE_BIT_5 +                                                    \
            SIZE_BIT_6 +                                                    \
            SIZE_BIT_7 +                                                    \
            SIZE_BIT_8,                                                     \
            sizeof(UNSIGNED_TYPE) * 8);                                     \
        typedef union {                                                     \
            struct {                                                        \
                VAR_TYPE_1 NAME_1 : SIZE_BIT_1;                             \
                VAR_TYPE_2 NAME_2 : SIZE_BIT_2;                             \
                VAR_TYPE_3 NAME_3 : SIZE_BIT_3;                             \
                VAR_TYPE_4 NAME_4 : SIZE_BIT_4;                             \
                VAR_TYPE_5 NAME_5 : SIZE_BIT_5;                             \
                VAR_TYPE_6 NAME_6 : SIZE_BIT_6;                             \
                VAR_TYPE_7 NAME_7 : SIZE_BIT_7;                             \
                VAR_TYPE_8 NAME_8 : SIZE_BIT_8;                             \
            } bits;                                                         \
            UNSIGNED_TYPE value;                                            \
        } STRUCT_NAME

#define TOMMROC_BIT_FIELD_9_FIELD(                                          \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,                                     \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,                                     \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,                                     \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,                                     \
        VAR_TYPE_5, NAME_5, SIZE_BIT_5,                                     \
        VAR_TYPE_6, NAME_6, SIZE_BIT_6,                                     \
        VAR_TYPE_7, NAME_7, SIZE_BIT_7,                                     \
        VAR_TYPE_8, NAME_8, SIZE_BIT_8,                                     \
        VAR_TYPE_9, NAME_9, SIZE_BIT_9,                                     \
        STRUCT_NAME,                                                        \
        UNSIGNED_TYPE)                                                      \
                                                                            \
        TOMMROC_SCTA_EQUALS(                                                \
            SIZE_BIT_1 +                                                    \
            SIZE_BIT_2 +                                                    \
            SIZE_BIT_3 +                                                    \
            SIZE_BIT_4 +                                                    \
            SIZE_BIT_5 +                                                    \
            SIZE_BIT_6 +                                                    \
            SIZE_BIT_7 +                                                    \
            SIZE_BIT_8 +                                                    \
            SIZE_BIT_9,                                                     \
            sizeof(UNSIGNED_TYPE) * 8);                                     \
        typedef union {                                                     \
            struct {                                                        \
                VAR_TYPE_1 NAME_1 : SIZE_BIT_1;                             \
                VAR_TYPE_2 NAME_2 : SIZE_BIT_2;                             \
                VAR_TYPE_3 NAME_3 : SIZE_BIT_3;                             \
                VAR_TYPE_4 NAME_4 : SIZE_BIT_4;                             \
                VAR_TYPE_5 NAME_5 : SIZE_BIT_5;                             \
                VAR_TYPE_6 NAME_6 : SIZE_BIT_6;                             \
                VAR_TYPE_7 NAME_7 : SIZE_BIT_7;                             \
                VAR_TYPE_8 NAME_8 : SIZE_BIT_8;                             \
                VAR_TYPE_9 NAME_9 : SIZE_BIT_9;                             \
            } bits;                                                         \
            UNSIGNED_TYPE value;                                            \
        } STRUCT_NAME

#define TOMMROC_BIT_FIELD_10_FIELD(                                         \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,                                     \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,                                     \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,                                     \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,                                     \
        VAR_TYPE_5, NAME_5, SIZE_BIT_5,                                     \
        VAR_TYPE_6, NAME_6, SIZE_BIT_6,                                     \
        VAR_TYPE_7, NAME_7, SIZE_BIT_7,                                     \
        VAR_TYPE_8, NAME_8, SIZE_BIT_8,                                     \
        VAR_TYPE_9, NAME_9, SIZE_BIT_9,                                     \
        VAR_TYPE_10, NAME_10, SIZE_BIT_10,                                  \
        STRUCT_NAME,                                                        \
        UNSIGNED_TYPE)                                                      \
                                                                            \
        TOMMROC_SCTA_EQUALS(                                                \
            SIZE_BIT_1 +                                                    \
            SIZE_BIT_2 +                                                    \
            SIZE_BIT_3 +                                                    \
            SIZE_BIT_4 +                                                    \
            SIZE_BIT_5 +                                                    \
            SIZE_BIT_6 +                                                    \
            SIZE_BIT_7 +                                                    \
            SIZE_BIT_8 +                                                    \
            SIZE_BIT_9 +                                                    \
            SIZE_BIT_10,                                                    \
            sizeof(UNSIGNED_TYPE) * 8);                                     \
        typedef union {                                                     \
            struct {                                                        \
                VAR_TYPE_1 NAME_1 : SIZE_BIT_1;                             \
                VAR_TYPE_2 NAME_2 : SIZE_BIT_2;                             \
                VAR_TYPE_3 NAME_3 : SIZE_BIT_3;                             \
                VAR_TYPE_4 NAME_4 : SIZE_BIT_4;                             \
                VAR_TYPE_5 NAME_5 : SIZE_BIT_5;                             \
                VAR_TYPE_6 NAME_6 : SIZE_BIT_6;                             \
                VAR_TYPE_7 NAME_7 : SIZE_BIT_7;                             \
                VAR_TYPE_8 NAME_8 : SIZE_BIT_8;                             \
                VAR_TYPE_9 NAME_9 : SIZE_BIT_9;                             \
                VAR_TYPE_10 NAME_10 : SIZE_BIT_10;                          \
            } bits;                                                         \
            UNSIGNED_TYPE value;                                            \
        } STRUCT_NAME

#define TOMMROC_BIT_FIELD_11_FIELD(                                         \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,                                     \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,                                     \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,                                     \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,                                     \
        VAR_TYPE_5, NAME_5, SIZE_BIT_5,                                     \
        VAR_TYPE_6, NAME_6, SIZE_BIT_6,                                     \
        VAR_TYPE_7, NAME_7, SIZE_BIT_7,                                     \
        VAR_TYPE_8, NAME_8, SIZE_BIT_8,                                     \
        VAR_TYPE_9, NAME_9, SIZE_BIT_9,                                     \
        VAR_TYPE_10, NAME_10, SIZE_BIT_10,                                  \
        VAR_TYPE_11, NAME_11, SIZE_BIT_11,                                  \
        STRUCT_NAME,                                                        \
        UNSIGNED_TYPE)                                                      \
                                                                            \
        TOMMROC_SCTA_EQUALS(                                                \
            SIZE_BIT_1 +                                                    \
            SIZE_BIT_2 +                                                    \
            SIZE_BIT_3 +                                                    \
            SIZE_BIT_4 +                                                    \
            SIZE_BIT_5 +                                                    \
            SIZE_BIT_6 +                                                    \
            SIZE_BIT_7 +                                                    \
            SIZE_BIT_8 +                                                    \
            SIZE_BIT_9 +                                                    \
            SIZE_BIT_10 +                                                   \
            SIZE_BIT_11,                                                    \
            sizeof(UNSIGNED_TYPE) * 8);                                     \
        typedef union {                                                     \
            struct {                                                        \
                VAR_TYPE_1 NAME_1 : SIZE_BIT_1;                             \
                VAR_TYPE_2 NAME_2 : SIZE_BIT_2;                             \
                VAR_TYPE_3 NAME_3 : SIZE_BIT_3;                             \
                VAR_TYPE_4 NAME_4 : SIZE_BIT_4;                             \
                VAR_TYPE_5 NAME_5 : SIZE_BIT_5;                             \
                VAR_TYPE_6 NAME_6 : SIZE_BIT_6;                             \
                VAR_TYPE_7 NAME_7 : SIZE_BIT_7;                             \
                VAR_TYPE_8 NAME_8 : SIZE_BIT_8;                             \
                VAR_TYPE_9 NAME_9 : SIZE_BIT_9;                             \
                VAR_TYPE_10 NAME_10 : SIZE_BIT_10;                          \
                VAR_TYPE_11 NAME_11 : SIZE_BIT_11;                          \
            } bits;                                                         \
            UNSIGNED_TYPE value;                                            \
        } STRUCT_NAME

#define TOMMROC_BIT_FIELD_12_FIELD(                                         \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,                                     \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,                                     \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,                                     \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,                                     \
        VAR_TYPE_5, NAME_5, SIZE_BIT_5,                                     \
        VAR_TYPE_6, NAME_6, SIZE_BIT_6,                                     \
        VAR_TYPE_7, NAME_7, SIZE_BIT_7,                                     \
        VAR_TYPE_8, NAME_8, SIZE_BIT_8,                                     \
        VAR_TYPE_9, NAME_9, SIZE_BIT_9,                                     \
        VAR_TYPE_10, NAME_10, SIZE_BIT_10,                                  \
        VAR_TYPE_11, NAME_11, SIZE_BIT_11,                                  \
        VAR_TYPE_12, NAME_12, SIZE_BIT_12,                                  \
        STRUCT_NAME,                                                        \
        UNSIGNED_TYPE)                                                      \
                                                                            \
        TOMMROC_SCTA_EQUALS(                                                \
            SIZE_BIT_1 +                                                    \
            SIZE_BIT_2 +                                                    \
            SIZE_BIT_3 +                                                    \
            SIZE_BIT_4 +                                                    \
            SIZE_BIT_5 +                                                    \
            SIZE_BIT_6 +                                                    \
            SIZE_BIT_7 +                                                    \
            SIZE_BIT_8 +                                                    \
            SIZE_BIT_9 +                                                    \
            SIZE_BIT_10 +                                                   \
            SIZE_BIT_11 +                                                   \
            SIZE_BIT_12,                                                    \
            sizeof(UNSIGNED_TYPE) * 8);                                     \
        typedef union {                                                     \
            struct {                                                        \
                VAR_TYPE_1 NAME_1 : SIZE_BIT_1;                             \
                VAR_TYPE_2 NAME_2 : SIZE_BIT_2;                             \
                VAR_TYPE_3 NAME_3 : SIZE_BIT_3;                             \
                VAR_TYPE_4 NAME_4 : SIZE_BIT_4;                             \
                VAR_TYPE_5 NAME_5 : SIZE_BIT_5;                             \
                VAR_TYPE_6 NAME_6 : SIZE_BIT_6;                             \
                VAR_TYPE_7 NAME_7 : SIZE_BIT_7;                             \
                VAR_TYPE_8 NAME_8 : SIZE_BIT_8;                             \
                VAR_TYPE_9 NAME_9 : SIZE_BIT_9;                             \
                VAR_TYPE_10 NAME_10 : SIZE_BIT_10;                          \
                VAR_TYPE_11 NAME_11 : SIZE_BIT_11;                          \
                VAR_TYPE_12 NAME_12 : SIZE_BIT_12;                          \
            } bits;                                                         \
            UNSIGNED_TYPE value;                                            \
        } STRUCT_NAME

#define TOMMROC_BIT_FIELD_13_FIELD(                                         \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,                                     \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,                                     \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,                                     \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,                                     \
        VAR_TYPE_5, NAME_5, SIZE_BIT_5,                                     \
        VAR_TYPE_6, NAME_6, SIZE_BIT_6,                                     \
        VAR_TYPE_7, NAME_7, SIZE_BIT_7,                                     \
        VAR_TYPE_8, NAME_8, SIZE_BIT_8,                                     \
        VAR_TYPE_9, NAME_9, SIZE_BIT_9,                                     \
        VAR_TYPE_10, NAME_10, SIZE_BIT_10,                                  \
        VAR_TYPE_11, NAME_11, SIZE_BIT_11,                                  \
        VAR_TYPE_12, NAME_12, SIZE_BIT_12,                                  \
        VAR_TYPE_13, NAME_13, SIZE_BIT_13,                                  \
        STRUCT_NAME,                                                        \
        UNSIGNED_TYPE)                                                      \
                                                                            \
        TOMMROC_SCTA_EQUALS(                                                \
            SIZE_BIT_1 +                                                    \
            SIZE_BIT_2 +                                                    \
            SIZE_BIT_3 +                                                    \
            SIZE_BIT_4 +                                                    \
            SIZE_BIT_5 +                                                    \
            SIZE_BIT_6 +                                                    \
            SIZE_BIT_7 +                                                    \
            SIZE_BIT_8 +                                                    \
            SIZE_BIT_9 +                                                    \
            SIZE_BIT_10 +                                                   \
            SIZE_BIT_11 +                                                   \
            SIZE_BIT_12 +                                                   \
            SIZE_BIT_13,                                                    \
            sizeof(UNSIGNED_TYPE) * 8);                                     \
        typedef union {                                                     \
            struct {                                                        \
                VAR_TYPE_1 NAME_1 : SIZE_BIT_1;                             \
                VAR_TYPE_2 NAME_2 : SIZE_BIT_2;                             \
                VAR_TYPE_3 NAME_3 : SIZE_BIT_3;                             \
                VAR_TYPE_4 NAME_4 : SIZE_BIT_4;                             \
                VAR_TYPE_5 NAME_5 : SIZE_BIT_5;                             \
                VAR_TYPE_6 NAME_6 : SIZE_BIT_6;                             \
                VAR_TYPE_7 NAME_7 : SIZE_BIT_7;                             \
                VAR_TYPE_8 NAME_8 : SIZE_BIT_8;                             \
                VAR_TYPE_9 NAME_9 : SIZE_BIT_9;                             \
                VAR_TYPE_10 NAME_10 : SIZE_BIT_10;                          \
                VAR_TYPE_11 NAME_11 : SIZE_BIT_11;                          \
                VAR_TYPE_12 NAME_12 : SIZE_BIT_12;                          \
                VAR_TYPE_13 NAME_13 : SIZE_BIT_13;                          \
            } bits;                                                         \
            UNSIGNED_TYPE value;                                            \
        } STRUCT_NAME

#define TOMMROC_BIT_FIELD_14_FIELD(                                         \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,                                     \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,                                     \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,                                     \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,                                     \
        VAR_TYPE_5, NAME_5, SIZE_BIT_5,                                     \
        VAR_TYPE_6, NAME_6, SIZE_BIT_6,                                     \
        VAR_TYPE_7, NAME_7, SIZE_BIT_7,                                     \
        VAR_TYPE_8, NAME_8, SIZE_BIT_8,                                     \
        VAR_TYPE_9, NAME_9, SIZE_BIT_9,                                     \
        VAR_TYPE_10, NAME_10, SIZE_BIT_10,                                  \
        VAR_TYPE_11, NAME_11, SIZE_BIT_11,                                  \
        VAR_TYPE_12, NAME_12, SIZE_BIT_12,                                  \
        VAR_TYPE_13, NAME_13, SIZE_BIT_13,                                  \
        VAR_TYPE_14, NAME_14, SIZE_BIT_14,                                  \
        STRUCT_NAME,                                                        \
        UNSIGNED_TYPE)                                                      \
                                                                            \
        TOMMROC_SCTA_EQUALS(                                                \
            SIZE_BIT_1 +                                                    \
            SIZE_BIT_2 +                                                    \
            SIZE_BIT_3 +                                                    \
            SIZE_BIT_4 +                                                    \
            SIZE_BIT_5 +                                                    \
            SIZE_BIT_6 +                                                    \
            SIZE_BIT_7 +                                                    \
            SIZE_BIT_8 +                                                    \
            SIZE_BIT_9 +                                                    \
            SIZE_BIT_10 +                                                   \
            SIZE_BIT_11 +                                                   \
            SIZE_BIT_12 +                                                   \
            SIZE_BIT_13 +                                                   \
            SIZE_BIT_14,                                                    \
            sizeof(UNSIGNED_TYPE) * 8);                                     \
        typedef union {                                                     \
            struct {                                                        \
                VAR_TYPE_1 NAME_1 : SIZE_BIT_1;                             \
                VAR_TYPE_2 NAME_2 : SIZE_BIT_2;                             \
                VAR_TYPE_3 NAME_3 : SIZE_BIT_3;                             \
                VAR_TYPE_4 NAME_4 : SIZE_BIT_4;                             \
                VAR_TYPE_5 NAME_5 : SIZE_BIT_5;                             \
                VAR_TYPE_6 NAME_6 : SIZE_BIT_6;                             \
                VAR_TYPE_7 NAME_7 : SIZE_BIT_7;                             \
                VAR_TYPE_8 NAME_8 : SIZE_BIT_8;                             \
                VAR_TYPE_9 NAME_9 : SIZE_BIT_9;                             \
                VAR_TYPE_10 NAME_10 : SIZE_BIT_10;                          \
                VAR_TYPE_11 NAME_11 : SIZE_BIT_11;                          \
                VAR_TYPE_12 NAME_12 : SIZE_BIT_12;                          \
                VAR_TYPE_13 NAME_13 : SIZE_BIT_13;                          \
                VAR_TYPE_14 NAME_14 : SIZE_BIT_14;                          \
            } bits;                                                         \
            UNSIGNED_TYPE value;                                            \
        } STRUCT_NAME

#define TOMMROC_BIT_FIELD_15_FIELD(                                         \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,                                     \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,                                     \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,                                     \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,                                     \
        VAR_TYPE_5, NAME_5, SIZE_BIT_5,                                     \
        VAR_TYPE_6, NAME_6, SIZE_BIT_6,                                     \
        VAR_TYPE_7, NAME_7, SIZE_BIT_7,                                     \
        VAR_TYPE_8, NAME_8, SIZE_BIT_8,                                     \
        VAR_TYPE_9, NAME_9, SIZE_BIT_9,                                     \
        VAR_TYPE_10, NAME_10, SIZE_BIT_10,                                  \
        VAR_TYPE_11, NAME_11, SIZE_BIT_11,                                  \
        VAR_TYPE_12, NAME_12, SIZE_BIT_12,                                  \
        VAR_TYPE_13, NAME_13, SIZE_BIT_13,                                  \
        VAR_TYPE_14, NAME_14, SIZE_BIT_14,                                  \
        VAR_TYPE_15, NAME_15, SIZE_BIT_15,                                  \
        STRUCT_NAME,                                                        \
        UNSIGNED_TYPE)                                                      \
                                                                            \
        TOMMROC_SCTA_EQUALS(                                                \
            SIZE_BIT_1 +                                                    \
            SIZE_BIT_2 +                                                    \
            SIZE_BIT_3 +                                                    \
            SIZE_BIT_4 +                                                    \
            SIZE_BIT_5 +                                                    \
            SIZE_BIT_6 +                                                    \
            SIZE_BIT_7 +                                                    \
            SIZE_BIT_8 +                                                    \
            SIZE_BIT_9 +                                                    \
            SIZE_BIT_10 +                                                   \
            SIZE_BIT_11 +                                                   \
            SIZE_BIT_12 +                                                   \
            SIZE_BIT_13 +                                                   \
            SIZE_BIT_14 +                                                   \
            SIZE_BIT_15,                                                    \
            sizeof(UNSIGNED_TYPE) * 8);                                     \
        typedef union {                                                     \
            struct {                                                        \
                VAR_TYPE_1 NAME_1 : SIZE_BIT_1;                             \
                VAR_TYPE_2 NAME_2 : SIZE_BIT_2;                             \
                VAR_TYPE_3 NAME_3 : SIZE_BIT_3;                             \
                VAR_TYPE_4 NAME_4 : SIZE_BIT_4;                             \
                VAR_TYPE_5 NAME_5 : SIZE_BIT_5;                             \
                VAR_TYPE_6 NAME_6 : SIZE_BIT_6;                             \
                VAR_TYPE_7 NAME_7 : SIZE_BIT_7;                             \
                VAR_TYPE_8 NAME_8 : SIZE_BIT_8;                             \
                VAR_TYPE_9 NAME_9 : SIZE_BIT_9;                             \
                VAR_TYPE_10 NAME_10 : SIZE_BIT_10;                          \
                VAR_TYPE_11 NAME_11 : SIZE_BIT_11;                          \
                VAR_TYPE_12 NAME_12 : SIZE_BIT_12;                          \
                VAR_TYPE_13 NAME_13 : SIZE_BIT_13;                          \
                VAR_TYPE_14 NAME_14 : SIZE_BIT_14;                          \
                VAR_TYPE_15 NAME_15 : SIZE_BIT_15;                          \
            } bits;                                                         \
            UNSIGNED_TYPE value;                                            \
        } STRUCT_NAME

#define TOMMROC_BIT_FIELD_16_FIELD(                                         \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,                                     \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,                                     \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,                                     \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,                                     \
        VAR_TYPE_5, NAME_5, SIZE_BIT_5,                                     \
        VAR_TYPE_6, NAME_6, SIZE_BIT_6,                                     \
        VAR_TYPE_7, NAME_7, SIZE_BIT_7,                                     \
        VAR_TYPE_8, NAME_8, SIZE_BIT_8,                                     \
        VAR_TYPE_9, NAME_9, SIZE_BIT_9,                                     \
        VAR_TYPE_10, NAME_10, SIZE_BIT_10,                                  \
        VAR_TYPE_11, NAME_11, SIZE_BIT_11,                                  \
        VAR_TYPE_12, NAME_12, SIZE_BIT_12,                                  \
        VAR_TYPE_13, NAME_13, SIZE_BIT_13,                                  \
        VAR_TYPE_14, NAME_14, SIZE_BIT_14,                                  \
        VAR_TYPE_15, NAME_15, SIZE_BIT_15,                                  \
        VAR_TYPE_16, NAME_16, SIZE_BIT_16,                                  \
        STRUCT_NAME,                                                        \
        UNSIGNED_TYPE)                                                      \
                                                                            \
        TOMMROC_SCTA_EQUALS(                                                \
            SIZE_BIT_1 +                                                    \
            SIZE_BIT_2 +                                                    \
            SIZE_BIT_3 +                                                    \
            SIZE_BIT_4 +                                                    \
            SIZE_BIT_5 +                                                    \
            SIZE_BIT_6 +                                                    \
            SIZE_BIT_7 +                                                    \
            SIZE_BIT_8 +                                                    \
            SIZE_BIT_9 +                                                    \
            SIZE_BIT_10 +                                                   \
            SIZE_BIT_11 +                                                   \
            SIZE_BIT_12 +                                                   \
            SIZE_BIT_13 +                                                   \
            SIZE_BIT_14 +                                                   \
            SIZE_BIT_15 +                                                   \
            SIZE_BIT_16,                                                    \
            sizeof(UNSIGNED_TYPE) * 8);                                     \
        typedef union {                                                     \
            struct {                                                        \
                VAR_TYPE_1 NAME_1 : SIZE_BIT_1;                             \
                VAR_TYPE_2 NAME_2 : SIZE_BIT_2;                             \
                VAR_TYPE_3 NAME_3 : SIZE_BIT_3;                             \
                VAR_TYPE_4 NAME_4 : SIZE_BIT_4;                             \
                VAR_TYPE_5 NAME_5 : SIZE_BIT_5;                             \
                VAR_TYPE_6 NAME_6 : SIZE_BIT_6;                             \
                VAR_TYPE_7 NAME_7 : SIZE_BIT_7;                             \
                VAR_TYPE_8 NAME_8 : SIZE_BIT_8;                             \
                VAR_TYPE_9 NAME_9 : SIZE_BIT_9;                             \
                VAR_TYPE_10 NAME_10 : SIZE_BIT_10;                          \
                VAR_TYPE_11 NAME_11 : SIZE_BIT_11;                          \
                VAR_TYPE_12 NAME_12 : SIZE_BIT_12;                          \
                VAR_TYPE_13 NAME_13 : SIZE_BIT_13;                          \
                VAR_TYPE_14 NAME_14 : SIZE_BIT_14;                          \
                VAR_TYPE_15 NAME_15 : SIZE_BIT_15;                          \
                VAR_TYPE_16 NAME_16 : SIZE_BIT_16;                          \
            } bits;                                                         \
            UNSIGNED_TYPE value;                                            \
        } STRUCT_NAME


/******************* Unsigned 8 bit field structure define */

#define TOMMROC_BIT_FIELD_U8_1_FIELD(               \
        NAME_1, SIZE_BIT_1,                         \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_1_FIELD(                  \
                uint8_t, NAME_1, SIZE_BIT_1,        \
                STRUCT_NAME,                        \
                uint8_t)

#define TOMMROC_BIT_FIELD_U8_2_FIELD(               \
        NAME_1, SIZE_BIT_1,                         \
        NAME_2, SIZE_BIT_2,                         \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_2_FIELD(                  \
                uint8_t, NAME_1, SIZE_BIT_1,        \
                uint8_t, NAME_2, SIZE_BIT_2,        \
                STRUCT_NAME,                        \
                uint8_t)

#define TOMMROC_BIT_FIELD_U8_3_FIELD(               \
        NAME_1, SIZE_BIT_1,                         \
        NAME_2, SIZE_BIT_2,                         \
        NAME_3, SIZE_BIT_3,                         \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_3_FIELD(                  \
                uint8_t, NAME_1, SIZE_BIT_1,        \
                uint8_t, NAME_2, SIZE_BIT_2,        \
                uint8_t, NAME_3, SIZE_BIT_3,        \
                STRUCT_NAME,                        \
                uint8_t)

#define TOMMROC_BIT_FIELD_U8_4_FIELD(               \
        NAME_1, SIZE_BIT_1,                         \
        NAME_2, SIZE_BIT_2,                         \
        NAME_3, SIZE_BIT_3,                         \
        NAME_4, SIZE_BIT_4,                         \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_4_FIELD(                  \
                uint8_t, NAME_1, SIZE_BIT_1,        \
                uint8_t, NAME_2, SIZE_BIT_2,        \
                uint8_t, NAME_3, SIZE_BIT_3,        \
                uint8_t, NAME_4, SIZE_BIT_4,        \
                STRUCT_NAME,                        \
                uint8_t)

#define TOMMROC_BIT_FIELD_U8_5_FIELD(               \
        NAME_1, SIZE_BIT_1,                         \
        NAME_2, SIZE_BIT_2,                         \
        NAME_3, SIZE_BIT_3,                         \
        NAME_4, SIZE_BIT_4,                         \
        NAME_5, SIZE_BIT_5,                         \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_5_FIELD(                  \
                uint8_t, NAME_1, SIZE_BIT_1,        \
                uint8_t, NAME_2, SIZE_BIT_2,        \
                uint8_t, NAME_3, SIZE_BIT_3,        \
                uint8_t, NAME_4, SIZE_BIT_4,        \
                uint8_t, NAME_5, SIZE_BIT_5,        \
                STRUCT_NAME,                        \
                uint8_t)

#define TOMMROC_BIT_FIELD_U8_6_FIELD(               \
        NAME_1, SIZE_BIT_1,                         \
        NAME_2, SIZE_BIT_2,                         \
        NAME_3, SIZE_BIT_3,                         \
        NAME_4, SIZE_BIT_4,                         \
        NAME_5, SIZE_BIT_5,                         \
        NAME_6, SIZE_BIT_6,                         \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_6_FIELD(                  \
                uint8_t, NAME_1, SIZE_BIT_1,        \
                uint8_t, NAME_2, SIZE_BIT_2,        \
                uint8_t, NAME_3, SIZE_BIT_3,        \
                uint8_t, NAME_4, SIZE_BIT_4,        \
                uint8_t, NAME_5, SIZE_BIT_5,        \
                uint8_t, NAME_6, SIZE_BIT_6,        \
                STRUCT_NAME,                        \
                uint8_t)

#define TOMMROC_BIT_FIELD_U8_7_FIELD(               \
        NAME_1, SIZE_BIT_1,                         \
        NAME_2, SIZE_BIT_2,                         \
        NAME_3, SIZE_BIT_3,                         \
        NAME_4, SIZE_BIT_4,                         \
        NAME_5, SIZE_BIT_5,                         \
        NAME_6, SIZE_BIT_6,                         \
        NAME_7, SIZE_BIT_7,                         \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_7_FIELD(                  \
                uint8_t, NAME_1, SIZE_BIT_1,        \
                uint8_t, NAME_2, SIZE_BIT_2,        \
                uint8_t, NAME_3, SIZE_BIT_3,        \
                uint8_t, NAME_4, SIZE_BIT_4,        \
                uint8_t, NAME_5, SIZE_BIT_5,        \
                uint8_t, NAME_6, SIZE_BIT_6,        \
                uint8_t, NAME_7, SIZE_BIT_7,        \
                STRUCT_NAME,                        \
                uint8_t)

#define TOMMROC_BIT_FIELD_U8_8_FIELD(               \
        NAME_1, SIZE_BIT_1,                         \
        NAME_2, SIZE_BIT_2,                         \
        NAME_3, SIZE_BIT_3,                         \
        NAME_4, SIZE_BIT_4,                         \
        NAME_5, SIZE_BIT_5,                         \
        NAME_6, SIZE_BIT_6,                         \
        NAME_7, SIZE_BIT_7,                         \
        NAME_8, SIZE_BIT_8,                         \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_8_FIELD(                  \
                uint8_t, NAME_1, SIZE_BIT_1,        \
                uint8_t, NAME_2, SIZE_BIT_2,        \
                uint8_t, NAME_3, SIZE_BIT_3,        \
                uint8_t, NAME_4, SIZE_BIT_4,        \
                uint8_t, NAME_5, SIZE_BIT_5,        \
                uint8_t, NAME_6, SIZE_BIT_6,        \
                uint8_t, NAME_7, SIZE_BIT_7,        \
                uint8_t, NAME_8, SIZE_BIT_8,        \
                STRUCT_NAME,                        \
                uint8_t)


/******************* Unsigned 16 bit field structure define */

#define TOMMROC_BIT_FIELD_U16_1_FIELD(              \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,             \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_1_FIELD(                  \
                VAR_TYPE_1, NAME_1, SIZE_BIT_1,     \
                STRUCT_NAME,                        \
                uint16_t)

#define TOMMROC_BIT_FIELD_U16_2_FIELD(              \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,             \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,             \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_2_FIELD(                  \
                VAR_TYPE_1, NAME_1, SIZE_BIT_1,     \
                VAR_TYPE_2, NAME_2, SIZE_BIT_2,     \
                STRUCT_NAME,                        \
                uint16_t)

#define TOMMROC_BIT_FIELD_U16_3_FIELD(              \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,             \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,             \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,             \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_3_FIELD(                  \
                VAR_TYPE_1, NAME_1, SIZE_BIT_1,     \
                VAR_TYPE_2, NAME_2, SIZE_BIT_2,     \
                VAR_TYPE_3, NAME_3, SIZE_BIT_3,     \
                STRUCT_NAME,                        \
                uint16_t)

#define TOMMROC_BIT_FIELD_U16_4_FIELD(              \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,             \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,             \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,             \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,             \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_4_FIELD(                  \
                VAR_TYPE_1, NAME_1, SIZE_BIT_1,     \
                VAR_TYPE_2, NAME_2, SIZE_BIT_2,     \
                VAR_TYPE_3, NAME_3, SIZE_BIT_3,     \
                VAR_TYPE_4, NAME_4, SIZE_BIT_4,     \
                STRUCT_NAME,                        \
                uint16_t)

#define TOMMROC_BIT_FIELD_U16_5_FIELD(              \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,             \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,             \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,             \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,             \
        VAR_TYPE_5, NAME_5, SIZE_BIT_5,             \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_5_FIELD(                  \
                VAR_TYPE_1, NAME_1, SIZE_BIT_1,     \
                VAR_TYPE_2, NAME_2, SIZE_BIT_2,     \
                VAR_TYPE_3, NAME_3, SIZE_BIT_3,     \
                VAR_TYPE_4, NAME_4, SIZE_BIT_4,     \
                VAR_TYPE_5, NAME_5, SIZE_BIT_5,     \
                STRUCT_NAME,                        \
                uint16_t)

#define TOMMROC_BIT_FIELD_U16_6_FIELD(              \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,             \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,             \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,             \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,             \
        VAR_TYPE_5, NAME_5, SIZE_BIT_5,             \
        VAR_TYPE_6, NAME_6, SIZE_BIT_6,             \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_6_FIELD(                  \
                VAR_TYPE_1, NAME_1, SIZE_BIT_1,     \
                VAR_TYPE_2, NAME_2, SIZE_BIT_2,     \
                VAR_TYPE_3, NAME_3, SIZE_BIT_3,     \
                VAR_TYPE_4, NAME_4, SIZE_BIT_4,     \
                VAR_TYPE_5, NAME_5, SIZE_BIT_5,     \
                VAR_TYPE_6, NAME_6, SIZE_BIT_6,     \
                STRUCT_NAME,                        \
                uint16_t)

#define TOMMROC_BIT_FIELD_U16_7_FIELD(              \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,             \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,             \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,             \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,             \
        VAR_TYPE_5, NAME_5, SIZE_BIT_5,             \
        VAR_TYPE_6, NAME_6, SIZE_BIT_6,             \
        VAR_TYPE_7, NAME_7, SIZE_BIT_7,             \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_7_FIELD(                  \
                VAR_TYPE_1, NAME_1, SIZE_BIT_1,     \
                VAR_TYPE_2, NAME_2, SIZE_BIT_2,     \
                VAR_TYPE_3, NAME_3, SIZE_BIT_3,     \
                VAR_TYPE_4, NAME_4, SIZE_BIT_4,     \
                VAR_TYPE_5, NAME_5, SIZE_BIT_5,     \
                VAR_TYPE_6, NAME_6, SIZE_BIT_6,     \
                VAR_TYPE_7, NAME_7, SIZE_BIT_7,     \
                STRUCT_NAME,                        \
                uint16_t)

#define TOMMROC_BIT_FIELD_U16_8_FIELD(              \
        VAR_TYPE_1, NAME_1, SIZE_BIT_1,             \
        VAR_TYPE_2, NAME_2, SIZE_BIT_2,             \
        VAR_TYPE_3, NAME_3, SIZE_BIT_3,             \
        VAR_TYPE_4, NAME_4, SIZE_BIT_4,             \
        VAR_TYPE_5, NAME_5, SIZE_BIT_5,             \
        VAR_TYPE_6, NAME_6, SIZE_BIT_6,             \
        VAR_TYPE_7, NAME_7, SIZE_BIT_7,             \
        VAR_TYPE_8, NAME_8, SIZE_BIT_8,             \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_8_FIELD(                  \
                VAR_TYPE_1, NAME_1, SIZE_BIT_1,     \
                VAR_TYPE_2, NAME_2, SIZE_BIT_2,     \
                VAR_TYPE_3, NAME_3, SIZE_BIT_3,     \
                VAR_TYPE_4, NAME_4, SIZE_BIT_4,     \
                VAR_TYPE_5, NAME_5, SIZE_BIT_5,     \
                VAR_TYPE_6, NAME_6, SIZE_BIT_6,     \
                VAR_TYPE_7, NAME_7, SIZE_BIT_7,     \
                VAR_TYPE_8, NAME_8, SIZE_BIT_8,     \
                STRUCT_NAME,                        \
                uint16_t)

#define TOMMROC_BIT_FIELD_U16_9_FIELD(              \
        NAME_1, SIZE_BIT_1,                         \
        NAME_2, SIZE_BIT_2,                         \
        NAME_3, SIZE_BIT_3,                         \
        NAME_4, SIZE_BIT_4,                         \
        NAME_5, SIZE_BIT_5,                         \
        NAME_6, SIZE_BIT_6,                         \
        NAME_7, SIZE_BIT_7,                         \
        NAME_8, SIZE_BIT_8,                         \
        NAME_9, SIZE_BIT_9,                         \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_9_FIELD(                  \
                uint8_t, NAME_1, SIZE_BIT_1,        \
                uint8_t, NAME_2, SIZE_BIT_2,        \
                uint8_t, NAME_3, SIZE_BIT_3,        \
                uint8_t, NAME_4, SIZE_BIT_4,        \
                uint8_t, NAME_5, SIZE_BIT_5,        \
                uint8_t, NAME_6, SIZE_BIT_6,        \
                uint8_t, NAME_7, SIZE_BIT_7,        \
                uint8_t, NAME_8, SIZE_BIT_8,        \
                uint8_t, NAME_9, SIZE_BIT_9,        \
                STRUCT_NAME,                        \
                uint16_t)

#define TOMMROC_BIT_FIELD_U16_10_FIELD(             \
        NAME_1, SIZE_BIT_1,                         \
        NAME_2, SIZE_BIT_2,                         \
        NAME_3, SIZE_BIT_3,                         \
        NAME_4, SIZE_BIT_4,                         \
        NAME_5, SIZE_BIT_5,                         \
        NAME_6, SIZE_BIT_6,                         \
        NAME_7, SIZE_BIT_7,                         \
        NAME_8, SIZE_BIT_8,                         \
        NAME_9, SIZE_BIT_9,                         \
        NAME_10, SIZE_BIT_10,                       \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_10_FIELD(                 \
                uint8_t, NAME_1, SIZE_BIT_1,        \
                uint8_t, NAME_2, SIZE_BIT_2,        \
                uint8_t, NAME_3, SIZE_BIT_3,        \
                uint8_t, NAME_4, SIZE_BIT_4,        \
                uint8_t, NAME_5, SIZE_BIT_5,        \
                uint8_t, NAME_6, SIZE_BIT_6,        \
                uint8_t, NAME_7, SIZE_BIT_7,        \
                uint8_t, NAME_8, SIZE_BIT_8,        \
                uint8_t, NAME_9, SIZE_BIT_9,        \
                uint8_t, NAME_10, SIZE_BIT_10,      \
                STRUCT_NAME,                        \
                uint16_t)

#define TOMMROC_BIT_FIELD_U16_11_FIELD(             \
        NAME_1, SIZE_BIT_1,                         \
        NAME_2, SIZE_BIT_2,                         \
        NAME_3, SIZE_BIT_3,                         \
        NAME_4, SIZE_BIT_4,                         \
        NAME_5, SIZE_BIT_5,                         \
        NAME_6, SIZE_BIT_6,                         \
        NAME_7, SIZE_BIT_7,                         \
        NAME_8, SIZE_BIT_8,                         \
        NAME_9, SIZE_BIT_9,                         \
        NAME_10, SIZE_BIT_10,                       \
        NAME_11, SIZE_BIT_11,                       \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_11_FIELD(                 \
                uint8_t, NAME_1, SIZE_BIT_1,        \
                uint8_t, NAME_2, SIZE_BIT_2,        \
                uint8_t, NAME_3, SIZE_BIT_3,        \
                uint8_t, NAME_4, SIZE_BIT_4,        \
                uint8_t, NAME_5, SIZE_BIT_5,        \
                uint8_t, NAME_6, SIZE_BIT_6,        \
                uint8_t, NAME_7, SIZE_BIT_7,        \
                uint8_t, NAME_8, SIZE_BIT_8,        \
                uint8_t, NAME_9, SIZE_BIT_9,        \
                uint8_t, NAME_10, SIZE_BIT_10,      \
                uint8_t, NAME_11, SIZE_BIT_11,      \
                STRUCT_NAME,                        \
                uint16_t)

#define TOMMROC_BIT_FIELD_U16_12_FIELD(             \
        NAME_1, SIZE_BIT_1,                         \
        NAME_2, SIZE_BIT_2,                         \
        NAME_3, SIZE_BIT_3,                         \
        NAME_4, SIZE_BIT_4,                         \
        NAME_5, SIZE_BIT_5,                         \
        NAME_6, SIZE_BIT_6,                         \
        NAME_7, SIZE_BIT_7,                         \
        NAME_8, SIZE_BIT_8,                         \
        NAME_9, SIZE_BIT_9,                         \
        NAME_10, SIZE_BIT_10,                       \
        NAME_11, SIZE_BIT_11,                       \
        NAME_12, SIZE_BIT_12,                       \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_12_FIELD(                 \
                uint8_t, NAME_1, SIZE_BIT_1,        \
                uint8_t, NAME_2, SIZE_BIT_2,        \
                uint8_t, NAME_3, SIZE_BIT_3,        \
                uint8_t, NAME_4, SIZE_BIT_4,        \
                uint8_t, NAME_5, SIZE_BIT_5,        \
                uint8_t, NAME_6, SIZE_BIT_6,        \
                uint8_t, NAME_7, SIZE_BIT_7,        \
                uint8_t, NAME_8, SIZE_BIT_8,        \
                uint8_t, NAME_9, SIZE_BIT_9,        \
                uint8_t, NAME_10, SIZE_BIT_10,      \
                uint8_t, NAME_11, SIZE_BIT_11,      \
                uint8_t, NAME_12, SIZE_BIT_12,      \
                STRUCT_NAME,                        \
                uint16_t)

#define TOMMROC_BIT_FIELD_U16_13_FIELD(             \
        NAME_1, SIZE_BIT_1,                         \
        NAME_2, SIZE_BIT_2,                         \
        NAME_3, SIZE_BIT_3,                         \
        NAME_4, SIZE_BIT_4,                         \
        NAME_5, SIZE_BIT_5,                         \
        NAME_6, SIZE_BIT_6,                         \
        NAME_7, SIZE_BIT_7,                         \
        NAME_8, SIZE_BIT_8,                         \
        NAME_9, SIZE_BIT_9,                         \
        NAME_10, SIZE_BIT_10,                       \
        NAME_11, SIZE_BIT_11,                       \
        NAME_12, SIZE_BIT_12,                       \
        NAME_13, SIZE_BIT_13,                       \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_13_FIELD(                 \
                uint8_t, NAME_1, SIZE_BIT_1,        \
                uint8_t, NAME_2, SIZE_BIT_2,        \
                uint8_t, NAME_3, SIZE_BIT_3,        \
                uint8_t, NAME_4, SIZE_BIT_4,        \
                uint8_t, NAME_5, SIZE_BIT_5,        \
                uint8_t, NAME_6, SIZE_BIT_6,        \
                uint8_t, NAME_7, SIZE_BIT_7,        \
                uint8_t, NAME_8, SIZE_BIT_8,        \
                uint8_t, NAME_9, SIZE_BIT_9,        \
                uint8_t, NAME_10, SIZE_BIT_10,      \
                uint8_t, NAME_11, SIZE_BIT_11,      \
                uint8_t, NAME_12, SIZE_BIT_12,      \
                uint8_t, NAME_13, SIZE_BIT_13,      \
                STRUCT_NAME,                        \
                uint16_t)

#define TOMMROC_BIT_FIELD_U16_14_FIELD(             \
        NAME_1, SIZE_BIT_1,                         \
        NAME_2, SIZE_BIT_2,                         \
        NAME_3, SIZE_BIT_3,                         \
        NAME_4, SIZE_BIT_4,                         \
        NAME_5, SIZE_BIT_5,                         \
        NAME_6, SIZE_BIT_6,                         \
        NAME_7, SIZE_BIT_7,                         \
        NAME_8, SIZE_BIT_8,                         \
        NAME_9, SIZE_BIT_9,                         \
        NAME_10, SIZE_BIT_10,                       \
        NAME_11, SIZE_BIT_11,                       \
        NAME_12, SIZE_BIT_12,                       \
        NAME_13, SIZE_BIT_13,                       \
        NAME_14, SIZE_BIT_14,                       \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_14_FIELD(                 \
                uint8_t, NAME_1, SIZE_BIT_1,        \
                uint8_t, NAME_2, SIZE_BIT_2,        \
                uint8_t, NAME_3, SIZE_BIT_3,        \
                uint8_t, NAME_4, SIZE_BIT_4,        \
                uint8_t, NAME_5, SIZE_BIT_5,        \
                uint8_t, NAME_6, SIZE_BIT_6,        \
                uint8_t, NAME_7, SIZE_BIT_7,        \
                uint8_t, NAME_8, SIZE_BIT_8,        \
                uint8_t, NAME_9, SIZE_BIT_9,        \
                uint8_t, NAME_10, SIZE_BIT_10,      \
                uint8_t, NAME_11, SIZE_BIT_11,      \
                uint8_t, NAME_12, SIZE_BIT_12,      \
                uint8_t, NAME_13, SIZE_BIT_13,      \
                uint8_t, NAME_14, SIZE_BIT_14,      \
                STRUCT_NAME,                        \
                uint16_t)

#define TOMMROC_BIT_FIELD_U16_15_FIELD(             \
        NAME_1, SIZE_BIT_1,                         \
        NAME_2, SIZE_BIT_2,                         \
        NAME_3, SIZE_BIT_3,                         \
        NAME_4, SIZE_BIT_4,                         \
        NAME_5, SIZE_BIT_5,                         \
        NAME_6, SIZE_BIT_6,                         \
        NAME_7, SIZE_BIT_7,                         \
        NAME_8, SIZE_BIT_8,                         \
        NAME_9, SIZE_BIT_9,                         \
        NAME_10, SIZE_BIT_10,                       \
        NAME_11, SIZE_BIT_11,                       \
        NAME_12, SIZE_BIT_12,                       \
        NAME_13, SIZE_BIT_13,                       \
        NAME_14, SIZE_BIT_14,                       \
        NAME_15, SIZE_BIT_15,                       \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_15_FIELD(                 \
                uint8_t, NAME_1, SIZE_BIT_1,        \
                uint8_t, NAME_2, SIZE_BIT_2,        \
                uint8_t, NAME_3, SIZE_BIT_3,        \
                uint8_t, NAME_4, SIZE_BIT_4,        \
                uint8_t, NAME_5, SIZE_BIT_5,        \
                uint8_t, NAME_6, SIZE_BIT_6,        \
                uint8_t, NAME_7, SIZE_BIT_7,        \
                uint8_t, NAME_8, SIZE_BIT_8,        \
                uint8_t, NAME_9, SIZE_BIT_9,        \
                uint8_t, NAME_10, SIZE_BIT_10,      \
                uint8_t, NAME_11, SIZE_BIT_11,      \
                uint8_t, NAME_12, SIZE_BIT_12,      \
                uint8_t, NAME_13, SIZE_BIT_13,      \
                uint8_t, NAME_14, SIZE_BIT_14,      \
                uint8_t, NAME_15, SIZE_BIT_15,      \
                STRUCT_NAME,                        \
                uint16_t)

#define TOMMROC_BIT_FIELD_U16_16_FIELD(             \
        NAME_1, SIZE_BIT_1,                         \
        NAME_2, SIZE_BIT_2,                         \
        NAME_3, SIZE_BIT_3,                         \
        NAME_4, SIZE_BIT_4,                         \
        NAME_5, SIZE_BIT_5,                         \
        NAME_6, SIZE_BIT_6,                         \
        NAME_7, SIZE_BIT_7,                         \
        NAME_8, SIZE_BIT_8,                         \
        NAME_9, SIZE_BIT_9,                         \
        NAME_10, SIZE_BIT_10,                       \
        NAME_11, SIZE_BIT_11,                       \
        NAME_12, SIZE_BIT_12,                       \
        NAME_13, SIZE_BIT_13,                       \
        NAME_14, SIZE_BIT_14,                       \
        NAME_15, SIZE_BIT_15,                       \
        NAME_16, SIZE_BIT_16,                       \
        STRUCT_NAME)                                \
                                                    \
        TOMMROC_BIT_FIELD_16_FIELD(                 \
                uint8_t, NAME_1, SIZE_BIT_1,        \
                uint8_t, NAME_2, SIZE_BIT_2,        \
                uint8_t, NAME_3, SIZE_BIT_3,        \
                uint8_t, NAME_4, SIZE_BIT_4,        \
                uint8_t, NAME_5, SIZE_BIT_5,        \
                uint8_t, NAME_6, SIZE_BIT_6,        \
                uint8_t, NAME_7, SIZE_BIT_7,        \
                uint8_t, NAME_8, SIZE_BIT_8,        \
                uint8_t, NAME_9, SIZE_BIT_9,        \
                uint8_t, NAME_10, SIZE_BIT_10,      \
                uint8_t, NAME_11, SIZE_BIT_11,      \
                uint8_t, NAME_12, SIZE_BIT_12,      \
                uint8_t, NAME_13, SIZE_BIT_13,      \
                uint8_t, NAME_14, SIZE_BIT_14,      \
                uint8_t, NAME_15, SIZE_BIT_15,      \
                uint8_t, NAME_16, SIZE_BIT_16,      \
                STRUCT_NAME,                        \
                uint16_t)


/******************* Generic bit field structure configuration set  */

#define TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME, UNSIGNED_TYPE, STRUCT_NAME)              \
        TOMMRO_C_UTIL_UNUSED_PRE static void _ ## STRUCT_NAME ## _ ## BIT_NAME ## _(    \
                        void*           const   refValuePtr,                            \
                const   UNSIGNED_TYPE           value) TOMMRO_C_UTIL_UNUSED_POST {      \
            ((STRUCT_NAME*) refValuePtr)->bits.BIT_NAME = value;                        \
        }

#define TOMMROC_BIT_FIELD_1_FIELD_CONFIG_SET(                                   \
        BIT_NAME_1,                                                             \
        UNSIGNED_TYPE,                                                          \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_1, UNSIGNED_TYPE, STRUCT_NAME)

#define TOMMROC_BIT_FIELD_2_FIELD_CONFIG_SET(                                   \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        UNSIGNED_TYPE,                                                          \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_1, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_2, UNSIGNED_TYPE, STRUCT_NAME)

#define TOMMROC_BIT_FIELD_3_FIELD_CONFIG_SET(                                   \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        UNSIGNED_TYPE,                                                          \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_1, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_2, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_3, UNSIGNED_TYPE, STRUCT_NAME)

#define TOMMROC_BIT_FIELD_4_FIELD_CONFIG_SET(                                   \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        UNSIGNED_TYPE,                                                          \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_1, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_2, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_3, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_4, UNSIGNED_TYPE, STRUCT_NAME)

#define TOMMROC_BIT_FIELD_5_FIELD_CONFIG_SET(                                   \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        UNSIGNED_TYPE,                                                          \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_1, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_2, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_3, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_4, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_5, UNSIGNED_TYPE, STRUCT_NAME)

#define TOMMROC_BIT_FIELD_6_FIELD_CONFIG_SET(                                   \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        UNSIGNED_TYPE,                                                          \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_1, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_2, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_3, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_4, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_5, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_6, UNSIGNED_TYPE, STRUCT_NAME)

#define TOMMROC_BIT_FIELD_7_FIELD_CONFIG_SET(                                   \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        UNSIGNED_TYPE,                                                          \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_1, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_2, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_3, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_4, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_5, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_6, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_7, UNSIGNED_TYPE, STRUCT_NAME)

#define TOMMROC_BIT_FIELD_8_FIELD_CONFIG_SET(                                   \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        UNSIGNED_TYPE,                                                          \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_1, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_2, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_3, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_4, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_5, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_6, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_7, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_8, UNSIGNED_TYPE, STRUCT_NAME)

#define TOMMROC_BIT_FIELD_9_FIELD_CONFIG_SET(                                   \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        BIT_NAME_9,                                                             \
        UNSIGNED_TYPE,                                                          \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_1, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_2, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_3, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_4, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_5, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_6, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_7, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_8, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_9, UNSIGNED_TYPE, STRUCT_NAME))

#define TOMMROC_BIT_FIELD_10_FIELD_CONFIG_SET(                                  \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        BIT_NAME_9,                                                             \
        BIT_NAME_10,                                                            \
        UNSIGNED_TYPE,                                                          \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_1, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_2, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_3, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_4, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_5, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_6, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_7, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_8, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_9, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_10, UNSIGNED_TYPE, STRUCT_NAME)

#define TOMMROC_BIT_FIELD_11_FIELD_CONFIG_SET(                                  \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        BIT_NAME_9,                                                             \
        BIT_NAME_10,                                                            \
        BIT_NAME_11,                                                            \
        UNSIGNED_TYPE,                                                          \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_1, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_2, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_3, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_4, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_5, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_6, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_7, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_8, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_9, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_10, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_11, UNSIGNED_TYPE, STRUCT_NAME)

#define TOMMROC_BIT_FIELD_12_FIELD_CONFIG_SET(                                  \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        BIT_NAME_9,                                                             \
        BIT_NAME_10,                                                            \
        BIT_NAME_11,                                                            \
        BIT_NAME_12,                                                            \
        UNSIGNED_TYPE,                                                          \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_1, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_2, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_3, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_4, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_5, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_6, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_7, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_8, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_9, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_10, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_11, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_12, UNSIGNED_TYPE, STRUCT_NAME)

#define TOMMROC_BIT_FIELD_13_FIELD_CONFIG_SET(                                  \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        BIT_NAME_9,                                                             \
        BIT_NAME_10,                                                            \
        BIT_NAME_11,                                                            \
        BIT_NAME_12,                                                            \
        BIT_NAME_13,                                                            \
        UNSIGNED_TYPE,                                                          \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_1, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_2, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_3, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_4, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_5, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_6, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_7, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_8, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_9, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_10, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_11, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_12, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_13, UNSIGNED_TYPE, STRUCT_NAME)

#define TOMMROC_BIT_FIELD_14_FIELD_CONFIG_SET(                                  \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        BIT_NAME_9,                                                             \
        BIT_NAME_10,                                                            \
        BIT_NAME_11,                                                            \
        BIT_NAME_12,                                                            \
        BIT_NAME_13,                                                            \
        BIT_NAME_14,                                                            \
        UNSIGNED_TYPE,                                                          \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_1, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_2, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_3, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_4, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_5, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_6, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_7, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_8, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_9, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_10, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_11, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_12, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_13, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_14, UNSIGNED_TYPE, STRUCT_NAME)

#define TOMMROC_BIT_FIELD_15_FIELD_CONFIG_SET(                                  \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        BIT_NAME_9,                                                             \
        BIT_NAME_10,                                                            \
        BIT_NAME_11,                                                            \
        BIT_NAME_12,                                                            \
        BIT_NAME_13,                                                            \
        BIT_NAME_14,                                                            \
        BIT_NAME_15,                                                            \
        UNSIGNED_TYPE,                                                          \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_1, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_2, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_3, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_4, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_5, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_6, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_7, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_8, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_9, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_10, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_11, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_12, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_13, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_14, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_15, UNSIGNED_TYPE, STRUCT_NAME)

#define TOMMROC_BIT_FIELD_16_FIELD_CONFIG_SET(                                  \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        BIT_NAME_9,                                                             \
        BIT_NAME_10,                                                            \
        BIT_NAME_11,                                                            \
        BIT_NAME_12,                                                            \
        BIT_NAME_13,                                                            \
        BIT_NAME_14,                                                            \
        BIT_NAME_15,                                                            \
        BIT_NAME_16,                                                            \
        UNSIGNED_TYPE,                                                          \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_1, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_2, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_3, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_4, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_5, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_6, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_7, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_8, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_9, UNSIGNED_TYPE, STRUCT_NAME)    \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_10, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_11, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_12, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_13, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_14, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_15, UNSIGNED_TYPE, STRUCT_NAME)   \
        TOMMROC_BIT_FIELD_CONFIG_SET(BIT_NAME_16, UNSIGNED_TYPE, STRUCT_NAME)


/******************* Unsigned 8 bit field structure configuration set */

#define TOMMROC_BIT_FIELD_U8_1_FIELD_CONFIG_SET(                                \
        BIT_NAME_1,                                                             \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_1_FIELD_CONFIG_SET(                                   \
                BIT_NAME_1,                                                     \
                uint8_t,                                                        \
                STRUCT_NAME)

#define TOMMROC_BIT_FIELD_U8_2_FIELD_CONFIG_SET(                                \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_2_FIELD_CONFIG_SET(                                   \
                BIT_NAME_1,                                                     \
                BIT_NAME_2,                                                     \
                uint8_t,                                                        \
                STRUCT_NAME)

#define TOMMROC_BIT_FIELD_U8_3_FIELD_CONFIG_SET(                                \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_3_FIELD_CONFIG_SET(                                   \
                BIT_NAME_1,                                                     \
                BIT_NAME_2,                                                     \
                BIT_NAME_3,                                                     \
                uint8_t,                                                        \
                STRUCT_NAME)

#define TOMMROC_BIT_FIELD_U8_4_FIELD_CONFIG_SET(                                \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_4_FIELD_CONFIG_SET(                                   \
                BIT_NAME_1,                                                     \
                BIT_NAME_2,                                                     \
                BIT_NAME_3,                                                     \
                BIT_NAME_4,                                                     \
                uint8_t,                                                        \
                STRUCT_NAME)

#define TOMMROC_BIT_FIELD_U8_5_FIELD_CONFIG_SET(                                \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_5_FIELD_CONFIG_SET(                                   \
                BIT_NAME_1,                                                     \
                BIT_NAME_2,                                                     \
                BIT_NAME_3,                                                     \
                BIT_NAME_4,                                                     \
                BIT_NAME_5,                                                     \
                uint8_t,                                                        \
                STRUCT_NAME)

#define TOMMROC_BIT_FIELD_U8_6_FIELD_CONFIG_SET(                                \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_6_FIELD_CONFIG_SET(                                   \
                BIT_NAME_1,                                                     \
                BIT_NAME_2,                                                     \
                BIT_NAME_3,                                                     \
                BIT_NAME_4,                                                     \
                BIT_NAME_5,                                                     \
                BIT_NAME_6,                                                     \
                uint8_t,                                                        \
                STRUCT_NAME)

#define TOMMROC_BIT_FIELD_U8_7_FIELD_CONFIG_SET(                                \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_7_FIELD_CONFIG_SET(                                   \
                BIT_NAME_1,                                                     \
                BIT_NAME_2,                                                     \
                BIT_NAME_3,                                                     \
                BIT_NAME_4,                                                     \
                BIT_NAME_5,                                                     \
                BIT_NAME_6,                                                     \
                BIT_NAME_7,                                                     \
                uint8_t,                                                        \
                STRUCT_NAME)

#define TOMMROC_BIT_FIELD_U8_8_FIELD_CONFIG_SET(                                \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_8_FIELD_CONFIG_SET(                                   \
                BIT_NAME_1,                                                     \
                BIT_NAME_2,                                                     \
                BIT_NAME_3,                                                     \
                BIT_NAME_4,                                                     \
                BIT_NAME_5,                                                     \
                BIT_NAME_6,                                                     \
                BIT_NAME_7,                                                     \
                BIT_NAME_8,                                                     \
                uint8_t,                                                        \
                STRUCT_NAME)

#define TOMMROC_BIT_FIELD_U8_9_FIELD_CONFIG_SET(                                \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        BIT_NAME_9,                                                             \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_9_FIELD_CONFIG_SET(                                   \
                BIT_NAME_1,                                                     \
                BIT_NAME_2,                                                     \
                BIT_NAME_3,                                                     \
                BIT_NAME_4,                                                     \
                BIT_NAME_5,                                                     \
                BIT_NAME_6,                                                     \
                BIT_NAME_7,                                                     \
                BIT_NAME_8,                                                     \
                BIT_NAME_9,                                                     \
                uint8_t,                                                        \
                STRUCT_NAME)

#define TOMMROC_BIT_FIELD_U8_10_FIELD_CONFIG_SET(                               \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        BIT_NAME_9,                                                             \
        BIT_NAME_10,                                                            \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_10_FIELD_CONFIG_SET(                                  \
                BIT_NAME_1,                                                     \
                BIT_NAME_2,                                                     \
                BIT_NAME_3,                                                     \
                BIT_NAME_4,                                                     \
                BIT_NAME_5,                                                     \
                BIT_NAME_6,                                                     \
                BIT_NAME_7,                                                     \
                BIT_NAME_8,                                                     \
                BIT_NAME_9,                                                     \
                BIT_NAME_10,                                                    \
                uint8_t,                                                        \
                STRUCT_NAME)

#define TOMMROC_BIT_FIELD_U8_11_FIELD_CONFIG_SET(                               \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        BIT_NAME_9,                                                             \
        BIT_NAME_10,                                                            \
        BIT_NAME_11,                                                            \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_11_FIELD_CONFIG_SET(                                  \
                BIT_NAME_1,                                                     \
                BIT_NAME_2,                                                     \
                BIT_NAME_3,                                                     \
                BIT_NAME_4,                                                     \
                BIT_NAME_5,                                                     \
                BIT_NAME_6,                                                     \
                BIT_NAME_7,                                                     \
                BIT_NAME_8,                                                     \
                BIT_NAME_9,                                                     \
                BIT_NAME_10,                                                    \
                BIT_NAME_11,                                                    \
                uint8_t,                                                        \
                STRUCT_NAME)

#define TOMMROC_BIT_FIELD_U8_12_FIELD_CONFIG_SET(                               \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        BIT_NAME_9,                                                             \
        BIT_NAME_10,                                                            \
        BIT_NAME_11,                                                            \
        BIT_NAME_12,                                                            \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_12_FIELD_CONFIG_SET(                                  \
                BIT_NAME_1,                                                     \
                BIT_NAME_2,                                                     \
                BIT_NAME_3,                                                     \
                BIT_NAME_4,                                                     \
                BIT_NAME_5,                                                     \
                BIT_NAME_6,                                                     \
                BIT_NAME_7,                                                     \
                BIT_NAME_8,                                                     \
                BIT_NAME_9,                                                     \
                BIT_NAME_10,                                                    \
                BIT_NAME_11,                                                    \
                BIT_NAME_12,                                                    \
                uint8_t,                                                        \
                STRUCT_NAME)

#define TOMMROC_BIT_FIELD_U8_13_FIELD_CONFIG_SET(                               \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        BIT_NAME_9,                                                             \
        BIT_NAME_10,                                                            \
        BIT_NAME_11,                                                            \
        BIT_NAME_12,                                                            \
        BIT_NAME_13,                                                            \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_13_FIELD_CONFIG_SET(                                  \
                BIT_NAME_1,                                                     \
                BIT_NAME_2,                                                     \
                BIT_NAME_3,                                                     \
                BIT_NAME_4,                                                     \
                BIT_NAME_5,                                                     \
                BIT_NAME_6,                                                     \
                BIT_NAME_7,                                                     \
                BIT_NAME_8,                                                     \
                BIT_NAME_9,                                                     \
                BIT_NAME_10,                                                    \
                BIT_NAME_11,                                                    \
                BIT_NAME_12,                                                    \
                BIT_NAME_13,                                                    \
                uint8_t,                                                        \
                STRUCT_NAME)

#define TOMMROC_BIT_FIELD_U8_14_FIELD_CONFIG_SET(                               \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        BIT_NAME_9,                                                             \
        BIT_NAME_10,                                                            \
        BIT_NAME_11,                                                            \
        BIT_NAME_12,                                                            \
        BIT_NAME_13,                                                            \
        BIT_NAME_14,                                                            \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_14_FIELD_CONFIG_SET(                                  \
                BIT_NAME_1,                                                     \
                BIT_NAME_2,                                                     \
                BIT_NAME_3,                                                     \
                BIT_NAME_4,                                                     \
                BIT_NAME_5,                                                     \
                BIT_NAME_6,                                                     \
                BIT_NAME_7,                                                     \
                BIT_NAME_8,                                                     \
                BIT_NAME_9,                                                     \
                BIT_NAME_10,                                                    \
                BIT_NAME_11,                                                    \
                BIT_NAME_12,                                                    \
                BIT_NAME_13,                                                    \
                BIT_NAME_14,                                                    \
                uint8_t,                                                        \
                STRUCT_NAME)

#define TOMMROC_BIT_FIELD_U8_15_FIELD_CONFIG_SET(                               \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        BIT_NAME_9,                                                             \
        BIT_NAME_10,                                                            \
        BIT_NAME_11,                                                            \
        BIT_NAME_12,                                                            \
        BIT_NAME_13,                                                            \
        BIT_NAME_14,                                                            \
        BIT_NAME_15,                                                            \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_15_FIELD_CONFIG_SET(                                  \
                BIT_NAME_1,                                                     \
                BIT_NAME_2,                                                     \
                BIT_NAME_3,                                                     \
                BIT_NAME_4,                                                     \
                BIT_NAME_5,                                                     \
                BIT_NAME_6,                                                     \
                BIT_NAME_7,                                                     \
                BIT_NAME_8,                                                     \
                BIT_NAME_9,                                                     \
                BIT_NAME_10,                                                    \
                BIT_NAME_11,                                                    \
                BIT_NAME_12,                                                    \
                BIT_NAME_13,                                                    \
                BIT_NAME_14,                                                    \
                BIT_NAME_15,                                                    \
                uint8_t,                                                        \
                STRUCT_NAME)

#define TOMMROC_BIT_FIELD_U8_16_FIELD_CONFIG_SET(                               \
        BIT_NAME_1,                                                             \
        BIT_NAME_2,                                                             \
        BIT_NAME_3,                                                             \
        BIT_NAME_4,                                                             \
        BIT_NAME_5,                                                             \
        BIT_NAME_6,                                                             \
        BIT_NAME_7,                                                             \
        BIT_NAME_8,                                                             \
        BIT_NAME_9,                                                             \
        BIT_NAME_10,                                                            \
        BIT_NAME_11,                                                            \
        BIT_NAME_12,                                                            \
        BIT_NAME_13,                                                            \
        BIT_NAME_14,                                                            \
        BIT_NAME_15,                                                            \
        BIT_NAME_16,                                                            \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_16_FIELD_CONFIG_SET(                                  \
                BIT_NAME_1,                                                     \
                BIT_NAME_2,                                                     \
                BIT_NAME_3,                                                     \
                BIT_NAME_4,                                                     \
                BIT_NAME_5,                                                     \
                BIT_NAME_6,                                                     \
                BIT_NAME_7,                                                     \
                BIT_NAME_8,                                                     \
                BIT_NAME_9,                                                     \
                BIT_NAME_10,                                                    \
                BIT_NAME_11,                                                    \
                BIT_NAME_12,                                                    \
                BIT_NAME_13,                                                    \
                BIT_NAME_14,                                                    \
                BIT_NAME_15,                                                    \
                BIT_NAME_16,                                                    \
                uint8_t,                                                        \
                STRUCT_NAME)


/******************* Unsigned 16 bit field structure configuration set */

#define TOMMROC_BIT_FIELD_U16_1_FIELD_CONFIG_SET(                               \
        BIT_NAME_1,                                                             \
        STRUCT_NAME)                                                            \
                                                                                \
        TOMMROC_BIT_FIELD_1_FIELD_CONFIG_SET(                                   \
                BIT_NAME_1,                                                     \
                uint16_t,                                                       \
                STRUCT_NAME)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * @}
 */

#endif
