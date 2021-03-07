################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/MK64F12_Project_can_example.c \
../source/semihost_hardfault.c 

OBJS += \
./source/MK64F12_Project_can_example.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/MK64F12_Project_can_example.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\HP\Documents\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\Node\board" -I"C:\Users\HP\Documents\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\Node\source" -I"C:\Users\HP\Documents\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\Node\freertos\freertos_kernel\include" -I"C:\Users\HP\Documents\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\Node\freertos\template\ARM_CM4F" -I"C:\Users\HP\Documents\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\Node\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\HP\Documents\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\Node\drivers" -I"C:\Users\HP\Documents\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\Node\utilities" -I"C:\Users\HP\Documents\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\Node\component\serial_manager" -I"C:\Users\HP\Documents\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\Node\component\uart" -I"C:\Users\HP\Documents\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\Node\component\lists" -I"C:\Users\HP\Documents\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\Node\CMSIS" -I"C:\Users\HP\Documents\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\Node\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


