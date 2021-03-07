################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/serial_manager/fsl_component_serial_manager.c \
../component/serial_manager/fsl_component_serial_port_uart.c 

OBJS += \
./component/serial_manager/fsl_component_serial_manager.o \
./component/serial_manager/fsl_component_serial_port_uart.o 

C_DEPS += \
./component/serial_manager/fsl_component_serial_manager.d \
./component/serial_manager/fsl_component_serial_port_uart.d 


# Each subdirectory must supply rules for building sources it contributes
component/serial_manager/%.o: ../component/serial_manager/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -D_POSIX_SOURCE -DUSE_RTOS=1 -DPRINTF_ADVANCED_ENABLE=1 -DFRDM_K64F -DFREEDOM -DSERIAL_PORT_TYPE_UART=1 -DFSL_RTOS_FREE_RTOS -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\board" -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\source" -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\mdio" -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\phy" -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\lwip\src\include\lwip\apps" -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\lwip\port" -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\lwip\src" -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\lwip\src\include" -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\drivers" -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\utilities" -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\device" -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\component\uart" -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\component\serial_manager" -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\component\lists" -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\CMSIS" -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\freertos\freertos_kernel\include" -I"D:\Archivos(D)\ITESO\8vo SEMESTRE\Redes para Sistemas Embebidos\workspace\frdmk64f_lwip_mqtt_freertos_kevin\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


