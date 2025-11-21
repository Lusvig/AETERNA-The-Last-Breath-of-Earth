# AETERNA: Survival Mechanics Design Document

## Overview

Survival mechanics in AETERNA are not arbitrary difficulty sliders—they are the narrative. Every stat tells a story. When the player's hunger bar is empty, they are living the story of scarcity. When their sanity drops, they are experiencing psychological breakdown alongside the character.

## The 8 Core Stats

### 1. Hunger (0–100)
**Starts at**: 50
**Decays at**: 0.5 points/second (baseline, varies by activity)
**Critical threshold**: Below 20
**Effects**:
- 50–40: Stomach growls (audio cue), minor movement penalty (-10%)
- 40–20: Vision slightly blurs, decision-making affected
- 20–0: Movement -50%, hallucinations begin, weakness visible in animations
- 0: Game over (starvation death)

**Restoration**:
- Cooked game meat: +40 hunger
- Canned goods (pre-collapse): +25 hunger
- Foraged berries: +10 hunger (risk of poisoning: 15%)
- Human flesh: +50 hunger (sanity -50)

**Interactions**:
- Hunger + Cold: Decay rate increases 1.5x (body needs more energy)
- Hunger + Activity: Each sprint burns +10 hunger per second
- Hunger + Thirst: Both decay faster (-15% each)

### 2. Thirst (0–100)
**Starts at**: 50
**Decays at**: 0.8 points/second (faster than hunger)
**Critical threshold**: Below 15
**Effects**:
- 50–35: Subtle thirst indication
- 35–20: Hallucinations begin, vision distorts, NPCs appear blurry
- 20–0: Severe hallucinations, speech slurred, movement erratic
- 0: Game over (dehydration death)

**Restoration**:
- Clean water (bottled, purified): +30 thirst
- Rain water (collected): +25 thirst (if uncontaminated)
- River water (unpurified): +15 thirst (+40% disease risk)
- Snow/ice (melted, requires fuel): +20 thirst

**Purification Options**:
- Boiling: Requires water + fire + container + 10 minutes
- Water filter (rare, ~20 liters per filter): Instant purification
- Chemical tablets (very rare): Instant, slight taste penalty
- Solar still (requires sun, 30 minutes, outputs 2 liters)

### 3. Cold/Heat (-50 to +50)
**Starts at**: 0
**Environmental base**: Varies by biome and time of day
**Critical thresholds**: Below -30 (hypothermia) or above +40 (heat stroke)
**Effects**:
- -50 to -30: Hypothermia stage 1 (shivering, +10% exhaustion gain)
- -30 to -20: Hypothermia stage 2 (confusion, -20% movement speed)
- -20 to 0: Cold discomfort (animations show shivering)
- 0 to +20: Comfortable temperature
- +20 to +40: Heat discomfort (sweating)
- +40 to +50: Heat sickness stage 1 (nausea, vision distortion)
- +50+: Heat sickness stage 2 (vision blur, movement erratic, death in 20 minutes)

**Warming methods**:
- Campfire (proximity): +8°C
- Shelter (sealed room): +12–15°C
- Layered clothing (each layer): +2–3°C
- Running/activity: +3°C temporary
- Another person (body heat): +1°C
- Cooked food (internal warmth): +2°C temporary

**Cooling methods**:
- Shade: -5°C
- Water immersion: -10°C (risk of cold exposure if air temperature low)
- Rest in open: -3°C
- Hydration (drinking water): -2°C temporary

**Environmental Modifiers**:
```
Base Temp = Biome Temperature ± Time of Day ± Weather
Time of Day: 6 AM (+0°C) → 6 PM (+5°C, peak heat) → Midnight (-10°C)
Weather: Clear (+0°C), Cloudy (-3°C), Raining (-5°C), Blizzard (-20°C)
Altitude: Each 100m elevation = -0.5°C
Wind: Strong wind = -5°C + movement penalty
```

### 4. Radiation (0–100, one-way counter)
**Starts at**: 0
**NEVER decreases** (accumulates permanently)
**Critical threshold**: 75+
**Effects**:
- 0–25: No effect (background radiation)
- 25–50: Mild nausea audio cues
- 50–75: Vomiting (visual effect), -10% movement speed, Geiger counter clicking increases
- 75–100: Bleeding from orifices, vomiting, severe pain, death imminent
- 100+: Acute radiation sickness, death in 1–3 days

**Exposure sources**:
- Chernobyl zone (varies by location, up to +2 radiation/second)
- Radiation storms (temporary global spike)
- Contaminated food/water (+5–20 radiation)
- Fallout (visible after explosions/storms)

**Mitigation**:
- Geiger counter (detects zones)
- Lead-lined shelter (-50% radiation exposure while inside)
- Anti-radiation pills (rare, reduce exposure rate temporarily)
- Decontamination shower (removes surface contamination only)
- Medical treatment (slows progression, doesn't reverse)

### 5. Injury (0–100)
**Starts at**: 0
**Decay rate**: -0.2 points/second (heals slowly while resting)
**Critical threshold**: Above 60
**Types of injury**:
- **Open wound**: Bleeds continuously (-0.5 health/second), infection risk +2%/hour
- **Broken bone**: Severe movement penalty (-50%), healing takes 10+ hours
- **Internal bleeding**: Health damage (-5 points/minute), not visible until severe
- **Burns**: Movement penalty, severe pain, infection risk
- **Infection/Sepsis**: Progresses over 3–5 days if untreated, leads to death

**Healing options**:
- Rest (minimal healing, -0.2 injury/second in safe location)
- Bandaging (removes open wound status, +5 sanity, uses cloth resource)
- Antiseptic (prevents infection if applied immediately)
- Antibiotics (halts infection progression, very rare)
- Surgery (requires skill, tools, risks going worse)
- Field amputation (extreme measure, permanent stat loss)

**Complication example**:
```
Event: Player shot in leg
Effects: Injury +60, movement -50%, bleeding -0.5 health/sec

Player chooses NOT to treat:
Hour 1: Bleeding continues, Injury stays at 60
Hour 2: Infection begins (+1% risk now fulfilled), enters "Infected" state
Hour 4: Sepsis progresses, Health -2/sec, Fever (hallucinations begin)
Hour 8: Organ failure imminent, unless antibiotics administered
Hour 12: Death (unless medical intervention)
```

### 6. Exhaustion (0–100)
**Starts at**: 0
**Accumulates from**: Sprinting (+5/sec), climbing (+3/sec), swimming (+4/sec), combat (+6/sec)
**Decays from**: Rest (-2/sec), sleep (-5/sec), eating food (-1/sec)
**Critical threshold**: 80+
**Effects**:
- 0–40: No effect (normal stamina)
- 40–70: Slightly slower movement, occasional stumbling
- 70–100: Movement -30%, higher mistake rate in crafting, speech slurred
- 100: Complete collapse, forced to rest for 30 seconds
- While collapsed: Vulnerable to predators, NPCs can steal supplies

**Recovery**:
- 4–6 hours sleep in safe location: Full recovery
- 1–2 hours rest in dangerous location: Partial recovery
- Sleep interrupted: Exhaustion partially recovered (dangerous to be caught sleeping)
- Eating food: -1 exhaustion per food consumed

### 7. Sanity (0–100)
**Starts at**: 50 (neutral psychological state)
**Decreases from**: Witnessing death (-10), prolonged isolation >48 hours (-1/min), eating human flesh (-50), committing atrocities (-5 per kill above 3)
**Increases from**: Social interaction (+5), helping others (+3), finding shelter (+2), small victories (+1)
**Critical threshold**: Below 30 (severe breakdown)
**Effects**:
- 50–75: Normal perception
- 30–50: Mild paranoia, NPCs appear slightly less trustworthy, audio distortion
- 10–30: Significant hallucinations (shadowy figures), unreliable UI (stats randomly spike/drop), hearing voices
- 0–10: Severe breakdown, suicidal ideation, player may walk off cliffs
- 0: Game over (player suicide)

**Sanity-affecting events**:
- Witness death of NPC: -15 sanity
- Find mass grave: -20 sanity
- Eat human flesh: -50 sanity
- Kill innocent NPC: -25 sanity
- Kill in self-defense: -5 sanity
- Spend 48+ hours alone: -1 sanity/minute
- Kill animal for food: -2 sanity (survival necessity)
- Help stranger: +5 sanity
- Rest in shelter: +1 sanity/minute
- Reach milestone/safe zone: +10 sanity

### 8. Health (0–100, aggregated)
**Calculated from**: All other stats
**Formula**:
```
Health = 100
        - (0.1 * max(0, 20 - Hunger))        // Starvation damage
        - (0.2 * max(0, 15 - Thirst))        // Dehydration damage
        - (0.15 * max(0, Radiation - 75))    // Radiation sickness
        - (0.5 * max(0, Injury - 20))        // Injury complications
        - (0.1 * max(0, Exhaustion - 80))    // Collapse damage
        - (0.05 * max(0, Sanity - 0))        // Psychological damage
        - (Cold exposure penalties)
```

**Death threshold**: 0 health triggers death sequence

---

## Stat Interactions (The Cascade)

### Hunger + Cold
When both low, they compound:
- Cold increases metabolism: Hunger decays 1.5x faster
- Hungry body can't regulate temperature: Cold threshold drops -10°C
- Result: Starvation + hypothermia is deadliest combination

### Thirst + Heat
- Heat increases fluid loss: Thirst decays 2x faster in +30°C+ zones
- Dehydrated body can't cool itself: Heat tolerance -10°C
- Dehydration + heat = heat stroke in 10 minutes

### Injury + Activity
- Movement with open wound: Bleeding increases 50%
- Infection + movement: Sepsis accelerates
- Climbing/running with broken limb: Compound fracture, permanent damage risk

### Sanity + Isolation
- Each hour alone: Sanity -1/min (normally decreases much slower)
- Extreme isolation >72 hours: Risk of complete psychological breakdown
- Finding another person: Immediate sanity +10 boost
- But if that person dies: Sanity -20 (double the normal witness penalty)

### Exhaustion + Hunger
- Exhausted state increases hunger decay 1.2x
- Hungry body recovers exhaustion slower
- Must choose: Rest (but get hungrier) or Move (but get more exhausted)

---

## Environmental Modifiers

### Biome Effects

**Paris (Flooded)**
- Base temperature: 8–16°C (cool)
- Humidity: Very high (affects heat/cold perception)
- Water everywhere: Easy to find water, hard to find fire
- Radiation: Low (0.1 baseline)

**Venice (Archipelago)**
- Base temperature: 12–18°C
- Wind effect: Strong winds (-3°C modifier)
- Water: Abundant (but salty, must be desalinated)
- Radiation: Low
- Unique hazard: Buildings sink gradually (time pressure)

**Alps (Mountains)**
- Base temperature: 2–8°C (cold)
- Altitude modifier: Each 100m elevation -0.5°C
- Wind: Can be severe (-5 to -15°C in storms)
- Difficulty: Hypothermia risk very high
- Advantage: Medicinal plants, clean water from snow

**Chernobyl (Exclusion Zone)**
- Base temperature: 6–14°C
- Radiation: 0.5–2.0 baseline (extremely high)
- Danger zones: Specific areas with +5 radiation/second
- Safe zones: Underground bunkers with lead shielding
- Risk/reward: Valuable supplies in most radiated areas

**Scandinavia (Tundra)**
- Base temperature: -20 to -5°C (extreme cold)
- Wind chill: Severe (-10 to -30°C modifier)
- Exhaustion accelerates in extreme cold (-0.5/sec additional)
- Hypothermia risk: Constant threat (must have shelter)
- Resource scarcity: Very few animals, limited plant life

---

## Survival Scenarios & Solutions

### Scenario 1: "I'm starving and dehydrated in the desert"
**Stats**: Hunger 5, Thirst 2, Temp +45°C

**Problem**: Both critical, heat making thirst worse (decays 2x faster), dehydration prevents heat regulation

**Player options**:
1. Find water source (risk of contamination, but restores thirst immediately)
2. Hunt animal (exhausting in heat, but provides food and liquid)
3. Find shelter (reduces heat exposure, but doesn't help hunger/thirst)
4. Wait for night (temperature drops, thirst decay slows)
5. Move toward known settlement (costs exhaustion, but might have supplies)

**Recommended approach**: Find shelter first (reduce heat damage), then locate water (highest priority), then hunt if energy permits

### Scenario 2: "I'm injured and infected in a remote location"
**Stats**: Injury 75 (bleeding wound, infected), Health 35, Sanity 40

**Problem**: Infection accelerating (sepsis risk in 2 hours), bleeding continues, sanity dropping from isolation

**Player options**:
1. Find antibiotics (unlikely without settlement access)
2. Cauterize wound (stop bleeding, but very painful, sanity -10)
3. Attempt surgery (risky without medical skill)
4. Find settlement for medical help (risky, others may be hostile/infected)
5. Rest and hope immune system wins (unlikely, 20% survival chance)

**Recommended**: Reach settlement for antibiotics, or attempt cauterization if isolated

### Scenario 3: "I'm freezing in a blizzard without shelter"
**Stats**: Cold -35°C (hypothermia stage 2), Exhaustion 60, Temp outside -25°C

**Problem**: Hypothermia worsening, must find shelter immediately or die in 15 minutes

**Player options**:
1. Sprint to last known shelter (burns exhaustion quickly, risk of collapse)
2. Build emergency shelter (requires materials, takes 10 minutes, might not survive)
3. Find cave/building nearby (requires luck/knowledge of area)
4. Keep moving (risk exhaustion collapse, but maintains warmth from activity)
5. Stay put and prepare for death (wait and see if storm passes)

**Recommended**: Sprint toward nearest shelter, or build emergency shelter if none nearby

---

## Crafting & Resource Integration

Survival stats determine which crafting recipes are available:

- **High Sanity + Time**: Complex, quality items (better durability)
- **Low Sanity + Rushed**: Poor-quality items (might fail during use)
- **Exhaustion 80+**: Crafting mistakes increase (+50% fail rate)
- **Hunger <20**: Shaking hands (-50% crafting accuracy)

Example:
```
Crafting: Bandage (from cloth)
Normal (Healthy): 95% success, takes 5 seconds
Low sanity (hallucinogenic state): 60% success, takes 8 seconds, might create "infected bandage"
Exhausted (shaking): 70% success, takes 6 seconds
Starving (trembling): 50% success, takes 10 seconds, high failure risk
```

---

## Death Sequences

When any stat hits critical:

### Starvation Death
Player slows down, speech slurs, collapses animation plays. Screen gradually darkens. Diary entry recorded: "I can't remember the last time I ate something real..."

### Dehydration Death
Vision blurs severely, Mirage hallucinations appear, player walks confused, collapses, sepia-tones fade to black. Gurgling audio cue.

### Hypothermia Death
Character shivers violently, speech broken, stumbling movement, eventually lies down. Screen has blue tint, fades. Audio: slowing heartbeat.

### Radiation Sickness Death
Bleeding from nose/mouth, severe pain animations, character vomits repeatedly, collapses with screaming. Screen distorts. Audio: Geiger counter clicks fastest possible speed.

### Sepsis Death
Fever-induced delirium, character wanders aimlessly, sweating, hallucinating, collapses. Vision has reddish tint. Death occurs slowly (3+ minutes).

### Psychological Breakdown
Sanity = 0: Character hears voices, makes final monologue, walks toward cliffs/danger, walks into fire, or sits down and becomes unresponsive (30-second wait, then game over).

---

**END DOCUMENT**
