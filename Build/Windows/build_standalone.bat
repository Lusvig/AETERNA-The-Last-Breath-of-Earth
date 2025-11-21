@echo off
REM ============================================================================
REM AETERNA Windows Standalone Build Script
REM Builds AETERNA_Day47_FirstContact.exe for distribution
REM ============================================================================
REM
REM Requirements:
REM   - Unreal Engine 5.4+ installed
REM   - Visual Studio 2022 with C++ tools
REM   - ~100GB free disk space
REM
REM Usage:
REM   build_standalone.bat [UPROJECT_PATH] [ENGINE_PATH]
REM
REM Example:
REM   build_standalone.bat C:\Game\Aeterna.uproject C:\Program Files\Epic\UE5.4
REM ============================================================================

setlocal enabledelayedexpansion

REM Parse arguments or use defaults
set UPROJECT=%~1
set ENGINE_PATH=%~2

if "%UPROJECT%"=="" (
    echo ERROR: UPROJECT_PATH not specified
    echo Usage: build_standalone.bat UPROJECT_PATH [ENGINE_PATH]
    exit /b 1
)

if "%ENGINE_PATH%"=="" (
    REM Try to find UE5.4 in standard Epic location
    if exist "C:\Program Files\Epic\UE_5.4\Engine\Build\BatchFiles\Build.bat" (
        set ENGINE_PATH=C:\Program Files\Epic\UE_5.4
    ) else (
        echo ERROR: ENGINE_PATH not found and not specified
        echo Provide ENGINE_PATH as second argument
        exit /b 1
    )
)

set BUILD_SCRIPT=%ENGINE_PATH%\Engine\Build\BatchFiles\Build.bat

if not exist "%BUILD_SCRIPT%" (
    echo ERROR: Build.bat not found at %BUILD_SCRIPT%
    exit /b 1
)

set PROJECT_DIR=%~dp1
cd /d "%PROJECT_DIR%"

echo.
echo ============================================================================
echo AETERNA Windows Standalone Build
echo ============================================================================
echo Project:       %UPROJECT%
echo Engine:        %ENGINE_PATH%
echo Configuration: Shipping
echo Target:        Win64
echo.

REM Step 1: Clean build directories
echo [1/5] Cleaning previous builds...
if exist "Binaries" (
    rmdir /s /q Binaries >nul 2>&1
)
if exist "Intermediate" (
    rmdir /s /q Intermediate >nul 2>&1
)
if exist "Saved" (
    rmdir /s /q Saved >nul 2>&1
)
echo Done.

REM Step 2: Generate Visual Studio project files
echo [2/5] Generating Visual Studio project files...
if exist "GenerateProjectFiles.bat" (
    call GenerateProjectFiles.bat
) else (
    "%ENGINE_PATH%\Engine\Build\BatchFiles\GenerateProjectFiles.bat" "%UPROJECT%"
)
if errorlevel 1 (
    echo ERROR: Failed to generate project files
    exit /b 1
)
echo Done.

REM Step 3: Build the engine module
echo [3/5] Compiling Aeterna module (Shipping config)...
call "%BUILD_SCRIPT%" Aeterna Win64 Shipping -Project="%UPROJECT%" -NoGold
if errorlevel 1 (
    echo ERROR: Failed to compile game module
    exit /b 1
)
echo Done.

REM Step 4: Build the editor (required for packaging)
echo [4/5] Building Unreal Automation Tool...
call "%ENGINE_PATH%\Engine\Build\BatchFiles\Build.bat" UnrealAutomationTool Win64 Development
if errorlevel 1 (
    echo WARNING: Automation Tool build failed, continuing anyway...
)

REM Step 5: Package the game
echo [5/5] Packaging standalone game...
set AUTOMATION_TOOL=%ENGINE_PATH%\Engine\Build\BatchFiles\RunUAT.bat

REM Create Build directory for packaged output
if not exist "%PROJECT_DIR%Build" mkdir "%PROJECT_DIR%Build"

"%AUTOMATION_TOOL%" BuildCookRun ^
    -Project="%UPROJECT%" ^
    -NoP4 ^
    -NoGold ^
    -ClientConfig=Shipping ^
    -ServerConfig=Shipping ^
    -Build ^
    -Cook ^
    -Compressed ^
    -Package ^
    -TargetPlatform=Win64 ^
    -UnversionedCookedContent ^
    -CreatePhysicsAsset ^
    -Map=/Maps/VerticalSlice/Paris_Overgrown_Day47 ^
    -CreateReleaseVersion=0.1.0 ^
    -BuildMachineTarget ^
    -SkipBuildClient ^
    -UnattendedMode

if errorlevel 1 (
    echo ERROR: Packaging failed
    exit /b 1
)

echo.
echo ============================================================================
echo Build Complete!
echo ============================================================================
echo.
echo Output location: %PROJECT_DIR%Binaries\Win64\UE4Client\Aeterna\Binaries\Win64\AeternaGame-Win64-Shipping.exe
echo.
echo Next steps:
echo   1. Rename to: AETERNA_Day47_FirstContact.exe
echo   2. Create installer or ZIP package
echo   3. Upload to GitHub Releases
echo.
exit /b 0
