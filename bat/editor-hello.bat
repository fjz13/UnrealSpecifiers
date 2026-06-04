@echo off
setlocal EnableExtensions
call "%~dp0common.bat"
if %ERRORLEVEL% NEQ 0 exit /b %ERRORLEVEL%

start "" "%UE_EDITOR_EXE%" "%UESPEC_HELLO_UPROJECT%" %*

