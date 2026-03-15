


//
//
///* I2C Start - bit bang */
//void I2C_START(void)
//{
//    /* I2C Start condition, data line goes low when clock is high */
//    I2C_DATA = HIGH;
//    I2C_CLK = HIGH;
//    I2C_DATA = LOW;
//    I2C_CLK = LOW;
//}
//
///* I2C Stop - bit bang */
//void I2C_STOP (void)
//{
//    /* I2C Stop condition, clock goes high when data is low */
//    I2C_CLK = LOW;
//    I2C_DATA = LOW;
//    I2C_CLK = HIGH;
//    I2C_DATA = HIGH;
//}
//
///* I2C Write - bit bang */
//void I2C_WRITE(unsigned char data)
//{
//	unsigned char outBits;
//	unsigned char inBit;
//
// 	/* 8 bits */
//	for(outBits = 0; outBits < 8; outBits++)
//	{
//	    if (data & 0x80)
//		    I2C_DATA = 1;
//		else
//		    I2C_DATA = 0;
//      	data  <<= 1;
//		/* Generate clock for 8 data bits */
//		SCLK = HIGH;
//		SCLK = LOW;
//	}
//
//	/* Generate clock for ACK */
//	I2C_CLK = HIGH;
//        /* Wait for clock to go high, clock stretching */
//        while(I2C_CLK);
//        /* Clock high, valid ACK */
//	inBit = I2C_DATA;
//	I2C_CLK = LOW;
//}
//
//unsigned char I2C_READ (void)
//{
//	unsigned char inData, inBits;
//
//	inData = 0x00;
//	/* 8 bits */
//	for(inBits = 0; inBits < 8; inBits++)
//	{
//		inData <<= 1;
//		I2C_CLK = HIGH;
//      	inData |= I2C_DATA;
//		I2C_CLK = LOW;
//	}
//
//   return inData;
//}
//
///* Examble for writing to I2C Slave */
//void writeI2CSlave (unsigned char data)
//{
//    /* Start */
//  	I2C_START();
//	/* Slave address */
//   	I2C_WRITE(0xAA)
//	/* Slave control byte */
//   	I2C_WRITE(0xBB);
//	/* Slave data */
//   	I2C_WRITE(data);
//	/* Stop */
//   	I2C_STOP();
//}
//
///* Examble for reading from I2C Slave */
//unsigned char readI2CSlave(unsigned char data)
//{
//   	unsigned char inData;
//
//	/* Start */
//  	I2C_START();
//	/* Slave address */
//   	I2C_WRITE(0xAA);
//	/* Slave control byte */
//   	I2C_WRITE(data);
//	/* Stop */
//   	I2C_STOP();
//
//	/* Start */
//   	I2C_START();
//	/* Slave address + read */
//   	I2C_WRITE(0xAA | 1);
//	/* Read */
//	inData = I2C_READ();
//
//   	return inData;
//}
//
//
//
//
//
//
//
//
//





/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCHwTemplateBusI2CMasterSw.h"

#if defined (__TOMMROC_HW_AT_LEAST_ONE_I2C_MASTER_SW_TEMPLATE_IS_USED__)

#include "TOMMROC.h"

/*******************************************************************************
 * local defines
 ******************************************************************************/

typedef struct {

    tommRoC_hw_gpio_set_cb_t    clkHigh;
    tommRoC_hw_gpio_set_cb_t    clkLow;
    tommRoC_hw_gpio_set_cb_t    dataHigh;
    tommRoC_hw_gpio_set_cb_t    dataLow;
    tommRoC_hw_gpio_get_cb_t    dataStatus;
    uint32_t                    baseDelayUsec;

} _tommRoC_hw_template_bus_i2c_master_sw_base_gpio_t_;

#define __EMPTY__tommRoC_hw_template_bus_i2c_master_sw_base_gpio_t___   \
{                                                                       \
    /* .clkHigh */          NULL,                                       \
    /* .clkLow */           NULL,                                       \
    /* .dataLow */          NULL,                                       \
    /* .mosiLowr */         NULL,                                       \
    /* .dataStatus */       NULL,                                       \
    /* .baseDelayUsec */    0,                                          \
}

/*******************************************************************************
 * local typedefs
 ******************************************************************************/

/*******************************************************************************
 * local vars
 ******************************************************************************/
#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_SW_TEMPLATE__)
static _tommRoC_hw_template_bus_i2c_master_sw_base_gpio_t_ _i2c_master_0_sw = TOMMROC_UTIL_EMPTY_VARIABLE(_tommRoC_hw_template_bus_i2c_master_sw_base_gpio_t_);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_SW_TEMPLATE__)
static _tommRoC_hw_template_bus_i2c_master_sw_base_gpio_t_ _i2c_master_1_sw = TOMMROC_UTIL_EMPTY_VARIABLE(_tommRoC_hw_template_bus_i2c_master_sw_base_gpio_t_);
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_SW_TEMPLATE__)
static _tommRoC_hw_template_bus_i2c_master_sw_base_gpio_t_ _i2c_master_2_sw = TOMMROC_UTIL_EMPTY_VARIABLE(_tommRoC_hw_template_bus_i2c_master_sw_base_gpio_t_);
#endif

/*******************************************************************************
 * local functions
 ******************************************************************************/
static tommRoC_hw_err_enum_t _i2c_master_write_buffer_bit_bang(
        const   _tommRoC_hw_template_bus_i2c_master_sw_t_*  const   i2cMasterSwPtr,
        const   uint8_t*                                    const   writeBufferPtr,
        const   uint16_t                                            writeBufferLen) {

    uint8_t* ptr;

    for (ptr = (uint8_t*) writeBufferPtr; (uint16_t) (ptr - writeBufferPtr) < writeBufferLen; ++ptr) {
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _i2c_master_read_buffer_bit_bang(
        const   _tommRoC_hw_template_bus_i2c_master_sw_t_*  const   i2cMasterSwPtr,
                uint8_t*                                    const   readBufferPtr,
        const   uint16_t                                            toReadAmount,
                uint16_t*                                   const   readedAmountPtr) {

    uint8_t* ptr;

    for (ptr = (uint8_t*) readBufferPtr; (uint16_t) (ptr - readBufferPtr) < toReadAmount; ++ptr) {
    }

    *readedAmountPtr = toReadAmount;

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _i2c_master_sw_write_buffers(
        const   _tommRoC_hw_template_bus_i2c_master_sw_t_*  const   i2cMasterSwPtr,
        const   tommRoC_hw_bus_write_buf_t*                 const   writeBuffersPtr,
        const   uint8_t                                             writeBuffersAmount,
        const   uint8_t*                                    const   inputPtr,
                void*                                       const   resultPtr) {

    const tommRoC_hw_bus_write_buf_t* writeBufferPtr;
    uint8_t index;

    TOMMROC_UTIL_UNUSED_PARAM(inputPtr);
    TOMMROC_UTIL_UNUSED_PARAM(resultPtr);

    for (index = 0, writeBufferPtr = writeBuffersPtr; index < writeBuffersAmount; ++index, ++writeBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _i2c_master_write_buffer_bit_bang(
                        i2cMasterSwPtr,
                        writeBufferPtr->bufferPtr,
                        writeBufferPtr->toWriteAmount));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static tommRoC_hw_err_enum_t _i2c_master_sw_read_buffers(
        const   _tommRoC_hw_template_bus_i2c_master_sw_t_*  const   i2cMasterSwPtr,
                tommRoC_hw_bus_read_buf_t*                  const   readBuffersPtr,
        const   uint8_t                                             readBuffersAmount,
        const   uint8_t*                                    const   inputPtr,
                void*                                       const   resultPtr) {

    tommRoC_hw_bus_read_buf_t* readBufferPtr;
    uint8_t index;

    TOMMROC_UTIL_UNUSED_PARAM(inputPtr);
    TOMMROC_UTIL_UNUSED_PARAM(resultPtr);

    for (index = 0, readBufferPtr = readBuffersPtr; index < readBuffersAmount; ++index, ++readBufferPtr) {

        TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
                _i2c_master_read_buffer_bit_bang(
                        i2cMasterSwPtr,
                        readBufferPtr->bufferPtr,
                        readBufferPtr->toReadAmount,
                        readBufferPtr->readedAmountPtr));
    }

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static void _init_pins(
        const   tommRoC_hw_template_bus_i2c_master_sw_init_t*   const swInitPtr) {

    swInitPtr->clkHigh();
    swInitPtr->dataHigh();
}

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_SW_TEMPLATE__)
static tommRoC_hw_err_enum_t _i2c_master_0_sw_write_buffers(
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _i2c_master_sw_write_buffers(
            &_i2c_master_0_sw,
            writeBuffersPtr,
            writeBuffersAmount,
            inputPtr,
            resultPtr);
}

static tommRoC_hw_err_enum_t _i2c_master_0_sw_read_buffers(
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _i2c_master_sw_read_buffers(
            &_i2c_master_0_sw,
            readBuffersPtr,
            readBuffersAmount,
            inputPtr,
            resultPtr);
}

static void _i2c_master_0_sw_get_callback(
        tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwBusCbFunctReset(cbFunctPtr));

    cbFunctPtr->writeBuffers    = _i2c_master_0_sw_write_buffers;
    cbFunctPtr->readBuffers     = _i2c_master_0_sw_read_buffers;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_SW_TEMPLATE__)
static tommRoC_hw_err_enum_t _i2c_master_1_sw_write_buffers(
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _i2c_master_sw_write_buffers(
            &_i2c_master_1_sw,
            writeBuffersPtr,
            writeBuffersAmount,
            inputPtr,
            resultPtr);
}

static tommRoC_hw_err_enum_t _i2c_master_1_sw_read_buffers(
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _i2c_master_sw_read_buffers(
            &_i2c_master_1_sw,
            readBuffersPtr,
            readBuffersAmount,
            inputPtr,
            resultPtr);
}

static void _i2c_master_1_sw_get_callback(
        tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwBusCbFunctReset(cbFunctPtr));

    cbFunctPtr->writeBuffers    = _i2c_master_1_sw_write_buffers;
    cbFunctPtr->readBuffers     = _i2c_master_1_sw_read_buffers;
}
#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_SW_TEMPLATE__)
static tommRoC_hw_err_enum_t _i2c_master_2_sw_write_buffers(
        const   tommRoC_hw_bus_write_buf_t* const   writeBuffersPtr,
        const   uint8_t                             writeBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _i2c_master_sw_write_buffers(
            &_i2c_master_2_sw,
            writeBuffersPtr,
            writeBuffersAmount,
            inputPtr,
            resultPtr);
}

static tommRoC_hw_err_enum_t _i2c_master_2_sw_read_buffers(
                tommRoC_hw_bus_read_buf_t*  const   readBuffersPtr,
        const   uint8_t                             readBuffersAmount,
        const   void*                       const   inputPtr,
                void*                       const   resultPtr) {

    return _i2c_master_sw_read_buffers(
            &_i2c_master_2_sw,
            readBuffersPtr,
            readBuffersAmount,
            inputPtr,
            resultPtr);
}

static void _i2c_master_2_sw_get_callback(
        tommRoC_hw_bus_cb_funct_t*  const   cbFunctPtr) {

    TOMMROC_HW_ASSERT_TOMMROC_HW_LIB_FUNCT_SUCCESS(
            tommRoCHwBusCbFunctReset(cbFunctPtr));

    cbFunctPtr->writeBuffers    = _i2c_master_2_sw_write_buffers;
    cbFunctPtr->readBuffers     = _i2c_master_2_sw_read_buffers;
}
#endif















static tommRoC_hw_err_enum_t _ckeck_init_param(
        const   tommRoC_hw_template_bus_i2c_master_sw_init_t*   const   swInitPtr) {

    TOMMROC_ASSERT_NOT_NULL(swInitPtr);
    TOMMROC_ASSERT_NOT_NULL(swInitPtr->clkHigh);
    TOMMROC_ASSERT_NOT_NULL(swInitPtr->clkLow);
    TOMMROC_ASSERT_NOT_NULL(swInitPtr->dataHigh);
    TOMMROC_ASSERT_NOT_NULL(swInitPtr->dataLow);
    TOMMROC_ASSERT_NOT_NULL(swInitPtr->dataStatus);
    TOMMROC_ASSERT_NOT_ZERO(swInitPtr->baudRateKbits);

    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(swInitPtr);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(swInitPtr->clkHigh);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(swInitPtr->clkLow);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(swInitPtr->dataHigh);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(swInitPtr->dataLow);
    TOMMROC_HW_PARAM_CHECK_ON_NULL_RETURN_ERR(swInitPtr->dataStatus);
    TOMMROC_HW_ERR_IF_ZERO_RETURN_TOMMRO_C_HW_PARAM_ERR(swInitPtr->baudRateKbits);

    return TOMMRO_C_HW_ERR_SUCCESS;
}

static void _init_i2c_master_sw_struct(
        const   tommRoC_hw_template_bus_i2c_master_sw_init_t*   const   swInitPtr,
                _tommRoC_hw_template_bus_i2c_master_sw_t_*      const   i2cMasterSwPtr) {

    i2cMasterSwPtr->clkHigh     = swInitPtr->clkHigh;
    i2cMasterSwPtr->clkLow      = swInitPtr->clkLow;
    i2cMasterSwPtr->dataHigh    = swInitPtr->dataHigh;
    i2cMasterSwPtr->dataLow     = swInitPtr->dataLow;
    i2cMasterSwPtr->dataStatus  = swInitPtr->dataStatus;

    i2cMasterSwPtr->baseDelayUsec   = (uint32_t) (1000) / ((uint32_t)swInitPtr->baudRateKbits * (uint32_t)2);
}

/*******************************************************************************
 * functions
 ******************************************************************************/

#if defined (__TOMMROC_HW_USE_I2C_MASTER_0_SW_TEMPLATE__)

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CMaster0SwStart(
        const   tommRoC_hw_template_bus_i2c_master_sw_init_t*   const   swInitPtr,
                tommRoC_hw_bus_t*                               const   busHandlePtr) {

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_ckeck_init_param(swInitPtr));

    _init_pins(swInitPtr);

    _init_i2c_master_sw_struct(swInitPtr, &_i2c_master_0_sw);

    _i2c_master_0_sw_get_callback(&cbFunct);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwBusInit(
                    TOMMRO_C_HW_BUS_I2C_MASTER_BUS_TYPE,
                    &cbFunct,
                    busHandlePtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_1_SW_TEMPLATE__)

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CMaster1SwStart(
        const   tommRoC_hw_template_bus_i2c_master_sw_init_t*   const   swInitPtr,
                tommRoC_hw_bus_t*                               const   busHandlePtr) {

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_ckeck_init_param(swInitPtr));

    _init_pins(swInitPtr);

    _init_i2c_master_sw_struct(swInitPtr, &_i2c_master_1_sw);

    _i2c_master_1_sw_get_callback(&cbFunct);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwBusInit(
                    TOMMRO_C_HW_BUS_I2C_MASTER_BUS_TYPE,
                    &cbFunct,
                    busHandlePtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif

#if defined (__TOMMROC_HW_USE_I2C_MASTER_2_SW_TEMPLATE__)

tommRoC_hw_err_enum_t tommRoCHwTemplateBusI2CMaster2SwStart(
        const   tommRoC_hw_template_bus_i2c_master_sw_init_t*   const   swInitPtr,
                tommRoC_hw_bus_t*                               const   busHandlePtr) {

    static tommRoC_hw_bus_cb_funct_t cbFunct;

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(_ckeck_init_param(swInitPtr));

    _init_pins(swInitPtr);

    _init_i2c_master_sw_struct(swInitPtr, &_i2c_master_2_sw);

    _i2c_master_2_sw_get_callback(&cbFunct);

    TOMMROC_HW_ERR_IF_TOMMROC_HW_LIB_FUNCT_NOT_SUCCESS_RETURN_RESULT(
            tommRoCHwBusInit(
                    TOMMRO_C_HW_BUS_I2C_MASTER_BUS_TYPE,
                    &cbFunct,
                    busHandlePtr));

    return TOMMRO_C_HW_ERR_SUCCESS;
}

#endif

#endif
