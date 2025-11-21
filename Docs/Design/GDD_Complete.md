# AETERNA: The Last Breath of Earth
## Complete Game Design Document v2.1

**Document Status**: Active Development  
**Last Updated**: 2025-01-15  
**Version**: 2.1 (Vertical Slice Build)  
**Classification**: Internal | Confidential

---

## Table of Contents

1. [Executive Summary](#executive-summary)
2. [Game Overview](#game-overview)
3. [Core Design Pillars](#core-design-pillars)
4. [Player Experience Goals](#player-experience-goals)
5. [Setting & World](#setting--world)
6. [Core Gameplay Systems](#core-gameplay-systems)
7. [Narrative Design](#narrative-design)
8. [Technical Architecture](#technical-architecture)
9. [Content Roadmap](#content-roadmap)
10. [Success Metrics](#success-metrics)

---

## Executive Summary

**AETERNA: The Last Breath of Earth** is an ultra-realistic, narratively-driven survival simulator set in 2087—Earth's final decade before atmospheric collapse. The player is one of 1,000 remaining humans, racing toward the last evacuation ark in Antarctica while their world crumbles around them.

Unlike traditional survival games (which are about winning), AETERNA is about *witnessing* and *grieving*. Every system—from hunger mechanics to NPC interactions to environmental hazards—serves the emotional core: **What does it feel like to live in a dying world?**

**Target Audience**: Mature gamers (18–55) who appreciate:
- Narrative depth and emotional weight
- Photorealistic aesthetics
- Systems-driven gameplay
- Moral ambiguity and consequences
- Climate fiction (cli-fi) themes

**Release Target**: Q3 2026 (PC/Next-Gen)

---

## Game Overview

### High Concept

*"The Last of Us Part II meets Death Stranding meets Red Dead Redemption 2 meets STALKER 2—set at the end of the world, with a climate collapse timer and 27 different endings, none of them happy."*

### Core Loop

```
1. Assess Survival Needs (hunger, cold, radiation, sanity)
   ↓
2. Explore World / Scavenge Resources
   ↓
3. Encounter NPCs / Discover Memory Echoes
   ↓
4. Make Moral Choices (consequences are permanent)
   ↓
5. Craft / Build / Shelter
   ↓
6. Face Consequences (world state changes)
   ↓
Return to Step 1
```

### Player Fantasy

You are a survivor—not a hero, not chosen—trying to reach safety while watching the world's final beautiful, terrible moments. Your choices matter. Every person you save or abandon changes the world. Every resource you use or preserve affects your environment. You cannot save everyone. You cannot save anything, really.

But you can *witness*. And in witnessing, perhaps you find meaning.

---

## Core Design Pillars

### 1. Photorealism as Immersion

Every visual element is rooted in reality:
- Characters' skin pores open/close with stress and temperature
- Buildings have real structural physics (poor construction collapses in storms)
- Ecosystems operate on real-world logic (predator/prey cycles, seasonal migration)
- Weather affects gameplay meaningfully (radiation storms reduce visibility and increase exposure risk)

**Principle**: *Realism breaks immersion when players notice it's fake. We eliminate the "seams."*

### 2. Meaningful Consequences

All player choices are permanent:
- Save an NPC → they become a recruitable ally, but you used precious supplies
- Loot a body → gain resources, but lose narrative opportunity and emotional connection
- Burn forest for warmth → immediate survival gain, permanent ecosystem damage
- Tell a story of hope → others believe in you, or dismiss you as delusional

**Principle**: *Players should fear their own decisions.*

### 3. Systems Over Spectacle

No cinematic moments that don't earn their weight:
- We don't force emotional beats; we *create conditions* for them to emerge
- A quiet scene of you sharing food with an NPC can be more powerful than an explosion
- Survival mechanics create natural pacing and tension

**Principle**: *Systems create storytelling; storytelling doesn't override systems.*

### 4. Emotional Authenticity

Design everything to maximize emotional resonance:
- Stat tracking (you *see* yourself deteriorating)
- Sound design (absence of sound is more powerful than presence)
- NPC reactions (they fear you, hope with you, betray you)
- Environmental storytelling (abandoned homes, mass graves, gardens reclaiming cities)

**Principle**: *Make players *feel* before asking them to think.*

---

## Player Experience Goals

### Primary Goals (Must Achieve)
- [ ] Player feels the weight of choices
- [ ] Player experiences climate grief (not forced, but organic)
- [ ] Player questions their own morality
- [ ] Player remembers this game years later
- [ ] Player plays multiple times to see different endings

### Secondary Goals (Should Achieve)
- [ ] Photorealistic world feels alive and responsive
- [ ] Survival mechanics create meaningful tension (not frustration)
- [ ] NPCs feel like real people (not quest-dispensers)
- [ ] Permadeath mode feels genuinely threatening
- [ ] Co-op Ghost Mode creates unique emotional bonds

### Tertiary Goals (Nice to Have)
- [ ] Speedrunning community emerges
- [ ] Fan fiction/art community thrives
- [ ] Academic discussion of game's climate themes
- [ ] Critical acclaim and award nominations

---

## Setting & World

### Timeline

**2025–2050**: Climate tipping points (methane release, ice sheet collapse, mass migration crises)  
**2050–2080**: Societal collapse (wars over resources, government breakdown, organized society dissolves)  
**2080–2087**: The Silent Era (1 billion humans → 1,000 survivors in isolated refuges)  
**2087 (Game Start)**: Day 1 of countdown to final methane burst  
**2096**: "The Last Breath" – final atmospheric collapse

**Player's Timeframe**: 9 months to reach Antarctica (Days 1–275 of 3,650-day countdown)

### Geography

**Explorable Regions** (400 km² total, hand-crafted + procedurally enhanced):

#### 1. **Paris Reclaimed** (Vertical Slice)
- Flooded lower city (Seine and its tributaries have risen 8 meters)
- Notre-Dame converted into bioluminescent organism hive
- Eiffel Tower leaning at 47° angle (structural compromise visible)
- Métro system flooded—navigable only by boat or diving
- The Louvre: ransacked but structurally intact—good shelter
- Population: ~12 surviving NPCs scattered, 3 Memory Echoes

#### 2. **Venice Archipelago**
- Former Venice is now an archipelago of ruins
- Buildings sink 2cm per month (time-pressure mechanic)
- Canals choked with kelp forests and mutated aquatic creatures
- Underground tunnels provide fast travel but high radiation risk
- Population: ~35 survivors (largest settlement), 7 Memory Echoes

#### 3. **Alpine Refuge**
- Formerly the Alps—now a temperate-to-tundra transition zone
- Mountain passes choked with permafrost and unstable avalanche zones
- Monasteries and research stations repurposed as shelter
- Rare medicinal plants grow only here (strategic resource)
- Population: ~80 survivors (semi-organized community), 12 Memory Echoes

#### 4. **Chernobyl 2.0**
- Pripyat 2.0 + expanded exclusion zone covering 5,000 km²
- Radiation hotspots create deadly environmental hazards
- Creatures evolved radiation tolerance (bioluminescent creatures, deformed flora)
- Geiger counter clicking is constant soundtrack
- Underground laboratory offers forbidden knowledge (but terrible cost)
- Population: ~20 hermits/scientists, 4 Memory Echoes

#### 5. **Scandinavian Tundra**
- Former Scandinavia transformed into permafrost tundra
- Endless white landscape, extreme cold, wind that kills exposed skin in minutes
- Aurora borealis visible nightly (beautiful and deadly—increases radiation storms)
- Old research stations abandoned, valuable supplies frozen in time
- Population: ~5 isolated survivors, 2 Memory Echoes

#### 6. **The Route South** (Procedurally Generated)
- Randomly generated path through Germany/Austria/Italy toward Africa
- Different each playthrough (player choices affect terrain/settlements)
- Travel time compressed (20–30 hours of gameplay per 1,000 km)
- Random encounter zones with other survivors (some friendly, many hostile)

#### 7. **Antarctica (End Destination)**
- The Evacuation Ark exists, or doesn't (depends on your choices)
- Locked behind one of 5 final keys (players must choose which to pursue)
- Each key represents different moral commitments
- Arrival triggers ending sequence evaluation

---

## Core Gameplay Systems

### System 1: Survival Statistics

Player tracks 8 interconnected survival stats, each with cascading effects:

#### 1.1 **Hunger** (0–100)
- **Effects**: At 0-20: movement speed -50%, vision blurs, decision-making impaired
- **Acceleration**: Varies by activity (sprinting +10/min, sleeping -2/min)
- **Solutions**: Hunting, scavenging, cannibalism (moral choice with psychological cost)
- **UI**: Subtle stomach growl audio (increases with intensity)

#### 1.2 **Thirst** (0–100)
- **Effects**: At 0-15: hallucinations begin, stat tracking becomes unreliable
- **Acceleration**: Faster than hunger (temperature dependent)
- **Solutions**: Finding water (must purify with rare filters or boil)
- **Consequence**: Dehydration → kidney failure → death within hours

#### 1.3 **Cold/Heat** (-50 to +50)
- **Effects**: Below -30: hypothermia risk, manual movement control becomes difficult
- **Effects**: Above +40: heat stroke, vision distortion, movement penalty
- **Acceleration**: Environmental temperature ± activity + clothing
- **Solutions**: Shelter, fire, appropriate clothing, rest
- **Consequence**: Extreme values → death in minutes

#### 1.4 **Radiation Exposure** (0–100)
- **Effects**: At 50-100: nausea, vomiting, bleeding, cellular damage
- **Effects**: At 100+: acute radiation sickness, death guaranteed
- **Accumulation**: Never decreases (one-way counter)
- **Solutions**: Reduce future exposure, medical treatment (only delays inevitable)
- **Detection**: Handheld Geiger counter with audio feedback

#### 1.5 **Injury** (0–100)
- **Tracking**: Multiple injury types (broken leg, open wound, internal bleeding, burned skin)
- **Effects**: At 50+: infection risk increases 2%/hour
- **Progression**: Infection → sepsis (organ failure) → death (3–5 days)
- **Solutions**: Clean wound, apply antiseptic (rare), antibiotics (very rare), surgery (requires skill + tools + risk)
- **Permanent Damage**: Severe injuries may cause permanent stat penalties

#### 1.6 **Exhaustion** (0–100)
- **Acceleration**: Depends on exertion and hunger level
- **Effects**: At 80+: movement speed reduced, mistakes more likely, judgment impaired
- **Solutions**: Sleep (6–8 hours safe, 2–3 hours minimum)
- **Interruption**: Sounds, danger, cold can wake you prematurely
- **Risk**: Fall asleep and never wake (if cold/injured enough)

#### 1.7 **Sanity** (0–100, starting at 50)
- **Decreases**: After witnessing death, isolation (>48 hours alone), eating human flesh, killing NPCs
- **Increases**: Social interaction, finding safe shelter, small victories (eating well, seeing beauty)
- **Effects**: At 30-50: mild hallucinations, paranoia, NPCs distrust you
- **Effects**: At 0-30: severe hallucinations, suicidal ideation, unreliable UI feedback
- **Consequence**: At 0: game over (player character takes own life)

#### 1.8 **Health/Vitality** (0–100)
- **Influenced By**: All other stats (starvation lowers health, cold injury raises it, etc.)
- **Cascading Effect**: Below 30 = bleeding becomes more likely from any injury
- **Recovery**: Extremely slow without medication (1 point per 2 hours resting safely)
- **Death Threshold**: Reaches 0 → game over (death scene triggers)

**Stat Interaction Example**:
```
Scenario: Player is cold (-15°C), hungry (25 hunger), and injured (bullet wound)

Mechanics:
- Cold + Activity = Energy drain 2x faster
- Hunger + Activity = Movement speed reduced 30%
- Injury + Activity = Bleed rate increases
- Hunger + Cold + Injury = Infection risk +3%/hour

Outcome: Player must choose quickly:
- Sleep now (risks freezing to death)
- Hunt (risky with injury, may bleed out)
- Find shelter first (uses precious time, infection worsens)
- Abandon injured NPC companion (moral cost, psychological trauma -10 sanity)
```

### System 2: Survival Mechanics

#### 2.1 **Hunger & Eating**

**Food Types**:
- **Safe Foods**: Canned goods (pre-collapse), grown vegetables, hunted game (after cooking)
- **Risk Foods**: Scavenged bodies (high disease risk), unknown mushrooms (poisoning), water plants (mild nutrition)
- **Morally Compromising**: Human flesh (extreme sanity cost), companion body after death (severe trauma)

**Hunting Mechanics**:
- Track animals using visual signs (droppings, tracks, bent vegetation)
- Stalk without being detected (wind direction matters, noise discipline)
- Use weapons/traps (bows preferred over loud firearms)
- Butcher animal (attracts scavengers, takes 20 minutes, blood spatter visible for tracking)
- Cook meat (wood resource, time, or eat raw for disease risk)

**Gathering Mechanics**:
- Search buildings systematically (each room has randomized loot, some poisoned)
- Identify edible plants (requires herbalism skill or trial-and-error risk)
- Manage encumbrance (carrying capacity based on fitness stat)
- Time cost (each search takes 5–30 minutes)

#### 2.2 **Water & Hydration**

**Water Sources**:
- Bottled water (pre-collapse, rare)
- Rain water (safe if collected properly)
- Lakes/rivers (requires purification)
- Melted ice (high energy cost to melt, requires fuel)
- Condensation collection (slow, passive)

**Purification**:
- Boiling (requires water, fire, container, 10+ minutes)
- Filters (rare, limited uses ~20 liters per filter)
- Chemical purification (very rare, instant but risky if contaminated)
- Ingesting unpurified water (disease risk ~40%, symptoms appear in 2–6 hours)

#### 2.3 **Temperature & Shelter**

**Temperature Calculation**:
```
Base Temp = Biome Temperature ± Time of Day ± Weather ± Altitude ± Encumbrance
Clothing Bonus = Jacket (+5°C) + Layers (+3°C each) + Boots (+2°C)
Shelter Bonus = Uninsulated Building (+3°C) + Campfire (+8°C) + Sealed Base (+15°C)
Activity Bonus = Movement (+3°C) + Sprinting (+6°C) + Rest (-1°C/min)
```

**Extreme Cold Effects**:
- -20°C: Player can survive ~30 minutes without shelter
- -40°C: Player can survive ~5 minutes without shelter
- -60°C (tundra zones): Player can survive ~1 minute without shelter
- Frostbite (if exposed 15+ minutes): Permanent dexterity penalty, fingers turn black/unusable

**Extreme Heat Effects**:
- +50°C: Desert-like zones (rare but possible during radiation storms)
- +60°C: Death within 20 minutes without water/shade
- Heat stroke: Hallucinations, delirium, confused movement controls

**Shelter Building**:
- Simple shelter (cardboard box, abandoned building): 3–8°C bonus, takes 5–10 minutes, breakable
- Medium shelter (improved building, sealed room): 10–12°C bonus, takes 20–30 minutes, durable
- Advanced shelter (constructed base with fireplace): 15–20°C bonus, takes 2–4 hours, requires materials, very durable
- Failure mechanics: Build shelter wrong → collapses in storm, injures player, wastes materials

---

## Narrative Design

### The Memory Echo System

**Core Concept**: Players meet NPCs who are already dead when discovered. Their final moments are reconstructed as photorealistic holographic "Memory Echoes"—fully voice-acted, emotionally devastating scenes from their lives.

#### How It Works:

1. **Discovery**: Player finds an NPC's body (in shelter, on roadside, in ruins)
2. **Investigation**: Player can examine body, find journal entries, recover memory device
3. **Activation**: Body or device triggers holographic replay
4. **Experience**: 2–8 minute cinematic showing NPC's final moments, relationships, fears, hopes
5. **Connection**: Player learns NPC's story, which may inspire or horrify them
6. **Legacy**: NPC becomes part of player's "memorial" (viewable in post-game)

#### Memory Echo Examples:

**Echo #1: "Sarah's Last Day"** (Paris, Notre-Dame)
- Sarah was a marine biologist studying the bioluminescent organisms
- Echo shows her last hours: discovering her daughter is dead (killed 2 weeks ago), deciding to stay and continue research
- Final moment: Sarah walks into bioluminescent zone to end her life peacefully
- Player finds her body, can choose to:
  - Continue her research (moral victory)
  - Loot her equipment (practical but disrespectful)
  - Give her a funeral (time/resource cost, sanity boost)
  - Eat her body (extreme hunger, sanity -50)

**Echo #2: "Marcus's Betrayal"** (Venice)
- Marcus was a settlements leader who made a terrible choice
- Echo shows his decision to sacrifice a family to save the group
- Final moment: Marcus realizes his choice was wrong, attempts to undo it
- Player finds his suicide note, can choose to:
  - Publicize his guilt (destabilize settlement)
  - Keep it secret (moral burden, sanity -5)
  - Use it as blackmail (pragmatic but evil)

**Echo #3: "The Child's Hope"** (Alpine Refuge)
- A 10-year-old girl who was drawing pictures of "the world after"
- Echo shows her teaching other children about hope
- Final moment: She collapses from illness, surrounded by her drawings
- Player can choose to preserve her drawings (emotional weight, takes space)

### The Choice Tracking System

Every player decision is logged and tracked:

```
CHOICE CATEGORIES:

1. Moral Choices (Save vs. Loot)
   - Each choice tracked (binary: compassionate vs. pragmatic)
   - Running total: Compassion Score (0–100)

2. Resource Choices (Use vs. Preserve)
   - Each consumption tracked (e.g., "burned forest for warmth")
   - Running total: Environmental Score (-100 to 100)

3. NPC Relationship Choices (Help vs. Harm)
   - Each interaction tracked (trust/betray/ignore)
   - Per-NPC reputation (-100 to 100)

4. Narrative Choices (Dialogue/Moral Dilemmas)
   - ~50 branching points throughout game
   - Each tracked with contextual weight (some matter more than others)

5. Gameplay Choices (Permadeath, Iron Mode, Difficulty)
   - Modifier to final ending calculation

EXAMPLE: 200-hour playthrough might include:
- 85 save/loot encounters (player saved 45, looted 40)
- 12 resource scarcity choices (player conserved 8, consumed 4)
- 34 NPC interactions (relationships span -45 to +78)
- 47 story-critical choices
- Permadeath: No (ended game with 3 character deaths)

Result: "The Compassionate Witness" ending path eligible
```

### The 27 Endings Framework

**Ending Calculation Algorithm** (simplified):

```
Compassion Score (0–100)     →  0–25: Pragmatist   | 26–75: Balanced   | 76–100: Idealist
Environmental Score (-100–100) →  <0: Despoiler    | 0: Neutral        | >0: Caretaker
Kill Count (0–500)             →  0–5: Pacifist    | 6–50: Realist     | 51+: Killer
Trust/Betrayal Ratio (0–1)     →  <0.4: Traitor   | 0.4–0.7: Complex  | >0.7: Ally
Ending Determinant Combinations: 5 × 3 × 3 × 3 = 135 possible paths, filtered to 27 "true" endings
```

**Example Ending Tiers**:

**TRANSCENDENCE ENDINGS** (If Compassion >75 AND Environmental >50 AND Pacifist):
1. "The Gardener's Dream": Plant consciousness, merge with bioluminescent organism
2. "The Bridge Builder": Unite all surviving communities before evacuation
3. "The Archive": Record all human knowledge before collapse

**ACCEPTANCE ENDINGS** (If Compassion 26–75 AND Kill Count 6–50):
4. "The Witness": Reach Antarctica but choose not to board the Ark
5. "The Caretaker": Establish permanent settlement and build new society
6. "The Storyteller": Broadcast story to any remaining listeners

**TRAGIC ENDINGS** (If Compassion <25 OR Environmental <-50):
7. "The Despoiler": Reach Ark, humanity survives as parasites (moral cost)
8. "The Last": Everyone dies except you; you board Ark alone
9. "The Saboteur": Destroy the Ark to prevent corrupt humanity from escaping

**+ 18 more with specific combinations...**

---

## Technical Architecture

### Engine & Framework Overview

**Engine**: Unreal Engine 5.4+

**Core Systems Architecture**:

```
AeternaGameMode
    ├── Survival System Manager (Hunger, Thirst, Cold, Radiation, etc.)
    ├── Narrative Manager (Choice Tracker, Memory Echo Controller)
    ├── World State Manager (Dynamic consequences)
    ├── AI Manager (Mass Entity for 1000+ NPCs)
    ├── Weather System (Procedural storms, radiation bursts)
    ├── Ecosystem Manager (Animal migration, plant growth, seasonal changes)
    ├── Save Game Manager (Permadeath tracking, legacy system)
    └── UI/HUD Manager (Stats display, menus, world UI)
```

### Gameplay Systems (C++)

```cpp
// Core survival stat system
class USurvivalComponent : public UActorComponent {
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Hunger;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Thirst;
    
    // ... other stats
    
    UFUNCTION(BlueprintCallable, Category="Survival")
    void ApplyDamage(EStatType StatType, float Amount);
    
    UFUNCTION(BlueprintCallable, Category="Survival")
    void RestoreHealth(EStatType StatType, float Amount);
};

// NPC interaction with memory echo system
class UMemoryEchoComponent : public UActorComponent {
public:
    UPROPERTY(EditAnywhere)
    class AMemoryEchoNPC* AssociatedNPC;
    
    UFUNCTION(BlueprintCallable, Category="Narrative")
    void TriggerEcho();
    
    UFUNCTION(BlueprintCallable, Category="Narrative")
    void RecordChoice(EChoiceType ChoiceType, float Weight);
};

// Choice tracking system
class UChoiceTrackerComponent : public UActorComponent {
public:
    UPROPERTY()
    TMap<FString, float> ChoiceMetrics;
    
    UFUNCTION(BlueprintCallable, Category="Narrative")
    void RecordMoralChoice(bool bWasCompassionate);
    
    UFUNCTION(BlueprintCallable, Category="Narrative")
    int32 CalculateEndingIndex();
};
```

### Content Pipeline

#### Asset Preparation

1. **Characters**: MetaHuman base + custom modifications
   - Pore/sweat system using Substrate materials
   - Real-time hair physics with Chaos
   - Breathing animation cycles (5 different states: calm, stressed, exertion, suffering, dying)

2. **Environments**: Quixel Megascans + hand-crafted enhancement
   - 8K textures with Nanite virtualization
   - Lumen for real-time GI
   - Destruction-ready geometry with Chaos physics

3. **Audio**: Wwise middleware + spatial HRTF
   - 3D audio positioning for all sounds
   - Real-time atmospheric propagation (sound travels differently through flooded areas, ruins, etc.)
   - Procedural wind/vegetation rustling based on weather simulation

---

## Content Roadmap

### Vertical Slice (Q1 2025) ✓
- Paris Overgrown – Day 47 (fully playable, 1–2 hours)
- 3 Memory Echoes implemented
- Core survival systems functional
- 2 choice-driven NPC encounters
- 2 endings visible

### Alpha Build (Q2 2025)
- Venice Archipelago + Alpine Refuge regions
- 12 more Memory Echoes
- 15 total NPC characters
- Crafting system V1
- 8 endings visible
- Permadeath mode stable

### Beta Build (Q3 2025)
- Chernobyl 2.0 + Scandinavian Tundra regions
- All 27 endings implemented
- 35+ NPCs with full dialogue trees
- Advanced crafting + base-building
- Co-op Ghost Mode beta
- Performance optimization pass

### Gold Master (Q1 2026)
- Final polish
- All content implemented
- Comprehensive bug fixing
- Marketing trailer production
- Pre-order campaign launch

### Launch (Q3 2026)
- Day 1 patch preparation
- Season pass content planned

---

## Success Metrics

### Critical (Must Achieve)
- [ ] Game runs at 60fps average on target hardware (RTX 4090)
- [ ] All 27 endings are reachable and unique
- [ ] Player completes game in 25–40 hours first playthrough
- [ ] Survival mechanics feel impactful, not frustrating
- [ ] No game-breaking bugs at launch

### Important (Should Achieve)
- [ ] 85%+ critic approval on Metacritic
- [ ] 80,000+ players within first month
- [ ] Active speedrunning community (sub-20 hour runs)
- [ ] 50+ fan-created Memory Echoes (community content)
- [ ] Award nominations (BAFTA, Golden Joystick, etc.)

### Nice to Have
- [ ] Speedrunning world record broken 10+ times
- [ ] Academic papers analyzing game's climate messaging
- [ ] Mainstream media coverage (New York Times, BBC, etc.)
- [ ] 500,000+ players lifetime
- [ ] Sequel/spin-off opportunities

---

## Appendix A: Glossary

- **Memory Echo**: Holographic reconstruction of an NPC's final moments
- **Legacy System**: Tracks all player choices and calculates ending
- **Ghost Mode**: Co-op where friends appear as echoes of deceased loved ones
- **Iron Mode**: Permadeath hardcore difficulty
- **Survival Stats**: 8 interconnected metrics tracking player's physiological/psychological state
- **Ecosystem Cascade**: Game mechanic where players' actions affect animal/plant populations
- **Choice Permanence**: Design philosophy that player decisions cannot be undone

---

## Appendix B: Design Inspirations

- **The Last of Us Part II**: Narrative complexity, moral ambiguity, character depth
- **Death Stranding**: Survival mechanics, NPC interaction, philosophical depth
- **Red Dead Redemption 2**: Living world, emergent storytelling, photorealism
- **STALKER 2**: Atmosphere, environmental storytelling, danger
- **Outer Wilds**: Emotional payoff, discovery-driven narrative
- **What Remains of Edith Finch**: Intimate storytelling, emotional resonance
- **Firewatch**: Dialogue-driven narrative, mystery
- **Greedfall**: Smaller-scale open world, meaningful NPC relationships
- **Climate Science Literature**: "The Uninhabitable Earth" by David Wallace-Wells

---

## Document History

- **v1.0** (2024-11-01): Initial GDD outline
- **v1.5** (2024-12-15): Added Memory Echo system details
- **v2.0** (2025-01-01): Finalized 27 endings framework
- **v2.1** (2025-01-15): Updated for vertical slice build

---

**END OF DOCUMENT**

*For questions or clarifications, contact: design@aeterna-game.dev*
