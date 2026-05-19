# Playable Game Specification

This document reconstructs the likely first playable game from the old repository. It separates confirmed behavior from recommended v1 decisions so the reboot can move in small issues instead of guessing from memory.

## Source Evidence

- `Documents/koncept.docx`: original concept keywords: multiplayer, split screen, LAN, online, keyboard, joystick, 8-direction movement, capture the flag, deathmatch.
- `Documents/rozměry.txt`: old dimensions for rocket missile, armor, and bullet.
- `The_Game/The_Game/WorldObject/Game.cpp`: main arena loop, split-screen views, rune spawning, shooting, map draw order, pause/escape events.
- `The_Game/The_Game/WorldObject/Player1.cpp`: player movement, HP UI, sprint input, direction handling.
- `The_Game/The_Game/WorldObject/Character.cpp`: armor/speed buff exclusivity and 10 second buff duration.
- `The_Game/The_Game/WorldObject/Bullet.cpp`: bullet placement, direction, rotation, speed, animation.
- `The_Game/The_Game/WorldObject/Map.cpp` and `The_Game/The_Game/Maps/mapa.txt`: tile map loading.
- `The_Game_2/The_Game_2/LanCreate.cpp` and `The_Game_2/The_Game_2/LanJoin.cpp`: TCP lobby prototype on port 53000.
- `LAN/`: smaller menu/LAN experiment using the same SFML menu ideas.

## Confirmed Original Shape

The game was intended as a local/LAN top-down arena. The main working prototype is not a finished multiplayer game yet; it renders one player through two side-by-side camera views, which looks like split-screen scaffolding rather than complete two-player play.

Confirmed identity:

- top-down arena,
- keyboard input,
- eight-direction movement,
- split-screen as a core presentation idea,
- LAN as a major planned feature,
- deathmatch and capture the flag as planned modes,
- pickups/runes that change player abilities.

## Core Loop

Confirmed loop in `Game::play()`:

1. Clear window.
2. Draw tile map into player 1 view and player 2 view.
3. Read window events.
4. Handle player/rune collisions.
5. Spawn and expire runes.
6. Draw active buffs.
7. Fire and update bullets.
8. Update player movement and UI.
9. Draw runes, bullets, and player into both views.
10. Draw FPS.
11. Update camera views and display.

Recommended v1 loop:

1. Start a local deathmatch round.
2. Move two players in the arena.
3. Shoot projectiles.
4. Pick up temporary runes.
5. Lose HP on hits.
6. Die at 0 HP.
7. Restart the round quickly.

## Players And Inputs

Confirmed:

- Player defaults to 100 HP.
- Current `Player` uses arrow keys for movement.
- `LShift` doubles movement speed while held.
- `LControl` fires bullets.
- Movement supports diagonals and normalizes diagonal speed.
- Direction is stored as a vector and reused when firing.
- Concept document mentions keyboard and joystick.

Recommended v1:

- Two local players.
- Player 1: WASD movement, Left Shift sprint, Space shoot.
- Player 2: arrow movement, Right Shift or Num0 sprint, Right Control shoot.
- Gamepad support remains a later issue unless the chosen engine makes it nearly free.

## Camera And Screen

Confirmed:

- The original `Game` creates a fullscreen SFML window.
- There are two gameplay views:
  - `player1_view`: left 49.5% of screen width, top 95% height.
  - `player2_view`: right 49.5% of screen width, top 95% height.
- There are two bottom bar views for UI, each 50% width and 5% height.
- Both gameplay views currently follow the same single player.
- Camera position is clamped to map boundaries.

Recommended v1:

- If the arena fits on screen, shared camera is acceptable for the first spike.
- If the map is larger than the viewport, keep split-screen as a signature feature.
- Do not block v1 on polished camera effects.

## Movement

Confirmed:

- Movement is eight-directional.
- Diagonal movement uses `sqrt(speed * speed / 2)` so diagonal travel is not faster.
- Sprite direction rows are ordered as Down, Left, Right, Up.
- The newer player code scales movement by elapsed microseconds.
- Older player code clamps movement to the window edge; the newer map-based code does not show complete map collision.

Recommended v1:

- Use fixed or delta-time movement with clear units.
- Add collision against arena bounds and solid tiles.
- Keep sprint as either a held modifier or a later rune-only speed boost, not both if it makes balance noisy.

## Combat

Confirmed:

- Bullet cooldown is 350 ms in `Game::handlingMissiles()`.
- Bullet speed is 2 in old SFML units.
- Bullets move in the player's last direction.
- Bullet rotation supports all eight directions.
- Bullet animation advances every 150 ms.
- Damage code exists on `Character::receiveDamage(int damage)`, but player-vs-player hit handling is not complete in the preserved main loop.

Recommended v1:

- Bullet damage: 20 HP.
- Bullet lifetime: expire on wall hit, player hit, or after a short max range/time.
- Friendly fire is irrelevant for 1v1 and can be enabled by default.
- First v1 does not need weapon variants.

## Health, Death, And Round Flow

Confirmed:

- Player HP is displayed as text.
- Armor has its own HP display in the UI when active.
- There is no confirmed complete death, respawn, score, or round reset implementation.

Recommended v1:

- Players start with 100 HP.
- A player dies at 0 HP.
- Round ends immediately when one player remains alive.
- Restart returns both players, HP, bullets, and runes to initial state.
- Scoreboard can be a follow-up.

## Runes And Buffs

Confirmed:

- Two rune types are implemented: armor rune and speed rune.
- Rune type is selected by `rand() % 2`.
- Rune spawn interval is 500 ms in `Game.cpp` and `Settings.cpp`.
- Runes spawn at random pixel positions inside the map size.
- Runes expire after their configured duration. The base `Rune` exposes `duration`; the observed buff duration is 10 seconds.
- Picking up armor calls `activateArmor()`.
- Picking up speed calls `activateSpeed()`.
- Armor and speed are exclusive:
  - activating armor removes active speed and restores movement speed,
  - activating speed removes active armor,
  - reactivating either refreshes it.
- Armor visual uses two rotating armor sprites.
- Speed buff multiplies movement by 1.5.

Recommended v1:

- Use at most one or two active rune pickups at a time.
- Spawn interval should be slower than 500 ms for a readable duel; start around 5-10 seconds.
- Keep armor and speed as the first two pickups.
- Armor should absorb a fixed amount of damage or block one hit; choose and document during implementation.

## Map And Tiles

Confirmed:

- The main map file is `The_Game/The_Game/Maps/mapa.txt`.
- The first line points to `Maps/mapa.png`.
- Map dimensions are 100 by 100 tiles.
- Tile size is 30 by 30.
- Tile IDs are stored as comma-separated 1-based values and converted to 0-based indexes.
- Tileset dimensions are 120 by 60, so it likely contains 4 by 2 tiles.
- `Grafika/new_map/mapa_1.png` is a rendered 3000 by 3000 map image.
- Old map notes mention:
  - grain/crop for hiding,
  - tree stump as obstacle,
  - dirt as random danger,
  - water as death or damage.

Recommended v1:

- Start with one arena.
- Use simple solid collision tiles first.
- Treat water/hazards/hiding as follow-up mechanics unless the chosen engine makes them cheap.

## LAN

Confirmed:

- `The_Game_2` has a LAN create/join menu prototype.
- Host listens on TCP port 53000.
- Host displays local IP and connected player count.
- Join uses hard-coded IP `192.168.0.128` and port `53000`.
- Start sends one byte to clients; clients reply with a ready boolean.
- `LanServer` and `LanClient` hint at UDP setup, but gameplay synchronization is not implemented.

Recommended v1:

- Do not block v1 on LAN.
- Design gameplay state cleanly so LAN can be added later.
- After local v1, implement LAN as a separate milestone with a deterministic state protocol.

## Minimum v1

The smallest version worth calling playable:

- two local players,
- one arena,
- movement with collision,
- shooting and hit detection,
- HP/death/restart,
- armor rune,
- speed rune,
- a stable run command.

## Open Decisions

- Shared camera first or split-screen first.
- Armor behavior: extra HP pool, one-hit shield, or percentage reduction.
- Whether sprint stays as a baseline input or only exists through speed rune.
- Which engine becomes the v1 implementation path after the three spikes.
