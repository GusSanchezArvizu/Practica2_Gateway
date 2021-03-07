################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/freertos_kernel/portable/MemMang/heap_4.c 

OBJS += \
./freertos/freertos_kernel/portable/MemMang/heap_4.o 

C_DEPS += \
./freertos/freertos_kernel/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/freertos_kernel/portable/MemMang/%.o: ../freertos/freertos_kernel/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\kcdia\Documents\Redes_ws\p2\Node\board" -I"D:\kcdia\Documents\Redes_ws\p2\Node\source" -I"D:\kcdia\Documents\Redes_ws\p2\Node\freertos\freertos_kernel\include" -I"D:\kcdia\Documents\Redes_ws\p2\Node\freertos\template\ARM_CM4F" -I"D:\kcdia\Documents\Redes_ws\p2\Node\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\kcdia\Documents\Redes_ws\p2\Node\drivers" -I"D:\kcdia\Documents\Redes_ws\p2\Node\utilities" -I"D:\kcdia\Documents\Redes_ws\p2\Node\component\serial_manager" -I"D:\kcdia\Documents\Redes_ws\p2\Node\component\uart" -I"D:\kcdia\Documents\Redes_ws\p2\Node\component\lists" -I"D:\kcdia\Documents\Redes_ws\p2\Node\CMSIS" -I"D:\kcdia\Documents\Redes_ws\p2\Node\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


