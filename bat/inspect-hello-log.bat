@echo off
setlocal EnableExtensions
call "%~dp0common.bat"
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%

set "HELLO_SAVED_LOG_DIR=%UESPEC_HELLO_ROOT%\Saved\Logs"

if not exist "%HELLO_SAVED_LOG_DIR%" (
    echo Missing Hello Saved Logs directory: %HELLO_SAVED_LOG_DIR%
    exit /b 2
)

for /f "usebackq delims=" %%I in (`powershell -NoProfile -ExecutionPolicy Bypass -Command "Get-ChildItem -LiteralPath '%HELLO_SAVED_LOG_DIR%' -Filter '*.log' -File | Sort-Object LastWriteTime -Descending | Select-Object -First 1 -ExpandProperty FullName"`) do set "LOGFILE=%%I"

if not defined LOGFILE (
    echo No Hello log files found under: %HELLO_SAVED_LOG_DIR%
    exit /b 2
)

echo Inspecting latest Hello editor log...
echo Log: %LOGFILE%

echo.
echo -- Errors / Fatal / Assertions --
powershell -NoProfile -ExecutionPolicy Bypass -Command "Select-String -Path '%LOGFILE%' -Pattern ': Error:|Fatal error|Assertion failed|appError called|Ensure condition failed' -CaseSensitive:$false | Select-Object -First 120 | ForEach-Object { $_.Line }"

echo.
echo -- Specifier / Reflection Markers --
powershell -NoProfile -ExecutionPolicy Bypass -Command "Select-String -Path '%LOGFILE%' -Pattern 'UPROPERTY|UFUNCTION|UCLASS|meta=|PropertyFlags|ClassFlags|FunctionFlags|EditCondition|SaveGame|Instanced|WorldContext' -CaseSensitive:$false | Select-Object -First 120 | ForEach-Object { $_.Line }"

echo.
echo -- Tail --
powershell -NoProfile -ExecutionPolicy Bypass -Command "Get-Content -Path '%LOGFILE%' -Tail 80"

exit /b 0
