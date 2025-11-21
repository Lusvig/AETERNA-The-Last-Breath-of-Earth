# AETERNA Build System

**Production-ready build pipeline for AETERNA Day 47 Vertical Slice**

---

## Quick Start

**TL;DR**: Want to build and ship right now?

```powershell
# Windows PowerShell
cd Build\Windows
.\build_standalone.ps1 -UProjectPath "C:\Full\Path\To\Aeterna.uproject" `
                       -EnginePath "C:\Program Files\Epic Games\UE_5.4"

# This builds everything and packages it ready for GitHub Releases
# Time: 2-4 hours
# Output: Build/Windows/Packaged/AETERNA_Day47_FirstContact.zip
```

Or use **GitHub Actions** (automatic):
```bash
git tag v0.1.0 && git push origin v0.1.0
# Build starts automatically → release created automatically
```

---

## Directory Structure

```
Build/
├── README.md                                [This file]
├── BUILD_GUIDE.md                           [Comprehensive build walkthrough]
├── DEPLOYMENT_CHECKLIST.md                  [Pre-release verification checklist]
│
├── Windows/
│   ├── build_standalone.bat                 [Batch script for automation]
│   ├── build_standalone.ps1                 [PowerShell version (recommended)]
│   └── Packaged/                            [Output directory - created after build]
│       ├── AETERNA_Day47_FirstContact.exe   [Final executable]
│       ├── AETERNA_Day47_FirstContact.zip   [Distribution package]
│       ├── Source_Code.zip                  [Source code archive]
│       └── AeternaGame/                     [Engine runtime + assets]
│
└── Scripts/
    └── (Optional) Platform-specific scripts
```

---

## Three Ways to Build

### 1️⃣ Automatic Script (Easiest)

**Use this if**: You want one-click builds with minimal setup

```powershell
cd Build\Windows
.\build_standalone.ps1 -UProjectPath "C:\path\to\Aeterna.uproject"
```

**What it does**:
- Cleans old builds
- Generates project files
- Compiles game module
- Packages standalone exe
- Creates distribution zip
- Outputs ready for GitHub

**Time**: 2-4 hours  
**Complexity**: None - fully automated

---

### 2️⃣ GitHub Actions CI/CD (Most Professional)

**Use this if**: You want automated builds on every tag push

**Setup** (one-time):
1. Ensure `.github/workflows/build-standalone-windows.yml` exists ✓ (already included)
2. Enable Actions in GitHub repository settings

**Usage**:
```bash
git tag v0.1.0 && git push origin v0.1.0
# Workflow starts automatically on GitHub servers
# Check: https://github.com/AeternaGame/aeterna/actions
```

**What it does**:
- Runs on GitHub-hosted Windows runner
- Automatic compilation and packaging
- Creates GitHub Release automatically
- Attaches exe to release
- No local build time needed

**Time**: 3-4 hours (on GitHub servers)  
**Complexity**: Minimal - just push a tag  
**Cost**: Free for public repositories

---

### 3️⃣ Manual Compilation (Full Control)

**Use this if**: You want to understand every step or troubleshoot

See `BUILD_GUIDE.md` for complete step-by-step instructions.

**Time**: 2-4 hours  
**Complexity**: High - requires manual intervention  
**Best for**: Development, troubleshooting, custom builds

---

## Pre-Build Checklist

Before starting any build:

- [ ] Unreal Engine 5.4 installed
- [ ] Visual Studio 2022 with C++ tools
- [ ] 150GB free disk space
- [ ] 32GB+ RAM
- [ ] On branch: `release-win-standalone-day47-first-contact`
- [ ] All changes committed: `git status` shows clean
- [ ] Git LFS pulled: `git lfs pull`

---

## Build Outputs

### After successful build:

```
Build/Windows/Packaged/
│
├── AETERNA_Day47_FirstContact.exe          [11 GB]
│   └── Ready to run - no dependencies
│
├── AETERNA_Day47_FirstContact.zip          [27 GB]
│   └── Ready to upload to GitHub Releases
│
├── Source_Code.zip                         [50 MB]
│   └── Complete C++ source included
│
└── AeternaGame/                            [70 GB uncompressed]
    ├── Binaries/Win64/
    ├── Content/
    ├── Plugins/
    ├── Saved/
    └── Config/
```

### Total Disk Usage: ~120 GB (before zip compression)

---

## Deployment

Once build completes:

### Option A: Manual Upload

```bash
# GitHub CLI (recommended)
gh release create v0.1.0 Build/Windows/Packaged/AETERNA_Day47_FirstContact.zip \
  --title "AETERNA – Day 47 | First Contact" \
  --body-file ../RELEASE_NOTES.md

# Or upload via web UI:
# 1. Go to https://github.com/AeternaGame/aeterna/releases
# 2. Create new release
# 3. Attach AETERNA_Day47_FirstContact.zip
```

### Option B: GitHub Actions (Automatic)

Release created automatically when workflow completes.

---

## Configuration

### Default Build Settings

**Game Map**: `/Maps/VerticalSlice/Paris_Overgrown_Day47`  
**Configuration**: `Shipping` (optimized, no debug)  
**Target Platform**: `Win64`  
**Graphics**: DLSS 3 + Frame Gen enabled  
**Package Size**: ~27 GB (compressed)

### Customization

Edit `Build/Windows/build_standalone.ps1` to modify:

```powershell
# Change default map (line ~120)
-Map=/Your/Custom/Map `

# Change compression level (line ~110)
-Compress=1  # 0=none, 1=default, 2=maximum

# Change output name (line ~50)
$GAME_NAME = "YourCustomName.exe"
```

---

## Troubleshooting

### Build fails during compilation

**Error**: `MSVC compiler not found`
- Solution: Reinstall Visual Studio 2022 with C++ workload

**Error**: `Unreal Engine not found`
- Solution: Update `-EnginePath` parameter to correct UE5.4 location

**Error**: `Out of disk space`
- Solution: Free up 150GB, or clear build cache: `Remove-Item Intermediate -Recurse`

### Build fails during packaging

**Error**: `Automation Tool crashed`
- Solution: Delete `Intermediate/`, `Saved/`, regenerate project files

**Error**: `Package too large`
- Solution: Normal - vertical slice is expected to be 25-30GB

### Runtime issues

**Error**: `Game won't start after packaging`
- Solution: Check `Saved/Logs/AeternaGame.log` for errors

**Error**: `DLSS not working`
- Solution: Verify RTX GPU, update drivers, re-enable DLSS in settings

---

## Performance Optimization

### Faster Builds

- Use SSD (not HDD) for project directory
- Disable ray tracing in config for dev builds
- Use parallel compilation: Add `-j8` to build command
- Use incremental builds for iteration

### Smaller Package

- Remove unused Content/ directories
- Compress textures to lower resolution
- Disable unused plugins in `.uproject`

### Better Runtime

- Enable DLSS + Frame Gen ✓ (default)
- Disable ray tracing on lower-end GPUs
- Set frame rate cap to 120 for stability

---

## Advanced: Custom Builds

### Build for different configurations

**Debug** (for testing, slow):
```powershell
$config = "Debug"
```

**Development** (faster than Shipping, still slow):
```powershell
$config = "Development"
```

**Custom Map**:
```powershell
-Map=/Your/Map/Name `
```

### Build for other platforms (future)

```powershell
# PS5 build (when supported)
-TargetPlatform=PS5 `

# Xbox build (when supported)
-TargetPlatform=XSX `

# Mac build
-TargetPlatform=Mac `
```

---

## Monitoring & Logging

### During build

**PowerShell**: Watch real-time output as script runs

**Logs location**: `Intermediate/Build/Logs/`

**Check build progress**:
```powershell
# Monitor process
Get-Process | Where-Object {$_.Name -like "*UE*" -or $_.Name -like "*cl.exe"}

# Check disk usage
Get-Volume
```

### After build

**Engine logs**: `Saved/Logs/AeternaGame.log`

**Check runtime performance**:
```bash
# Launch game and open console (~)
stat FPS       # Show frame rate
stat Unit      # Frame time breakdown
stat Levels    # Streaming performance
```

---

## Support & Resources

**Build failing?** Check:
1. `BUILD_GUIDE.md` - Detailed step-by-step
2. GitHub Issues - Search for your error
3. Unreal Engine docs - https://docs.unrealengine.com/

**Need help?**
- Discord: https://discord.gg/aeterna
- Email: contact@aeterna-game.dev
- GitHub Issues: https://github.com/AeternaGame/aeterna/issues

---

## Next Steps

### After build completes:

1. **Test locally** - Run the .exe, verify no crashes
2. **Create tag** - `git tag v0.1.0`
3. **Push tag** - `git push origin v0.1.0` (triggers GitHub Actions if available)
4. **Create release** - Upload zip to GitHub Releases
5. **Announce** - Tweet, Discord, email community

---

## Quick Reference

| Task | Command | Time |
|------|---------|------|
| Build all | `.\build_standalone.ps1` | 2-4h |
| Generate project files | `GenerateProjectFiles.bat` | 1-2m |
| Compile only | `Build.bat Aeterna Win64 Shipping` | 30-60m |
| Package only | `RunUAT.bat BuildCookRun ...` | 30-90m |
| Create release | `gh release create v0.1.0 ...` | 2m |
| Upload artifact | GitHub web UI or CLI | 5-10m |

---

## Files in This Directory

| File | Purpose |
|------|---------|
| `README.md` | This file - Overview |
| `BUILD_GUIDE.md` | Complete build walkthrough (70+ steps) |
| `DEPLOYMENT_CHECKLIST.md` | Pre-release verification (80+ checkpoints) |
| `Windows/build_standalone.bat` | Batch script (legacy) |
| `Windows/build_standalone.ps1` | PowerShell script (recommended) |
| `Windows/Packaged/` | Output directory (created after build) |

---

## Version History

- **v0.1.0** (2025) - Initial Windows Standalone release
  - Paris Overgrown - Day 47 vertical slice
  - 27GB packaged size
  - DLSS 3 + Frame Gen enabled
  - Direct-to-gameplay launch

---

## Final Word

This build system is designed to be:
- **Automated** - Minimal manual intervention
- **Reliable** - Tested on production hardware
- **Scalable** - Ready for full game builds (400km²)
- **Professional** - GitHub Actions integration
- **Transparent** - Full logging and documentation

**One command. Two hours. One release.**

That's the goal.

---

*AETERNA Build System v0.1.0*  
*For Windows Standalone Distribution*  
*Last Updated: 2025*
