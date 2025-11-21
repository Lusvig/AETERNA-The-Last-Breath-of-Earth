@echo off
setlocal enableextensions
title AETERNA – Uninstall
echo Thank you for carrying the memory.
timeout /t 3 >nul
set "INSTALL_DIR=%~dp0"
set "SHORTCUT_NAME=AETERNA – Day 47.lnk"
set "DESKTOP_LINK=%USERPROFILE%\Desktop\%SHORTCUT_NAME%"
set "STARTMENU_LINK=%APPDATA%\Microsoft\Windows\Start Menu\Programs\%SHORTCUT_NAME%"
if exist "%DESKTOP_LINK%" del "%DESKTOP_LINK%" >nul 2>&1
if exist "%STARTMENU_LINK%" del "%STARTMENU_LINK%" >nul 2>&1
cd /d "%TEMP%"
start "" cmd /c "rmdir /s /q \"%INSTALL_DIR%\""
endlocal
exit /b 0
