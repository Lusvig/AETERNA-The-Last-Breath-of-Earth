@echo off
REM ============================================================================
REM AETERNA Start Script
REM Opens the project in Unreal Editor or runs packaged game
REM ============================================================================
REM
REM This script will:
REM   - Detect Unreal Engine 5.4+
REM   - Open the project in the Editor
REM   - Or launch the packaged game if available
REM
REM Usage:
REM   start.bat              - Open in Editor (default)
REM   start.bat editor       - Open in Editor
REM   start.bat game         - Launch packaged game
REM   start.bat build        - Build the project first, then open in Editor
REM
REM ============================================================================

setlocal enabledelayedexpansion

cd /d "%~dp0"

set MODE=editor
if not "%~1"=="" set MODE=%~1

echo.
echo ============================================================================
echo AETERNA Launcher
echo ============================================================================
echo.

REM Check if project file exists
if not exist "Aeterna.uproject" (
    echo ERROR: Aeterna.uproject not found
    echo Make sure you're running this from the project root directory
    exit /b 1
)

REM Try to find Unreal Engine
echo Searching for Unreal Engine 5.4+...
set "ENGINE_PATH="

REM Check common installation locations
for %%D in (
    "C:\Program Files\Epic\UE_5.4"
    "C:\Program Files\Epic\UE_5.5"
    "C:\Program Files\Epic\UE_5.6"
    "C:\Program Files\Epic\UE_5.7"
) do (
    if exist "%%D\Engine\Binaries\Win64\UE4Editor.exe" (
        set "ENGINE_PATH=%%D"
        goto :engine_found
    )
)

if "!ENGINE_PATH!"=="" (
    echo ERROR: Unreal Engine 5.4+ not found
    echo.
    echo Please install Unreal Engine 5.4 or later:
    echo   https://www.unrealengine.com/download
    echo.
    echo Expected installation location:
    echo   C:\Program Files\Epic\UE_5.4
    echo.
    exit /b 1
)

:engine_found
echo Found: !ENGINE_PATH!
echo.

REM Handle different modes
if /i "%MODE%"=="editor" goto :open_editor
if /i "%MODE%"=="build" goto :build_and_edit
if /i "%MODE%"=="game" goto :launch_game
(
    echo ERROR: Unknown mode '%MODE%'
    echo.
    echo Usage:
    echo   start.bat              - Open in Editor
    echo   start.bat editor       - Open in Editor
    echo   start.bat build        - Build then open in Editor
    echo   start.bat game         - Launch packaged game
    echo.
    exit /b 1
)

:open_editor
echo [*] Opening AETERNA in Unreal Editor...
echo.
"!ENGINE_PATH!\Engine\Binaries\Win64\UE4Editor.exe" "%cd%\Aeterna.uproject"
exit /b 0

:build_and_edit
echo [*] Building project...
set "BUILD_SCRIPT=!ENGINE_PATH!\Engine\Build\BatchFiles\Build.bat"
if not exist "!BUILD_SCRIPT!" (
    echo ERROR: Build.bat not found at !BUILD_SCRIPT!
    exit /b 1
)

REM Generate project files first
if exist "GenerateProjectFiles.bat" (
    call GenerateProjectFiles.bat
)

REM Build in Development configuration
call "!BUILD_SCRIPT!" Aeterna Win64 Development -Project="%cd%\Aeterna.uproject" -NoGold
if errorlevel 1 (
    echo WARNING: Build failed, opening editor anyway...
)

echo.
echo [*] Opening AETERNA in Unreal Editor...
"!ENGINE_PATH!\Engine\Binaries\Win64\UE4Editor.exe" "%cd%\Aeterna.uproject"
exit /b 0

:launch_game
echo [*] Launching packaged game...
echo.

REM Check for packaged executable
set "GAME_EXE="
if exist "Binaries\Win64\UE4Client\Aeterna\Binaries\Win64\AeternaGame-Win64-Shipping.exe" (
    set "GAME_EXE=Binaries\Win64\UE4Client\Aeterna\Binaries\Win64\AeternaGame-Win64-Shipping.exe"
) else if exist "AETERNA_Day47_FirstContact.exe" (
    set "GAME_EXE=AETERNA_Day47_FirstContact.exe"
)

if "!GAME_EXE!"=="" (
    echo ERROR: Packaged game executable not found
    echo.
    echo To build the game, run:
    echo   .\Build\Windows\build_standalone.ps1
    echo.
    echo Or open the editor and build from there:
    echo   start.bat editor
    echo.
    exit /b 1
)

echo Launching: !GAME_EXE!
echo.
start "" "!GAME_EXE!"
exit /b 0
