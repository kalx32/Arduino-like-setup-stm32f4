#/ Project: smps-controller
#/ File: CMakeLists.txt
#/ @author Abdulrahman S Jafari
#/ @brief CMake Scripts for cross-compiling cortex-m4 STM32F401xE on Windows Host

cmake_minimum_required(VERSION 3.28)

project(
    smps-controller
    VERSION 1.0.0
    LANGUAGES C ASM
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/STM32/build)

set(TARGET_MCU_FAMILY STM32F4xx)
set(TARGET_CPU STM32F401xE)
set(CPU_ATTRIBUTES 
        -mcpu=cortex-m4
        -mthumb
        -mfloat-abi=hard
        -mfpu=fpv4-sp-d16
)

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32F401CDUX_FLASH.ld)
set(STARTUP_CODE ${CMAKE_CURRENT_SOURCE_DIR}/STM32/startup/*.s)

enable_language(C ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(INCLUDE_DIR 
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Include 
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32_HAL/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32_HAL/Include/Legacy
    ${CMAKE_CURRENT_SOURCE_DIR}/Core_PROJECT/Include
)

file (GLOB SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32_HAL/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core_PROJECT/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/project_main.c
    ${STARTUP_CODE}
)


#TARGET SPECIFIC SETTINGS
add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${INCLUDE_DIR})

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    USE_HAL_DRIVER
    ${TARGET_CPU}
)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
    -Wall
    -Wno-unused-parameter
     $<$<CONFIG:Debug>: -Og -g3 -ggdb>
     $<$<CONFIG:Release>: -Og -g6>
    ${CPU_ATTRIBUTES}
)

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    -T${LINKER_SCRIPT}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -Wl,--start-group
        -lc
        -lm
    -Wl,--end-group
    -Wl,--print-memory-usage
    --specs=nosys.specs
    ${CPU_ATTRIBUTES}
)

#CREATING BINARY 
add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
)