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


typedef struct
{
	__vo uint32_t MODER; //GPIO port mode register
	__vo uint32_t OTYPER; //GPIO port output type register
	__vo uint32_t OSPEED; //GPIO port output speed register
	__vo uint32_t PUPDR; //GPIO port pull-up/pull-down register
	__vo uint32_t IDR; //GPIO port input data register (
	__vo uint32_t ODR; //GPIO port output data register
	__vo uint32_t BSRR; //GPIO port bit set/reset register
	__vo uint32_t LCKR; //GPIO port configuration lock register
	__vo uint32_t AFRL; //GPIO alternate function low register
	__vo uint32_t AFRH; //GPIO alternate function high register


}GPIOA_RegDef_t;


typedef struct
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


	/*__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
	 uint32_t RESERVED10;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	uint32_t RESERVED11;
	uint32_t RESERVED12;
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	uint32_t RESERVED13;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	uint32_t RESERVED14;
	uint32_t RESERVED15;
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
	uint32_t RESERVED16;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	uint32_t RESERVED17;
	uint32_t RESERVED18;
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	uint32_t RESERVED19;
	uint32_t RESERVED20;
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;
	uint32_t RESERVED21;
	__vo uint32_t DCKCFGR;
*/
}RCC_RegDef_t;


#define GPIOA ((GPIOA_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB ((GPIOA_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC ((GPIOA_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD ((GPIOA_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE ((GPIOA_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF ((GPIOA_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG ((GPIOA_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH ((GPIOA_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI ((GPIOA_RegDef_t*)GPIOI_BASEADDR)


#define RCC ((RCC_RegDef_t*)RCC_BASEADDR)


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




#endif /* STM32F401XX_H_ */
