################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Controle_Vent_entry.c \
../src/Controle_saida_entry.c \
../src/Controle_valvula_entry.c \
../src/guiapp_event_handlers.c \
../src/hal_entry.c \
../src/lcd_thread_entry.c 

C_DEPS += \
./src/Controle_Vent_entry.d \
./src/Controle_saida_entry.d \
./src/Controle_valvula_entry.d \
./src/guiapp_event_handlers.d \
./src/hal_entry.d \
./src/lcd_thread_entry.d 

OBJS += \
./src/Controle_Vent_entry.o \
./src/Controle_saida_entry.o \
./src/Controle_valvula_entry.o \
./src/guiapp_event_handlers.o \
./src/hal_entry.o \
./src/lcd_thread_entry.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	$(file > $@.in,-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_SYNERGY_ -I"C:/temp/controle_temperatura/synergy_cfg/ssp_cfg/bsp" -I"C:/temp/controle_temperatura/synergy_cfg/ssp_cfg/driver" -I"C:/temp/controle_temperatura/synergy/ssp/inc" -I"C:/temp/controle_temperatura/synergy/ssp/inc/bsp" -I"C:/temp/controle_temperatura/synergy/ssp/inc/bsp/cmsis/Include" -I"C:/temp/controle_temperatura/synergy/ssp/inc/driver/api" -I"C:/temp/controle_temperatura/synergy/ssp/inc/driver/instances" -I"C:/temp/controle_temperatura/src" -I"C:/temp/controle_temperatura/src/synergy_gen" -I"C:/temp/controle_temperatura/synergy_cfg/ssp_cfg/framework" -I"C:/temp/controle_temperatura/synergy/ssp/inc/framework/api" -I"C:/temp/controle_temperatura/synergy/ssp/inc/framework/instances" -I"C:/temp/controle_temperatura/synergy/ssp/inc/framework/tes" -I"C:/temp/controle_temperatura/synergy_cfg/ssp_cfg/framework/el" -I"C:/temp/controle_temperatura/synergy/ssp/inc/framework/el" -I"C:/temp/controle_temperatura/synergy/ssp/src/framework/el/tx" -I"C:/temp/controle_temperatura/synergy/ssp_supplemental/inc/framework/instances" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

