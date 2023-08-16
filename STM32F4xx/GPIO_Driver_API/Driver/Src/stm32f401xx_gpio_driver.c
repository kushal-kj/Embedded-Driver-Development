/*
 * stm32f401xx_gpio_driver.c
 *
 *  Created on: Jan 17, 2023
 *      Author: KJ
 */
#include "stm32f401xx.h"
#include "stm32f401xx_gpio_driver.h"
#include<stdint.h>

void GPIO_PeripheralClockControl(GPIOx_RegDef_t *pGPIOx,uint8_t En_Di)
{
	if(En_Di==ENABLE)
	{
		if(pGPIOx==GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		if(pGPIOx==GPIOB)
				{
					GPIOB_PCLK_EN();
				}
		if(pGPIOx==GPIOC)
				{
					GPIOC_PCLK_EN();
				}
		if(pGPIOx==GPIOD)
				{
					GPIOD_PCLK_EN();
				}
		if(pGPIOx==GPIOE)
				{
					GPIOE_PCLK_EN();
				}
		if(pGPIOx==GPIOF)
				{
					GPIOF_PCLK_EN();
				}
		if(pGPIOx==GPIOG)
				{
					GPIOG_PCLK_EN();
				}
		if(pGPIOx==GPIOH)
				{
					GPIOH_PCLK_EN();
				}
		if(pGPIOx==GPIOI)
				{
					GPIOI_PCLK_EN();
				}

	}
	else{

		if(pGPIOx==GPIOA)
				{
					GPIOA_PCLK_DI();
				}
				if(pGPIOx==GPIOB)
						{
							GPIOB_PCLK_DI();
						}
				if(pGPIOx==GPIOC)
						{
							GPIOC_PCLK_DI();
						}
				if(pGPIOx==GPIOD)
						{
							GPIOD_PCLK_DI();
						}
				if(pGPIOx==GPIOE)
						{
							GPIOE_PCLK_DI();
						}
				if(pGPIOx==GPIOF)
						{
							GPIOF_PCLK_DI();
						}
				if(pGPIOx==GPIOG)
						{
							GPIOG_PCLK_DI();
						}
				if(pGPIOx==GPIOH)
						{
							GPIOH_PCLK_DI();
						}
				if(pGPIOx==GPIOI)
						{
							GPIOI_PCLK_DI();
						}
	}
}
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp=0;
	// Configure the Mode of GPIO Pin

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode<=GPIO_MODE_ANALOG)
	{
		uint32_t temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode<<(2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &=~(0x3<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIOx->MODER |=temp;
	}
	else
	{
		//interrupt mode
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_IT_FT)
		{
			//configure FTSR
			EXTI->EXTI_FTSR |=(1U<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->EXTI_RSTR &=~(1U<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_IT_RT)
		{
			//configure RTSR
			EXTI->EXTI_RSTR |=(1U<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->EXTI_FTSR &=~(1U<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode==GPIO_MODE_IT_RFT)
		{
			//configure RFTSR
			EXTI->EXTI_FTSR |=(1U<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->EXTI_RSTR |=(1U<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}

		//configure GPIO port selection in SYSCFG
		uint8_t temp1 ,temp2;
		temp1=pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber /4;
		temp2=pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber %4;

		uint8_t portcode=GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->SYSCFG_EXTICR[temp1]=portcode<<(4*temp2);
	}

	// Configure Speed
	 temp=0;
	  temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode<<(2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	 		pGPIOHandle->pGPIOx->OSPEED &=~(0x3<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	 		pGPIOHandle->pGPIOx->OSPEED |=temp;

	// Configure the pupd settings
	 temp=0;
	  temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode<<(2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			pGPIOHandle->pGPIOx->PUPDR &=~(0x3<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			pGPIOHandle->pGPIOx->PUPDR |=temp;

	// Configure the Optype
	 temp=0;
	  temp=(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode<<(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			pGPIOHandle->pGPIOx->OTYPER &=~(0x3<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			pGPIOHandle->pGPIOx->OTYPER |=temp;


	// Configure the alt functionality
			temp=0;
			if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ALTFN)
			{
			uint32_t temp1 ,temp2;
			temp1=pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber /8;
			temp2=pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber %8;
			pGPIOHandle->pGPIOx->AFR[temp1]&= ~(0xF <<(4 *temp2));
			pGPIOHandle->pGPIOx->AFR[temp1]|= pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode <<(4 *temp2);
			}



}
void GPIO_DeInit(GPIOx_RegDef_t *pGPIOx)
{

			if(pGPIOx==GPIOA)
			{
				GPIOA_REG_RESET();
			}
			if(pGPIOx==GPIOB)
					{
				GPIOB_REG_RESET();
					}
			if(pGPIOx==GPIOC)
					{
				GPIOC_REG_RESET();
					}
			if(pGPIOx==GPIOD)
					{
				GPIOD_REG_RESET();
					}
			if(pGPIOx==GPIOE)
					{
				GPIOE_REG_RESET();
					}
			if(pGPIOx==GPIOF)
					{
				GPIOF_REG_RESET();
					}
			if(pGPIOx==GPIOG)
					{
				GPIOG_REG_RESET();
					}
			if(pGPIOx==GPIOH)
					{
				GPIOH_REG_RESET();
					}
			if(pGPIOx==GPIOI)
					{
				GPIOI_REG_RESET();
					}

		}


uint8_t GPIO_ReadFromInputPin(GPIOx_RegDef_t *pGPIOx,uint8_t PinNumber)
{
uint8_t value;
value=(uint8_t)(pGPIOx->IDR>>PinNumber)&(0x00000001);
return value;

}
void GPIO_WriteToOutputPin(GPIOx_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t value)
{
	if(value==GPIO_PIN_SET){
		pGPIOx->ODR |=(1<<PinNumber);
	}
	else{
		pGPIOx->ODR &=~(1<<PinNumber);

	}
}
uint16_t GPIO_ReadFromInputPort(GPIOx_RegDef_t *pGPIOx)
{
	uint16_t value;
	value=(uint16_t)(pGPIOx->IDR);
	return value;

}
void GPIO_WriteToOutputPort(GPIOx_RegDef_t *pGPIOx,uint8_t value)
{
	pGPIOx->ODR |=value;

}
void GPIO_ToggleOutputPin(GPIOx_RegDef_t *pGPIOx,uint8_t PinNumber)
{

	pGPIOx->ODR ^=(1<<PinNumber);

}
void GPIO_IRQConfig(uint8_t IRQNumber,uint8_t En_Di)
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
		else if(IRQNumber>64 && IRQNumber<96)
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
				else if(IRQNumber>64 && IRQNumber<96)
				{
					*NVIC_ICER3=(1U<<IRQNumber%64);

				}


	}

}

void GPIO_IRQPriority(uint8_t IRQNumber,uint8_t IRQPriority)
{
	uint8_t temp1=IRQNumber/4;
	uint8_t temp2=IRQNumber%4;
	uint8_t shiftcount=(8*temp2)+(8-NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASEADDR+(temp1*4)) |=(IRQPriority<<shiftcount);

}

void GPIO_IRQHandling(uint8_t PinNumber)
{
	if(EXTI->EXTI_PR & (1U<<PinNumber))
	{
		EXTI->EXTI_PR |=(1U<<PinNumber);
	}

}

