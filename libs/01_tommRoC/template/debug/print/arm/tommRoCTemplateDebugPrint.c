
#if defined (__TOMMROC_USE_ARM_DEBUG_TEMPLATE__)

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "debug/print/tommRoCTemplateDebugPrint.h"

#include "env/tommRoCTemplateEnv.h"

#include "debug/print/arm/core/tommRoCTemplateDebugPrint_ARM.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/

/*******************************************************************************
 * local functions
 ******************************************************************************/
#if defined (ITM)
static void _configure_itm(void) {

    uint32_t freq;
    uint32_t div;

    // Enable trace in core debug
    CoreDebug->DHCSR |= CoreDebug_DHCSR_C_DEBUGEN_Msk;
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    // Enable PC and IRQ sampling output
    DWT->CTRL |= 0x400003FE;

//    DWT->CTRL = (1 << DWT_CTRL_CYCTAP_Pos) // Prescaler for PC sampling
//                                              // 0 = x32, 1 = x512
//                 | (0 << DWT_CTRL_POSTPRESET_Pos) // Postscaler for PC sampling
//                                                   // Divider = value + 1
//                 | (1 << DWT_CTRL_PCSAMPLENA_Pos) // Enable PC sampling
//                 | (2 << DWT_CTRL_SYNCTAP_Pos)    // Sync packet interval
//                                                  // 0 = Off, 1 = Every 2^23 cycles,
//                                                  // 2 = Every 2^25, 3 = Every 2^27
//                 | (1 << DWT_CTRL_EXCTRCENA_Pos)  // Enable exception trace
//                   (1 << DWT_CTRL_CYCCNTENA_Pos); // Enable cycle counter

    /* Set TPIU prescaler for the current debug clock frequency.
     * Target frequency is "SWOSpeed" so we choose a divider that gives us the closest match.
       Actual divider is TPI->ACPR + 1. */
    freq = tommRoCTemplateDebugPrint_ARM_GetCpuDebugFreqHz() + (tommRoCTemplateDebugPrint_ARM_GetSWOSpeedHz() / 2);
    div  = freq / tommRoCTemplateDebugPrint_ARM_GetSWOSpeedHz();
    TPI->ACPR = div - 1;

    // Set protocol to NRZ
    TPI->SPPR = 0x00000002;                 // Pin protocol = NRZ/USART

    // Disable continuous formatting
    TPI->FFCR = 0x00000100;                 // TPIU packet framing enabled when bit 2 is set.
                                            // You can use 0x100 if you only need DWT/ITM and not ETM.

    // Unlock ITM and output data
    ITM->LAR = 0xC5ACCE55;                  // ITM Lock Access Register, C5ACCE55 enables more write access to Control Register 0xE00 :: 0xFFC
    ITM->TCR = 0x00010009;

//    ITM->TCR = (1 << ITM_TCR_TraceBusID_Pos) // Trace bus ID for TPIU
//             | (1 << ITM_TCR_DWTENA_Pos) // Enable events from DWT
//             | (1 << ITM_TCR_SYNCENA_Pos) // Enable sync packets
//             | (1 << ITM_TCR_ITMENA_Pos); // Main enable for ITM


    //ITM->TCR = ITM_TCR_TraceBusID_Msk | ITM_TCR_SWOENA_Msk | ITM_TCR_SYNCENA_Msk | ITM_TCR_ITMENA_Msk; /* ITM Trace Control Register */
    ITM->TPR = ITM_TPR_PRIVMASK_Msk;        // ITM Trace Privilege Register

    // ITM Channel 0 is used for UART output
    ITM->TER |= (1UL << 0);
}

static void _setup_itm(void) {

    tommRoCTemplateDebugPrint_ARM_OnEnterSetupITM();

    _configure_itm();
}

static void _send_string_len(const char* const stringPtr, const uint16_t stringLen) {

    uint16_t index;
    char* ptr;

    for (index = 0, ptr = (char*) stringPtr; index < stringLen; ++index, ++ptr) {
        ITM_SendChar(*ptr);
    }
}
#endif

/*******************************************************************************
 * functions
 ******************************************************************************/

tommRoC_err_enum_t tommRoCTemplateDebugPrintStart(void) {

#if defined (ITM)

    _setup_itm();

    return TOMMRO_C_ERR_SUCCESS;

#else
    return TOMMRO_C_LOW_LEVEL_ERR;
#endif
}

const char* tommRoCTemplateDebugPrintNewLineStr(void) {

    static const char newLineStr[] = TOMMROC_STRING_NEW_LINE_STR;

    return newLineStr;
}

tommRoC_err_enum_t tommRoCTemplateDebugPrintStr(const tommRoC_debug_level_enum_t debugLevel, const char* const stringPtr) {

#if defined (ITM)

    _send_string_len(stringPtr, tommRoCStringStrLen(stringPtr));

    return TOMMRO_C_ERR_SUCCESS;
#else

    TOMMROC_UTIL_UNUSED_PARAM(str);

    return TOMMRO_C_LOW_LEVEL_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateDebugPrintStrLen(const tommRoC_debug_level_enum_t debugLevel, const char* const stringPtr, const uint16_t stringLen) {

#if defined (ITM)

    _send_string_len(stringPtr, stringLen);

    return TOMMRO_C_ERR_SUCCESS;
#else

    TOMMROC_UTIL_UNUSED_PARAM(str);

    return TOMMRO_C_LOW_LEVEL_ERR;
#endif
}

tommRoC_err_enum_t tommRoCTemplateDebugPrintIsPending(bool* const isPendingPtr) {

#if defined (ITM)

    *isPendingPtr = false;

    return TOMMRO_C_ERR_SUCCESS;
#else

    TOMMROC_UTIL_UNUSED_PARAM(isPendingPtr);

    return TOMMRO_C_LOW_LEVEL_ERR;
#endif
}

#endif
