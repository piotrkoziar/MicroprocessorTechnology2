################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/srcdawnetest4/explorer.c \
../src/srcdawnetest4/main.c \
../src/srcdawnetest4/menu.c 

OBJS += \
./src/srcdawnetest4/explorer.o \
./src/srcdawnetest4/main.o \
./src/srcdawnetest4/menu.o 

C_DEPS += \
./src/srcdawnetest4/explorer.d \
./src/srcdawnetest4/main.d \
./src/srcdawnetest4/menu.d 


# Each subdirectory must supply rules for building sources it contributes
src/srcdawnetest4/%.o: ../src/srcdawnetest4/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -DSTM32 '-D__FPU_PRESENT = 1' -DARM_MATH_CM7 -DSTM32F7 -DSTM32F723IEKx -DSTM32F723E_DISCO -DDEBUG -DSTM32F723xx -DUSE_HAL_DRIVER -DINCLUDE_FATFS -DUSE_USB_FS -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/Utilities/STM32F723E-Discovery" -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/Utilities/Components/st7789h2" -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/Utilities/Components/mx25l512" -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/CMSIS/device" -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/Utilities/Components/ft6x06" -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/HAL_Driver/Inc/Legacy" -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc" -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/Utilities/Components/Common" -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/Middlewares/Third_Party/FatFs/src" -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/HAL_Driver/Inc" -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/Utilities/Components/wm8994" -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/Utilities/Fonts" -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/inc" -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/Utilities/Log" -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/Middlewares/Third_Party/FatFs/src/drivers" -I"C:/Users/piotr/OneDrive/Pulpit/Eclipse/test4/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


