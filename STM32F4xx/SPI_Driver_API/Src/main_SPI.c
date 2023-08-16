/*
 * PB12- SS or NSS
 * PB13-SCLK
 * PB14-MISO
 * PB15-MOSI
 */

#include<stdint.h>
#include<string.h>
#include "stm32f401xx.h"
#include "stm32f401xx_spi_driver.h"
#include "stm32f401xx_gpio_driver.h"

void SPI2_GPIO_Init(void)
{
	GPIO_Handle_t SPIPins;
	SPIPins.pGPIOx=GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode=5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType=GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_pupdControl=GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed=GPIO_SPEED_FAST;

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins);

}

void SPI2_Inits(void)
{
	SPI_Handle_t SPI2Handle;

	SPI2Handle.pSPIx=SPI2;
	SPI2Handle.SPI_Config.SPI_BusConfig=SPI_BUS_CONFIG_FD;
	SPI2Handle.SPI_Config.SPI_DeviceMode=SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPI_Config.SPI_DFF=SPI_DFF_8BITS;
	SPI2Handle.SPI_Config.SPI_SCLKSpeed=SPI_CLK_SPEED_DIV2;
	SPI2Handle.SPI_Config.SPI_CPOL=SPI_CPOL_LOW;
	SPI2Handle.SPI_Config.SPI_CPHA=SPI_CPHA_LOW;
	SPI2Handle.SPI_Config.SPI_SSM=SPI_SSM_EN;
	SPI_Init(&SPI2Handle);

}


int main()
{
	char user_data[]="hello world";
	SPI2_GPIO_Init();
	SPI2_Inits();

	SPI_SSIConfig(SPI2,ENABLE);
	SPI_SSOEConfig(SPI2,ENABLE);

	SPI_SendData(SPI2, user_data, strlen(user_data));
	while(1){

		SPI_PeripheralControl(SPI2,ENABLE);
	//	uint8_t datalen=strlen(user_data);
		cs_enable();

		SPI_SendData(SPI2, user_data, strlen(user_data));
		cs_disable();
		while(SPI_GetFlagStatus(SPI2,SPI_SR_BSY));
		SPI_PeripheralControl(SPI2,DISABLE);



	}

	return 0;
}
