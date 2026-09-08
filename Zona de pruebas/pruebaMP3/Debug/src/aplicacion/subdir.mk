################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/aplicacion/aplicacion.cpp \
../src/aplicacion/inicializacion.cpp \
../src/aplicacion/main.cpp 

CPP_DEPS += \
./src/aplicacion/aplicacion.d \
./src/aplicacion/inicializacion.d \
./src/aplicacion/main.d 

OBJS += \
./src/aplicacion/aplicacion.o \
./src/aplicacion/inicializacion.o \
./src/aplicacion/main.o 


# Each subdirectory must supply rules for building sources it contributes
src/aplicacion/%.o: ../src/aplicacion/%.cpp src/aplicacion/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -DCPP_USE_HEAP -D__LPC84X__ -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\aplicacion" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\Firmware" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\10-Teclado" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\11-Usart" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\12-lcd" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\13-adc" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\14-dac" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\1-io" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\2-gpio" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\3-PerifericoTemporizado" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\4-Timers" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\6-SalidasDigitales" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\7-EntradasDigitales" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\8-IntExt" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\9-Display" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\9-Display\09A-barrido" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\9-Display\09A-barrido\barrido-interfaz" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\9-Display\09B-segmentos" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\9-Display\09B-segmentos\segmentos-interfaz" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\9-Display\09C-display" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-aplicacion

clean-src-2f-aplicacion:
	-$(RM) ./src/aplicacion/aplicacion.d ./src/aplicacion/aplicacion.o ./src/aplicacion/inicializacion.d ./src/aplicacion/inicializacion.o ./src/aplicacion/main.d ./src/aplicacion/main.o

.PHONY: clean-src-2f-aplicacion

