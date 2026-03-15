
#ifndef TOMMROC_HW_DEVICES_POWER_MON_MCP39F511N_H_
#define TOMMROC_HW_DEVICES_POWER_MON_MCP39F511N_H_

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
#include "tommRoCHwBus.h"
#include "tommRoCHwBusDevice.h"
#include "tommRoCHwErr.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

/*******************************************************************************
 * typedefs
 ******************************************************************************/
// Enumeration of channel reference
typedef enum {

    /**
     * Channel 1
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_CH1 = 0,

    /**
     * Channel 2
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_CH2,

    /**
     * TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_COMMON is used to indicate the access to a property/register
     * in common between the two channels
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_COMMON

} tommRoC_hw_devices_pmon_mcp39f511n_ch_enum_t;


// Enumeration of MCP39F511N Output Registers properties.
typedef enum {


    /**
     * System status register, common between the two channels
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_SYS_STATUS_OR_PROP,

    /**
     * System version register, common between the two channels
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_SYS_VERSION_OR_PROP,

    /**
     * Voltage RMS register, common between the two channels
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_VOLTAGE_RMS_OR_PROP,

    /**
     * Line Frequency register, common between the two channels
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_LINE_FREQ_OR_PROP,

    /**
     * Power Factor output from channel 1 and 2
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_PWR_FACT_CH_OR_PROP,

    /**
     * RMS Current output from channel 1 and 2
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_CURR_RMS_CH_OR_PROP,

    /**
     * Active Power output from channel 1 and 2
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_ACT_PWR_CH_OR_PROP,

    /**
     * Reactive Power output from channel 1 and 2
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_REACT_PWR_CH_OR_PROP,

    /**
     * Apparent Power output from channel 1 and 2
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_APP_PWR_CH_OR_PROP,

    /**
     * Accumulator for Active Energy, Import, channel 1 and 2
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_IMP_EN_ACT_CNTR_CH_OR_PROP,

    /**
     * Accumulator for Active Energy, Export, channel 1 and 2
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_EXP_EN_ACT_CNTR_CH_OR_PROP,

    /**
     * Accumulator for Reactive Energy, Import, channel 1 and 2
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_IMP_EN_REACT_CNTR_CH_OR_PROP,

    /**
     * Accumulator for Reactive Energy, Export, channel 1 and 2
     *
     * Available:   get
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_EXP_EN_REACT_CNTR_CH_OR_PROP

} tommRoC_hw_devices_pmon_mcp39f511n_or_prop_enum_t;

// Enumeration of MCP39F511N Calibration Registers properties.
typedef enum {

    /**
     * Calibration Registers Delimiter, common between the two channels
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_CALIB_DELIM_CR_PROP,

    /**
     *  Gain Calibration Factor for RMS Current, channel 1 and 2
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_GAIN_CURR_RMS_CH_CR_PROP,

    /**
     *  Gain Calibration Factor for RMS Voltage, common between the two channels
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_GAIN_VOLT_RMS_CR_PROP,

    /**
     *  Gain Active Power, channel 1 and 2
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_GAIN_ACT_PWR_CH_CR_PROP,

    /**
     *  Gain Reactive Power, channel 1 and 2
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_GAIN_REACT_PWR_CH_CR_PROP,

    /**
     * Gain Calibration Factor for the Line Frequency, common between the two channels
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_GAIN_LINE_FREQ_CR_PROP,

    /**
     *  Offset Current RMS, channel 1 and 2
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_OFFSET_CURR_RMS_CH_CR_PROP,

    /**
     *  Offset Calibration Factor for Active Power, channel 1 and 2
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_OFFSET_ACT_PWR_CH_CR_PROP,

    /**
     *  Offset Calibration Factor for Reactive Power, channel 1 and 2
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_OFFSET_REACT_PWR_CH_CR_PROP,

    /**
     *  Phase Compensation, channel 1 and 2
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_PHASE_COMPENS_CH_CR_PROP,

    /**
     *  Number of Digits for apparent power divisor to match IRMS and VRMS resolution, channel 1 and 2
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_APP_PWR_DIVISOR_CH_CR_PROP

} tommRoC_hw_devices_pmon_mcp39f511n_cr_prop_enum_t;

// Enumeration of MCP39F511N Design Configuration Registers properties.
typedef enum {

    /**
     * Control for device configuration, including ADC configuration
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_SYS_CONFIG_DR_PROP,

    /**
     * Settings for the Event pins including Relay Control
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_EVENT_CONFIG_DR_PROP,

    /**
     * N for 2N number of line cycles to be used during a single computation cycle
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_ACC_INT_PARAM_DR_PROP,

    /**
     * Target Voltage to be used during single-point calibration
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_CALIB_VOLT_DR_PROP,

    /**
     * Reference Value for the nominal line frequency
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_CALIB_LINE_FREQ_DR_PROP,

    /**
     * Scaling factor for Outputs, channel 1 and 2
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_RANGE_FOR_OUT_CH_DR_PROP,

    /**
     * Target Current to be used during single-point calibration, channel 1 and 2
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_CALIBR_CURR_CH_DR_PROP,

    /**
     * Target Active Power to be used during single-point calibration, channel 1 and 2
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_CALIBR_PWR_ACT_CH_DR_PROP,

    /**
     * Target Active Power to be used during single-point calibration, channel 1 and 2
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_CALIBR_PWR_REACT_CH_DR_PROP,

    /**
     * RMS Voltage Sag threshold at which an event flag is recorded
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_VOLT_SAG_LIMIT_DR_PROP,

    /**
     * RMS Voltage Surge threshold at which an event flag is recorded
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_VOLT_SURGE_LIMIT_DR_PROP,

    /**
     * RMS Over Current threshold at which an event flag is recorded, channel 1 and 2
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_OVER_CURR_LIMIT_CH_DR_PROP,

    /**
     * Over Power threshold at which an event flag is recorded, channel 1 and 2
     *
     * Available:   get/set
     * Notes:
     */
    TOMMRO_C_HW_DEVICES_PMON_MCP39F511N_OVER_PWR_LIMIT_CH_DR_PROP

} tommRoC_hw_devices_pmon_mcp39f511n_dr_prop_enum_t;

// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[256];  // @AS_TBD: QUESTA SIZE VA SISTEMATA (E CAPITA LA LOGICA)
} tommRoC_hw_devices_power_mon_mcp39f511_device_data_t;

/*******************************************************************************
 * functions
 ******************************************************************************/
/**
 *
 * NOTE:
 *
 * param[in]
 * param[in]
 * param[in]
 * param[out]
 * param[out]
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesPowerMonMCP39F511NInitUART(
        const   tommRoC_hw_bus_t*                                   const   busHandlerPtr,
        const   tommRoC_guard_t*                                    const   guardPtr,
                tommRoC_hw_bus_device_specific_uart_t*              const   specificPtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 *
 * NOTE:
 *
 * param[in]
 * param[in]
 * param[in]
 * param[out]
 * param[out]
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesPowerMonMCP39F511NAttachDeviceData(
        const   tommRoC_hw_devices_power_mon_mcp39f511_device_data_t*   const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                                const   busDevicePtr);

/**
 *
 * NOTE:
 *
 * param[in]
 * param[in]
 * param[in]
 * param[out]
 * param[out]
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesPowerMonMCP39F511NReadReg(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   uint16_t                                                    regAdd,
        const   uint16_t                                                    numOfByteToRead,
                void*                                               const   dataReadBuffPtr,
                bool*                                               const   readRegOkPtr);

/**
 *
 * NOTE:
 *
 * param[in]
 * param[in]
 * param[in]
 * param[out]
 * param[out]
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesPowerMonMCP39F511NWriteReg(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
        const   uint16_t                                                    regAdd,
                void*                                               const   dataToWriteBuffPtr,
        const   uint16_t                                                    numOfByteToWrite,
                bool*                                               const   writeRegOkPtr);
/**
 *
 * NOTE:
 *
 * param[in]
 * param[in]
 * param[in]
 * param[out]
 * param[out]
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesPowerMonMCP39F511NOutRegPropGet(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
        const   tommRoC_hw_devices_pmon_mcp39f511n_or_prop_enum_t                   outRegProperty,
        const   tommRoC_hw_devices_pmon_mcp39f511n_ch_enum_t                        channel,
                void*                                                       const   outRegGetValuePtr,
                bool*                                                       const   outRegGetSuccessPtr);

/**
 *
 * NOTE:
 *
 * param[in]
 * param[in]
 * param[in]
 * param[out]
 * param[out]
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesPowerMonMCP39F511NCalibRegPropGet(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
        const   tommRoC_hw_devices_pmon_mcp39f511n_cr_prop_enum_t                   calibRegProperty,
        const   tommRoC_hw_devices_pmon_mcp39f511n_ch_enum_t                        channel,
                void*                                                       const   calibRegGetValuePtr,
                bool*                                                       const   calibRegGetSuccessPtr);

/**
 *
 * NOTE:
 *
 * param[in]
 * param[in]
 * param[in]
 * param[out]
 * param[out]
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesPowerMonMCP39F511NCalibRegPropSet(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
        const   tommRoC_hw_devices_pmon_mcp39f511n_cr_prop_enum_t                   calibRegProperty,
        const   tommRoC_hw_devices_pmon_mcp39f511n_ch_enum_t                        channel,
                void*                                                       const   calibRegSetValuePtr,
                bool*                                                       const   calibRegSetSuccessPtr);

/**
 *
 * NOTE:
 *
 * param[in]
 * param[in]
 * param[in]
 * param[out]
 * param[out]
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesPowerMonMCP39F511NDesignConfigRegPropGet(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
        const   tommRoC_hw_devices_pmon_mcp39f511n_dr_prop_enum_t                   designConfigRegProperty,
        const   tommRoC_hw_devices_pmon_mcp39f511n_ch_enum_t                        channel,
                void*                                                       const   designConfigRegGetValuePtr,
                bool*                                                       const   designConfigRegGetSuccessPtr);

/**
 *
 * NOTE:
 *
 * param[in]
 * param[in]
 * param[in]
 * param[out]
 * param[out]
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesPowerMonMCP39F511NAutoCalibrateGain(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
        const   tommRoC_hw_devices_pmon_mcp39f511n_ch_enum_t                        channel,
                bool*                                                       const   autoCalibrateGainSuccessPtr);

/**
 *
 * NOTE:
 *
 * param[in]
 * param[in]
 * param[in]
 * param[out]
 * param[out]
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesPowerMonMCP39F511NAutoCalibrateReactiveGain(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
        const   tommRoC_hw_devices_pmon_mcp39f511n_ch_enum_t                        channel,
                bool*                                                       const   autoCalibrateGainSuccessPtr);

/**
 *
 * NOTE:
 *
 * param[in]
 * param[in]
 * param[in]
 * param[out]
 * param[out]
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesPowerMonMCP39F511NAutoCalibrateFrequency(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                bool*                                                       const   autoCalibFreqSuccessPtr);

/**
 *
 * NOTE:
 *
 * param[in]
 * param[in]
 * param[in]
 * param[out]
 * param[out]
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesPowerMonMCP39F511NSaveRegistersToFlash(
        const   tommRoC_hw_bus_device_t*                                    const   busDevicePtr,
                bool*                                                       const   saveRegToFlashSuccessPtr);

#endif
