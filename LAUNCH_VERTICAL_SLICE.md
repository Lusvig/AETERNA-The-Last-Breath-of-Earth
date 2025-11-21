# AETERNA Vertical Slice - Launch Instructions (15 minutes)

**YOU NEED:**
- Windows 10/11 64-bit
- Unreal Engine 5.4 (source-built OR launcher version)
- Visual Studio 2022 with C++ tools installed
- ~100GB free space on SSD
- Fresh repository clone

---

## STEP-BY-STEP

### 1. Navigate to Your Project Folder
```
Open Command Prompt (Win+R → cmd)
cd C:\Path\To\Your\aeterna\folder
```

### 2. Generate Visual Studio Project Files
```
Right-click Aeterna.uproject → "Generate Visual Studio project files"
WAIT for it to complete (you'll see file explorer updates)
```
**OR** run this in Command Prompt:
```
GenerateProjectFiles.bat
```

### 3. Open in Visual Studio 2022
```
Double-click Aeterna.sln (in your project root)
VS2022 opens → Wait for it to fully load solution
```

### 4. Compile the C++ Code
```
In VS2022:
Build Menu → Build Solution
(Ctrl+Shift+B)

WAIT 5-15 minutes (depending on your PC)
Status bar shows progress at bottom of window
```
**What you're waiting for:**
- ✓ First compile is slowest
- ✓ You'll see "Build succeeded" message in Output window
- ✓ DO NOT CLOSE Visual Studio

### 5. Open the Unreal Engine Editor
```
In your project folder:
Double-click Aeterna.uproject

OR in File Explorer:
Right-click Aeterna.uproject → "Open with Unreal Engine"

Wait for the launcher to detect the project
```

### 6. Wait for Initial Shader Compilation (Critical Step)
```
Editor opens → You'll see shader compilation progress in bottom right corner

STATUS: "Compiling shaders (1234/5678)"

WAIT 30-60 minutes
- Go get coffee ☕
- Check your email
- Scroll through Reddit
- DO NOT CLOSE THE EDITOR

You know it's done when:
- Progress bar disappears
- Editor is fully responsive
- No more "compiling shaders" message
```

### 7. Verify All Plugins Loaded
```
In the Editor:
Edit Menu → Plugins

Search for and VERIFY these are ENABLED:
✓ Nanite
✓ Lumen
✓ World Partition
✓ Niagara
✓ Mass Entity
✓ Gameplay Abilities
✓ Gameplay Tags
✓ Wwise

(They should all be green/enabled by default)
```

### 8. Open the Paris Vertical Slice Level
```
In the Editor:
File Menu → Open Level

Navigate to: Maps/ParisVerticalSlice
(or similar - look for "Paris" level)

Click Open
WAIT for level to load (10-30 seconds)
```

### 9. Configure Game Mode (First Time Only)
```
In the Level (if game doesn't auto-start):

Window Menu → World Settings
Look for "GameMode Override"

If empty:
- Search "AeternaGameMode" in the dropdown
- Select it

This starts the 275-day countdown and survival systems
```

### 10. Press Play and Experience the Vertical Slice
```
In the Editor:
Press the PLAY button (top center of screen)
OR press Alt+P

YOU SHOULD SEE:
✓ Overgrown Paris with sun beams hitting Notre-Dame
✓ Bioluminescent deer or creatures in the distance
✓ Survival HUD (hunger, thirst, cold, radiation values)
✓ Your player standing in Day 47 of the apocalypse
✓ Sarah's Memory Echo notifications ready to trigger
✓ Ambient sounds of a dead world

CONTROLS:
- WASD = Move
- Mouse = Look around
- Space = Jump
- E = Interact with objects/echoes
- Esc = Pause

OPTIONAL: See the Memory Echo cinematics:
- Press E near glowing echo markers
- Watch Sarah Chen's memory unfold
```

---

## WHAT IF SOMETHING BREAKS?

### "Visual Studio won't compile code"
```
1. Delete the Intermediate/ folder (entire folder)
2. Delete the Binaries/ folder (entire folder)
3. Right-click Aeterna.uproject → Generate Visual Studio project files
4. In VS2022: Build → Clean Solution
5. Build → Build Solution
```

### "Shader compilation stuck / taking forever"
```
This is NORMAL for first launch (can be 1-2 hours)
DO NOT FORCE CLOSE
If it freezes for >2 hours:
1. Close editor gracefully
2. Delete Intermediate/Shaders folder
3. Reopen project → shaders restart
```

### "Game crashes on startup"
```
1. Check Output Log: Window → Output Log
2. Look for red error messages
3. Common fix: Delete Saved/ folder (local save data)
4. Reopen project
```

### "Plugins show as red/disabled"
```
1. Edit → Plugins
2. Re-enable them
3. Close editor
4. It will recompile
5. Reopen project
```

### "Level won't load"
```
1. File → New Level
2. Save as Maps/TestLevel
3. Place: AeternaGameMode actor
4. Place: SurvivalManager actor
5. Place: ChoiceTracker actor
6. Press Play to test basic setup
```

---

## UNREAL ENGINE VERSION DETAILS

**Required UE Version**: 5.4 (UE 5.4.0, 5.4.4, or later)

**Which UE 5.4?**
- ✓ Launcher version (from Epic Games Launcher) - EASIEST
- ✓ Source-built (from GitHub) - Fine if you already have it
- ✓ 5.4.4 specifically recommended (most stable)

**NOT Compatible**:
- ❌ UE 5.3 or earlier
- ❌ UE 5.5 (beta/experimental - may work but not supported)
- ❌ UE 4.x

**Where to get UE 5.4**:
1. Epic Games Launcher → Library → Unreal Engine
2. Click "+ Create" or install 5.4.4
3. Takes 30-60 minutes to download

---

## VISUAL STUDIO VERSION REQUIRED

**Visual Studio 2022** (Community, Professional, or Enterprise)

**Which components to install** (if you haven't already):
- ✓ Desktop development with C++
- ✓ Windows SDK (latest)
- ✓ CMake Tools for Windows
- ✓ .NET Framework targeting pack

**NOT Compatible**:
- ❌ Visual Studio 2019 (too old)
- ❌ Visual Studio Code (wrong tool)
- ❌ Visual Studio 2024 (may work but unsupported)

---

## TOTAL TIME BREAKDOWN

| Step | Time |
|------|------|
| 1-2: File generation | 1 min |
| 3-4: Visual Studio compile | 10 min |
| 5-6: Shader compilation | 45 min ⏳ |
| 7-8: Plugin check + level load | 2 min |
| 9-10: Game mode setup + Play | 1 min |
| **TOTAL** | **~60 minutes** |

**YOUR ACTIVE TIME**: ~10 minutes
**COMPUTER'S ACTIVE TIME**: ~50 minutes (you can leave it alone)

---

## SUCCESS CRITERIA

You'll know it worked when:

✅ Editor opens without crashing
✅ Shader compilation completes
✅ Level loads with no errors
✅ You can walk around overgrown Paris
✅ Survival stats visible on HUD
✅ Can interact with bioluminescent deer
✅ Memory echo system triggers
✅ Game runs at 30+ FPS

---

## NEXT STEPS AFTER RUNNING

- Explore the Paris level fully
- Trigger different Memory Echoes by walking around
- Check the survival mechanics (damage yourself, get hungry)
- Test the ending system by making different choices
- Read `QUICKSTART.md` for development tasks
- Read `Docs/Design/GDD_Complete.md` for full game vision

---

## STILL STUCK?

Check these files:
- **For errors**: Look in `Saved/Logs/Aeterna.log`
- **For help**: Read `QUICKSTART.md` (comprehensive dev guide)
- **For design context**: Read `Docs/Design/GDD_Complete.md`
- **For troubleshooting**: See Troubleshooting section above

**If Output Log shows errors**, read them carefully - they tell you exactly what broke.

---

## ENJOY

You're now in **Day 47 of the apocalypse**, standing in an overgrown Paris where nature has reclaimed humanity's masterpieces.

The story is waiting.

Welcome to AETERNA.

---

*Last Updated: 2025-01*
*Target: UE 5.4.4 + Visual Studio 2022 + Windows 10/11*
