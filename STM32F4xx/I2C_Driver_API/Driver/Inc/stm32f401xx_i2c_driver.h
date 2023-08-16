/*
 * stm32f401xx_i2c_driver.h
 *
 *  Created on: 25-Jan-2023
 *      Author: KJ
 */

#ifndef STM32F401XX_I2C_DRIVER_H_
#define STM32F401XX_I2C_DRIVER_H_

#include "stm32f401xx.h"

typedef struct
{
	uint32_t I2C_SCLSpeed;
	uint32_t I2C_DeviceAddress;
	uint32_t I2C_AckControl;
	uint32_t I2C_FMDutyCyce;

}I2C_Config_t;

typedef struct
{
	I2C_Config_t I2C_Config;
	I2C_RegDef_t *pI2Cx;
	uint8_t *pTXBuffer;
	uint8_t *pRXBuffer;
	uint32_t TX_len;
	uint32_t RX_len;
	uint8_t TxRxState;
	uint32_t RxSize;
	uint8_t Sr;

}I2C_Handle_t;



#define I2C_SCL_SPEED_SM 100000 //I2C_SCL_SPEED
#define I2C_SCL_SPEED_FM4K 400000
#define I2C_SCL_SPEED_FM2K 200000

#define I2C_ACK_ENABLE 1
#define I2C_ACK_DISABLE 0

#define I2C_FM_DUTY_2 0
#define I2C_FM_DUTY_16_9 1

//	I2C APPLICATION STATES
#define I2C_READY 0
#define I2C_BUSY_IN_RX 1
#define I2C_BUSY_IN_TX 2

#define I2C_DISABLE_SR RESET
#define I2C_ENABLE_SR SET

//I2C STATUS FLAG RELATED DEFINATIONS
#define I2C_FLAG_TXE (1U<<I2C_SR1_TXE)
#define I2C_FLAG_RXNE (1U<<I2C_SR1_RXNE)
#define I2C_FLAG_SB (1U<<I2C_SR1_SB)
#define I2C_FLAG_OVR (1U<<I2C_SR1_OVR)
#define I2C_FLAG_ARLO (1U<<I2C_SR1_ARLO)
#define I2C_FLAG_BERR (1U<<I2C_SR1_BERR)
#define I2C_FLAG_STOPF (1U<<I2C_SR1_STOPF)
#define I2C_FLAG_ADD10 (1U<<I2C_SR1_ADD10)
#define I2C_FLAG_BTF (1U<<I2C_SR1_BTF)
#define I2C_FLAG_ADDR (1U<<I2C_SR1_ADDR)
#define I2C_FLAG_TIMEOUT (1U<<I2C_SR1_TIMEOUT)



void I2C_PeripheralClockControl(I2C_RegDef_t *pI2Cx,uint8_t En_Di);

void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *pTXBuffer,uint32_t len,uint8_t SlaveAddr,uint8_t sr);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,uint8_t *pRXBuffer,uint32_t len,uint8_t SlaveAddr,uint8_t sr);

void I2C_ManageACKing(I2C_RegDef_t *pI2Cx,uint8_t En_Di);

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx,uint32_t Flagname);

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx,uint8_t En_Di);

void I2C_IRQPriority(uint8_t IRQNumber,uint32_t IRQPriority);
void I2C_IRQConfig(uint8_t IRQNumber,uint8_t En_Di);

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle,uint8_t app_event);









#endif /* STM32F401XX_I2C_DRIVER_H_ */
