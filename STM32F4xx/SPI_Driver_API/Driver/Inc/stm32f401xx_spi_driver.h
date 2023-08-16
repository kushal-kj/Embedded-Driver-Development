/*
 * stm32f401xx_spi_driver.h
 *
 *  Created on: 20-Jan-2023
 *      Author: KJ
 */

#ifndef STM32F401XX_SPI_DRIVER_H_
#define STM32F401XX_SPI_DRIVER_H_

#include "stm32f401xx.h"
#include "stm32f401xx_gpio_driver.h"

#define SPI_DEVICE_MODE_MASTER 1
#define SPI_DEVICE_MODE_SLAVE 0

//BUS CONFIGURATION
#define SPI_BUS_CONFIG_FD 1 //full duplex
#define SPI_BUS_CONFIG_HD 2 //half duplex
#define SPI_BUS_CONFIG_SIMPLEX_RX_ONLY 3

//CLOCK SPEED
#define SPI_CLK_SPEED_DIV2 0
#define SPI_CLK_SPEED_DIV4 1
#define SPI_CLK_SPEED_DIV8 2
#define SPI_CLK_SPEED_DIV16 3
#define SPI_CLK_SPEED_DIV32 4
#define SPI_CLK_SPEED_DIV64 5
#define SPI_CLK_SPEED_DIV128 6
#define SPI_CLK_SPEED_DIV256 7

//DFF
#define SPI_DFF_8BITS 0
#define SPI_DFF_16BITS 1

//CPOL
#define SPI_CPOL_LOW 0
#define SPI_CPOL_HIGH 1

//CPHA
#define SPI_CPHA_LOW 0
#define SPI_CPHA_HIGH 1

//SSM-software slave management
#define SPI_SSM_EN 1  //hardware connection
#define SPI_SSM_DI 0  //software connection

#define SPI_TXE_FLAG (1U<<SPI_SR_TXE)
#define SPI_RXNE_FLAG (1U<<SPI_SR_RXNE)
#define SPI_BUSY_FLAG (1U<<SPI_SR_BSY)

#define SPI_READY 0
#define SPI_BUSY_IN_RX 1
#define SPI_BUSY_IN_TX 2

//spi application events
#define SPI_EVENT_TX_CMPLT 1
#define SPI_EVENT_RX_CMPLT 2
#define SPI_EVENT_OVR_ERR 3
#define SPI_EVENT_CRC_ERR 4


typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SCLKSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;


}SPI_Config_t;


typedef struct
{
	SPI_RegDef_t *pSPIx;
	SPI_Config_t SPI_Config;
	uint8_t *pTXBuffer;
	uint8_t *pRXBuffer;
	uint8_t TX_len;
	uint8_t RX_len;
	uint8_t TX_State;
	uint8_t RX_State;

}SPI_Handle_t;


void SPI_PeripheralClockControl(SPI_RegDef_t *pSPIx,uint8_t En_Di);
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx,uint32_t Flagname);
void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTXBuffer,uint32_t length);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *pRXBuffer,uint32_t length);
void SPI_IRQConfig(uint8_t IRQNumber,uint8_t En_Di);
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx,uint8_t En_Di);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx,uint8_t En_Di);
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx,uint8_t En_Di);

void SPI_IRQPriority(uint8_t IRQNumber,uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pTXBuffer,uint32_t length);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pRXBuffer,uint32_t length);

void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle,uint8_t app_event);

static void spi_txe_interrupt_handle( SPI_Handle_t *pSPIHandle);
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle);
void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle);
void SPI_CloseReception(SPI_Handle_t *pSPIHandle);
void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx);


#endif /* STM32F401XX_SPI_DRIVER_H_ */
