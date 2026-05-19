# v1 Web

Active implementation path for the first playable reboot. The old code remains in the repository as the archive; this folder is where the new browser-based version should grow.

## Current Features

- TypeScript game loop.
- Canvas renderer.
- Two local players.
- Split-screen cameras.
- Deterministic collision against selected solid tiles.
- Shooting, HP, death, score, countdown, and restart.
- Armor and speed runes.
- Compact generated v1 arena using the old tileset.
- Old sprite and tileset assets loaded from the repository without duplicating binaries.

## Run

```bash
cd v1-web
npm install
npm run dev
```

Open:

```text
http://localhost:5177/v1-web/
```

## Controls

- P1: WASD move, Left Shift sprint, Space shoot.
- P2: Arrow keys move, Right Shift sprint, slash shoot.
- Restart after a win: R. Score persists across rounds.

## Verification

```bash
npm run check
npm run build
npm run dev
curl -fsS http://localhost:5177/v1-web/
```

Visual screenshot verification is tracked separately because Playwright Chromium is not installed in the current environment.

## Arena And Collision

The active v1 game uses a compact generated arena instead of the archived 100x100 `The_Game/The_Game/Maps/mapa.txt`. The old map stays in the repo as source material, but the generated arena is faster to playtest and easier to balance.

The old tileset is 4 columns by 2 rows. The generated arena uses the same 0-based tile IDs as the parsed old map.

Solid in v1:

- 0: stones
- 1: stump
- 3: wall/brick

Water and crop are intentionally not solid yet. They can become hazards or hiding mechanics in later issues.

Player and initial rune spawns are normalized through a nearest-open-position check so they do not start inside solid tiles or tiny blocked pockets.
