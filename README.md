# AETERNA: The Last Breath of Earth

> **A game that will make you feel the weight of what we've lost—and what we still have time to save.**

## Vision Statement

In 2087, Earth is in its final decade. Climate collapse, mass extinction, and societal breakdown have transformed our world into a hauntingly beautiful wasteland of overgrown megacities, flooded coastlines, radioactive exclusion zones, and vast wilderness reclaiming everything humanity built.

You are not a hero. You are not chosen. You are one of the last 1,000 humans alive—just a regular person trying to reach the final evacuation ark in Antarctica before the final methane burst makes the atmosphere unbreathable in 9 months.

**AETERNA** is the first true climate grief simulator. It is not a game about winning. It is a game about *witnessing*. About the terrifying beauty of a dying world. About every choice you make—who you save, what you burn, what you preserve—permanently altering reality itself.

When critics play this game, they will weep. Not for their character, but for our world.

---

## Key Features

### 1. **Photorealistic 400km² Open World**
- **Former Europe**: Paris's flooded Notre-Dame with bioluminescent ecosystems, Venice as an archipelago of ruins, the Alps reclaimed by wilderness, Chernobyl reimagined as a radioactive garden, Scandinavian tundra frozen and silent.
- **World Partition Technology**: Seamless streaming, zero load times, 8K textures throughout.
- **Full Dynamic Seasons**: Summer floods become winter permafrost. Radiation storms pass through. Ecosystems migrate and transform.

### 2. **Uncompromising Survival Systems**
- **Physiological Depth**: Hunger, thirst, radiation sickness, psychological trauma, micro-nutrient deficiencies, hypothermia, sepsis, PTSD hallucinations—each stat interconnected.
- **Real Medical Conditions**: Contract diseases. Infections spread. Without proper treatment, you die a slow, horrible death.
- **Breathing, Sweating, Suffering**: Every NPC's skin pores open and close, sweat pools in stress, muscles tense. They are *alive*.

### 3. **Legacy System: 27 Endings, None Happy**
Every choice is permanent:
- **Kill for supplies** or **help strangers**? The world remembers both.
- **Burn the forest for warmth** or **preserve the last ecosystem**? The game changes.
- **Racial reconciliation ending**, **extinction acceptance ending**, **transhumanist transcendence ending**, **solitary enlightenment ending**—each shaped by 100+ variables tracking your moral geography.

No save-scumming. No "good" or "bad"—just *human* choices with inhuman consequences.

### 4. **Memory Echoes: Narrative Through Ghosts**
- Meet NPCs who are already dead when you find them.
- Photorealistic holographic flashbacks of their final moments, fully voiced in 8 languages, emotionally devastating.
- Their stories are woven into YOUR story. You are inheriting their unfinished business.

### 5. **Co-op Ghost Mode**
- Your friends can visit your world as *echoes of people you once knew*.
- They leave supplies, messages, warnings, love notes.
- Their ghost world and yours gradually diverge—creating unique, shared grief-spaces.

### 6. **Iron Mode Permadeath**
- **Actually meaningful**. Lose 40 hours of progress? Your base, your supplies, your story—*gone*.
- Every permadeath changes the world state. Your abandoned supplies become someone else's lifeline.
- The game keeps a memorial of every character you've lost.

### 7. **Living Ecosystems**
- Animals migrate seasonally. They have AI schedules—grazing, nesting, hunting, dying.
- Plants grow and wither in real-time. Forests expand or burn. Weather affects everything.
- You can't just "kill all deer for meat"—the ecosystem collapses, and you starve.

---

## Technical Specifications

| Aspect | Specification |
|--------|--------------|
| **Engine** | Unreal Engine 5.4+ |
| **Target Platform** | PC/Next-Gen (8K, ray-traced, 4090+) |
| **Resolution** | 1440p to 4K, DLSS 3.7 / FSR 3 / XeSS |
| **Framerate** | 60fps (Quality) / 120fps (Performance) |
| **World Size** | 400 km² (hand-crafted + procedural enhancement) |
| **Texture Fidelity** | 8K PBR, real-world scan sourcing (Quixel Megascans) |
| **Rendering** | Full ray-traced, Nanite virtualized geometry, Lumen GI |
| **Physics** | Chaos Destruction, real-time structural integrity |
| **NPCs** | 1000+ simultaneously, Mass Entity framework, MetaHuman |
| **Audio** | 3D HRTF spatial, Wwise, real-time propagation |
| **LOD System** | Aggressive multi-level distance-based streaming |

---

## Architecture

### Engine Subsystems

**Core Gameplay Framework**
- State machines for survival mechanics
- Event-driven architecture for narrative triggers
- Performance-optimized tick systems

**Survival Systems**
- Modular stat system (hunger, thirst, radiation, temperature, sanity, health)
- Resource consumption based on activity level, environment, and equipment
- Realistic medical progression (infection → sepsis → death)

**Narrative Engine**
- Choice persistence and world-state tracking
- Memory Echo playback system with photogrammetry-based reconstruction
- Dialogue system supporting 8 languages with real-time HRTF positioning

**AI & Creatures**
- Mass Entity framework for 1000+ NPCs with behavior trees
- Dynamic scheduling and routing based on world state
- Creature AI with seasonal migration, hunting, nesting

**Legacy System**
- Global state manager tracking 500+ world variables
- Ending calculation engine evaluating player choices against 27 possible conclusions
- Memorialization and permadeath tracking system

---

## Development Stack

```
Engine:              Unreal Engine 5.4
Language (Gameplay): C++ (core) + Blueprint (prototyping)
Language (Tools):    Python 3.10+
Audio Middleware:    Wwise 2024
AI Framework:        Mass Entity + Behavior Trees
Physics:             Chaos Engine
VFX:                 Niagara
Materials:           Substrate (next-gen)
Cinematics:          Sequencer
Source Control:      Git (GitHub)
CI/CD:               GitHub Actions
Documentation:       Markdown (Design Docs)
```

---

## Project Structure

```
aeterna-game/
├── .github/
│   └── workflows/
│       ├── build.yml
│       ├── validation.yml
│       └── documentation.yml
├── Config/
│   ├── DefaultEngine.ini
│   ├── DefaultGame.ini
│   ├── Scalability/
│   └── Platform/
├── Content/
│   ├── Characters/
│   │   ├── MetaHumans/
│   │   ├── Creatures/
│   │   └── NPCs/
│   ├── World/
│   │   ├── Aeterna_World/          # World Partition streaming regions
│   │   │   ├── Paris/
│   │   │   ├── Venice/
│   │   │   ├── Alps/
│   │   │   ├── Chernobyl/
│   │   │   └── Scandinavia/
│   │   ├── Vegetation/
│   │   ├── Props/
│   │   └── Architecture/
│   ├── Cinematics/
│   │   ├── MemoryEchoes/
│   │   ├── Sequences/
│   │   └── Cutscenes/
│   ├── Audio/
│   │   ├── Dialogue/
│   │   ├── Ambient/
│   │   ├── SFX/
│   │   └── Music/
│   ├── Materials/
│   │   ├── Substrate/
│   │   ├── Environments/
│   │   └── Characters/
│   └── VFX/
│       ├── Niagara/
│       ├── Particles/
│       └── Atmospheric/
├── Plugins/
│   ├── AdvancedLocomotionSystem/
│   └── CustomSurvivalTools/
├── Source/
│   └── Aeterna/
│       ├── Core/
│       │   ├── AeternaGameMode.h/cpp
│       │   ├── AeternaPlayerController.h/cpp
│       │   ├── AeternaCharacter.h/cpp
│       │   └── GameState/
│       ├── SurvivalSystems/
│       │   ├── Health/
│       │   ├── Hunger/
│       │   ├── Radiation/
│       │   ├── Temperature/
│       │   ├── Sanity/
│       │   └── SurvivalManager.h/cpp
│       ├── Narrative/
│       │   ├── MemoryEchoSystem.h/cpp
│       │   ├── DialogueSystem.h/cpp
│       │   ├── LegacySystem.h/cpp
│       │   └── ChoiceTracker.h/cpp
│       ├── AI/
│       │   ├── Creatures/
│       │   ├── NPCs/
│       │   └── MassEntity/
│       ├── World/
│       │   ├── Weather/
│       │   ├── Ecosystem/
│       │   └── TimeOfDay/
│       ├── Crafting/
│       │   ├── CraftingSystem.h/cpp
│       │   ├── RecipeDatabase.h/cpp
│       │   └── InventorySystem.h/cpp
│       ├── Interaction/
│       │   ├── InteractionSystem.h/cpp
│       │   └── ObjectInteraction.h/cpp
│       └── UI/
│           ├── HUD/
│           ├── Menus/
│           └── WorldUI/
├── Docs/
│   ├── Design/
│   │   ├── GDD_Complete.md
│   │   ├── NarrativeDesign.md
│   │   ├── SurvivalMechanics.md
│   │   ├── AIFramework.md
│   │   ├── LegacySystem.md
│   │   └── Endings.md
│   ├── Art/
│   │   ├── ArtBible.md
│   │   ├── CharacterGuidelines.md
│   │   └── EnvironmentPalette.md
│   ├── Audio/
│   │   ├── AudioBible.md
│   │   └── DialogueProtocol.md
│   ├── Technical/
│   │   ├── ArchitectureOverview.md
│   │   ├── PerformanceGuidelines.md
│   │   └── NetworkingProtocol.md
│   └── API/
│       └── CodeDocumentation.md
├── Tools/
│   ├── ProceduralGeneration/
│   │   ├── WorldGenerator.py
│   │   └── BiomeGenerator.py
│   ├── AssetPipeline/
│   │   ├── QuixelMegascansPipeline.py
│   │   └── TextureProcessor.py
│   └── DataGeneration/
│       ├── NPCGenerator.py
│       └── DialogueGenerator.py
├── Build/
│   ├── Scripts/
│   └── Containers/
├── CHANGELOG.md
├── CODE_OF_CONDUCT.md
├── CONTRIBUTING.md
├── LICENSE
└── Aeterna.uproject
```

---

## Getting Started

### Prerequisites
- **Unreal Engine 5.4** or higher
- **Visual Studio 2022** (C++ development tools)
- **Git LFS** for large asset files
- **Python 3.10+** for tools pipeline
- **16GB RAM minimum** (32GB recommended for editor)
- **NVIDIA RTX 4090** or equivalent for optimal visual fidelity

### Installation

```bash
# Clone the repository
git clone https://github.com/AeternaGame/aeterna.git
cd aeterna

# Initialize Git LFS
git lfs install
git lfs pull

# Generate Visual Studio project
./Aeterna/GenerateProjectFiles.bat

# Open in Unreal Editor
# UE5.4 should auto-detect the .uproject file
```

### First Run

1. Open `Aeterna.uproject` with Unreal Engine 5.4
2. Wait for shader compilation (30–60 minutes on first load)
3. Navigate to `Maps/VerticalSlice/Paris_Overgrown_Day47`
4. Press Play

---

## Vertical Slice: "Paris Overgrown – Day 47"

The first fully playable slice demonstrates all core mechanics:

- **Location**: Flooded Notre-Dame, bioluminescent ecosystem, vine-covered Eiffel Tower (leaning dangerously)
- **Duration**: 45–60 minutes to reach evacuation zone
- **Mechanics Demonstrated**:
  - Survival stat management (hunger, radiation, temperature)
  - Creature interaction (herds of bioluminescent deer)
  - Environmental hazards (flooded basements, unstable structures, radiation hotspots)
  - NPC encounters with Memory Echoes
  - Crafting and resource management
  - Choice consequences (save or loot an injured NPC)

**How to Play**:
1. Start with basic supplies and a handheld Geiger counter
2. Navigate the flooded Metro toward the Seine
3. Encounter the first NPC "ghost" – a scientist who can help or harm you
4. Reach the Evacuation Point and choose your ending path

---

## Design Philosophy

### Emotional Authenticity
Every system serves the narrative: survival systems are not "game mechanics"—they are *grief*. When you're cold, hungry, and alone in a dead world, you understand loss.

### Photorealism Over Fantasy
All visuals are grounded in real-world photography. Every building was a real place. Every creature behavior is based on actual ethology research. When you play AETERNA, you are exploring Earth as it could be—not as fantasy, but as *possible*.

### Choice Permanence
No save-scumming. No "perfect" endings. Every decision leaves marks. The game remembers. The world changes. You cannot undo your choices—and that is the point.

### Accessible Difficulty
- **Story Mode**: Focused on narrative, reduced survival pressure
- **Standard Mode**: Full survival mechanics (recommended)
- **Iron Mode**: Permadeath (for the brave)
- **Hardcore Simulation**: Realistic damage, disease progression, psychological trauma (for the insane)

---

## The 27 Endings

AETERNA tracks 500+ variables across your playthrough and evaluates them against 27 possible conclusions:

1. **Sacrificial Redemption**: You reach Antarctica but realize humanity doesn't deserve saving
2. **Hopeful Persistence**: Against all odds, you find others and establish a refuge
3. **Solitary Enlightenment**: You abandon civilization and merge with nature
4. **Transhumanist Transcendence**: You upload consciousness to escape biology
5. **Collective Memory**: You record everything and leave it for whoever comes next
6. **Extinction Acceptance**: You stop running and witness Earth's final days
7. **Vengeful Reckoning**: You hunt down those responsible for the collapse
8. ... and 20 others, each earned through your unique journey

---

## Contributors & Credits

**Created by**: A passionate team of ex-Epic, ex-CD PROJEKT RED, and ex-Rockstar developers

**Special Thanks**: To the real climate scientists, ecologists, and grief counselors who consulted on accuracy

---

## License

AETERNA is proprietary. All rights reserved. © 2087 Studios, 2025.

---

## Contact & Community

- **Website**: [aeterna-game.dev] (coming 2025)
- **Twitter**: [@AeternaGame](https://twitter.com/AeternaGame)
- **Discord**: [Community Server](https://discord.gg/aeterna)
- **Email**: contact@aeterna-game.dev

---

## Final Word

AETERNA is not for everyone. It is a game that will make you cry looking at grass. It is a game that will haunt you after you finish it. It is a game about the most important question facing our species: *What do we do when the world is dying?*

The answer, we believe, is not to rage. Not to despair. But to *witness*. To grieve. To love what remains. And to never stop trying.

Even when all hope seems lost.

*—The AETERNA Development Team*

