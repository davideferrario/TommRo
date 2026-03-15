
#ifndef TOMMROC_HW_DEVICES_COMM_UWB_DW1000_H_
#define TOMMROC_HW_DEVICES_COMM_UWB_DW1000_H_

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
#include "tommRoCHwGPIO.h"

#include "tommRoCHwDevicesCommUWBDW1000DecawaveIEEEPckt.h"

#include "TOMMROC.h"

/*******************************************************************************
 * defines
 ******************************************************************************/

// Device data.
#if defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_8_BIT_SIZE)
#define TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DEVICE_DATA_SIZE ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_16_BIT_SIZE)
#define TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DEVICE_DATA_SIZE ()
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_32_BIT_SIZE)
#define TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DEVICE_DATA_SIZE (28)
#elif defined (TOMMRO_C_ENV_MEMORY_ARCHITECTURE_IS_64_BIT_SIZE)
#define TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DEVICE_DATA_SIZE (56)
#endif

/*******************************************************************************
 * typedefs
 ******************************************************************************/

/**
 * Callback for disable DW1000 EXT_IRQ interrupts. This is called by library at the start of a critical section.
 * It returns the IRQ state before disable; the returned value is used to re-enable in mutex_off call.
 */
typedef int (*tommRoC_hw_devices_comm_uwb_dw1000_mutex_on_cb_t)(void);

/**
 * Callback for enable DW1000 EXT_IRQ interrupts, or at least restore their state as returned by mutex_on call.
 * This is called at the end of a critical section.
 */
typedef void (*tommRoC_hw_devices_comm_uwb_dw1000_mutex_off_cb_t)(const int s);

/**
 * Example:
 *
 * static int _check_IRQ_enabled(IRQn_Type IRQn) {
 *     return ((NVIC->ISER[((uint32_t)(IRQn) >> 5)] & (uint32_t)0x01 << (IRQn & (uint8_t)0x1F)) ? 1 : 0);
 * }
 *
 * static int _mutex_on(void) {
 *     int s;
 *
 *     s = _check_IRQ_enabled(IRQn);
 *
 *     if (s) {
 *         // disable the external interrupt line from MASTER chip IRQ
 *         NVIC_DisableIRQ(IRQn);
 *         __DSB();
 *         __ISB();
 *     }
 *
 *     // return state before disable, value is used to re-enable in _mutex_off call;
 *     return s;
 * }
 *
 * static void _mutex_off(const int s) {
 *     if (s) {
 *         NVIC_EnableIRQ(IRQn);
 *     }
 * }
 */


/******************* DWT interface configuration structure */

// Channel number
typedef enum {

    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_CHAN_1 = 0,               // Channel 1
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_CHAN_2,                   // Channel 2
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_CHAN_3,                   // Channel 3
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_CHAN_4,                   // Channel 4
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_CHAN_5,                   // Channel 5
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_CHAN_7,                   // Channel 7

} tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_chan_enum_t;

// Pulse Repetition Frequency
typedef enum {

    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PRF_16M = 0,              // UWB PRF 16 MHz
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PRF_64M,                  // UWB PRF 64 MHz

} tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_prf_enum_t;

// TX Preamble length in symbols
typedef enum {

    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PLEN_64 = 0,              // Standard preamble length 64 symbols
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PLEN_128,                 // Non-standard preamble length 128 symbols
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PLEN_256,                 // Non-standard preamble length 256 symbols
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PLEN_512,                 // Non-standard preamble length 512 symbols
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PLEN_1024,                // Standard preamble length 1024 symbols
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PLEN_1536,                // Non-standard preamble length 1536 symbols
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PLEN_2048,                // Non-standard preamble length 2048 symbols
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PLEN_4096,                // Standard preamble length 4096 symbols

} tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_tx_plen_enum_t;

// Preamble Acquisition Chunk (PAC) Size in symbols
typedef enum {

    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PAC_8 = 0,                // PAC 8 (recommended for RX of preamble length 128 and below)
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PAC_16,                   // PAC 16 (recommended for RX of preamble length 256)
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PAC_32,                   // PAC 32 (recommended for RX of preamble length 512)
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PAC_64,                   // PAC 64 (recommended for RX of preamble length 1024)

} tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_pac_enum_t;

// Bit rate for data TX (and RX)
typedef enum {

    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_DATA_RATE_BR_110K = 0,    // UWB bit rate 110 kbits/s
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_DATA_RATE_BR_850K,        // UWB bit rate 850 kbits/s
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_DATA_RATE_BR_6M8,         // UWB bit rate 6.8 Mbits/s

} tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_data_rate_enum_t;

// PHR mode
typedef enum {

    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PHR_MODE_STD = 0,         // Standard PHR mode
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PHR_MODE_EXT,             // DW proprietary extended frames PHR mode

} tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_phr_mode_enum_t;

// SFD timeout value (in symbols)
typedef enum {

    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_SFD_TOC_DEFAULT = 0,      // Default SFD timeout value

} tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_sfd_to_enum_t;

// DWT interface configuration structure.
typedef struct {

    tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_chan_enum_t       chan;       // Channel number
    tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_prf_enum_t        PRF;        // Pulse Repetition Frequency
    tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_tx_plen_enum_t    PLEN;       // PLEN
    tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_pac_enum_t        rxPAC;      // Acquisition Chunk Size (Relates to RX preamble length)
    uint8_t                                                             txCode;     // TX preamble code
    uint8_t                                                             rxCode;     // RX preamble code
    bool                                                                nsSFD;      // Boolean should we use non-standard SFD for better performance
    tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_data_rate_enum_t  dataRate;   // Data Rate
    tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_phr_mode_enum_t   phrMode;    // PHR mode
    tommRoC_util_enabled_status_enum_t                                  smartPower; // Is not used; left for backward compatibility with previous
    tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_sfd_to_enum_t     sfdTO;      // SFD timeout value (in symbols)

} tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_t__                       \
{                                                                                           \
    /* .chan */         TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_CHAN_2,           \
    /* .PRF */          TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PRF_64M,          \
    /* .PLEN */         TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PLEN_128,         \
    /* .rxPAC */        TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PAC_8,            \
    /* .txCode */       9,                                                                  \
    /* .rxCode */       9,                                                                  \
    /* .nsSFD */        false,                                                              \
    /* .dataRate */     TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_DATA_RATE_BR_6M8, \
    /* .phrMode */      TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_PHR_MODE_STD,     \
    /* .smartPower */   TOMMRO_C_UTIL_ENABLED,                                              \
    /* .sfdTO */        TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DWT_ITF_CONFIG_SFD_TOC_DEFAULT,  \
}


/******************* Configuration structure */

typedef struct {

    tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_t dwtItfConfig;

    tommRoC_util_enabled_status_enum_t sleepStatus;         // Enable sleep/deep sleep functionality

    /**
     * Specification of what configuration to load.
     */

    tommRoC_util_enabled_status_enum_t loadUCodeStatus;     // Load the LDE microcode from ROM - enable accurate RX timestamp
    tommRoC_util_enabled_status_enum_t dwWakeUpStatus;      // Just initialise dw1000local[] values (e.g. DW1000 has woken up)
    tommRoC_util_enabled_status_enum_t dwWUPNoUCodeStatus;  // If microcode/LDE algorithm has not already been loaded (on power up) e.g. when LDE is not used
    tommRoC_util_enabled_status_enum_t dwWUPRdOTPPrev;      // Init after wakeup - read OTP rev after wake up
    tommRoC_util_enabled_status_enum_t readOTPPIDStatus;    // Read part ID from OTP
    tommRoC_util_enabled_status_enum_t readOTPLIDStatus;    // Read lot ID from OTP
    tommRoC_util_enabled_status_enum_t readOTPBatStatus;    // Read ref voltage from OTP
    tommRoC_util_enabled_status_enum_t readOTPTmpStatus;    // Read ref temperature from OTP

} tommRoC_hw_devices_comm_uwb_dw1000_config_t;

#define __EMPTY_tommRoC_hw_devices_comm_uwb_dw1000_config_t__                                   \
{                                                                                               \
    /* .dwtItfConfig */         __EMPTY_tommRoC_hw_devices_comm_uwb_dw1000_dwt_itf_config_t__,  \
                                                                                                \
    /* .sleepStatus */          TOMMRO_C_UTIL_ENABLED,                                          \
                                                                                                \
    /* .loadUCodeStatus */      TOMMRO_C_UTIL_ENABLED,                                          \
    /* .dwWakeUpStatus */       TOMMRO_C_UTIL_ENABLED,                                          \
    /* .dwWUPNoUCodeStatus */   TOMMRO_C_UTIL_DISABLED,                                         \
    /* .dwWUPRdOTPPrev */       TOMMRO_C_UTIL_DISABLED,                                         \
    /* .readOTPPIDStatus */     TOMMRO_C_UTIL_ENABLED,                                          \
    /* .readOTPLIDStatus */     TOMMRO_C_UTIL_ENABLED,                                          \
    /* .readOTPBatStatus */     TOMMRO_C_UTIL_ENABLED,                                          \
    /* .readOTPTmpStatus */     TOMMRO_C_UTIL_ENABLED,                                          \
}


typedef enum {

    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_START_TX_IMMEDIATE = 0,                  // Immediate TX (no response expected)
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_START_TX_DELAYED,                        // Delayed TX (no response expected)
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_START_TX_IMMEDIATE_RESPONSE_EXPECTED,    // Immediate TX (response expected - the receiver will be automatically turned on after TX is done)
    TOMMROC_HW_DEVICES_COMM_UWB_DW1000_START_TX_DELAYED_RESPONSE_EXPECTED,      // Delayed TX (response expected - the receiver will be automatically turned on after TX is done)

} tommRoC_hw_devices_comm_uwb_dw1000_tx_mode_enum_t;


// Device data.
// NOTE: HAVE to be a static variable.
typedef struct {
    uint8_t data[TOMMROC_HW_DEVICES_COMM_UWB_DW1000_DEVICE_DATA_SIZE];
} tommRoC_hw_devices_comm_uwb_dw1000_device_data_t;

/*******************************************************************************
 * functions
 ******************************************************************************/

/**
 * Init bus device as for SPI master bus.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        chipSelect              chip select function pointer.
 * param[in]        chipDeSelect            chip de-select function pointer.
 * param[in]        busHandlerPtr           bus pointer.
 * param[in]        guardPtr                bus device guard (NULL if none).
 * param[out]       specificSlavePtr        output specific SPI slave pointer [needed as static because linked by bus device].
 * param[out]       busDevicePtr            output bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBDW1000InitSPI(
        const   tommRoC_hw_gpio_set_cb_t                                    chipSelect,
        const   tommRoC_hw_gpio_set_cb_t                                    chipDeSelect,
        const   tommRoC_hw_bus_t*                                   const   busHandlerPtr,
        const   tommRoC_guard_t*                                    const   guardPtr,
                tommRoC_hw_bus_device_specific_spi_slave_t*         const   specificSlavePtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Attach device data to bus device.
 * NOTE: chip is not started; function MUST be called.
 *
 * param[in]        deviceDataPtr           device data pointer (HAVE to be a static variable).
 * param[in/out]    busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBDW1000AttachDeviceData(
        const   tommRoC_hw_devices_comm_uwb_dw1000_device_data_t*   const   deviceDataPtr,
                tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Start chip.
 *
 * param[in]        resetLow                set RESETn pin low function pointer.
 * param[in]        resetHigh               set RESETn pin high function pointer.
 * param[in]        mutexOn                 disable DW1000 interrupt function pointer.
 * param[in]        mutexOff                enable DW1000 interrupt function pointer.
 * param[in]        configPtr               chip configuration pointer.
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBDW1000Start(
        const   tommRoC_hw_gpio_set_cb_t                                    resetLow,
        const   tommRoC_hw_gpio_set_cb_t                                    resetHigh,
        const   tommRoC_hw_devices_comm_uwb_dw1000_mutex_on_cb_t            mutexOn,
        const   tommRoC_hw_devices_comm_uwb_dw1000_mutex_off_cb_t           mutexOff,
        const   tommRoC_hw_devices_comm_uwb_dw1000_config_t*        const   configPtr,
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

/**
 * Read part ID (or chip ID) of the device.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       partIDPtr               32 bit part ID (or chip ID) value as programmed in the factory pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBDW1000GetPartID(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                uint32_t*                                           const   partIDPtr);

/**
 * Read lot ID of the device.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[out]       lotIDPtr                32 bit lot ID value as programmed in the factory pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBDW1000GetLotID(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                uint32_t*                                           const   lotIDPtr);

/**
 * Write a buffer into the DW1000's TX buffer.
 *
 * param[in]        busDevicePtr            bus device pointer.
 * param[in]        writeBufferPtr          user data buffer pointer.
 * param[in]        txFrameLength           total frame length, including the two byte CRC [MAX: 1023 byte].
 * param[in]        txBufferOffset          DW1000 TX Buffer offset at which to start writing data (usually 0).
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBDW1000WriteTxData(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr,
                void*                                               const   writeBufferPtr,
        const   uint16_t                                                    writeBufferLen,
        const   uint16_t                                                    txBufferOffset,
        const   tommRoC_hw_devices_comm_uwb_dw1000_tx_mode_enum_t           txMode);













/**
 * DW1000's general Interrupt Service Routine.
 *
 * param[in]        busDevicePtr            bus device pointer.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_hw_err_enum_t tommRoCHwDevicesCommUWBDW1000ISR(
        const   tommRoC_hw_bus_device_t*                            const   busDevicePtr);

#endif
