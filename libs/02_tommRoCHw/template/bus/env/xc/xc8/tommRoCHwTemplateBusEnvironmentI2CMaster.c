
/*******************************************************************************
 * includes
 ******************************************************************************/
#include "bus/env/tommRoCHwTemplateBusEnvironmentI2CMaster.h"

#include "TOMMROC.h"

#if defined (TOMMRO_C_ENV_ENVIRONMENT_IS_XC8)

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__)

#include "mcc.h"

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

#define __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(i2cMasterPrefix)                    \
                                                                                                            \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _wait_message_complete_XC(              \
            const   uint32_t                                    timeoutMsec,                                \
                    i2cMasterPrefix ## _MESSAGE_STATUS* const   statusPtr) {                                \
                                                                                                            \
        /* "Wait with timer" variables */                                                                   \
        tommRoC_timer_t timer;                                                                              \
        /* "Wait with counter" variables */                                                                 \
        uint8_t msecCount;                                                                                  \
        /* Check variable */                                                                                \
        bool isOsUptimeInit;                                                                                \
                                                                                                            \
        tommRoCOsIsInitEnv(TOMMRO_C_OS_UPTIME_MSEC_FUNCT_RES, &isOsUptimeInit);                             \
                                                                                                            \
        if (isOsUptimeInit) {                                                                               \
            /* Start "wait with timer" timer */                                                             \
            TOMMROC_ERR_IF_TOMMROC_LIB_FUNCT_NOT_SUCCESS_RETURN_SPECIFIC_RESULT(                            \
                tommRoCTimerStart(&timer, timeoutMsec), TOMMRO_C_HW_ENVIRONMENT_NOT_INIT_ERR);              \
        }                                                                                                   \
        else {                                                                                              \
            msecCount = 0;                                                                                  \
        }                                                                                                   \
                                                                                                            \
        while (i2cMasterPrefix ## _MESSAGE_PENDING == *statusPtr) {                                         \
                                                                                                            \
            if (isOsUptimeInit) {                                                                           \
                /* "Wait with timer" */                                                                     \
                if (TOMMRO_C_TIMER_EXPIRED_ERR == tommRoCTimerIsExpired(&timer)) {                          \
                    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;                                              \
                }                                                                                           \
            }                                                                                               \
            else {                                                                                          \
                /* "Wait with counter" */                                                                   \
                if (msecCount == timeoutMsec) {                                                             \
                    return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;                                              \
                }                                                                                           \
                                                                                                            \
                tommRoCOsDelayMsec(1);                                                                      \
                msecCount++;                                                                                \
            }                                                                                               \
        }                                                                                                   \
                                                                                                            \
        if (i2cMasterPrefix ## _MESSAGE_COMPLETE != *statusPtr) {                                           \
            return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;                                                      \
        }                                                                                                   \
                                                                                                            \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _hw_write_buffer_XC(                    \
            const   uint8_t*    const   writeBufferPtr,                                                     \
            const   uint16_t            writeBufferLen,                                                     \
            const   uint16_t            slaveAddress) {                                                     \
                                                                                                            \
        i2cMasterPrefix ## _MESSAGE_STATUS status = i2cMasterPrefix ## _MESSAGE_PENDING;                    \
        uint8_t retryCount;                                                                                 \
                                                                                                            \
        for (retryCount = 0; retryCount < I2C_MASTER_WRITE_TO_SLAVE_RETRY_COUNT; ++retryCount) {            \
                                                                                                            \
            i2cMasterPrefix ## _MasterWrite(                                                                \
                    (uint8_t*) writeBufferPtr,                                                              \
                    writeBufferLen,                                                                         \
                    slaveAddress,                                                                           \
                    &status);                                                                               \
                                                                                                            \
            if (i2cMasterPrefix ## _MESSAGE_FAIL == status) {                                               \
                return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;                                                  \
            }                                                                                               \
                                                                                                            \
            if (TOMMRO_C_HW_ERR_SUCCESS == _i2c_master_ ## i2cMasterPrefix ## _wait_message_complete_XC(    \
                    I2C_MASTER_WAIT_STATUS_x_BYTE_LENGTH_MSEC * (uint32_t) writeBufferLen, &status)) {      \
                                                                                                            \
                return TOMMRO_C_HW_ERR_SUCCESS;                                                             \
            }                                                                                               \
        }                                                                                                   \
                                                                                                            \
        return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;                                                          \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _hw_read_buffer_XC(                     \
                    uint8_t*    const   readBufferPtr,                                                      \
            const   uint16_t            toReadAmount,                                                       \
                    uint16_t*   const   readedAmountPtr,                                                    \
            const   uint16_t            slaveAddress) {                                                     \
                                                                                                            \
        i2cMasterPrefix ## _MESSAGE_STATUS status = i2cMasterPrefix ## _MESSAGE_PENDING;                    \
        uint8_t retryCount;                                                                                 \
                                                                                                            \
        for (retryCount = 0; retryCount < I2C_MASTER_READ_FROM_SLAVE_RETRY_COUNT; ++retryCount) {           \
                                                                                                            \
            i2cMasterPrefix ## _MasterRead(                                                                 \
                    readBufferPtr,                                                                          \
                    toReadAmount,                                                                           \
                    slaveAddress,                                                                           \
                    &status);                                                                               \
                                                                                                            \
            if (TOMMRO_C_HW_ERR_SUCCESS == _i2c_master_ ## i2cMasterPrefix ## _wait_message_complete_XC(    \
                    I2C_MASTER_WAIT_STATUS_x_BYTE_LENGTH_MSEC * (uint32_t) toReadAmount, &status)) {        \
                                                                                                            \
                *readedAmountPtr = toReadAmount;                                                            \
                                                                                                            \
                return TOMMRO_C_HW_ERR_SUCCESS;                                                             \
            }                                                                                               \
        }                                                                                                   \
                                                                                                            \
        return TOMMRO_C_HW_BUS_OPERATION_FAIL_ERR;                                                          \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _write_buffers_XC(                      \
            const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,                                    \
            const   uint8_t                             writeBuffersAmount,                                 \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        const tommRoC_hw_bus_write_buf_t* writeBufferPtr;                                                   \
        uint8_t idx;                                                                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        tommRoC_hw_bus_device_specific_i2c_slave_t* specificI2CSlavePtr =                                   \
                (tommRoC_hw_bus_device_specific_i2c_slave_t*) inputPtr;                                     \
                                                                                                            \
        for (idx = 0, writeBufferPtr = writeBuffersPtr; idx < writeBuffersAmount; ++idx, ++writeBufferPtr) {\
                                                                                                            \
            TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(                               \
                    _i2c_master_ ## i2cMasterPrefix ## _hw_write_buffer_XC(                                 \
                            writeBufferPtr->bufferPtr,                                                      \
                            writeBufferPtr->toWriteAmount,                                                  \
                            specificI2CSlavePtr->slaveAddress));                                            \
        }                                                                                                   \
                                                                                                            \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
    }                                                                                                       \
                                                                                                            \
    static tommRoC_hw_err_enum_t _i2c_master_ ## i2cMasterPrefix ## _read_buffers_XC(                       \
                    tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,                                     \
            const   uint8_t                             readBuffersAmount,                                  \
            const   void*                       const   inputPtr,                                           \
                    void*                       const   resultPtr) {                                        \
                                                                                                            \
        tommRoC_hw_bus_read_buf_t* readBufferPtr;                                                           \
        uint8_t idx;                                                                                        \
                                                                                                            \
        TOMMROC_UTIL_UNUSED_PARAM(resultPtr);                                                               \
                                                                                                            \
        tommRoC_hw_bus_device_specific_i2c_slave_t* specificI2CSlavePtr =                                   \
                (tommRoC_hw_bus_device_specific_i2c_slave_t*) inputPtr;                                     \
                                                                                                            \
        for (idx = 0, readBufferPtr = readBuffersPtr; idx < readBuffersAmount; ++idx, ++readBufferPtr) {    \
                                                                                                            \
            TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(                               \
                    _i2c_master_ ## i2cMasterPrefix ## _hw_read_buffer_XC(                                  \
                            readBufferPtr->bufferPtr,                                                       \
                            readBufferPtr->toReadAmount,                                                    \
                            readBufferPtr->readedAmountPtr,                                                 \
                            specificI2CSlavePtr->slaveAddress));                                            \
        }                                                                                                   \
                                                                                                            \
        return TOMMRO_C_HW_ERR_SUCCESS;                                                                     \
    }                                                                                                       \
                                                                                                            \
    static void _i2c_master_ ## i2cMasterPrefix ## _get_callback_XC(                                        \
                    tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {                                       \
                                                                                                            \
        cbFunctPtr->writeBuffers    = _i2c_master_ ## i2cMasterPrefix ## _write_buffers_XC;                 \
        cbFunctPtr->readBuffers     = _i2c_master_ ## i2cMasterPrefix ## _read_buffers_XC;                  \
    }

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C1);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C2);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_3_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C3);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_4_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C4);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_5_TEMPLATE__)
    __TOMMROC_HW_I2C_MASTER_FUNCTIONALITY_IMPLEMENTATION_TEMPLATE__(I2C5);
#endif


#define __TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_START_XC__(i2cMasterPrefix, cbFunctPtr)    \
        _i2c_master_ ## i2cMasterPrefix ## _get_callback_XC(cbFunctPtr);                \
        return TOMMRO_C_HW_ERR_SUCCESS;

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_DEF_AT_LEAST_ONE_IS_USED__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMasterSetProp(
        const   tommRoC_hw_template_bus_spi_master_prop_enum_t          property,
        const   tommRoC_hw_template_bus_spi_master_enum_t               bus,
        const   void*                                           const   propValuePtr) {

    TOMMROC_UTIL_UNUSED_PARAM(property);
    TOMMROC_UTIL_UNUSED_PARAM(bus);
    TOMMROC_UTIL_UNUSED_PARAM(propValuePtr);

    return TOMMRO_C_HW_NOT_AVAILABLE_ERR;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster0Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_START_XC__(I2C, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster1Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_START_XC__(I2C1, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster2Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_START_XC__(I2C2, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_3_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster3Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_START_XC__(I2C3, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_4_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster4Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_START_XC__(I2C4, cbFunctPtr);
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_5_TEMPLATE__)
tommRoC_hw_err_enum_t tommRoCHwTemplateBusEnvironmentI2CMaster5Start(
                tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    __TOMMROC_HW_TEMPLATE_BUS_I2C_MASTER_START_XC__(I2C5, cbFunctPtr);
}
#endif

#endif

#endif
