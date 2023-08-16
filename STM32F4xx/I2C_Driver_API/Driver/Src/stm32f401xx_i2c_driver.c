/*
 * stm32f401xx_i2c_driver.c
 *
 *  Created on: 25-Jan-2023
 *      Author: KJ
 */

#include "stm32f401xx.h"
#include "stm32f401xx_i2c_driver.h"

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx,uint8_t SlaveAddr);
static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx,uint8_t SlaveAddr);
static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle);
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);

void I2C_ManageACKing(I2C_RegDef_t *pI2Cx,uint8_t En_Di)
{
	if(En_Di==I2C_ACK_ENABLE){
		//enable the ack
		pI2Cx->I2C_CR1 |=(1<<I2C_CR1_ACK);
	}
	else{
		pI2Cx->I2C_CR1 &=~(1<<I2C_CR1_ACK);

	}
}

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->I2C_CR1 |=(1<<I2C_CR1_START);

}
static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx,uint8_t SlaveAddr)
{
	SlaveAddr=SlaveAddr<<1;
	SlaveAddr&=~(1); //write bit=0
	pI2Cx->I2C_DR =SlaveAddr;
}
static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx,uint8_t SlaveAddr)
{
	SlaveAddr=SlaveAddr<<1;
	SlaveAddr|=1; //read bit=1
	pI2Cx->I2C_DR =SlaveAddr;
}
static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle)
{
	uint32_t dummy_read;
	//check for device mode
	if(pI2CHandle->pI2Cx->I2C_SR2&(1<<I2C_SR2_MSL))
	{
		//DEVICE IS IN MASTER MODE
		if(pI2CHandle->TxRxState==I2C_BUSY_IN_RX)
		{
			if(pI2CHandle->RxSize){
				//disable the ack
				I2C_ManageACKing(pI2CHandle->pI2Cx,DISABLE);
				//clear the ADDR flag(read sr1,read sr2)
						dummy_read=pI2CHandle->pI2Cx->I2C_SR1;
						dummy_read=pI2CHandle->pI2Cx->I2C_SR2;
						(void)dummy_read;
			}
		}

		else{
			//clear the ADDR flag(read sr1,read sr2)
		dummy_read=pI2CHandle->pI2Cx->I2C_SR1;
		dummy_read=pI2CHandle->pI2Cx->I2C_SR2;
		(void)dummy_read;

	}
	}
	else{
		//device is in slave mode
		//clear the ADDR flag(read sr1,read sr2)
		dummy_read=pI2CHandle->pI2Cx->I2C_SR1;
		dummy_read=pI2CHandle->pI2Cx->I2C_SR2;
		(void)dummy_read;
	}
}

static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->I2C_CR1 |=(1<<I2C_CR1_STOP);
}

uint32_t RCC_GetPLLOutputClock()
{
	return 0;
}

void I2C_PeripheralClockControl(I2C_RegDef_t *pI2Cx,uint8_t En_Di)
{
	if(En_Di==ENABLE)
		{
			if(pI2Cx==I2C1)
			{
			I2C1_PCLK_EN();
			}
			else if(pI2Cx==I2C2)
			{
			I2C2_PCLK_EN();
			}
			else if(pI2Cx==I2C3)
			{
			I2C3_PCLK_EN();
			}
		}
	else
	{
			if(pI2Cx==I2C1)
			{
			I2C1_PCLK_DI();
			}
			else if(pI2Cx==I2C2)
			{
			I2C2_PCLK_DI();
			}
			else if(pI2Cx==I2C3)
			{
			I2C3_PCLK_DI();
			}
	}
}

uint16_t AHB_PreScalar[8]={2,4,8,16,64,128,256,512};
uint16_t APB_PreScalar[8]={2,4,8,16};


uint32_t RCC_GetPCLKvalue(void)
{
	uint32_t pclk1,SystemClk;
	uint8_t clksrc,temp,ahbp,apb1;
	clksrc=((RCC->CFGR>>2)&3);
	if(clksrc==0)
	{
		SystemClk=8000000;

	}
	else if(clksrc==1)
	{
		SystemClk=16000000;

	}
	else if(clksrc==2)
	{
		SystemClk=RCC_GetPLLOutputClock();

	}
temp=((RCC->CFGR>>4)&0xF);
	if(temp<8){
		ahbp=1;
	}
	else{
		ahbp=AHB_PreScalar[temp-8];
	}
temp=((RCC->CFGR>>10)&0xF);
		if(temp<8){
			apb1=1;
		}
		else{
			apb1=APB_PreScalar[temp-4];
		}
		pclk1=(SystemClk/ahbp)/apb1;
	return pclk1;
}

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	uint32_t tempreg=0;
	//enable clock for i2c peripheral
	I2C_PeripheralClockControl(pI2CHandle->pI2Cx,ENABLE);
	//enable ACK control bit
	tempreg|=pI2CHandle->I2C_Config.I2C_AckControl<<10;
	pI2CHandle->pI2Cx->I2C_CR1=tempreg;

	//config the freq field of CR2
	tempreg=0;
	tempreg|=RCC_GetPCLKvalue()/1000000U;
	pI2CHandle->pI2Cx->I2C_CR2=tempreg & 0x3F;

	//program the device own address
	tempreg=0;
	tempreg|=pI2CHandle->I2C_Config.I2C_DeviceAddress<<1;
	tempreg|=(1<<14);

	pI2CHandle->pI2Cx->I2C_OAR1=tempreg;

	//ccr calculations
	uint16_t ccr_value=0;
	tempreg=0;
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed<=I2C_SCL_SPEED_SM){
		//mode is standard mode
		ccr_value=(RCC_GetPCLKvalue()/(2*pI2CHandle->I2C_Config.I2C_SCLSpeed));
		tempreg|=(ccr_value & 0xfff);

	}
	else{
		//mode is fast mode
		tempreg|=(1<<15);
		tempreg|=(pI2CHandle->I2C_Config.I2C_FMDutyCyce<<14);
		if(pI2CHandle->I2C_Config.I2C_FMDutyCyce==I2C_FM_DUTY_2)
		{
			ccr_value=(RCC_GetPCLKvalue()/(3*pI2CHandle->I2C_Config.I2C_SCLSpeed));

		}
		else{
			ccr_value=(RCC_GetPCLKvalue()/(25*pI2CHandle->I2C_Config.I2C_SCLSpeed));

		}
		tempreg|=(ccr_value & 0xfff);

	}
	pI2CHandle->pI2Cx->I2C_CCR=tempreg;

	//Trise configuration
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed<=I2C_SCL_SPEED_SM)
	{
		//for standard mode
		tempreg|=(RCC_GetPCLKvalue()/1000000U)+1;
	}
	else
	{
		//for fast mode
		tempreg|=(RCC_GetPCLKvalue()*300/1000000U);

	}
	pI2CHandle->pI2Cx->I2C_TRISE=(tempreg & 0x3F);

}

void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{

}

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *pTXBuffer,uint32_t len,uint8_t SlaveAddr,uint8_t sr)
{
	//generate start condition
	 I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//confirm the start condition is generation is completed by checking the SB Flag in SR1
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB));

	//send the address of the slave r/w bit set - totally 8 bits(write)
	I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx,SlaveAddr);

	//confirm the address flag is completed by chcking the ADDR flag in SR1
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));


	//clear the ADDR flag
	I2C_ClearADDRFlag(pI2CHandle);

	//send the data till len is 0
	while(len>0)
	{
		while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE));
		pI2CHandle->pI2Cx->I2C_DR=*pTXBuffer;
		pTXBuffer++;
		len--;

	}
	//when len is 0 wait for TXE=1 & BTF=1
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE));
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF));


	//generate a stop condition
	if(sr==I2C_DISABLE_SR)
	I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

}

void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,uint8_t *pRXBuffer,uint32_t len,uint8_t SlaveAddr,uint8_t sr)
{
		//generate start condition
	 I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

		//confirm the start condition is generation is completed by checking the SB Flag in SR1
		while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB));

		//send the address of the slave r/w bit set - totally 8 bits(read)
		I2C_ExecuteAddressPhaseRead(pI2CHandle->pI2Cx,SlaveAddr);

		//confirm the address flag is completed by checking the ADDR flag in SR1
		while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));

		//procedure to read only  byte
		if(len==1)
		{
			//clear the addr flag
			I2C_ClearADDRFlag(pI2CHandle);
			//wait until rxne is 1
			while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE));
			//geneate stop condition
			if(sr==I2C_DISABLE_SR)
				I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
			//read data from the buffer
			*pRXBuffer=pI2CHandle->pI2Cx->I2C_DR;
		}

		//procedure to read multiple bytes
		if(len>1)
		{
			//clear the addr flag
			I2C_ClearADDRFlag(pI2CHandle);
			//read until len becomes 0
			for(uint32_t i=len;i>0;i--)
			{
				//wait until rxne is 1
							while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE));
			if(i==2)//last 2 bytes are remaining
			{
				//disable acking
				I2C_ManageACKing(pI2CHandle->pI2Cx,I2C_ACK_DISABLE);
				I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

			}
			*pRXBuffer=pI2CHandle->pI2Cx->I2C_DR;
			pRXBuffer++;
			}
		}
//RENABLE ACKING
		if(pI2CHandle->I2C_Config.I2C_AckControl==I2C_ACK_ENABLE)
			I2C_ManageACKing(pI2CHandle->pI2Cx,I2C_ACK_ENABLE);

}




uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx,uint32_t Flagname)
{
	if(pI2Cx->I2C_SR1 & Flagname)
		{


			return FLAG_SET;
		}
		return FLAG_RESET;
}

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx,uint8_t En_Di)
{
	if(En_Di==ENABLE)
		{
		pI2Cx->I2C_CR1 |=(1U<<I2C_CR1_PE);
		}
		else{
			pI2Cx->I2C_CR1 &=~(1U<<I2C_CR1_PE);

		}
}

void I2C_IRQPriority(uint8_t IRQNumber,uint32_t IRQPriority)
{

}
void I2C_IRQConfig(uint8_t IRQNumber,uint8_t En_Di)
{

}

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle,uint8_t app_event)
{

}


