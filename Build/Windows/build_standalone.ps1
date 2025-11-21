#requires -version 5.0
<#
.SYNOPSIS
    AETERNA Windows Standalone Build Script
    Builds AETERNA_Day47_FirstContact.exe for distribution

.DESCRIPTION
    Compiles and packages the AETERNA game for Windows Shipping distribution.
    Handles all build steps from project file generation to final packaging.

.PARAMETER UProjectPath
    Full path to Aeterna.uproject

.PARAMETER EnginePath
    Full path to Unreal Engine 5.4+ installation
    If not specified, searches standard Epic Games locations

.PARAMETER OutputDir
    Output directory for packaged game (default: ./Build/Windows/Packaged)

.EXAMPLE
    .\build_standalone.ps1 -UProjectPath "C:\Game\Aeterna.uproject" -EnginePath "C:\Program Files\Epic\UE_5.4"

.NOTES
    Requirements:
    - Unreal Engine 5.4+
    - Visual Studio 2022 with C++ tools
    - ~100GB free disk space
    - Administrator privileges may be required
#>

param(
    [Parameter(Mandatory=$true)]
    [string]$UProjectPath,
    
    [Parameter(Mandatory=$false)]
    [string]$EnginePath,
    
    [Parameter(Mandatory=$false)]
    [string]$OutputDir
)

# Enable strict error handling
$ErrorActionPreference = "Stop"

function Write-BuildStep {
    param([string]$Message, [int]$Step, [int]$Total)
    Write-Host ""
    Write-Host "[$Step/$Total] $Message" -ForegroundColor Cyan
    Write-Host ""
}

function Test-Prerequisites {
    Write-Host "Checking prerequisites..." -ForegroundColor Yellow
    
    # Check if uproject exists
    if (-not (Test-Path $UProjectPath)) {
        throw "Aeterna.uproject not found at: $UProjectPath"
    }
    Write-Host "✓ Aeterna.uproject found" -ForegroundColor Green
    
    # Find Engine if not specified
    if ([string]::IsNullOrEmpty($EnginePath)) {
        Write-Host "Searching for Unreal Engine 5.4..." -ForegroundColor Yellow
        
        $possiblePaths = @(
            "C:\Program Files\Epic\UE_5.4",
            "C:\Program Files\Epic Games\UE_5.4",
            "D:\Program Files\Epic\UE_5.4",
            "D:\Program Files\Epic Games\UE_5.4"
        )
        
        $found = $false
        foreach ($path in $possiblePaths) {
            if (Test-Path "$path\Engine\Build\BatchFiles\Build.bat") {
                $EnginePath = $path
                $found = $true
                break
            }
        }
        
        if (-not $found) {
            throw "Unreal Engine 5.4 not found. Please specify -EnginePath parameter."
        }
    }
    
    # Verify Engine path
    $buildBat = "$EnginePath\Engine\Build\BatchFiles\Build.bat"
    if (-not (Test-Path $buildBat)) {
        throw "Engine Build.bat not found at: $buildBat"
    }
    Write-Host "✓ Unreal Engine 5.4 found at $EnginePath" -ForegroundColor Green
    
    # Set output directory
    if ([string]::IsNullOrEmpty($OutputDir)) {
        $OutputDir = Join-Path (Split-Path $UProjectPath) "Build\Windows\Packaged"
    }
    Write-Host "✓ Output directory: $OutputDir" -ForegroundColor Green
    
    return @{
        UProjectPath = $UProjectPath
        EnginePath = $EnginePath
        OutputDir = $OutputDir
        BuildBat = $buildBat
    }
}

function Invoke-Build {
    param($Config)
    
    $projectDir = Split-Path $Config.UProjectPath -Parent
    Push-Location $projectDir
    
    try {
        Write-Host ""
        Write-Host "========================================================================" -ForegroundColor Magenta
        Write-Host "AETERNA Windows Standalone Build" -ForegroundColor Magenta
        Write-Host "========================================================================" -ForegroundColor Magenta
        Write-Host "Project:       $($Config.UProjectPath)"
        Write-Host "Engine:        $($Config.EnginePath)"
        Write-Host "Configuration: Shipping"
        Write-Host "Target:        Win64"
        Write-Host "Output:        $($Config.OutputDir)"
        Write-Host ""
        
        # Step 1: Clean
        Write-BuildStep "Cleaning previous builds" 1 5
        $cleanDirs = @("Binaries", "Intermediate", "Saved")
        foreach ($dir in $cleanDirs) {
            $path = Join-Path $projectDir $dir
            if (Test-Path $path) {
                Remove-Item -Path $path -Recurse -Force | Out-Null
                Write-Host "  Removed: $dir" -ForegroundColor Gray
            }
        }
        
        # Step 2: Generate project files
        Write-BuildStep "Generating Visual Studio project files" 2 5
        $genScript = Join-Path $projectDir "GenerateProjectFiles.bat"
        if (Test-Path $genScript) {
            & $genScript
        } else {
            & "$($Config.EnginePath)\Engine\Build\BatchFiles\GenerateProjectFiles.bat" $Config.UProjectPath
        }
        if ($LASTEXITCODE -ne 0) {
            throw "Failed to generate project files"
        }
        Write-Host "✓ Project files generated" -ForegroundColor Green
        
        # Step 3: Compile game module
        Write-BuildStep "Compiling Aeterna module (Shipping)" 3 5
        & $Config.BuildBat Aeterna Win64 Shipping -Project="$($Config.UProjectPath)" -NoGold
        if ($LASTEXITCODE -ne 0) {
            throw "Failed to compile game module"
        }
        Write-Host "✓ Compilation complete" -ForegroundColor Green
        
        # Step 4: Create output directory
        Write-BuildStep "Preparing output directory" 4 5
        if (-not (Test-Path $Config.OutputDir)) {
            New-Item -ItemType Directory -Path $Config.OutputDir -Force | Out-Null
        }
        Write-Host "✓ Output directory ready" -ForegroundColor Green
        
        # Step 5: Package game
        Write-BuildStep "Packaging Shipping build (this may take 15-30 minutes)" 5 5
        $runUAT = "$($Config.EnginePath)\Engine\Build\BatchFiles\RunUAT.bat"
        
        & $runUAT BuildCookRun `
            -Project="$($Config.UProjectPath)" `
            -NoP4 `
            -NoGold `
            -ClientConfig=Shipping `
            -ServerConfig=Shipping `
            -Build `
            -Cook `
            -Compressed `
            -Package `
            -TargetPlatform=Win64 `
            -UnversionedCookedContent `
            -CreatePhysicsAsset `
            -Pak `
            -ArchivePath="$($Config.OutputDir)" `
            -CreateReleaseVersion="0.1.0" `
            -UnattendedMode
        
        if ($LASTEXITCODE -ne 0) {
            throw "Packaging failed"
        }
        Write-Host "✓ Packaging complete" -ForegroundColor Green
        
    } finally {
        Pop-Location
    }
}

function Invoke-PostBuild {
    param($Config)
    
    Write-Host ""
    Write-Host "========================================================================" -ForegroundColor Green
    Write-Host "Build Successful!" -ForegroundColor Green
    Write-Host "========================================================================" -ForegroundColor Green
    Write-Host ""
    Write-Host "Package location: $($Config.OutputDir)" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Next steps:" -ForegroundColor Yellow
    Write-Host "  1. Locate the .exe in the output directory"
    Write-Host "  2. Rename to: AETERNA_Day47_FirstContact.exe"
    Write-Host "  3. Create a ZIP package with the executable and supporting files"
    Write-Host "  4. Create a GitHub Release v0.1.0"
    Write-Host "  5. Upload the ZIP to the release"
    Write-Host ""
}

# Main execution
try {
    Write-Host ""
    $config = Test-Prerequisites
    Invoke-Build $config
    Invoke-PostBuild $config
} catch {
    Write-Host ""
    Write-Host "ERROR: $_" -ForegroundColor Red
    Write-Host ""
    exit 1
}

exit 0
