:: Abdulrahman S Jafari

echo off

echo the following programs need to be installed to compile this project

echo looking for cmake.exe

where cmake.exe >null 2>&1
if %errorlevel% neq 0 (
    echo please install cmake and make sure it is added in the path
) else (
    echo cmake found
)

echo looking for ninja.exe

where ninja.exe >null 2>&1
if %errorlevel% neq 0 (
    echo please install ninja and make sure it is added in the path
) else (
    echo ninja found
)

echo looking for gnu-arm embedded toolchain

where arm-none-eabi-gcc.exe >null 2>&1
if %errorlevel% neq 0 (
    echo please install GNU-ARM embedded toolchain for Windows i.e arm-none-eabi-gcc, g++, etc
)

echo running cmake

cmake . --preset debug 

ninja -C ./STM32/build
if %errorlevel% neq 0 (
    echo build finish with error
)
