/*
 * stm32f401xx_gpio_driver.h
 *
 *  Created on: Jan 17, 2023
 *      Author: KJ
 */

#ifndef STM32F401XX_GPIO_DRIVER_H_
#define STM32F401XX_GPIO_DRIVER_H_
#include "stm32f401xx.h"
#include<stdint.h>

//MACROS FOR GPIO_PinNumber(@GPIO_PIN_NUMBER)
#define GPIO_PIN_NO_0 0
#define GPIO_PIN_NO_1 1
#define GPIO_PIN_NO_2 2
#define GPIO_PIN_NO_3 3
#define GPIO_PIN_NO_4 4
#define GPIO_PIN_NO_5 5
#define GPIO_PIN_NO_6 6
#define GPIO_PIN_NO_7 7
#define GPIO_PIN_NO_8 8
#define GPIO_PIN_NO_9 9
#define GPIO_PIN_NO_10 10
#define GPIO_PIN_NO_11 11
#define GPIO_PIN_NO_12 12
#define GPIO_PIN_NO_13 13
#define GPIO_PIN_NO_14 14
#define GPIO_PIN_NO_15 15

//MACROS FOR GPIO_PinMode(@GPIO_PIN_MODES)
#define GPIO_MODE_IN 0
#define GPIO_MODE_OUT 1
#define GPIO_MODE_ALTFN 2
#define GPIO_MODE_ANALOG 3

#define GPIO_MODE_IT_FT 4 //interrupt
#define GPIO_MODE_IT_RT 5 //interrupt
#define GPIO_MODE_IT_RFT 6 //interrupt

//MACROS FOR GPIO_PinSpeed(@GPIO_PIN_SPEED)
#define GPIO_SPEED_LOW 0
#define GPIO_SPEED_MEDIUM 1
#define GPIO_SPEED_FAST 2
#define GPIO_SPEED_HIGH 3

//MACROS FOR GPIO_pupdControl(@GPIO_PIN_PU_PD)
#define GPIO_NO_PUPD 0
#define GPIO_PIN_PU 1
#define GPIO_PIN_PD 2
#define GPIO_PIN_RESERVED 3

//MACROS FOR GPIO_PinOPType(@GPIO_PIN_OUTPUT_TYPE)
#define GPIO_OP_TYPE_PP 0
#define GPIO_OP_TYPE_OD 1


typedef struct
{

	uint8_t GPIO_PinNumber;  //@GPIO_PIN_NUMBER
	uint8_t GPIO_PinMode;  //@GPIO_PIN_MODES
	uint8_t GPIO_PinSpeed;  //@GPIO_PIN_SPEED
	uint8_t GPIO_pupdControl;  //@GPIO_PIN_PU_PD
	uint8_t GPIO_PinOPType;  //@GPIO_PIN_OUTPUT_TYPE
	uint8_t GPIO_PinAltFunMode;

}GPIO_PinConfig_t;

typedef struct
{
	GPIO_PinConfig_t GPIO_PinConfig;
	GPIOx_RegDef_t *pGPIOx; //this pointer holds the base address of all GPIO registers

}GPIO_Handle_t;


void GPIO_PeripheralClockControl(GPIOx_RegDef_t *pGPIOx,uint8_t En_Di);
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIOx_RegDef_t *pGPIOx);
uint8_t GPIO_ReadFromInputPin(GPIOx_RegDef_t *pGPIOx,uint8_t PinNumber);
void GPIO_WriteToOutputPin(GPIOx_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t value);
uint16_t GPIO_ReadFromInputPort(GPIOx_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPort(GPIOx_RegDef_t *pGPIOx,uint8_t value);
void GPIO_ToggleOutputPin(GPIOx_RegDef_t *pGPIOx,uint8_t PinNumber);
void GPIO_IRQConfig(uint8_t IRQNumber,uint8_t En_Di);
void GPIO_IRQPriority(uint8_t IRQNumber,uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);



#endif /* STM32F401XX_GPIO_DRIVER_H_ */




