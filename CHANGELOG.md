# AETERNA: The Last Breath of Earth - Changelog

All notable changes to AETERNA will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Core Game Mode framework (AeternaGameMode)
- Survival Component system with 8 interconnected stats
  - Hunger, Thirst, Cold/Heat, Radiation, Injury, Exhaustion, Sanity, Health
- Choice Tracker system for 27 different endings
- Memory Echo narrative system with 4 initial echoes
- Survival Manager for environmental conditions and resource management
- World Partition support for 400km² seamless streaming
- Basic configuration files (DefaultEngine.ini, DefaultGame.ini)
- Comprehensive design documentation (35+ pages)
- C++ foundation for gameplay systems

### In Progress
- Paris Overgrown vertical slice level
- Bioluminescent ecosystem implementation
- NPC AI framework (Mass Entity)
- Dynamic weather system
- Crafting and base-building mechanics
- Full dialogue system with 8 languages

### Planned
- Venice Archipelago region
- Alpine Refuge region
- Chernobyl 2.0 region
- Scandinavian Tundra region
- 35+ NPC characters with full behavior trees
- Permadeath Iron Mode
- Co-op Ghost Mode
- All 27 ending cinematics
- Wwise audio integration

## [0.1.0] - 2025-01-15

### Initial Commit
- Project structure established
- Unreal Engine 5.4 support configured
- .gitignore and Git LFS setup
- README and documentation baseline
- Core gameplay framework skeleton

---

## Version History

### v0.1.0 (Vertical Slice Foundation)
**Release Date**: 2025-01-15  
**Status**: In Development

**Features**:
- Game Mode framework
- Survival stat system
- Choice tracking
- Memory Echo system
- Manager classes for survival/narrative

**Known Limitations**:
- Only core systems implemented (no playable content yet)
- No visuals/audio
- Placeholder ending calculations
- Single test level not yet created

**Next Milestone**: Vertical Slice Completion (Paris Region, Day 47)

---

## Deprecated Features

None yet. All current features are under active development.

---

## Notes on Versioning

We use:
- **Major version** (X.0.0): Regional releases (each explorable region)
- **Minor version** (0.X.0): System implementations (crafting, NPCs, etc.)
- **Patch version** (0.0.X): Bug fixes and refinements

Expected timeline:
- v0.1.0 → v0.2.0: Core systems + Vertical Slice
- v0.2.0 → v0.3.0: Narrative system + Memory Echoes
- v0.3.0 → v1.0.0: Paris region complete
- v1.0.0 → v2.0.0: Venice region + multiplayer
- ...and so on through launch

---

## Contributing

See CONTRIBUTING.md for guidelines on submitting changes.

---

## License

AETERNA: The Last Breath of Earth © 2087 Studios, 2025. All rights reserved.

---

**Last Updated**: 2025-01-15
