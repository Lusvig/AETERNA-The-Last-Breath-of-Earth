# AETERNA: Vertical Slice System Integration Guide

## Overview

The Paris Overgrown vertical slice demonstrates every core system in AETERNA working in perfect orchestration. This document explains how systems communicate and cascade off each other.

---

## System Communication Architecture

```
                          AeternaGameMode
                                 |
                ___________________+___________________
                |                 |                   |
         SurvivalManager  ChoiceTracker    MemoryEchoSystem
                |              |                  |
        ________+_____    _____|_____        _____|____
       |        |     |   |         |       |         |
  OxygenSystem Health Hunger NPC Psych Trail MemoryEcho
               System Stats  Rel    State    Cinematic
                                    
                          ParisLevel
                    (orchestrates all above)
                    |      |      |      |
            DialogueSystem CreatureController
            InteractionPoints RadiationSystem
```

---

## System Initialization Order

### Phase 1: Foundation (GameMode.BeginPlay)
1. **AeternaGameMode spawns:**
   - ASurvivalManager
   - AChoiceTracker
   - AMemoryEchoSystem

2. **Player spawns with components:**
   - USurvivalComponent (8 stats)
   - UOxygenSystem (hypoxia)
   - UPsychologicalSystem (trauma/hallucinations)

3. **Paris Level initializes:**
   - Zones activated (Notre-Dame, Seine, Parks)
   - Water level set to 0
   - Radiation at 0.15
   - Temperature at 12°C

### Phase 2: Content Creation (ParisLevel.BeginPlay)
1. Dialogue System spawns and initializes first conversation
2. Memory Echo System registers 4 echoes (Sarah, Marcus, Child, Doctor)
3. Zones marked active/inactive
4. Creature spawn points registered

### Phase 3: Gameplay Loop (ParisLevel.Tick)
- Environmental effects update (water rising, temperature cycling)
- Story progression checks (has 2 minutes passed? trigger state change)
- Creature behaviors update (herd AI, fear responses)

---

## Example: Complete Player Interaction Flow

### Player finds Sarah's body in Louvre

```
1. Player interacts with corpse
   └─> EnvironmentInteraction::OnInteract() fires
       └─> Memory Echo ID 1 queued

2. MemoryEchoCinematic::PlayMemoryEcho(1)
   └─> Cinematic plays (6:45 minutes)
   └─> Player sees Sarah's final moments
   └─> OnEchoCompleted fires

3. ChoiceTracker records 3-branch choice:
   - Choice A (Respectful): MoralWeight +1.0
   - Choice B (Loot): MoralWeight -0.5
   - Choice C (Funeral): MoralWeight +1.5, Time +30min

4. Survivor Component reacts to Memory Echo:
   └─> InflictTrauma(Witnessed_Death, 1.5)
   └─> Sanity -15
   └─> TraumaLevel +15
   └─> Possibility: HallucinationTriggered

5. If player chose FUNERAL:
   └─> 30 minutes of gameplay pass
   └─> SanityLevel +10 (spiritual closure)
   └─> PsychologicalSystem reduces TraumaLevel by 5

6. Environmental consequence:
   └─> If player chose LOOT:
       └─> Later NPC encounters: trust reduced by 5
       └─> "You've been looting the dead..."
```

---

## System Interactions During Flooding Event

### Water rises, all systems cascade:

```
ParisLevel::TriggerFloodingEvent()
    |
    +─> UpdateWaterLevel() called each frame
    |   └─> Current = 0.0 + (15.0 * DeltaTime)
    |       +─> AmbientTemperature -= 0.5 (getting colder)
    |       +─> RadiationIntensity increases (underwater sources)
    |
    +─> CreatureController responses:
    |   └─> All creatures FleeFromThreat()
    |       +─> Behavior set to FLEEING
    |       +─> FearLevel = 100
    |       +─> BioluminesenceIntensity reduced (dim from fear)
    |       +─> All deer move to high ground pathfinding
    |
    +─> OxygenSystem threat increases:
    |   └─> If player enters water:
    |       +─> OxygenLevel depletes 4x faster
    |       +─> HeartbeatRate accelerates
    |       +─> ScreenVignette increases
    |       +─> HallucinationIntensity might spike
    |
    +─> PsychologicalSystem stress response:
    |   └─> DespairLevel increasing (escape pressure)
    |   └─> IsolationTime increases (if NPC separated)
    |   +─> TriggerParanoia() possible (water sounds = threats)
    |
    +─> DialogueSystem integration:
    |   └─> NPC companion panics
    |       +─> "Water's rising! We have to go!"
    |       +─> Relationship changes based on player response
    |           ├─> Wait for them: +10 relationship
    |           ├─> Leave them: -20 relationship + guilt trauma
    |           └─> Help them up: +15 relationship
    |
    +─> SurvivalSystem updates:
        └─> Temperature dropping
        |   +─> Cold exposure damage if no shelter
        |   +─> Movement speed reduced if hypothermia begins
        └─> Radiation increasing
            +─> ExposeToRadiation() called
            +─> Sanity damage if radiation >50
```

---

## Choice Tracking Through Entire Slice

```
CHOICE 1: Sarah's Body
Action: Funeral rite
Impact: Moral +1.0 (compassionate)
        Time +30min
        Sanity +10 (spiritual closure)

CHOICE 2: Herd Approach
Action: Peacefully observe
Impact: ExperienceBeauty() called
        Sanity +25
        ParanoiaLevel -10
        No creatures harmed (Moral +0.5)

CHOICE 3: NPC Encounter
Action: "I'll help you survive"
Impact: Moral +1.0 (compassionate)
        NPCRelationship +10 (Sarah NPC)
        Dialogue path: ALLY branch
        NPC will help escape later

CHOICE 4: Flood Response
Action: "We escape together"
Impact: Moral +2.0 (sacrifice)
        Risk: May both fail and drown
        Success: Together ending (+5 relationship, +10 moral)

FINAL CALCULATION:
CompassionScore = 50 + (1.0 + 0.5 + 1.0 + 2.0) × 10 = 90.0
EnvironmentalScore = 0 + 0 (no trees burned, no creatures killed) = 0
KillCount = 0 (pacifist approach)
TrustRatio = 1.0 (all interactions positive)

ELIGIBLE ENDING: "The Compassionate"
```

---

## Key Integration Points

### 1. Survival Stats → UI/Audio

```cpp
// When hunger drops below 20:
USurvivalComponent::ApplyDamage(Hunger, 1.0)
    └─> OnStatChanged broadcast
        └─> HUD updates to show warning
        └─> Audio plays stomach growl
        └─> Movement speed reduced

// When temperature drops below -30:
OnStatChanged(Cold)
    └─> PsychologicalSystem gets callback
        └─> DespairLevel +5 (cold is depressing)
        └─> Hallucination chance +20%
    └─> UI flips to blue tint
    └─> Audio: chattering teeth
```

### 2. Choice → Relationship → Future Dialogue

```cpp
// Player chooses compassionate dialogue option
DialogueSystem::SelectDialogueChoice(1)
    └─> ModifyNPCRelationship("Sarah", +1.0)
    └─> Future dialogue has +relationship bonus
        └─> "You were kind to me back then..."
        └─> NPC more likely to help in crisis

// Player chooses pragmatic option
DialogueSystem::SelectDialogueChoice(2)
    └─> ModifyNPCRelationship("Sarah", -0.5)
    └─> NPC suspicious now
        └─> "Why should I trust you?"
        └─> NPC may abandon during flood
```

### 3. Psychological Trauma → Visual/Audio Effects

```cpp
// Witness Mass Grave (30 bodies)
PsychologicalSystem::FindMassGrave(30)
    └─> InflictTrauma(Mass_Grave, 1.5)
    └─> Sanity -60
    └─> TraumaLevel +60
    └─> TriggerHallucination() likely
        └─> HallucinationIntensity = 0.6
        └─> ScreenDistortion enabled
        └─> Audio: whispers, screaming
        └─> Duration: 8 seconds
    └─> OnStateChanged broadcast
        └─> CurrentState = Hallucinating
        └─> UI feedback: distorted health display
        └─> Player can't control reliably (game mechanics reflect psychology)
```

### 4. Creature AI → Environment → Narrative

```cpp
// Water rises (ParisLevel::FloodingEvent triggered)
CreatureController::FleeFromThreat(WaterFlood)
    └─> All herd set to FLEEING
    └─> Bioluminescence dims (fear response)
    └─> Creatures pathfind upward
    └─> OnHerdEncounter broadcast
        └─> DialogueSystem queues: "They're running too!"
        └─> If player has high relationship:
            └─> NPC: "We should follow them to high ground"
            └─> Moral +2.0 if player helps herd to safety

// Creatures reach safety
MemoryEchoSystem might trigger new echo:
    └─> "The herd survived, like we did"
    └─> Environmental consequence: life continues after us
```

---

## Failure/Success Cascades

### Path A: Compassion Route (Success Ending)

```
Compassionate choices
    ↓
Sanity maintained above 50
    ↓
Relationships positive
    ↓
NPC and herd reach safety with player
    ↓
Memory Echo plays: "We made it. We were not alone."
    ↓
Ending: THE COMPASSIONATE
(Credits: "By choosing connection, you proved humanity's worth")
```

### Path B: Pragmatism Route (Survivor Ending)

```
Pragmatic choices
    ↓
Sanity moderate (30-50)
    ↓
Mixed relationships
    ↓
Player reaches safety, others may not
    ↓
Hollow ending: survivor's guilt
    ↓
Ending: THE SURVIVOR
(Credits: "You lived. But at what cost?")
```

### Path C: Selfishness Route (Monster Ending)

```
Selfish/harmful choices
    ↓
Sanity low (<30)
    ↓
NPCs distrust/betrayed
    ↓
Herd slaughtered for food
    ↓
Reach safety alone
    ↓
Hallucinations of dead herd/NPC
    ↓
Ending: THE MONSTER
(Credits: "Was survival worth this? Can you live with who you became?")
```

---

## Technical Performance Considerations

### System Update Order (to minimize lag):

1. **High Priority (every frame):**
   - SurvivalComponent::TickComponent (stat decay)
   - OxygenSystem (hypoxia immediate threat)
   - InputSystem (player input responsiveness)

2. **Medium Priority (every 0.1s):**
   - PsychologicalSystem (trauma cascades)
   - CreatureController (AI decisions)
   - ParisLevel (environmental updates)

3. **Low Priority (every 0.2s):**
   - DialogueSystem (dialogue timing, less critical)
   - MemoryEchoSystem (stateful, not real-time)
   - NPC pathfinding updates

### Memory Management:

- Pre-allocate arrays for stats to avoid runtime allocations
- Pool Memory Echo cinematics (4 total in slice)
- Stream creatures in/out based on player proximity
- Dialogue strings loaded once, not recreated each display

---

## Testing Integration Checklist

- [ ] Start level → All managers spawn correctly
- [ ] Player moves → Survival stats decay realistically
- [ ] Enter water → Oxygen depletes 4x faster
- [ ] Find Sarah body → Memory Echo plays (6:45 exactly)
- [ ] Choose dialogue → ChoiceTracker records moral weight
- [ ] Meet herd → Creatures flock together, pulsing
- [ ] Trigger flood → Water rises, creatures flee, temp drops
- [ ] Drowning scenario → Screen vignettes, heartbeat audio
- [ ] Extreme trauma → Hallucinations trigger visually
- [ ] Final escape → All systems converge on ending calc
- [ ] Ending triggers → Correct cinematic plays based on choices

---

**THIS IS THE SOUL OF AETERNA.**

**Systems united in service of emotional truth.**

**Every mechanic serves narrative.**

**Every choice carries weight.**

**The game feels your decisions.**

---

**END INTEGRATION SPECIFICATION**
