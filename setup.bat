@echo off
REM ============================================================================
REM AETERNA Setup Script
REM Initial environment setup for development
REM ============================================================================
REM
REM This script handles:
REM   - Git LFS initialization and pull
REM   - Visual Studio project file generation
REM   - First-time build setup
REM
REM Requirements:
REM   - Git with LFS support
REM   - Unreal Engine 5.4+
REM   - Visual Studio 2022 with C++ tools
REM
REM ============================================================================

setlocal enabledelayedexpansion

cd /d "%~dp0"

echo.
echo ============================================================================
echo AETERNA Initial Setup
echo ============================================================================
echo.

REM Step 1: Git LFS Setup
echo [1/3] Setting up Git LFS...
git lfs install
if errorlevel 1 (
    echo WARNING: Git LFS installation failed or already installed
)

echo [1/3] Pulling Git LFS files...
git lfs pull
if errorlevel 1 (
    echo WARNING: Git LFS pull failed
    echo Please ensure you have Git LFS installed: https://git-lfs.github.com
)
echo Done.
echo.

REM Step 2: Generate Visual Studio Project Files
echo [2/3] Generating Visual Studio project files...
if not exist "GenerateProjectFiles.bat" (
    echo ERROR: GenerateProjectFiles.bat not found
    echo Make sure you're running this from the project root directory
    exit /b 1
)

call GenerateProjectFiles.bat
if errorlevel 1 (
    echo ERROR: Failed to generate project files
    exit /b 1
)
echo Done.
echo.

REM Step 3: Information
echo [3/3] Setup complete!
echo.
echo ============================================================================
echo Next Steps:
echo ============================================================================
echo.
echo Option 1: Open in Unreal Editor
echo   - Run: start.bat
echo   - Or double-click: Aeterna.uproject
echo.
echo Option 2: Compile in Visual Studio
echo   - Open: Aeterna.sln
echo   - Build Solution (Ctrl+Shift+B)
echo.
echo Option 3: Build standalone package
echo   - Run: Build\Windows\build_standalone.ps1
echo   - Or: Build\Windows\build_standalone.bat
echo.
echo For more information, see:
echo   - QUICKSTART.md (development guide)
echo   - README.md (project overview)
echo   - READY_TO_SHIP.md (build & release info)
echo.
echo ============================================================================
echo.
pause
exit /b 0
