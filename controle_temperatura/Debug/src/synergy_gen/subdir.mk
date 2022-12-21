################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/synergy_gen/Controle_Vent.c \
../src/synergy_gen/Controle_saida.c \
../src/synergy_gen/Controle_valvula.c \
../src/synergy_gen/common_data.c \
../src/synergy_gen/hal_data.c \
../src/synergy_gen/lcd_thread.c \
../src/synergy_gen/main.c \
../src/synergy_gen/pin_data.c 

C_DEPS += \
./src/synergy_gen/Controle_Vent.d \
./src/synergy_gen/Controle_saida.d \
./src/synergy_gen/Controle_valvula.d \
./src/synergy_gen/common_data.d \
./src/synergy_gen/hal_data.d \
./src/synergy_gen/lcd_thread.d \
./src/synergy_gen/main.d \
./src/synergy_gen/pin_data.d 

OBJS += \
./src/synergy_gen/Controle_Vent.o \
./src/synergy_gen/Controle_saida.o \
./src/synergy_gen/Controle_valvula.o \
./src/synergy_gen/common_data.o \
./src/synergy_gen/hal_data.o \
./src/synergy_gen/lcd_thread.o \
./src/synergy_gen/main.o \
./src/synergy_gen/pin_data.o 


# Each subdirectory must supply rules for building sources it contributes
src/synergy_gen/%.o: ../src/synergy_gen/%.c
	$(file > $@.in,-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_SYNERGY_ -I"C:/temp/controle_temperatura/synergy_cfg/ssp_cfg/bsp" -I"C:/temp/controle_temperatura/synergy_cfg/ssp_cfg/driver" -I"C:/temp/controle_temperatura/synergy/ssp/inc" -I"C:/temp/controle_temperatura/synergy/ssp/inc/bsp" -I"C:/temp/controle_temperatura/synergy/ssp/inc/bsp/cmsis/Include" -I"C:/temp/controle_temperatura/synergy/ssp/inc/driver/api" -I"C:/temp/controle_temperatura/synergy/ssp/inc/driver/instances" -I"C:/temp/controle_temperatura/src" -I"C:/temp/controle_temperatura/src/synergy_gen" -I"C:/temp/controle_temperatura/synergy_cfg/ssp_cfg/framework" -I"C:/temp/controle_temperatura/synergy/ssp/inc/framework/api" -I"C:/temp/controle_temperatura/synergy/ssp/inc/framework/instances" -I"C:/temp/controle_temperatura/synergy/ssp/inc/framework/tes" -I"C:/temp/controle_temperatura/synergy_cfg/ssp_cfg/framework/el" -I"C:/temp/controle_temperatura/synergy/ssp/inc/framework/el" -I"C:/temp/controle_temperatura/synergy/ssp/src/framework/el/tx" -I"C:/temp/controle_temperatura/synergy/ssp_supplemental/inc/framework/instances" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

