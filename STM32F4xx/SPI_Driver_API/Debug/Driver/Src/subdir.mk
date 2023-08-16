################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Src/stm32f401xx_gpio_driver.c \
../Driver/Src/stm32f401xx_spi_driver.c 

OBJS += \
./Driver/Src/stm32f401xx_gpio_driver.o \
./Driver/Src/stm32f401xx_spi_driver.o 

C_DEPS += \
./Driver/Src/stm32f401xx_gpio_driver.d \
./Driver/Src/stm32f401xx_spi_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Src/%.o Driver/Src/%.su: ../Driver/Src/%.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F401RE -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"C:/Users/ravindra/Desktop/STM32embedded/Embedded_Driver_Development/target/SPI_Driver_API/Driver/Inc" -I"C:/Users/ravindra/Desktop/STM32embedded/Embedded_Driver_Development/target/SPI_Driver_API/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-Src

clean-Driver-2f-Src:
	-$(RM) ./Driver/Src/stm32f401xx_gpio_driver.d ./Driver/Src/stm32f401xx_gpio_driver.o ./Driver/Src/stm32f401xx_gpio_driver.su ./Driver/Src/stm32f401xx_spi_driver.d ./Driver/Src/stm32f401xx_spi_driver.o ./Driver/Src/stm32f401xx_spi_driver.su

.PHONY: clean-Driver-2f-Src

