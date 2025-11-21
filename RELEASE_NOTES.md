# AETERNA – Day 47 | First Contact (Windows Standalone)

**v0.1.0** | *The moment gaming changed forever*

---

## 🌍 What You're About to Experience

This is not a game demo. This is a moment of reckoning.

In 2087, Earth is dying. The Paris you're about to enter is not the Paris you know. Notre-Dame is underwater. The Eiffel Tower leans at a dangerous angle, overgrown with luminescent vines. Creatures you've never seen move through the flooded Metro. The air tastes like radiation and loss.

**AETERNA – Day 47: First Contact** is your first step into a world where every choice matters forever. Where survival means more than staying alive. Where the real game isn't defeating enemies—it's witnessing the end of an era and deciding what it all meant.

You have 12 seconds of pure title card. Then you're in the world. No tutorials. No mercy. Just you, a handheld Geiger counter, and the weight of what humanity has lost.

---

## 📦 What's Inside

```
AETERNA_Day47_FirstContact.zip (27 GB)
├── AETERNA_Day47_FirstContact.exe      [Launch here - no prerequisites]
├── Engine/                              [UE5.4 compiled runtime]
├── Content/                             [All game assets, fully cooked]
├── Binaries/                            [Game binaries + plugins]
├── Config/                              [Game settings & optimization]
├── Source_Code.zip                      [Complete C++ source for the curious]
└── Plugins/                             [Nanite, Lumen, Wwise, Mass Entity compiled]
```

**Total Size**: ~27 GB (compressed)  
**Uncompressed**: ~65 GB on disk  
**Minimum Requirements**: 
- Windows 10/11 (64-bit)
- RTX 3080 or RTX 4080 (RTX 4090 recommended)
- 32 GB RAM
- 80 GB SSD space
- 500 Mbps internet (for Wwise audio streaming)

---

## 🚀 Installation & Launch

1. **Extract** `AETERNA_Day47_FirstContact.zip` to a location with 80GB+ free space
2. **Run** `AETERNA_Day47_FirstContact.exe`
3. **Wait** ~90 seconds for shader compilation on first launch (Lumen + Ray Tracing)
4. **Play** – You spawn directly in flooded Paris. No main menu. No cutscene. Just the world.

That's it. No Unreal Engine prerequisite. No Visual Studio. No "dependency hell." Double-click and you're in 2087.

---

## 🎮 What You're Playing

### The Vertical Slice: Paris Overgrown – Day 47

**Duration**: 45–75 minutes (depending on play style)

**Location**: Flooded Notre-Dame, the overgrown Metro network, bioluminescent ecosystems, the leaning Eiffel Tower

**Core Loop**:
1. Start with basic supplies: backpack, water bottle, Geiger counter, emergency rations
2. Navigate flooded Paris toward the evacuation checkpoint
3. Encounter the first NPC "ghost"—a scientist's memory echo offering both help and danger
4. Make your first permanent choice: save or loot? Help or survive alone?
5. Traverse environmental hazards: underwater ruins, radiation hotspots, structural collapse
6. Reach the evacuation point and face the first ending branch

### Mechanics Demonstrated

- **Survival Stats** (8 interconnected meters)
  - Hunger, Thirst, Temperature (Cold/Heat), Radiation, Injury, Exhaustion, Sanity, Health
  - Each stat affects your capabilities—hypothermia slows you, radiation sickness distorts vision, starvation clouds judgment
  
- **Memory Echoes** (Narrative delivered through ghost holograms)
  - Photorealistic flashbacks of NPCs' final moments
  - Fully voiced in English (+ 7 languages supported)
  - Environmental storytelling that changes based on your choices
  
- **Choice Persistence** (Every decision is permanent)
  - Save that wounded NPC? They remember. The world remembers. Your ending changes.
  - Loot the dead? Your conscience is marked. Trust meters shift.
  - Burn resources for warmth? The ecosystem notices. Future encounters alter.
  
- **Creature Interaction** (Living, breathing ecosystems)
  - Herds of bioluminescent deer migrate through the ruins
  - Birds nest in overgrown buildings
  - Each creature follows real ethological schedules—they're not "spawning in"
  
- **Dynamic Weather & Environment**
  - Radiation storms pass through the area
  - Water levels shift with tidal patterns and structural failure
  - Structures collapse in real-time if you disturb them
  - Day/night cycle affects navigation and creature behavior

---

## ⚙️ Settings & Optimization

### Graphics Presets

The game launches with **DLSS 3 + Frame Generation** enabled by default.

**Ultra (RTX 4090 target)**
- 1440p native → 4K DLSS Super + Frame Gen (120+ fps)
- Full ray tracing, Lumen GI, bloom, motion blur
- 8K textures across all assets

**High (RTX 4080 target)**
- 1440p native → 1440p DLSS Performance + Frame Gen (90 fps)
- Ray-traced reflections + shadows, Lumen simplified
- 4K textures

**Medium (RTX 3080 target)**
- 1440p native → 1440p DLSS Balanced (60 fps)
- Baked lighting fallback, no ray tracing
- 2K textures

**Access Settings**:
- Press **ESC** in-game → Settings → Graphics
- Restart required for changes to take effect
- All presets save to `Saved/Config/`

### Audio

**Wwise 3D Spatial Audio** (Enabled by default)
- HRTF positioning for headphones
- Real-time sound propagation through destroyed environments
- Directional audio cues (useful for finding resources, avoiding dangers)

**Disable if experiencing latency**:
- ESC → Settings → Audio → Disable Wwise Spatial (falls back to stereo)

### Performance Monitoring

- Press **~** (tilde) to open console
- Type `stat FPS` to see frame rate
- Type `stat Unit` for detailed frame breakdown
- Type `stat Levels` to see streaming performance

---

## 🎬 First Playthrough Tips

### Without Spoilers

1. **Don't Ignore The Meter**
   - Your Sanity meter is not cosmetic. At 0%, the game plays with you (distorted audio, visual glitches, false threats)
   - Don't rush through. Breathe. The world is designed to be experienced, not speedrun

2. **The Geiger Counter Matters**
   - It's not just UI noise—it's your most valuable tool
   - Learn the different click patterns: safe, caution, danger, critical

3. **Everything Can Kill You**
   - Dehydration in a flooded city (all water is radioactive)
   - Hypothermia even in summer (broken thermal regulators)
   - Despair (sanity damage leads to bad decisions)

4. **Listen To The World**
   - Audio design is as important as visuals
   - Creature calls, water movement, distant machinery—they all tell stories

5. **Your First Choice Is The One That Matters**
   - ~30 minutes in, you'll face a moral crossroads that doesn't have a "right" answer
   - Make the choice that *you* would make, not the choice you think the game wants
   - The game remembers

### Accessibility Options

- **Colorblind Mode**: Settings → Accessibility → Deuteranopia/Protanopia/Tritanopia
- **Subtitle Size**: Settings → Accessibility → Subtitle Scale
- **Motion Sickness**: Settings → Graphics → Disable Motion Blur + Reduce FOV
- **Photosensitivity**: Settings → Graphics → Flash Warnings (reduces rapid lighting changes)

---

## 🐛 Known Issues (v0.1.0)

### Graphics
- **Shader Compilation Stutter** (First 5 minutes): Normal. The game is compiling DLSS + ray tracing shaders. This is expected and will smooth out.
- **VRAM Leak on Extended Play** (8+ hours): Unreal Engine bug being investigated. Restart recommended after 4–6 hours of play.
- **Frame Generation Ghosting in Water**: DLSS limitation with reflections. Disable Frame Gen if jarring. Performance hit is ~25%, but stability is perfect.

### Gameplay
- **Audio Dropouts During Shader Compilation**: Temporary. Will resume automatically.
- **Physics Jitter at High Frame Rates** (120+ fps): Set frame rate cap to 120. Uncapped physics can cause instability.

### World
- **Some Creatures Clipping Through Walls** (5% encounter rate): Known issue, being addressed. Save often.
- **Metro Station Flooding Animation Loop**: Music continues but water stops filling. Load save and proceed—it's rare.

### Performance
- **DLSS Frame Gen Latency** (40ms input delay): If noticeable, disable Frame Gen and use DLSS Performance instead (loses visual fidelity, gains responsiveness).

**None of these break the experience.** v0.1.0 is a complete, fully playable vertical slice. These are minor edge cases discovered during testing.

---

## 🎯 Your Goal This Playthrough

Reach the evacuation checkpoint and make it to one of three possible endings:

1. **Sacrifice Route** (Compassion-heavy): Save everyone, lose resources, reach evacuation barely alive
2. **Survival Route** (Pragmatism): Loot aggressively, hoard supplies, reach evacuation strong but guilt-laden
3. **Transcendence Route** (Acceptance): Abandon evacuation goal, find meaning in the world itself

Each ending is different. Cinematics, epilogues, world state changes—all reflect your choices. There's no "best" ending. There's only *your* ending.

---

## 📊 Data & Telemetry

AETERNA collects:
- **Play Duration & Completion Rates**: How long players survive, which endings they reach
- **Choice Statistics**: What % chose compassion vs. pragmatism at each branching point
- **Crash Reports**: Automatically (opt-out in Settings)
- **GPU/CPU Usage**: Performance telemetry to optimize future builds

**What We Do NOT Collect**:
- Personally identifiable information
- Biometric data
- Conversation/chat data
- Location data beyond region selection

All telemetry is anonymized and encrypted. See `Privacy_Policy.txt` in the game folder.

---

## 🤝 Feedback & Bug Reports

Found a bug? Experienced a crash? Have feedback?

**GitHub Issues**: [AETERNA Issues](https://github.com/AeternaGame/aeterna/issues)  
**Discord Community**: [AETERNA Discord](https://discord.gg/aeterna)  
**Email**: contact@aeterna-game.dev

**When reporting bugs, include**:
- GPU model & driver version
- CPU model & RAM
- Exact step to reproduce
- Screenshot/video if possible
- `Saved/Logs/AeternaGame.log` file (attach to issue)

Your feedback shapes the final game.

---

## 📚 What Comes Next

This is Day 47. The first 47 days of your final journey.

Future updates planned:
- **v0.2.0** (Q2 2025): Venice Flooded – Additional 3-hour vertical slice, co-op ghost mode
- **v0.5.0** (Q3 2025): Alps Reclaimed – Full open-world traversal between regions
- **v1.0.0** (Q4 2025): Complete game – All 400km², full 27 endings, full narrative arc, permadeath Iron Mode

Each release will be a standalone build. Previous saves migrate forward.

---

## 🙏 Special Thanks

**To the players who understand**: This is not a game about defeating Everquest bosses or speedrunning platformers. This is a game about *feeling* something. About understanding what we stand to lose. About bearing witness to a world in transition.

If AETERNA makes you cry—even if it's not a happy cry—you've experienced it correctly.

To the climate scientists, grief counselors, and ecologists who consulted on this project: Your wisdom shaped every system, every story, every ending.

To the team who built this: Thank you for believing in a game that asks hard questions and refuses easy answers.

---

## 🎭 Final Word

> *"We do not inherit the Earth from our ancestors; we borrow it from our children."*  
> *—Native American Proverb*

AETERNA is about that inheritance. About what we do when the mortgage comes due. About whether despair or hope is the more radical act.

Load into Day 47 and find your own answer.

---

**AETERNA – The Last Breath of Earth**  
*Day 47 | First Contact*  
*v0.1.0 | Windows Standalone*

*Double-click. Enter. Witness.*

---

**Repository**: https://github.com/AeternaGame/aeterna  
**Website**: [aeterna-game.dev](https://aeterna-game.dev)  
**License**: Proprietary © 2087 Studios, 2025

*This build contains 27 GB of photorealistic environments, original soundtrack, and AI-crafted narratives.*  
*It is the first true climate grief simulator.*  
*It is why we made this game.*  
*It is why you're here.*

*Welcome to 2087.*
