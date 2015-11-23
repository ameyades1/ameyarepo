################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BMPHeader.c \
../DigitRec.c \
../Filter.c \
../IconStatus.c \
../SSOCR.c \
../Version.c 

OBJS += \
./BMPHeader.o \
./DigitRec.o \
./Filter.o \
./IconStatus.o \
./SSOCR.o \
./Version.o 

C_DEPS += \
./BMPHeader.d \
./DigitRec.d \
./Filter.d \
./IconStatus.d \
./SSOCR.d \
./Version.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


