@echo off
REM ============================================================================
REM AETERNA Setup Script - Initializes development environment
REM ============================================================================
REM
REM This script performs initial setup for AETERNA development:
REM   - Validates prerequisites (Unreal Engine, Visual Studio)
REM   - Generates Visual Studio project files
REM   - Compiles the game module
REM   - Initializes Git LFS
REM
REM Requirements:
REM   - Unreal Engine 5.4+ installed
REM   - Visual Studio 2022 with C++ tools
REM   - Git with LFS support
REM
REM Usage:
REM   setup.bat [ENGINE_PATH]
REM
REM Example:
REM   setup.bat "C:\Program Files\Epic\UE_5.4"
REM ============================================================================

setlocal enabledelayedexpansion

REM Get the script directory
set SCRIPT_DIR=%~dp0
cd /d "%SCRIPT_DIR%"

echo.
echo ============================================================================
echo AETERNA Development Setup
echo ============================================================================
echo.

REM Parse engine path argument
set ENGINE_PATH=%~1

if "%ENGINE_PATH%"=="" (
    echo [*] Searching for Unreal Engine 5.4 in standard locations...
    
    if exist "C:\Program Files\Epic\UE_5.4\Engine\Build\BatchFiles\Build.bat" (
        set ENGINE_PATH=C:\Program Files\Epic\UE_5.4
        echo [✓] Found at: !ENGINE_PATH!
    ) else if exist "C:\Program Files\Epic\UE_5.4.0\Engine\Build\BatchFiles\Build.bat" (
        set ENGINE_PATH=C:\Program Files\Epic\UE_5.4.0
        echo [✓] Found at: !ENGINE_PATH!
    ) else (
        echo.
        echo [!] ERROR: Unreal Engine 5.4+ not found in standard location
        echo.
        echo Please specify ENGINE_PATH as argument:
        echo   setup.bat "C:\Program Files\Epic\UE_5.4"
        echo.
        exit /b 1
    )
)

if not exist "%ENGINE_PATH%\Engine\Build\BatchFiles\Build.bat" (
    echo.
    echo [!] ERROR: Invalid ENGINE_PATH
    echo   Path does not exist: %ENGINE_PATH%
    echo.
    exit /b 1
)

echo.
echo [1/5] Validating prerequisites...
echo   Engine: %ENGINE_PATH%
echo   Project: %SCRIPT_DIR%Aeterna.uproject

if not exist "%SCRIPT_DIR%Aeterna.uproject" (
    echo [!] ERROR: Aeterna.uproject not found
    exit /b 1
)
echo [✓] Prerequisites valid

REM Step 1: Initialize Git LFS if available
echo.
echo [2/5] Initializing Git LFS...
where /q git
if !errorlevel! equ 0 (
    git lfs install
    git lfs pull
    echo [✓] Git LFS initialized
) else (
    echo [~] Git not found, skipping LFS setup
)

REM Step 2: Clean previous build artifacts
echo.
echo [3/5] Cleaning previous build artifacts...
if exist "Intermediate" (
    rmdir /s /q Intermediate >nul 2>&1
)
if exist "Binaries" (
    rmdir /s /q Binaries >nul 2>&1
)
if exist "Saved" (
    rmdir /s /q Saved >nul 2>&1
)
echo [✓] Build artifacts cleaned

REM Step 3: Generate Visual Studio project files
echo.
echo [4/5] Generating Visual Studio project files...
if exist "%SCRIPT_DIR%GenerateProjectFiles.bat" (
    call "%SCRIPT_DIR%GenerateProjectFiles.bat"
) else (
    call "%ENGINE_PATH%\Engine\Build\BatchFiles\GenerateProjectFiles.bat" "%SCRIPT_DIR%Aeterna.uproject"
)
if errorlevel 1 (
    echo [!] WARNING: Failed to generate project files
    echo    This may be normal if GenerateProjectFiles is not available
) else (
    echo [✓] Project files generated
)

REM Step 4: Build the game module
echo.
echo [5/5] Compiling AETERNA module...
call "%ENGINE_PATH%\Engine\Build\BatchFiles\Build.bat" Aeterna Win64 Development -Project="%SCRIPT_DIR%Aeterna.uproject"
if errorlevel 1 (
    echo [!] WARNING: Compilation completed with warnings or errors
    echo    Check the output above for details
) else (
    echo [✓] Compilation successful
)

echo.
echo ============================================================================
echo Setup Complete!
echo ============================================================================
echo.
echo Next steps:
echo   1. Open Aeterna.sln in Visual Studio 2022
echo   2. OR double-click Aeterna.uproject to open in Unreal Editor
echo   3. Run 'start.bat' to launch the editor
echo.
echo Documentation:
echo   - QUICKSTART.md      - Developer quick start guide
echo   - Build/README.md    - Build system overview
echo   - Build/BUILD_GUIDE.md - Complete build walkthrough
echo.
exit /b 0
