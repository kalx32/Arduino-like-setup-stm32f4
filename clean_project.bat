:: Abdulrahman S Jafari

echo off

ninja -C ./STM32/build clean 
if %errorlevel% neq 0 (
    echo error building the project
)