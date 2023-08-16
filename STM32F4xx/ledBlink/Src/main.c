

#include <stdint.h>


int main(void)
{
uint32_t *AHBIENR=(uint32_t*)0x40023830;
uint32_t *GPIOA_MODER=(uint32_t*)0x40020000;
uint32_t *GPIOA_ODR=(uint32_t*)0x40020014;

*AHBIENR |=(1U<<0);

*GPIOA_MODER &=0XFFFFF3FF; //to clear ODR register
*GPIOA_MODER |=(1U<<10);
*GPIOA_ODR |=(1U<<5);

	for(;;);
}


