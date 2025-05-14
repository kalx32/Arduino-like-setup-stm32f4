##Abdulrahman S Jafari

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(C_FLAGS 
"  -fdata-sections \
   -ffunction-sections \
   -mfloat-abi=hard \
   -mfpu=fpv4-sp-d16 \
   -Wl,--gc-sections")

set(COMPILER_PATH "C:/ST/STM32CubeCLT_1.16.0/GNU-tools-for-STM32/bin/") #the path to gnu-arm compiler
set(CMAKE_C_COMPILER "${COMPILER_PATH}arm-none-eabi-gcc.exe" )
set(CMAKE_CXX_COMPILER "${COMPILER_PATH}arm-none-eabi-g++.exe")
set(CMAKE_ASM_COMPILER "${COMPILER_PATH}arm-none-eabi-gcc.exe")
set(CMAKE_OBJCOPY "${COMPILER_PATH}arm-none-eabi-objcopy.exe")
set(CMAKE_SIZE "${COMPILER_PATH}arm-none-eabi-size.exe")

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${C_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGS}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${C_FLAGS}")

set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_ASM ".elf")