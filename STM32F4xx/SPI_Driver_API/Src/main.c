

#include <stdint.h>
#include "stm32f401xx.h"
#include "stm32f401xx_gpio_driver.h"

void delay(void){
	for(uint32_t i=0;i<500000;i++);
}

int main(void)
{
	GPIO_Handle_t GPIOLED;
	GPIOLED.pGPIOx=GPIOA;
	GPIOLED.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_5;
	GPIOLED.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUT;
	GPIOLED.GPIO_PinConfig.GPIO_PinOPType=GPIO_OP_TYPE_OD;
	GPIOLED.GPIO_PinConfig.GPIO_PinSpeed=GPIO_SPEED_LOW;
	GPIOLED.GPIO_PinConfig.GPIO_pupdControl=GPIO_NO_PUPD;

	GPIO_PeripheralClockControl(GPIOA,ENABLE);
	GPIO_Init(&GPIOLED);

	while(1){
			GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
			delay();
		}


	return 0;
}
