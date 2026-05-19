# Godot 4 Spike

Minimal text-first Godot 4 project for comparing the engine path. The project is intentionally simple so it can be reviewed without opening the editor.

## What It Tests

- Godot 4 project structure.
- One playable arena scene.
- Two local players.
- Split-screen-like two-panel drawing in a single scene.
- Shooting, HP, death, restart.
- Armor and speed runes.

## Required Tools

- Godot 4.x executable.

Current WSL preflight:

- Godot 4.4.1 is available at `~/.local/bin/godot4`.
- Headless script parse and scene smoke checks pass.

## Run

```bash
cd spikes/godot
godot4 --path .
```

If your binary is named `godot`, use:

```bash
godot --path .
```

## Controls

- P1: WASD move, Space shoot.
- P2: Arrow keys move, slash shoot.
- Restart after a win: R.

## Recommendation

Maybe candidate. Godot is a strong fit for a 2D arena game and now runs headlessly, but the web path still has lower automation friction for the current v1.
