# Project Backlog

This file mirrors the first GitHub issues and keeps the intended order visible inside the repository.

## Phase 0 - Repository Setup

- [x] Add a project README that explains the archive and reboot direction.
- [x] Expand `.gitignore` for old Visual Studio build outputs and future spike folders.
- [x] Decide whether future implementation lives in this repository or a clean new repository.

## Phase 1 - Archeology

- [x] Reconstruct the playable game specification from `The_Game/`, `The_Game_2/`, `LAN/`, and `Documents/`.
- [x] Build an asset catalog with image dimensions, audio files, likely purpose, and reuse notes.
- [x] Record the differences between the three C++ prototypes.

## Phase 2 - Engine Spikes

- [x] Spike modern C++/SFML with CMake: load one map and move one player.
- [x] Spike Godot 4: load old-style arena assets and implement movement plus shooting.
- [x] Spike web/TypeScript: local two-player arena with keyboard input and screenshot-friendly run flow.
- [x] Choose the v1 implementation path based on iteration friction, testability, and playability.

## Phase 3 - Playable v0

- [ ] Two local players with separate inputs.
- [ ] One arena map with collisions.
- [ ] Shooting, hit detection, health, death, and restart.
- [ ] Armor and speed runes.
- [ ] Minimal menu or immediate restart loop.

## Automation Rules

- One AI iteration should map to one small issue.
- A task may create follow-up issues, but should not silently expand its own scope.
- Every implementation issue should include a verification step: build, test, screenshot, or direct playability check.
- Prefer short-lived branches or small PRs over large unreviewable batches.
