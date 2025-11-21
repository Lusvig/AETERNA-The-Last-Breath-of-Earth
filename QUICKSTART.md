# AETERNA: Quick Start Guide

## For Developers

### Initial Setup (5 minutes)

```bash
# 1. Clone repository
git clone https://github.com/AeternaGame/aeterna.git
cd aeterna

# 2. Initialize Git LFS (if not already done)
git lfs install
git lfs pull

# 3. Generate Visual Studio project
./Aeterna/GenerateProjectFiles.bat

# 4. Open in Visual Studio 2022
# File → Open → Aeterna.sln

# 5. Compile
# Build → Build Solution (Ctrl+Shift+B)
# Wait 5-10 minutes for initial compilation
```

### First Editor Launch (20 minutes)

1. **Open Unreal Editor**
   - UE 5.4 should auto-detect `Aeterna.uproject`
   - Double-click `Aeterna.uproject` OR right-click → "Open with Unreal Engine"

2. **Initial Shader Compilation**
   - First launch compiles all shaders (~30-60 minutes)
   - Status bar shows progress
   - Go get coffee ☕

3. **Create Test Level**
   - File → New Level
   - Save as `Maps/Test_VerticalSlice`

4. **Place GameMode**
   - Place actor: Search "AeternaGameMode"
   - Place: Survival Manager, Choice Tracker, Memory Echo System

5. **Test Core Systems**
   - In Blueprint: Trigger "StartNewGame()"
   - Check output log for initialization messages

### Code Organization Cheat Sheet

```
Source/Aeterna/
├── Core/                    # Game flow & framework
├── SurvivalSystems/         # Health, hunger, radiation, etc.
├── Narrative/               # Choices, memory echoes, NPCs
├── AI/                      # Creature and NPC behavior
├── World/                   # Weather, time, ecosystems
├── Crafting/                # Crafting and inventory
├── UI/                       # HUD and menus
└── Interaction/             # Object interaction system
```

### Common Tasks

#### "I want to add a new stat to the survival system"

1. Open `SurvivalComponent.h`
2. Add new `FSurvivalStat` member variable
3. Initialize in constructor
4. Add getter/setter functions
5. Update `UpdateStats()` and `ApplyStatInteractions()`
6. Add to save game format

#### "I want to create a new Memory Echo"

1. Open `MemoryEchoSystem.cpp` (InitializeDefaultEchoes)
2. Create new `FMemoryEcho` struct
3. Set Echo ID, NPC name, title, description
4. Set duration (in seconds)
5. Point to cinematic sequence path
6. Call `RegisterEcho()`

#### "I want to test a specific ending"

1. Open `ChoiceTracker.cpp`
2. Manually set scores in `BeginPlay()`:
   ```cpp
   CompassionScore = 90.0f;       // Target ending A
   EnvironmentalScore = 70.0f;
   KillCount = 2;
   TrustRatio = 0.8f;
   ```
3. Play game, reach end game trigger
4. Check which ending calculated

#### "I need to debug stat calculations"

1. Add breakpoint in `USurvivalComponent::UpdateStats()`
2. Watch variables in debugger
3. Check Output Log (Window → Output Log)
4. Use `UE_LOG()` for print statements:
   ```cpp
   UE_LOG(LogTemp, Warning, TEXT("Hunger: %.1f"), HungerStat.CurrentValue);
   ```

### Testing Checklist

- [ ] Game initializes without crashes
- [ ] All stats update correctly per tick
- [ ] Stat cascades work (hunger + cold interaction)
- [ ] Death conditions trigger properly
- [ ] Choices are recorded
- [ ] Memory echoes play
- [ ] Ending calculation returns valid result

### Performance Profiling

```
Window → Developer Tools → Profiler

Key metrics to watch:
- Frame rate (target: 60fps)
- Garbage collection pauses (<16ms)
- Stat update overhead (<0.1ms)
- NPC AI updates (<5ms)
```

---

## For Content Creators / Level Designers

### Creating a Level

1. **File → New Level**
2. **Save Location**: `Content/World/Aeterna_World/[RegionName]/`
3. **Streaming Setup**:
   - Enable World Partition: Details → World → Enable World Partition
   - Cells load automatically based on player proximity

### Populating with NPCs

1. **Place NPC Character**:
   - Search "ANPCCharacter" in Place Actor menu
   - Set character type (Leader, Survivor, etc.)
   - Configure relationships in Details panel

2. **Set NPC Schedule**:
   - Add waypoints for daily routine
   - Set behavior tree
   - Configure dialogue options

### Creating a Memory Echo

1. **Open Sequencer**
   - Create new Cinematic Sequence
   - Save in: `Content/Cinematics/MemoryEchoes/`

2. **Film Your Echo**
   - Place actors (NPC character, environment)
   - Animate camera movements
   - Add dialogue track
   - Add VFX (Niagara emitters)

3. **Register Echo**
   - Open `MemoryEchoSystem.cpp`
   - Add echo to `InitializeDefaultEchoes()`
   - Set path to your new sequence

### Placing Resources

1. **Food Items**:
   - Canned goods: `Content/World/Props/Food/Canned_*`
   - Fresh vegetables: `Content/World/Vegetation/Edible_*`
   - Hunted game: Spawned by creature AI

2. **Environmental Hazards**:
   - Radiation zones: Paint with radiation volume
   - Cold areas: Configure weather triggers
   - Flooded areas: Set water level

---

## For Designers / Game Balance

### Adjusting Survival Difficulties

**File**: `Docs/Design/SurvivalMechanics.md`

Key values to tune:
- `DecayRate`: How fast stats worsen
- Critical thresholds: When penalties apply
- Environmental modifiers: Temperature, radiation
- Food nutrition values
- Disease progression speed

### Changing Choice Weights

**File**: `Source/Aeterna/Narrative/ChoiceTracker.h`

Adjust these to change ending balance:
```cpp
CompassionScore = Clamp(CompassionScore + (10.0f * Weight), 0.0f, 100.0f);
                                           ^^^ Adjust this multiplier
```

### Tweaking Ending Thresholds

**File**: `Source/Aeterna/Narrative/ChoiceTracker.cpp`

Edit `CheckEndingEligibility()` to adjust when endings become reachable:
```cpp
Eligibility.CompassionRequirement = 76.0f;  // Adjust thresholds
```

---

## Documentation References

| Topic | Location |
|-------|----------|
| Game Design | `Docs/Design/GDD_Complete.md` |
| Survival Mechanics | `Docs/Design/SurvivalMechanics.md` |
| Narrative Design | `Docs/Design/NarrativeDesign.md` |
| All 27 Endings | `Docs/Design/Endings.md` |
| Technical Architecture | `Docs/Technical/ArchitectureOverview.md` |
| Contributing | `CONTRIBUTING.md` |
| Changelog | `CHANGELOG.md` |

---

## Troubleshooting

### "Project won't compile"
- [ ] Have you installed Visual Studio 2022 with C++ tools?
- [ ] Is UE 5.4+ installed?
- [ ] Try: Delete `Intermediate/` folder and regenerate project

### "Shaders not compiling"
- [ ] First launch always takes 30-60 minutes
- [ ] Check shader compilation status in bottom right
- [ ] On Windows 11: Ensure Visual Studio Build Tools updated

### "Game crashes on startup"
- [ ] Check Output Log for error messages
- [ ] Ensure GameMode is placed in level
- [ ] Verify all managers spawned correctly

### "Stats not updating"
- [ ] Check SurvivalComponent is attached to player
- [ ] Verify `BeginPlay()` was called
- [ ] Check tick is enabled: `SetComponentTickEnabled(true)`

### "Memory Echoes won't play"
- [ ] Ensure cinematic path exists
- [ ] Check echo duration is reasonable (>1 second)
- [ ] Verify Sequencer movie is created and saved

---

## Performance Tips

1. **Use World Partition** for large areas (auto LOD management)
2. **Disable ticking** on components that don't need it
3. **Batch stat updates** (update every 0.1s, not every frame)
4. **Profile before optimizing** (use Unreal Profiler)
5. **Test on target hardware** (RTX 4090, 32GB RAM minimum)

---

## Discord / Support

- **#development**: General questions
- **#bugs**: Report issues
- **#design-discussion**: Gameplay feedback
- **#art**: Asset and visual questions

---

## Next Steps

1. ✅ Set up environment (see above)
2. ✅ Familiarize yourself with the codebase
3. ✅ Read relevant design documents
4. ✅ Create a test level
5. ✅ Implement your first feature
6. ✅ Submit PR

**Welcome to AETERNA Development!**

---

*Last Updated: 2025-01-15*
