# AETERNA Batch Scripts

This directory contains convenient batch scripts for AETERNA development and deployment.

> **Heads up:** The root-level `setup.bat`, `start.bat`, and `uninstall.bat` deliver the one-click player installer/launcher experience. Developers should continue using `setup_dev.bat` and `start_dev.bat` as documented below for engine and source workflows.

## Quick Start

### First Time Setup

```batch
setup_dev.bat
```

This initializes your development environment by:
- Finding Unreal Engine 5.4+ 
- Initializing Git LFS
- Generating Visual Studio project files
- Compiling the game module

You can optionally specify an engine path:
```batch
setup_dev.bat "C:\Program Files\Epic\UE_5.4"
```

### Running AETERNA

```batch
start_dev.bat
```

This launches the Unreal Editor with the project. You can also:

**Launch editor (default):**
```batch
start_dev.bat
start_dev.bat editor
```

**Run packaged game:**
```batch
start_dev.bat game
```

**Run specific map in editor:**
```batch
start_dev.bat map Paris_Overgrown_Day47
```

**Specify custom engine path:**
```batch
start_dev.bat editor "C:\Program Files\Epic\UE_5.4"
start_dev.bat game "C:\Program Files\Epic\UE_5.4"
start_dev.bat map Paris_Overgrown_Day47 "C:\Program Files\Epic\UE_5.4"
```

## Available Scripts

### `setup_dev.bat` - Development Environment Setup

**Purpose:** Initialize the development environment for AETERNA

**Features:**
- ✓ Auto-detects Unreal Engine 5.4+ installation
- ✓ Initializes Git LFS if available
- ✓ Cleans previous build artifacts
- ✓ Generates Visual Studio project files
- ✓ Compiles the game module (Development config)
- ✓ Validates prerequisites

**Usage:**
```batch
setup_dev.bat [ENGINE_PATH]
```

**Examples:**
```batch
setup_dev.bat
setup_dev.bat "C:\Program Files\Epic\UE_5.4"
setup_dev.bat "D:\UnrealEngine\UE_5.4"
```

**What it does:**
1. Validates that Aeterna.uproject exists
2. Searches for UE 5.4 in standard Epic locations if not specified
3. Initializes Git LFS for tracking large files
4. Cleans Intermediate, Binaries, and Saved directories
5. Generates Visual Studio project files via GenerateProjectFiles.bat
6. Compiles the Aeterna module in Development configuration

**Next steps after setup:**
- Open `Aeterna.sln` in Visual Studio 2022 for C++ development
- Or run `start_dev.bat` to open the editor
- See QUICKSTART.md for detailed developer guide

### `start_dev.bat` - Launch AETERNA

**Purpose:** Conveniently launch AETERNA in various modes

**Modes:**

| Mode | Command | Purpose |
|------|---------|---------|
| Editor | `start_dev.bat` or `start_dev.bat editor` | Launch Unreal Editor with project |
| Game | `start_dev.bat game` | Run packaged game executable |
| Map | `start_dev.bat map <name>` | Launch editor with specific map |

**Usage:**
```batch
start_dev.bat [MODE] [EXTRA_ARG] [ENGINE_PATH]
```

**Examples:**

```batch
REM Launch editor (default)
start_dev.bat

REM Launch editor explicitly
start_dev.bat editor

REM Run packaged game
start_dev.bat game

REM Launch editor with Paris vertical slice map
start_dev.bat map Paris_Overgrown_Day47

REM Specify custom engine location
start_dev.bat editor "C:\Program Files\Epic\UE_5.4"

REM Run game with custom engine
start_dev.bat game "C:\Program Files\Epic\UE_5.4"

REM Launch map with custom engine
start_dev.bat map Paris_Overgrown_Day47 "C:\Program Files\Epic\UE_5.4"
```

**Features:**
- ✓ Auto-detects Unreal Engine 5.4+ in standard locations
- ✓ Validates project file before launching
- ✓ Support for multiple launch modes
- ✓ Intelligent executable detection for game mode
- ✓ Custom engine path support

**Editor Launch:**
- Searches standard Epic locations for UE 5.4
- Launches UnrealEditor.exe with your project
- Suitable for development, content creation, and testing

**Game Launch:**
- Looks for packaged game executable in Binaries\Win64
- Requires game to be packaged first via `Build\Windows\build_standalone.bat`
- Launches in standalone/shipped mode

**Map Launch:**
- Launches editor with specific map pre-loaded
- Requires map name (without .umap extension)
- Maps should be in Content\Maps directory

## Build Scripts

For production builds, see also:
- `Build\Windows\build_standalone.bat` - Creates packaged game executable
- `Build\Windows\build_standalone.ps1` - PowerShell version of build script

## Requirements

### For setup_dev.bat:
- Unreal Engine 5.4 or newer
- Visual Studio 2022 with C++ tools
- Git with LFS support (optional, for large file tracking)
- ~100GB free disk space for builds

### For start_dev.bat:
- Unreal Engine 5.4 or newer installed
- Project must be compiled first (run `setup_dev.bat`)
- For game mode: pre-packaged executable required

## Troubleshooting

### Script won't find Unreal Engine

1. Verify UE 5.4 is installed:
   - Check `C:\Program Files\Epic\UE_5.4\Engine\Binaries\Win64\UnrealEditor.exe`
   - Or `C:\Program Files\Epic\UE_5.4.0\Engine\Binaries\Win64\UnrealEditor.exe`

2. Specify engine path explicitly:
   ```batch
   setup_dev.bat "D:\UnrealEngine\UE_5.4"
   start_dev.bat editor "D:\UnrealEngine\UE_5.4"
   ```

### setup_dev.bat fails to compile

1. Ensure Visual Studio 2022 is installed with C++ workload
2. Run `setup_dev.bat` again - compilation warnings are usually recoverable
3. Check Visual Studio build output for specific errors
4. Try running `Build\Windows\build_standalone.bat` for more verbose output

### start_dev.bat game not finding executable

1. Package the game first:
   ```batch
   Build\Windows\build_standalone.bat Aeterna.uproject "C:\Program Files\Epic\UE_5.4"
   ```

2. Wait for packaging to complete (2-4 hours)

3. Try `start_dev.bat game` again

### Map not found in editor

1. Verify map exists in `Content\Maps` directory
2. Check exact map name matches file name (case-sensitive in some cases)
3. Use full path format if needed:
   ```batch
   start_dev.bat map /Game/Maps/VerticalSlice/Paris_Overgrown_Day47
   ```

## Exit Codes

- `0` - Success
- `1` - Error (script will display error message)

## Tips

1. **Speed up setup:** If you've already compiled, run `setup_dev.bat` briefly and cancel after generation step
2. **Multiple engine versions:** Always specify ENGINE_PATH if you have multiple UE versions
3. **Development workflow:** Use `start_dev.bat` for quick editor launches during development
4. **Production builds:** Use `Build\Windows\build_standalone.bat` for shipping/packaged builds
5. **Script customization:** Feel free to edit these .bat files to match your workflow

## Documentation

- **QUICKSTART.md** - Developer quick start guide
- **Build/README.md** - Build system overview
- **Build/BUILD_GUIDE.md** - Complete build walkthrough (70+ steps)
- **README.md** - Main project documentation

## Related Commands

```batch
REM Full developer setup
setup_dev.bat
start_dev.bat

REM Package for distribution
Build\Windows\build_standalone.bat

REM Just compile without launching
Build\Windows\build_standalone.bat Aeterna.uproject "C:\Program Files\Epic\UE_5.4"
```
