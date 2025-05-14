:: Abdulrahman S Jafari

echo off

ninja -C ./STM32/build
if %errorlevel% neq 0 (
    echo build finish with error
)