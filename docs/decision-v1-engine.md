# Decision: v1 Engine Path

Status: provisional decision, 2026-05-19.

## Decision

Use the web/TypeScript path for the first playable v1 slice.

Keep Godot as the strongest alternate if editor/runtime installation becomes cheap. Keep modern C++/SFML as an archive/learning path, not the default AI-only implementation path.

## Why

The current goal is minimum-prompt AI iteration. That means the winning path is the one an agent can build, run, inspect, screenshot, and change repeatedly with the least environment friction.

The web spike is the only path that is fully runnable in the current WSL environment without sudo or a native editor install.

## Comparison

| Path | AI iteration friction | Build/run reliability | Screenshot/playtest verification | Asset reuse | LAN/split-screen future | Result |
| --- | --- | --- | --- | --- | --- | --- |
| Web/TypeScript | Low | High in current env | Good once Playwright browser is installed; HTTP gate works now | Good; can load old PNG/TXT assets directly | Good for local, workable for WebSocket LAN later | Continue |
| Godot 4 | Medium | Blocked: Godot missing | Good after Godot install | Medium; best if assets are imported into project | Strong for 2D local play, LAN possible | Maybe |
| Modern C++/SFML | High | Blocked: CMake/libsfml-dev missing | Medium; native window is harder in WSL | Good; closest to original | Strong but more manual | Defer |

## Spike Results

### Web/TypeScript

Location: `spikes/web/`

Implemented:

- TypeScript game loop.
- Canvas rendering.
- Two local players.
- Split-screen cameras.
- Shooting, HP, death, restart.
- Armor and speed runes.
- Old map parsing from `The_Game/The_Game/Maps/mapa.txt`.
- Old tileset/player/bullet/rune assets loaded from the repository.
- Local Node static server.

Validation:

- `npm install`
- `npm run check`
- `npm run build`
- `npm run dev`
- `curl http://localhost:5177/spikes/web/`
- `curl http://localhost:5177/The_Game/The_Game/Maps/mapa.txt`
- `curl -I http://localhost:5177/The_Game/The_Game/Maps/mapa.png`

Screenshot gate:

- Attempted with `npx playwright screenshot --browser chromium http://localhost:5177/spikes/web/ /tmp/ofg-web-spike.png`.
- Blocked. Martin tried `npx playwright install --with-deps chromium`, but Playwright 1.60 reports that Chromium is not supported on `ubuntu26.04-x64`.
- Keep #11 open and solve later via a supported browser path, pinned Playwright/browser version, system Chromium, or another screenshot tool.

### Godot 4

Location: `spikes/godot/`

Implemented:

- Text-first Godot project.
- One `Node2D` arena scene.
- GDScript loop for two players, shooting, HP, restart, and armor/speed runes.

Validation:

- `~/.local/bin/godot4 --headless --path spikes/godot --check-only --script scripts/arena.gd`
- `~/.local/bin/godot4 --headless --path spikes/godot --quit-after 3`
- Both passed after Martin installed Godot 4.4.1.

### Modern C++/SFML

Location: `spikes/sfml-cmake/`

Implemented:

- Isolated CMake project.
- C++17 source.
- Old map parsing.
- Old tileset/player loading.
- Two local players.
- Split-screen views.
- Basic shooting.

Validation:

- `g++ -std=c++17 -I ../../SFML/include -DREPO_ROOT=... -fsyntax-only src/main.cpp` passed against the vendored SFML headers.
- Updated the spike to SFML 3.0.2 after Martin installed native dependencies.
- `cmake -S . -B build`
- `cmake --build build`
- Full build passed.

## First v1 Implementation Issues

1. Promote the web spike into a real `v1-web` implementation folder with stable structure.
2. Add deterministic map collision based on parsed tile IDs.
3. Add proper two-player round state: countdown, win message, score, restart.
4. Add a Playwright/browser verification gate once Chromium is installed.
5. Add lightweight backlog automation that picks one implementation issue for `ai/reboot` and reports to Discord.

## Repository Strategy

Use this repository for the reboot for now, on the long-running `ai/reboot` branch. The old code remains the archive; new implementation work should stay isolated under a new folder so the legacy code is not churned unnecessarily.
