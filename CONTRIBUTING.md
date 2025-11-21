# Contributing to AETERNA

Thank you for your interest in contributing to AETERNA: The Last Breath of Earth!

## Code Style Guidelines

### C++ Standards
- Use modern C++ (C++17 minimum)
- Follow Unreal Engine 5 coding standards
- Use `UPROPERTY()` and `UFUNCTION()` macros for editor exposure
- Prefer const correctness
- Use meaningful variable names (no single-letter variables except loop counters)

### Naming Conventions
- Classes: `AActorName`, `UComponentName`, `FStructName`
- Variables: `CamelCase` (member variables with `m_` prefix in some contexts)
- Functions: `VerbNoun()` (e.g., `ApplyDamage()`, `RestoreHealth()`)
- Enums: `EEnumName` with `UENUM()` macro
- Constants: `CONSTANT_NAME` or `CamelCase` depending on context

### Comment Style
- Use `//` for single-line comments
- Use `/* */` for multi-line comments
- Document complex algorithms with explanation of intent
- Do NOT over-comment obvious code

### Blueprint Conventions
- Organize variables into categories using `Category="Category Name"`
- Mark frequently-accessed functions as `BlueprintCallable`
- Expose only necessary variables (prefer private with accessors)

## Branching Strategy

We follow Git Flow:
- `main`: Production-ready code
- `develop`: Integration branch for features
- `feat/FEATURE-NAME`: Feature branches
- `fix/BUG-NAME`: Bug fix branches

## Commit Message Format

```
[TYPE] Brief description (50 chars max)

Detailed explanation (72 chars per line)
- Use bullet points for multiple changes
- Reference issues: Closes #123
- Explain WHY, not WHAT
```

Types:
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation
- `style`: Code formatting
- `refactor`: Code restructuring
- `perf`: Performance improvement
- `test`: Tests added/modified

Example:
```
[feat] Add radiation storm system

Implements procedural radiation storms that:
- Increase radiation exposure by 0.3/sec
- Reduce visibility by 50%
- Create audio ambience

Closes #45
```

## Development Setup

1. Clone the repository
2. Install UE 5.4+
3. Generate Visual Studio project: `./Aeterna/GenerateProjectFiles.bat`
4. Open in Visual Studio 2022
5. Compile and open in Unreal Editor

## Testing Requirements

- All new gameplay systems must have corresponding test maps
- Vertical slice features must be playtested before PR
- Run pre-commit validation: `python3 Tools/Validation/validate.py`

## Performance Guidelines

- Target 60fps on RTX 4090 (1440p with ray tracing enabled)
- Profile before optimization (use Unreal Profiler)
- Submit performance metrics with any heavy features
- Use LOD systems for distant objects

## Documentation

- Update GDD if design changes
- Add code comments for non-obvious logic
- Document new systems in `Docs/Technical/`
- Update README if adding major features

## Pull Request Process

1. Create feature branch from `develop`
2. Make atomic commits with clear messages
3. Submit PR with description of changes
4. Link related issues
5. Ensure CI passes (build validation, linting)
6. Request review from maintainers
7. Address feedback and rebase if needed
8. Squash commits if requested
9. Merge to `develop` when approved

## Code Review Standards

- Be constructive and respectful
- Suggest improvements, don't demand
- Approve when code meets quality standards
- Request changes only for blocking issues

## Questions?

- Check existing documentation first
- Ask in Discord #development-questions
- Contact: dev@aeterna-game.dev

---

**Remember**: Every line of code you write becomes part of Earth's final story.
