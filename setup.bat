@echo off
setlocal enableextensions

set "SOURCE_DIR=%~dp0"
set "TARGET_DIR=%APPDATA%\AETERNA"
set "SHORTCUT_NAME=AETERNA – Day 47.lnk"
set "DESKTOP_DIR=%USERPROFILE%\Desktop"
set "DESKTOP_LINK=%DESKTOP_DIR%\%SHORTCUT_NAME%"
set "STARTMENU_DIR=%APPDATA%\Microsoft\Windows\Start Menu\Programs"
set "STARTMENU_LINK=%STARTMENU_DIR%\%SHORTCUT_NAME%"
set "UNINSTALL_SOURCE=%SOURCE_DIR%uninstall.bat"
set "SOURCE_DIR_TRIM=%SOURCE_DIR:~0,-1%"

call :Main
set "EXIT_CODE=%ERRORLEVEL%"
endlocal & exit /b %EXIT_CODE%

:Main
if "%APPDATA%"=="" (
    echo [!] APPDATA is not defined. Please run this from a standard user session.
    exit /b 1
)

if not exist "%SOURCE_DIR%AETERNA_Day47_FirstContact.exe" (
    echo [!] AETERNA_Day47_FirstContact.exe is missing. Please run setup from the official release folder.
    exit /b 1
)

call :EnsureUserDirs

if /I "%SOURCE_DIR_TRIM%"=="%TARGET_DIR%" (
    call "%TARGET_DIR%\start.bat"
    exit /b 0
)

if exist "%TARGET_DIR%\start.bat" (
    call "%TARGET_DIR%\start.bat"
    exit /b 0
)

call :CopyPayload
if errorlevel 1 exit /b 1
call :EnsureUninstaller
call :CreateShortcut "%DESKTOP_LINK%" "%TARGET_DIR%\start.bat" "%TARGET_DIR%"
call :CreateShortcut "%STARTMENU_LINK%" "%TARGET_DIR%\start.bat" "%TARGET_DIR%"
call :ShowSplash
call "%TARGET_DIR%\start.bat"
exit /b 0

:EnsureUserDirs
if not exist "%DESKTOP_DIR%" (
    mkdir "%DESKTOP_DIR%" >nul 2>&1
)
if not exist "%STARTMENU_DIR%" (
    mkdir "%STARTMENU_DIR%" >nul 2>&1
)
exit /b 0

:CopyPayload
if exist "%TARGET_DIR%" (
    rmdir /s /q "%TARGET_DIR%" >nul 2>&1
)
mkdir "%TARGET_DIR%" >nul 2>&1
robocopy "%SOURCE_DIR%" "%TARGET_DIR%" /MIR /R:1 /W:1 /NFL /NDL /NJH /NJS >nul
if errorlevel 8 (
    echo [!] Failed to copy AETERNA files. Please ensure you have enough disk space.
    exit /b 1
)
if not exist "%TARGET_DIR%\AETERNA_Day47_FirstContact.exe" (
    echo [!] Installation incomplete: AETERNA_Day47_FirstContact.exe not found.
    exit /b 1
)
exit /b 0

:EnsureUninstaller
if exist "%UNINSTALL_SOURCE%" (
    copy /y "%UNINSTALL_SOURCE%" "%TARGET_DIR%\uninstall.bat" >nul 2>&1
) else (
    call :WriteUninstallFallback
)
exit /b 0

:WriteUninstallFallback
(
    echo @echo off
    echo title AETERNA – Uninstall
    echo echo Thank you for carrying the memory.
    echo timeout /t 3 ^>nul
    echo set "INSTALL_DIR=%%~dp0"
    echo set "SHORTCUT_NAME=AETERNA – Day 47.lnk"
    echo set "DESKTOP_LINK=%%USERPROFILE%%\Desktop\%%SHORTCUT_NAME%%"
    echo set "STARTMENU_LINK=%%APPDATA%%\Microsoft\Windows\Start Menu\Programs\%%SHORTCUT_NAME%%"
    echo if exist "%%DESKTOP_LINK%%" del "%%DESKTOP_LINK%%" ^>nul 2^>^&1
    echo if exist "%%STARTMENU_LINK%%" del "%%STARTMENU_LINK%%" ^>nul 2^>^&1
    echo cd /d %%TEMP%%
    echo start "" cmd /c "rmdir /s /q ""%%INSTALL_DIR%%"""
) > "%TARGET_DIR%\uninstall.bat"
exit /b 0

:CreateShortcut
set "SHORTCUT_PATH=%~1"
set "SHORTCUT_TARGET=%~2"
set "SHORTCUT_WORKING=%~3"
powershell -NoProfile -ExecutionPolicy Bypass -Command "$ws = New-Object -ComObject WScript.Shell; $s = $ws.CreateShortcut(\"%SHORTCUT_PATH%\"); $s.TargetPath = \"%SHORTCUT_TARGET%\"; $s.WorkingDirectory = \"%SHORTCUT_WORKING%\"; $s.IconLocation = \"%TARGET_DIR%\AETERNA_Day47_FirstContact.exe,0\"; $s.Save()" >nul 2>&1
exit /b 0

:ShowSplash
start "AETERNA Install" /MIN /WAIT cmd /c "title AETERNA – Day 47 && mode con: cols=60 lines=5 && echo AETERNA is installing... && echo    Please wait while we prepare the end of the world. && timeout /t 3 >nul"
exit /b 0
