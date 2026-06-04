@echo off
set "UESPEC_REPO_ROOT=%~dp0.."
for %%I in ("%UESPEC_REPO_ROOT%") do set "UESPEC_REPO_ROOT=%%~fI"

if not defined UESPEC_UE_ROOT set "UESPEC_UE_ROOT=C:\Program Files\Epic Games\UE_5.8"
if not defined UESPEC_HELLO_ROOT set "UESPEC_HELLO_ROOT=D:\github\GitWorkspace\Hello"

set "UE_EDITOR_EXE=%UESPEC_UE_ROOT%\Engine\Binaries\Win64\UnrealEditor.exe"
set "UE_EDITOR_CMD_EXE=%UESPEC_UE_ROOT%\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
set "UE_BUILD_BAT=%UESPEC_UE_ROOT%\Engine\Build\BatchFiles\Build.bat"
set "UESPEC_HELLO_UPROJECT=%UESPEC_HELLO_ROOT%\Hello.uproject"
set "UESPEC_LOG_DIR=%UESPEC_REPO_ROOT%\.agents\logs"

if not exist "%UESPEC_LOG_DIR%" mkdir "%UESPEC_LOG_DIR%" >NUL 2>&1
for /f %%I in ('powershell -NoProfile -ExecutionPolicy Bypass -Command "Get-Date -Format yyyyMMdd-HHmmss-fff"') do set "UESPEC_LOG_RUN_ID=%%I-%RANDOM%"
powershell -NoProfile -ExecutionPolicy Bypass -Command "Get-ChildItem -LiteralPath '%UESPEC_LOG_DIR%' -Filter '*.log' -File -ErrorAction SilentlyContinue | Where-Object { $_.LastWriteTime -lt (Get-Date).AddDays(-14) } | Remove-Item -Force -ErrorAction SilentlyContinue" >NUL 2>&1

if not exist "%UE_BUILD_BAT%" (
    echo Missing UE build script: %UE_BUILD_BAT%
    exit /b 2
)

if not exist "%UE_EDITOR_EXE%" (
    echo Missing UnrealEditor.exe: %UE_EDITOR_EXE%
    exit /b 2
)

if not exist "%UE_EDITOR_CMD_EXE%" (
    echo Missing UnrealEditor-Cmd.exe: %UE_EDITOR_CMD_EXE%
    exit /b 2
)

if not exist "%UESPEC_HELLO_UPROJECT%" (
    echo Missing Hello.uproject: %UESPEC_HELLO_UPROJECT%
    exit /b 2
)

