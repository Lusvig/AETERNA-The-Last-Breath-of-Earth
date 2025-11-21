@echo off
REM ============================================================================
REM AETERNA Start Script - Launches the editor or game
REM ============================================================================
REM
REM This script launches AETERNA in one of three modes:
REM   - Editor mode (default): Opens Unreal Editor with the project
REM   - Game mode: Runs the packaged game executable
REM   - Map mode: Runs specific map in editor
REM
REM Usage:
REM   start.bat [MODE] [ENGINE_PATH]
REM
REM Modes:
REM   (none)     - Launch editor (default)
REM   editor     - Launch editor (same as default)
REM   game       - Run packaged game executable
REM   map <name> - Run specific map in editor (e.g., "map Paris_Overgrown_Day47")
REM
REM Examples:
REM   start.bat
REM   start.bat editor
REM   start.bat game
REM   start.bat map Paris_Overgrown_Day47
REM ============================================================================

setlocal enabledelayedexpansion

REM Get the script directory
set SCRIPT_DIR=%~dp0
cd /d "%SCRIPT_DIR%"

REM Parse arguments
set MODE=%~1
set EXTRA_ARG=%~2
set ENGINE_PATH=%~3

REM Default to editor mode if no mode specified
if "%MODE%"=="" set MODE=editor

echo.
echo ============================================================================
echo AETERNA Launcher
echo ============================================================================
echo.

REM Validate Aeterna.uproject exists
if not exist "%SCRIPT_DIR%Aeterna.uproject" (
    echo [!] ERROR: Aeterna.uproject not found
    echo    Expected at: %SCRIPT_DIR%Aeterna.uproject
    echo.
    exit /b 1
)

REM Find Unreal Engine if not specified
if "%ENGINE_PATH%"=="" (
    echo [*] Searching for Unreal Engine 5.4...
    
    if exist "C:\Program Files\Epic\UE_5.4\Engine\Binaries\Win64\UnrealEditor.exe" (
        set ENGINE_PATH=C:\Program Files\Epic\UE_5.4
        echo [✓] Found at: !ENGINE_PATH!
    ) else if exist "C:\Program Files\Epic\UE_5.4.0\Engine\Binaries\Win64\UnrealEditor.exe" (
        set ENGINE_PATH=C:\Program Files\Epic\UE_5.4.0
        echo [✓] Found at: !ENGINE_PATH!
    ) else (
        echo.
        echo [!] ERROR: Unreal Engine 5.4+ not found
        echo.
        echo Please install Unreal Engine 5.4 or specify ENGINE_PATH:
        echo   start.bat editor "C:\Program Files\Epic\UE_5.4"
        echo.
        exit /b 1
    )
)

set EDITOR_EXE=%ENGINE_PATH%\Engine\Binaries\Win64\UnrealEditor.exe

if not exist "%EDITOR_EXE%" (
    echo [!] ERROR: Unreal Editor not found at %EDITOR_EXE%
    exit /b 1
)

REM Handle different launch modes
if /i "%MODE%"=="editor" (
    echo [*] Launching Unreal Editor...
    echo    Project: Aeterna.uproject
    echo.
    start "" "%EDITOR_EXE%" "%SCRIPT_DIR%Aeterna.uproject" -LogCmds="LogInit: Warning"
    exit /b !errorlevel!
)

if /i "%MODE%"=="game" (
    echo [*] Launching game executable...
    
    REM Look for packaged game executable
    if exist "%SCRIPT_DIR%Binaries\Win64\UE4Client\Aeterna\Binaries\Win64\AternaGame-Win64-Shipping.exe" (
        set GAME_EXE=%SCRIPT_DIR%Binaries\Win64\UE4Client\Aeterna\Binaries\Win64\AternaGame-Win64-Shipping.exe
    ) else if exist "%SCRIPT_DIR%Binaries\Win64\AternaGame.exe" (
        set GAME_EXE=%SCRIPT_DIR%Binaries\Win64\AternaGame.exe
    ) else if exist "%SCRIPT_DIR%Binaries\Win64\AETERNA_Day47_FirstContact.exe" (
        set GAME_EXE=%SCRIPT_DIR%Binaries\Win64\AETERNA_Day47_FirstContact.exe
    ) else (
        echo.
        echo [!] ERROR: Game executable not found
        echo.
        echo The game must be packaged first using:
        echo   Build\Windows\build_standalone.bat
        echo.
        exit /b 1
    )
    
    echo    Executable: !GAME_EXE!
    echo.
    start "" "!GAME_EXE!"
    exit /b !errorlevel!
)

if /i "%MODE%"=="map" (
    if "%EXTRA_ARG%"=="" (
        echo [!] ERROR: map mode requires map name
        echo.
        echo Usage: start.bat map ^<map_name^>
        echo Example: start.bat map Paris_Overgrown_Day47
        echo.
        exit /b 1
    )
    
    set MAP_NAME=%EXTRA_ARG%
    echo [*] Launching editor with specific map...
    echo    Project: Aeterna.uproject
    echo    Map: !MAP_NAME!
    echo.
    start "" "%EDITOR_EXE%" "%SCRIPT_DIR%Aeterna.uproject" "%SCRIPT_DIR%Content\Maps\!MAP_NAME!.umap" -LogCmds="LogInit: Warning"
    exit /b !errorlevel!
)

echo.
echo [!] ERROR: Unknown mode '%MODE%'
echo.
echo Valid modes:
echo   editor     - Launch editor (default)
echo   game       - Run packaged game
echo   map        - Run specific map in editor
echo.
exit /b 1
