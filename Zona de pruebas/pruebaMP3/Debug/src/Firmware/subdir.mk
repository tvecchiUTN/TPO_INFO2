################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Firmware/cr_cpp_config.cpp \
../src/Firmware/cr_startup_lpc84x.cpp \
../src/Firmware/oscilador.cpp \
../src/Firmware/swm.cpp \
../src/Firmware/systick.cpp 

C_SRCS += \
../src/Firmware/crp.c \
../src/Firmware/mtb.c 

S_SRCS += \
../src/Firmware/aeabi_romdiv_patch.s 

CPP_DEPS += \
./src/Firmware/cr_cpp_config.d \
./src/Firmware/cr_startup_lpc84x.d \
./src/Firmware/oscilador.d \
./src/Firmware/swm.d \
./src/Firmware/systick.d 

C_DEPS += \
./src/Firmware/crp.d \
./src/Firmware/mtb.d 

OBJS += \
./src/Firmware/aeabi_romdiv_patch.o \
./src/Firmware/cr_cpp_config.o \
./src/Firmware/cr_startup_lpc84x.o \
./src/Firmware/crp.o \
./src/Firmware/mtb.o \
./src/Firmware/oscilador.o \
./src/Firmware/swm.o \
./src/Firmware/systick.o 


# Each subdirectory must supply rules for building sources it contributes
src/Firmware/%.o: ../src/Firmware/%.s src/Firmware/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__USE_ROMDIVIDE -D__LPC84X__ -g3 -gdwarf-4 -mcpu=cortex-m0 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Firmware/%.o: ../src/Firmware/%.cpp src/Firmware/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -DCPP_USE_HEAP -D__LPC84X__ -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\aplicacion" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\Firmware" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\10-Teclado" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\11-Usart" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\12-lcd" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\13-adc" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\14-dac" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\1-io" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\2-gpio" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\3-PerifericoTemporizado" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\4-Timers" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\6-SalidasDigitales" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\7-EntradasDigitales" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\8-IntExt" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\9-Display" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\9-Display\09A-barrido" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\9-Display\09A-barrido\barrido-interfaz" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\9-Display\09B-segmentos" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\9-Display\09B-segmentos\segmentos-interfaz" -I"C:\Users\tomas\Github\TPO_INFO2\Zona de pruebas\pruebaMP3\src\modulos\9-Display\09C-display" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Firmware/%.o: ../src/Firmware/%.c src/Firmware/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -DCPP_USE_HEAP -D__LPC84X__ -O0 -fno-common -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Firmware

clean-src-2f-Firmware:
	-$(RM) ./src/Firmware/aeabi_romdiv_patch.o ./src/Firmware/cr_cpp_config.d ./src/Firmware/cr_cpp_config.o ./src/Firmware/cr_startup_lpc84x.d ./src/Firmware/cr_startup_lpc84x.o ./src/Firmware/crp.d ./src/Firmware/crp.o ./src/Firmware/mtb.d ./src/Firmware/mtb.o ./src/Firmware/oscilador.d ./src/Firmware/oscilador.o ./src/Firmware/swm.d ./src/Firmware/swm.o ./src/Firmware/systick.d ./src/Firmware/systick.o

.PHONY: clean-src-2f-Firmware

