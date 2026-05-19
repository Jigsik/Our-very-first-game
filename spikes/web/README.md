# Web TypeScript Spike

Minimal browser prototype for the reboot path. It intentionally favors fast AI iteration and screenshot-friendly verification over engine completeness.

## What It Tests

- TypeScript game loop.
- Canvas rendering.
- Old map parsing from `The_Game/The_Game/Maps/mapa.txt`.
- Old tileset and sprites loaded from the archive.
- Two local players.
- Split-screen cameras.
- Shooting, HP, death, restart.
- Armor and speed runes.

## Run

```bash
cd spikes/web
npm install
npm run dev
```

Open:

```text
http://localhost:5177/spikes/web/
```

## Controls

- P1: WASD move, Left Shift sprint, Space shoot.
- P2: Arrow keys move, Right Shift sprint, slash shoot.
- Restart after a win: R.

## Recommendation

Continue candidate. This path has the lowest current friction because the local environment already has Node/npm and the prototype can be verified in a browser without native graphics libraries.
