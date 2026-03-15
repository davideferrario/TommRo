
#ifndef TOMMROC_UNIT_MEASURE_H_
#define TOMMROC_UNIT_MEASURE_H_

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
 * @defgroup tommRoCUnitMeasure tommRoCUnitMeasure
 *
 * @brief  TommRoC library unit measure module
 * @author TommRo Software Department
 *
 * This module is providing unit measure define and conversion functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"
#include "tommRoCMath.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/**
 * Bit/byte unit measure conversion define.
 */
#define TOMMROC_UNIT_MEASURE_BIT_IN_ONE_BYTE                (8UL)
#define TOMMROC_UNIT_MEASURE_BYTE_IN_ONE_KBYTE              (1024UL)
#define TOMMROC_UNIT_MEASURE_KBYTE_IN_ONE_MBYTE             (1024UL)
#define TOMMROC_UNIT_MEASURE_BYTE_IN_ONE_MBYTE              (TOMMROC_UNIT_MEASURE_BYTE_IN_ONE_KBYTE * TOMMROC_UNIT_MEASURE_KBYTE_IN_ONE_MBYTE)

#define TOMMROC_UNIT_MEASURE_BYTE_TO_BIT(byte)              ((byte) * TOMMROC_UNIT_MEASURE_BIT_IN_ONE_BYTE)
#define TOMMROC_UNIT_MEASURE_KBYTE_TO_BYTE(KByte)           ((KByte) * TOMMROC_UNIT_MEASURE_BYTE_IN_ONE_KBYTE)
#define TOMMROC_UNIT_MEASURE_MBYTE_TO_KBYTE(MByte)          ((MByte) * TOMMROC_UNIT_MEASURE_KBYTE_IN_ONE_MBYTE)
#define TOMMROC_UNIT_MEASURE_MBYTE_TO_BYTE(MByte)           ((MByte) * TOMMROC_UNIT_MEASURE_BYTE_IN_ONE_MBYTE)

#define TOMMROC_UNIT_MEASURE_BIT_TO_BYTE(bit)               ((bit) / TOMMROC_UNIT_MEASURE_BIT_IN_ONE_BYTE)
#define TOMMROC_UNIT_MEASURE_BYTE_TO_KBYTE(byte)            ((byte) / TOMMROC_UNIT_MEASURE_BYTE_IN_ONE_KBYTE)
#define TOMMROC_UNIT_MEASURE_BYTE_TO_MBYTE(byte)            ((byte) / TOMMROC_UNIT_MEASURE_BYTE_IN_ONE_MBYTE)
#define TOMMROC_UNIT_MEASURE_KBYTE_TO_MBYTE(KByte)          ((KByte) / TOMMROC_UNIT_MEASURE_KBYTE_IN_ONE_MBYTE)

#define TOMMROC_UNIT_MEASURE_KBIT_TO_BIT(KBit)              (TOMMROC_UNIT_MEASURE_KBYTE_TO_BYTE(KBit))
#define TOMMROC_UNIT_MEASURE_MBIT_TO_KBIT(MBit)             (TOMMROC_UNIT_MEASURE_MBYTE_TO_KBYTE(MBit))
#define TOMMROC_UNIT_MEASURE_MBIT_TO_BIT(MBit)              (TOMMROC_UNIT_MEASURE_MBYTE_TO_BYTE(MBit))

#define TOMMROC_UNIT_MEASURE_BIT_TO_KBIT(bit)               (TOMMROC_UNIT_MEASURE_BYTE_TO_KBYTE(bit))
#define TOMMROC_UNIT_MEASURE_BIT_TO_MBIT(bit)               (TOMMROC_UNIT_MEASURE_BYTE_TO_MBYTE(bit))
#define TOMMROC_UNIT_MEASURE_KBIT_TO_MBIT(KBit)             (TOMMROC_UNIT_MEASURE_KBYTE_TO_MBYTE(KBit))


/**
 * Generic natural unit measure conversion define.
 *
 * Unit:    10 ^ 0
 * Kilo:    10 ^ 3
 * Mega:    10 ^ 6
 * Giga:    10 ^ 9
 * Milli:   10 ^ -3
 * Micro:   10 ^ -6
 * Nano:    10 ^ -9
 * Pico:    10 ^ -12
 */
#define TOMMROC_UNIT_MEASURE_PICO_IN_1_NANO                 (1000UL)
#define TOMMROC_UNIT_MEASURE_NANO_IN_1_MICRO                (1000UL)
#define TOMMROC_UNIT_MEASURE_MICRO_IN_1_MILLI               (1000UL)
#define TOMMROC_UNIT_MEASURE_MILLI_IN_1_UNIT                (1000UL)
#define TOMMROC_UNIT_MEASURE_UNIT_IN_1_KILO                 (1000UL)
#define TOMMROC_UNIT_MEASURE_KILO_IN_1_MEGA                 (1000UL)
#define TOMMROC_UNIT_MEASURE_MEGA_IN_1_GIGA                 (1000UL)

#define TOMMROC_UNIT_MEASURE_NANO_TO_PICO(nano)             ((nano)     * TOMMROC_UNIT_MEASURE_PICO_IN_1_NANO)
#define TOMMROC_UNIT_MEASURE_MICRO_TO_NANO(micro)           ((micro)    * TOMMROC_UNIT_MEASURE_NANO_IN_1_MICRO)
#define TOMMROC_UNIT_MEASURE_MILLI_TO_MICRO(milli)          ((milli)    * TOMMROC_UNIT_MEASURE_MICRO_IN_1_MILLI)
#define TOMMROC_UNIT_MEASURE_UNIT_TO_MILLI(unit)            ((unit)     * TOMMROC_UNIT_MEASURE_MILLI_IN_1_UNIT)
#define TOMMROC_UNIT_MEASURE_UNIT_TO_MICRO(unit)            ((unit)     * (TOMMROC_UNIT_MEASURE_MILLI_IN_1_UNIT * TOMMROC_UNIT_MEASURE_MICRO_IN_1_MILLI))
#define TOMMROC_UNIT_MEASURE_UNIT_TO_NANO(unit)             ((unit)     * (TOMMROC_UNIT_MEASURE_MILLI_IN_1_UNIT * TOMMROC_UNIT_MEASURE_MICRO_IN_1_MILLI * TOMMROC_UNIT_MEASURE_NANO_IN_1_MICRO))
#define TOMMROC_UNIT_MEASURE_UNIT_TO_PICO(unit)             ((unit)     * (TOMMROC_UNIT_MEASURE_MILLI_IN_1_UNIT * TOMMROC_UNIT_MEASURE_MICRO_IN_1_MILLI * TOMMROC_UNIT_MEASURE_NANO_IN_1_MICRO * TOMMROC_UNIT_MEASURE_PICO_IN_1_NANO))
#define TOMMROC_UNIT_MEASURE_KILO_TO_UNIT(kilo)             ((kilo)     * TOMMROC_UNIT_MEASURE_UNIT_IN_1_KILO)
#define TOMMROC_UNIT_MEASURE_MEGA_TO_KILO(mega)             ((mega)     * TOMMROC_UNIT_MEASURE_KILO_IN_1_MEGA)
#define TOMMROC_UNIT_MEASURE_MEGA_TO_UNIT(mega)             ((mega)     * (TOMMROC_UNIT_MEASURE_KILO_IN_1_MEGA * TOMMROC_UNIT_MEASURE_UNIT_IN_1_KILO))
#define TOMMROC_UNIT_MEASURE_GIGA_TO_MEGA(giga)             ((giga)     * TOMMROC_UNIT_MEASURE_MEGA_IN_1_GIGA)

#define TOMMROC_UNIT_MEASURE_PICO_TO_NANO(pico)             ((pico)     / TOMMROC_UNIT_MEASURE_PICO_IN_1_NANO)
#define TOMMROC_UNIT_MEASURE_NANO_TO_MICRO(nano)            ((nano)     / TOMMROC_UNIT_MEASURE_NANO_IN_1_MICRO)
#define TOMMROC_UNIT_MEASURE_MICRO_TO_MILLI(micro)          ((micro)    / TOMMROC_UNIT_MEASURE_MICRO_IN_1_MILLI)
#define TOMMROC_UNIT_MEASURE_MILLI_TO_UNIT(milli)           ((milli)    / TOMMROC_UNIT_MEASURE_MILLI_IN_1_UNIT)
#define TOMMROC_UNIT_MEASURE_MICRO_TO_UNIT(micro)           ((micro)    / (TOMMROC_UNIT_MEASURE_MILLI_IN_1_UNIT * TOMMROC_UNIT_MEASURE_MICRO_IN_1_MILLI))
#define TOMMROC_UNIT_MEASURE_NANO_TO_UNIT(nano)             ((nano)     / (TOMMROC_UNIT_MEASURE_MILLI_IN_1_UNIT * TOMMROC_UNIT_MEASURE_MICRO_IN_1_MILLI * TOMMROC_UNIT_MEASURE_NANO_IN_1_MICRO))
#define TOMMROC_UNIT_MEASURE_PICO_TO_UNIT(pico)             ((pico)     / (TOMMROC_UNIT_MEASURE_MILLI_IN_1_UNIT * TOMMROC_UNIT_MEASURE_MICRO_IN_1_MILLI * TOMMROC_UNIT_MEASURE_NANO_IN_1_MICRO * TOMMROC_UNIT_MEASURE_PICO_IN_1_NANO))
#define TOMMROC_UNIT_MEASURE_UNIT_TO_KILO(unit)             ((unit)     / TOMMROC_UNIT_MEASURE_UNIT_IN_1_KILO)
#define TOMMROC_UNIT_MEASURE_KILO_TO_MEGA(kilo)             ((kilo)     / TOMMROC_UNIT_MEASURE_KILO_IN_1_MEGA)
#define TOMMROC_UNIT_MEASURE_UNIT_TO_MEGA(unit)             ((unit)     / (TOMMROC_UNIT_MEASURE_KILO_IN_1_MEGA * TOMMROC_UNIT_MEASURE_UNIT_IN_1_KILO))
#define TOMMROC_UNIT_MEASURE_MEGA_TO_GIGA(mega)             ((mega)     / TOMMROC_UNIT_MEASURE_MEGA_IN_1_GIGA)

#define TOMMROC_UNIT_MEASURE_APPROX_PICO_TO_NANO(pico)      (TOMMROC_MATH_UINT_DIVIDE_APPROX((pico),    TOMMROC_UNIT_MEASURE_PICO_IN_1_NANO)
#define TOMMROC_UNIT_MEASURE_APPROX_NANO_TO_MICRO(nano)     (TOMMROC_MATH_UINT_DIVIDE_APPROX((nano),    TOMMROC_UNIT_MEASURE_NANO_IN_1_MICRO)
#define TOMMROC_UNIT_MEASURE_APPROX_MICRO_TO_MILLI(micro)   (TOMMROC_MATH_UINT_DIVIDE_APPROX((micro),   TOMMROC_UNIT_MEASURE_MICRO_IN_1_MILLI)
#define TOMMROC_UNIT_MEASURE_APPROX_MILLI_TO_UNIT(milli)    (TOMMROC_MATH_UINT_DIVIDE_APPROX((milli),   TOMMROC_UNIT_MEASURE_MILLI_IN_1_UNIT)
#define TOMMROC_UNIT_MEASURE_APPROX_MICRO_TO_UNIT(micro)    (TOMMROC_MATH_UINT_DIVIDE_APPROX((micro),   (TOMMROC_UNIT_MEASURE_MILLI_IN_1_UNIT * TOMMROC_UNIT_MEASURE_MICRO_IN_1_MILLI))
#define TOMMROC_UNIT_MEASURE_APPROX_NANO_TO_UNIT(nano)      (TOMMROC_MATH_UINT_DIVIDE_APPROX((nano),    (TOMMROC_UNIT_MEASURE_MILLI_IN_1_UNIT * TOMMROC_UNIT_MEASURE_MICRO_IN_1_MILLI * TOMMROC_UNIT_MEASURE_NANO_IN_1_MICRO))
#define TOMMROC_UNIT_MEASURE_APPROX_PICO_TO_UNIT(pico)      (TOMMROC_MATH_UINT_DIVIDE_APPROX((pico),    (TOMMROC_UNIT_MEASURE_MILLI_IN_1_UNIT * TOMMROC_UNIT_MEASURE_MICRO_IN_1_MILLI * TOMMROC_UNIT_MEASURE_NANO_IN_1_MICRO * TOMMROC_UNIT_MEASURE_PICO_IN_1_NANO))
#define TOMMROC_UNIT_MEASURE_APPROX_UNIT_TO_KILO(unit)      (TOMMROC_MATH_UINT_DIVIDE_APPROX((unit),    TOMMROC_UNIT_MEASURE_UNIT_IN_1_KILO))
#define TOMMROC_UNIT_MEASURE_APPROX_KILO_TO_MEGA(kilo)      (TOMMROC_MATH_UINT_DIVIDE_APPROX((kilo),    TOMMROC_UNIT_MEASURE_KILO_IN_1_MEGA))
#define TOMMROC_UNIT_MEASURE_APPROX_UNIT_TO_MEGA(unit)      (TOMMROC_MATH_UINT_DIVIDE_APPROX((unit),    (TOMMROC_UNIT_MEASURE_KILO_IN_1_MEGA * TOMMROC_UNIT_MEASURE_UNIT_IN_1_KILO))
#define TOMMROC_UNIT_MEASURE_APPROX_MEGA_TO_GIGA(mega)      (TOMMROC_MATH_UINT_DIVIDE_APPROX((mega),    TOMMROC_UNIT_MEASURE_MEGA_IN_1_GIGA))


/**
 * Time unit measure conversion define.
 */
#define TOMMROC_UNIT_MEASURE_TIME_pSEC_IN_A_nSEC            (TOMMROC_UNIT_MEASURE_PICO_IN_1_NANO)
#define TOMMROC_UNIT_MEASURE_TIME_nSEC_IN_A_uSEC            (TOMMROC_UNIT_MEASURE_NANO_IN_1_MICRO)
#define TOMMROC_UNIT_MEASURE_TIME_nSEC_IN_A_mSEC            (TOMMROC_UNIT_MEASURE_NANO_IN_1_MICRO * TOMMROC_UNIT_MEASURE_MICRO_IN_1_MILLI)
#define TOMMROC_UNIT_MEASURE_TIME_uSEC_IN_A_mSEC            (TOMMROC_UNIT_MEASURE_MICRO_IN_1_MILLI)
#define TOMMROC_UNIT_MEASURE_TIME_mSEC_IN_A_SEC             (TOMMROC_UNIT_MEASURE_MILLI_IN_1_UNIT)
#define TOMMROC_UNIT_MEASURE_TIME_SEC_IN_A_MIN              (60UL)
#define TOMMROC_UNIT_MEASURE_TIME_MIN_IN_A_HR               (60UL)
#define TOMMROC_UNIT_MEASURE_TIME_HR_IN_A_DAY               (24UL)
#define TOMMROC_UNIT_MEASURE_TIME_uSEC_IN_A_SEC             (TOMMROC_UNIT_MEASURE_TIME_mSEC_IN_A_SEC * TOMMROC_UNIT_MEASURE_TIME_uSEC_IN_A_mSEC)
#define TOMMROC_UNIT_MEASURE_TIME_nSEC_IN_A_SEC             (TOMMROC_UNIT_MEASURE_TIME_mSEC_IN_A_SEC * TOMMROC_UNIT_MEASURE_TIME_uSEC_IN_A_mSEC * TOMMROC_UNIT_MEASURE_TIME_nSEC_IN_A_uSEC)
#define TOMMROC_UNIT_MEASURE_TIME_pSEC_IN_A_SEC             (TOMMROC_UNIT_MEASURE_TIME_mSEC_IN_A_SEC * TOMMROC_UNIT_MEASURE_TIME_uSEC_IN_A_mSEC * TOMMROC_UNIT_MEASURE_TIME_nSEC_IN_A_uSEC * TOMMROC_UNIT_MEASURE_TIME_pSEC_IN_A_nSEC)

#define TOMMROC_UNIT_MEASURE_TIME_nSEC_TO_pSEC(nsec)        ((nsec) * TOMMROC_UNIT_MEASURE_TIME_pSEC_IN_A_nSEC)
#define TOMMROC_UNIT_MEASURE_TIME_uSEC_TO_nSEC(usec)        ((usec) * TOMMROC_UNIT_MEASURE_TIME_nSEC_IN_A_uSEC)
#define TOMMROC_UNIT_MEASURE_TIME_mSEC_TO_uSEC(msec)        ((msec) * TOMMROC_UNIT_MEASURE_TIME_uSEC_IN_A_mSEC)
#define TOMMROC_UNIT_MEASURE_TIME_mSEC_TO_nSEC(msec)        ((msec) * TOMMROC_UNIT_MEASURE_TIME_nSEC_IN_A_mSEC)
#define TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(sec)          ((sec)  * TOMMROC_UNIT_MEASURE_TIME_mSEC_IN_A_SEC)
#define TOMMROC_UNIT_MEASURE_TIME_MIN_TO_SEC(min)           ((min)  * TOMMROC_UNIT_MEASURE_TIME_SEC_IN_A_MIN)
#define TOMMROC_UNIT_MEASURE_TIME_HRS_TO_MIN(hrs)           ((hrs)  * TOMMROC_UNIT_MEASURE_TIME_MIN_IN_A_HR)
#define TOMMROC_UNIT_MEASURE_TIME_HRS_TO_SEC(hrs)           (TOMMROC_UNIT_MEASURE_TIME_MIN_TO_SEC(TOMMROC_UNIT_MEASURE_TIME_HRS_TO_MIN(hrs)))
#define TOMMROC_UNIT_MEASURE_TIME_DAYS_TO_HRS(days)         ((days) * TOMMROC_UNIT_MEASURE_TIME_HR_IN_A_DAY)
#define TOMMROC_UNIT_MEASURE_TIME_SEC_TO_uSEC(sec)          ((sec)  * TOMMROC_UNIT_MEASURE_TIME_uSEC_IN_A_SEC)
#define TOMMROC_UNIT_MEASURE_TIME_SEC_TO_nSEC(sec)          ((sec)  * TOMMROC_UNIT_MEASURE_TIME_nSEC_IN_A_SEC)
#define TOMMROC_UNIT_MEASURE_TIME_SEC_TO_pSEC(sec)          ((sec)  * TOMMROC_UNIT_MEASURE_TIME_pSEC_IN_A_SEC)
#define TOMMROC_UNIT_MEASURE_TIME_MIN_TO_mSEC(min)          (TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(TOMMROC_UNIT_MEASURE_TIME_MIN_TO_SEC(min)))
#define TOMMROC_UNIT_MEASURE_TIME_HRS_TO_mSEC(hrs)          (TOMMROC_UNIT_MEASURE_TIME_MIN_TO_mSEC(TOMMROC_UNIT_MEASURE_TIME_HRS_TO_MIN(hrs)))
#define TOMMROC_UNIT_MEASURE_TIME_DAYS_TO_mSEC(days)        (TOMMROC_UNIT_MEASURE_TIME_HRS_TO_mSEC(TOMMROC_UNIT_MEASURE_TIME_DAYS_TO_HRS(days)))

#define TOMMROC_UNIT_MEASURE_TIME_pSEC_TO_SEC(psec)         ((psec) / TOMMROC_UNIT_MEASURE_TIME_pSEC_IN_A_SEC)
#define TOMMROC_UNIT_MEASURE_TIME_pSEC_TO_nSEC(psec)        ((psec) / TOMMROC_UNIT_MEASURE_TIME_pSEC_IN_A_nSEC)
#define TOMMROC_UNIT_MEASURE_TIME_nSEC_TO_SEC(nsec)         ((nsec) / TOMMROC_UNIT_MEASURE_TIME_nSEC_IN_A_SEC)
#define TOMMROC_UNIT_MEASURE_TIME_nSEC_TO_mSEC(nsec)        ((nsec) / TOMMROC_UNIT_MEASURE_TIME_nSEC_IN_A_mSEC)
#define TOMMROC_UNIT_MEASURE_TIME_nSEC_TO_uSEC(nsec)        ((nsec) / TOMMROC_UNIT_MEASURE_TIME_nSEC_IN_A_uSEC)
#define TOMMROC_UNIT_MEASURE_TIME_uSEC_TO_SEC(usec)         ((usec) / TOMMROC_UNIT_MEASURE_TIME_uSEC_IN_A_SEC)
#define TOMMROC_UNIT_MEASURE_TIME_uSEC_TO_mSEC(usec)        ((usec) / TOMMROC_UNIT_MEASURE_TIME_uSEC_IN_A_mSEC)
#define TOMMROC_UNIT_MEASURE_TIME_mSEC_TO_SEC(msec)         ((msec) / TOMMROC_UNIT_MEASURE_TIME_mSEC_IN_A_SEC)
#define TOMMROC_UNIT_MEASURE_TIME_SEC_TO_MIN(sec)           ((sec)  / TOMMROC_UNIT_MEASURE_TIME_SEC_IN_A_MIN)
#define TOMMROC_UNIT_MEASURE_TIME_MIN_TO_HRS(min)           ((min)  / TOMMROC_UNIT_MEASURE_TIME_MIN_IN_A_HR)
#define TOMMROC_UNIT_MEASURE_TIME_HRS_TO_DAYS(hrs)          ((hrs)  / TOMMROC_UNIT_MEASURE_TIME_HR_IN_A_DAY)

#define TOMMROC_UNIT_MEASURE_TIME_APPROX_pSEC_TO_SEC(psec)  (TOMMROC_MATH_UINT_DIVIDE_APPROX((psec),    TOMMROC_UNIT_MEASURE_TIME_pSEC_IN_A_SEC))
#define TOMMROC_UNIT_MEASURE_TIME_APPROX_pSEC_TO_nSEC(psec) (TOMMROC_MATH_UINT_DIVIDE_APPROX((psec),    TOMMROC_UNIT_MEASURE_TIME_pSEC_IN_A_nSEC))
#define TOMMROC_UNIT_MEASURE_TIME_APPROX_nSEC_TO_SEC(nsec)  (TOMMROC_MATH_UINT_DIVIDE_APPROX((nsec),    TOMMROC_UNIT_MEASURE_TIME_nSEC_IN_A_SEC))
#define TOMMROC_UNIT_MEASURE_TIME_APPROX_nSEC_TO_mSEC(nsec) (TOMMROC_MATH_UINT_DIVIDE_APPROX((nsec),    TOMMROC_UNIT_MEASURE_TIME_nSEC_IN_A_mSEC))
#define TOMMROC_UNIT_MEASURE_TIME_APPROX_nSEC_TO_uSEC(nsec) (TOMMROC_MATH_UINT_DIVIDE_APPROX((nsec),    TOMMROC_UNIT_MEASURE_TIME_nSEC_IN_A_uSEC))
#define TOMMROC_UNIT_MEASURE_TIME_APPROX_uSEC_TO_SEC(usec)  (TOMMROC_MATH_UINT_DIVIDE_APPROX((usec),    TOMMROC_UNIT_MEASURE_TIME_uSEC_IN_A_SEC))
#define TOMMROC_UNIT_MEASURE_TIME_APPROX_uSEC_TO_mSEC(usec) (TOMMROC_MATH_UINT_DIVIDE_APPROX((usec),    TOMMROC_UNIT_MEASURE_TIME_uSEC_IN_A_mSEC))
#define TOMMROC_UNIT_MEASURE_TIME_APPROX_mSEC_TO_SEC(msec)  (TOMMROC_MATH_UINT_DIVIDE_APPROX((msec),    TOMMROC_UNIT_MEASURE_TIME_mSEC_IN_A_SEC))
#define TOMMROC_UNIT_MEASURE_TIME_APPROX_SEC_TO_MIN(sec)    (TOMMROC_MATH_UINT_DIVIDE_APPROX((sec),     TOMMROC_UNIT_MEASURE_TIME_SEC_IN_A_MIN))
#define TOMMROC_UNIT_MEASURE_TIME_APPROX_MIN_TO_HRS(min)    (TOMMROC_MATH_UINT_DIVIDE_APPROX((min),     TOMMROC_UNIT_MEASURE_TIME_MIN_IN_A_HR))
#define TOMMROC_UNIT_MEASURE_TIME_APPROX_HRS_TO_DAYS(hrs)   (TOMMROC_MATH_UINT_DIVIDE_APPROX((hrs),     TOMMROC_UNIT_MEASURE_TIME_HR_IN_A_DAY))


/**
 * Frequency unit measure conversion define.
 */
#define TOMMROC_UNIT_MEASURE_FREQ_HZ_IN_A_KHZ               (TOMMROC_UNIT_MEASURE_UNIT_IN_1_KILO)
#define TOMMROC_UNIT_MEASURE_FREQ_KHZ_IN_A_MHZ              (TOMMROC_UNIT_MEASURE_KILO_IN_1_MEGA)
#define TOMMROC_UNIT_MEASURE_FREQ_MHZ_IN_A_GHZ              (TOMMROC_UNIT_MEASURE_MEGA_IN_1_GIGA)

#define TOMMROC_UNIT_MEASURE_FREQ_KHZ_TO_HZ(KHz)            (TOMMROC_UNIT_MEASURE_KILO_TO_UNIT(KHz))
#define TOMMROC_UNIT_MEASURE_FREQ_MHZ_TO_KHZ(MHz)           (TOMMROC_UNIT_MEASURE_MEGA_TO_KILO(MHz))
#define TOMMROC_UNIT_MEASURE_FREQ_GHZ_TO_MHZ(GHz)           (TOMMROC_UNIT_MEASURE_GIGA_TO_MEGA(GHz))

#define TOMMROC_UNIT_MEASURE_FREQ_APPROX_HZ_TO_KHZ(Hz)      (TOMMROC_UNIT_MEASURE_APPROX_UNIT_TO_KILO(Hz))
#define TOMMROC_UNIT_MEASURE_FREQ_APPROX_KHZ_TO_MHZ(KHz)    (TOMMROC_UNIT_MEASURE_APPROX_KILO_TO_MEGA(KHz))
#define TOMMROC_UNIT_MEASURE_FREQ_APPROX_MHZ_TO_GHZ(MHz)    (TOMMROC_UNIT_MEASURE_APPROX_MEGA_TO_GIGA(MHz))


/**
 * Period to Frequency unit measure conversion define.
 */
#define TOMMROC_UNIT_MEASURE_PERIOD_SEC_TO_FREQ_HZ(sec)     (TOMMROC_MATH_UINT_DIVIDE_APPROX(1UL, sec))
#define TOMMROC_UNIT_MEASURE_PERIOD_mSEC_TO_FREQ_HZ(msec)   (TOMMROC_MATH_UINT_DIVIDE_APPROX(TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(1), msec))
#define TOMMROC_UNIT_MEASURE_PERIOD_uSEC_TO_FREQ_HZ(usec)   (TOMMROC_MATH_UINT_DIVIDE_APPROX(TOMMROC_UNIT_MEASURE_TIME_SEC_TO_uSEC(1), usec))


/**
 * Frequency to Period unit measure conversion define.
 */
#define TOMMROC_UNIT_MEASURE_FREQ_HZ_TO_PERIOD_SEC(Hz)      (TOMMROC_MATH_UINT_DIVIDE_APPROX(1UL, Hz))
#define TOMMROC_UNIT_MEASURE_FREQ_HZ_TO_PERIOD_mSEC(Hz)     (TOMMROC_MATH_UINT_DIVIDE_APPROX(TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(1), Hz))
#define TOMMROC_UNIT_MEASURE_FREQ_HZ_TO_PERIOD_uSEC(Hz)     (TOMMROC_MATH_UINT_DIVIDE_APPROX(TOMMROC_UNIT_MEASURE_TIME_SEC_TO_uSEC(1), Hz))

#define TOMMROC_UNIT_MEASURE_FREQ_KHZ_TO_PERIOD_SEC(KHz)    (TOMMROC_MATH_UINT_DIVIDE_APPROX(1UL, TOMMROC_UNIT_MEASURE_FREQ_KHZ_TO_HZ(KHz)))
#define TOMMROC_UNIT_MEASURE_FREQ_KHZ_TO_PERIOD_mSEC(KHz)   (TOMMROC_MATH_UINT_DIVIDE_APPROX(TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(1), TOMMROC_UNIT_MEASURE_FREQ_KHZ_TO_HZ(KHz)))
#define TOMMROC_UNIT_MEASURE_FREQ_KHZ_TO_PERIOD_uSEC(KHz)   (TOMMROC_MATH_UINT_DIVIDE_APPROX(TOMMROC_UNIT_MEASURE_TIME_SEC_TO_uSEC(1), TOMMROC_UNIT_MEASURE_FREQ_KHZ_TO_HZ(KHz)))

#define TOMMROC_UNIT_MEASURE_FREQ_MHZ_TO_PERIOD_SEC(MHz)    (TOMMROC_MATH_UINT_DIVIDE_APPROX(1UL, TOMMROC_UNIT_MEASURE_FREQ_MHZ_TO_HZ(MHz)))
#define TOMMROC_UNIT_MEASURE_FREQ_MHZ_TO_PERIOD_mSEC(MHz)   (TOMMROC_MATH_UINT_DIVIDE_APPROX(TOMMROC_UNIT_MEASURE_TIME_SEC_TO_mSEC(1), TOMMROC_UNIT_MEASURE_FREQ_KHZ_TO_HZ(TOMMROC_UNIT_MEASURE_FREQ_MHZ_TO_KHZ(MHz))))
#define TOMMROC_UNIT_MEASURE_FREQ_MHZ_TO_PERIOD_uSEC(MHz)   (TOMMROC_MATH_UINT_DIVIDE_APPROX(TOMMROC_UNIT_MEASURE_TIME_SEC_TO_uSEC(1), TOMMROC_UNIT_MEASURE_FREQ_KHZ_TO_HZ(TOMMROC_UNIT_MEASURE_FREQ_MHZ_TO_KHZ(MHz))))


/**
 * Electric/electronic unit measure conversion define.
 */
#define TOMMROC_UNIT_MEASURE_RESISTANCE_OHM_IN_A_KOHM       (TOMMROC_UNIT_MEASURE_UNIT_IN_1_KILO)
#define TOMMROC_UNIT_MEASURE_RESISTANCE_KOHM_IN_A_MOHM      (TOMMROC_UNIT_MEASURE_KILO_IN_1_MEGA)

#define TOMMROC_UNIT_MEASURE_RESISTANCE_mOHM_TO_OHM(mOhm)   (TOMMROC_UNIT_MEASURE_MILLI_TO_UNIT(mOhm))
#define TOMMROC_UNIT_MEASURE_RESISTANCE_OHM_TO_KOHM(Ohm)    (TOMMROC_UNIT_MEASURE_UNIT_TO_KILO(Ohm))
#define TOMMROC_UNIT_MEASURE_RESISTANCE_KOHM_TO_MOHM(KOhm)  (TOMMROC_UNIT_MEASURE_KILO_TO_MEGA(KOhm))

#define TOMMROC_UNIT_MEASURE_RESISTANCE_KOHM_TO_OHM(KOhm)   (TOMMROC_UNIT_MEASURE_KILO_TO_UNIT(KOhm))
#define TOMMROC_UNIT_MEASURE_RESISTANCE_MOHM_TO_KOHM(MOhm)  (TOMMROC_UNIT_MEASURE_MEGA_TO_KILO(MOhm))
#define TOMMROC_UNIT_MEASURE_RESISTANCE_MOHM_TO_OHM(MOhm)   (TOMMROC_UNIT_MEASURE_MEGA_TO_UNIT(MOhm))


/**
 * Acceleration unit measure conversion define.
 */
#define TOMMROC_UNIT_MEASURE_ACC_G_TO_mG(g)                 (TOMMROC_UNIT_MEASURE_UNIT_TO_MILLI(g))
#define TOMMROC_UNIT_MEASURE_ACC_mG_TO_G(mg)                (TOMMROC_UNIT_MEASURE_MILLI_TO_UNIT(mg))


/**
 * Magnetic field unit measure conversion define - Tesla.
 */
#define TOMMROC_UNIT_MEASURE_MAGNETIC_FIELD_mT_TO_uT(mT)    (TOMMROC_UNIT_MEASURE_MILLI_TO_MICRO(mT))
#define TOMMROC_UNIT_MEASURE_MAGNETIC_FIELD_T_TO_mT(T)      (TOMMROC_UNIT_MEASURE_UNIT_TO_MILLI(T))
#define TOMMROC_UNIT_MEASURE_MAGNETIC_FIELD_T_TO_uT(T)      (TOMMROC_UNIT_MEASURE_UNIT_TO_MICRO(T))

#define TOMMROC_UNIT_MEASURE_MAGNETIC_FIELD_uT_TO_mT(uT)    (TOMMROC_UNIT_MEASURE_MICRO_TO_MILLI(uT))
#define TOMMROC_UNIT_MEASURE_MAGNETIC_FIELD_uT_TO_T(uT)     (TOMMROC_UNIT_MEASURE_MICRO_TO_UNIT(uT))
#define TOMMROC_UNIT_MEASURE_MAGNETIC_FIELD_mT_TO_T(mT)     (TOMMROC_UNIT_MEASURE_MILLI_TO_UNIT(mT))


/**
 * Magnetic field unit measure conversion define - Gauss.
 */
#define TOMMROC_UNIT_MEASURE_MAGNETIC_FIELD_mG_TO_uG(mG)    (TOMMROC_UNIT_MEASURE_MILLI_TO_MICRO(mG))
#define TOMMROC_UNIT_MEASURE_MAGNETIC_FIELD_G_TO_mG(G)      (TOMMROC_UNIT_MEASURE_UNIT_TO_MILLI(G))
#define TOMMROC_UNIT_MEASURE_MAGNETIC_FIELD_G_TO_uG(G)      (TOMMROC_UNIT_MEASURE_UNIT_TO_MICRO(G))

#define TOMMROC_UNIT_MEASURE_MAGNETIC_FIELD_uG_TO_mG(uG)    (TOMMROC_UNIT_MEASURE_MICRO_TO_MILLI(uG))
#define TOMMROC_UNIT_MEASURE_MAGNETIC_FIELD_uG_TO_G(uG)     (TOMMROC_UNIT_MEASURE_MICRO_TO_UNIT(uG))
#define TOMMROC_UNIT_MEASURE_MAGNETIC_FIELD_mG_TO_G(mG)     (TOMMROC_UNIT_MEASURE_MILLI_TO_UNIT(mG))


/**
 * tommRoC acceleration unit measure.
 */
#define TOMMROC_UNIT_MEASURE_ACCELERATION_GRAVITY_M_S2      (9.80665f)


/**
 * tommRoC pressure unit measure type.
 */
#define TOMMROC_UNIT_MEASURE_PRESSURE_ATMOSFERIC_PA         (101325.0f)
#define TOMMROC_UNIT_MEASURE_PRESSURE_ATMOSFERIC_ATM        (1.0f)
#define TOMMROC_UNIT_MEASURE_PRESSURE_ATMOSFERIC_TORR       (760.0f)
#define TOMMROC_UNIT_MEASURE_PRESSURE_ATMOSFERIC_BAR        (1.01325f)

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * tommRoC time unit measure type.
 */
typedef float tommRoC_unit_measure_time_seconds_t;              // [s]

/**
 * tommRoC length unit measure type.
 */
typedef float tommRoC_unit_measure_length_meter_t;              // [m]

/**
 * tommRoC speed unit measure type.
 */
typedef float tommRoC_unit_measure_speed_m_s_t;                 // [m/s]

/**
 * tommRoC acceleration unit measure type.
 */
typedef float tommRoC_unit_measure_acceleration_m_s2_t;         // [m/s^2]
typedef float tommRoC_unit_measure_acceleration_g_t;            // [g]

/**
 * tommRoC angle unit measure type.
 */
typedef float tommRoC_unit_measure_angle_degree_t;              // [degree]
typedef float tommRoC_unit_measure_angle_radian_t;              // [radian]

/**
 * tommRoC percentage unit measure type.
 */
typedef float tommRoC_unit_measure_percentage_t;                // [% Relative]
                                                                // 1% -> 0.01f
                                                                // 50% -> 0.5f
                                                                // 100% -> 1.0f
typedef float tommRoC_unit_measure_percentage_x_100_t;          // [% Percentage * 100]
                                                                // 1% -> 1.0f
                                                                // 50% -> 50.0f
                                                                // 100% -> 100.0f

/**
 * tommRoC humidity unit measure type.
 */
typedef float tommRoC_unit_measure_humidity_kg_m3_t;                                            // [kg/m3]
typedef tommRoC_unit_measure_percentage_t tommRoC_unit_measure_humidity_relative_t;             // [Relative]
                                                                                                // Humidity = 1% -> 0.01f
                                                                                                //          = 50% -> 0.5f
                                                                                                //          = 100% -> 1.0f
typedef tommRoC_unit_measure_percentage_x_100_t tommRoC_unit_measure_humidity_relative_x_100_t; // [Percentage * 100]
                                                                                                // Humidity = 1% -> 1.0f
                                                                                                //          = 50% -> 50.0f
                                                                                                //          = 100% -> 100.0f

/**
 * tommRoC temperature unit measure type.
 */
typedef float tommRoC_unit_measure_temperature_celsius_t;       // [Celsius]
typedef float tommRoC_unit_measure_temperature_kelvin_t;        // [Kelvin]
typedef float tommRoC_unit_measure_temperature_fahrenheit_t;    // [Fahrenheit]

/**
 * tommRoC electric/electronic unit measure type.
 */
typedef float tommRoC_unit_measure_voltage_volt_t;              // [Volt]
typedef float tommRoC_unit_measure_current_ampere_t;            // [Ampere]
typedef float tommRoC_unit_measure_resistance_ohm_t;            // [Ohm]
typedef float tommRoC_unit_measure_capacity_ampere_hour_t;      // [Ampere/hour]

/**
 * tommRoC magnetic field unit measure type.
 */
typedef float tommRoC_unit_measure_magnetic_field_gauss_t;      // [Gauss]
typedef float tommRoC_unit_measure_magnetic_field_tesla_t;      // [Tesla]

/**
 * tommRoC pressure unit measure type.
 */
typedef float tommRoC_unit_measure_pressure_pa_t;               // [Pascal - Pa]
typedef float tommRoC_unit_measure_pressure_atm_t;              // [atm]
typedef float tommRoC_unit_measure_pressure_torr_t;             // [torr]
typedef float tommRoC_unit_measure_pressure_bar_t;              // [bar]

/**
 * tommRoC NMEA locations unit measure type.
 */
typedef char* tommRoC_unit_measure_nmea_latitude_t;             // NMEA latitude    - ddmm.mmmm,N/S     - d=degrees and m=minutes
typedef char* tommRoC_unit_measure_nmea_longitude_t;            // NMEA longitude   - (d)ddmm.mmmm,E/W  - d=degrees and m=minutes

/**
 * tommRoC decimal degrees locations unit measure type.
 */
typedef float tommRoC_unit_measure_degrees_latitude_t;          // Latitude
typedef float tommRoC_unit_measure_degrees_longitude_t;         // Longitude

/**
 * tommRoC CO2 unit measure type.
 */
typedef float tommRoC_unit_measure_co2_ppm_t;                   // CO2 ppm

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Acceleration unit measure conversion.
 *
 * param[in]        inValue                 input value.
 * param[out]       outValuePtr             output value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUnitMeasureAccelerationMs2ToG(
        const   tommRoC_unit_measure_acceleration_m_s2_t                inValue,
                tommRoC_unit_measure_acceleration_g_t*          const   outValuePtr);
tommRoC_err_enum_t tommRoCUnitMeasureAccelerationGToMs2(
        const   tommRoC_unit_measure_acceleration_g_t                   inValue,
                tommRoC_unit_measure_acceleration_m_s2_t*       const   outValuePtr);

/**
 * Angle unit measure conversion.
 *
 * param[in]        inValue                 input value.
 * param[out]       outValuePtr             output value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUnitMeasureAngleDegreeToRadian(
        const   tommRoC_unit_measure_angle_degree_t                     inValue,
                tommRoC_unit_measure_angle_radian_t*            const   outValuePtr);
tommRoC_err_enum_t tommRoCUnitMeasureAngleRadianToDegree(
        const   tommRoC_unit_measure_angle_radian_t                     inValue,
                tommRoC_unit_measure_angle_degree_t*            const   outValuePtr);


/**
 * Humidity unit measure conversion.
 *
 * param[in]        inValue                 input value.
 * param[out]       outValuePtr             output value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUnitMeasureHumidityRelativeToRelativeX100(
        const   tommRoC_unit_measure_humidity_relative_t                inValue,
                tommRoC_unit_measure_humidity_relative_x_100_t* const   outValuePtr);
tommRoC_err_enum_t tommRoCUnitMeasureHumidityRelativeX100ToRelative(
        const   tommRoC_unit_measure_humidity_relative_x_100_t          inValue,
                tommRoC_unit_measure_humidity_relative_t*       const   outValuePtr);


/**
 * Temperature unit measure conversion.
 *
 * param[in]        inValue                 input value.
 * param[out]       outValuePtr             output value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUnitMeasureTemperatureCelsiusToKelvin(
        const   tommRoC_unit_measure_temperature_celsius_t              inValue,
                tommRoC_unit_measure_temperature_kelvin_t*      const   outValuePtr);
tommRoC_err_enum_t tommRoCUnitMeasureTemperatureCelsiusToFahrenheit(
        const   tommRoC_unit_measure_temperature_celsius_t              inValue,
                tommRoC_unit_measure_temperature_fahrenheit_t*  const   outValuePtr);

tommRoC_err_enum_t tommRoCUnitMeasureTemperatureKelvinToCelsius(
        const   tommRoC_unit_measure_temperature_kelvin_t               inValue,
                tommRoC_unit_measure_temperature_celsius_t*     const   outValuePtr);
tommRoC_err_enum_t tommRoCUnitMeasureTemperatureKelvinToFahrenheit(
        const   tommRoC_unit_measure_temperature_kelvin_t               inValue,
                tommRoC_unit_measure_temperature_fahrenheit_t*  const   outValuePtr);

tommRoC_err_enum_t tommRoCUnitMeasureTemperatureFahrenheitToCelsius(
        const   tommRoC_unit_measure_temperature_fahrenheit_t           inValue,
                tommRoC_unit_measure_temperature_celsius_t*     const   outValuePtr);
tommRoC_err_enum_t tommRoCUnitMeasureTemperatureFahrenheitToKelvin(
        const   tommRoC_unit_measure_temperature_fahrenheit_t           inValue,
                tommRoC_unit_measure_temperature_kelvin_t*      const   outValuePtr);


/**
 * Pressure unit measure conversion.
 *
 * param[in]        inValue                 input value.
 * param[out]       outValuePtr             output value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUnitMeasurePressurePascalToAtm(
        const   tommRoC_unit_measure_pressure_pa_t                      inValue,
                tommRoC_unit_measure_pressure_atm_t*            const   outValuePtr);
tommRoC_err_enum_t tommRoCUnitMeasurePressurePascalToTorr(
        const   tommRoC_unit_measure_pressure_pa_t                      inValue,
                tommRoC_unit_measure_pressure_torr_t*           const   outValuePtr);
tommRoC_err_enum_t tommRoCUnitMeasurePressurePascalToBar(
        const   tommRoC_unit_measure_pressure_pa_t                      inValue,
                tommRoC_unit_measure_pressure_bar_t*            const   outValuePtr);

tommRoC_err_enum_t tommRoCUnitMeasurePressureAtmToPascal(
        const   tommRoC_unit_measure_pressure_atm_t                     inValue,
                tommRoC_unit_measure_pressure_pa_t*             const   outValuePtr);
tommRoC_err_enum_t tommRoCUnitMeasurePressureAtmToTorr(
        const   tommRoC_unit_measure_pressure_atm_t                     inValue,
                tommRoC_unit_measure_pressure_torr_t*           const   outValuePtr);
tommRoC_err_enum_t tommRoCUnitMeasurePressureAtmToBar(
        const   tommRoC_unit_measure_pressure_atm_t                     inValue,
                tommRoC_unit_measure_pressure_bar_t*            const   outValuePtr);

tommRoC_err_enum_t tommRoCUnitMeasurePressureTorrToPascal(
        const   tommRoC_unit_measure_pressure_torr_t                    inValue,
                tommRoC_unit_measure_pressure_pa_t*             const   outValuePtr);
tommRoC_err_enum_t tommRoCUnitMeasurePressureTorrToAtm(
        const   tommRoC_unit_measure_pressure_torr_t                    inValue,
                tommRoC_unit_measure_pressure_atm_t*            const   outValuePtr);
tommRoC_err_enum_t tommRoCUnitMeasurePressureTorrToBar(
        const   tommRoC_unit_measure_pressure_torr_t                    inValue,
                tommRoC_unit_measure_pressure_bar_t*            const   outValuePtr);

tommRoC_err_enum_t tommRoCUnitMeasurePressureBarToPascal(
        const   tommRoC_unit_measure_pressure_bar_t                     inValue,
                tommRoC_unit_measure_pressure_pa_t*             const   outValuePtr);
tommRoC_err_enum_t tommRoCUnitMeasurePressureBarToAtm(
        const   tommRoC_unit_measure_pressure_bar_t                     inValue,
                tommRoC_unit_measure_pressure_atm_t*            const   outValuePtr);
tommRoC_err_enum_t tommRoCUnitMeasurePressureBarToTorr(
        const   tommRoC_unit_measure_pressure_bar_t                     inValue,
                tommRoC_unit_measure_pressure_torr_t*           const   outValuePtr);


/**
 * Locations unit measure conversion.
 *
 * param[in]        inValue                 input value.
 * param[out]       outValuePtr             output value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUnitMeasureLocationLatitudeNMEAToDegrees(
        const   tommRoC_unit_measure_nmea_latitude_t                    inValue,
                tommRoC_unit_measure_degrees_latitude_t*        const   outValuePtr);

tommRoC_err_enum_t tommRoCUnitMeasureLocationLongitudeNMEAToDegrees(
        const   tommRoC_unit_measure_nmea_longitude_t                   inValue,
                tommRoC_unit_measure_degrees_longitude_t*       const   outValuePtr);


/**
 * Magnetic field unit measure conversion.
 *
 * param[in]        inValue                 input value.
 * param[out]       outValuePtr             output value pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCUnitMeasureMagneticFieldGaussToTesla(
        const   tommRoC_unit_measure_magnetic_field_gauss_t             inValue,
                tommRoC_unit_measure_magnetic_field_tesla_t*    const   outValuePtr);

tommRoC_err_enum_t tommRoCUnitMeasureMagneticFieldTeslaToGauss(
        const   tommRoC_unit_measure_magnetic_field_tesla_t             inValue,
                tommRoC_unit_measure_magnetic_field_gauss_t*    const   outValuePtr);

/**
 * @}
 */

#endif
