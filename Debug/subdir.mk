################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Client.cpp \
../ClientManager.cpp \
../CommandDispatcher.cpp \
../MThread.cpp \
../TCPSocket.cpp \
../UDPMessenger.cpp \
../UDPSocket.cpp \
../main.cpp 

OBJS += \
./Client.o \
./ClientManager.o \
./CommandDispatcher.o \
./MThread.o \
./TCPSocket.o \
./UDPMessenger.o \
./UDPSocket.o \
./main.o 

CPP_DEPS += \
./Client.d \
./ClientManager.d \
./CommandDispatcher.d \
./MThread.d \
./TCPSocket.d \
./UDPMessenger.d \
./UDPSocket.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


