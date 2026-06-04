@echo off
setlocal EnableExtensions
call "%~dp0common.bat"
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%

set "LOGFILE=%UESPEC_LOG_DIR%\hello-build-%UESPEC_LOG_RUN_ID%.log"

echo Running Hello UE5.8 editor build...
echo Project: %UESPEC_HELLO_UPROJECT%
echo Log: %LOGFILE%

call "%UE_BUILD_BAT%" HelloEditor Win64 Development "%UESPEC_HELLO_UPROJECT%" -waitmutex %* > "%LOGFILE%" 2>&1
set "EXIT_CODE=%ERRORLEVEL%"

echo.
echo -- Build Result --
echo Exit code: %EXIT_CODE%

if %EXIT_CODE% EQU 0 (
    echo Build succeeded.
    echo.
    echo -- Summary --
    findstr /I /C:"Total execution time" /C:"Build succeeded" /C:"Result:" "%LOGFILE%"
) else (
    echo Build failed.
    echo.
    echo -- Errors --
    powershell -NoProfile -ExecutionPolicy Bypass -Command "Select-String -Path '%LOGFILE%' -Pattern 'error|fatal|failed|exception|assertion|ensure|crash' -CaseSensitive:$false | Select-Object -First 120 | ForEach-Object { $_.Line }"
    echo.
    echo -- Last 120 Lines --
    powershell -NoProfile -ExecutionPolicy Bypass -Command "Get-Content -Path '%LOGFILE%' -Tail 120"
)

echo.
echo Full log: %LOGFILE%
exit /b %EXIT_CODE%

