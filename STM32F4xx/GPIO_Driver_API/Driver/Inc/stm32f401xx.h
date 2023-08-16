/*
 * stm32f401xx.h
 *
 *  Created on: Jan 16, 2023
 *      Author: KJ
 */

#ifndef STM32F401XX_H_
#define STM32F401XX_H_
#include <stdint.h>

#define __vo volatile

//For INTERRUPTS
#define NVIC_ISER0 ((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1 ((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2 ((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3 ((__vo uint32_t*)0xE000E10C)

#define NVIC_ICER0 ((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1 ((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2 ((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3 ((__vo uint32_t*)0xE000E18C)

#define NVIC_IPR0 ((__vo uint32_t*)0xE000E400)
#define NVIC_IPR1 ((__vo uint32_t*)0xE000E404)
#define NVIC_IPR2 ((__vo uint32_t*)0xE000E408)
#define NVIC_IPR3 ((__vo uint32_t*)0xE000E40C)

#define NVIC_PR_BASEADDR ((__vo uint32_t*)0xE000E400)
#define NO_PR_BITS_IMPLEMENTED 4

#define NVIC_IRQ_PRIORITY1 1
#define NVIC_IRQ_PRIORITY2 2
#define NVIC_IRQ_PRIORITY3 3
#define NVIC_IRQ_PRIORITY4 4
#define NVIC_IRQ_PRIORITY5 5
#define NVIC_IRQ_PRIORITY6 6
#define NVIC_IRQ_PRIORITY7 7
#define NVIC_IRQ_PRIORITY8 8
#define NVIC_IRQ_PRIORITY9 9
#define NVIC_IRQ_PRIORITY10 10
#define NVIC_IRQ_PRIORITY11 11
#define NVIC_IRQ_PRIORITY12 12
#define NVIC_IRQ_PRIORITY13 13
#define NVIC_IRQ_PRIORITY14 14
#define NVIC_IRQ_PRIORITY15 15
#define NVIC_IRQ_PRIORITY16 16

#define FLASH_BASEADDR 0X80000000U
#define SRAM1_BASEADDR 0X20000000U
#define SRAM2_BASEADDR 0X2001C000U
#define ROM_BASEADDR 0X1FFF0000U
#define SRAM SRAM1_BASEADDR


#define APB1PERIPH_BASEADDR 0X40000000U
#define APB2PERIPH_BASEADDR 0X40010000U
#define AHB1PERIPH_BASEADDR 0X40020000U
#define AHB2PERIPH_BASEADDR 0X50000000U
#define AHB3PERIPH_BASEADDR 0XA0000000U


#define RCC_BASEADDR 0X40023800U
#define EXTI_BASEADDR 0X40013C00U
#define SYSCFG_BASEADDR 0X40013800U


#define GPIOA_BASEADDR 0X40020000U
#define GPIOB_BASEADDR 0X40020400U
#define GPIOC_BASEADDR 0X40020800U
#define GPIOD_BASEADDR 0X40020C00U
#define GPIOE_BASEADDR 0X40021000U
#define GPIOF_BASEADDR 0X40021400U
#define GPIOG_BASEADDR 0X40021800U
#define GPIOH_BASEADDR 0X40021C00U
#define GPIOI_BASEADDR 0X40022000U


#define I2C1_BASEADDR 0X40005400U
#define I2C2_BASEADDR 0X40005800U
#define I2C3_BASEADDR 0X40005C00U


#define SPI1_BASEADDR 0X40013000U
#define SPI2_BASEADDR 0X40003800U
#define SPI3_BASEADDR 0X40003C00U
#define SPI4_BASEADDR 0X40013400U
#define SPI5_BASEADDR 0X40015000U
#define SPI6_BASEADDR 0X40015400U


#define USART1_BASEADDR 0X40011000U
#define USART2_BASEADDR 0X40004400U
#define USART3_BASEADDR 0X40004800U
#define UART4_BASEADDR 0X40004C00U
#define UART5_BASEADDR 0X40005000U
#define USART6_BASEADDR 0X40011400U
#define UART7_BASEADDR 0X40007800U
#define UART8_BASEADDR 0X40007C00U


typedef struct //PERIPHERAL REGISTER DEFINATION FOR RCC
{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
	 uint32_t RESERVED0;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	uint32_t RESERVED1;
	uint32_t RESERVED2;
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	uint32_t RESERVED3;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	uint32_t RESERVED4;
	uint32_t RESERVED5;
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
	uint32_t RESERVED6;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	uint32_t RESERVED7;
	uint32_t RESERVED8;
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	uint32_t RESERVED9;
	uint32_t RESERVED10;
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;

}RCC_RegDef_t;


typedef struct //PERIPHERAL REGISTER DEFINATION FOR GPIO
{
	__vo uint32_t MODER; //GPIO port mode register
	__vo uint32_t OTYPER; //GPIO port output type register
	__vo uint32_t OSPEED; //GPIO port output speed register
	__vo uint32_t PUPDR; //GPIO port pull-up/pull-down register
	__vo uint32_t IDR; //GPIO port input data register (
	__vo uint32_t ODR; //GPIO port output data register
	__vo uint32_t BSRR; //GPIO port bit set/reset register
	__vo uint32_t LCKR; //GPIO port configuration lock register
	__vo uint32_t AFR[2]; // AFR[0]=GPIO alternate function LOW register AND AFR[1]=GPIO alternate function HIGH register



}GPIOx_RegDef_t;


typedef struct //PERIPHERAL REGISTER DEFINATION FOR EXTI
{
	__vo uint32_t EXTI_IMR;
	__vo uint32_t EXTI_EMR;
	__vo uint32_t EXTI_RSTR;
	__vo uint32_t EXTI_FTSR;
	__vo uint32_t EXTI_SWIER;
	__vo uint32_t EXTI_PR;

}EXTI_RegDef_t;


typedef struct //PERIPHERAL REGISTER DEFINATION FOR SYSCFG
{
	__vo uint32_t SYSCFG_MEMRM;
	__vo uint32_t SYSCFG_PMC;
	__vo uint32_t SYSCFG_EXTICR[4];
	__vo uint32_t SYSCFG_CMPCR;


}SYSCFG_RegDef_t;


#define GPIOA ((GPIOx_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB ((GPIOx_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC ((GPIOx_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD ((GPIOx_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE ((GPIOx_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF ((GPIOx_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG ((GPIOx_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH ((GPIOx_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI ((GPIOx_RegDef_t*)GPIOI_BASEADDR)


#define RCC ((RCC_RegDef_t*)RCC_BASEADDR)
#define EXTI ((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)


#define GPIOA_PCLK_EN() (RCC->AHB1ENR |=(1U<<0)) //CLOCK ENABLE FOR GPIO
#define GPIOB_PCLK_EN() (RCC->AHB1ENR |=(1U<<1))
#define GPIOC_PCLK_EN() (RCC->AHB1ENR |=(1U<<2))
#define GPIOD_PCLK_EN() (RCC->AHB1ENR |=(1U<<3))
#define GPIOE_PCLK_EN() (RCC->AHB1ENR |=(1U<<4))
#define GPIOF_PCLK_EN() (RCC->AHB1ENR |=(1U<<5))
#define GPIOG_PCLK_EN() (RCC->AHB1ENR |=(1U<<6))
#define GPIOH_PCLK_EN() (RCC->AHB1ENR |=(1U<<7))
#define GPIOI_PCLK_EN() (RCC->AHB1ENR |=(1U<<8))

#define GPIOA_PCLK_DI() (RCC->AHB1ENR &=~(1U<<0)) //CLOCK DISABLE FOR GPIO
#define GPIOB_PCLK_DI() (RCC->AHB1ENR &=~(1U<<1))
#define GPIOC_PCLK_DI() (RCC->AHB1ENR &=~(1U<<2))
#define GPIOD_PCLK_DI() (RCC->AHB1ENR &=~(1U<<3))
#define GPIOE_PCLK_DI() (RCC->AHB1ENR &=~(1U<<4))
#define GPIOF_PCLK_DI() (RCC->AHB1ENR &=~(1U<<5))
#define GPIOG_PCLK_DI() (RCC->AHB1ENR &=~(1U<<6))
#define GPIOH_PCLK_DI() (RCC->AHB1ENR &=~(1U<<7))
#define GPIOI_PCLK_DI() (RCC->AHB1ENR &=~(1U<<8))


#define GPIOA_REG_RESET() do{(RCC->AHB1RSTR |=(1U<<0));(RCC->AHB1RSTR &=~(1U<<0));}while(0)
#define GPIOB_REG_RESET() do{(RCC->AHB1RSTR |=(1U<<1));(RCC->AHB1RSTR &=~(1U<<1));}while(0)
#define GPIOC_REG_RESET() do{(RCC->AHB1RSTR |=(1U<<2));(RCC->AHB1RSTR &=~(1U<<2));}while(0)
#define GPIOD_REG_RESET() do{(RCC->AHB1RSTR |=(1U<<3));(RCC->AHB1RSTR &=~(1U<<3));}while(0)
#define GPIOE_REG_RESET() do{(RCC->AHB1RSTR |=(1U<<4));(RCC->AHB1RSTR &=~(1U<<4));}while(0)
#define GPIOF_REG_RESET() do{(RCC->AHB1RSTR |=(1U<<5));(RCC->AHB1RSTR &=~(1U<<5));}while(0)
#define GPIOG_REG_RESET() do{(RCC->AHB1RSTR |=(1U<<6));(RCC->AHB1RSTR &=~(1U<<6));}while(0)
#define GPIOH_REG_RESET() do{(RCC->AHB1RSTR |=(1U<<7));(RCC->AHB1RSTR &=~(1U<<7));}while(0)
#define GPIOI_REG_RESET() do{(RCC->AHB1RSTR |=(1U<<8));(RCC->AHB1RSTR &=~(1U<<8));}while(0)


#define SYSCFG_PCLK_EN() (RCC->APB2ENR |=(1U<<14))
#define GPIO_BASEADDR_TO_CODE(x) ((x=GPIOA)?0:\
									(x=GPIOB)?1:\
									(x=GPIOC)?2:\
									(x=GPIOD)?3:\
									(x=GPIOE)?4:\
									(x=GPIOF)?5:\
									(x=GPIOG)?6:\
									(x=GPIOH)?7:\
									(x=GPIOI)?8:0)


#define IRQ_NO_EXTI0 6
#define IRQ_NO_EXTI1 7
#define IRQ_NO_EXTI2 8
#define IRQ_NO_EXTI3 9
#define IRQ_NO_EXTI4 10
#define IRQ_NO_EXTI5_9 23
#define IRQ_NO_EXTI10_15 40



#define ENABLE 1
#define DISABLE 0
#define SET ENABLE
#define RESET DISABLE
#define GPIO_PIN_SET SET
#define GPIO_PIN_RESET RESET


#endif /* STM32F401XX_H_ */
