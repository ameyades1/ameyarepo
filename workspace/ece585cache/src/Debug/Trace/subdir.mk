################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Trace/Trace.cpp \
../Trace/Trace_Cmds.cpp 

OBJS += \
./Trace/Trace.o \
./Trace/Trace_Cmds.o 

CPP_DEPS += \
./Trace/Trace.d \
./Trace/Trace_Cmds.d 


# Each subdirectory must supply rules for building sources it contributes
Trace/%.o: ../Trace/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


