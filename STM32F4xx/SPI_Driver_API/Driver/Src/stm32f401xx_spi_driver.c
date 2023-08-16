/*
 * stm32f401xx_spi_driver.c
 *
 *  Created on: 20-Jan-2023
 *      Author: KJ
 */

#include<stdint.h>
#include "stm32f401xx.h"
#include "stm32f401xx_spi_driver.h"
#include "stm32f401xx_gpio_driver.h"

void SPI_PeripheralClockControl(SPI_RegDef_t *pSPIx,uint8_t En_Di)
{

	if(En_Di==ENABLE)
	{
		if(pSPIx==SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if(pSPIx==SPI2)
				{
					SPI2_PCLK_EN();
				}
		else if(pSPIx==SPI3)
				{
					SPI3_PCLK_EN();
				}
		else if(pSPIx==SPI4)
				{
					SPI4_PCLK_EN();
				}
		else if(pSPIx==SPI5)
				{
					SPI5_PCLK_EN();
				}
		else if(pSPIx==SPI6)
				{
					SPI6_PCLK_EN();
				}
	}
	else
	{
		if(pSPIx==SPI1)
				{
					SPI1_PCLK_DI();
				}
				else if(pSPIx==SPI2)
						{
							SPI2_PCLK_DI();
						}
				else if(pSPIx==SPI3)
						{
							SPI3_PCLK_DI();
						}
				else if(pSPIx==SPI4)
						{
							SPI4_PCLK_DI();
						}
				else if(pSPIx==SPI5)
						{
							SPI5_PCLK_DI();
						}
				else if(pSPIx==SPI6)
						{
							SPI6_PCLK_DI();
						}
	}

}


void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	uint32_t temp=0;
	SPI_PeripheralClockControl(pSPIHandle->pSPIx,ENABLE);
	//configure the device mode
	temp |=pSPIHandle->SPI_Config.SPI_DeviceMode<<2; //it checks the MSTR pin

	//configure bus config
	if(pSPIHandle->SPI_Config.SPI_BusConfig==SPI_BUS_CONFIG_FD)
	{
		temp |=(1U<<15);
	}
	else if(pSPIHandle->SPI_Config.SPI_BusConfig==SPI_BUS_CONFIG_HD)
	{
		temp &=~(1U<<15);

	}
	else if(pSPIHandle->SPI_Config.SPI_BusConfig==SPI_BUS_CONFIG_SIMPLEX_RX_ONLY)
	{
		temp &=~(1U<<15);
		temp |=(1U<<10);

	}

	//configure the SPI serial clock speed
	temp |=pSPIHandle->SPI_Config.SPI_SCLKSpeed<<3;

	//configure DFF
	temp |=pSPIHandle->SPI_Config.SPI_DFF<<11;

	//configure CPOL
	temp |=pSPIHandle->SPI_Config.SPI_CPOL<<1;

	//configure CPHA
	temp |=pSPIHandle->SPI_Config.SPI_CPHA<<0;

	pSPIHandle->pSPIx->SPI_CR1=temp;

}
void SPI_DeInit(SPI_RegDef_t *pSPIx)
{



}

void SPI_SSIConfig(SPI_RegDef_t *pSPIx,uint8_t En_Di)
{
	if(En_Di==ENABLE)
	{
		pSPIx->SPI_CR1 |=(1U<<SPI_CR1_SSI);
	}
	else{
		pSPIx->SPI_CR1 &=~(1U<<SPI_CR1_SSI);
	}
}

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx,uint8_t En_Di)
{
	if(En_Di==ENABLE)
	{
		pSPIx->SPI_CR1 |=(1U<<SPI_CR1_SPE);
	}
	else{
		pSPIx->SPI_CR1 &=~(1U<<SPI_CR1_SPE);

	}
}

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx,uint8_t En_Di)
{
	if(En_Di==ENABLE)
	{
		pSPIx->SPI_CR2 |=(1U<<SPI_CR2_SSOE);
	}
	else{
		pSPIx->SPI_CR2 &=~(1U<<SPI_CR2_SSOE);

	}

}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx,uint32_t Flagname)
{
	if(pSPIx->SPI_SR & Flagname)
	{


		return FLAG_SET;
	}
	return FLAG_RESET;
}

void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTXBuffer,uint32_t length)
{
	uint8_t temp;
	while(length>0)
	{
		//wait until TXE is empty
		while(SPI_GetFlagStatus(pSPIx,SPI_TXE_FLAG)==FLAG_RESET);

		//CHECK DFF bit in CR1
		if(pSPIx->SPI_CR1 & (1U<<SPI_CR1_DFF))
		{
			//FOR 16 BIT DATA
			pSPIx->SPI_DR=*(uint16_t*)pTXBuffer;
			length--;
			length--;
			(uint16_t*)pTXBuffer++;
		}
		else{
			//for 8 bit data
			pSPIx->SPI_DR=*pTXBuffer;
			length--;
			pTXBuffer++;

		}


	}
	while(!(pSPIx->SPI_CR1 & (SPI_TXE_FLAG))){} //wait until txe flag is set
	while(!(pSPIx->SPI_CR1 & (SPI_RXNE_FLAG))){}  //wait until rxne flag is set

		//clear overflow flag
	temp=pSPIx->SPI_DR;
	temp=pSPIx->SPI_SR;

}


void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *pRXBuffer,uint32_t length)
{
	while(length>0)
		{
			//wait until TXE is empty
			while(SPI_GetFlagStatus(pSPIx,SPI_RXNE_FLAG)==FLAG_RESET);

			//CHECK DFF bit in CR1
			if(pSPIx->SPI_CR1 & (1U<<SPI_CR1_DFF))
			{
				//FOR 16 BIT DATA
				*(uint16_t*)pRXBuffer=pSPIx->SPI_DR;
				length--;
				length--;
				(uint16_t*)pRXBuffer++;
			}
			else{
				//for 8 bit data
			*pRXBuffer=	pSPIx->SPI_DR;
				length--;
				pRXBuffer++;

			}

}

}
void SPI_IRQConfig(uint8_t IRQNumber,uint8_t En_Di)
{
	if(En_Di==ENABLE)
		{
			if(IRQNumber<=31)
			{
				*NVIC_ISER0=(1U<<IRQNumber);
			}
			else if(IRQNumber>31 && IRQNumber<64)
			{
				*NVIC_ISER2=(1U<<IRQNumber%32);

			}
			else if(IRQNumber>=64 && IRQNumber<96)
			{
				*NVIC_ISER3=(1U<<IRQNumber%64);

			}

		}
		else{
			if(IRQNumber<=31)
					{
						*NVIC_ICER0=(1U<<IRQNumber);
					}
					else if(IRQNumber>31 && IRQNumber<64)
					{
						*NVIC_ICER2=(1U<<IRQNumber%32);

					}
					else if(IRQNumber>=64 && IRQNumber<96)
					{
						*NVIC_ICER3=(1U<<IRQNumber%64);

					}


		}

}


void SPI_IRQPriority(uint8_t IRQNumber,uint32_t IRQPriority)
{
		uint8_t temp1=IRQNumber/4;
		uint8_t temp2=IRQNumber%4;
		uint8_t shiftcount=(8*temp2)+(8-NO_PR_BITS_IMPLEMENTED);
		*(NVIC_PR_BASEADDR+(temp1*4)) |=(IRQPriority<<shiftcount);

}

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pTXBuffer,uint32_t length)
{
	uint8_t state=pSPIHandle->TX_State;
	if(state!=SPI_BUSY_IN_TX){

	//save the tx buffer address and length info
	pSPIHandle->pTXBuffer=pTXBuffer;
	pSPIHandle->TX_len=length;
	//mark the SPI state busy in transmission
	pSPIHandle->TX_State=SPI_BUSY_IN_TX;
	//enable the clock control bit to get the interrupt whenever TXE flag is set in status register
	pSPIHandle->pSPIx->SPI_CR2 |=(1U<<SPI_CR2_TXEIE);
	}
	return state;
}

uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pRXBuffer,uint32_t length)
{
	uint8_t state=pSPIHandle->RX_State;
		if(state!=SPI_BUSY_IN_RX){


		//save the tx buffer address and length info
		pSPIHandle->pRXBuffer=pRXBuffer;
		pSPIHandle->RX_len=length;
		//mark the SPI state busy in transmission
		pSPIHandle->RX_State=SPI_BUSY_IN_RX;
		//enable the clock control bit to get the interrupt whenever TXE flag is set in status register
		pSPIHandle->pSPIx->SPI_CR2 |=(1U<<SPI_CR2_RXNEIE);
		}
		return state;
}

void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp1=0,temp2=0;
	//first lets check for TXE
	temp1=pSPIHandle->pSPIx->SPI_SR & (SPI_SR_TXE);
	temp1=pSPIHandle->pSPIx->SPI_CR2 & (SPI_CR2_TXEIE);

	if(temp1 && temp2)
	{
		//handling TXE
		spi_txe_interrupt_handle(pSPIHandle);
	}
	//check for RXNE
	temp1=pSPIHandle->pSPIx->SPI_SR & (SPI_SR_RXNE);
	temp1=pSPIHandle->pSPIx->SPI_CR2 & (SPI_CR2_RXNEIE);

	if(temp1&&temp2)
		{
			//Handling RXNE
		spi_rxne_interrupt_handle(pSPIHandle);

		}
		//check for Overflow flag
		temp1=pSPIHandle->pSPIx->SPI_SR & (SPI_SR_OVR);
		temp1=pSPIHandle->pSPIx->SPI_CR2 & (SPI_CR2_ERRIE);

		if(temp1&&temp2)
				{
					//Handling overflow flag
			spi_ovr_err_interrupt_handle(pSPIHandle);

				}
}

static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	if(pSPIHandle->pSPIx->SPI_CR1 & (1U<<SPI_CR1_DFF))
			{
				//FOR 16 BIT DATA
				pSPIHandle->pSPIx->SPI_DR=*(uint16_t*)pSPIHandle->pTXBuffer;
				pSPIHandle->TX_len--;
				pSPIHandle->TX_len--;
				(uint16_t*)pSPIHandle->pTXBuffer++;
			}
			else{
				//for 8 bit data
				pSPIHandle->pSPIx->SPI_DR=*pSPIHandle->pTXBuffer;
				pSPIHandle->TX_len--;
				pSPIHandle->pTXBuffer++;

			}
	if(!pSPIHandle->TX_len)
	{
		SPI_CloseTransmission(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_TX_CMPLT);
	}

}
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	if(pSPIHandle->pSPIx->SPI_CR1 & (1U<<SPI_CR1_DFF))
				{
					//FOR 16 BIT DATA
					*(uint16_t*)pSPIHandle->pTXBuffer=pSPIHandle->pSPIx->SPI_DR;
					pSPIHandle->RX_len--;
					pSPIHandle->RX_len--;
					(uint16_t*)pSPIHandle->pTXBuffer++;
				}
				else{
					//for 8 bit data
				*pSPIHandle->pTXBuffer=	pSPIHandle->pSPIx->SPI_DR;
				pSPIHandle->RX_len--;
				pSPIHandle->pRXBuffer++;

				}
	if(!pSPIHandle->RX_len)
		{
		SPI_CloseReception(pSPIHandle);
			SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_RX_CMPLT);
		}
}
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp;
	if(pSPIHandle->TX_State!=SPI_BUSY_IN_TX){
	temp=pSPIHandle->pSPIx->SPI_DR;
	temp=pSPIHandle->pSPIx->SPI_SR;
	}
	(void)temp;
	SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_OVR_ERR);
}

void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->SPI_CR2&=~(1<<SPI_CR2_TXEIE);
			pSPIHandle->pTXBuffer=NULL;
			pSPIHandle->TX_len=0;
			pSPIHandle->TX_State=SPI_READY;
}
void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{

				pSPIHandle->pSPIx->SPI_CR2&=~(1<<SPI_CR2_RXNEIE);
				pSPIHandle->pRXBuffer=NULL;
				pSPIHandle->RX_len=0;
				pSPIHandle->RX_State=SPI_READY;

}
void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx)
{
	uint8_t temp;
		temp=pSPIx->SPI_DR;
		temp=pSPIx->SPI_SR;

		(void)temp;
}

__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle,uint8_t app_event)
{

}
