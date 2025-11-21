# AETERNA Windows Standalone Build Guide

**Build the Day 47 Vertical Slice Yourself**

---

## Overview

This guide walks you through building `AETERNA_Day47_FirstContact.exe` from source code. The build process is fully automated and typically takes 2-4 hours depending on hardware.

---

## Requirements

### Hardware
- **CPU**: Intel i7-12700K or AMD Ryzen 7 5800X (or better)
- **RAM**: 32GB minimum (64GB recommended for parallel compilation)
- **GPU**: NVIDIA RTX 3070+ or AMD 6800 XT+ (for development)
- **Disk**: 150GB free (100GB for build cache, 50GB for project)
- **Network**: Broadband (downloading engine/assets = ~30GB)

### Software
- **Windows 10/11** (64-bit)
- **Visual Studio 2022** with C++ tools
- **Unreal Engine 5.4** (source or pre-built)
- **Git LFS** (for large asset files)
- **Python 3.10+** (optional, for tools)

---

## Step 1: Set Up Your Build Environment

### A. Install Visual Studio 2022

If you already have VS2022 installed, verify C++ tools:

1. Open **Visual Studio Installer**
2. Click **Modify** on Visual Studio 2022
3. Go to **Workloads** tab
4. Ensure **Desktop development with C++** is checked
5. Ensure these individual components are checked:
   - MSVC v143 x64/x86 build tools
   - Windows 10/11 SDK (latest)
   - CMake tools for Windows
6. Click **Modify** and wait for installation

### B. Install Unreal Engine 5.4

Option 1: **Pre-compiled Binary** (Recommended for first build)
1. Download from [Epic Games Launcher](https://www.unrealengine.com/)
2. Install UE5.4 to standard location: `C:\Program Files\Epic Games\UE_5.4`
3. Launch editor once to initialize shaders

Option 2: **From Source** (Advanced users)
```bash
# Clone from GitHub
git clone --branch 5.4 https://github.com/EpicGames/UnrealEngine.git C:\UE5.4_Source
cd C:\UE5.4_Source

# Generate project files
GenerateProjectFiles.bat

# Compile (takes 1-2 hours)
msbuild -p:Configuration=Development+Editor -p:Platform=Win64 UE5.sln
```

### C. Install Git LFS

```bash
# Install Git LFS
git lfs install

# In your project directory
git lfs pull
```

---

## Step 2: Prepare the Project

### Clone Repository

```bash
git clone https://github.com/AeternaGame/aeterna.git C:\Game\Aeterna
cd C:\Game\Aeterna

# Verify branch
git branch
# Should show: * main
#              release-win-standalone-day47-first-contact
```

### Switch to Release Branch

```bash
git checkout release-win-standalone-day47-first-contact
```

### Verify Project Structure

```bash
# Check if these files exist
if exist Aeterna.uproject echo Project file OK
if exist Source/Aeterna echo Source code OK
if exist Config/DefaultEngine.ini echo Config OK
if exist Plugins/*/Binaries echo Plugins OK
```

---

## Step 3: Generate Project Files

### Using Batch Script (Simple)

```bash
cd C:\Game\Aeterna
GenerateProjectFiles.bat
```

### Using PowerShell (Recommended)

```powershell
cd C:\Game\Aeterna
$enginePath = "C:\Program Files\Epic Games\UE_5.4"
& "$enginePath\Engine\Build\BatchFiles\GenerateProjectFiles.bat" "$pwd\Aeterna.uproject"
```

**Expected Output**:
- `Aeterna.sln` (Visual Studio solution file)
- `Intermediate/ProjectFiles/` (build configuration)

---

## Step 4: Compile the Engine Module

### Option A: Using Build Script (Automatic)

```powershell
# Run the standalone build script
cd C:\Game\Aeterna\Build\Windows
.\build_standalone.ps1 -UProjectPath "C:\Game\Aeterna\Aeterna.uproject" `
                       -EnginePath "C:\Program Files\Epic Games\UE_5.4"
```

This handles all steps automatically (compilation, packaging, output).

### Option B: Manual Compilation

```bash
cd C:\Game\Aeterna
set UE_FOLDER=C:\Program Files\Epic Games\UE_5.4

REM Compile the Aeterna module
%UE_FOLDER%\Engine\Build\BatchFiles\Build.bat Aeterna Win64 Shipping ^
  -Project="%cd%\Aeterna.uproject" ^
  -NoGold

REM Wait 30-60 minutes for compilation
```

**Expected Output**: `Binaries/Win64/UE4Editor-Aeterna.dll`

---

## Step 5: Package the Standalone Game

The most important step. This creates the final executable.

```bash
set UE_FOLDER=C:\Program Files\Epic Games\UE_5.4
set UAT=%UE_FOLDER%\Engine\Build\BatchFiles\RunUAT.bat

REM Package for shipping distribution
%UAT% BuildCookRun ^
  -Project="C:\Game\Aeterna\Aeterna.uproject" ^
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
  -Pak ^
  -ArchivePath="C:\Game\Aeterna\Build\Windows\Packaged" ^
  -CreateReleaseVersion="0.1.0" ^
  -UnattendedMode

REM This takes 30-90 minutes depending on hardware
```

### What This Does:
1. **Build**: Compiles C++ code in Shipping mode (optimized, no debug info)
2. **Cook**: Converts game assets to engine-optimized format
3. **Compressed**: Compresses assets for distribution
4. **Package**: Bundles everything into executable + supporting files
5. **Pak**: Creates `.pak` files for efficient asset streaming

### Output Location
```
C:\Game\Aeterna\Build\Windows\Packaged\
├── AeternaGame-Win64-Shipping.exe
├── AeternaGame\Binaries\Win64\
├── AeternaGame\Content\
└── AeternaGame\Plugins\
```

---

## Step 6: Create Distribution Package

Once packaging completes:

### Rename Executable

```powershell
$source = "C:\Game\Aeterna\Build\Windows\Packaged\AeternaGame-Win64-Shipping.exe"
$dest = "C:\Game\Aeterna\Build\Windows\Packaged\AETERNA_Day47_FirstContact.exe"
Copy-Item -Path $source -Destination $dest -Force
```

### Create Source Code Archive (Optional)

```powershell
$sourceDir = "C:\Game\Aeterna\Source"
$zipPath = "C:\Game\Aeterna\Build\Windows\Packaged\Source_Code.zip"
Compress-Archive -Path $sourceDir -DestinationPath $zipPath -Force
```

### Create Final Release Package

```powershell
$packDir = "C:\Game\Aeterna\Build\Windows\Packaged"
$releaseDir = "$packDir\AETERNA_Release"

# Create release structure
New-Item -ItemType Directory -Path $releaseDir -Force | Out-Null
Copy-Item "$packDir\AETERNA_Day47_FirstContact.exe" -Destination $releaseDir
Copy-Item "$packDir\Source_Code.zip" -Destination $releaseDir -ErrorAction SilentlyContinue
Copy-Item "C:\Game\Aeterna\README.md" -Destination "$releaseDir\README.txt"
Copy-Item "C:\Game\Aeterna\RELEASE_NOTES.md" -Destination "$releaseDir\RELEASE_NOTES.txt"

# Create final ZIP
Compress-Archive -Path $releaseDir -DestinationPath "$packDir\AETERNA_Day47_FirstContact.zip" -Force

Write-Host "Release package ready: $packDir\AETERNA_Day47_FirstContact.zip"
$size = '{0:N2}' -f ((Get-Item "$packDir\AETERNA_Day47_FirstContact.zip").Length / 1GB)
Write-Host "Size: $size GB"
```

---

## Step 7: Create GitHub Release

### Using GitHub CLI (Recommended)

```bash
# Install GitHub CLI if needed
# https://cli.github.com/

cd C:\Game\Aeterna
git tag -a v0.1.0 -m "AETERNA - Day 47 | First Contact (Windows Standalone)"
git push origin v0.1.0

# Create release with notes
gh release create v0.1.0 ^
  "Build/Windows/Packaged/AETERNA_Day47_FirstContact.zip" ^
  --title "AETERNA – Day 47 | First Contact (Windows Standalone)" ^
  --body-file RELEASE_NOTES.md

# Or upload manually
gh release upload v0.1.0 "Build/Windows/Packaged/AETERNA_Day47_FirstContact.zip"
```

### Using GitHub Web UI

1. Go to https://github.com/AeternaGame/aeterna
2. Click **Releases** → **Create a new release**
3. **Tag**: `v0.1.0`
4. **Title**: `AETERNA – Day 47 | First Contact (Windows Standalone)`
5. **Description**: Copy contents from `RELEASE_NOTES.md`
6. **Attach file**: Upload `AETERNA_Day47_FirstContact.zip`
7. **Publish**

---

## Troubleshooting

### Build Fails at Compilation Step

**Error**: `MSVC not found`
- **Solution**: Reinstall Visual Studio 2022 with C++ workload

**Error**: `Engine module not found`
- **Solution**: Verify UE5.4 path in build script
- Run: `"C:\Program Files\Epic Games\UE_5.4\Engine\Build\BatchFiles\Build.bat" -help`

**Error**: `Out of memory`
- **Solution**: Close other applications, increase virtual memory
- Or compile in Debug instead of Shipping first (faster, for testing)

### Build Fails at Packaging Step

**Error**: `Automation Tool crashed`
- **Solution**: 
  1. Delete `Intermediate/` and `Saved/` directories
  2. Run `GenerateProjectFiles.bat` again
  3. Restart packaging

**Error**: `Pak file too large`
- **Solution**: This is normal. Expected file size is 15-20GB uncompressed per region. The vertical slice (Paris only) should be 8-12GB.

**Error**: `DLSS plugin missing`
- **Solution**: The plugin may not have built properly. Verify in `Plugins/Nvidia/DLSS/Binaries/` exists
- If missing, download from NVIDIA directly and place in `Plugins/`

### Slow Build Process

**Too slow?** Optimize by:
- Disabling plugins you don't need in `Aeterna.uproject`
- Compiling in parallel: Add `-j8` flag to build commands
- Using incremental builds: Only rebuild changed code
- Enabling distributed compilation (requires network setup)

### Testing Locally Before Release

```bash
# Run the packaged game to verify
C:\Game\Aeterna\Build\Windows\Packaged\AETERNA_Day47_FirstContact.exe

# Check logs
C:\Game\Aeterna\Saved\Logs\AeternaGame.log

# Verify graphics settings
Launch game -> ESC -> Settings -> Graphics -> Verify DLSS + Frame Gen enabled
```

---

## Performance Optimization Tips

### For Faster Builds
1. Use **SSD** for project directory (not HDD)
2. Disable raytracing in `DefaultEngine.ini` for dev builds
3. Use **Shipping** config only for final release (Debug/Development are faster for iteration)

### For Smaller Package
1. Remove unused Content/ directories
2. Compress textures to lower resolution
3. Remove unused plugins from `.uproject`

### For Better Runtime Performance
1. Ensure DLSS is enabled in `DefaultEngine.ini`
2. Enable Frame Generation for RTX 40-series
3. Disable ray tracing reflections for slower GPUs

---

## Advanced: Automated CI/CD

For production, use GitHub Actions to automate builds:

**File**: `.github/workflows/build-standalone-windows.yml` (already included)

This workflow:
- Triggers on tag push (`git tag v0.1.0`)
- Runs build on GitHub's Windows runner
- Automatically creates GitHub Release
- Uploads exe to releases
- Sends notifications

To use:
1. Ensure repository has Actions enabled
2. Tag commit: `git tag -a v0.1.0 -m "message"`
3. Push: `git push origin v0.1.0`
4. GitHub Actions builds automatically

---

## Files Generated

After a complete build, these files are created:

```
Build/Windows/Packaged/
├── AETERNA_Day47_FirstContact.exe          [~11 GB] Final executable
├── AETERNA_Day47_FirstContact.zip          [~27 GB] Distribution package
├── AeternaGame/
│   ├── Binaries/Win64/                     [Engine + runtime]
│   ├── Content/                            [Game assets, cooked]
│   ├── Plugins/                            [Compiled plugins]
│   ├── Saved/                              [Generated files]
│   └── Config/                             [Runtime settings]
├── Source_Code.zip                         [~50 MB] Source included
└── AeternaGame-Win64-Shipping.exe          [Backup of original]
```

Total disk footprint after build: **~120 GB** (before compression)

---

## Next Steps

1. **Test locally**: Run exe, verify no crashes, check frame rates
2. **Create release tag**: `git tag v0.1.0 && git push origin v0.1.0`
3. **Upload to GitHub**: Create release and attach zip file
4. **Announce**: Tweet, Discord, email list

---

## Support

Build issues? See:
- **GitHub Issues**: https://github.com/AeternaGame/aeterna/issues
- **UE5 Build Docs**: https://docs.unrealengine.com/5.4/en-US/building-unreal-engine-from-source/
- **Discord**: https://discord.gg/aeterna

**Build succeeded?** Congratulations! You've just built a AAA-studio-quality game from source.

Welcome to development hell. It gets better.

---

*AETERNA Build Guide v0.1.0*  
*Last Updated: 2025*  
*For Windows Standalone Distribution*
