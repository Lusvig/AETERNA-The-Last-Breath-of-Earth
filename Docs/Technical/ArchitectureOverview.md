# AETERNA: Technical Architecture Overview

## System Architecture

AETERNA's architecture is built on a modular, event-driven design that allows systems to communicate without tight coupling while maintaining high performance across 400km² of seamless world.

### Core Architecture Diagram

```
┌─────────────────────────────────────────────────────────────┐
│                   AETERNA GAME MODE                         │
│  (Main orchestrator, handles time, day/night, game flow)   │
└──────────┬──────────────────────────────────────────────────┘
           │
    ┌──────┴──────────────────────────────────────────┐
    │                                                  │
    ▼                                                  ▼
┌─────────────────────┐  ┌──────────────────────────────────┐
│ SURVIVAL SYSTEMS    │  │ NARRATIVE SYSTEMS                │
├─────────────────────┤  ├──────────────────────────────────┤
│ • Health Tracking   │  │ • Choice Tracker                 │
│ • Stats Decay       │  │ • Memory Echo System             │
│ • Environmental FX  │  │ • NPC Relationships              │
│ • Resource Manager  │  │ • Dialogue Engine                │
│ • Disease/Injury    │  │ • Legacy System                  │
└─────────────────────┘  └──────────────────────────────────┘
    │                            │
    ▼                            ▼
┌─────────────────────┐  ┌──────────────────────────────────┐
│ WORLD SYSTEMS       │  │ AI SYSTEMS                       │
├─────────────────────┤  ├──────────────────────────────────┤
│ • Weather Engine    │  │ • Mass Entity Framework          │
│ • Time of Day       │  │ • Creature Spawning              │
│ • Radiation Storms  │  │ • NPC Scheduling                 │
│ • Ecosystem        │  │ • Behavior Trees                 │
│ • World Partition   │  │ • Perception Systems             │
└─────────────────────┘  └──────────────────────────────────┘
```

## Module Organization

### 1. Core Module (Aeterna)
**Purpose**: Game framework and orchestration

**Key Classes**:
- `AAeternaGameMode`: Main game mode, orchestrates all systems
- `AGameStateCustom`: Extended game state for survival tracking
- `APlayerController`: Input handling and player state

**Responsibilities**:
- Initialize all subsystems
- Manage game flow (start, pause, end)
- Broadcast important events
- Handle save/load operations

### 2. Survival Systems Module
**Purpose**: Track and simulate player survival mechanics

**Key Classes**:
- `USurvivalComponent`: Individual stat tracking (on player)
- `ASurvivalManager`: Global survival mechanics coordinator
- `UHealthSystem`: Disease, injury, infection simulation
- `UResourceManager`: Inventory and crafting

**Responsibilities**:
- Decay stats over time
- Apply stat interactions
- Trigger death conditions
- Manage food/water availability
- Simulate medical conditions

### 3. Narrative Systems Module
**Purpose**: Handle storytelling, choices, and NPC interactions

**Key Classes**:
- `AChoiceTracker`: Track all player decisions
- `AMemoryEchoSystem`: Deliver narrative through echoes
- `ANPCCharacter`: Individual NPC with relationships and schedules
- `UDialogueComponent`: Handle NPC conversations

**Responsibilities**:
- Record player choices with weight
- Calculate ending eligibility
- Trigger memory echoes
- Manage NPC relationships
- Track legacy/world state

### 4. World Systems Module
**Purpose**: Environmental simulation and world state

**Key Classes**:
- `AWeatherSystem`: Procedural weather and radiation storms
- `AEcosystemManager`: Creature and plant simulation
- `ATimeOfDaySystem`: 24-hour cycle and seasonal changes
- `AWorldStateManager`: Global world variables (275-day countdown)

**Responsibilities**:
- Generate weather conditions
- Calculate temperature/radiation
- Trigger environmental events
- Manage creature spawning/migration
- Track day counter

### 5. AI Systems Module
**Purpose**: NPC and creature behavior

**Key Classes**:
- `AMassEntityAIManager`: Manages 1000+ NPCs via Mass Framework
- `ACreatureController`: Individual creature behavior
- `ANPCBehaviorTree`: Decision trees for NPC actions

**Responsibilities**:
- Spawn and manage NPCs efficiently
- Execute behavior trees
- Handle perception and decision-making
- Trigger emergent interactions

## Data Flow

### Player Action to World State Change

```
Player Input
    │
    ▼
PlayerController::ProcessInput()
    │
    ▼
Character:Action() (e.g., "Take Food")
    │
    ├─→ SurvivalComponent::EatFood()
    │   └─→ Hunger stat decreases
    │   └─→ Health stat increases
    │
    ├─→ ChoiceTracker::RecordChoice()
    │   └─→ Choice recorded (if meaningful)
    │
    └─→ WorldStateManager::ApplyConsequence()
        └─→ World state updated
        └─→ NPC reactions triggered
```

### Memory Echo Trigger Flow

```
Player discovers NPC body
    │
    ▼
Interaction triggered
    │
    ▼
MemoryEchoSystem::TriggerEcho(EchoID)
    │
    ▼
Cinematic plays (Sequencer)
    │
    ├─→ Voices play (Wwise)
    ├─→ Visual FX (Niagara)
    ├─→ Camera animation
    │
    ▼
Echo conclusion
    │
    ▼
ChoiceTracker records moral weight
    └─→ Affects ending calculation
```

## Performance Optimization Strategies

### 1. World Partition Streaming
- World divided into cells (~2km × 2km each)
- Cells load/unload based on player proximity
- Serialization-optimized for fast streaming
- Zero load times with proper implementation

### 2. Nanite Virtualization
- High-poly models rendered at any distance
- Automatic LOD management
- Memory bandwidth optimization
- Dramatic polygon count reduction needed

### 3. Lumen Global Illumination
- Real-time GI without baked lightmaps
- Dynamic lighting updates
- Full ray tracing support
- GPU-driven at massive scale

### 4. Mass Entity Framework
- 1000+ NPCs with minimal overhead
- Efficient memory layout (ECS architecture)
- CPU-driven pathfinding
- Scalable to tens of thousands with optimization

### 5. Stat Calculation Optimization
- Delta-time based stat decay (not per-frame)
- Cached interaction calculations
- Lazy evaluation of complex cascades
- Stat update batching every 0.1 seconds

## Save Game Architecture

### Save File Structure
```json
{
  "version": "0.1.0",
  "day": 47,
  "timeOfDay": 14.5,
  "player": {
    "position": [1024.0, 2048.0, 512.0],
    "survival_stats": {
      "hunger": 35.0,
      "thirst": 42.0,
      "cold": -5.0,
      "radiation": 12.5,
      "injury": 0.0,
      "exhaustion": 45.0,
      "sanity": 65.0,
      "health": 78.5
    },
    "inventory": [
      {"item": "canned_beans", "count": 2},
      {"item": "water_bottle", "count": 1}
    ]
  },
  "choices_made": [
    {"id": 1, "type": "moral", "alignment": 1.0, "weight": 1.5},
    {"id": 2, "type": "environmental", "alignment": -0.5, "weight": 1.0}
  ],
  "world_state": {
    "compassion_score": 52.5,
    "environmental_score": -10.0,
    "kill_count": 2,
    "trust_ratio": 0.65,
    "echoes_triggered": [1, 2],
    "npcs_alive": {
      "sarah": false,
      "marcus": true,
      "child": true
    }
  }
}
```

## Event System

### Subscription Model
```cpp
// Systems subscribe to events
SurvivalComponent->OnStatChanged.AddDynamic(HUDManager, &AHUDManager::UpdateStatDisplay);
GameMode->OnDayAdvanced.AddDynamic(WeatherSystem, &AWeatherSystem::UpdateConditions);
ChoiceTracker->OnMoralChoice.AddDynamic(NarrativeSystem, &AChoiceTracker::RecordMoralInfluence);

// When event occurs
OnStatChanged.Broadcast(ESurvivalStat::Hunger, 35.0f);
```

### Event Types
- **SurvivalEvents**: Stat changes, death, critical conditions
- **NarrativeEvents**: Choices recorded, echoes triggered, relationships changed
- **WorldEvents**: Day advanced, weather changed, ecosystem updated
- **NPCEvents**: NPC died, dialogue triggered, scheduled action occurred

## Network Architecture (Future)

For Ghost Mode co-op:
- P2P connection between players
- Local player owns their world state
- Ghost player receives read-only world copy
- Message passing for ghost interactions
- 1000-message-per-second bandwidth target

---

**END DOCUMENT**
