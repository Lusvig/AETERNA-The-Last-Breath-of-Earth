# AETERNA v0.1.0 Deployment Checklist

**Ready to ship to GitHub Releases?** Run through this checklist before going live.

---

## Pre-Build Verification

- [ ] Branch verified: `git branch` shows `* release-win-standalone-day47-first-contact`
- [ ] Working directory clean: `git status` shows no uncommitted changes
- [ ] Latest code pulled: `git pull origin release-win-standalone-day47-first-contact`
- [ ] Git LFS initialized: `git lfs pull` completes
- [ ] Tag doesn't exist: `git tag -l | grep v0.1.0` returns empty

---

## Environment Setup

- [ ] Visual Studio 2022 installed with C++ workload
- [ ] Unreal Engine 5.4 installed at: `C:\Program Files\Epic Games\UE_5.4`
- [ ] 150GB+ free disk space verified
- [ ] 32GB+ RAM available
- [ ] Build machine rebooted (fresh start)
- [ ] No other builds running
- [ ] GitHub CLI installed (`gh --version` works)

---

## Pre-Build Configuration

- [ ] `Config/DefaultEngine.ini` has ray tracing enabled
- [ ] `Config/DefaultGame.ini` has project version: `ProjectVersion=0.1.0`
- [ ] `Aeterna.uproject` has all plugins enabled (Nanite, Lumen, Wwise, etc.)
- [ ] Default map set to: `/Maps/VerticalSlice/Paris_Overgrown_Day47`
- [ ] Game mode is `AeternaGameMode`
- [ ] No debug symbols in Shipping build (checked via `DefaultEngine.ini`)

---

## Build Execution

### Option A: Manual Build Script

```powershell
# From Build/Windows directory
cd C:\Game\Aeterna\Build\Windows
.\build_standalone.ps1 -UProjectPath "C:\Game\Aeterna\Aeterna.uproject" `
                       -EnginePath "C:\Program Files\Epic Games\UE_5.4"

# Expected duration: 2-4 hours
# Monitor with: Get-Process | Where-Object {$_.Name -like "*UE*"}
```

- [ ] Script execution started
- [ ] Logs show: `[1/5] Cleaning previous builds...`
- [ ] Logs show: `[2/5] Generating Visual Studio project files...`
- [ ] Logs show: `[3/5] Compiling Aeterna module (Shipping config)...`
- [ ] Logs show: `[4/5] Preparing output directory...`
- [ ] Logs show: `[5/5] Packaging Shipping build...`
- [ ] Build completes without errors
- [ ] Logs show: `Build Successful!`

### Option B: GitHub Actions (Automated)

```bash
git tag -a v0.1.0 -m "AETERNA – Day 47 | First Contact (Windows Standalone)"
git push origin v0.1.0

# GitHub Actions workflow starts automatically
# Check: https://github.com/AeternaGame/aeterna/actions
```

- [ ] Tag created successfully
- [ ] Pushed to remote
- [ ] GitHub Actions workflow triggered
- [ ] Build step: `Install Unreal Engine 5.4` passed
- [ ] Build step: `Build Shipping Configuration` passed
- [ ] Build step: `Package Standalone Game` passed
- [ ] Artifact uploaded
- [ ] Release created (if auto-release enabled)

---

## Post-Build Verification

### File Structure Check

```powershell
$packDir = "C:\Game\Aeterna\Build\Windows\Packaged"

# Verify files exist
$requiredFiles = @(
    "AETERNA_Day47_FirstContact.exe",
    "AeternaGame-Win64-Shipping.exe",
    "Source_Code.zip",
    "AETERNA_Day47_FirstContact.zip"
)

foreach ($file in $requiredFiles) {
    $path = Join-Path $packDir $file
    if (Test-Path $path) {
        $size = '{0:N2}' -f ((Get-Item $path).Length / 1GB)
        Write-Host "✓ $file ($size GB)" -ForegroundColor Green
    } else {
        Write-Host "✗ $file MISSING" -ForegroundColor Red
    }
}
```

- [ ] `AETERNA_Day47_FirstContact.exe` exists (~11 GB)
- [ ] `AETERNA_Day47_FirstContact.zip` exists (~27 GB)
- [ ] `Source_Code.zip` exists (~50 MB)
- [ ] `AeternaGame/` directory contains `/Binaries/`, `/Content/`, `/Plugins/`

### File Size Validation

- [ ] Exe size: 10-12 GB (sanity check)
- [ ] Zip size: 25-30 GB (compressed)
- [ ] Uncompressed size on disk: 60-70 GB

### Local Runtime Test

```bash
# Extract and test locally
cd C:\Game\Aeterna\Build\Windows\Packaged
.\AETERNA_Day47_FirstContact.exe
```

- [ ] Exe launches (shows Unreal splash screen)
- [ ] Shaders compile (~90 seconds)
- [ ] Game loads into Paris Day 47 map
- [ ] No crashes in first 2 minutes
- [ ] Audio plays correctly
- [ ] DLSS is enabled (check console: `r.ScreenPercentage`)
- [ ] Frame rates show reasonable performance (>30 fps on target GPU)
- [ ] Quit game with ESC
- [ ] Check logs: `Saved/Logs/AeternaGame.log` has no critical errors

---

## Git Operations

```bash
cd C:\Game\Aeterna

# Create annotated tag
git tag -a v0.1.0 -m "AETERNA - Day 47 | First Contact (Windows Standalone) - Ready for production"

# Verify tag
git tag -l -n1 v0.1.0
# Should show your message

# Push to remote
git push origin v0.1.0

# Verify remote has tag
git ls-remote --tags origin | grep v0.1.0
```

- [ ] Tag created locally
- [ ] Tag message is descriptive
- [ ] Tag pushed to GitHub
- [ ] Tag visible on GitHub under Releases

---

## GitHub Release Creation

### Using GitHub CLI

```bash
# Verify authentication
gh auth status

# Create release from tag
gh release create v0.1.0 `
  "C:\Game\Aeterna\Build\Windows\Packaged\AETERNA_Day47_FirstContact.zip" `
  --title "AETERNA – Day 47 | First Contact (Windows Standalone)" `
  --body-file C:\Game\Aeterna\RELEASE_NOTES.md `
  --draft=false

# Verify
gh release view v0.1.0
```

- [ ] GitHub CLI authenticated
- [ ] Release created with correct tag
- [ ] Release title matches specification
- [ ] Release notes from `RELEASE_NOTES.md` populated
- [ ] Asset uploaded and visible
- [ ] Release is **published** (not draft)

### Using GitHub Web UI

1. Go to: https://github.com/AeternaGame/aeterna/releases
2. Click **Create a new release**

- [ ] Tag: `v0.1.0`
- [ ] Title: `AETERNA – Day 47 | First Contact (Windows Standalone)`
- [ ] Description: (Paste from `RELEASE_NOTES.md`)
  - [ ] Includes download instructions
  - [ ] Includes graphics settings info
  - [ ] Includes known issues
  - [ ] Includes gameplay tips
- [ ] Uploaded files:
  - [ ] `AETERNA_Day47_FirstContact.zip` (main package)
  - [ ] `Source_Code.zip` (optional, included in main zip)
- [ ] Release **Published** (not draft)

---

## Post-Release Verification

```bash
# Verify release is public
curl -s https://api.github.com/repos/AeternaGame/aeterna/releases/tags/v0.1.0 | jq '.draft'
# Should return: false

# Verify asset download link works
curl -I https://github.com/AeternaGame/aeterna/releases/download/v0.1.0/AETERNA_Day47_FirstContact.zip
# Should return: 200 OK
```

- [ ] Release visible at: https://github.com/AeternaGame/aeterna/releases/tag/v0.1.0
- [ ] Download link active (test in browser)
- [ ] File download starts immediately
- [ ] No 404 errors
- [ ] Release listed on main releases page

---

## Communication & Announcement

- [ ] Discord server updated with download link
- [ ] Twitter/X post drafted and scheduled
- [ ] Email list notified (if applicable)
- [ ] Reddit post prepared
- [ ] Internal team notified
- [ ] Website updated with download link
- [ ] Social media announcement includes:
  - [ ] Download link
  - [ ] Key features (survival, choices, memory echoes)
  - [ ] System requirements
  - [ ] Estimated playtime (45-75 minutes)
  - [ ] Screenshot/gif of gameplay

---

## Monitoring Post-Release

### First 24 Hours

- [ ] Monitor GitHub issues for crash reports
- [ ] Check Discord for feedback
- [ ] Verify no authentication/download issues
- [ ] Track download count
- [ ] Check for common error patterns in reported issues

### Week 1

- [ ] Collect performance telemetry data
- [ ] Identify top reported bugs
- [ ] Note most common gameplay questions
- [ ] Prepare hotfix list if needed

### Documentation

- [ ] Create FAQ based on support tickets
- [ ] Document workarounds for known issues
- [ ] Update troubleshooting guide
- [ ] Archive feedback for future builds

---

## Rollback Plan (If Critical Issue Found)

If a game-breaking bug is discovered:

```bash
# Option 1: Create hotfix release v0.1.1
git checkout -b hotfix/v0.1.1 v0.1.0
# Make fixes...
git tag v0.1.1
git push origin v0.1.1

# Option 2: Deprecate release
gh release delete v0.1.0 --confirm
# Then create new release when fixed
```

- [ ] Have hotfix plan ready
- [ ] Git branch naming consistent
- [ ] Release communication strategy decided
- [ ] Support team informed of protocol

---

## Success Criteria

**Release is successful when:**

✅ Release tagged `v0.1.0`  
✅ Exe available for download on GitHub Releases  
✅ File size under 30GB ✓  
✅ Local testing completed without crashes  
✅ DLSS + Frame Gen enabled and working  
✅ Straight into gameplay (no splash screens)  
✅ Release notes reflect scope  
✅ Source code included  
✅ Download functional and fast  
✅ Community engagement positive  

---

## Sign-Off

- [ ] Tech Lead: `________________` Date: `________`
- [ ] QA Lead: `________________` Date: `________`
- [ ] Release Manager: `________________` Date: `________`

---

**Once all boxes are checked: AETERNA Day 47 is live to the world.**

*Double-click. Enter. Witness.*

---

Generated: 2025  
For: AETERNA v0.1.0 Windows Standalone Release
