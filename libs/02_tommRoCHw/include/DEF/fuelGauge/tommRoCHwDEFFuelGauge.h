
#ifndef TOMMROC_HW_DEF_FUEL_GAUGE_H_
#define TOMMROC_HW_DEF_FUEL_GAUGE_H_

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

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/

// Enumeration of tommRoC hardware fuel gauge readable values.
typedef enum {

    /**
     * Voltage value [volt].
     *
     * Available:   get
     * Notes:       valuePtr has to be tommRoC_unit_measure_voltage_volt_t*
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_VOLTAGE = 0,

    /**
     * Temperature value [°C].
     *
     * Available:   get
     * Notes:       valuePtr has to be tommRoC_unit_measure_temperature_celsius_t*
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TEMPERATURE_C,

    /**
     * Temperature value [°K].
     *
     * Available:   get
     * Notes:       valuePtr has to be tommRoC_unit_measure_temperature_kelvin_t*
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TEMPERATURE_K,


    /**
     * Internal temperature value [°C].
     *
     * Available:   get
     * Notes:       valuePtr has to be tommRoC_unit_measure_temperature_celsius_t*
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_INTERNAL_TEMPERATURE_C,

    /**
     * Internal temperature value [°K].
     *
     * Available:   get
     * Notes:       valuePtr has to be tommRoC_unit_measure_temperature_kelvin_t*
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_INTERNAL_TEMPERATURE_K,

    /**
     * Current value [A].
     *
     * Available:   get
     * Notes:       valuePtr has to be tommRoC_unit_measure_current_ampere_t*
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_CURRENT,

    /**
     * Reported remaining capacity value [Ah].
     *
     * Available:   get
     * Notes:       valuePtr has to be tommRoC_unit_measure_capacity_ampere_hour_t*
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_REMAINING_CAPACITY,

    /**
     * Reported accumulated capacity value [Ah].
     *
     * Available:   get
     * Notes:       valuePtr has to be tommRoC_unit_measure_capacity_ampere_hour_t*
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_ACCUMULATED_CAPACITY,

    /**
     * Reported design capacity value [Ah].
     *
     * Available:   get
     * Notes:       valuePtr has to be tommRoC_unit_measure_capacity_ampere_hour_t*
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_DESIGN_CAPACITY,

    /**
     * Reported state of charge [% Percentage * 100].
     *
     * Available:   get
     * Notes:       valuePtr has to be tommRoC_unit_measure_percentage_x_100_t*
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_STATE_OF_CHARGE,

    /**
     * Time To Empty value [s].
     * NOTE: TTE value is the estimated time to empty the battery.
     *
     * Available:   get
     * Notes:       valuePtr has to be tommRoC_unit_measure_time_seconds_t*
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TTE,

    /**
     * Time To Full value [s].
     * NOTE: TTF value is the estimated time to full the battery.
     *
     * Available:   get
     * Notes:       valuePtr has to be tommRoC_unit_measure_time_seconds_t*
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TTF,

    /**
     * Internal resistance [Ohm].
     *
     * Available:   get
     * Notes:       valuePtr has to be tommRoC_unit_measure_resistance_ohm_t*
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_INTERNAL_RESISTANCE,

    /**
     * Raw coulomb count generated by the device. [A].
     *
     * Available:   get
     * Notes:       valuePtr has to be tommRoC_unit_measure_current_ampere_t*
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_COULOMB_COUNTER,

    /**
     * Register raw value.
     *
     * Available:   get/set
     * Notes:       valuePtr has to be specific for different hardware chip
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_REGISTER_RAW,


    /******************* Specific for multi cell values */

    /**
     * Voltage cell 1/2/3/4 value [volt].
     *
     * Available:   get
     * Notes:       valuePtr has to be tommRoC_unit_measure_voltage_volt_t*
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_VOLTAGE_CELL1,
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_VOLTAGE_CELL2,
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_VOLTAGE_CELL3,
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_VOLTAGE_CELL4,

    /**
     * Temperature 1/2 value [°C].
     *
     * Available:   get
     * Notes:       valuePtr has to be tommRoC_unit_measure_temperature_celsius_t*
     */
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TEMPERATURE_1,
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TEMPERATURE_2,
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TEMPERATURE_3,
    TOMMRO_C_HW_HW_FUEL_GAUGE_DEF_VALUE_TEMPERATURE_4,

} tommRoC_hw_fuel_gauge_def_value_enum_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

#endif
