################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/syscalls.c \
../src/system_stm32f30x.c 

CPP_SRCS += \
../src/Button.cpp \
../src/ByteDisplay.cpp \
../src/CurrentSource.cpp \
../src/Settings.cpp \
../src/Temperature.cpp \
../src/TimeUtils.cpp \
../src/main.cpp 

OBJS += \
./src/Button.o \
./src/ByteDisplay.o \
./src/CurrentSource.o \
./src/Settings.o \
./src/Temperature.o \
./src/TimeUtils.o \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f30x.o 

C_DEPS += \
./src/syscalls.d \
./src/system_stm32f30x.d 

CPP_DEPS += \
./src/Button.d \
./src/ByteDisplay.d \
./src/CurrentSource.d \
./src/Settings.d \
./src/Temperature.d \
./src/TimeUtils.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=c++1y -DSTM32 -DSTM32F3 -DSTM32F30 -DSTM32F303VCTx -DSTM32F3DISCOVERY -DSTM32F303xC -DUSE_STDPERIPH_DRIVER -I"C:/Users/Mikhail/git/temperatureController/Utilities" -I"C:/Users/Mikhail/git/temperatureController/StdPeriph_Driver/inc" -I"C:/Users/Mikhail/git/temperatureController/inc" -I"C:/Users/Mikhail/git/temperatureController/CMSIS/device" -I"C:/Users/Mikhail/git/temperatureController/CMSIS/core" -O0 -g3 -pedantic -pedantic-errors -Wall -Wextra -Wconversion -fmessage-length=0  -fno-threadsafe-statics -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F3 -DSTM32F30 -DSTM32F303VCTx -DSTM32F3DISCOVERY -DSTM32F303xC -DUSE_STDPERIPH_DRIVER -I"C:/Users/Mikhail/git/temperatureController/Utilities" -I"C:/Users/Mikhail/git/temperatureController/StdPeriph_Driver/inc" -I"C:/Users/Mikhail/git/temperatureController/inc" -I"C:/Users/Mikhail/git/temperatureController/CMSIS/device" -I"C:/Users/Mikhail/git/temperatureController/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

