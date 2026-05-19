# Our Very First Game

Twelve-year-old prototype for a local/LAN top-down arena game inspired by old-school split-screen play. The original code was written while learning C++ and SFML, so this repository is currently more useful as a source archive than as a modern build target.

The near-term goal is not a heroic rewrite. It is to reconstruct the actual game idea, decide on a low-friction technology path, and then let small AI-driven tasks move the project toward a playable v1.

## Current State

- Original technology: C++ with SFML 2.2, Visual Studio 2013, Win32.
- Default branch: `master`.
- Main game prototype: `The_Game/`.
- Menu/LAN prototype: `The_Game_2/`.
- Smaller LAN experiment: `LAN/`.
- LibGDX scaffold: `Java/`, mostly default generated code.
- Vendored legacy SFML: `SFML/`.
- Assets and old notes: `Grafika/`, `Sounds/`, `Documents/`, `Fonts/`.

The old Visual Studio projects contain absolute Windows paths and Windows-style includes. Some source files can be inspected or syntax-checked, but the repository should not be treated as ready to build on a modern machine.

## Game Idea

The preserved code and documents point to a simple arena game:

- 2-4 players, initially local split-screen or shared-screen.
- Top-down movement in eight directions.
- Deathmatch as the first complete mode.
- LAN as a later identity feature, not the first blocker.
- Bullets or missiles with cooldowns.
- Runes/pickups that temporarily change player abilities.
- Maps with obstacles, hiding spots, and hazards.

Important old mechanics already visible in code:

- split-screen via SFML views,
- tile map loading,
- player health and direction,
- bullet firing,
- armor rune,
- speed rune,
- exclusive buffs where one rune replaces the previous one.

## Recommended Direction

Use this repository as the canon archive for rules, assets, and history. Before committing to a full implementation, run small engine spikes:

1. Modern C++/SFML with CMake.
2. Godot 4.
3. Web/TypeScript with Canvas or Pixi.

Pick the path by friction: how quickly an agent can implement, run, screenshot-test, and iterate on a playable slice.

Current v1 implementation path: `v1-web/`.

## Definition Of v1

A good first version is deliberately small:

- two local players,
- one playable map,
- movement and collision,
- shooting,
- health, death, and restart,
- armor and speed runes,
- basic menu or restart flow,
- repeatable local run instructions.

LAN, online play, richer modes, and better assets can come later.

## Working Method

This project should advance through small GitHub issues. Each issue should have:

- one clear outcome,
- acceptance criteria,
- a test or screenshot gate when possible,
- permission to create follow-up issues when new work is discovered.

Avoid long single-agent marathons. The useful loop is:

1. pick one issue,
2. implement the smallest working slice,
3. verify it,
4. update the backlog,
5. repeat.

## More Context

The workspace project brief lives outside this repository:

`/home/jigs/.openclaw/workspace/projects/our-very-first-game/README.md`
