

#include <stdint.h>
#include "stm32f401xx.h"
#include "stm32f401xx_gpio_driver.h"
#include "stm32f401xx_spi_driver.h"

#define BUTTONPRESSED 0

void delay(void){
	for(uint32_t i=0;i<500000;i++);
}
void EXTI15_10_IRQHandler(void);
int main(void)
{
	GPIO_Handle_t GPIOLED,GPIOButton;
	GPIOLED.pGPIOx=GPIOA;
	GPIOLED.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_5;
	GPIOLED.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_IT_FT;
	GPIOLED.GPIO_PinConfig.GPIO_PinOPType=GPIO_OP_TYPE_PP;
	GPIOLED.GPIO_PinConfig.GPIO_PinSpeed=GPIO_SPEED_LOW;
	GPIOLED.GPIO_PinConfig.GPIO_pupdControl=GPIO_NO_PUPD;

	GPIOButton.pGPIOx=GPIOC;
	GPIOButton.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_13;
	GPIOButton.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_IT_FT;
	GPIOButton.GPIO_PinConfig.GPIO_PinSpeed=GPIO_SPEED_LOW;
	GPIOButton.GPIO_PinConfig.GPIO_PinOPType=GPIO_OP_TYPE_PP;
	GPIOButton.GPIO_PinConfig.GPIO_pupdControl=GPIO_NO_PUPD;

	GPIO_PeripheralClockControl(GPIOA,ENABLE);
	GPIO_PeripheralClockControl(GPIOC,ENABLE);

	GPIO_Init(&GPIOLED);
	GPIO_Init(&GPIOButton);

	/*
	 {
		if(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13)==BUTTONPRESSED)
		{
			GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
			delay();
		}
		}
*/
	GPIO_IRQConfig(IRQ_NO_EXTI10_15,ENABLE);
	GPIO_IRQPriority(IRQ_NO_EXTI10_15,NVIC_IRQ_PRIORITY15);


	while(1);
	return 0;
}
void EXTI15_10_IRQHandler(void)
{
	GPIO_IRQHandling(GPIO_PIN_NO_13);
	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
				delay();
}
